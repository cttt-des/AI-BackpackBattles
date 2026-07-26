"""
用已知节点(Combat, node=0x...)反推 Node.name(StringName) 的偏移。
StringName 在 Godot 3.x：字段是 _Data*；_Data 里含 String name。
本工具扫描节点前 0x40..0x400 字节的每个指针，逐层尝试把它解释为
StringName->_Data->(某偏移)->String，解码看能否得到 "Combat"。
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
from tools.script_paths import read_godot_string

ML_OFF = 0x1D0
ROOT_OFF = 0x230


def ru64(r, a):
    d = r.read(a, 8)
    return struct.unpack("<Q", d)[0] if d and len(d) == 8 else None


def ru32(r, a):
    d = r.read(a, 4)
    return struct.unpack("<I", d)[0] if d and len(d) == 4 else None


def get_children_vec(r, obj, off):
    ptr = ru64(r, obj + off)
    cnt = ru32(r, ptr - 4) if ptr else None
    out = []
    if ptr and cnt and 0 < cnt < 500:
        for i in range(cnt):
            out.append(ru64(r, ptr + i * 8))
    return out


def try_decode_stringname(r, sn_field_addr, want):
    """sn_field_addr 存放 _Data*；在 _Data 内不同偏移尝试 String。返回(命中偏移, s)。"""
    data = ru64(r, sn_field_addr)
    if not data or data < 0x10000:
        return None
    for doff in range(0, 0x60, 8):
        strptr = ru64(r, data + doff)
        if not strptr or strptr < 0x10000:
            continue
        s = read_godot_string(r, strptr)
        if s == want:
            return (doff, s)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, default=None)
    ap.add_argument("--want", default="Combat")
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
    kids = get_children_vec(r, root, 0x108)
    print(f"[*] root={hex(root)} root+0x108 子节点数={len(kids)}")
    # Combat 节点是 root 子节点里带 Combat.gd 的那个（node=0x1b250d83380 之前已知）
    combat = 0x1b250d83380
    print(f"[*] 用 Combat 节点 {hex(combat)} 反推 name 偏移，目标字符串='{args.want}'\n")

    for noff in range(0x8, 0x400, 8):
        res = try_decode_stringname(r, combat + noff, args.want)
        if res:
            doff, s = res
            print(f"[+] 命中: node.name 字段偏移 = {hex(noff)}，_Data 内 String 偏移 = {hex(doff)}  值='{s}'")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
