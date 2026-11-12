#!/usr/bin/env python3
"""疑点贴图深挖：对目检发现的可疑物品，dump 其 db 条目 / tscn 贴图引用 /
多版本源 PNG 哈希比对，并渲染「合成图 vs 源贴图」并排图供目检。

用法: python -X utf8 tools/audit_sprite_suspects.py [名字...]
不带参数时跑内置疑点清单。
"""
import hashlib
import json
import sys
from pathlib import Path

BASE = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(BASE / "tools"))
sys.path.insert(0, str(BASE))

from PIL import Image  # noqa: E402
from core.item_db import ItemDB  # noqa: E402
from tools import extract_sprites as ex  # noqa: E402

ASSETS = BASE / "assets"
AUDIT_DIR = ASSETS / "_audit"
SRC_ROOT = ex.SRC_ROOT if ex.SRC_ROOT.exists() else ex.FALLBACK_ROOT
EXTRACTED = BASE / "extracted"

DEFAULT_SUSPECTS = [
    "劣质紫水晶", "Greatsword", "全能狼崽", "武士刀", "秃莺之簇", "双特武器",
    "砸木", "治疗草药", "荷包里圣锅", "幸运存钱罐", "紫水晶碎片", "驭魔剑",
    "命运小姐", "炽热巨剑", "Molten Spear", "Phoenix2", "Lucky Shortbow",
    "剧毒常春藤", "彩虹剑", "Random Loado", "拼图背包", "铁匠入门指南",
    "鼻涕大师", "细绳", "万里挑一", "Whetstone2", "Whetstone3",
    "白色主教", "黑色主教", "Wand", "失响魔棒", "水银元素", "驯兽笼",
    "棋盘", "棋艺大师",
]


def find_tscn(key: str):
    p = SRC_ROOT / "Items" / (key + ".tscn")
    if p.exists():
        return p
    for cand in SRC_ROOT.rglob(key + ".tscn"):
        return cand
    return None


def png_hash_variants(res_path: str):
    """同一 res:// 路径在不同提取源里的文件与哈希。"""
    rel = res_path[6:] if res_path.startswith("res://") else res_path
    out = []
    for tag, root in (("oracle", SRC_ROOT), ("v117", EXTRACTED)):
        f = root / rel
        if f.exists():
            h = hashlib.md5(f.read_bytes()).hexdigest()[:10]
            out.append(f"{tag}:{h}")
        else:
            out.append(f"{tag}:缺")
    return " ".join(out)


def resolve_label(db, label):
    if label in db:
        return label, db[label]
    for name, e in db.items():
        if e.get("zh") == label:
            return name, e
    for name, e in db.items():
        zh = e.get("zh") or ""
        if zh and (zh.startswith(label) or label.startswith(zh)) and label:
            return name, e
        if name.startswith(label) or (label and name and label.startswith(name)):
            return name, e
    return None, None


def main():
    labels = sys.argv[1:] or DEFAULT_SUSPECTS
    db = json.loads((ASSETS / "item_db.json").read_text(encoding="utf-8"))
    idb = ItemDB(ASSETS)
    AUDIT_DIR.mkdir(parents=True, exist_ok=True)

    for label in labels:
        name, e = resolve_label(db, label)
        if e is None:
            print(f"\n### {label}: db 中未找到")
            continue
        key = e.get("key", "")
        print(f"\n### {name}  (key={key}, zh={e.get('zh')})")
        print(f"    gd={e.get('gd')}")
        meta = e.get("layer_meta") or []
        print(f"    layers={[(m.get('tex'), m.get('x'), m.get('y')) for m in meta]}")
        tscn = find_tscn(key)
        if tscn is None:
            print("    [!] 找不到 tscn")
            continue
        rel_t = tscn.relative_to(SRC_ROOT).as_posix()
        print(f"    tscn={rel_t}")
        ext, nodes = ex.parse_tscn(tscn.read_text(encoding="utf-8", errors="replace"))
        # 本文件直接引用的贴图
        for nid, path in sorted(ext.items(), key=lambda kv: int(kv[0])):
            if path.lower().endswith(".png") and "/Tiles/" not in path:
                print(f"      ext[{nid}] {path}  [{png_hash_variants(path)}]")
        # 展开后 Icon 层实际用的贴图
        nodes_full, tex_map = ex.expand_scene(tscn)
        for p, res in sorted(tex_map.items()):
            if ex.is_icon_layer(p, res):
                print(f"      层 {p} → {res}")

        # 并排渲染：合成图 | 各源 PNG
        comp = SPRITES = ASSETS / "sprites" / e.get("sprite", "")
        panels = []
        if comp.exists():
            panels.append(("composed", Image.open(comp).convert("RGBA")))
        for p, res in sorted(tex_map.items()):
            if not ex.is_icon_layer(p, res):
                continue
            f = ex.res_to_file(res)
            if f:
                panels.append((Path(res).stem, Image.open(f).convert("RGBA")))
        if panels:
            H = 200
            ims = []
            for tag, im in panels:
                cp = im.copy()
                cp.thumbnail((H, H))
                ims.append((tag, cp))
            W = sum(i.width + 14 for _, i in ims) + 14
            sheet = Image.new("RGBA", (W, H + 26), (24, 26, 32, 255))
            x = 14
            from PIL import ImageDraw
            dr = ImageDraw.Draw(sheet)
            for tag, im in ims:
                sheet.alpha_composite(im, (x, 13))
                dr.text((x, H + 2), tag[:20][:20], fill=(220, 224, 232, 255))
                x += im.width + 14
            out = AUDIT_DIR / f"suspect_{key}.png"
            sheet.save(out)
            print(f"    → {out.name}")


if __name__ == "__main__":
    main()
