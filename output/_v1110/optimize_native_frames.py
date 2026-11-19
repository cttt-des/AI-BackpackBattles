"""Use concrete C++ receivers in the verified 1.1.10 frame scheduler."""
import argparse
import hashlib
from pathlib import Path
import re


COMBAT = "Gd__gd_core__CoreCombat"
CHARACTER = "Gd__gd_core__CoreCharacter"
CONTEXT = "Gd__gd_core__CoreContext"
GRID = "Gd__gd_core__CoreGrid"

RECEIVERS = {
    "gd::GdVal::from_obj(this)": ("this", COMBAT),
    "this->f_ctx": ("context()", CONTEXT),
    "this->f_opponent": ("opponent()", CHARACTER),
    "this->f_player": ("player()", CHARACTER),
}
TYPED_RECEIVERS = """    // The native battle constructs exact CoreContext and CoreCharacter objects.
    const auto context = [this] { return static_cast<Gd__gd_core__CoreContext*>(this->f_ctx.obj); };
    const auto opponent = [this] { return static_cast<Gd__gd_core__CoreCharacter*>(this->f_opponent.obj); };
    const auto player = [this] { return static_cast<Gd__gd_core__CoreCharacter*>(this->f_player.obj); };
"""

FAST_STAMINA = """    if (this->f_curStamina.kind == gd::GdVal::Kind::Float
            && lv_amount.kind == gd::GdVal::Kind::Float
            && this->f_maxStamina.kind == gd::GdVal::Kind::Float
            && this->f_temporaryMaxStamina.kind == gd::GdVal::Kind::Float) {
        const double stamina = this->f_curStamina.f + lv_amount.f;
        const double limit = this->f_maxStamina.f + this->f_temporaryMaxStamina.f;
        // Preserve gd_clamp's ordered comparisons, including NaN and signed zero.
        this->f_curStamina = gd::GdVal::from_float(stamina < 0.0 ? 0.0 : (stamina > limit ? limit : stamina));
        return gd::GdVal::null();
    }
"""


def checked_method(source, owner, name, expected):
    method = re.search(rf"^gd::GdVal {owner}::fn_{name}\([^\n]*\n.*?^\}}\n", source, re.M | re.S)
    if not method or hashlib.sha256(method[0].encode()).hexdigest() != expected:
        raise ValueError(f"Unexpected generated body for {owner}::{name}")
    return method


def lower_frame(body, dispatch_sources):
    for receiver, (typed, owner) in RECEIVERS.items():
        original = re.escape(receiver)

        def direct_method(match):
            symbol, name, arguments = match.groups()
            forwarding = f"case {symbol}: out = fn_{name}(args, argc); return true;"
            if forwarding not in dispatch_sources[owner]:
                raise ValueError(f"Unexpected {owner} dispatch for {symbol}")
            return f"{typed}->fn_{name}({arguments})"

        body = re.sub(
            rf"gd::call_method\(gd_ctx, {original}, (SYM_GEN_(\w+)_\d+), ((?:_ca|nullptr), \d+)\)",
            direct_method, body,
        )

    def context_property(match):
        symbol, name = match.groups()
        getter = f"case {symbol}: out = this->f_{name}; return true;"
        if getter not in dispatch_sources[CONTEXT]:
            return match[0]
        return f"context()->f_{name}"

    body = re.sub(r"gd::get_prop\(gd_ctx, this->f_ctx, (SYM_GEN_(\w+)_\d+)\)",
                  context_property, body)

    def set_context_property(match):
        symbol, name, expression = match.groups()
        setter = f"case {symbol}: this->f_{name} = val; return true;"
        if setter not in dispatch_sources[CONTEXT]:
            raise ValueError(f"Unexpected context setter for {symbol}")
        return f"context()->f_{name} = {expression};"

    body = re.sub(r"gd::set_prop\(gd_ctx, this->f_ctx, (SYM_GEN_(\w+)_\d+), ([^\n]+)\);",
                  set_context_property, body)

    inventory = r"gd::call_method\(gd_ctx, gd::get_prop\(gd_ctx, this->f_(opponent|player), SYM_GEN_inventory_\d+\), SYM_GEN_getItems_\d+, nullptr, 0\)"
    if not re.search(
        r"::fn_getItems\([^\n]*\n    gd::BattleCtx& gd_ctx = \*this->rt_ctx_;\n    return this->f_items;",
        dispatch_sources[GRID],
    ):
        raise ValueError("Unexpected CoreGrid inventory accessor")
    body = re.sub(inventory, rf"static_cast<{GRID}*>(\1()->f_inventory.obj)->f_items", body)
    body = re.sub(r"gd::gd_truth\(gd::GdVal::from_bool\(gd::gd_ne\(lv_gem, gd::GdVal::null\(\)\)\)\)",
                  "!lv_gem.is_null()", body)
    body = re.sub(r"gd::get_prop\(gd_ctx, this->f_ctx, (SYM_GEN_PHYSICS_DELTA_\d+)\)",
                  rf"{CONTEXT}::get_static_const_or_enum(gd_ctx, \1)", body)
    return body.replace("    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n",
                        "    gd::BattleCtx& gd_ctx = *this->rt_ctx_;\n" + TYPED_RECEIVERS, 1)


def optimize_scheduler(native):
    shards = native / "gen/shards"
    path = shards / "shard_03.cpp"
    source = path.read_text("utf8")
    dispatch_sources = {owner: (shards / shard).read_text("utf8") for owner, shard in (
        (COMBAT, "shard_03.cpp"), (CHARACTER, "shard_02.cpp"),
        (CONTEXT, "shard_07.cpp"), (GRID, "shard_13.cpp"),
    )}
    functions = {
        "physicsTick": "11fc7eb9a75067a3dfee503f1ca4ff0a8fd9d8310d5ae1a0d66d4c05ed9cda2e",
        "stepCharacterIdle": "2d35d644edcc499b288c040d5096c8a753a0f6175f07fe62b92e11583062d5e1",
    }
    for name, expected in functions.items():
        method = checked_method(source, COMBAT, name, expected)
        lower = lower_frame(method[0], dispatch_sources)
        source = source[:method.start()] + lower + source[method.end():]

    # A constant read should use the context's accessor rather than building
    # the static-property dispatcher's thread-local arena each frame.
    old = "gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreContext), SYM_GEN_PHYSICS_DELTA_1404)"
    new = f"{CONTEXT}::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1404)"
    accessor = "case SYM_GEN_PHYSICS_DELTA_1404: return gd::GdVal::from_float(0.01666666753590107);"
    if accessor not in dispatch_sources[CONTEXT] or old not in source:
        raise ValueError("Unexpected physics step accessor")
    source = source.replace(old, new)
    context_header = f'#include "../hdrs/{CONTEXT}.hpp"\n'
    if context_header not in source:
        start = source.index("#include ")
        source = source[:start] + context_header + source[start:]
    path.write_text(source, encoding="utf8", newline="\n")


def optimize_character(native):
    generated = native / "gen"
    path = generated / "shards/shard_02.cpp"
    source = path.read_text("utf8")
    headers = {path.stem: path.read_text("utf8") for path in (generated / "hdrs").glob("*.hpp")}
    for name in ("getMaxStamina", "clampStamina", "addStamina", "isStunned", "endStun"):
        declaration = re.compile(rf"\bfn_{name}\(")
        if {owner for owner, body in headers.items() if declaration.search(body)} != {CHARACTER}:
            raise ValueError(f"Unexpected implementations of CoreCharacter::{name}")

    checked_method(source, CHARACTER, "clampStamina", "38f853cbfeaa46647b1d3b19272acc36126fb5f9d7d2bf40876183747e57f4fc")
    checked_method(source, CHARACTER, "getMaxStamina", "24d9734864d6b2d7d93857467ad7d5327cdff2540ad6b142fc695a2b01395f80")
    add_stamina = checked_method(
        source, CHARACTER, "addStamina", "8f1c0de24940ba9ba98e3fc2d8d143c23a1d50ff62ff6b29d4679142d7eaac57",
    )
    # Literal #8 is the folded empty string used by the generated trace guard.
    literals = re.search(r"constexpr gd::GdStr battle_string_literals\[\] = \{(.*?)^\};", source, re.S | re.M)[1]
    if literals.splitlines()[9].strip() != '{"", 0u, 2166136261u},':
        raise ValueError("Stamina trace guard is no longer constant")
    body = add_stamina[0].replace("    this->f_curStamina =", FAST_STAMINA + "    this->f_curStamina =", 1)
    trace_start = body.index("    if (gd::gd_truth(")
    body = body[:trace_start] + "    return gd::GdVal::null();\n}\n"
    source = source[:add_stamina.start()] + body + source[add_stamina.end():]

    tick = checked_method(
        source, CHARACTER, "physicsTickCharacter", "e6c6c112205755a1ce23c668e8dcbab618a39e96d1eae8356703f53d9f6398ed",
    )
    body = re.sub(
        r"gd::call_method\(gd_ctx, gd::GdVal::from_obj\(this\), SYM_GEN_(isStunned|endStun|addStamina)_\d+,",
        r"this->fn_\1(", tick[0],
    ).replace("( nullptr", "(nullptr").replace("( _ca", "(_ca")
    source = source[:tick.start()] + body + source[tick.end():]

    timers = checked_method(
        source, CHARACTER, "tickPhysicsTimers", "7bbbc96c5bc319a5611d0e6d2d2fb7fc770f1985f47ea1e15d6150930db57553",
    )
    body = re.sub(
        r"    if \(gd::gd_truth\(\(gd::gd_truth\(this->(f__\w+)\) \? [^\n]*"
        r"gd::gd_bitand\(this->f__physics_timer_mask, gd::GdVal::from_int\((\d+)LL\)\)[^\n]*\{",
        r"    if (gd::gd_truth(this->\1) && (this->f__physics_timer_mask.as_int() & \2)) {",
        timers[0],
    )
    if body.count("f__physics_timer_mask.as_int()") != 4:
        raise ValueError("Expected four independently checked character timers")
    source = source[:timers.start()] + body + source[timers.end():]

    snapshot = checked_method(
        source, CHARACTER, "snapshotPhysicsTimers", "eeb1b46d96224e7d13a839f1d19fde520c1e1f507dd75798436159fea49ecf1e",
    )
    body = """gd::GdVal Gd__gd_core__CoreCharacter::fn_snapshotPhysicsTimers(const gd::GdVal*, int) {
    const int64_t mask = (gd::gd_truth(this->f__tick_timer_active) ? 1 : 0)
                       | (gd::gd_truth(this->f__rage_active) ? 2 : 0)
                       | (gd::gd_truth(this->f__invul_active) ? 4 : 0)
                       | (gd::gd_truth(this->f__autoRage_active) ? 8 : 0);
    this->f__physics_timer_mask = gd::GdVal::from_int(mask);
    return gd::GdVal::null();
}
"""
    source = source[:snapshot.start()] + body + source[snapshot.end():]

    buffs = checked_method(
        source, CHARACTER, "tickBuffs", "97e83d6e788f9b9bfcb128a4a31f1337bcf34761cb05379e1c03b36d2edce05e",
    )
    body = buffs[0].replace("if (gd::gd_truth(buff->f__timer_active))",
                            "const auto& active = buff->f__timer_active;\n"
                            "        if (active.kind == gd::GdVal::Kind::Bool ? active.b : gd::gd_truth(active))")
    source = source[:buffs.start()] + body + source[buffs.end():]
    path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("native", type=Path)
    parser.add_argument("--part", choices=("scheduler", "character", "all"), default="scheduler")
    args = parser.parse_args()
    if args.part in ("scheduler", "all"):
        optimize_scheduler(args.native)
    if args.part in ("character", "all"):
        optimize_character(args.native)
