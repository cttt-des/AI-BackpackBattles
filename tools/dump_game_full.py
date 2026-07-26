"""
锁定 members_off=0x20 + CowData(size@ptr-4)，dump 每个候选子节点的完整成员，
只显示 int/real/bool 值，便于用「游戏内数值」肉眼识别 Game / Player 单例。
"""
import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.window_manager import WindowManager
from core.memory_reader import MemoryReader
from core.godot_probe import discover_os_singleton_rva
from core.godot_reader import GODOT_OFFSETS

SI_OFF = 0x58
CHILDREN_OFF = 0x6C0
ML_OFF = 0x1D0
ROOT_OFF = 0x230
MEMBERS_OFF = 0x20
VARIANT_SIZE = 24


def ru64(r, a):
    d = r.read(a, 8)
    return struct.unpack("<Q", d)[0] if d and len(d) == 8 else None


def ru32(r, a):
    d = r.read(a, 4)
    return struct.unpack("<I", d)[0] if d and len(d) == 4 else None


def rvariant(r, a):
    t = ru32(r, a)
    if t is None:
        return None
    if t == 2:
        d = r.read(a + 8, 8)
        return ("int", struct.unpack("<q", d)[0]) if d and len(d) == 8 else None
    if t == 3:
        d = r.read(a + 8, 8)
        return ("real", round(struct.unpack("<d", d)[0], 3)) if d and len(d) == 8 else None
    if t == 1:
        d = r.read(a + 8, 8)
        return ("bool", bool(struct.unpack("<q", d)[0])) if d and len(d) == 8 else None
    if t == 4:
        return ("str", "<String>")
    return (f"t{t}", None)


def enum_children(r, root):
    out = []
    elem = ru64(r, root + CHILDREN_OFF)
    guard = 0
    while elem and elem > 0x10000 and guard < 5000:
        val = ru64(r, elem)
        if val and val > 0x10000:
            out.append(val)
        elem = ru64(r, elem + 8)
        guard += 1
    return out


def read_members(r, node):
    si = ru64(r, node + SI_OFF)
    if not si or si < 0x10000:
        return None, None
    vec = ru64(r, si + MEMBERS_OFF)
    if not vec or vec < 0x10000:
        return si, None
    sz = ru32(r, vec - 4)
    if sz is None or sz <= 0 or sz > 4000:
        return si, None
    out = []
    for i in range(sz):
        out.append(rvariant(r, vec + i * VARIANT_SIZE))
    return si, out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, default=None)
    ap.add_argument("--min", type=int, default=6)
    ap.add_argument("--max", type=int, default=200)
    ap.add_argument("--find", type=int, default=None, help="只显示成员里含此整数值的节点")
    args = ap.parse_args()

    pid = args.pid
    if not pid:
        wm = WindowManager()
        if not wm.refresh():
            print("ERROR: 未找到游戏窗口")
            return 1
        pid = wm.window.pid

    r = MemoryReader(pid)
    base = r.module_base
    rva, _ = discover_os_singleton_rva(r, GODOT_OFFSETS, diag=True)
    os_obj = ru64(r, base + rva)
    root = ru64(r, ru64(r, os_obj + ML_OFF) + ROOT_OFF)
    children = enum_children(r, root)
    print(f"[*] base={hex(base)} rva={hex(rva)} root={hex(root)} 子节点={len(children)}\n")

    for ci, node in enumerate(children):
        si, mem = read_members(r, node)
        if not mem:
            continue
        sz = len(mem)
        if sz < args.min or sz > args.max:
            continue
        # 仅统计标量成员（int/real/bool）
        scalars = [(i, v) for i, v in enumerate(mem)
                   if v and v[0] in ("int", "real", "bool")]
        if args.find is not None:
            if not any(v[0] in ("int", "real") and v[1] == args.find for _, v in scalars):
                continue
        print(f"=== child[{ci:3d}] node={hex(node)} si={hex(si)} size={sz} "
              f"标量数={len(scalars)} ===")
        for i, v in enumerate(mem):
            tag = ""
            if v and v[0] in ("int", "real"):
                tag = "  <<"
            print(f"    [{i:2d}] {v}{tag}")
        print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
