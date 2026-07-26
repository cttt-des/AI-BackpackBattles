"""
校准 StringName 解码：对给定节点，暴力尝试 (StringName::_Data 偏移, String::str 偏移)
组合，并用 UTF-8 / UTF-32 两种解码，打印所有可读串。目标是找到 root 节点的名字
（应含 "root"），从而确定正确的偏移布局；随后可用于在 children 中找 "Game"。

用法：
  python tools/name_calib2.py --pid 18616 --node <root_addr>
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def read_str(reader, strp, utf32):
    raw = reader.read(strp, 256)
    if not raw:
        return None
    chars = []
    if utf32:
        for i in range(0, 256, 4):
            u = int.from_bytes(raw[i:i + 4], "little")
            if u == 0:
                break
            if 32 <= u < 127:
                chars.append(chr(u))
            else:
                return None
    else:
        for i in range(0, 256):
            c = raw[i]
            if c == 0:
                break
            if 32 <= c < 127:
                chars.append(chr(c))
            else:
                return None
    s = "".join(chars)
    return s if 1 <= len(s) <= 40 else None


def decode_all(reader, node):
    nmem = reader.read(node, 0x400) or b""
    found = []
    for i in range(0, len(nmem) - 8, 8):
        q = int.from_bytes(nmem[i:i + 8], "little")
        if not _is_plausible_ptr(q):
            continue
        for name_off in (0x18, 0x20, 0x28, 0x30, 0x10, 0x38):
            sdata = _read_u64(reader, q + name_off)
            if not _is_plausible_ptr(sdata):
                continue
            for str_off in (0x8, 0x10, 0x18, 0x20, 0x28, 0x0, 0x30):
                for utf32 in (True, False):
                    strp = _read_u64(reader, sdata + str_off)
                    if not _is_plausible_ptr(strp):
                        continue
                    s = read_str(reader, strp, utf32)
                    if s:
                        found.append((i, name_off, str_off, "u32" if utf32 else "u8", s))
    return found


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, required=True)
    ap.add_argument("--node", type=lambda x: int(x, 16), required=True)
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

    found = decode_all(reader, args.node)
    print(f"[*] node={hex(args.node)} 候选名字数={len(found)}")
    # 去重
    seen = set()
    for i, no, so, enc, s in found:
        key = (no, so, enc, s)
        if key in seen:
            continue
        seen.add(key)
        print(f"    q_off={hex(i)} name_off={hex(no)} str_off={hex(so)} {enc} name={s!r}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
