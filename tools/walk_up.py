"""
从 SceneTree+0x230 指向的节点沿 parent(+0x8) 向上走，找到真正的 root 视口，
并在每一层枚举其 0x6c0 子节点链，打印脚本路径，定位 Game 自动载入单例。
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

SI_OFF = 0x58
SCRIPT_OFF = 0x10
ML_OFF = 0x1D0
ROOT_OFF = 0x230
PARENT_OFF = 0x8
CHILDREN_OFF = 0x6C0


def ru64(r, a):
    d = r.read(a, 8)
    return struct.unpack("<Q", d)[0] if d and len(d) == 8 else None


def node_script_path(r, node):
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


def enum_children(r, node, limit=60):
    out = []
    first = ru64(r, node + CHILDREN_OFF)
    cur = first
    guard = 0
    while cur and cur > 0x10000 and guard < limit:
        val = ru64(r, cur)
        out.append(val)
        cur = ru64(r, cur + 8)
        guard += 1
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, default=None)
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
    scene_tree = ru64(r, os_obj + ML_OFF)
    start = ru64(r, scene_tree + ROOT_OFF)
    print(f"[*] base={hex(base)} SceneTree={hex(scene_tree)} start(0x230节点)={hex(start)}")

    # 向上走 parent
    chain = []
    node = start
    seen = set()
    while node and node > 0x10000 and node not in seen:
        seen.add(node)
        parent = ru64(r, node + PARENT_OFF)
        chain.append((node, parent))
        node = parent
    print(f"[*] parent 链（自下而上）:")
    for i, (n, p) in enumerate(chain):
        print(f"      [{i}] node={hex(n)} parent={hex(p) if p else '0(null=root)'}")
    true_root = chain[-1][0]
    print(f"[*] 推定 true_root = {hex(true_root)}\n")

    # 在 true_root 与其下一层枚举子节点脚本
    for label, target in (("true_root", true_root), ("start(0x230)", start)):
        kids = enum_children(r, target, limit=80)
        print(f"=== {label} = {hex(target)} 的 0x6c0 子节点（{len(kids)}）===")
        for i, k in enumerate(kids):
            if not k or k < 0x10000:
                continue
            sp = node_script_path(r, k)
            if sp:
                print(f"      [{i:2d}] node={hex(k)} {sp}")
        print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
