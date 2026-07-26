"""
用已确认的偏移遍历场景树，按节点名/脚本路径定位 Game 自动载入单例：
  children Vector<Node*>  @ node+0x108  (CowData: count@ptr-4)
  node.name StringName    @ node+0x130 -> _Data -> String@+0x10
  script_instance         @ node+0x58 ; script @ si+0x10
BFS 整棵树，命中 name=='Game' 或 script 含 Core/Game.gd 即报告其路径与地址。
"""
import argparse
import struct
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.window_manager import WindowManager
from core.memory_reader import MemoryReader
from core.godot_probe import discover_os_singleton_rva
from core.godot_reader import GODOT_OFFSETS
from tools.script_paths import read_godot_string

ML_OFF = 0x1D0
ROOT_OFF = 0x230
CHILDREN_OFF = 0x108
NAME_OFF = 0x130
NAME_DATA_STR_OFF = 0x10
SI_OFF = 0x58
SCRIPT_OFF = 0x10


def ru64(r, a):
    d = r.read(a, 8)
    return struct.unpack("<Q", d)[0] if d and len(d) == 8 else None


def ru32(r, a):
    d = r.read(a, 4)
    return struct.unpack("<I", d)[0] if d and len(d) == 4 else None


def node_name(r, node):
    data = ru64(r, node + NAME_OFF)
    if not data or data < 0x10000:
        return None
    strptr = ru64(r, data + NAME_DATA_STR_OFF)
    if not strptr or strptr < 0x10000:
        return None
    return read_godot_string(r, strptr)


def node_script(r, node):
    si = ru64(r, node + SI_OFF)
    if not si or si < 0x10000:
        return None
    script = ru64(r, si + SCRIPT_OFF)
    if not script or script < 0x10000:
        return None
    for off in range(0, 0x200, 8):
        p = ru64(r, script + off)
        if not p or p < 0x10000:
            continue
        s = read_godot_string(r, p)
        if s and s.startswith("res://") and s.endswith(".gd"):
            return s
    return None


def children(r, node):
    ptr = ru64(r, node + CHILDREN_OFF)
    if not ptr or ptr < 0x10000:
        return []
    cnt = ru32(r, ptr - 4)
    if not cnt or cnt <= 0 or cnt > 500:
        return []
    out = []
    for i in range(cnt):
        c = ru64(r, ptr + i * 8)
        if c and c > 0x10000:
            out.append(c)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, default=None)
    ap.add_argument("--max-depth", type=int, default=3)
    ap.add_argument("--rva", type=lambda x: int(x, 0), default=0x1eba290,
                    help="已知 os_singleton_rva，跳过慢速扫描")
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
    rva = args.rva
    if not rva:
        rva, _ = discover_os_singleton_rva(r, GODOT_OFFSETS, diag=True)
    os_obj = ru64(r, base + rva)
    root = ru64(r, ru64(r, os_obj + ML_OFF) + ROOT_OFF)
    print(f"[*] root={hex(root)}  root.name={node_name(r, root)}")

    print("[*] root 直接子节点:")
    for i, c in enumerate(children(r, root)):
        print(f"      [{i}] {hex(c)} name={node_name(r, c)!r} script={node_script(r, c)}")
    print()

    # BFS 找 Game
    dq = deque([(root, 0, "root")])
    seen = {root}
    found = []
    visited = 0
    while dq:
        node, depth, path = dq.popleft()
        visited += 1
        nm = node_name(r, node)
        sc = node_script(r, node)
        p2 = f"{path}/{nm}" if nm else f"{path}/?"
        if (nm == "Game") or (sc and "Core/Game.gd" in sc):
            found.append((node, p2, nm, sc))
        if depth < args.max_depth:
            for c in children(r, node):
                if c not in seen:
                    seen.add(c)
                    dq.append((c, depth + 1, p2))
    print(f"[*] BFS 访问 {visited} 个节点")
    if found:
        for node, path, nm, sc in found:
            print(f"[+] 找到 Game: node={hex(node)} name={nm!r} script={sc}")
            print(f"      树路径: {path}")
    else:
        print("[-] 未在深度内找到 Game 节点")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
