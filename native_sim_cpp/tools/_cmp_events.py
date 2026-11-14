# -*- coding: utf-8 -*-
"""native 事件流 vs py 腿留档事件流 逐行对拍——定位内核首个分叉事件。

用法: python -X utf8 native_sim_cpp/tools/_cmp_events.py run1160_r18 [run570_r18 ...]
"""
import ctypes
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))  # bundle root

from native_sim.sim import get_simulator  # noqa: E402

ROOT = Path(r"D:\文件资料\学习\自动背包AI")


def f2h(x: float) -> str:
    return "f:%016x" % struct.unpack(">Q", struct.pack(">d", float(x)))[0]


def canon_val(v):
    if v is None:
        return "n"
    if isinstance(v, bool):
        return "b:1" if v else "b:0"
    if isinstance(v, int):
        return "i:%d" % v
    if isinstance(v, float):
        return f2h(v)
    if isinstance(v, str):
        return "s:" + v
    if isinstance(v, list):
        return "a:[" + ",".join(canon_val(x) for x in v) + "]"
    if isinstance(v, dict):
        return "d:{" + ",".join("%s=%s" % (k, canon_val(x)) for k, x in sorted(v.items())) + "}"
    return "x:" + type(v).__name__


STACK_NAMES = {100: "block", 101: "lucky", 102: "regen", 103: "vampirism",
               104: "spikes", 105: "mana", 106: "empower", 107: "heat",
               108: "poison", 109: "blind", 110: "cold",
               # CoreDamageSource.Type 全集（Melee=0…Fatigue=99）：py 腿以 keyword
               # 渲染，native 以 Int origin 出现——映射后按行对齐
               0: "melee", 1: "ranged", 2: "effect", 3: "selfdamage",
               98: "unhealing", 99: "fatigue",
               # EventType 22=BattleRageEnd 兼作 origin（run635 id1093 实测：
               # py 渲染 dmgsrc:battlerageend，native 是 Int 22）
               22: "battlerageend"}


def coarse_origin(origin_str: str) -> str:
    # 口径归一：宝石事件 py 记宿主（kind=gem, 无 identifier），native 记宝石物品自身
    # identifier + ownerType=7(Socket)；伤害源 py 记 kind=damage_source，native 记类名。
    if origin_str.startswith("o:item:") and origin_str.endswith("#7"):
        return "o:gem"
    if origin_str.startswith("o:cls:") and "DamageSource" in origin_str:
        return "o:dmgsrc"
    if origin_str.startswith("i:") and int(origin_str[2:]) in STACK_NAMES:
        return "o:dmgsrc:" + STACK_NAMES[int(origin_str[2:])]
    return origin_str


def py_origin_coarse(o) -> str:
    if o is None:
        return "n"
    if isinstance(o, bool):
        return "b:1" if o else "b:0"
    if isinstance(o, int):
        return "i:%d" % o
    if isinstance(o, dict):
        k = o.get("kind")
        if k == "item":
            return "o:item:%s#%s" % (o.get("identifier"), o.get("owner_type"))
        if k == "gem":
            return "o:gem"
        if k == "damage_source":
            return "o:dmgsrc:" + str(o.get("keyword"))
        return "o:%s" % k
    return "x:" + str(o)


def py_row_canonical(r: dict) -> str:
    tgt = r.get("target")
    tgt = -999 if tgt is None else int(tgt)
    par = r.get("parent_id")
    par = -1 if par is None else int(par)
    origin = py_origin_coarse(r.get("origin"))
    return "ts=%s|type=%s|id=%s|tgt=%d|parent=%d|origin=%s|params=%s" % (
        f2h(r.get("timestamp") or 0.0), r.get("type"), r.get("id"), tgt, par,
        origin, canon_val(r.get("params") or {}))


PY_LEG_ROOT = ROOT / "output" / "oracle" / "align" / "py"  # REG9（旧语料）py 腿留档根


def native_lines(sim, case) -> list[str]:
    lib = sim.lib
    lib.gd_sim_set_dbg_events.argtypes = [ctypes.c_int32]
    lib.gd_sim_set_dbg_events.restype = None
    lib.gd_sim_set_dbg_events(1)  # 调试记录只允许单线程 run_one 路径
    lib.gd_sim_dbg_event_count.argtypes = []
    lib.gd_sim_dbg_event_count.restype = ctypes.c_int32
    lib.gd_sim_dbg_event_line.argtypes = [ctypes.c_int32]
    lib.gd_sim_dbg_event_line.restype = ctypes.c_char_p
    res = sim.run_one(case["player"], case["opponent"],
                      seed=int(case["seed"]), round_id=int(case.get("round_id", 1)),
                      label_rng_enabled=bool(case.get("label_rng", True)),
                      custom_health_multiplier=float(case.get("custom_health_multiplier", 100.0)),
                      native_activation_order=True, reseed_after_player_character=True,
                      below_master=True, formal_ev_gate=25000, max_time=90.0)
    n = lib.gd_sim_dbg_event_count()
    lines = []
    for i in range(n):
        s = lib.gd_sim_dbg_event_line(i)
        lines.append(s.decode("utf-8", "replace") if s else "")
    return lines


def main() -> int:
    sim = get_simulator()
    src = ROOT / "gd_core_test" / "expand_align_cases.json" if "--expand" in sys.argv else ROOT / "gd_core_test" / "oracle_align_cases.json"
    cases = {c["case_id"]: c for c in json.load(open(src, encoding="utf-8"))["cases"]}
    exit_code = 0
    for cid in [a for a in sys.argv[1:] if not a.startswith("--")]:
        case = cases[cid]
        py_root = PY_LEG_ROOT
        if "--expand" in sys.argv:
            py_root = ROOT / "output" / "oracle" / "align_expand" / "py"
        pyd = json.load(open(py_root / cid / "events.json", encoding="utf-8"))
        py_rows = [r for r in pyd["events"] if r.get("id") is not None and r["id"] >= 0]  # 去合成行
        py_canon = [py_row_canonical(r) for r in py_rows]
        nat = native_lines(sim, case)
        print(f"== {cid}: py kernel rows={len(py_canon)} native rows={len(nat)} "
              f"(py ticks={pyd['ticks']} native ticks~)")
        m = min(len(py_canon), len(nat))
        first = None
        def coarse_origin_seg(line: str) -> str:
            # 行内 origin 段归一（origin= 到 |params= 之间）
            a = line.index("|origin=") + len("|origin=")
            b = line.index("|params=")
            return line[:a] + coarse_origin(line[a:b]) + line[b:]

        nat = [coarse_origin_seg(x) for x in nat]

        for i in range(m):
            if py_canon[i] != nat[i]:
                first = i
                break
        if first is None:
            if len(py_canon) == len(nat):
                print(f"   全部 {m} 行逐位一致")
            else:
                print(f"   前 {m} 行一致；行数不同（尾段 py: {py_canon[m:m+3]}")
                print(f"                                    native: {nat[m:m+3]}）")
                exit_code = 1
            continue
        exit_code = 1
        print(f"   首个分叉行 #{first}（0 起）：")
        lo = max(0, first - 2)
        for i in range(lo, min(m, first + 6)):
            mark = ">>" if i == first else "  "
            print(f"   {mark} py {py_canon[i]}")
            print(f"   {mark} nt {nat[i]}")
        if len(nat) != len(py_canon):
            print(f"   行数差: py={len(py_canon)} native={len(nat)}")
    return exit_code


if __name__ == "__main__":
    raise SystemExit(main())
