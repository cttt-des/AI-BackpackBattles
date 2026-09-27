#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
gen_test_project.py — 从 gd_core/ 自动生成无头测试工程的 class_name 注册表

为什么要这个工具：
  Godot 3 的 `_global_script_classes` 缓存写在 project.godot 里，手工维护极易漏项。
  漏项的典型症状是 `Parse Error: The identifier "CoreXxx" isn't declared in the
  current scope.` —— 但脚本本身没问题。本工具扫描 gd_core/*.gd 里带 class_name 的
  脚本，重写 gd_core_test/project.godot 的注册表与图标表，消除这类漂移。

用法：
    python tools/gen_test_project.py           # 就地重写
    python tools/gen_test_project.py --check   # 只校验，不同步（CI/闸门用）
"""
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GD_CORE = os.path.join(ROOT, "gd_core")
GD_CORE_ITEMS = os.path.join(ROOT, "gd_core_items")
GD_CORE_TEST = os.path.join(ROOT, "gd_core_test")
PROJECT = os.path.join(ROOT, "gd_core_test", "project.godot")

CLASS_RE = re.compile(r'^class_name\s+([A-Za-z_]\w*)', re.M)
EXTENDS_RE = re.compile(r'^extends\s+([A-Za-z_]\w*)', re.M)


def scan():
    """返回 [(class_name, base, res_path)]，按 class_name 排序。

    扫三处：gd_core/（内核）、gd_core_items/（原版物品行为脚本转译产物）、
    gd_core_test/（测试工程自身的 class_name，如由 gen_lineup_fixture.py 生成的
    LineupFixture）。第二处里带 class_name 的是中间基类
    （Item / Weapon / Food / Bag / Gem …），子类 `extends Weapon` 靠这些注册解析。
    """
    out = []
    # 第三个元素 top_only：gd_core_test/ 里放的是**目录联接**（gd_core、gd_core_items），
    # 在 Windows 上 os.path.islink() 对 mklink /D 建的联接不一定返回 True，
    # os.walk 于是会再走一遍那两个目录，导致同一 class_name 被注册两次
    # （res 路径还各不相同）。故测试工程这一层只取顶层文件。
    for base_dir, res_prefix, top_only in ((GD_CORE, "res://gd_core/", False),
                                           (GD_CORE_ITEMS, "res://gd_core_items/", False),
                                           (GD_CORE_TEST, "res://", True)):
        if not os.path.isdir(base_dir):
            continue
        if top_only:
            walker = [(base_dir, [], [f for f in os.listdir(base_dir)
                                      if os.path.isfile(os.path.join(base_dir, f))])]
        else:
            walker = os.walk(base_dir)
        for dirpath, _dirs, files in walker:
            for fn in sorted(files):
                if not fn.endswith(".gd"):
                    continue
                full = os.path.join(dirpath, fn)
                src = io.open(full, encoding="utf-8", errors="replace").read()
                m = CLASS_RE.search(src)
                if not m:
                    continue
                cls = m.group(1)
                e = EXTENDS_RE.search(src)
                base = e.group(1) if e else "Reference"
                rel = os.path.relpath(full, base_dir).replace(os.sep, "/")
                out.append((cls, base, res_prefix + rel))
    out.sort(key=lambda t: t[0])
    return out


def render(entries):
    blocks = []
    for cls, base, path in entries:
        blocks.append('{\n"base": "%s",\n"class": "%s",\n"language": "GDScript",\n'
                      '"path": "%s"\n}' % (base, cls, path))
    icons = ",\n".join('"%s": ""' % c for c, _, _ in entries)
    return ("_global_script_classes=[ " + ", ".join(blocks) + " ]\n"
            "_global_script_class_icons={\n" + icons + "\n}\n")


TEMPLATE = """; Engine configuration file.
; It's best edited using the editor UI and not directly,
; since the parameters that go here are not all obvious.
;
; Format:
;   [section] ; section goes between []
;   param=value ; assign values to parameters
;
; ★ 本文件的 _global_script_classes 由 tools/gen_test_project.py 自动生成，
;   请勿手工维护 —— 漏注册 class_name 会报
;   `The identifier "CoreXxx" isn't declared in the current scope.`

config_version=4

%s
[application]

config/name="gd_core smoke"
run/main_scene="res://Smoke.tscn"
"""


def main():
    check = "--check" in sys.argv
    entries = scan()
    if not entries:
        print("[错误] gd_core/ 下未找到任何 class_name 脚本")
        return 1

    names = [c for c, _, _ in entries]
    old = ""
    if os.path.exists(PROJECT):
        old = io.open(PROJECT, encoding="utf-8").read()
    old_names = sorted(re.findall(r'^"class": "(\w+)"', old, re.M))

    if old_names == names and not check:
        # 内容一致（成员相同）也要确认顺序/路径无漂移，故照常重写
        pass

    if check:
        if old_names == names:
            print("project.godot class_name 注册表一致（%d 个）：%s"
                  % (len(names), ", ".join(names)))
            return 0
        miss = [n for n in names if n not in old_names]
        extra = [n for n in old_names if n not in names]
        print("[不一致] 缺少 %s / 多余 %s" % (miss or "无", extra or "无"))
        print("         请运行 python tools/gen_test_project.py 同步")
        return 1

    with io.open(PROJECT, "w", encoding="utf-8", newline="\n") as f:
        f.write(TEMPLATE % render(entries))
    print("已重写 gd_core_test/project.godot，注册 %d 个 class_name：" % len(names))
    print("  " + ", ".join(names))
    return 0


if __name__ == "__main__":
    sys.exit(main())
