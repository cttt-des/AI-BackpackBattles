# -*- coding: utf-8 -*-
"""scan_item_deps.py — 统计 Items/*.gd 引用的外部符号

决定「原版物品脚本直挂 CoreItem」需要哪些转译规则：
  · 单例访问（Game. / Global. / Util. / ItemBook. / Sound. / Music. ...）
  · 引擎内建类（Node/Timer/Tween/Sprite/...）
  · 未限定标识符（枚举名、全局常量、class_name 引用）
"""
from __future__ import annotations

import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "decompiled_full", "Items")

# 引擎内建 / 已知外部
ENGINE = {
    "Node", "Node2D", "RigidBody2D", "Area2D", "Sprite", "Reference", "Object",
    "Timer", "Tween", "SceneTree", "Engine", "OS", "Input", "Resource",
    "PackedScene", "Image", "ImageTexture", "Label", "ColorRect", "Control",
    "AnimationPlayer", "Particles2D", "CPUParticles2D", "AudioStreamPlayer",
    "CollisionShape2D", "RectangleShape2D", "Sprite3D", "CanvasItem", "Texture",
    "Vector2", "Vector3", "Rect2", "Color", "Transform2D", "Basis", "Quat",
    "Array", "Dictionary", "String", "PoolStringArray", "PoolByteArray",
    "PoolIntArray", "PoolRealArray", "PoolVector2Array", "PoolColorArray",
    "File", "Directory", "JSON", "Marshalls", "RandomNumberGenerator",
    "Viewport", "WindowDialog", "Popup", "RichTextLabel", "TextureRect",
    "StreamTexture", "AtlasTexture", "DynamicFont", "Font", "Theme",
    "KinematicBody2D", "StaticBody2D", "PhysicsBody2D", "CanvasLayer",
    "ShaderMaterial", "Material", "Gradient", "Curve", "Path2D", "Line2D",
    "Polygon2D", "Light2D", "Camera2D", "VisibilityNotifier2D", "Groups",
    "Performance", "ProjectSettings", "Thread", "Mutex", "FuncRef", "WeakRef",
    "MainLoop", "SceneTreeTimer", "ReferenceRect", "NinePatchRect", "Button",
    "LineEdit", "ItemList", "Tree", "TabContainer", "VBoxContainer",
    "HBoxContainer", "GridContainer", "MarginContainer", "PanelContainer",
    "ScrollContainer", "Container", "Position2D", "YSort", "TileMap",
    "AnimationTree", "AnimationNodeStateMachine", "AudioStream",
    "AudioStreamSample", "AudioServer", "VisualServer", "Physics2DServer",
    "TriangleMesh", "CubeMesh", "Mesh", "MeshInstance",
}

CALL_RE = re.compile(r"(?<![\w.])([A-Z][A-Za-z0-9_]*)\s*\.")
IDENT_RE = re.compile(r"(?<![\w.\"'])([A-Z][A-Za-z0-9_]{2,})(?![\w(])")

# GDScript 关键字 / 内建函数 / 常见局部名
IGNORE = {
    "Vector2", "Vector3", "Color", "Rect2", "Transform2D", "Array", "Dictionary",
    "String", "Math", "PI", "TAU", "INF", "NAN", "OK", "FAILED", "TYPE_",
    "AABB", "Plane", "Quat", "Basis", "RID", "NodePath", "PoolByteArray",
}


def collect():
    out = {}
    for dirpath, _dirs, files in os.walk(SRC):
        for fn in files:
            if not fn.endswith(".gd"):
                continue
            path = os.path.join(dirpath, fn)
            rel = os.path.relpath(path, SRC).replace(os.sep, "/")
            with open(path, encoding="utf-8", errors="replace") as fh:
                out[rel] = fh.read()
    return out


def strip_comments_and_strings(body: str) -> str:
    body = re.sub(r"#[^\n]*", "", body)
    body = re.sub(r'"(?:[^"\\]|\\.)*"', '""', body)
    return body


def main() -> int:
    scr = collect()
    # 本工程内定义的 class_name（物品自己的，不算外部）
    local_cls = set()
    for rel, body in scr.items():
        for m in re.finditer(r"^class_name\s+([A-Za-z_]\w*)", body, re.M):
            local_cls.add(m.group(1))
    local_cls.add("Item")

    dots = collections.Counter()
    dots_by_file = collections.defaultdict(set)
    for rel, body in scr.items():
        if rel == "Item.gd":
            continue
        code = strip_comments_and_strings(body)
        for m in CALL_RE.finditer(code):
            name = m.group(1)
            if name in ENGINE or name in local_cls:
                continue
            dots[name] += 1
            dots_by_file[name].add(rel)

    print("=== 非引擎、非本地 class_name 的「大写名.」访问（前 40） ===")
    for k, v in dots.most_common(40):
        print("  %-28s %4d 次  出现在 %d 个文件" % (k, v, len(dots_by_file[k])))

    # 未限定的大写标识符（枚举名、全局常量）
    known = set(local_cls) | ENGINE | set(dots)
    bare = collections.Counter()
    bare_by_file = collections.defaultdict(set)
    for rel, body in scr.items():
        if rel == "Item.gd":
            continue
        code = strip_comments_and_strings(body)
        # 去掉 extends 行
        code = re.sub(r"^\s*extends[^\n]*", "", code, flags=re.M)
        for m in IDENT_RE.finditer(code):
            name = m.group(1)
            if name in known or name in IGNORE:
                continue
            bare[name] += 1
            bare_by_file[name].add(rel)

    print("\n=== 未限定的外部大写标识符（前 40） ===")
    for k, v in bare.most_common(40):
        print("  %-28s %4d 次  出现在 %d 个文件" % (k, v, len(bare_by_file[k])))

    # 汇总：每个脚本引用了多少种外部符号（决定转译难度）
    print("\n=== 单文件外部符号种类数分布 ===")
    per = collections.Counter()
    hard = []
    for rel, body in scr.items():
        if rel == "Item.gd":
            continue
        code = strip_comments_and_strings(body)
        code = re.sub(r"^\s*extends[^\n]*", "", code, flags=re.M)
        names = set()
        for m in CALL_RE.finditer(code):
            if m.group(1) not in ENGINE and m.group(1) not in local_cls:
                names.add(m.group(1))
        for m in IDENT_RE.finditer(code):
            n = m.group(1)
            if n not in known and n not in IGNORE:
                names.add(n)
        per[len(names)] += 1
        if len(names) >= 4:
            hard.append((len(names), rel, sorted(names)[:8]))
    for k in sorted(per):
        print("  引用 %2d 种：%d 个脚本" % (k, per[k]))
    hard.sort(reverse=True)
    print("\n=== 最难的 15 个脚本 ===")
    for n, rel, sample in hard[:15]:
        print("  %-40s %d 种  %s" % (rel, n, sample))
    print("\n合计需转译脚本：%d" % (len(scr) - 1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
