"""
在 root 视口对象上暴力搜索「真正的直接子节点 List 偏移」。

自动载入(autoloads)是 root 视口的直接子节点，按 project 顺序添加：
  ControllerIcons, Util, SteamHelper, Settings, InputMapping, SilentWolf,
  ItemBook, SkinBook, Game, ObjectPool, RunDatabase, Sound, CrazySDK,
  CraftingManager, MaterialCompiler, EventBus, CustomRules, InputBlocker
之后才是 current_scene。

策略：对 root 的每个 8 字节偏移 O，把 *(root+O) 当作 List.first，
沿 Element.next(+8) 走链，读每个 Element.value(节点) 的脚本路径；
若能连续读出多个 res://...gd 且其中含 Game.gd/Util.gd/Settings.gd，即命中。
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
from tools.script_paths import read_godot_string  # 复用字符串解码

SI_OFF = 0x58
SCRIPT_OFF = 0x10
ML_OFF = 0x1D0
ROOT_OFF = 0x230


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
        if s and (s.startswith("res://") and s.endswith(".gd")):
            return s
    return None


def walk_list(r, first, max_nodes=40):
    """把 first 当作 List.first，返回 [(node, script_path)]。"""
    out = []
    cur = first
    guard = 0
    while cur and cur > 0x10000 and guard < max_nodes:
        node = ru64(r, cur)  # Element.value
        if node and node > 0x10000:
            sp = node_script_path(r, node)
            out.append((node, sp))
        else:
            out.append((node, None))
        cur = ru64(r, cur + 8)  # Element.next
        guard += 1
    return out


TARGET_HINTS = ("Game.gd", "Util.gd", "Settings.gd", "RunDatabase.gd", "ItemBook.gd")


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
    print(f"[*] base={hex(base)} rva={hex(rva)} SceneTree={hex(scene_tree)} root={hex(root)}\n")

    best = []
    for off in range(0, 0x800, 8):
        first = ru64(r, root + off)
        if not first or first < 0x10000:
            continue
        nodes = walk_list(r, first, max_nodes=40)
        if len(nodes) < 3:
            continue
        scripts = [sp for _, sp in nodes if sp]
        if not scripts:
            continue
        hint_hit = any(any(h in sp for h in TARGET_HINTS) for sp in scripts)
        if hint_hit or len(scripts) >= 5:
            best.append((off, len(nodes), scripts, hint_hit))

    # 优先展示命中 autoload 提示的
    best.sort(key=lambda x: (not x[3], -len(x[2])))
    for off, n, scripts, hint in best[:8]:
        print(f"=== root+{hex(off)}  链长={n}  含autoload提示={hint} ===")
        for sp in scripts[:25]:
            print(f"      {sp}")
        print()
    if not best:
        print("[-] 未找到含脚本节点的子节点 List 偏移")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
