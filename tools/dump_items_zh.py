# -*- coding: utf-8 -*-
"""dump_items_zh.py — 从 Items.zh_Hans_CN.translation 的 bucket elem 精确提取物品名。

PHashTranslation 布局（本游戏 exe 标定）：
  [0:301]   RSRC 头
  [301..]   hash_table（larger_prime 个 uint32）
  bucket 区：每桶 <i32 size><u32 func> + size×<u32 key><u32 off><u32 cs><u32 us>
  strings 区：明文 UTF-8，NUL 分隔（zh 表未压缩）
Godot 查询：key = hash(func, msgid)。en 表的 key 与 zh 表的 key 对同一 msgid
相同 —— 因此 key 精确配对。en 表是 smaz 压缩（cs != us），zh 表明文（cs == us）。

用法: python tools/dump_items_zh.py
输出: assets/items_zh_exact.json {英文物品名: 中文名}
"""
import json
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, "C:/tmp/bb_tr")
from smaz_dict import smaz_decompress

TR = "C:/tmp/bb_tr/Sheets/CSV"
HT_OFF, HT_SIZE = 301, 397


def parse_buckets(path, ht_off=HT_OFF, ht_size=HT_SIZE):
    """返回 (elems, strings_start)。elems = [(key, off, cs, us)]"""
    d = open(path, "rb").read()
    o = ht_off + ht_size * 4
    elems = []
    while o + 8 <= len(d):
        size = struct.unpack("<i", d[o:o + 4])[0]
        func = struct.unpack("<I", d[o + 4:o + 8])[0]
        if not (0 <= size <= 2000) or func > 5000:
            break
        o += 8
        for _ in range(size):
            if o + 16 > len(d):
                break
            key, soff, cs, us = struct.unpack("<IIII", d[o:o + 16])
            elems.append((key, soff, cs, us))
            o += 16
    return elems, o


def read_string(d, S, off, cs, us):
    raw = d[S + off:S + off + cs]
    if cs == us:
        # 明文（zh 表）
        return raw.decode("utf-8", errors="replace").rstrip("\x00")
    try:
        return smaz_decompress(raw).decode("utf-8")
    except Exception:
        return None


def try_layout(d, ht_off, ht_size):
    """尝试给定布局，返回 (elems, strings_start) 或 (None, None)"""
    o = ht_off + ht_size * 4
    if o >= len(d):
        return None, None
    elems = []
    while o + 8 <= len(d):
        size = struct.unpack("<i", d[o:o + 4])[0]
        func = struct.unpack("<I", d[o + 4:o + 8])[0]
        if not (0 <= size <= 2000) or func > 5000:
            break
        o += 8
        for _ in range(size):
            if o + 16 > len(d):
                return None, None
            key, soff, cs, us = struct.unpack("<IIII", d[o:o + 16])
            # off+cs 必须落在文件内（相对 strings 起点，strings 起点未知，
            # 用 off+cs <= len(d) 粗筛）
            if soff + cs > len(d):
                return None, None
            elems.append((key, soff, cs, us))
            o += 16
    return elems, o


def find_zh_ht_off(path):
    """zh 表比 en 表多一个 locale 属性（"zh_Hans_CN" 16 字节）——hash_table 起点
    通过在 zh 表中定位 en 表 hash_table 起点开始的 200 字节窗口得到。"""
    en = open(f"{TR}/Items.en.translation", "rb").read()
    zh = open(path, "rb").read()
    probe = en[HT_OFF:HT_OFF + 200]
    idx = zh.find(probe)
    return idx if idx > 0 else HT_OFF + 16


def main():
    en_d = open(f"{TR}/Items.en.translation", "rb").read()
    zh_d = open(f"{TR}/Items.zh_Hans_CN.translation", "rb").read()
    zh_ht_off = find_zh_ht_off(f"{TR}/Items.zh_Hans_CN.translation")
    print(f"zh hash_table @ {zh_ht_off}（en @ {HT_OFF}）")

    en_elems, en_S = parse_buckets(f"{TR}/Items.en.translation")
    zh_elems, zh_S = parse_buckets(f"{TR}/Items.zh_Hans_CN.translation",
                                   ht_off=zh_ht_off)

    en = {}
    for key, off, cs, us in en_elems:
        s = read_string(en_d, en_S, off, cs, us)
        if s:
            en[key] = s
    zh = {}
    for key, off, cs, us in zh_elems:
        s = read_string(zh_d, zh_S, off, cs, us)
        if s:
            zh[key] = s
    print(f"en={len(en)} zh={len(zh)}")

    pairs = {}
    for key, e in en.items():
        z = zh.get(key)
        if z:
            pairs[e] = z
    print(f"精确配对（同 hash key）: {len(pairs)}")
    out = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                       "assets", "items_zh_exact.json")
    json.dump(pairs, open(out, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    print("写出", out)
    # 抽查
    for probe in ("Wooden Sword", "Busted Blade", "Battery", "Goobert", "Sun Armor"):
        if probe in pairs:
            print(f"  {probe} -> {pairs[probe]}")
        else:
            print(f"  {probe} -> <无>")


if __name__ == "__main__":
    main()
