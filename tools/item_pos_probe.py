# -*- coding: utf-8 -*-
"""探测物品节点的位置信息：
1) dump GDScript 成员中的 Vector2/int/real（找网格坐标成员）
2) 扫描 Node2D 原生字段里的 float 对（找 pos 偏移）
"""
import sys, os, argparse, struct
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import yaml
from core.memory_reader import MemoryReader
from core.godot_reader import GodotReader, GODOT_OFFSETS

CFG = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "config.yaml")


def load_reader(pid):
    r = MemoryReader(pid)
    offs = dict(GODOT_OFFSETS)
    try:
        cfg = yaml.safe_load(open(CFG, encoding="utf-8"))
        offs.update(cfg.get("godot", {}))
    except Exception:
        pass
    return r, GodotReader(r, offs), offs


def find_node(gr, root, name):
    stack = [(root, 0)]
    seen = set()
    while stack:
        n, d = stack.pop()
        if n in seen or d > 12:
            continue
        seen.add(n)
        if gr.node_name(n) == name:
            return n
        for c in gr.get_children(n):
            stack.append((c, d + 1))
    return None


def dump_members_typed(r, gr, offs, node):
    si = gr._ptr(node + offs["object_script_instance_off"])
    if not si:
        print("  (无 script_instance)")
        return
    vec = gr._ptr(si + offs["gdscript_members_off"])
    if not vec:
        print("  (members 空)")
        return
    cnt = gr._cow_count(vec)
    if not cnt or cnt > 2000:
        print(f"  (members 计数异常: {cnt})")
        return
    VS = offs["variant_size"]
    print(f"  members = {cnt}")
    for i in range(cnt):
        d = r.read(vec + i * VS, VS)
        if not d:
            continue
        t = struct.unpack_from("<I", d, 0)[0]
        if t == 1:
            print(f"    [{i:3d}] bool = {struct.unpack_from('<I', d, 8)[0]}")
        elif t == 2:
            print(f"    [{i:3d}] int  = {struct.unpack_from('<q', d, 8)[0]}")
        elif t == 3:
            print(f"    [{i:3d}] real = {struct.unpack_from('<d', d, 8)[0]:.3f}")
        elif t == 5:
            x, y = struct.unpack_from("<2f", d, 8)
            print(f"    [{i:3d}] vec2 = ({x:.1f}, {y:.1f})")
        elif t == 4:
            # String: 指针在 +8 -> CowData<wchar>
            sptr = struct.unpack_from("<Q", d, 8)[0]
            s = gr._read_godot_string(sptr) if sptr else None
            if s:
                print(f"    [{i:3d}] str  = {s[:40]!r}")


def scan_float_pairs(r, node, lo=0x100, hi=0x800):
    """扫描节点内存里成对的合理 float（坐标形态）。"""
    d = r.read(node + lo, hi - lo)
    if not d:
        print("  (读取失败)")
        return
    for off in range(0, len(d) - 8, 4):
        x, y = struct.unpack_from("<2f", d, off)
        def ok(v):
            return v == v and abs(v) < 20000 and (v == 0 or 1e-2 < abs(v))
        # 坐标形态：至少一个分量非零，且都是"像素级"数值
        if ok(x) and ok(y) and (abs(x) >= 4 or abs(y) >= 4):
            print(f"    +{lo+off:#x}: ({x:.1f}, {y:.1f})")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, required=True)
    ap.add_argument("--names", nargs="+", required=True)
    ap.add_argument("--members", action="store_true")
    ap.add_argument("--floats", action="store_true")
    args = ap.parse_args()

    r, gr, offs = load_reader(args.pid)
    root = gr.get_root()
    if not root:
        print("ERROR: root 不可达"); return 1
    for nm in args.names:
        node = find_node(gr, root, nm)
        print(f"\n== {nm} @ {hex(node) if node else 'NOT FOUND'} ==")
        if not node:
            continue
        if args.members:
            dump_members_typed(r, gr, offs, node)
        if args.floats:
            scan_float_pairs(r, node)
    return 0


if __name__ == "__main__":
    sys.exit(main())
