# -*- coding: utf-8 -*-
"""活体扫描：从场景树中找出所有物品节点（脚本 res://Items/*.gd）及其父链位置。"""
import sys, os, argparse
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import yaml
from core.memory_reader import MemoryReader
from core.godot_reader import GodotReader, GODOT_OFFSETS

CFG = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "config.yaml")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, required=True)
    ap.add_argument("--max-depth", type=int, default=10)
    ap.add_argument("--show-all", action="store_true", help="同时打印 Inventory/Storage 容器节点")
    args = ap.parse_args()

    r = MemoryReader(args.pid)
    offs = dict(GODOT_OFFSETS)
    try:
        cfg = yaml.safe_load(open(CFG, encoding="utf-8"))
        offs.update(cfg.get("godot", {}))
    except Exception as e:
        print(f"WARN: config.yaml 读取失败 {e}")
    gr = GodotReader(r, offs)
    root = gr.get_root()
    if not root:
        print("ERROR: root 不可达"); return 1
    print(f"root = {hex(root)} name={gr.node_name(root)}")

    # BFS 全树
    items = []      # (path, addr, script)
    containers = [] # (path, addr, script, n_children)
    stack = [(root, "root", 0)]
    seen = set()
    while stack:
        node, path, depth = stack.pop()
        if node in seen or depth > args.max_depth:
            continue
        seen.add(node)
        sp = gr.node_script_path(node) or ""
        nm = gr.node_name(node) or "?"
        if sp.startswith("res://Items/"):
            items.append((path + "/" + nm, node, sp))
        low = (nm or "").lower()
        if ("inventory" in low or "storage" in low or "stash" in low
                or sp.endswith("Inventory.gd")):
            kids = gr.get_children(node)
            containers.append((path + "/" + nm, node, sp, len(kids)))
        for c in gr.get_children(node):
            stack.append((c, path + "/" + nm, depth + 1))

    print(f"\n== 容器节点 ({len(containers)}) ==")
    for p, a, s, n in containers:
        print(f"  {p}  script={s}  children={n}  @{hex(a)}")

    print(f"\n== 物品节点 ({len(items)}) ==")
    for p, a, s in items:
        print(f"  {p}  @{hex(a)}  {s}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
