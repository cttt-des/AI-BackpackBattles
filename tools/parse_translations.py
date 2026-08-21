# -*- coding: utf-8 -*-
"""parse_translations.py — 精确解析 Godot PHashTranslation (.translation) 物品中英文名。

原理：
- .translation = RSRC 资源，属性序列化含 hash_table(质数大小 uint32 数组) +
  bucket_table(完美哈希桶) + strings(smaz 压缩流)。
- 每个 bucket elem = (key=hash(func,str), off, comp_size, uncomp_size)。
- en 与 zh_Hans_CN 对同一源字符串 hash 相同 → 用 key 精确配对（替代旧的比例线性映射）。
- 布局参数（本游戏 exe 版本标定）：hash_table 起点 309、大小 397（Items 表）。

用法: python tools/parse_translations.py [sheet]
输出: assets/zh_translation.json {英文物品名: 中文名}
"""
import json, os, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
sys.path.insert(0, "C:/tmp/bb_tr")
from smaz_dict import smaz_decompress

TR_DIR = "C:/tmp/bb_tr/Sheets/CSV"
HT_OFF = 309      # hash_table 起点（标定）
HT_SIZE = 397     # hash_table 大小（larger_prime，标定）


def parse(path):
    d = open(path, "rb").read()
    elems = []
    o = HT_OFF + HT_SIZE * 4   # bucket_table 起点
    while o + 8 <= len(d):
        size = struct.unpack('<i', d[o:o+4])[0]
        func = struct.unpack('<I', d[o+4:o+8])[0]
        if not (0 <= size <= 2000) or func > 5000:
            break
        o += 8
        for _ in range(size):
            if o + 16 > len(d):
                break
            key, soff, cs, us = struct.unpack('<IIII', d[o:o+16])
            elems.append((key, soff, cs, us))
            o += 16
    S = o   # strings 块起点
    out = {}
    for key, soff, cs, us in elems:
        try:
            s = smaz_decompress(d[S+soff:S+soff+cs]).decode('utf-8')
        except Exception:
            s = None
        out[key] = s
    return out


def main(sheet="Items"):
    en = parse(os.path.join(TR_DIR, f"{sheet}.en.translation"))
    zh = parse(os.path.join(TR_DIR, f"{sheet}.zh_Hans_CN.translation"))
    print(f"{sheet}: en={len(en)} zh={len(zh)}")
    pairs = {}
    for key, e in en.items():
        if not e:
            continue
        z = zh.get(key)
        if z:
            pairs[e] = z
    print("matched pairs:", len(pairs))
    return pairs


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "Items")
