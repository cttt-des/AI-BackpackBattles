"""
在 root 上搜索 children 作为 Vector<Node*>(CowData) 的偏移。
CowData: 字段保存 _ptr；count = *(uint32)(_ptr-4)；元素是连续的 Node* 数组。
命中判据：解析出的若干 Node* 的脚本路径里含 autoload（Game.gd 等）。
同时也对 SceneTree 对象本身扫描（autoload 也可能挂在别处）。
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
HINTS = ("Game.gd", "Util.gd", "Settings.gd", "RunDatabase.gd", "ItemBook.gd",
         "EventBus.gd", "ObjectPool.gd", "SkinBook.gd")


def ru64(r, a):
    d = r.read(a, 8)
    return struct.unpack("<Q", d)[0] if d and len(d) == 8 else None


def ru32(r, a):
    d = r.read(a, 4)
    return struct.unpack("<I", d)[0] if d and len(d) == 4 else None


def node_script_path(r, node):
    if not node or node < 0x10000:
        return None
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


def scan_vector(r, obj, label, scan=0x1000):
    hits = []
    for off in range(0, scan, 8):
        ptr = ru64(r, obj + off)
        if not ptr or ptr < 0x10000:
            continue
        cnt = ru32(r, ptr - 4)
        if cnt is None or cnt < 4 or cnt > 200:
            continue
        # 读取前 cnt 个 Node*，解析脚本
        named = []
        valid = 0
        for i in range(min(cnt, 60)):
            n = ru64(r, ptr + i * 8)
            if n and n > 0x10000:
                valid += 1
                sp = node_script_path(r, n)
                if sp:
                    named.append((i, n, sp))
        if valid < min(cnt, 4) * 0.6:
            continue
        if not named:
            continue
        has_hint = any(any(h in s for _, _, s in named for h in [hh]) for hh in HINTS)
        hits.append((off, cnt, named, has_hint))
    hits.sort(key=lambda x: (not x[3], -len(x[2])))
    print(f"====== 扫描 {label}={hex(obj)} ======")
    for off, cnt, named, has_hint in hits[:6]:
        print(f"  {label}+{hex(off)} count={cnt} 命中autoload={has_hint} 解析脚本数={len(named)}")
        for i, n, s in named[:30]:
            print(f"        [{i:2d}] {hex(n)} {s}")
        print()
    if not hits:
        print("  (无候选)")
    print()
    return hits


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
    root = ru64(r, scene_tree + ROOT_OFF)
    print(f"[*] base={hex(base)} SceneTree={hex(scene_tree)} root={hex(root)}\n")

    scan_vector(r, root, "root", scan=0x1000)
    scan_vector(r, scene_tree, "SceneTree", scan=0x400)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
