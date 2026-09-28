#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""compare_events.py — 双引擎**逐事件**对照（Task #9 的判定工具）

它回答的问题
============
「GDScript 版内核」与「Python 转写版」在**同一批对局**里，是否发出了**逐条相同**的
战斗事件流。

此前已有的证据只到**摘要**一级：56 局的
`win / t / php / ohp / act / dmg / heal / gem / fat / stun` 逐字符一致
（闸门 13/14）。摘要一致是必要条件，不是充分条件 —— 两句不同的战斗可以有完全相同的
摘要（某次伤害被挪后一拍、某个层数施加到了另一件物品、某次治疗换了起源）。
本工具把口径推到 `CoreCombatLog` 的**每一次 logEvent**，即原版战斗事件的全部输出面。

两侧取样面（同构，各自实现）
===========================
    事件汇点：CoreCombatLog.logEvent(event) → _ctx.hooks.logEvent(event)
    行格式  ：<id>|<type>|<depth>|<origin>|<target>|<params>
    GDScript：gd_core_test/LineupBattle.gd 的 HookProbe._eline
    Python  ：tools/run_gd_py.py 的 eline
    输入文件：gd_core_test/event_trace.txt  vs  output/py_event_trace.txt

差异分级（★ 本工具的核心，不是「相等/不等」二值）
================================================
两侧的**数值表示**本来就可能不同：GDScript 的 `int` 与 `float` 是两种类型，
Python 的转写产物里 `4` 与 `4.0` 也可能各自成立（整除规则、`round()` 返 float 等）。
把这类差异直接判 FAIL 会让工具变成噪声源；直接忽略又会让真差异溜过去。故分三级：

  SAME      逐字符相同
  NUMEQ     仅数值表示不同（`4` vs `4.000000`），且两侧**数值相等**。
            → 不是逻辑差异；但它**值得计数**：数量突变说明某处类型语义变了。
  DIFF      其余（值不等 / 字段结构不同 / 事件条数不同）
            → 必须逐条归因，不得有 UNATTRIBUTED

★ 「值相等」为什么不等于「无害」：若某处 `int` 参与了整除或取余，类型一变结果就变。
  故 NUMEQ 只说明**这一处**的事件输出相同；它的存在理由要回源码核。
  工具会按 (事件类型, 字段名) 聚合 NUMEQ，便于一眼看出集中在哪几条 createEvent_*。

用法
====
    python tools/compare_events.py               # 全量对照，非零退出码 = 有 DIFF
    python tools/compare_events.py --show 10     # 每类差异多打印几条
    python tools/compare_events.py --numeq-detail
"""
import argparse
import io
import os
import sys
from collections import Counter, defaultdict

sys.stdout.reconfigure(encoding="utf-8")

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GD_TRACE = os.path.join(ROOT, "gd_core_test", "event_trace.txt")
PY_TRACE = os.path.join(ROOT, "output", "py_event_trace.txt")


def read_traces(path):
    """→ [(header, [line, ...]), ...]，按 `## a|b|seed` 分块。"""
    if not os.path.exists(path):
        raise SystemExit("FAIL 缺轨迹文件：%s\n"
                         "     GDScript 侧：跑 gd_core_test/LineupBattle.gd\n"
                         "     Python 侧 ：跑 tools/run_gd_py.py" % path)
    out, header, lines = [], None, []
    for raw in io.open(path, encoding="utf-8"):
        ln = raw.rstrip("\n")
        if ln.startswith("## "):
            if header is not None:
                out.append((header, lines))
            header, lines = ln[3:], []
        elif ln:
            lines.append(ln)
    if header is not None:
        out.append((header, lines))
    return out


def num(v):
    """把 canonical 值解析成 (kind, number)；非数值返回 None。

    kind ∈ {"int", "float"}。canonical 约定（两侧同构）：
      GDScript/Python 的 int  → `i<N>`；float → `%.6f`；bool → `T`/`F`；null → `-`。

    ★ 先剥 `i` 前缀再比数值，是因为 GDScript 的带类型变量**会在赋值时强制转换**
      （`var damage: int` ← `damage * 1.5` 得 int），而 Python 不会 —— 于是同一处
      两侧可能一个 int 一个 float。这类差异必须单独成级，不能混进 DIFF。
    """
    if v == "-":
        return None
    if v.startswith("i") and v[1:].lstrip("-").isdigit():
        return ("int", int(v[1:]))
    try:
        return ("float", float(v))
    except ValueError:
        return None


def fields(line):
    """`id|type|depth|origin|target|params` → 6 元组；params 再拆成 dict。"""
    parts = line.split("|")
    if len(parts) != 6:
        return None
    params = {}
    if parts[5]:
        for kv in parts[5].split(","):
            k, _, v = kv.partition("=")
            params[k] = v
    return (parts[0], parts[1], parts[2], parts[3], parts[4], params)


def compare_line(a, b):
    """→ (class, detail)；class ∈ {"SAME","NUMEQ","DIFF"}。

    NUMEQ 细分（写进 detail，便于聚合）：
      `k:int≠float`  两侧都是数、数值相等，但一个是 int 一个是 float
      `k:fmt`        两侧同类型、数值相等，只是格式化不同（如 -0.0）
    """
    if a == b:
        return "SAME", ""

    fa, fb = fields(a), fields(b)
    if fa is None or fb is None:
        return "DIFF", "格式不可解析"

    # 事件号必须一致 —— 它是配对键，不一致说明整体错位
    if fa[0] != fb[0]:
        return "DIFF", "事件号 %s≠%s" % (fa[0], fb[0])

    for i, name in enumerate(("type", "depth", "origin", "target")):
        if fa[i + 1] != fb[i + 1]:
            return "DIFF", "%s: %s≠%s" % (name, fa[i + 1], fb[i + 1])

    # params：键集合必须一致，值可数值等价
    if set(fa[5]) != set(fb[5]):
        return "DIFF", "params 键不同: %s vs %s" % (
            sorted(fa[5]), sorted(fb[5]))

    numeq = []
    for k in sorted(fa[5]):
        va, vb = fa[5][k], fb[5][k]
        if va == vb:
            continue
        na, nb = num(va), num(vb)
        if na is None or nb is None or na[1] != nb[1]:
            # 值真的不等（或一侧根本不是数）—— 这是必须归因的差异
            return "DIFF", "params[%s]: %s≠%s" % (k, va, vb)
        numeq.append("%s:%s" % (k, "int≠float" if na[0] != nb[0] else "fmt"))

    if numeq:
        return "NUMEQ", ",".join(numeq)
    return "DIFF", "未知差异"


# createEvent_* ↔ EventType 名（供报告把差异落到源码函数上）
def load_type_names():
    sys.path.insert(0, ROOT)
    try:
        from gd_core_py import _bootstrap, _registry as _R
        _bootstrap.load_all()
        E = _R.C("res://gd_core/CoreConst.gd").EventType
        return {v: k for k, v in E.items()}
    except Exception as exc:            # 拿不到就退化成裸 int，不影响判定
        print("（提示：无法装载 CoreConst 取事件类型名：%s）" % exc)
        return {}


def main():
    ap = argparse.ArgumentParser(description="双引擎逐事件对照")
    ap.add_argument("--show", type=int, default=5, help="每类差异打印条数")
    ap.add_argument("--numeq-detail", action="store_true",
                    help="按 (事件类型, 字段) 聚合 NUMEQ")
    args = ap.parse_args()

    gd = read_traces(GD_TRACE)
    py = read_traces(PY_TRACE)
    tnames = load_type_names()

    print("=== 双引擎逐事件对照 ===")
    print("  GDScript：%s（%d 局 / %d 条事件）"
          % (os.path.relpath(GD_TRACE, ROOT), len(gd),
             sum(len(x[1]) for x in gd)))
    print("  Python  ：%s（%d 局 / %d 条事件）"
          % (os.path.relpath(PY_TRACE, ROOT), len(py),
             sum(len(x[1]) for x in py)))

    # 对局必须一一对应且同序
    gh = [h for h, _ in gd]
    ph = [h for h, _ in py]
    if gh != ph:
        print("\n[FAIL] 对局序列不一致：")
        for i in range(max(len(gh), len(ph))):
            a = gh[i] if i < len(gh) else "<缺>"
            b = ph[i] if i < len(ph) else "<缺>"
            if a != b:
                print("   #%d  GD=%s  PY=%s" % (i, a, b))
        print("EVENTS: FAIL")
        return 1

    n_same = n_numeq = n_diff = 0
    numeq_agg = Counter()
    diff_kind = Counter()
    examples = defaultdict(list)
    total = 0

    for (h, gl), (_, pl) in zip(gd, py):
        if len(gl) != len(pl):
            n_diff += 1
            diff_kind["事件条数不同"] += 1
            examples["事件条数不同"].append(
                "%s：GD %d 条 vs PY %d 条" % (h, len(gl), len(pl)))
            continue
        for i, (a, b) in enumerate(zip(gl, pl)):
            total += 1
            cls, detail = compare_line(a, b)
            if cls == "SAME":
                n_same += 1
            elif cls == "NUMEQ":
                n_numeq += 1
                tname = tnames.get(int(a.split("|")[1]), a.split("|")[1])
                numeq_agg[(tname, detail)] += 1
            else:
                n_diff += 1
                diff_kind[detail.split(":")[0]] += 1
                if len(examples[detail.split(":")[0]]) < args.show:
                    examples[detail.split(":")[0]].append(
                        "%s\n      #%d GD: %s\n      #%d PY: %s"
                        % (h, i + 1, a, i + 1, b))

    if total == 0 and n_diff == 0:
        print("\n[FAIL] 两侧都没有可比对的事件 —— 这是空断言，不是通过")
        print("EVENTS: FAIL")
        return 1

    print("\n── 逐条判定 ──")
    print("  可比对事件 %d 条" % total)
    print("    SAME  %6d" % n_same)
    print("    NUMEQ %6d   （仅 int/float 表示不同，数值相等）" % n_numeq)
    print("    DIFF  %6d" % n_diff)

    if numeq_agg:
        print("\n── NUMEQ 聚合（事件类型 × 字段） ──")
        for (t, f), n in numeq_agg.most_common():
            print("    %-28s %-12s ×%d" % (t, f, n))
        if args.numeq_detail:
            print("    ★ 这些位置两侧数值相等、仅类型表示不同。要判断是否无害，")
            print("      需回源码看该字段是否参与整除/取余（类型一变结果就变）。")

    if diff_kind:
        print("\n── DIFF 分类 ──")
        for k, n in diff_kind.most_common():
            print("    %-28s ×%d" % (k, n))
            for e in examples[k]:
                print("      " + e)

    print()
    if n_diff:
        print("EVENTS: FAIL（%d 条 DIFF，须逐条归因；不允许 UNATTRIBUTED）" % n_diff)
        return 1
    print("EVENTS: PASS（%d 条事件：SAME %d + NUMEQ %d，无值级差异）"
          % (total, n_same, n_numeq))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
