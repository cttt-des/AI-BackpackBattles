"""
从 BackpackBattles.pck 提取 GUI 可视化所需的游戏资源：
1. 物品贴图  res://Items/Sprites/<Item>.png  (.import/*.stex 内嵌 WebP) → assets/sprites/<Item>.png
2. 物品占格  extracted/Items/<Item>.tscn 的 CollisionMap.tile_data     → assets/item_db.json (shape)
3. 中文名称  res://Sheets/CSV/Items.*.translation (PHashTranslation)   → assets/item_db.json (zh)

输出:
  assets/sprites/*.png     每件物品的原始贴图
  assets/item_db.json      { itemKey: {en, zh, shape:[[dc,dr]..], is_bag} }

用法: python tools/extract_assets.py
"""
import io
import json
import os
import re
import struct
import sys
import zlib
import hashlib

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PCK = os.path.join(BASE, "Backpack Battles", "BackpackBattles.pck")
ITEMS_DIR = os.path.join(BASE, "extracted", "Items")
OUT_DIR = os.path.join(BASE, "assets")
SPRITE_DIR = os.path.join(OUT_DIR, "sprites")


# ---------------- PCK 读取 ----------------
def load_pck_index(path):
    f = open(path, "rb")
    assert f.read(4) == b"GDPC"
    f.read(16)
    f.read(64)
    n = struct.unpack("<I", f.read(4))[0]
    idx = {}
    for _ in range(n):
        pl = struct.unpack("<I", f.read(4))[0]
        p = f.read(pl).rstrip(b"\x00").decode("utf-8", "replace")
        off, size = struct.unpack("<QQ", f.read(16))
        f.read(16)
        idx[p] = (off, size)
    return f, idx


def read_entry(f, idx, path):
    if path not in idx:
        return None
    off, size = idx[path]
    f.seek(off)
    return f.read(size)


# ---------------- PHashTranslation 解析 ----------------
def parse_phash_translation(data: bytes):
    """解析 Godot 3.x 二进制资源里的 PHashTranslation。

    RSRC 容器 → 属性表；关键属性:
      hash_table:PoolIntArray, bucket_table:PoolIntArray, strings:PoolByteArray
    bucket: [size, func] + size×[key_hash, str_offset, comp_size, uncomp_size]
    字符串区: comp_size==uncomp_size 时为明文，否则 zlib（Godot smaz/zlib，实际是 zlib）。
    这里不依赖精确的 RSRC 解析——直接在文件中定位三个 PoolArray 的启发式方案不稳，
    改为完整解析 RSRC 属性。
    """
    # --- 最小 RSRC 解析器 (Godot 3.x binary resource, format v3) ---
    s = io.BytesIO(data)

    def u32():
        return struct.unpack("<I", s.read(4))[0]

    def u64():
        return struct.unpack("<Q", s.read(8))[0]

    assert s.read(4) == b"RSRC"
    big_endian = u32()
    use_real64 = u32()
    _ver_major, _ver_minor, _fmt = u32(), u32(), u32()
    _res_type = s.read(u32()).rstrip(b"\x00")  # unicode string: len + bytes
    _importmd_ofs = u64()
    _flags = u32()
    for _ in range(13):
        u32()  # reserved
    string_table = [None] * u32()
    for i in range(len(string_table)):
        ln = u32()
        string_table[i] = s.read(ln).rstrip(b"\x00").decode("utf-8", "replace")
    ext_count = u32()
    for _ in range(ext_count):
        s.read(u32())
        s.read(u32())
    int_count = u32()
    int_res = []
    for _ in range(int_count):
        s.read(u32())
        int_res.append(u64())

    # 跳到主资源（最后一个 internal resource 的 offset）
    s.seek(int_res[-1])
    _type = s.read(u32()).rstrip(b"\x00")

    props = _read_rsrc_props(s, string_table, u32)

    hash_table = props["hash_table"]
    bucket_table = props["bucket_table"]
    strings = props["strings"]
    return hash_table, bucket_table, strings


def _read_rsrc_props(s, string_table, u32):
    """通用 Godot 3.x 二进制资源属性读取（覆盖本项目所需 variant 类型）。"""
    prop_count = u32()
    props = {}
    for _ in range(prop_count):
        name_idx = u32()
        name = string_table[name_idx & 0x7FFFFFFF]
        vtype = u32()
        if vtype in (2, 3):          # BOOL / INT
            props[name] = struct.unpack("<i", s.read(4))[0]
        elif vtype == 4:             # REAL
            props[name] = struct.unpack("<f", s.read(4))[0]
        elif vtype == 40:            # INT64
            props[name] = struct.unpack("<q", s.read(8))[0]
        elif vtype == 41:            # DOUBLE
            props[name] = struct.unpack("<d", s.read(8))[0]
        elif vtype == 5:             # STRING
            ln = u32()
            props[name] = s.read(ln).rstrip(b"\x00").decode("utf-8", "replace")
        elif vtype == 10:            # VECTOR2
            props[name] = struct.unpack("<2f", s.read(8))
        elif vtype == 11:            # RECT2
            props[name] = struct.unpack("<4f", s.read(16))
        elif vtype == 20:            # COLOR
            props[name] = struct.unpack("<4f", s.read(16))
        elif vtype == 24:            # OBJECT
            sub = u32()
            if sub == 0:             # empty
                props[name] = None
            elif sub == 1:           # external by path
                ln = u32()
                props[name] = ("ext_path", s.read(ln).rstrip(b"\x00").decode("utf-8", "replace"))
            elif sub == 2:           # internal index
                props[name] = ("int_res", u32())
            elif sub == 3:           # external by index
                props[name] = ("ext_idx", u32())
        elif vtype == 31:            # RAW/PoolByteArray
            ln = u32()
            props[name] = s.read(ln)
            if ln % 4:
                s.read(4 - ln % 4)
        elif vtype == 32:            # PoolIntArray
            ln = u32()
            props[name] = list(struct.unpack("<%di" % ln, s.read(4 * ln)))
        else:
            raise ValueError(f"未处理的 variant 类型 {vtype} (prop={name})")
    return props


def parse_atlas_texture(data: bytes):
    """解析 AtlasTexture .res → (atlas_res_path, region(x,y,w,h), margin)。"""
    s = io.BytesIO(data)

    def u32():
        return struct.unpack("<I", s.read(4))[0]

    def u64():
        return struct.unpack("<Q", s.read(8))[0]

    assert s.read(4) == b"RSRC"
    u32(); u32(); u32(); u32(); u32()
    s.read(u32())          # res_type
    u64(); u32()
    for _ in range(13):
        u32()
    string_table = [None] * u32()
    for i in range(len(string_table)):
        string_table[i] = s.read(u32()).rstrip(b"\x00").decode("utf-8", "replace")
    ext = []
    for _ in range(u32()):
        s.read(u32())                    # type
        ext.append(s.read(u32()).rstrip(b"\x00").decode("utf-8", "replace"))
    int_res = []
    for _ in range(u32()):
        s.read(u32())
        int_res.append(u64())
    s.seek(int_res[-1])
    s.read(u32())          # type name
    props = _read_rsrc_props(s, string_table, u32)
    atlas = props.get("atlas")
    apath = None
    if isinstance(atlas, tuple):
        if atlas[0] == "ext_idx":
            apath = ext[atlas[1]] if atlas[1] < len(ext) else None
        elif atlas[0] == "ext_path":
            apath = atlas[1]
    return apath, props.get("region"), props.get("margin")


def _smaz_decompress(data: bytes) -> bytes:
    """Godot PHashTranslation 用的 smaz 压缩解码。"""
    _SMAZ_CB = [
        " ", "the", "e", "t", "a", "of", "o", "and", "i", "n", "s", "e ", "r", " th",
        " t", "in", "he", "th", "h", "he ", "to", "\r\n", "l", "s ", "d", " a", "an",
        "er", "c", " o", "d ", "on", " of", "re", "of ", "t ", ", ", "is", "u", "at",
        "   ", "n ", "or", "which", "f", "m", "as", "it", "that", "\n", "was", "en",
        "  ", " w", "es", " an", " i", "\r", "f ", "g", "p", "nd", " s", "nd ", "ed ",
        "w", "ed", "http://", "for", "te", "ing", "y ", "The", " c", "ti", "r ", "his",
        "st", " in", "ar", "nt", ",", " to", "y", "ng", " h", "with", "le", "al", "to ",
        "b", "ou", "be", "were", " b", "se", "o ", "ent", "ha", "ng ", "their", "\"",
        "hi", "from", " f", "in ", "de", "ion", "me", "v", ".", "ve", "all", "re ",
        "ri", "ro", "is ", "co", "f t", "are", "ea", ". ", "her", " m", "er ", " p",
        "es ", "by", "they", "di", "ra", "ic", "not", "s, ", "d t", "at ", "ce", "la",
        "h ", "ne", "as ", "tio", "on ", "n t", "io", "we", " a ", "om", ", a", "s o",
        "ur", "li", "ll", "ch", "had", "this", "e t", "g ", "e\r\n", " wh", "ere",
        " co", "e o", "a ", "us", " d", "ss", "\n\r\n", "\r\n\r", "=\"", " be", " e",
        "s a", "ma", "one", "t t", "or ", "but", "el", "so", "l ", "e s", "s,", "no",
        "ter", " wa", "iv", "ho", "e a", " r", "hat", "s t", "ns", "ch ", "wh", "tr",
        "ut", "/", "have", "ly ", "ta", " ha", " on", "tha", "-", " l", "ati", "en ",
        "pe", " re", "there", "ass", "si", " fo", "wa", "ec", "our", "who", "its", "z",
        "fo", "rs", ">", "ot", "un", "<", "im", "th ", "nc", "ate", "><", "ver", "ad",
        " we", "ly", "ee", " n", "id", " cl", "ac", "il", "</", "rt", " wi", "div",
        "e, ", " it", "whi", " ma", "ge", "x", "e c", "men", ".com",
    ]
    out = bytearray()
    i = 0
    n = len(data)
    while i < n:
        b = data[i]
        if b == 254:  # verbatim byte
            i += 1
            out.append(data[i])
            i += 1
        elif b == 255:  # verbatim string
            i += 1
            ln = data[i] + 1
            i += 1
            out += data[i:i + ln]
            i += ln
        else:
            out += _SMAZ_CB[b].encode("utf-8", "replace")
            i += 1
    return bytes(out)


def translation_to_dict(hash_table, bucket_table, strings):
    """遍历 bucket_table 导出 str_offset→text 全量（不做哈希查询，直接全量展开）。"""
    out = []
    # bucket_table 布局: 对每个非空桶 [size, func, (hash, str_off, comp_size, uncomp_size)*size]
    i = 0
    n = len(bucket_table)
    while i < n:
        size = bucket_table[i]
        i += 2  # skip size, func
        for _ in range(size):
            _h, off, csize, usize = bucket_table[i:i + 4]
            i += 4
            raw = bytes(strings[off:off + csize])
            if csize < usize:
                try:
                    txt = _smaz_decompress(raw).decode("utf-8", "replace")
                except Exception:
                    continue
            else:
                txt = raw.split(b"\x00")[0].decode("utf-8", "replace")
            txt = txt.rstrip("\x00")
            out.append((off, txt))
    return out


def build_key_map(f, idx):
    """en 与 zh 的 translation 用相同 key 集合；PHashTranslation 保留 key 的哈希。
    直接办法：en 表把 text 当 key 反查（物品英文名 == key 本身在 Items.csv 中通常成立），
    稳妥办法：同一 key 在两个表中的 bucket 位置由 (hash, capacity) 决定，capacity 相同则
    hash_table/bucket 布局一一对应 → 用 (bucket_index, slot_hash) 做对齐。
    """
    tables = [("res://Sheets/CSV/Items.en.translation",
               "res://Sheets/CSV/Items.zh_Hans_CN.translation"),
              ("res://Sheets/CSV/ExclusiveItems.en.translation",
               "res://Sheets/CSV/ExclusiveItems.zh_Hans_CN.translation"),
              ("res://Sheets/CSV/Full.en.translation",
               "res://Sheets/CSV/Full.zh_Hans_CN.translation")]
    merged = {}
    for en_path, zh_path in tables:
        merged.update(_pair_tables(
            parse_phash_translation(read_entry(f, idx, en_path)),
            parse_phash_translation(read_entry(f, idx, zh_path))))
    return merged


def _pair_tables(en, zh):

    def explode(tbl):
        hash_table, bucket_table, strings = tbl
        m = {}  # (bucket_idx, key_hash) -> text
        for bi, boff in enumerate(hash_table):
            if boff == -1:
                continue
            size = bucket_table[boff]
            p = boff + 2
            for _ in range(size):
                h, off, csize, usize = bucket_table[p:p + 4]
                p += 4
                raw = bytes(strings[off:off + csize])
                if csize < usize:
                    try:
                        txt = _smaz_decompress(raw).decode("utf-8", "replace")
                    except Exception:
                        txt = ""
                else:
                    txt = raw.split(b"\x00")[0].decode("utf-8", "replace")
                m[(bi, h)] = txt.rstrip("\x00")
        return m

    men, mzh = explode(en), explode(zh)
    if len(en[0]) != len(zh[0]):
        print("[!] en/zh hash_table 容量不同，槽位对齐不可用", len(en[0]), len(zh[0]))
    en2zh = {}
    for k, entxt in men.items():
        zhtxt = mzh.get(k)
        if zhtxt:
            en2zh[entxt] = zhtxt
    return en2zh


# ---------------- tscn 解析（占格 + 贴图路径 + 容器判定） ----------------
def parse_tile_data(pool: str):
    """tile_data PoolIntArray：每 3 个 int 一组 (cell_id, tile_id, flip)。
    cell_id 编码: int32, 低16位=x(有符号), 高16位=y(有符号)。
    tile_id 语义（Item.tscn tile_set 实测）:
      2 = 袋内槽位(Slot)  3 = 实体占格(Collision)  4 = 扩展预留区(PotentialSpace)
    返回 [(x, y, tile_id), ...]"""
    nums = [int(x) for x in pool.split(",") if x.strip().lstrip("-").isdigit()]
    cells = []
    for i in range(0, len(nums) - 2, 3):
        cid = nums[i] & 0xFFFFFFFF
        x = cid & 0xFFFF
        y = (cid >> 16) & 0xFFFF
        if x >= 0x8000:
            x -= 0x10000
        if y >= 0x8000:
            y -= 0x10000
        cells.append((x, y, nums[i + 1] & 0xFFFF))
    return cells


def parse_item_tscn(path):
    return parse_item_tscn_text(
        open(path, "r", encoding="utf-8", errors="replace").read())


def parse_item_tscn_text(txt):
    info = {}
    # 贴图（第一个 Sprites 目录引用，兼容 Items/Sprites 与 Items/Exclusive/Sprites）
    m = re.search(r'path="(res://Items/(?:Exclusive/)?Sprites/[^"]+\.png)"', txt)
    info["sprite"] = m.group(1) if m else None
    # 显示名（根节点名）
    m = re.search(r'\[node name="([^"]+)" instance=', txt)
    info["display"] = m.group(1) if m else None
    # 容器判定：Icon 下有 TileMap（袋内格子）的是容器（LeatherBag/FannyPack/PotionBelt 等）
    info["is_bag"] = bool(re.search(r'type="TileMap" parent="Icon"', txt))
    # CollisionMap 的 tile_data 与 position
    blk = re.search(
        r'\[node name="CollisionMap"[^\]]*\](.*?)(?=\n\[node|\Z)', txt, re.S)
    cells, cm_pos = [], (0.0, 0.0)
    if blk:
        b = blk.group(1)
        m = re.search(r"tile_data = PoolIntArray\(([^)]*)\)", b)
        if m:
            cells = parse_tile_data(m.group(1))
        m = re.search(r"position = Vector2\( ([-\d.]+), ([-\d.]+) \)", b)
        if m:
            cm_pos = (float(m.group(1)), float(m.group(2)))
    info["cells_raw"] = cells
    info["cm_pos"] = cm_pos
    # tile id 语义: 2=CantAdd(容器占格) 3=SlotPreview(实体占格) 4=AffectedTile(效果区)
    #             0=Slot(袋内槽位)
    def to_px(sel):
        return [(cx * 80 + cm_pos[0], cy * 80 + cm_pos[1])
                for cx, cy, tid in cells if tid in sel]

    info["cell_px"] = to_px({2, 3})     # 实际占用格
    info["effect_px"] = to_px({4})      # 效果影响区
    info["slot_px"] = to_px({0})        # 袋内槽位（容器）
    return info


def _decode_image(data: bytes):
    """stex → 内嵌 WebP/PNG 解码。"""
    from PIL import Image
    i = data.find(b"RIFF")
    if i < 0:
        i = data.find(b"\x89PNG")
    if i < 0:
        raise ValueError("no RIFF/PNG payload")
    return Image.open(io.BytesIO(data[i:])).convert("RGBA")


def _trim(img):
    """剔除透明边：裁剪到非透明像素的包围盒，使贴图尺寸正好贴合内容。"""
    bbox = img.getbbox()
    if bbox:
        return img.crop(bbox)
    return img


def _load_ui_texture(f, idx, res_path):
    """按 res:// 路径加载一个 UI/格子纹理（独立 stex，无图集）。"""
    h = hashlib.md5(res_path.encode()).hexdigest()
    name = res_path.rsplit("/", 1)[-1][:-4]
    data = read_entry(f, idx, f"res://.import/{name}.png-{h}.stex")
    if not data:
        return None
    return _decode_image(data)


def load_sprite(f, idx, res, atlas_cache):
    """按 .import 描述加载贴图：独立 stex 直接解码；texture_atlas 则从图集裁剪。
    res 为完整资源路径 res://.../<Name>.png。返回裁剪掉透明边的贴图。"""
    h = hashlib.md5(res.encode()).hexdigest()
    sprite_name = res.rsplit("/", 1)[-1][:-4]
    # 1) 独立 stex
    data = read_entry(f, idx, f"res://.import/{sprite_name}.png-{h}.stex")
    if data:
        return _trim(_decode_image(data))
    # 2) 图集 .res (AtlasTexture)
    data = read_entry(f, idx, f"res://.import/{sprite_name}.png-{h}.res")
    if not data:
        return None
    apath, region, margin = parse_atlas_texture(data)
    if not apath or not region:
        return None
    if apath not in atlas_cache:
        ah = hashlib.md5(apath.encode()).hexdigest()
        aname = apath.rsplit("/", 1)[-1]
        adata = read_entry(f, idx, f"res://.import/{aname}-{ah}.stex")
        if not adata:
            return None
        atlas_cache[apath] = _decode_image(adata)
    x, y, w, hh = [int(round(v)) for v in region]
    return _trim(atlas_cache[apath].crop((x, y, x + w, y + hh)))


# 改名物品的手工别名（tscn 显示名 → 翻译表键名）
ALIAS = {
    "Platin Customer Card": "Platinum Customer Card",
    "Rib Saw Blade": "Ripsaw Blade",
    "Gingerbread Man": "Gingerbread Jerry",
}


def main():
    os.makedirs(SPRITE_DIR, exist_ok=True)
    f, idx = load_pck_index(PCK)
    atlas_cache = {}

    # 1. 中文映射
    print("[*] 解析翻译表 ...")
    try:
        en2zh = build_key_map(f, idx)
        print(f"    en→zh 对齐 {len(en2zh)} 条")
    except Exception as e:
        print("    [!] 翻译解析失败:", e)
        en2zh = {}

    # 2. 物品 db + 贴图（直接从 pck 读 tscn，覆盖 Items/ 与 Items/Exclusive/）
    from PIL import Image
    db = {}
    n_sprite = 0
    tscn_paths = sorted(
        p for p in idx
        if p.endswith(".tscn") and (
            (p.startswith("res://Items/") and p.count("/") == 3)
            or p.startswith("res://Items/Exclusive/")))
    for res_path in tscn_paths:
        fn = res_path.rsplit("/", 1)[-1]
        key = fn[:-5]
        if key in ("Item", "ItemPushZone"):
            continue
        txt = read_entry(f, idx, res_path).decode("utf-8", "replace")
        # 真实物品必须实例化自 Item.tscn（动画/特效节点不算）
        if 'path="res://Items/Item.tscn"' not in txt:
            continue
        try:
            info = parse_item_tscn_text(txt)
        except Exception as e:
            print(f"    [!] {fn}: {e}")
            continue
        display = info["display"] or key
        zh = en2zh.get(display) or en2zh.get(key) or \
            (en2zh.get(ALIAS[display]) if display in ALIAS else "") or ""
        if not zh:
            # 模糊兜底：显示名是翻译键的子串（如 Greatsword ⊂ Impractically Large Greatsword）
            # 或翻译键去掉标点后相等（Mr Struggles vs Mr. Struggles）
            norm = lambda t: re.sub(r"[^a-z0-9]", "", t.lower())
            nd = norm(display)
            cands = [k for k in en2zh if norm(k) == nd] or \
                    [k for k in en2zh if nd and nd in norm(k)]
            if len(cands) == 1:
                zh = en2zh[cands[0]]
        db[display] = {
            "key": key,
            "zh": zh,
            "is_bag": info["is_bag"],
            "cell_px": info["cell_px"],
            "slot_px": info["slot_px"],
            "sprite": None,
        }
        # 贴图（独立 stex 或图集 AtlasTexture .res）
        sp = info["sprite"]
        if sp:
            try:
                img = load_sprite(f, idx, sp, atlas_cache)
                if img is not None:
                    out = os.path.join(SPRITE_DIR, f"{key}.png")
                    img.save(out)
                    db[display]["sprite"] = f"{key}.png"
                    n_sprite += 1
            except Exception as e:
                print(f"    [!] 贴图 {sp}: {e}")

    with open(os.path.join(OUT_DIR, "item_db.json"), "w", encoding="utf-8") as fp:
        json.dump(db, fp, ensure_ascii=False, indent=1)
    n_zh = sum(1 for v in db.values() if v["zh"])
    n_bag = sum(1 for v in db.values() if v["is_bag"])
    print(f"[✓] item_db.json: {len(db)} 件物品 | 中文 {n_zh} | 容器 {n_bag} | 贴图 {n_sprite}")

    # 3. UI 格子素材（背包网格的槽位纹理，游戏内 res://Items/Tiles/）
    #    Slot.png=空格子, FilledSlot.png=被占用的格子；裁剪掉透明边后保存。
    ui_textures = [
        ("res://Items/Tiles/Slot.png", "cell_empty.png"),
        ("res://Items/Tiles/FilledSlot.png", "cell_filled.png"),
    ]
    for src, out in ui_textures:
        try:
            img = _load_ui_texture(f, idx, src)
            if img is not None:
                img.save(os.path.join(OUT_DIR, out))
                print(f"    [UI] 提取 {out} ({img.size}) <- {src}")
            else:
                print(f"    [!] UI 纹理缺失: {src}")
        except Exception as e:
            print(f"    [!] UI 纹理 {src}: {e}")


if __name__ == "__main__":
    main()
