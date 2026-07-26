# -*- coding: utf-8 -*-
"""验证物品位置假设：+0x270=局部pos, +0x260=全局origin；背包物品应对齐80px网格。"""
import sys, os, struct, argparse
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import yaml
from core.memory_reader import MemoryReader
from core.godot_reader import GodotReader, GODOT_OFFSETS

CFG = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "config.yaml")
POS_LOCAL = 0x270
POS_GLOBAL = 0x260


def read_vec2(r, addr):
    d = r.read(addr, 8)
    if not d:
        return None
    return struct.unpack("<2f", d)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, required=True)
    args = ap.parse_args()

    r = MemoryReader(args.pid)
    offs = dict(GODOT_OFFSETS)
    cfg = yaml.safe_load(open(CFG, encoding="utf-8"))
    offs.update(cfg.get("godot", {}))
    gr = GodotReader(r, offs)
    root = gr.get_root()

    # 收集：路径 -> 节点
    results = []  # (fullpath, node)
    stack = [(root, "", 0)]
    seen = set()
    while stack:
        n, path, d = stack.pop()
        if n in seen or d > 12:
            continue
        seen.add(n)
        nm = gr.node_name(n) or "?"
        full = path + "/" + nm
        sp = gr.node_script_path(n) or ""
        interesting = (sp.startswith("res://Items/") and "/Icon/" not in full
                       and not sp.endswith(("SocketsNode.gd", "GemSocket.gd", "BagBorder.gd",
                                            "GooglyEye.gd", "ItemPushZone.gd")))
        if interesting or nm in ("Inventory", "Storagebox", "Player", "Shop", "Items"):
            results.append((full, n))
        for c in gr.get_children(n):
            stack.append((c, full, d + 1))

    for full, n in sorted(results):
        lp = read_vec2(r, n + POS_LOCAL)
        gp = read_vec2(r, n + POS_GLOBAL)
        lps = f"local=({lp[0]:8.1f},{lp[1]:8.1f})" if lp else "local=?"
        gps = f"global=({gp[0]:8.1f},{gp[1]:8.1f})" if gp else "global=?"
        print(f"{full:60s} {lps}  {gps}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
