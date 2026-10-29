
"""从全量反编译树提取物品贴图与元数据（多层合成，保留原画布几何）。

数据源：output/_recovery/decomp_cur（GDRE 全量反编译，含 png 与 tscn），
兜底 decompiled_full（仓库文本树，无 png）。

关键点
------
物品场景是「继承 + 覆盖」结构：Items/Xxx.tscn 实例化 res://Items/Item.tscn，
再用不带 type 的 [node name="Icon" parent="."] 覆盖基类属性。基类 Icon 是 Sprite，
子场景的 Icon 继承该类型——只按 type=="Sprite" 收层会漏掉绝大多数物品的主贴图，
这正是「缺失贴图」的根因；多层物品（Manathirst/RubyChonk/…）同理只画了一层。

输出
----
assets/sprites/<key>.png   合成图（画布=所有层包围盒，未裁透明边）
assets/item_db.json        {显示名: {key,zh,is_bag,cell_px,slot_px,sprite,
                                     img_w,img_h,origin_px,layers,layer_meta}}
   origin_px = 物品节点原点在合成图中的像素位置（GUI 据此把贴图钉到物品位置）

用法: python -X utf8 tools/extract_sprites.py
"""
import json
import math
import re
from pathlib import Path

import numpy as np
from PIL import Image

BASE = Path(__file__).resolve().parent.parent
OUT_DIR = BASE / "assets"
SPRITE_DIR = OUT_DIR / "sprites"
SRC_ROOT = BASE / "output" / "_recovery" / "decomp_cur"
FALLBACK_ROOT = BASE / "decompiled_full"

# 只认「物品」根场景：实例化 Item.tscn / Gem.tscn
_ITEM_SCENES = ("res://Items/Item.tscn", "res://Items/Gems/Gem.tscn")
# 基类模板（不是可购买物品），提取时跳过
_BASE_SCENES = {"Item", "Gem"}


# ======================= tscn 解析 =======================
def parse_tscn(text):
    """逐行解析 .tscn。

    不能用一条正则吃掉节点头：根节点可能带 groups=["Item"] 这类含 ']' 的属性，
    宽字符类会在第一个 ']' 处截断，导致基类根节点识别失败、整条继承链随之失效
    （表现为「所有物品都缺主贴图」）。
    """
    ext = {}
    for m in re.finditer(r'\[ext_resource path="([^"]+)" type="(\w+)" id=(\d+)\]', text):
        ext[m.group(3)] = m.group(1)
    nodes = []
    cur = None
    for line in text.splitlines():
        s = line.strip()
        if s.startswith("[node "):
            if cur is not None:
                nodes.append(cur)
            head = s[len("[node "):]
            if head.endswith("]"):
                head = head[:-1]
            nm = re.match(r'name="([^"]*)"', head)
            typ = re.search(r' type="([^"]*)"', head)
            par = re.search(r' parent="([^"]*)"', head)
            inst = re.search(r' instance=ExtResource\(\s*(\d+)\s*\)', head)
            idx = re.search(r' index="(\d+)"', head)
            cur = {
                "name": nm.group(1) if nm else "",
                "type": typ.group(1) if typ else None,
                "parent": par.group(1) if par else None,
                "instance": ext.get(inst.group(1)) if inst else None,
                "index": int(idx.group(1)) if idx else 0,
                "body": [],
            }
        elif s.startswith("["):
            if cur is not None:
                nodes.append(cur)
                cur = None
        elif cur is not None:
            cur["body"].append(line)
    if cur is not None:
        nodes.append(cur)
    for n in nodes:
        n["body"] = "\n".join(n["body"])
    return ext, nodes


def node_props(body):
    d = {}
    for line in body.splitlines():
        mm = re.match(r'^([A-Za-z_/0-9]+) = (.*)$', line.strip())
        if mm:
            d[mm.group(1)] = mm.group(2).strip()
    return d


def _vec2(s, default=(0.0, 0.0)):
    if not s:
        return default
    m = re.search(r'Vector2\(\s*([-\d.eE+]+)\s*,\s*([-\d.eE+]+)\s*\)', s)
    return (float(m.group(1)), float(m.group(2))) if m else default


def _color(s, default=(1.0, 1.0, 1.0, 1.0)):
    if not s:
        return default
    m = re.search(r'Color\(\s*([-\d.eE+]+)\s*,\s*([-\d.eE+]+)\s*,\s*'
                  r'([-\d.eE+]+)\s*,\s*([-\d.eE+]+)\s*\)', s)
    return tuple(float(m.group(i)) for i in range(1, 5)) if m else default


def _rect(s):
    if not s:
        return None
    m = re.search(r'Rect2\(\s*([-\d.eE+]+)\s*,\s*([-\d.eE+]+)\s*,\s*'
                  r'([-\d.eE+]+)\s*,\s*([-\d.eE+]+)\s*\)', s)
    return tuple(float(m.group(i)) for i in range(1, 5)) if m else None


def _ext_ref(ext, prop):
    m = re.search(r'ExtResource\(\s*(\d+)\s*\)', prop or '')
    return ext.get(m.group(1)) if m else None


def res_to_file(res_path):
    if not res_path or not res_path.lower().endswith(".png"):
        return None
    rel = res_path[6:] if res_path.startswith("res://") else res_path
    for root in (SRC_ROOT, FALLBACK_ROOT):
        p = root / rel
        if p.exists():
            return p
    return None


def scene_file(res_path):
    if not res_path or not res_path.endswith(".tscn"):
        return None
    rel = res_path[6:] if res_path.startswith("res://") else res_path
    for root in (SRC_ROOT, FALLBACK_ROOT):
        p = root / rel
        if p.exists():
            return p
    return None


# ======================= 场景继承展开 =======================
class SceneTree:
    """把继承链场景展开成扁平节点表：path → {type, props, order}。

    基类节点先入表，子场景同名 path 就地覆盖属性（Godot 继承覆盖语义）。
    """

    def __init__(self):
        self.nodes = {}
        self._order = 0
        self._seen = set()
        self._tex = {}      # path -> res:// png

    def load(self, path, prefix=""):
        if path in self._seen:
            return
        self._seen.add(path)
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except Exception:
            return
        ext, nodes = parse_tscn(text)
        root = next((n for n in nodes if n["parent"] is None), None)
        if root is None:
            return
        # 1) 基类实例先展开
        if root.get("instance"):
            base = scene_file(root["instance"])
            if base:
                self.load(base, prefix)
        for n in nodes:
            if n["parent"] is None and n["instance"]:
                base = scene_file(n["instance"])
                if base:
                    self.load(base, prefix)
        # 2) 本场景节点
        for n in nodes:
            if n["parent"] is None:
                continue
            par = "" if n["parent"] in (".", "") else n["parent"]
            rel = (par + "/" + n["name"]) if par else n["name"]
            full = (prefix + "/" + rel) if prefix else rel
            props = node_props(n["body"])
            tex = _ext_ref(ext, props.get("texture"))
            cur = self.nodes.get(full)
            if cur is None:
                self.nodes[full] = {"type": n["type"], "props": props,
                                    "order": self._order}
                self._order += 1
            else:
                if n["type"]:
                    cur["type"] = n["type"]
                cur["props"].update(props)
            if tex:
                self._tex[full] = tex
            if n["instance"]:
                base = scene_file(n["instance"])
                if base:
                    self.load(base, full)


def expand_scene(path):
    t = SceneTree()
    t.load(path)
    return t.nodes, t._tex


# ======================= 仿射（Godot 2D） =======================
ID = (1.0, 0.0, 0.0, 1.0, 0.0, 0.0)


def mat_mul(m1, m2):
    a1, b1, c1, d1, e1, f1 = m1
    a2, b2, c2, d2, e2, f2 = m2
    return (
        a1 * a2 + c1 * b2,
        b1 * a2 + d1 * b2,
        a1 * c2 + c1 * d2,
        b1 * c2 + d1 * d2,
        a1 * e2 + c1 * f2 + e1,
        b1 * e2 + d1 * f2 + f1,
    )


def mat_node(props):
    pos = _vec2(props.get("position"))
    rot = float(props.get("rotation", 0.0) or 0.0)
    scale = _vec2(props.get("scale"), (1.0, 1.0))
    cos_r, sin_r = math.cos(rot), math.sin(rot)
    return (cos_r * scale[0], sin_r * scale[0],
            -sin_r * scale[1], cos_r * scale[1], pos[0], pos[1])


def mat_apply(m, x, y):
    a, b, c, d, e, f = m
    return (a * x + c * y + e, b * x + d * y + f)


# ======================= 图层收集 =======================
_SKIP_TEX = ("/Tiles/", "/Masks/", "/Assets/Light/", "/Assets/Noise/",
             "/Assets/Particles/", "/Particles/", "/Assets/Buffs/",
             "/Assets/Background/", "/Assets/Shop/", "/Assets/Fonts/",
             # shader 辅助纹理：Pixel.png 只是 1x1 占位，被 Distortion 用
             # 「scale=270 + BackBufferCopy」做屏幕扭曲，静态合成会变成白块
             "/Assets/Pixel.png")


def is_icon_layer(node_path, res_path):
    """物品外观层判定。

    判定以**节点位置**为准（Icon 本身或 Icon 的子层），而不是贴图目录：
    多数物品主贴图在 Items/**/Sprites/，但也有物品（如 Fanfare）直接用
    Assets/Fanfare.png——按目录过滤会把它整件漏掉（缺失贴图的另一类成因）。
    """
    if not node_path or not res_path:
        return False
    if node_path != "Icon" and not node_path.startswith("Icon/"):
        return False
    return not any(seg in res_path for seg in _SKIP_TEX)


def collect_layers(nodes, tex_map):
    mats = {"": ID}
    for path, nd in sorted(nodes.items(), key=lambda kv: kv[1]["order"]):
        par = path.rsplit("/", 1)[0] if "/" in path else ""
        pm = _mat_to_root(par, nodes, mats)
        mats[path] = mat_mul(pm, mat_node(nd["props"]))

    layers = []
    for path, nd in sorted(nodes.items(), key=lambda kv: kv[1]["order"]):
        if nd["type"] not in ("Sprite", "Sprite2D"):
            continue
        p = nd["props"]
        if p.get("visible") == "false":
            continue
        # 注：show_behind_parent=true 是**正常**的层序属性（如 MagicRing 的宝石
        # 画在戒托之后），不能拿来过滤；真正要排除的是屏幕级 shader 辅助层，
        # 靠下面的夸张 scale 与 Pixel.png 黑名单处理。
        scale = _vec2(p.get("scale"), (1.0, 1.0))
        if abs(scale[0]) > 20 or abs(scale[1]) > 20:
            continue    # 夸张缩放 = 屏幕级效果层（如 270 倍扭曲），不参与静态合成
        res = tex_map.get(path)
        if not is_icon_layer(path, res):
            continue
        img_path = res_to_file(res)
        if img_path is None:
            continue
        try:
            img = Image.open(img_path).convert("RGBA")
        except Exception:
            continue
        layers.append({
            "name": path,
            "tex": res,
            "img": img,
            "m": mats.get(path, ID),
            "mod": _color(p.get("modulate")),
            "centered": p.get("centered", "true") != "false",
            "offset": _vec2(p.get("offset")),
            "flip_h": p.get("flip_h") == "true",
            "flip_v": p.get("flip_v") == "true",
            "region": (_rect(p.get("region_rect"))
                       if p.get("region_enabled") == "true" else None),
            "order": nd["order"],
        })
    return layers


def _mat_to_root(path, nodes, mats):
    if not path:
        return ID
    if path in mats:
        return mats[path]
    par = path.rsplit("/", 1)[0] if "/" in path else ""
    nd = nodes.get(path)
    if nd is None:
        return ID
    m = mat_mul(_mat_to_root(par, nodes, mats), mat_node(nd["props"]))
    mats[path] = m
    return m


def _layer_quad(ly):
    w, h = ly["img"].size
    if ly["region"]:
        w, h = int(round(ly["region"][2])), int(round(ly["region"][3]))
    if ly["centered"]:
        x0, y0 = -w / 2.0, -h / 2.0
    else:
        x0, y0 = 0.0, 0.0
    x0 += ly["offset"][0]
    y0 += ly["offset"][1]
    m = ly["m"]
    return [mat_apply(m, x0 + dx, y0 + dy)
            for dx, dy in ((0, 0), (w, 0), (0, h), (w, h))]


def _warp_layer(ly, minx, miny, W, H):
    img = ly["img"]
    if ly["region"]:
        rx, ry, rw, rh = [int(round(v)) for v in ly["region"]]
        rx, ry = max(0, rx), max(0, ry)
        img = img.crop((rx, ry, min(img.width, rx + rw), min(img.height, ry + rh)))
    if img.width <= 0 or img.height <= 0:
        return None
    if ly["flip_h"]:
        img = img.transpose(Image.FLIP_LEFT_RIGHT)
    if ly["flip_v"]:
        img = img.transpose(Image.FLIP_TOP_BOTTOM)
    w, h = img.size
    ox = (-w / 2.0 if ly["centered"] else 0.0) + ly["offset"][0]
    oy = (-h / 2.0 if ly["centered"] else 0.0) + ly["offset"][1]
    a, b, c, d, e, f = ly["m"]
    ex = e + a * ox + c * oy
    ey = f + b * ox + d * oy
    det = a * d - b * c
    if abs(det) < 1e-9:
        return None
    ia, ib = d / det, -b / det
    ic, id_ = -c / det, a / det
    dx, dy = ex - minx, ey - miny
    coeffs = (ia, ic, ia * (-dx) + ic * (-dy),
              ib, id_, ib * (-dx) + id_ * (-dy))
    warped = img.transform((W, H), Image.AFFINE, coeffs, resample=Image.BICUBIC)
    out = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    out.alpha_composite(warped)
    return out


def _apply_modulate(img, mod):
    arr = np.array(img, dtype=np.float32)
    arr[..., 0] *= mod[0]
    arr[..., 1] *= mod[1]
    arr[..., 2] *= mod[2]
    arr[..., 3] *= mod[3]
    return Image.fromarray(np.clip(arr, 0, 255).astype(np.uint8), "RGBA")


# ======================= 单物品 =======================
def build_item(path):
    text = path.read_text(encoding="utf-8", errors="replace")
    ext, raw_nodes = parse_tscn(text)
    root = next((n for n in raw_nodes if n["parent"] is None), None)
    if root is None:
        return None
    disp = root["name"]
    nodes, tex_map = expand_scene(path)
    if not nodes:
        return None
    layers = collect_layers(nodes, tex_map)
    if not layers:
        return None
    quads = [_layer_quad(ly) for ly in layers]
    xs = [p[0] for q in quads for p in q]
    ys = [p[1] for q in quads for p in q]
    pad = 1.5
    minx, maxx = min(xs) - pad, max(xs) + pad
    miny, maxy = min(ys) - pad, max(ys) + pad
    W = max(1, int(math.ceil(maxx - minx)))
    H = max(1, int(math.ceil(maxy - miny)))
    if W * H > 1400 * 1400:
        return None
    ox, oy = -minx, -miny
    canvas = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    meta = []
    for ly in layers:
        dst = _warp_layer(ly, minx, miny, W, H)
        if dst is None:
            continue
        if ly["mod"] != (1.0, 1.0, 1.0, 1.0):
            dst = _apply_modulate(dst, ly["mod"])
        canvas.alpha_composite(dst)
        a, b, c, d, e, f = ly["m"]
        meta.append({
            "tex": Path(ly["tex"]).stem,
            "x": round(e + ox, 2),
            "y": round(f + oy, 2),
            "rot": round(math.atan2(b, a), 4),
            "alpha": round(ly["mod"][3], 3),
        })
    # 根节点挂的脚本（res://.../Xxx.gd）：GUI 用它精确定位贴图。
    # 节点名会重名（护符们共用 Amulet Unidentified），脚本名却是唯一的。
    gd = ""
    for n in raw_nodes:
        if n["parent"] is None:
            m = re.search(r'^script = ExtResource\(\s*(\d+)\s*\)$',
                          n["body"], re.M)
            if m:
                gd = ext.get(m.group(1), "")
    return dict(display=disp, key=path.stem, canvas=canvas, gd=gd,
                origin=(ox, oy), size=(W, H), count=len(meta),
                layer_meta=meta)



# ======================= 占格 / 容器（tscn CollisionMap） =======================
def parse_tile_data(pool):
    """tile_data PoolIntArray：每 3 个 int 一组 (cell_id, tile_id, flip)。

    cell_id: 低 16 位 = x(有符号)，高 16 位 = y(有符号)。
    tile_id: 0=Slot(袋内槽位) 2=CantAdd 3=SlotPreview(实体占格) 4=Affected(效果区)
    """
    nums = [int(x) for x in re.findall(r'-?\d+', pool or '')]
    out = []
    for i in range(0, len(nums) - 2, 3):
        cid = nums[i] & 0xFFFFFFFF
        x = cid & 0xFFFF
        y = (cid >> 16) & 0xFFFF
        if x >= 0x8000:
            x -= 0x10000
        if y >= 0x8000:
            y -= 0x10000
        out.append((x, y, nums[i + 1] & 0xFFFF))
    return out


def scene_grid(nodes):
    """→ (cell_px, slot_px, is_bag)。cell_px 为占格左上角像素（相对物品原点）。"""
    cm = nodes.get("CollisionMap")
    cell_px, slot_px = [], []
    if cm is not None:
        p = cm["props"]
        pos = _vec2(p.get("position"))
        cells = parse_tile_data(p.get("tile_data"))
        for cx, cy, tid in cells:
            if tid in (2, 3):
                cell_px.append([cx * 80.0 + pos[0], cy * 80.0 + pos[1]])
            elif tid == 0:
                slot_px.append([cx * 80.0 + pos[0], cy * 80.0 + pos[1]])
    is_bag = any(k.startswith("Icon/") and v["type"] == "TileMap"
                 for k, v in nodes.items())
    return cell_px, slot_px, is_bag

# ======================= 别名 =======================
# 索引名(ItemBook CSV) → 场景文件名（不含扩展名）
#   Amulet of Agility：场景名为未鉴定护符，实际是敏捷护符的专属外观
_ALIAS_TO_KEY = {
    "Amulet of Agility": "AmuletofAgility",
    "Book of Ice New": "BookofIce",
}


# ======================= 主流程 =======================
def load_zh_map():
    """中文名：优先游戏内 Sheets/CSV/Full.csv（官方翻译真值），再叠旧库与补充表。"""
    out = {}
    csv = SRC_ROOT / ".assets" / "Sheets" / "CSV" / "Full.csv"
    if csv.exists():
        try:
            import csv as _csv
            with csv.open(encoding="utf-8-sig", newline="") as fp:
                rd = _csv.reader(fp)
                header = next(rd, None) or []
                try:
                    i_en = header.index("en")
                    i_zh = header.index("zh_Hans_CN")
                except ValueError:
                    i_en, i_zh = 1, 3
                for row in rd:
                    if len(row) > max(i_en, i_zh):
                        en, zh = row[i_en].strip(), row[i_zh].strip()
                        if en and zh:
                            out[en] = zh
        except Exception:
            pass
    for name in ("item_db.json", "item_zh_official.json",
                 "items_zh_official.json", "zh_pairs.json"):
        p = OUT_DIR / name
        if not p.exists():
            continue
        try:
            d = json.loads(p.read_text(encoding="utf-8"))
        except Exception:
            continue
        if not isinstance(d, dict):
            continue
        for k, v in d.items():
            if isinstance(v, str) and v:
                out.setdefault(k, v)
            elif isinstance(v, dict):
                if v.get("zh"):
                    out.setdefault(k, v["zh"])
                if v.get("key") and v.get("zh"):
                    out.setdefault(v["key"], v["zh"])
    return out


def main():
    SPRITE_DIR.mkdir(parents=True, exist_ok=True)
    src = SRC_ROOT if SRC_ROOT.exists() else FALLBACK_ROOT
    print("[*] 源:", src)
    old_db = {}
    p_old = OUT_DIR / "item_db.json"
    if p_old.exists():
        try:
            old_db = json.loads(p_old.read_text(encoding="utf-8"))
        except Exception:
            old_db = {}
    zh_map = load_zh_map()

    db = {}
    fails = []
    multi = 0
    for p in sorted(src.rglob("*.tscn")):
        try:
            text = p.read_text(encoding="utf-8", errors="replace")
        except Exception:
            continue
        if "res://Items/Item.tscn" not in text and "res://Items/Gems/Gem.tscn" not in text:
            continue
        # 基类场景本身不是物品（Gem 只是宝石的公共模板）
        if p.stem in _BASE_SCENES:
            continue
        try:
            item = build_item(p)
        except Exception as e:  # noqa: BLE001
            fails.append((p.name, repr(e)))
            continue
        if item is None:
            fails.append((p.name, "no layers"))
            continue
        key = item["key"]
        item["canvas"].save(SPRITE_DIR / (key + ".png"))
        name = item["display"]
        # 同名根节点（如 4 个护符场景都叫 Amulet Unidentified）不能互相覆盖：
        # 第一次用显示名，后续冲突者退回场景文件名当键，GUI 按脚本名也能查到。
        if name in db:
            name = key
        old = old_db.get(name) or {}
        nodes_all, _tm = expand_scene(p)
        cell_px, slot_px, is_bag = scene_grid(nodes_all)
        db[name] = {
            "key": key,
            "gd": item["gd"],
            "zh": zh_map.get(name) or zh_map.get(key) or old.get("zh") or "",
            "is_bag": bool(is_bag or old.get("is_bag")),
            "cell_px": cell_px or old.get("cell_px") or [],
            "slot_px": slot_px or old.get("slot_px") or [],
            "sprite": key + ".png",
            "img_w": item["size"][0],
            "img_h": item["size"][1],
            "origin_px": [round(item["origin"][0], 2), round(item["origin"][1], 2)],
            "layers": item["count"],
            "layer_meta": item["layer_meta"],
        }
        if item["count"] > 1:
            multi += 1
    # 别名字典：同一物品在不同来源里的名字（索引名 / 场景根名 / 旧库名）。
    # GUI 从内存读到的是**节点名**，而物品索引（ItemBook 表）用的是 CSV 名，
    # 两者偶尔不一致（Amulet Unidentified ↔ Amulet of Agility 等）。
    # 这里补一层别名，保证按索引名查询也能命中同一份合成贴图。
    by_key = {}
    for nm, ent in db.items():
        by_key.setdefault(ent.get("key"), nm)
    for alias, key in _ALIAS_TO_KEY.items():
        src = by_key.get(key)
        if src and alias not in db:
            e = dict(db[src])
            e["alias_of"] = src
            db[alias] = e

    p_old.write_text(json.dumps(db, ensure_ascii=False, indent=1), encoding="utf-8")
    print("[OK] 物品", len(db), "| 多层", multi, "| 失败", len(fails),
          "| 无中文", sum(1 for v in db.values() if not v["zh"]))
    for fn, err in fails[:12]:
        print("   [!]", fn, err)


if __name__ == "__main__":
    main()
