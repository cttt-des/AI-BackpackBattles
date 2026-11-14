#!/usr/bin/env python3
"""gd_to_cpp.py — Transpile all 663 GDScript files in gd_core/ & gd_core_items/ to C++20.

Outputs into native_sim/gen/:
  - sym_ids.hpp / sym_ids.cpp     Compile-time SymId enum + symbol table
  - class_metas.hpp               Forward declarations of all GdClassMeta globals
  - register_all.cpp              Registers all classes (topological base-first order)
  - hdrs/<cls>.hpp                One lightweight header per class
  - shards/shard_XX.cpp           16 parallel-compilable C++ shards

Usage:
  python tools/gd_to_cpp.py --parse-only   # Verify AST parse of all 663 .gd files
  python tools/gd_to_cpp.py                # Generate native_sim/gen/
"""
from __future__ import annotations

import argparse
import dataclasses
import os
import pathlib
import re
from typing import Any, Dict, List, Optional, Set, Tuple

ROOT = pathlib.Path(__file__).resolve().parent.parent
SRC_DIRS = ("gd_core", "gd_core_items")
GEN_DIR = ROOT / "native_sim" / "gen"
BUILTIN_SYMS_HDR = ROOT / "native_sim" / "builtin_syms.hpp"

BUILTIN_TYPE_MAP = {
    "void", "bool", "int", "float", "String", "Array", "Dictionary",
    "Vector2", "Vector3", "Color", "Reference", "Object", "Node",
    "Node2D", "Resource", "FuncRef", "RandomNumberGenerator",
    "PoolStringArray", "PoolByteArray", "PoolIntArray", "PoolRealArray",
    "PoolVector2Array", "PoolColorArray",
}

GD_TYPE_DEFAULTS = {
    "bool": "gd::GdVal::from_bool(false)",
    "int": "gd::GdVal::from_int(0)",
    "float": "gd::GdVal::from_float(0.0)",
    "String": "gd::GdVal::from_cstr(gd_ctx.arena, \"\")",
    "Array": "gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena))",
    "Dictionary": "gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))",
    "Vector2": "gd::GdVal::from_vec2(0.0, 0.0)",
    "Color": "gd::make_color_from_args(nullptr, 0)",
    "PoolStringArray": "gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena))",
    "PoolByteArray": "gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena))",
    "PoolIntArray": "gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena))",
    "PoolRealArray": "gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena))",
    "PoolVector2Array": "gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena))",
    "PoolColorArray": "gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena))",
}


def load_builtin_syms() -> Dict[str, str]:
    """Read native_sim/builtin_syms.hpp as single source of truth."""
    txt = BUILTIN_SYMS_HDR.read_text(encoding="utf-8")
    out: Dict[str, str] = {}
    for m in re.finditer(r'X\(\s*([A-Za-z_]\w*)\s*,\s*"([^"]+)"\s*\)', txt):
        out[m.group(2)] = m.group(1)
    return out


# ═══════════════════════════════ Lexer ═══════════════════════════════

@dataclasses.dataclass
class Tok:
    kind: str  # IDENT, INT, FLOAT, STR, OP, NEWLINE, INDENT, DEDENT, EOF
    val: str
    line: int


MULTI_OPS = (
    "<<=", ">>=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=",
    ":=", "->", "==", "!=", "<=", ">=", "<<", ">>", "&&", "||",
)


def lex_gdscript(src: str, filename: str = "") -> List[Tok]:
    tokens: List[Tok] = []
    indent_stack = [0]
    lines = src.splitlines()
    paren_depth = 0
    in_block_comment = False

    for lineno, raw_line in enumerate(lines, 1):
        # Quick scan preserving strings, stripping # comments, counting parens
        line = raw_line
        # Compute leading tabs/spaces if paren_depth == 0
        pos = 0
        n = len(line)
        indent = 0
        while pos < n and line[pos] in ("\t", " "):
            indent += 4 if line[pos] == "\t" else 1
            pos += 1

        # Check if line is empty or comment-only
        rest_tmp = pos
        if rest_tmp >= n or line[rest_tmp] == "#":
            continue

        if paren_depth == 0:
            if indent > indent_stack[-1]:
                indent_stack.append(indent)
                tokens.append(Tok("INDENT", "", lineno))
            elif indent < indent_stack[-1]:
                while len(indent_stack) > 1 and indent < indent_stack[-1]:
                    indent_stack.pop()
                    tokens.append(Tok("DEDENT", "", lineno))
                if indent != indent_stack[-1]:
                    raise SyntaxError(f"{filename}:{lineno}: inconsistent indent {indent} vs {indent_stack}")

        line_has_tokens = False
        while pos < n:
            c = line[pos]
            if c in (" ", "\t", "\r"):
                pos += 1
                continue
            if c == "#":
                break
            if c in ('"', "'"):
                q = c
                pos += 1
                buf = []
                while pos < n:
                    ch = line[pos]
                    if ch == "\\":
                        pos += 1
                        if pos < n:
                            esc = line[pos]
                            if esc == "n":
                                buf.append("\n")
                            elif esc == "t":
                                buf.append("\t")
                            elif esc == "r":
                                buf.append("\r")
                            elif esc == "\\":
                                buf.append("\\")
                            elif esc == '"':
                                buf.append('"')
                            elif esc == "'":
                                buf.append("'")
                            else:
                                buf.append(esc)
                            pos += 1
                        continue
                    if ch == q:
                        pos += 1
                        break
                    buf.append(ch)
                    pos += 1
                tokens.append(Tok("STR", "".join(buf), lineno))
                line_has_tokens = True
                continue
            # Number: hex or int or float (including .5)
            if c.isdigit() or (c == "." and pos + 1 < n and line[pos + 1].isdigit()):
                start = pos
                if c == "0" and pos + 1 < n and line[pos + 1] in ("x", "X"):
                    pos += 2
                    while pos < n and (line[pos].isdigit() or line[pos].lower() in "abcdef_"):
                        pos += 1
                    tokens.append(Tok("INT", line[start:pos].replace("_", ""), lineno))
                else:
                    is_float = False
                    while pos < n and (line[pos].isdigit() or line[pos] == "_"):
                        pos += 1
                    if pos < n and line[pos] == "." and (pos + 1 < n and line[pos + 1].isdigit() or c == "."):
                        is_float = True
                        pos += 1
                        while pos < n and (line[pos].isdigit() or line[pos] == "_"):
                            pos += 1
                    elif pos < n and line[pos] == "." and (pos + 1 >= n or not line[pos + 1].isalpha()):
                        # e.g. `1.` trailing dot
                        if pos + 1 >= n or line[pos + 1] != ".":
                            is_float = True
                            pos += 1
                    if pos < n and line[pos] in ("e", "E"):
                        is_float = True
                        pos += 1
                        if pos < n and line[pos] in ("+", "-"):
                            pos += 1
                        while pos < n and line[pos].isdigit():
                            pos += 1
                    num_txt = line[start:pos].replace("_", "")
                    tokens.append(Tok("FLOAT" if is_float else "INT", num_txt, lineno))
                line_has_tokens = True
                continue
            # Identifier
            if c.isalpha() or c == "_":
                start = pos
                while pos < n and (line[pos].isalnum() or line[pos] == "_"):
                    pos += 1
                tokens.append(Tok("IDENT", line[start:pos], lineno))
                line_has_tokens = True
                continue
            # Multi-char operators
            matched = None
            for op in MULTI_OPS:
                if line.startswith(op, pos):
                    matched = op
                    break
            if matched:
                tokens.append(Tok("OP", matched, lineno))
                pos += len(matched)
                line_has_tokens = True
                continue
            # Single char op/punct
            if c in "([{":
                paren_depth += 1
            elif c in ")]}":
                paren_depth -= 1
            tokens.append(Tok("OP", c, lineno))
            pos += 1
            line_has_tokens = True

        if paren_depth == 0 and line_has_tokens:
            tokens.append(Tok("NEWLINE", "", lineno))

    while len(indent_stack) > 1:
        indent_stack.pop()
        tokens.append(Tok("DEDENT", "", len(lines) + 1))
    tokens.append(Tok("EOF", "", len(lines) + 1))
    return tokens


# ═══════════════════════════════ AST & Parser ═══════════════════════════════

class Expr:
    pass

@dataclasses.dataclass
class LitExpr(Expr):
    kind: str  # null, bool, int, float, str
    val: Any

@dataclasses.dataclass
class IdentExpr(Expr):
    name: str

@dataclasses.dataclass
class ArrayExpr(Expr):
    elems: List[Expr]

@dataclasses.dataclass
class DictExpr(Expr):
    pairs: List[Tuple[Expr, Expr]]

@dataclasses.dataclass
class UnaryExpr(Expr):
    op: str
    expr: Expr

@dataclasses.dataclass
class BinExpr(Expr):
    op: str
    left: Expr
    right: Expr

@dataclasses.dataclass
class TernaryExpr(Expr):
    then_e: Expr
    cond_e: Expr
    else_e: Expr

@dataclasses.dataclass
class AttrExpr(Expr):
    recv: Expr
    attr: str

@dataclasses.dataclass
class IndexExpr(Expr):
    recv: Expr
    key: Expr

@dataclasses.dataclass
class CallExpr(Expr):
    callee: Expr
    args: List[Expr]

@dataclasses.dataclass
class SuperCallExpr(Expr):
    method: str
    args: List[Expr]

@dataclasses.dataclass
class IsExpr(Expr):
    expr: Expr
    type_name: str


class Stmt:
    pass

@dataclasses.dataclass
class PassStmt(Stmt): pass

@dataclasses.dataclass
class BreakStmt(Stmt): pass

@dataclasses.dataclass
class ContinueStmt(Stmt): pass

@dataclasses.dataclass
class ReturnStmt(Stmt):
    expr: Optional[Expr]

@dataclasses.dataclass
class VarStmt(Stmt):
    name: str
    type_ann: Optional[str]
    init: Optional[Expr]
    is_const: bool = False

@dataclasses.dataclass
class AssignStmt(Stmt):
    target: Expr
    op: str
    val: Expr

@dataclasses.dataclass
class ExprStmt(Stmt):
    expr: Expr

@dataclasses.dataclass
class IfStmt(Stmt):
    branches: List[Tuple[Expr, List[Stmt]]]
    else_body: List[Stmt]

@dataclasses.dataclass
class WhileStmt(Stmt):
    cond: Expr
    body: List[Stmt]

@dataclasses.dataclass
class ForStmt(Stmt):
    var: str
    seq: Expr
    body: List[Stmt]

@dataclasses.dataclass
class MatchStmt(Stmt):
    expr: Expr
    arms: List[Tuple[List[Expr], List[Stmt]]]  # empty pats list = `_` default


@dataclasses.dataclass
class ParamDecl:
    name: str
    type_ann: Optional[str]
    default: Optional[Expr]


@dataclasses.dataclass
class FuncDecl:
    name: str
    is_static: bool
    params: List[ParamDecl]
    ret_type: Optional[str]
    body: List[Stmt]


@dataclasses.dataclass
class VarDecl:
    name: str
    type_ann: Optional[str]
    init: Optional[Expr]
    is_const: bool


@dataclasses.dataclass
class EnumDecl:
    name: Optional[str]
    members: List[Tuple[str, int]]


@dataclasses.dataclass
class ClassDecl:
    name: Optional[str]
    extends: Optional[str]
    signals: List[str]
    enums: List[EnumDecl]
    vars: List[VarDecl]
    funcs: List[FuncDecl]
    inner_classes: List["ClassDecl"]


class Parser:
    def __init__(self, tokens: List[Tok], filename: str):
        self.toks = tokens
        self.pos = 0
        self.filename = filename

    def cur(self) -> Tok:
        return self.toks[self.pos]

    def peek(self, k: int = 1) -> Tok:
        idx = min(self.pos + k, len(self.toks) - 1)
        return self.toks[idx]

    def accept(self, kind: str, val: Optional[str] = None) -> Optional[Tok]:
        t = self.cur()
        if t.kind == kind and (val is None or t.val == val):
            self.pos += 1
            return t
        return None

    def expect(self, kind: str, val: Optional[str] = None) -> Tok:
        t = self.cur()
        if t.kind != kind or (val is not None and t.val != val):
            raise SyntaxError(f"{self.filename}:{t.line}: expected {kind} {val!r}, got {t.kind} {t.val!r}")
        self.pos += 1
        return t

    def skip_newlines(self):
        while self.cur().kind == "NEWLINE":
            self.pos += 1

    def parse_class(self, name: Optional[str] = None, extends: Optional[str] = None, is_inner: bool = False) -> ClassDecl:
        cls = ClassDecl(name=name, extends=extends, signals=[], enums=[], vars=[], funcs=[], inner_classes=[])
        while True:
            self.skip_newlines()
            t = self.cur()
            if t.kind == "EOF" or (is_inner and t.kind == "DEDENT"):
                if is_inner and t.kind == "DEDENT":
                    self.pos += 1
                break
            if t.kind == "IDENT" and t.val == "extends":
                self.pos += 1
                if self.cur().kind == "STR":
                    cls.extends = '"' + self.cur().val + '"'
                    self.pos += 1
                else:
                    cls.extends = self.expect("IDENT").val
                self.skip_stmt_end()
                continue
            if t.kind == "IDENT" and t.val == "class_name":
                self.pos += 1
                cls.name = self.expect("IDENT").val
                self.skip_stmt_end()
                continue
            if t.kind == "IDENT" and t.val == "signal":
                self.pos += 1
                sig_name = self.expect("IDENT").val
                if self.accept("OP", "("):
                    while self.cur().kind != "EOF" and not (self.cur().kind == "OP" and self.cur().val == ")"):
                        self.pos += 1
                    self.expect("OP", ")")
                cls.signals.append(sig_name)
                self.skip_stmt_end()
                continue
            if t.kind == "IDENT" and t.val == "enum":
                cls.enums.append(self.parse_enum())
                continue
            if t.kind == "IDENT" and t.val == "class":
                self.pos += 1
                iname = self.expect("IDENT").val
                iext = None
                if self.accept("IDENT", "extends"):
                    iext = self.expect("IDENT").val
                self.expect("OP", ":")
                self.expect("NEWLINE")
                self.expect("INDENT")
                cls.inner_classes.append(self.parse_class(iname, iext, is_inner=True))
                continue
            # Modifiers on var / const / func
            if t.kind == "IDENT" and t.val in ("onready", "export", "var", "const"):
                cls.vars.append(self.parse_var_decl())
                continue
            if t.kind == "IDENT" and (t.val == "func" or (t.val == "static" and self.peek().val == "func")):
                cls.funcs.append(self.parse_func())
                continue
            if t.kind == "IDENT" and t.val == "tool":
                self.pos += 1
                self.skip_stmt_end()
                continue
            raise SyntaxError(f"{self.filename}:{t.line}: unexpected class-level token {t}")
        return cls

    def skip_stmt_end(self):
        if self.cur().kind == "NEWLINE":
            self.pos += 1

    def _eval_enum_expr(self, e: Expr, env: Dict[str, int]) -> int:
        if isinstance(e, LitExpr) and e.kind == "int":
            return int(e.val)
        if isinstance(e, IdentExpr):
            return env[e.name]
        if isinstance(e, UnaryExpr):
            v = self._eval_enum_expr(e.expr, env)
            return -v if e.op == "-" else (~v if e.op == "~" else v)
        if isinstance(e, BinExpr):
            l = self._eval_enum_expr(e.left, env)
            r = self._eval_enum_expr(e.right, env)
            return {
                "+": l + r, "-": l - r, "*": l * r, "/": int(l / r),
                "|": l | r, "&": l & r, "^": l ^ r, "<<": l << r, ">>": l >> r,
            }[e.op]
        raise SyntaxError(f"{self.filename}: non-constant enum expr {e}")

    def parse_enum(self) -> EnumDecl:
        self.expect("IDENT", "enum")
        ename = None
        if self.cur().kind == "IDENT":
            ename = self.cur().val
            self.pos += 1
        self.expect("OP", "{")
        members: List[Tuple[str, int]] = []
        env: Dict[str, int] = {}
        nxt = 0
        while not self.accept("OP", "}"):
            if self.cur().kind == "NEWLINE":
                self.pos += 1
                continue
            k = self.expect("IDENT").val
            if self.accept("OP", "="):
                val = self._eval_enum_expr(self.parse_expr(), env)
                nxt = val + 1
            else:
                val = nxt
                nxt += 1
            members.append((k, val))
            env[k] = val
            self.accept("OP", ",")
        self.skip_stmt_end()
        return EnumDecl(ename, members)

    def parse_var_decl(self) -> VarDecl:
        while self.cur().kind == "IDENT" and self.cur().val in ("onready", "export"):
            self.pos += 1
            if self.accept("OP", "("):
                depth = 1
                while depth > 0 and self.cur().kind != "EOF":
                    if self.cur().kind == "OP" and self.cur().val == "(":
                        depth += 1
                    elif self.cur().kind == "OP" and self.cur().val == ")":
                        depth -= 1
                    self.pos += 1
        is_const = False
        if self.accept("IDENT", "const"):
            is_const = True
        else:
            self.expect("IDENT", "var")
        vname = self.expect("IDENT").val
        type_ann = None
        init = None
        if self.accept("OP", ":="):
            init = self.parse_expr()
        elif self.accept("OP", ":"):
            if self.cur().kind == "IDENT":
                type_ann = self.cur().val
                self.pos += 1
            if self.accept("OP", "="):
                init = self.parse_expr()
        elif self.accept("OP", "="):
            init = self.parse_expr()
        self.skip_stmt_end()
        return VarDecl(vname, type_ann, init, is_const)

    def parse_func(self) -> FuncDecl:
        is_static = bool(self.accept("IDENT", "static"))
        self.expect("IDENT", "func")
        fname = self.expect("IDENT").val
        self.expect("OP", "(")
        params: List[ParamDecl] = []
        while not self.accept("OP", ")"):
            pname = self.expect("IDENT").val
            tann = None
            default = None
            if self.accept("OP", ":="):
                default = self.parse_expr()
            elif self.accept("OP", ":"):
                if self.cur().kind == "IDENT":
                    tann = self.cur().val
                    self.pos += 1
                if self.accept("OP", "="):
                    default = self.parse_expr()
            elif self.accept("OP", "="):
                default = self.parse_expr()
            params.append(ParamDecl(pname, tann, default))
            if not self.accept("OP", ","):
                self.expect("OP", ")")
                break
        ret_type = None
        if self.accept("OP", "->"):
            ret_type = self.expect("IDENT").val
        self.expect("OP", ":")
        body = self.parse_suite()
        return FuncDecl(fname, is_static, params, ret_type, body)

    def parse_suite(self) -> List[Stmt]:
        if self.accept("NEWLINE"):
            if not self.accept("INDENT"):
                return [PassStmt()]
            stmts: List[Stmt] = []
            while True:
                self.skip_newlines()
                if self.accept("DEDENT") or self.cur().kind == "EOF":
                    break
                stmts.append(self.parse_stmt())
            return stmts
        # Inline suite on same line: `if x: return 1`
        st = self.parse_stmt()
        return [st]

    def parse_stmt(self) -> Stmt:
        t = self.cur()
        if t.kind == "IDENT":
            if t.val == "pass":
                self.pos += 1
                self.skip_stmt_end()
                return PassStmt()
            if t.val == "break":
                self.pos += 1
                self.skip_stmt_end()
                return BreakStmt()
            if t.val == "continue":
                self.pos += 1
                self.skip_stmt_end()
                return ContinueStmt()
            if t.val == "return":
                self.pos += 1
                if self.cur().kind in ("NEWLINE", "DEDENT", "EOF"):
                    self.skip_stmt_end()
                    return ReturnStmt(None)
                e = self.parse_expr()
                self.skip_stmt_end()
                return ReturnStmt(e)
            if t.val in ("var", "const"):
                vd = self.parse_var_decl()
                return VarStmt(vd.name, vd.type_ann, vd.init, vd.is_const)
            if t.val == "if":
                return self.parse_if()
            if t.val == "while":
                self.pos += 1
                cond = self.parse_expr()
                self.expect("OP", ":")
                body = self.parse_suite()
                return WhileStmt(cond, body)
            if t.val == "for":
                self.pos += 1
                v = self.expect("IDENT").val
                self.expect("IDENT", "in")
                seq = self.parse_expr()
                self.expect("OP", ":")
                body = self.parse_suite()
                return ForStmt(v, seq, body)
            if t.val == "match":
                return self.parse_match()

        lhs = self.parse_expr()
        if self.cur().kind == "OP" and self.cur().val in ("=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="):
            op = self.cur().val
            self.pos += 1
            rhs = self.parse_expr()
            self.skip_stmt_end()
            return AssignStmt(lhs, op, rhs)
        self.skip_stmt_end()
        return ExprStmt(lhs)

    def parse_if(self) -> IfStmt:
        self.expect("IDENT", "if")
        cond = self.parse_expr()
        self.expect("OP", ":")
        branches = [(cond, self.parse_suite())]
        else_body: List[Stmt] = []
        while True:
            self.skip_newlines()
            if self.accept("IDENT", "elif"):
                c = self.parse_expr()
                self.expect("OP", ":")
                branches.append((c, self.parse_suite()))
            else:
                break
        if self.accept("IDENT", "else"):
            self.expect("OP", ":")
            else_body = self.parse_suite()
        return IfStmt(branches, else_body)

    def parse_match(self) -> MatchStmt:
        self.expect("IDENT", "match")
        expr = self.parse_expr()
        self.expect("OP", ":")
        self.expect("NEWLINE")
        self.expect("INDENT")
        arms: List[Tuple[List[Expr], List[Stmt]]] = []
        while True:
            self.skip_newlines()
            if self.accept("DEDENT") or self.cur().kind == "EOF":
                break
            pats: List[Expr] = []
            is_default = False
            while True:
                if self.accept("IDENT", "_"):
                    is_default = True
                else:
                    pats.append(self.parse_expr())
                if not self.accept("OP", ","):
                    break
            self.expect("OP", ":")
            body = self.parse_suite()
            arms.append(([] if is_default else pats, body))
        return MatchStmt(expr, arms)

    # Expression precedence
    def parse_expr(self) -> Expr:
        e = self.parse_or()
        if self.accept("IDENT", "if"):
            cond = self.parse_or()
            self.expect("IDENT", "else")
            else_e = self.parse_expr()
            return TernaryExpr(e, cond, else_e)
        return e

    def parse_or(self) -> Expr:
        e = self.parse_and()
        while (self.cur().kind == "IDENT" and self.cur().val == "or") or (self.cur().kind == "OP" and self.cur().val == "||"):
            self.pos += 1
            e = BinExpr("or", e, self.parse_and())
        return e

    def parse_and(self) -> Expr:
        e = self.parse_not()
        while (self.cur().kind == "IDENT" and self.cur().val == "and") or (self.cur().kind == "OP" and self.cur().val == "&&"):
            self.pos += 1
            e = BinExpr("and", e, self.parse_not())
        return e

    def parse_not(self) -> Expr:
        if (self.cur().kind == "IDENT" and self.cur().val == "not") or (self.cur().kind == "OP" and self.cur().val == "!"):
            if self.cur().kind == "IDENT" and self.peek().kind == "IDENT" and self.peek().val == "in":
                pass
            else:
                self.pos += 1
                return UnaryExpr("not", self.parse_not())
        return self.parse_cmp()

    def parse_cmp(self) -> Expr:
        e = self.parse_bitor()
        while True:
            t = self.cur()
            if t.kind == "OP" and t.val in ("==", "!=", "<", "<=", ">", ">="):
                op = t.val
                self.pos += 1
                e = BinExpr(op, e, self.parse_bitor())
            elif t.kind == "IDENT" and t.val == "in":
                self.pos += 1
                e = BinExpr("in", e, self.parse_bitor())
            elif t.kind == "IDENT" and t.val == "not" and self.peek().kind == "IDENT" and self.peek().val == "in":
                self.pos += 2
                e = UnaryExpr("not", BinExpr("in", e, self.parse_bitor()))
            elif t.kind == "IDENT" and t.val == "is":
                self.pos += 1
                tn = self.expect("IDENT").val
                e = IsExpr(e, tn)
            else:
                break
        return e

    def parse_bitor(self) -> Expr:
        e = self.parse_bitxor()
        while self.accept("OP", "|"):
            e = BinExpr("|", e, self.parse_bitxor())
        return e

    def parse_bitxor(self) -> Expr:
        e = self.parse_bitand()
        while self.accept("OP", "^"):
            e = BinExpr("^", e, self.parse_bitand())
        return e

    def parse_bitand(self) -> Expr:
        e = self.parse_shift()
        while self.accept("OP", "&"):
            e = BinExpr("&", e, self.parse_shift())
        return e

    def parse_shift(self) -> Expr:
        e = self.parse_add()
        while self.cur().kind == "OP" and self.cur().val in ("<<", ">>"):
            op = self.cur().val
            self.pos += 1
            e = BinExpr(op, e, self.parse_add())
        return e

    def parse_add(self) -> Expr:
        e = self.parse_mul()
        while self.cur().kind == "OP" and self.cur().val in ("+", "-"):
            op = self.cur().val
            self.pos += 1
            e = BinExpr(op, e, self.parse_mul())
        return e

    def parse_mul(self) -> Expr:
        e = self.parse_unary()
        while self.cur().kind == "OP" and self.cur().val in ("*", "/", "%"):
            op = self.cur().val
            self.pos += 1
            e = BinExpr(op, e, self.parse_unary())
        return e

    def parse_unary(self) -> Expr:
        if self.cur().kind == "OP" and self.cur().val in ("-", "+", "~"):
            op = self.cur().val
            self.pos += 1
            return UnaryExpr(op, self.parse_unary())
        return self.parse_postfix()

    def parse_postfix(self) -> Expr:
        e = self.parse_primary()
        while True:
            if self.accept("OP", "."):
                attr = self.expect("IDENT").val
                e = AttrExpr(e, attr)
            elif self.accept("OP", "("):
                args = self.parse_arglist()
                e = CallExpr(e, args)
            elif self.accept("OP", "["):
                key = self.parse_expr()
                self.expect("OP", "]")
                e = IndexExpr(e, key)
            else:
                break
        return e

    def parse_arglist(self) -> List[Expr]:
        args: List[Expr] = []
        while not self.accept("OP", ")"):
            args.append(self.parse_expr())
            if not self.accept("OP", ","):
                self.expect("OP", ")")
                break
        return args

    def parse_primary(self) -> Expr:
        t = self.cur()
        if t.kind == "INT":
            self.pos += 1
            return LitExpr("int", int(t.val, 0))
        if t.kind == "FLOAT":
            self.pos += 1
            return LitExpr("float", float(t.val))
        if t.kind == "STR":
            self.pos += 1
            return LitExpr("str", t.val)
        if t.kind == "IDENT":
            self.pos += 1
            if t.val == "null":
                return LitExpr("null", None)
            if t.val == "true":
                return LitExpr("bool", True)
            if t.val == "false":
                return LitExpr("bool", False)
            return IdentExpr(t.val)
        if t.kind == "OP" and t.val == ".":
            self.pos += 1
            m = self.expect("IDENT").val
            self.expect("OP", "(")
            args = self.parse_arglist()
            return SuperCallExpr(m, args)
        if t.kind == "OP" and t.val == "(":
            self.pos += 1
            e = self.parse_expr()
            self.expect("OP", ")")
            return e
        if t.kind == "OP" and t.val == "[":
            self.pos += 1
            elems: List[Expr] = []
            while not self.accept("OP", "]"):
                elems.append(self.parse_expr())
                if not self.accept("OP", ","):
                    self.expect("OP", "]")
                    break
            return ArrayExpr(elems)
        if t.kind == "OP" and t.val == "{":
            self.pos += 1
            pairs: List[Tuple[Expr, Expr]] = []
            while not self.accept("OP", "}"):
                k = self.parse_expr()
                self.expect("OP", ":")
                v = self.parse_expr()
                pairs.append((k, v))
                if not self.accept("OP", ","):
                    self.expect("OP", "}")
                    break
            return DictExpr(pairs)
        raise SyntaxError(f"{self.filename}:{t.line}: unexpected token in expr {t}")


# ═══════════════════════════════ Class Registry & Collector ═══════════════════════════════

@dataclasses.dataclass
class ClsInfo:
    rel: str
    res_path: str
    is_behavior_tree: bool
    cpp_name: str
    gd_name: Optional[str]
    stem: str
    decl: ClassDecl
    base: Optional["ClsInfo"] = None
    outer: Optional["ClsInfo"] = None
    own_vars: Dict[str, VarDecl] = dataclasses.field(default_factory=dict)
    own_funcs: Dict[str, FuncDecl] = dataclasses.field(default_factory=dict)
    own_enums: Dict[str, EnumDecl] = dataclasses.field(default_factory=dict)
    own_signals: Set[str] = dataclasses.field(default_factory=set)
    own_inners: Dict[str, "ClsInfo"] = dataclasses.field(default_factory=dict)
    all_var_names: Set[str] = dataclasses.field(default_factory=set)
    all_const_names: Set[str] = dataclasses.field(default_factory=set)
    all_enum_names: Set[str] = dataclasses.field(default_factory=set)
    all_func_names: Set[str] = dataclasses.field(default_factory=set)
    all_static_funcs: Set[str] = dataclasses.field(default_factory=set)
    var_types: Dict[str, Optional[str]] = dataclasses.field(default_factory=dict)


def make_cpp_name(rel: str, inner_path: Tuple[str, ...] = ()) -> str:
    base = re.sub(r"[^0-9A-Za-z_]", "_", rel[:-3].replace("/", "__"))
    if inner_path:
        base += "__INNER__" + "__".join(inner_path)
    return "Gd__" + base


def scan_and_parse() -> Tuple[List[ClsInfo], Dict[str, ClsInfo]]:
    raw_files: List[Tuple[str, ClassDecl]] = []
    for d in SRC_DIRS:
        for p in sorted((ROOT / d).rglob("*.gd")):
            rel = p.relative_to(ROOT).as_posix()
            src = p.read_text(encoding="utf-8", errors="replace")
            toks = lex_gdscript(src, rel)
            decl = Parser(toks, rel).parse_class()
            raw_files.append((rel, decl))

    all_cls: List[ClsInfo] = []
    by_path: Dict[str, ClsInfo] = {}
    by_name_core: Dict[str, ClsInfo] = {}
    by_name_items: Dict[str, ClsInfo] = {}
    by_name_global: Dict[str, ClsInfo] = {}

    for rel, decl in raw_files:
        is_bt = rel.startswith("gd_core_items/")
        stem = pathlib.Path(rel).stem
        ci = ClsInfo(
            rel=rel,
            res_path="res://" + rel,
            is_behavior_tree=is_bt,
            cpp_name=make_cpp_name(rel),
            gd_name=decl.name or stem,
            stem=stem,
            decl=decl,
        )
        all_cls.append(ci)
        by_path[ci.res_path] = ci
        target_dir_map = by_name_items if is_bt else by_name_core
        if decl.name:
            target_dir_map[decl.name] = ci
            by_name_global[decl.name] = ci
        target_dir_map.setdefault(stem, ci)
        by_name_global.setdefault(stem, ci)

        for inner in decl.inner_classes:
            ici = ClsInfo(
                rel=rel,
                res_path="",
                is_behavior_tree=is_bt,
                cpp_name=make_cpp_name(rel, (inner.name or "Inner",)),
                gd_name=inner.name,
                stem=inner.name or "Inner",
                decl=inner,
                outer=ci,
            )
            all_cls.append(ici)
            ci.own_inners[inner.name or ""] = ici

    def resolve_base(ci: ClsInfo) -> Optional[ClsInfo]:
        ext = ci.decl.extends
        if not ext:
            return None
        if ext.startswith('"'):
            return by_path.get(ext.strip('"'))
        if ext in BUILTIN_TYPE_MAP:
            return None
        if ci.outer and ext in ci.outer.own_inners:
            return ci.outer.own_inners[ext]
        # Prefer same tree (items vs core) when resolving bare class names
        m = by_name_items if ci.is_behavior_tree else by_name_core
        return m.get(ext) or by_name_global.get(ext)

    for ci in all_cls:
        ci.base = resolve_base(ci)

    # Topological sort (base classes and outer classes first)
    order: List[ClsInfo] = []
    vis: Dict[str, int] = {}

    def visit(ci: ClsInfo):
        st = vis.get(ci.cpp_name, 0)
        if st == 2:
            return
        if st == 1:
            raise RuntimeError(f"Cycle in inheritance at {ci.cpp_name}")
        vis[ci.cpp_name] = 1
        if ci.base:
            visit(ci.base)
        vis[ci.cpp_name] = 2
        order.append(ci)

    for ci in all_cls:
        visit(ci)

    # Populate scopes in topological order
    for ci in order:
        if ci.base:
            ci.all_var_names |= ci.base.all_var_names
            ci.all_const_names |= ci.base.all_const_names
            ci.all_enum_names |= ci.base.all_enum_names
            ci.all_func_names |= ci.base.all_func_names
            ci.all_static_funcs |= ci.base.all_static_funcs
            ci.var_types.update(ci.base.var_types)
        if ci.outer:
            ci.all_const_names |= ci.outer.all_const_names
            ci.all_enum_names |= ci.outer.all_enum_names
        for v in ci.decl.vars:
            ci.own_vars[v.name] = v
            if v.is_const:
                ci.all_const_names.add(v.name)
            else:
                ci.all_var_names.add(v.name)
                ci.var_types[v.name] = v.type_ann
        for e in ci.decl.enums:
            if e.name:
                ci.own_enums[e.name] = e
                ci.all_enum_names.add(e.name)
        for s in ci.decl.signals:
            ci.own_signals.add(s)
        for f in ci.decl.funcs:
            ci.own_funcs[f.name] = f
            ci.all_func_names.add(f.name)
            if f.is_static:
                ci.all_static_funcs.add(f.name)
            else:
                ci.all_static_funcs.discard(f.name)

    return order, by_name_global


# ═══════════════════════════════ C++20 Code Emitter ═══════════════════════════════

def c_escape(s: str) -> str:
    out = ['"']
    for ch in s:
        if ch == "\\":
            out.append("\\\\")
        elif ch == '"':
            out.append('\\"')
        elif ch == "\n":
            out.append("\\n")
        elif ch == "\t":
            out.append("\\t")
        elif ch == "\r":
            out.append("\\r")
        else:
            o = ord(ch)
            if o < 32 or o > 126:
                for b in ch.encode("utf-8"):
                    out.append(f"\\x{b:02x}")
            else:
                out.append(ch)
    out.append('"')
    return "".join(out)


class SymCollector:
    def __init__(self, builtin_syms: Dict[str, str]):
        self.builtin = builtin_syms
        self.syms: Dict[str, str] = {}

    def sym(self, name: str) -> str:
        if name in self.builtin:
            return "gd::" + self.builtin[name]
        if name not in self.syms:
            cid = "SYM_GEN_" + re.sub(r"[^0-9A-Za-z_]", "_", name) + f"_{len(self.syms)}"
            self.syms[name] = cid
        return self.syms[name]


class CppEmitter:
    def __init__(self, order: List[ClsInfo], by_name_global: Dict[str, ClsInfo], symc: SymCollector):
        self.order = order
        self.by_name = by_name_global
        self.symc = symc
        self.cls_by_cpp = {c.cpp_name: c for c in order}
        self._tmp_id = 0

    def next_tmp(self) -> str:
        self._tmp_id += 1
        return f"_t{self._tmp_id}"

    def coerce_wrap(self, expr_cpp: str, type_ann: Optional[str]) -> str:
        if type_ann == "int":
            return f"gd::gd_coerce_int({expr_cpp})"
        if type_ann == "float":
            return f"gd::gd_coerce_float({expr_cpp})"
        if type_ann == "bool":
            return f"gd::gd_coerce_bool({expr_cpp})"
        return expr_cpp

    def is_lvalue_expr(self, e: Expr, ci: ClsInfo, locals_: Dict[str, Optional[str]], in_static: bool) -> bool:
        if isinstance(e, IdentExpr):
            if e.name in locals_:
                return True
            if not in_static and e.name in ci.all_var_names:
                return True
        return False

    def emit_expr(self, e: Expr, ci: ClsInfo, locals_: Dict[str, Optional[str]], in_static: bool, stmts_pre: Optional[List[str]] = None) -> str:
        if isinstance(e, LitExpr):
            if e.kind == "null":
                return "gd::GdVal::null()"
            if e.kind == "bool":
                return f"gd::GdVal::from_bool({'true' if e.val else 'false'})"
            if e.kind == "int":
                return f"gd::GdVal::from_int({int(e.val)}LL)"
            if e.kind == "float":
                if e.val == float("inf"):
                    return "gd::GdVal::from_float(std::numeric_limits<double>::infinity())"
                return f"gd::GdVal::from_float({repr(float(e.val))})"
            if e.kind == "str":
                return f"gd::GdVal::from_str(gd::make_str(gd_ctx.arena, {c_escape(e.val)}, {len(e.val.encode('utf-8'))}u))"

        if isinstance(e, IdentExpr):
            nm = e.name
            if nm in locals_:
                return f"lv_{nm}"
            if not in_static and nm in ci.all_var_names:
                return f"this->f_{nm}"
            if nm in ci.own_enums or nm in ci.all_enum_names:
                if nm in ci.own_enums or (ci.base and nm in ci.base.all_enum_names):
                    return f"{ci.cpp_name}::get_static_const_or_enum(gd_ctx, {self.symc.sym(nm)})"
                if ci.outer and nm in ci.outer.all_enum_names:
                    return f"{ci.outer.cpp_name}::get_static_const_or_enum(gd_ctx, {self.symc.sym(nm)})"
            if nm in ci.all_const_names:
                if ci.outer and nm in ci.outer.all_const_names and nm not in ci.own_vars and not (ci.base and nm in ci.base.all_const_names):
                    return f"{ci.outer.cpp_name}::get_static_const_or_enum(gd_ctx, {self.symc.sym(nm)})"
                return f"{ci.cpp_name}::get_static_const_or_enum(gd_ctx, {self.symc.sym(nm)})"
            if nm in ci.own_inners:
                return f"gd::GdVal::from_cls(&META_{ci.own_inners[nm].cpp_name})"
            if ci.outer and nm == ci.outer.gd_name:
                return f"gd::GdVal::from_cls(&META_{ci.outer.cpp_name})"
            if nm == "self" and not in_static:
                return "gd::GdVal::from_obj(this)"
            if nm == "PI":
                return "gd::GdVal::from_float(3.14159265358979323846)"
            if nm == "TAU":
                return "gd::GdVal::from_float(6.28318530717958647692)"
            if nm == "INF":
                return "gd::GdVal::from_float(std::numeric_limits<double>::infinity())"
            if nm == "NAN":
                return "gd::GdVal::from_float(std::numeric_limits<double>::quiet_NaN())"
            if nm == "TYPE_VECTOR2":
                return "gd::GdVal::from_int(5)"
            if nm in self.by_name and nm not in BUILTIN_TYPE_MAP:
                return f"gd::GdVal::from_cls(&META_{self.by_name[nm].cpp_name})"
            # Fallback to property on self
            if not in_static:
                return f"gd::get_prop(gd_ctx, gd::GdVal::from_obj(this), {self.symc.sym(nm)})"
            return "gd::GdVal::null()"

        if isinstance(e, ArrayExpr):
            elems = [self.emit_expr(el, ci, locals_, in_static) for el in e.elems]
            return f"gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {{{', '.join(elems)}}}))"

        if isinstance(e, DictExpr):
            if not e.pairs:
                return "gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))"
            parts = []
            for k, v in e.pairs:
                parts.append(f"d->set(gd_ctx.arena, {self.emit_expr(k, ci, locals_, in_static)}, {self.emit_expr(v, ci, locals_, in_static)});")
            return f"([&]() {{ auto* d = gd::GdDict::create(gd_ctx.arena, {len(e.pairs)}); {' '.join(parts)} return gd::GdVal::from_dict(d); }})()"

        if isinstance(e, UnaryExpr):
            sub = self.emit_expr(e.expr, ci, locals_, in_static)
            if e.op == "-":
                return f"gd::gd_neg({sub})"
            if e.op == "+":
                return f"gd::gd_pos({sub})"
            if e.op == "~":
                return f"gd::gd_bitnot({sub})"
            if e.op == "not":
                return f"gd::GdVal::from_bool(!gd::gd_truth({sub}))"

        if isinstance(e, BinExpr):
            if e.op == "and":
                return f"(gd::gd_truth({self.emit_expr(e.left, ci, locals_, in_static)}) ? gd::GdVal::from_bool(gd::gd_truth({self.emit_expr(e.right, ci, locals_, in_static)})) : gd::GdVal::from_bool(false))"
            if e.op == "or":
                return f"(gd::gd_truth({self.emit_expr(e.left, ci, locals_, in_static)}) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth({self.emit_expr(e.right, ci, locals_, in_static)})))"
            l = self.emit_expr(e.left, ci, locals_, in_static)
            r = self.emit_expr(e.right, ci, locals_, in_static)
            op_map = {
                "+": f"gd::gd_add(gd_ctx, {l}, {r})",
                "-": f"gd::gd_sub({l}, {r})",
                "*": f"gd::gd_mul({l}, {r})",
                "/": f"gd::gd_div(gd_ctx, {l}, {r})",
                "%": f"gd::gd_mod(gd_ctx, {l}, {r})",
                "&": f"gd::gd_bitand({l}, {r})",
                "|": f"gd::gd_bitor({l}, {r})",
                "^": f"gd::gd_bitxor({l}, {r})",
                "<<": f"gd::gd_shl({l}, {r})",
                ">>": f"gd::gd_shr({l}, {r})",
                "==": f"gd::GdVal::from_bool(gd::gd_eq({l}, {r}))",
                "!=": f"gd::GdVal::from_bool(gd::gd_ne({l}, {r}))",
                "<": f"gd::GdVal::from_bool(gd::gd_lt({l}, {r}))",
                "<=": f"gd::GdVal::from_bool(gd::gd_le({l}, {r}))",
                ">": f"gd::GdVal::from_bool(gd::gd_gt({l}, {r}))",
                ">=": f"gd::GdVal::from_bool(gd::gd_ge({l}, {r}))",
                "in": f"gd::gd_in({l}, {r})",
            }
            return op_map[e.op]

        if isinstance(e, TernaryExpr):
            c = self.emit_expr(e.cond_e, ci, locals_, in_static)
            t_e = self.emit_expr(e.then_e, ci, locals_, in_static)
            el_e = self.emit_expr(e.else_e, ci, locals_, in_static)
            return f"(gd::gd_truth({c}) ? ({t_e}) : ({el_e}))"

        if isinstance(e, IsExpr):
            sub = self.emit_expr(e.expr, ci, locals_, in_static)
            tn = e.type_name
            builtin_tags = {
                "bool": 1, "int": 2, "float": 3, "String": 4, "Vector2": 5,
                "Color": 14, "Dictionary": 18, "Array": 19,
                "Reference": 17, "Object": 17, "Node": 17, "Node2D": 17, "Resource": 17,
                "FuncRef": 17, "RandomNumberGenerator": 17,
            }
            if tn in builtin_tags:
                return f"gd::GdVal::from_bool(gd::gd_is_builtin({sub}, {builtin_tags[tn]}))"
            if tn in ci.own_inners:
                return f"gd::GdVal::from_bool(gd::gd_is_type({sub}, &META_{ci.own_inners[tn].cpp_name}))"
            if tn in self.by_name:
                return f"gd::GdVal::from_bool(gd::gd_is_type({sub}, &META_{self.by_name[tn].cpp_name}))"
            return "gd::GdVal::from_bool(false)"

        if isinstance(e, IndexExpr):
            r = self.emit_expr(e.recv, ci, locals_, in_static)
            k = self.emit_expr(e.key, ci, locals_, in_static)
            return f"gd::get_index(gd_ctx, {r}, {k})"

        if isinstance(e, AttrExpr):
            # Handle Vector2.ZERO etc. and Color.white
            if isinstance(e.recv, IdentExpr):
                rn = e.recv.name
                if rn == "Vector2":
                    vmap = {
                        "ZERO": "(0.0, 0.0)", "ONE": "(1.0, 1.0)",
                        "RIGHT": "(1.0, 0.0)", "LEFT": "(-1.0, 0.0)",
                        "UP": "(0.0, -1.0)", "DOWN": "(0.0, 1.0)",
                        "INF": "(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity())",
                    }
                    if e.attr in vmap:
                        return f"gd::GdVal::from_vec2{vmap[e.attr]}"
                if rn == "Color":
                    return f"gd::get_named_color({c_escape(e.attr)})"
                if rn == "Engine" and e.attr == "time_scale":
                    return "gd::GdVal::from_float(1.0)"
            r = self.emit_expr(e.recv, ci, locals_, in_static)
            return f"gd::get_prop(gd_ctx, {r}, {self.symc.sym(e.attr)})"

        if isinstance(e, SuperCallExpr):
            args_cpp = [self.emit_expr(a, ci, locals_, in_static) for a in e.args]
            sym = self.symc.sym(e.method)
            if ci.base:
                arr_lit = f"gd::GdVal _ca[] = {{{', '.join(args_cpp)}}};" if args_cpp else ""
                aptr = "_ca" if args_cpp else "nullptr"
                return (
                    f"([&]() {{ {arr_lit} gd::GdVal _out = gd::GdVal::null(); "
                    f"this->{ci.base.cpp_name}::call_method(gd_ctx, {sym}, {aptr}, {len(args_cpp)}, _out); return _out; }})()"
                )
            return "gd::GdVal::null()"

        if isinstance(e, CallExpr):
            return self.emit_call(e, ci, locals_, in_static)

        raise RuntimeError(f"Unhandled expr: {e}")

    def emit_call(self, e: CallExpr, ci: ClsInfo, locals_: Dict[str, Optional[str]], in_static: bool) -> str:
        args_cpp = [self.emit_expr(a, ci, locals_, in_static) for a in e.args]
        nargs = len(args_cpp)
        if isinstance(e.callee, AttrExpr):
            recv = e.callee.recv
            m = e.callee.attr
            # Builtin OS / RandomNumberGenerator / FuncRef
            if isinstance(recv, IdentExpr):
                rn = recv.name
                if rn == "OS" and m == "has_feature":
                    return "gd::GdVal::from_bool(false)"
                if rn == "OS" and m == "get_environment":
                    return "gd::GdVal::from_cstr(gd_ctx.arena, \"\")"
                if rn == "RandomNumberGenerator" and m == "new":
                    return "gd::GdVal::from_rng(gd_ctx.arena.make<gd::GdRng>())"
                if rn == "FuncRef" and m == "new":
                    return "gd::GdVal::from_funcref(gd_ctx.arena.make<gd::GdFuncRef>())"
            recv_cpp = self.emit_expr(recv, ci, locals_, in_static)
            sym = self.symc.sym(m)
            if nargs == 0:
                return f"gd::call_method(gd_ctx, {recv_cpp}, {sym}, nullptr, 0)"
            return f"([&]() {{ gd::GdVal _ca[] = {{{', '.join(args_cpp)}}}; return gd::call_method(gd_ctx, {recv_cpp}, {sym}, _ca, {nargs}); }})()"

        if isinstance(e.callee, IdentExpr):
            fn = e.callee.name
            # Builtin constructors & global math functions
            if fn == "Vector2":
                x = args_cpp[0] if nargs >= 1 else "gd::GdVal::from_float(0.0)"
                y = args_cpp[1] if nargs >= 2 else "gd::GdVal::from_float(0.0)"
                return f"gd::GdVal::from_vec2(({x}).as_float(), ({y}).as_float())"
            if fn == "Color":
                if nargs == 0:
                    return "gd::make_color_from_args(nullptr, 0)"
                return f"([&]() {{ gd::GdVal _ca[] = {{{', '.join(args_cpp)}}}; return gd::make_color_from_args(_ca, {nargs}); }})()"
            if fn == "Dictionary":
                return "gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))"
            if fn in ("Array", "PoolStringArray", "PoolIntArray", "PoolVector2Array", "PoolColorArray"):
                if nargs == 1:
                    return f"({args_cpp[0]})"
                return "gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena))"
            if fn == "PoolRealArray":
                if nargs == 1:
                    return f"([&]() {{ gd::GdVal _s = ({args_cpp[0]}); return gd::GdVal::from_arr(gd::GdArr::create_pool_real(gd_ctx.arena, &_s)); }})()"
                return "gd::GdVal::from_arr(gd::GdArr::create_pool_real(gd_ctx.arena))"
            if fn == "assert":
                return "gd::GdVal::null()"
            if fn == "int":
                return f"gd::gd_coerce_int({args_cpp[0] if nargs else 'gd::GdVal::from_int(0)'})"
            if fn == "float":
                return f"gd::gd_coerce_float({args_cpp[0] if nargs else 'gd::GdVal::from_float(0.0)'})"
            if fn == "bool":
                return f"gd::gd_coerce_bool({args_cpp[0] if nargs else 'gd::GdVal::from_bool(false)'})"
            if fn == "String":
                return f"gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, {args_cpp[0] if nargs else 'gd::GdVal::from_cstr(gd_ctx.arena, \"\")'}))"
            if fn == "str":
                if nargs == 0:
                    return "gd::GdVal::from_cstr(gd_ctx.arena, \"\")"
                return f"([&]() {{ gd::GdVal _ca[] = {{{', '.join(args_cpp)}}}; return gd::gd_str_fn(gd_ctx.arena, _ca, {nargs}); }})()"
            if fn == "range":
                return f"([&]() {{ gd::GdVal _ca[] = {{{', '.join(args_cpp)}}}; return gd::gd_range(gd_ctx.arena, _ca, {nargs}); }})()"
            if fn == "abs":
                return f"gd::gd_abs({args_cpp[0]})"
            if fn == "min":
                return f"gd::gd_min({args_cpp[0]}, {args_cpp[1]})"
            if fn == "max":
                return f"gd::gd_max({args_cpp[0]}, {args_cpp[1]})"
            if fn == "clamp":
                return f"gd::gd_clamp({args_cpp[0]}, {args_cpp[1]}, {args_cpp[2]})"
            if fn == "floor":
                return f"gd::gd_floor({args_cpp[0]})"
            if fn == "ceil":
                return f"gd::gd_ceil({args_cpp[0]})"
            if fn == "round":
                return f"gd::gd_round({args_cpp[0]})"
            if fn == "stepify":
                return f"gd::gd_stepify({args_cpp[0]}, {args_cpp[1]})"
            if fn == "snapped":
                return f"gd::gd_snapped({args_cpp[0]}, {args_cpp[1]})"
            if fn == "fmod":
                return f"gd::gd_fmod({args_cpp[0]}, {args_cpp[1]})"
            if fn == "posmod":
                return f"gd::gd_posmod({args_cpp[0]}, {args_cpp[1]})"
            if fn == "sqrt":
                return f"gd::gd_sqrt({args_cpp[0]})"
            if fn == "pow":
                return f"gd::gd_pow({args_cpp[0]}, {args_cpp[1]})"
            if fn == "sign":
                return f"gd::gd_sign({args_cpp[0]})"
            if fn == "lerp":
                return f"gd::gd_lerp({args_cpp[0]}, {args_cpp[1]}, {args_cpp[2]})"
            if fn == "inverse_lerp":
                return f"gd::gd_inverse_lerp({args_cpp[0]}, {args_cpp[1]}, {args_cpp[2]})"
            if fn == "smoothstep":
                return f"gd::gd_smoothstep({args_cpp[0]}, {args_cpp[1]}, {args_cpp[2]})"
            if fn == "move_toward":
                return f"gd::gd_move_toward({args_cpp[0]}, {args_cpp[1]}, {args_cpp[2]})"
            if fn == "wrapf":
                return f"gd::gd_wrapf({args_cpp[0]}, {args_cpp[1]}, {args_cpp[2]})"
            if fn == "wrapi":
                return f"gd::gd_wrapi({args_cpp[0]}, {args_cpp[1]}, {args_cpp[2]})"
            if fn == "deg2rad":
                return f"gd::gd_deg2rad({args_cpp[0]})"
            if fn == "rad2deg":
                return f"gd::gd_rad2deg({args_cpp[0]})"
            if fn == "is_equal_approx":
                return f"gd::GdVal::from_bool(gd::gd_is_equal_approx({args_cpp[0]}, {args_cpp[1]}))"
            if fn == "is_instance_valid":
                return f"gd::GdVal::from_bool(!({args_cpp[0]}).is_null())"
            if fn == "typeof":
                return f"gd::GdVal::from_int(gd::gd_typeof({args_cpp[0]}))"
            if fn == "tr":
                return args_cpp[0]
            if fn == "print":
                return "gd::GdVal::null()"
            if fn == "push_error" or fn == "push_warning":
                return "gd::GdVal::null()"
            if fn == "randomize":
                return "gd::GdVal::null()"
            if fn == "get_stack":
                return "gd::GdVal::null()"
            if fn == "load":
                return f"gd::load_resource((({args_cpp[0]}).kind == gd::GdVal::Kind::Str && ({args_cpp[0]}).str) ? std::string_view(({args_cpp[0]}).str->data, ({args_cpp[0]}).str->len) : std::string_view(\"\"))"
            if fn == "funcref":
                return (
                    f"([&]() {{ auto* fr = gd_ctx.arena.make<gd::GdFuncRef>(); "
                    f"gd::GdVal inst = {args_cpp[0]}; gd::GdVal mname = {args_cpp[1]}; "
                    f"fr->instance = (inst.kind == gd::GdVal::Kind::Obj) ? inst.obj : nullptr; "
                    f"fr->method = (mname.kind == gd::GdVal::Kind::Str && mname.str) ? gd::intern_sym(std::string_view(mname.str->data, mname.str->len)) : gd::SYM_NONE; "
                    f"return gd::GdVal::from_funcref(fr); }})()"
                )

            # Free method call in class / ancestor / self
            sym = self.symc.sym(fn)
            if in_static:
                if nargs == 0:
                    return f"([&]() {{ gd::GdVal _out = gd::GdVal::null(); {ci.cpp_name}::call_static_fn(gd_ctx, {sym}, nullptr, 0, _out); return _out; }})()"
                return f"([&]() {{ gd::GdVal _ca[] = {{{', '.join(args_cpp)}}}; gd::GdVal _out = gd::GdVal::null(); {ci.cpp_name}::call_static_fn(gd_ctx, {sym}, _ca, {nargs}, _out); return _out; }})()"
            # Instance context: check if fn is exclusively static in class hierarchy and not in own/inherited non-static
            if fn in ci.all_static_funcs:
                if nargs == 0:
                    return f"([&]() {{ gd::GdVal _out = gd::GdVal::null(); {ci.cpp_name}::call_static_fn(gd_ctx, {sym}, nullptr, 0, _out); return _out; }})()"
                return f"([&]() {{ gd::GdVal _ca[] = {{{', '.join(args_cpp)}}}; gd::GdVal _out = gd::GdVal::null(); {ci.cpp_name}::call_static_fn(gd_ctx, {sym}, _ca, {nargs}, _out); return _out; }})()"
            if nargs == 0:
                return f"gd::call_method(gd_ctx, gd::GdVal::from_obj(this), {sym}, nullptr, 0)"
            return f"([&]() {{ gd::GdVal _ca[] = {{{', '.join(args_cpp)}}}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), {sym}, _ca, {nargs}); }})()"

        raise RuntimeError(f"Unsupported direct call target: {e}")

    def emit_assign(self, target: Expr, op: str, val_e: Expr, ci: ClsInfo, locals_: Dict[str, Optional[str]], in_static: bool, lines: List[str], ind: str):
        rhs_cpp = self.emit_expr(val_e, ci, locals_, in_static)
        bin_op = None if op == "=" else op[:-1]

        def combine(lhs_cpp: str, r_cpp: str) -> str:
            if not bin_op:
                return r_cpp
            return {
                "+": f"gd::gd_add(gd_ctx, {lhs_cpp}, {r_cpp})",
                "-": f"gd::gd_sub({lhs_cpp}, {r_cpp})",
                "*": f"gd::gd_mul({lhs_cpp}, {r_cpp})",
                "/": f"gd::gd_div(gd_ctx, {lhs_cpp}, {r_cpp})",
                "%": f"gd::gd_mod(gd_ctx, {lhs_cpp}, {r_cpp})",
                "&": f"gd::gd_bitand({lhs_cpp}, {r_cpp})",
                "|": f"gd::gd_bitor({lhs_cpp}, {r_cpp})",
                "^": f"gd::gd_bitxor({lhs_cpp}, {r_cpp})",
                "<<": f"gd::gd_shl({lhs_cpp}, {r_cpp})",
                ">>": f"gd::gd_shr({lhs_cpp}, {r_cpp})",
            }[bin_op]

        if isinstance(target, IdentExpr):
            nm = target.name
            if nm in locals_:
                tann = locals_[nm]
                newv = combine(f"lv_{nm}", rhs_cpp)
                lines.append(f"{ind}lv_{nm} = {self.coerce_wrap(newv, tann)};")
                return
            if not in_static and nm in ci.all_var_names:
                tann = ci.var_types.get(nm)
                newv = combine(f"this->f_{nm}", rhs_cpp)
                lines.append(f"{ind}this->f_{nm} = {self.coerce_wrap(newv, tann)};")
                return
            if not in_static:
                sym = self.symc.sym(nm)
                newv = rhs_cpp if not bin_op else combine(f"gd::get_prop(gd_ctx, gd::GdVal::from_obj(this), {sym})", rhs_cpp)
                lines.append(f"{ind}{{ gd::GdVal _selfv = gd::GdVal::from_obj(this); gd::set_prop(gd_ctx, _selfv, {sym}, {newv}); }}")
                return
            raise RuntimeError(f"Unknown assignment target {nm} in static func of {ci.rel}")

        if isinstance(target, AttrExpr):
            sym = self.symc.sym(target.attr)
            if self.is_lvalue_expr(target.recv, ci, locals_, in_static):
                lv = self.emit_expr(target.recv, ci, locals_, in_static)
                newv = rhs_cpp if not bin_op else combine(f"gd::get_prop(gd_ctx, {lv}, {sym})", rhs_cpp)
                lines.append(f"{ind}gd::set_prop(gd_ctx, {lv}, {sym}, {newv});")
            else:
                tmp = self.next_tmp()
                rcv = self.emit_expr(target.recv, ci, locals_, in_static)
                newv = rhs_cpp if not bin_op else combine(f"gd::get_prop(gd_ctx, {tmp}, {sym})", rhs_cpp)
                lines.append(f"{ind}{{ gd::GdVal {tmp} = {rcv}; gd::set_prop(gd_ctx, {tmp}, {sym}, {newv}); }}")
            return

        if isinstance(target, IndexExpr):
            tmp_r = self.next_tmp()
            tmp_k = self.next_tmp()
            rcv = self.emit_expr(target.recv, ci, locals_, in_static)
            key = self.emit_expr(target.key, ci, locals_, in_static)
            newv = rhs_cpp if not bin_op else combine(f"gd::get_index(gd_ctx, {tmp_r}, {tmp_k})", rhs_cpp)
            lines.append(f"{ind}{{ gd::GdVal {tmp_r} = {rcv}; gd::GdVal {tmp_k} = {key}; gd::set_index(gd_ctx, {tmp_r}, {tmp_k}, {newv}); }}")
            return

        raise RuntimeError(f"Unsupported assign target: {target}")

    def emit_stmts(self, stmts: List[Stmt], ci: ClsInfo, locals_: Dict[str, Optional[str]], in_static: bool, lines: List[str], ind: str):
        for st in stmts:
            if isinstance(st, PassStmt):
                continue
            elif isinstance(st, BreakStmt):
                lines.append(f"{ind}break;")
            elif isinstance(st, ContinueStmt):
                lines.append(f"{ind}continue;")
            elif isinstance(st, ReturnStmt):
                if st.expr is None:
                    lines.append(f"{ind}return gd::GdVal::null();")
                else:
                    lines.append(f"{ind}return {self.emit_expr(st.expr, ci, locals_, in_static)};")
            elif isinstance(st, VarStmt):
                if st.init is not None:
                    val_cpp = self.coerce_wrap(self.emit_expr(st.init, ci, locals_, in_static), st.type_ann)
                else:
                    val_cpp = GD_TYPE_DEFAULTS.get(st.type_ann or "", "gd::GdVal::null()")
                if st.name in locals_:
                    lines.append(f"{ind}lv_{st.name} = {val_cpp};")
                else:
                    locals_[st.name] = st.type_ann
                    lines.append(f"{ind}gd::GdVal lv_{st.name} = {val_cpp};")
            elif isinstance(st, AssignStmt):
                self.emit_assign(st.target, st.op, st.val, ci, locals_, in_static, lines, ind)
            elif isinstance(st, ExprStmt):
                lines.append(f"{ind}(void){self.emit_expr(st.expr, ci, locals_, in_static)};")
            elif isinstance(st, IfStmt):
                for idx, (cond, body) in enumerate(st.branches):
                    kw = "if" if idx == 0 else "else if"
                    lines.append(f"{ind}{kw} (gd::gd_truth({self.emit_expr(cond, ci, locals_, in_static)})) {{")
                    sub_loc = dict(locals_)
                    self.emit_stmts(body, ci, sub_loc, in_static, lines, ind + "    ")
                    lines.append(f"{ind}}}")
                if st.else_body:
                    lines.append(f"{ind}else {{")
                    sub_loc = dict(locals_)
                    self.emit_stmts(st.else_body, ci, sub_loc, in_static, lines, ind + "    ")
                    lines.append(f"{ind}}}")
            elif isinstance(st, WhileStmt):
                lines.append(f"{ind}while (gd::gd_truth({self.emit_expr(st.cond, ci, locals_, in_static)})) {{")
                sub_loc = dict(locals_)
                self.emit_stmts(st.body, ci, sub_loc, in_static, lines, ind + "    ")
                lines.append(f"{ind}}}")
            elif isinstance(st, ForStmt):
                seq_t = self.next_tmp()
                arr_t = self.next_tmp()
                idx_t = self.next_tmp()
                seq_cpp = self.emit_expr(st.seq, ci, locals_, in_static)
                lines.append(f"{ind}{{")
                lines.append(f"{ind}    gd::GdVal {seq_t} = gd::gd_iter_seq(gd_ctx.arena, {seq_cpp});")
                lines.append(f"{ind}    gd::GdArr* {arr_t} = ({seq_t}.kind == gd::GdVal::Kind::Arr) ? {seq_t}.arr : nullptr;")
                lines.append(f"{ind}    uint32_t _len_{idx_t} = {arr_t} ? {arr_t}->len : 0u;")
                lines.append(f"{ind}    for (uint32_t {idx_t} = 0; {idx_t} < _len_{idx_t}; ++{idx_t}) {{")
                sub_loc = dict(locals_)
                sub_loc[st.var] = None
                if st.var in locals_:
                    lines.append(f"{ind}        lv_{st.var} = {arr_t}->data[{idx_t}];")
                else:
                    lines.append(f"{ind}        gd::GdVal lv_{st.var} = {arr_t}->data[{idx_t}];")
                self.emit_stmts(st.body, ci, sub_loc, in_static, lines, ind + "        ")
                lines.append(f"{ind}    }}")
                lines.append(f"{ind}}}")
            elif isinstance(st, MatchStmt):
                mv = self.next_tmp()
                lines.append(f"{ind}{{")
                lines.append(f"{ind}    gd::GdVal {mv} = {self.emit_expr(st.expr, ci, locals_, in_static)};")
                first = True
                for pats, body in st.arms:
                    if not pats:
                        lines.append(f"{ind}    {'if (true)' if first else 'else'} {{")
                    else:
                        conds = " || ".join(f"gd::gd_eq({mv}, {self.emit_expr(p, ci, locals_, in_static)})" for p in pats)
                        kw = "if" if first else "else if"
                        lines.append(f"{ind}    {kw} ({conds}) {{")
                    first = False
                    sub_loc = dict(locals_)
                    self.emit_stmts(body, ci, sub_loc, in_static, lines, ind + "        ")
                    lines.append(f"{ind}    }}")
                lines.append(f"{ind}}}")


def generate_cpp(order: List[ClsInfo], by_name: Dict[str, ClsInfo]):
    builtin_syms = load_builtin_syms()
    symc = SymCollector(builtin_syms)
    emitter = CppEmitter(order, by_name, symc)

    # First pass: generate class headers & shard method bodies while collecting all SymIds
    hdr_dir = GEN_DIR / "hdrs"
    shard_dir = GEN_DIR / "shards"
    hdr_dir.mkdir(parents=True, exist_ok=True)
    shard_dir.mkdir(parents=True, exist_ok=True)

    # Pre-register all member/func/enum/const/signal symbols
    for ci in order:
        for v in ci.decl.vars:
            symc.sym(v.name)
        for f in ci.decl.funcs:
            symc.sym(f.name)
        for e in ci.decl.enums:
            if e.name:
                symc.sym(e.name)
        for s in ci.decl.signals:
            symc.sym(s)
        for iname in ci.own_inners:
            symc.sym(iname)

    # Generate shard CPP contents and class HPP contents
    num_shards = 16
    shard_classes: List[List[ClsInfo]] = [[] for _ in range(num_shards)]
    for idx, ci in enumerate(order):
        shard_classes[idx % num_shards].append(ci)

    # Generate HPP for each class
    for ci in order:
        base_cpp = ci.base.cpp_name if ci.base else "gd::GdObj"
        base_inc = f'#include "{ci.base.cpp_name}.hpp"' if ci.base else '#include "../../gd_rt.hpp"'
        lines = [
            "#pragma once",
            "#pragma STDC FP_CONTRACT OFF",
            base_inc,
            '#include "../class_metas.hpp"',
            '#include "../sym_ids.hpp"',
            "",
            f"struct {ci.cpp_name} : public {base_cpp} {{",
            f"    explicit {ci.cpp_name}(gd::BattleCtx* ctx) : {base_cpp}(ctx) {{}}",
        ]
        for v in ci.decl.vars:
            if not v.is_const:
                lines.append(f"    gd::GdVal f_{v.name};")
        for f in ci.decl.funcs:
            args_sig = ["gd::BattleCtx& gd_ctx", "const gd::GdVal* _args", "int _argc"] if f.is_static else ["const gd::GdVal* _args", "int _argc"]
            if f.is_static:
                lines.append(f"    static gd::GdVal sf_{f.name}({', '.join(args_sig)});")
            else:
                lines.append(f"    gd::GdVal fn_{f.name}({', '.join(args_sig)});")
        lines.extend([
            "    const gd::GdClassMeta* meta() const override;",
            "    void init_fields(gd::BattleCtx& gd_ctx) override;",
            "    bool get_prop(gd::SymId prop, gd::GdVal& out) const override;",
            "    bool set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) override;",
            "    bool has_own_method(gd::SymId m) const override;",
            "    bool call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) override;",
            "    static gd::GdVal get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop);",
            "    static bool get_static_prop_fn(gd::SymId prop, gd::GdVal& out);",
            "    static bool call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out);",
            "};",
            "",
        ])
        (hdr_dir / f"{ci.cpp_name}.hpp").write_text("\n".join(lines), encoding="utf-8")

    # Generate shard CPP files
    for s_idx, group in enumerate(shard_classes):
        slines = ['#pragma STDC FP_CONTRACT OFF', ""]
        for ci in group:
            slines.append(f'#include "../hdrs/{ci.cpp_name}.hpp"')
            if ci.outer:
                slines.append(f'#include "../hdrs/{ci.outer.cpp_name}.hpp"')
        slines.append("")
        for ci in group:
            base_cpp = ci.base.cpp_name if ci.base else "gd::GdObj"
            # Static enum tables
            for e in ci.decl.enums:
                if e.name:
                    kvs = ", ".join(f"{{{c_escape(k)}, {v}LL}}" for k, v in e.members)
                    slines.append(f"static const gd::GdEnum::KV _ekv_{ci.cpp_name}_{e.name}[] = {{{kvs}}};")
                    slines.append(f"static const gd::GdEnum _enum_{ci.cpp_name}_{e.name} = {{{c_escape(e.name)}, _ekv_{ci.cpp_name}_{e.name}, {len(e.members)}u}};")
            # init_fields
            slines.append(f"void {ci.cpp_name}::init_fields(gd::BattleCtx& gd_ctx) {{")
            if ci.base:
                slines.append(f"    {base_cpp}::init_fields(gd_ctx);")
            for v in ci.decl.vars:
                if v.is_const:
                    continue
                if v.init is not None:
                    vcpp = emitter.coerce_wrap(emitter.emit_expr(v.init, ci, {}, False), v.type_ann)
                else:
                    vcpp = GD_TYPE_DEFAULTS.get(v.type_ann or "", "gd::GdVal::null()")
                slines.append(f"    this->f_{v.name} = {vcpp};")
            slines.append("}")
            # meta()
            slines.append(f"const gd::GdClassMeta* {ci.cpp_name}::meta() const {{ return &META_{ci.cpp_name}; }}")
            # get_static_const_or_enum
            slines.append(f"gd::GdVal {ci.cpp_name}::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {{")
            consts = [v for v in ci.decl.vars if v.is_const]
            enums = [e for e in ci.decl.enums if e.name]
            if consts or enums or ci.own_inners:
                slines.append("    switch (prop) {")
                for e in enums:
                    slines.append(f"        case {symc.sym(e.name)}: return gd::GdVal::from_enum(&_enum_{ci.cpp_name}_{e.name});")
                for cvar in consts:
                    vcpp = emitter.coerce_wrap(emitter.emit_expr(cvar.init, ci, {}, True), cvar.type_ann) if cvar.init else "gd::GdVal::null()"
                    slines.append(f"        case {symc.sym(cvar.name)}: return {vcpp};")
                for iname, ici in ci.own_inners.items():
                    slines.append(f"        case {symc.sym(iname)}: return gd::GdVal::from_cls(&META_{ici.cpp_name});")
                slines.append("        default: break;")
                slines.append("    }")
            if ci.base:
                slines.append(f"    return {base_cpp}::get_static_const_or_enum(gd_ctx, prop);")
            else:
                slines.append("    return gd::GdVal::null();")
            slines.append("}")
            # get_static_prop_fn (uses static_arena ctx safely via temporary or static lookup)
            slines.append(f"bool {ci.cpp_name}::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {{")
            slines.append("    static thread_local gd::BattleCtx s_const_ctx(1u << 16);")
            slines.append("    s_const_ctx.arena.reset();")
            slines.append(f"    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);")
            slines.append("    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }")
            slines.append("    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }")
            slines.append("    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }")
            slines.append("    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }")
            slines.append("    return false;")
            slines.append("}")
            # get_prop
            slines.append(f"bool {ci.cpp_name}::get_prop(gd::SymId prop, gd::GdVal& out) const {{")
            inst_vars = [v for v in ci.decl.vars if not v.is_const]
            if inst_vars or enums or consts or ci.own_inners:
                slines.append("    switch (prop) {")
                for v in inst_vars:
                    slines.append(f"        case {symc.sym(v.name)}: out = this->f_{v.name}; return true;")
                if enums or consts or ci.own_inners:
                    for e in enums:
                        slines.append(f"        case {symc.sym(e.name)}: out = gd::GdVal::from_enum(&_enum_{ci.cpp_name}_{e.name}); return true;")
                    for iname, ici in ci.own_inners.items():
                        slines.append(f"        case {symc.sym(iname)}: out = gd::GdVal::from_cls(&META_{ici.cpp_name}); return true;")
                    if consts:
                        for cvar in consts:
                            slines.append(f"        case {symc.sym(cvar.name)}: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;")
                slines.append("        default: break;")
                slines.append("    }")
            if ci.base:
                slines.append(f"    return {base_cpp}::get_prop(prop, out);")
            else:
                slines.append("    return false;")
            slines.append("}")
            # set_prop
            slines.append(f"bool {ci.cpp_name}::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {{")
            if inst_vars:
                slines.append("    switch (prop) {")
                for v in inst_vars:
                    w = emitter.coerce_wrap("val", v.type_ann)
                    slines.append(f"        case {symc.sym(v.name)}: this->f_{v.name} = {w}; return true;")
                slines.append("        default: break;")
                slines.append("    }")
            if ci.base:
                slines.append(f"    return {base_cpp}::set_prop(gd_ctx, prop, val);")
            else:
                slines.append("    return false;")
            slines.append("}")
            # has_own_method
            slines.append(f"bool {ci.cpp_name}::has_own_method(gd::SymId m) const {{")
            non_static_fs = [f for f in ci.decl.funcs if not f.is_static]
            if non_static_fs:
                slines.append("    switch (m) {")
                for f in non_static_fs:
                    slines.append(f"        case {symc.sym(f.name)}: return true;")
                slines.append("        default: break;")
                slines.append("    }")
            if ci.base:
                slines.append(f"    return {base_cpp}::has_own_method(m);")
            else:
                slines.append("    return false;")
            slines.append("}")
            # call_method
            slines.append(f"bool {ci.cpp_name}::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {{")
            if ci.decl.funcs:
                slines.append("    switch (m) {")
                for f in ci.decl.funcs:
                    if f.is_static:
                        slines.append(f"        case {symc.sym(f.name)}: out = sf_{f.name}(gd_ctx, args, argc); return true;")
                    else:
                        slines.append(f"        case {symc.sym(f.name)}: out = fn_{f.name}(args, argc); return true;")
                slines.append("        default: break;")
                slines.append("    }")
            if ci.base:
                slines.append(f"    return {base_cpp}::call_method(gd_ctx, m, args, argc, out);")
            else:
                slines.append("    return false;")
            slines.append("}")
            # call_static_fn
            slines.append(f"bool {ci.cpp_name}::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {{")
            static_fs = [f for f in ci.decl.funcs if f.is_static]
            if static_fs:
                slines.append("    switch (m) {")
                for f in static_fs:
                    slines.append(f"        case {symc.sym(f.name)}: out = sf_{f.name}(gd_ctx, args, argc); return true;")
                slines.append("        default: break;")
                slines.append("    }")
            if ci.base:
                slines.append(f"    return {base_cpp}::call_static_fn(gd_ctx, m, args, argc, out);")
            else:
                slines.append("    return false;")
            slines.append("}")
            # Function definitions
            for f in ci.decl.funcs:
                if f.is_static:
                    slines.append(f"gd::GdVal {ci.cpp_name}::sf_{f.name}(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {{")
                else:
                    slines.append(f"gd::GdVal {ci.cpp_name}::fn_{f.name}(const gd::GdVal* _args, int _argc) {{")
                    slines.append("    gd::BattleCtx& gd_ctx = *this->rt_ctx_;")
                locals_: Dict[str, Optional[str]] = {}
                for pi, p in enumerate(f.params):
                    locals_[p.name] = p.type_ann
                    if p.default is not None:
                        def_cpp = emitter.emit_expr(p.default, ci, locals_, f.is_static)
                        slines.append(f"    gd::GdVal lv_{p.name} = (_argc > {pi}) ? _args[{pi}] : ({def_cpp});")
                    else:
                        slines.append(f"    gd::GdVal lv_{p.name} = (_argc > {pi}) ? _args[{pi}] : gd::GdVal::null();")
                    if p.type_ann in ("int", "float", "bool"):
                        slines.append(f"    lv_{p.name} = {emitter.coerce_wrap('lv_' + p.name, p.type_ann)};")
                emitter.emit_stmts(f.body, ci, locals_, f.is_static, slines, "    ")
                slines.append("    return gd::GdVal::null();")
                slines.append("}")
            # Allocator + Meta
            slines.append(f"static gd::GdObj* _alloc_{ci.cpp_name}(gd::BattleCtx& ctx) {{ return ctx.arena.make<{ci.cpp_name}>(&ctx); }}")
            base_meta_ptr = f"&META_{ci.base.cpp_name}" if ci.base else "nullptr"
            slines.append(
                f"const gd::GdClassMeta META_{ci.cpp_name} = {{"
                f"CLS_{ci.cpp_name}, {c_escape(ci.gd_name or '')}, {c_escape(ci.res_path)}, "
                f"{base_meta_ptr}, {'true' if ci.is_behavior_tree else 'false'}, "
                f"_alloc_{ci.cpp_name}, &{ci.cpp_name}::get_static_prop_fn, &{ci.cpp_name}::call_static_fn}};"
            )
            slines.append("")

        (shard_dir / f"shard_{s_idx:02d}.cpp").write_text("\n".join(slines), encoding="utf-8")

    # Write sym_ids.hpp and sym_ids.cpp AFTER all files have registered their symbols
    sym_h = ["#pragma once", '#include "../gd_rt.hpp"', "", "enum GenSym : gd::SymId {", "    SYM_GEN_START = gd::SYM_BUILTIN_END,"]
    for name, cid in symc.syms.items():
        sym_h.append(f"    {cid},")
    sym_h.extend(["};", "void register_gen_syms();", ""])
    (GEN_DIR / "sym_ids.hpp").write_text("\n".join(sym_h), encoding="utf-8")

    sym_c = ['#include "sym_ids.hpp"', "", "void register_gen_syms() {", "    static bool done = false; if (done) return; done = true;"]
    for name, cid in symc.syms.items():
        sym_c.append(f"    gd::register_sym({cid}, {c_escape(name)});")
    sym_c.append("}\n")
    (GEN_DIR / "sym_ids.cpp").write_text("\n".join(sym_c), encoding="utf-8")

    # Write class_metas.hpp
    cm_h = ["#pragma once", '#include "../gd_rt.hpp"', "", "enum GenClsId : gd::ClsId {", "    CLS_GEN_START = 1,"]
    for ci in order:
        cm_h.append(f"    CLS_{ci.cpp_name},")
    cm_h.append("};")
    for ci in order:
        cm_h.append(f"extern const gd::GdClassMeta META_{ci.cpp_name};")
    cm_h.append("")
    (GEN_DIR / "class_metas.hpp").write_text("\n".join(cm_h), encoding="utf-8")

    # Write register_all.cpp
    reg_c = ['#include "class_metas.hpp"', '#include "sym_ids.hpp"', "", "extern \"C\" void gd_init_all_classes() {", "    static bool done = false; if (done) return; done = true;", "    register_gen_syms();"]
    for ci in order:
        reg_c.append(f"    gd::register_class(&META_{ci.cpp_name});")
    reg_c.append("}\n")
    (GEN_DIR / "register_all.cpp").write_text("\n".join(reg_c), encoding="utf-8")

    print(f"Generated {len(order)} classes ({len(symc.syms)} symbols) across {num_shards} shards into {GEN_DIR}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--parse-only", action="store_true")
    args = ap.parse_args()
    order, by_name = scan_and_parse()
    print(f"Parsed {len(order)} classes cleanly (including inner classes).")
    if not args.parse_only:
        generate_cpp(order, by_name)


if __name__ == "__main__":
    main()
