# -*- coding: utf-8 -*-
"""rsrc_translation_parse.py — Godot 3.6 PHashTranslation(.translation) RSRC 解析

解析 ResourceFormatLoaderBinary v3.6：
  头(RSRC/be/r64/ver/format/type/metadata_u64) → flags+string 表 → 属性流
  （属性 = string 表索引 u32 + Variant tag u32 + 值）。
PHashTranslation 属性：hash_table/bucket_table/strings/offsets(均 PoolIntArray)、
locale(String)。strings 是 PHashTranslation 自定义压缩流（Godot
PHashTranslation::get_string：首字节 = 与前一串的共享前缀长度，其后为后缀字节）。

用法：
  from rsrc_translation_parse import parse_phash
  strings, buckets = parse_phash(path)   # buckets: [(hash, str_idx, val_idx)]
  key_by_idx / val_by_idx 用 decode_strings 恢复明文
"""
import struct


def _read_pad4(d, o):
    return (o + 3) & ~3


def parse_rsrc_properties(d: bytes):
    """返回 (string_table, props{name: value})，value 按 tag 解码"""
    assert d[:4] == b'RSRC', 'not RSRC'
    be, r64, vmaj, vmin, fmt = struct.unpack('<5I', d[4:24])
    if be:
        raise NotImplementedError('big-endian RSRC')
    o = 24
    tlen, = struct.unpack('<I', d[o:o + 4]); o += 4
    o = _read_pad4(d, o + tlen)              # 类型名
    o += 8                                   # metadata offset (u64)
    str_table = []
    if fmt >= 4 or True:                     # 3.6 也写 flag+table（实测）
        flags, = struct.unpack('<I', d[o:o + 4]); o += 4
        if flags & 0x8000 or flags in (0x800, 0x4000, 0x8000):
            # flags 后跟 count；此处 3.6: u32 flags(0x800=string table) + u32 count
            pass
        count, = struct.unpack('<I', d[o:o + 4]); o += 4
        if count < 4096:
            for _ in range(count):
                ln, = struct.unpack('<I', d[o:o + 4]); o += 4
                s = d[o:o + ln].decode('utf-8', 'replace'); o = _read_pad4(d, o + ln)
                str_table.append(s)
        else:
            str_table = []
            o -= 4
    props = {}
    while o + 4 <= len(d):
        name_idx, = struct.unpack('<I', d[o:o + 4]); o += 4
        if name_idx == 0 and d[o:o + 4] == b'\0\0\0\0':
            break
        tag, = struct.unpack('<I', d[o:o + 4]); o += 4
        vtype = tag & 0xFFFF
        if vtype == 0:                       # NIL：某些写法为属性列表终止
            continue
        name = str_table[name_idx] if name_idx < len(str_table) else f'#{name_idx}'
        if vtype == 1:                       # BOOL
            props[name] = bool(struct.unpack('<I', d[o:o + 4])[0]); o += 4
        elif vtype == 2:                     # INT
            v, = struct.unpack('<i', d[o:o + 4]); o += 4
            props[name] = v
        elif vtype == 3:                     # REAL
            v, = struct.unpack('<f', d[o:o + 4]); o += 4
            props[name] = v
        elif vtype == 4:                     # STRING
            ln, = struct.unpack('<I', d[o:o + 4]); o += 4
            props[name] = d[o:o + ln].decode('utf-8', 'replace')
            o = _read_pad4(d, o + ln)
        elif vtype == 20:                    # POOL_BYTE_ARRAY
            n, = struct.unpack('<I', d[o:o + 4]); o += 4
            props[name] = d[o:o + n]; o = _read_pad4(d, o + n)
        elif vtype == 21:                    # POOL_INT_ARRAY
            n, = struct.unpack('<I', d[o:o + 4]); o += 4
            props[name] = list(struct.unpack('<%di' % n, d[o:o + 4 * n])); o += 4 * n
        elif vtype == 23:                    # POOL_STRING_ARRAY
            n, = struct.unpack('<I', d[o:o + 4]); o += 4
            arr = []
            for _ in range(n):
                ln, = struct.unpack('<I', d[o:o + 4]); o += 4
                arr.append(d[o:o + ln].decode('utf-8', 'replace'))
                o = _read_pad4(d, o + ln)
            props[name] = arr
        else:
            raise ValueError(f'未支持的 variant type {vtype} @ 属性 {name}')
        if name == 'locale':                 # locale 是最后一个属性
            break
    return str_table, props


def parse_phash(path: str):
    """返回 (str_idx→明文 dict, bucket 元素列表 [(hash, str_off, val_off, comp, uncomp)])"""
    d = open(path, 'rb').read()
    _, props = parse_rsrc_properties(d)
    ht = props['hash_table']
    bt = props['bucket_table']
    strings = props['strings']
    offsets = props['offsets']
    locale = props.get('locale', '')

    # bucket_table 布局（PHashTranslation::generate）：
    # [i] = 元素数；随后每元素 4×u32（后段含 hash/str_off/val_off/comp/uncomp）
    buckets = []
    i = 0
    while i < len(bt):
        n = bt[i]
        i += 1
        for _ in range(n):
            if i + 5 > len(bt):
                break
            h = bt[i] & 0xFFFFFFFF
            str_off = bt[i + 1]
            comp = bt[i + 2]
            uncomp = bt[i + 3]
            val_off = bt[i + 4]
            buckets.append((h, str_off, val_off, comp, uncomp))
            i += 5
    return strings, offsets, buckets, locale, props


def decode_strings(strings) -> dict:
    """PHashTranslation 前缀共享压缩流恢复（按顺序级联）。

    strings 池：每串编码 = [共享前缀长度 u32][后缀 char u32 ...]（Godot 3.6
    PHashTranslation::_set 的 strings 池由 generate() 顺序写入，
    get_string 沿后缀字节直到 0 终止）。此处按池内顺序重建完整串。
    """
    out = {}
    cur = ''
    i = 0
    n = len(strings)
    idx = 0
    while i < n:
        # 逐串尝试解析：共享前缀长度 p，然后后缀字符直到 0
        p = strings[i]
        if p < 0 or p > len(cur) or p > 65535:
            # 无法解析（非串起点），跳过
            i += 1
            continue
        j = i + 1
        suffix = ''
        while j < n and strings[j] != 0:
            suffix += chr(strings[j] & 0xFFFF)
            j += 1
            if j - i > 4096:
                break
        cur = cur[:p] + suffix
        out[idx] = cur
        idx += 1
        i = j + 1
    return out
