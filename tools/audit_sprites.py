#!/usr/bin/env python3
"""物品贴图逐项审计：查表自洽 + 文件完整 + 图层真值比对 + 缩略图总览。

检查项（对应「贴图与物品不符」的三类根因）：
  A. 文件完整：sprites/<key>.png 存在、尺寸=img_w×img_h、origin 在画布内
  B. 查表自洽：entry_for(name, gd) 命中自身；不带 script 的 entry(name)
     是否会命中别的条目（运行时任何丢 script 的调用点都会串图）
  C. 归一化冲突：两个物品名 _norm 后相同（setdefault 先到先得 → 后者被抢）
  D. 图层真值：按当前解包源重新展开 tscn 收集 Icon 图层，
     与 item_db.json 的 layer_meta 逐层比对（顺序+贴图名）
  E. 共脚本家族：脚本对应多件物品时，各成员按名字必须能命中自身
  F. 缩略图总览：assets/_audit/sheet_NN.png（8×8 格，含名字）供目检

用法: python -X utf8 tools/audit_sprites.py [--sheets-only]
"""
import json
import math
import sys
from pathlib import Path

BASE = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(BASE / "tools"))
sys.path.insert(0, str(BASE))

from PIL import Image, ImageDraw, ImageFont  # noqa: E402
from core.item_db import ItemDB, _norm  # noqa: E402
from tools import extract_sprites as ex  # noqa: E402

ASSETS = BASE / "assets"
SPRITES = ASSETS / "sprites"
AUDIT_DIR = ASSETS / "_audit"
SRC_ROOT = ex.SRC_ROOT if ex.SRC_ROOT.exists() else ex.FALLBACK_ROOT

problems = []       # (级别, 物品, 说明)
risky_no_script = []  # 不带 script 时会命中别的条目的名字


def add(level, item, msg):
    problems.append((level, item, msg))


def check_files(db):
    print("== A. 文件完整性 ==")
    for name, e in sorted(db.items()):
        key = e.get("key", "")
        p = SPRITES / e.get("sprite", "")
        if not p.exists():
            add("ERR", name, f"贴图缺失 {p.name}")
            continue
        try:
            img = Image.open(p)
        except Exception as exc:  # noqa: BLE001
            add("ERR", name, f"贴图打不开: {exc}")
            continue
        if img.size != (e.get("img_w"), e.get("img_h")):
            add("ERR", name,
                f"尺寸不符 db=({e.get('img_w')},{e.get('img_h')}) 实际={img.size}")
        ox, oy = e.get("origin_px", [0, 0])
        if not (0 <= ox <= img.width and 0 <= oy <= img.height):
            add("ERR", name, f"origin_px=({ox},{oy}) 超出画布 {img.size}")
    n_err = sum(1 for p in problems if p[0] == "ERR")
    print(f"   检查 {len(db)} 项，异常 {n_err}")


def check_lookup(db, idb):
    print("== B. 查表自洽（entry_for / 无 script 的 entry）==")
    for name, e in sorted(db.items()):
        got = idb.entry_for(name, e.get("gd") or None)
        if got is not e and got is not None and got.get("key") != e.get("key"):
            add("ERR", name,
                f"entry_for(name,gd) 命中 {got.get('key')}（应 {e.get('key')}）")
        plain = idb.entry(name)
        if plain is not None and plain.get("key") != e.get("key"):
            risky_no_script.append((name, plain.get("key"), e.get("key")))
    print(f"   无 script 时会串图的条目: {len(risky_no_script)}")
    for name, hit, own in risky_no_script:
        add("WARN", name, f"entry(name) → {hit}（自身 {own}）")


def check_norm_collisions(db):
    print("== C. 归一化名冲突 ==")
    seen = {}
    for name in db:
        seen.setdefault(_norm(name), []).append(name)
    for k, names in seen.items():
        if len(names) > 1:
            add("WARN", names[0], f"归一化名冲突 {k}: {names}（setdefault 先到先得）")
    n = sum(1 for p in problems if p[0] == "WARN" and "归一化名冲突" in p[2])
    print(f"   冲突组 {n}")


def expected_layers(tscn: Path):
    """按当前生成器逻辑重新推导 Icon 图层（tex res 路径列表，序敏感）。"""
    try:
        nodes, tex_map = ex.expand_scene(tscn)
    except Exception:  # noqa: BLE001
        return None
    layers = ex.collect_layers(nodes, tex_map)
    return [Path(ly["tex"]).stem for ly in layers]


def check_layers(db):
    print("== D. 图层真值比对（重推导 vs item_db）==")
    miss_src = 0
    diff = 0
    for name, e in sorted(db.items()):
        key = e.get("key", "")
        tscn = SRC_ROOT / "Items" / (key + ".tscn")
        if not tscn.exists():
            tscn = None
            for cand in SRC_ROOT.rglob(key + ".tscn"):
                tscn = cand
                break
        if tscn is None:
            miss_src += 1
            add("WARN", name, f"解包源无 {key}.tscn（无法重推导）")
            continue
        want = expected_layers(tscn)
        if want is None:
            add("WARN", name, "tscn 展开失败")
            continue
        got = [m.get("tex", "") for m in (e.get("layer_meta") or [])]
        if want != got:
            diff += 1
            add("ERR", name, f"图层不符 db={got} 重推导={want}")
    print(f"   源缺失 {miss_src} | 图层不一致 {diff}")


def check_shared_scripts(db):
    print("== E. 共脚本家族 ==")
    fams = {}
    for name, e in db.items():
        gd = e.get("gd") or ""
        if gd:
            fams.setdefault(gd, []).append(name)
    shared = {g: ns for g, ns in fams.items() if len(ns) > 1}
    print(f"   共脚本脚本数 {len(shared)}")
    for gd, names in sorted(shared.items()):
        print(f"   {Path(gd).stem}: {names}")


def sheets(db, per=64, cols=8, cell=110):
    print("== F. 缩略图总览 → assets/_audit/ ==")
    AUDIT_DIR.mkdir(parents=True, exist_ok=True)
    try:
        font = ImageFont.truetype("msyh.ttc", 11)
    except Exception:  # noqa: BLE001
        font = ImageFont.load_default()
    names = sorted(db.keys())
    n_sheets = math.ceil(len(names) / per)
    for s in range(n_sheets):
        chunk = names[s * per:(s + 1) * per]
        rows = math.ceil(len(chunk) / cols)
        im = Image.new("RGBA", (cols * cell, rows * (cell + 16)), (24, 26, 32, 255))
        dr = ImageDraw.Draw(im)
        for i, name in enumerate(chunk):
            r, c = divmod(i, cols)
            x0, y0 = c * cell, r * (cell + 16)
            e = db[name]
            p = SPRITES / e.get("sprite", "")
            dr.rectangle([x0, y0, x0 + cell - 1, y0 + cell + 15],
                         outline=(60, 64, 74, 255))
            if p.exists():
                img = Image.open(p).convert("RGBA")
                img.thumbnail((cell - 6, cell - 6))
                im.alpha_composite(img, (x0 + (cell - img.width) // 2,
                                         y0 + (cell - img.height) // 2))
            label = e.get("zh") or name
            if len(label) > 12:
                label = label[:12]
            dr.text((x0 + 3, y0 + cell + 1), label, fill=(220, 224, 232, 255),
                    font=font)
        out = AUDIT_DIR / f"sheet_{s:02d}.png"
        im.save(out)
        print(f"   {out.name}: {chunk[0]} … {chunk[-1]}")
    return n_sheets


def main():
    sheets_only = "--sheets-only" in sys.argv
    db = json.loads((ASSETS / "item_db.json").read_text(encoding="utf-8"))
    idb = ItemDB(ASSETS)
    if not sheets_only:
        check_files(db)
        check_lookup(db, idb)
        check_norm_collisions(db)
        check_layers(db)
        check_shared_scripts(db)
        print()
        print(f"==== 问题汇总：{len(problems)} 条 ====")
        for lv, item, msg in problems:
            print(f"  [{lv}] {item}: {msg}")
    n = sheets(db)
    print(f"[OK] {n} 张总览图已写入 {AUDIT_DIR}")


if __name__ == "__main__":
    main()
