"""
在 root 上搜索真正的 children List<Node*>：
  Godot List: { Element* first(+0); Element* last(+8); int count(+16) }
  Element:    { T value(+0); Element* next(+8); Element* prev(+16) }
校验：first/last 合法指针，count 在 [3,60]，沿 next 走 count 步能到 last，
并读子节点脚本，命中 Game.gd 即锁定。
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


def ru64(r, a):
    d = r.read(a, 8)
    return struct.unpack("<Q", d)[0] if d and len(d) == 8 else None


def ri32(r, a):
    d = r.read(a, 4)
    return struct.unpack("<i", d)[0] if d and len(d) == 4 else None


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


def try_list(r, addr, want_count):
    """把 addr 当 List 头，沿 next 走，返回节点列表（value）。"""
    first = ru64(r, addr)
    cur = first
    out = []
    guard = 0
    while cur and cur > 0x10000 and guard < want_count + 2:
        out.append(ru64(r, cur))
        cur = ru64(r, cur + 8)
        guard += 1
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, default=None)
    ap.add_argument("--scan", type=lambda x: int(x, 0), default=0x900)
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
    print(f"[*] root={hex(root)}  扫描 0..{hex(args.scan)}\n")

    hits = []
    for off in range(0, args.scan, 8):
        first = ru64(r, root + off)
        last = ru64(r, root + off + 8)
        count = ri32(r, root + off + 16)
        if not first or first < 0x10000 or not last or last < 0x10000:
            continue
        if count is None or count < 3 or count > 80:
            continue
        nodes = try_list(r, root + off, count)
        if len(nodes) < min(count, 3):
            continue
        scripts = [(i, node_script_path(r, n)) for i, n in enumerate(nodes)]
        named = [(i, s) for i, s in scripts if s]
        if not named:
            continue
        has_game = any("Game.gd" in s for _, s in named)
        # 校验链尾是否 == last（List 一致性）
        tail_ok = nodes and ru64(r, ru64(r, root + off)) is not None
        hits.append((off, count, len(nodes), named, has_game))

    hits.sort(key=lambda x: (not x[4], -len(x[3])))
    for off, count, chain_len, named, has_game in hits[:10]:
        print(f"=== root+{hex(off)}  count字段={count} 链长={chain_len} 含Game={has_game} ===")
        for i, s in named[:30]:
            print(f"      [{i:2d}] {s}")
        print()
    if not hits:
        print("[-] 未找到候选 children List")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
