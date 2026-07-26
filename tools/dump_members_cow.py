"""
诊断：枚举根视口全部子节点，对每个子节点尝试用 CowData 约定读取 GDScript 成员向量。

关键修正点
----------
Godot 3.x 的 Vector<T> 实际上是 CowData<T>——只有一个指针 _ptr；
元素个数存放在 _ptr 前 4 字节处（uint32），引用计数在 _ptr 前 8 字节处。
之前的读取假设「_ptr 在 +0，size(int32) 在 +8」是错的，导致 msize 读出垃圾。

本工具对每个子节点：
  * 读 script_instance = *(node + si_off)
  * 对候选 members_off，取 vec_ptr = *(si + members_off)
  * 用 CowData 约定：size = *(uint32*)(vec_ptr - 4)
  * 若 size 合理（1..2000），dump 前若干个整数/实数成员
从而定位 Game（成员最多、含明显数值的那个）。
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

SI_OFF = 0x58          # object -> script_instance
CHILDREN_OFF = 0x6C0   # node -> children List
ML_OFF = 0x1D0
ROOT_OFF = 0x230
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
    if t == 2:  # INT
        d = r.read(a + 8, 8)
        return ("int", struct.unpack("<q", d)[0]) if d and len(d) == 8 else None
    if t == 3:  # REAL (double)
        d = r.read(a + 8, 8)
        return ("real", struct.unpack("<d", d)[0]) if d and len(d) == 8 else None
    if t == 1:  # BOOL
        d = r.read(a + 8, 8)
        return ("bool", bool(struct.unpack("<q", d)[0])) if d and len(d) == 8 else None
    if t == 4:  # STRING
        return ("str", None)
    return (f"t{t}", None)


def enum_children(r, root):
    """返回 root 的所有子节点地址列表。"""
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


def cow_size(r, vec_ptr):
    """CowData：size 在 _ptr - 4 处（uint32）。"""
    if not vec_ptr or vec_ptr < 0x10000:
        return None
    return ru32(r, vec_ptr - 4)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, default=None)
    ap.add_argument("--min-size", type=int, default=3, help="只显示成员数 >= 此值的节点")
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
    print(f"[*] 模块基址 = {hex(base)}  PID={pid}")

    rva, _ = discover_os_singleton_rva(r, GODOT_OFFSETS, diag=True)
    if not rva:
        print("[-] 未定位 OS::singleton")
        return 1
    print(f"[*] os_singleton_rva = {hex(rva)}")

    os_obj = ru64(r, base + rva)
    main_loop = ru64(r, os_obj + ML_OFF)
    root = ru64(r, main_loop + ROOT_OFF)
    print(f"[*] OS={hex(os_obj)} SceneTree={hex(main_loop)} root={hex(root)}")

    children = enum_children(r, root)
    print(f"[*] 根视口子节点数 = {len(children)}")

    members_offs = [0x10, 0x18, 0x20, 0x28, 0x30]
    print(f"[*] 对每个子节点尝试 members_off ∈ {[hex(x) for x in members_offs]}，"
          f"用 CowData(size@ptr-4) 读取\n")

    hits = []
    for ci, node in enumerate(children):
        si = ru64(r, node + SI_OFF)
        if not si or si < 0x10000:
            continue
        for moff in members_offs:
            vec_ptr = ru64(r, si + moff)
            sz = cow_size(r, vec_ptr)
            if sz is None or sz < args.min_size or sz > 2000:
                continue
            # 采样前几个 variant，确认是合法 Variant 数组
            good = 0
            sample = []
            for i in range(min(sz, 12)):
                v = rvariant(r, vec_ptr + i * VARIANT_SIZE)
                if v is not None:
                    good += 1
                    sample.append(v)
            if good >= min(sz, 6) * 0.5:
                hits.append((ci, node, si, moff, sz, sample))

    if not hits:
        print("[-] 未找到任何具有合理成员向量的子节点（可能 si_off / members_off / CowData 约定仍需调整）")
        return 1

    for ci, node, si, moff, sz, sample in hits:
        print(f"child[{ci:3d}] node={hex(node)} si={hex(si)} members_off={hex(moff)} size={sz}")
        for i, v in enumerate(sample):
            print(f"        [{i:2d}] {v}")
        print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
