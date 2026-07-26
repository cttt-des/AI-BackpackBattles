"""
枚举 root.children(0x6c0) 子节点，用 Godot 3.6 StringName 布局解码每个节点的名字：
  node 内某 qword Q 是 StringName::_Data*；
  StringName::_Data: refcount(8)+prev(8)+next(8)+hash(4)+cached(4)+String name(+0x20)
  String name 是 String::_Data*；String::_Data: refcount(8)+length(4)+hash(4)+char32_t* str(+0x10)
  读 str 处的 UTF-32 得到名字。

找到名字为 Game 的节点即定位 Game 自动加载单例。

用法：
  python tools/name_enum.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def decode_name(reader, node):
    nmem = reader.read(node, 0x200) or b""
    cands = []
    for i in range(0, len(nmem) - 8, 8):
        q = int.from_bytes(nmem[i:i + 8], "little")
        if not _is_plausible_ptr(q):
            continue
        # 试几个 StringName::_Data -> String::_Data -> str 偏移组合
        for name_off in (0x20, 0x18, 0x28, 0x10):
            for str_off in (0x10, 0x8, 0x18):
                sdata = _read_u64(reader, q + name_off)
                if not _is_plausible_ptr(sdata):
                    continue
                strp = _read_u64(reader, sdata + str_off)
                if not _is_plausible_ptr(strp):
                    continue
                raw = reader.read(strp, 128)
                if not raw:
                    continue
                # UTF-32 解码
                try:
                    units = [int.from_bytes(raw[k:k + 4], "little") for k in range(0, 128, 4)]
                except Exception:
                    continue
                chars = []
                ok = True
                for u in units:
                    if u == 0:
                        break
                    if 32 <= u < 127:
                        chars.append(chr(u))
                    elif u >= 0x80:
                        # 非 ASCII，跳过（autoload 名通常为 ASCII）
                        ok = False
                        break
                    else:
                        ok = False
                        break
                if ok and 1 <= len(chars) <= 40:
                    name = "".join(chars)
                    cands.append((name_off, str_off, name))
    # 取出现最多的名字
    if not cands:
        return None
    from collections import Counter
    cnt = Counter(n for _, _, n in cands)
    return cnt.most_common(1)[0][0]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, required=True)
    args = ap.parse_args()

    reader = MemoryReader(args.pid)
    base = reader.module_base
    secs = read_module_sections(reader)
    text = next(s for s in secs if s[0] == ".text")
    rdata = next(s for s in secs if s[0] == ".rdata")
    data = next(s for s in secs if s[0] == ".data")
    text_lo, text_hi = base + text[1], base + text[1] + text[2]
    rdata_lo, rdata_hi = base + rdata[1], base + rdata[1] + rdata[2]

    _cache = {}
    def is_inst(a):
        if a in _cache:
            return _cache[a]
        r = _is_valid_instance(reader, a, text_lo, text_hi, rdata_lo, rdata_hi)
        _cache[a] = r
        return r

    instances = []
    addr = base + data[1]; end = addr + data[2]
    while addr < end:
        buf = reader.read(addr, min(1024 * 1024, end - addr))
        if not buf:
            break
        off = 0
        while off + 8 <= len(buf):
            obj = int.from_bytes(buf[off:off + 8], "little")
            if _is_plausible_ptr(obj) and is_inst(obj):
                instances.append(obj)
            off += 8
        addr += len(buf)

    chain = None
    for obj in instances:
        s = _read_u64(reader, obj + 0x1d0)
        if not _is_plausible_ptr(s) or not is_inst(s) or s == obj:
            continue
        r = _read_u64(reader, s + 0x230)
        if _is_plausible_ptr(r) and is_inst(r) and r != s:
            chain = (obj, s, r)
            break
    if not chain:
        print("[-] 链路未找到"); return 1
    obj, s, r = chain
    print(f"[*] root={hex(r)}")

    first = _read_u64(reader, r + 0x6c0)
    cur = first
    seen = set()
    for ci in range(40):
        if not _is_plausible_ptr(cur) or cur in seen:
            break
        seen.add(cur)
        val = _read_u64(reader, cur)
        if _is_plausible_ptr(val) and is_inst(val):
            name = decode_name(reader, val)
            mark = "  <== Game?" if name == "Game" else ""
            print(f"  [{ci:2d}] {hex(val)}  name={name!r}{mark}")
        nxt = _read_u64(reader, cur + 8)
        cur = nxt
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
