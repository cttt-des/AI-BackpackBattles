#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
enrich_scene_depth.py — 场景绑定深度（chanceRng 构造调用次数）写进 battle_items.json

依据（1.1.8 反编译源码 + run634_r18 逐抽归属实证）：
  * Item.gd:472 `var chanceRng = BalancedRng.new()` —— 每次脚本绑定跑 1 次
    （1 个 rng_log 行 = randf_range(0.2,-0.2)）；
  * 场景链 tscn1 instances tscn2 → 脚本覆盖重绑定 → 成员初始化器**整链重跑**：
    Item.tscn(Item.gd)=1 抽；X.tscn→Item.tscn=2 抽；Wisp.tscn→Gem.tscn→Item.tscn=3 抽。
  * 实证：oracle_fight [ASM] 逐实例标记 + rng_log 行号对位——Wisp gem ctor 消耗
    3 行（draws 110-112），内核固定 2 行 ⇒ 自 draw112 起全链错位（Kernel 早期
    「4 步/实例」模型=2 抽×2 PCG 步，普通件正确、三层件少 1 抽）。
  * 深度≠2 的 34 件 = 宝石 tiers（Ruby/Sapphire/Emerald/Topaz/Amethyst 五阶）、
    Lump of Coal/Burning Coal/Corrupted Crystal/Skull、四符文（Badger/Elephant/
    Hawk/Tiger）、Wisp（均为 Gem.tscn→Item.tscn 之上的第三层覆盖）。

用法：python -X utf8 tools/enrich_scene_depth.py [--root decompiled_full] [--dry-run]
写入：assets/battle_items.json 各物品条目 "scene_depth"（缺省 2，不写默认值）。
"""
from __future__ import annotations

import argparse
import io
import json
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")


def build_name_map(src_root):
    name2path = {}
    items_dir = os.path.join(src_root, "Items")
    for dirpath, _, files in os.walk(items_dir):
        for f in files:
            if f.endswith(".tscn"):
                # 场景文件名不含空格（"Cog Badge"→CogBadge.tscn），两种键都收
                name2path.setdefault(f[:-5], os.path.join(dirpath, f))
                name2path.setdefault(f[:-5].replace(" ", ""), os.path.join(dirpath, f))
    return name2path


def main() -> int:
    ap = argparse.ArgumentParser(description="场景绑定深度提取")
    ap.add_argument("--root", default=os.path.join(ROOT, "decompiled_full"))
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    name2path = build_name_map(args.root)
    memo = {}

    def base_scene(path):
        """返回 (基场景路径, 根节点是否覆盖脚本)。深度语义 = 脚本重绑定次数：
        继承场景只有当根节点写了 `script = ExtResource(n)`（覆盖基场景根脚本）
        时，成员初始化器才在该层重跑一遍（+1）；无覆盖（如 Coins.tscn 只换
        贴图/粒子）则沿用基脚本绑定，不加层。

        ★ A 阶段普适性修复（2026-11-14，run101354_r14 oracle [BARE]+[ITEMINIT]
        逐抽实证）：Coins 装配期只抽 1 笔 ctor（Item.gd 单绑定），旧模型按
        场景嵌套深度恒记 2 ⇒ py/gd 内核每件 Coins 多抽 1 笔（2 PCG 步），
        装配链位整体后移，flicker delay 抽值错位（20 场 flk_delay 开关的根因）。
        """
        txt = io.open(path, encoding="utf-8", errors="replace").read()
        ext = {}
        for m in re.finditer(r'\[ext_resource path="([^"]+)" type="PackedScene" id=(\d+)\]', txt):
            ext[m.group(2)] = m.group(1)
        m = re.search(r'\[node name=[^\]]+ instance=ExtResource\( ?(\d+) ?\)\]', txt)
        if not m:
            return None, False
        base = ext.get(m.group(1))
        # 根节点段 = 第一个 node 声明到下一个 node 之间
        seg_end = txt.find("[node", m.end())
        seg = txt[m.start():seg_end if seg_end > 0 else len(txt)]
        overridden = re.search(r'script = ExtResource\( ?(\d+) ?\)', seg) is not None
        return base, overridden

    def depth(path):
        if path in memo:
            return memo[path]
        memo[path] = 1
        d = 1
        b, overridden = base_scene(path)
        if b:
            rp = os.path.join(args.root, b.replace("res://", ""))
            if os.path.exists(rp):
                d = (1 if overridden else 0) + depth(rp)
        memo[path] = d
        return d

    db = json.load(io.open(DB_PATH, encoding="utf-8"))
    items = db["items"]
    from collections import Counter
    cnt = Counter()
    changed = 0
    for k, it in items.items():
        p = name2path.get(k) or name2path.get(k.replace(" ", ""))
        if not p:
            cnt["no-scene"] += 1
            continue
        d = depth(p)
        cnt[d] += 1
        want = d if d != 2 else None   # 2 为缺省语义，不落盘
        have = it.get("scene_depth")
        if want != have:
            if want is None:
                it.pop("scene_depth", None)
            else:
                it["scene_depth"] = want
            changed += 1
    print("[scan] 深度分布：%s" % dict(cnt))
    if args.dry_run:
        print("[dry-run] 将变更 %d 件" % changed)
        return 0
    with io.open(DB_PATH, "w", encoding="utf-8", newline="\n") as fh:
        json.dump(db, fh, ensure_ascii=False, indent=1)
        fh.write("\n")
    print("[write] %s：变更 %d 件" % (DB_PATH, changed))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
