"""
读取每个根子节点所挂 GDScript 的资源路径（res://...），据此精确识别 Game 单例。

GDScriptInstance 布局（Godot 3.x x64）：
  +0x00 vtable
  +0x08 owner (Object*)
  +0x10 Ref<GDScript> script  (单指针)
  +0x20 Vector<Variant> members (CowData)

GDScript 继承 Script->Resource；Resource 里有 `String path_cache`（资源路径）。
Godot 3.x String = CowData<CharType>，CharType 在 Windows 上是 wchar_t(2字节/UTF-16)。
本工具在 script 对象前若干字节内扫描「指向可读字符串的指针」，
分别按 UTF-16 / UTF-32 解码，命中 res:// 即打印。
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

SI_OFF = 0x58
CHILDREN_OFF = 0x6C0
ML_OFF = 0x1D0
ROOT_OFF = 0x230
SCRIPT_OFF = 0x10


def ru64(r, a):
    d = r.read(a, 8)
    return struct.unpack("<Q", d)[0] if d and len(d) == 8 else None


def ru32(r, a):
    d = r.read(a, 4)
    return struct.unpack("<I", d)[0] if d and len(d) == 4 else None


def read_godot_string(r, ptr):
    """ptr 是 String 字段里保存的 CowData._ptr。size 在 ptr-4（字符数）。尝试 UTF-16 与 UTF-32。"""
    if not ptr or ptr < 0x10000:
        return None
    n = ru32(r, ptr - 4)
    if n is None or n <= 0 or n > 512:
        return None
    # UTF-16 (Windows wchar_t)
    for width, enc in ((2, "utf-16-le"), (4, "utf-32-le")):
        raw = r.read(ptr, n * width)
        if not raw or len(raw) < n * width:
            continue
        try:
            s = raw.decode(enc)
        except Exception:
            continue
        # 去掉可能的结尾 NUL
        s = s.split("\x00", 1)[0]
        if s and all(0x20 <= ord(c) < 0x7f or ord(c) > 0xff for c in s):
            return s
    return None


def find_script_path(r, script_obj):
    """在 script 对象前 0x160 字节里找指向字符串的指针，返回首个像资源路径的字符串。"""
    if not script_obj or script_obj < 0x10000:
        return None, []
    found = []
    for off in range(0, 0x200, 8):
        p = ru64(r, script_obj + off)
        if not p or p < 0x10000:
            continue
        s = read_godot_string(r, p)
        if s and (s.startswith("res://") or s.endswith(".gd") or ("/" in s and len(s) > 4)):
            found.append((off, s))
    path = next((s for _, s in found if s.startswith("res://") or s.endswith(".gd")), None)
    return path, found


def enum_children(r, root, limit=None):
    out = []
    elem = ru64(r, root + CHILDREN_OFF)
    guard = 0
    while elem and elem > 0x10000 and guard < 5000:
        val = ru64(r, elem)
        if val and val > 0x10000:
            out.append(val)
            if limit and len(out) >= limit:
                break
        elem = ru64(r, elem + 8)
        guard += 1
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, default=None)
    ap.add_argument("--limit", type=int, default=40, help="只看前 N 个子节点")
    ap.add_argument("--all", action="store_true", help="扫描全部子节点")
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
    limit = None if args.all else args.limit
    children = enum_children(r, root, limit)
    print(f"[*] base={hex(base)} rva={hex(rva)} root={hex(root)} 扫描子节点={len(children)}\n")

    for ci, node in enumerate(children):
        si = ru64(r, node + SI_OFF)
        if not si or si < 0x10000:
            continue
        script = ru64(r, si + SCRIPT_OFF)
        path, found = find_script_path(r, script)
        if path:
            print(f"child[{ci:3d}] node={hex(node)} script={hex(script)}  PATH = {path}")
        elif found:
            print(f"child[{ci:3d}] node={hex(node)} script={hex(script)}  strings={found[:3]}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
