#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""enrich_flicker_animation.py — 把「物品场景内 FlickerAnimation 子节点」写进
battle_items.json（阶段2 装配期对齐，docs/alignment_fix_workflow.md §2）

缺口（本会话 oracle/oracle_stage_probe.gd 实测，run1029_r2 的逐件链态差分）：
  物品场景内挂 Items/Animations/FlickerAnimation.gd 的 AnimationPlayer 子节点时
  （1.1.8 运行版反编译树共 9 个场景），物品入树（_ready）即消耗链 2 抽
  （FlickerAnimation.gd:13-15：Util.callDelayed 的 randf_range(minDist,maxDist)
  实参求值），战斗期到点 playAni 再消耗 2 抽（:17-19 randf_range(minSpeed,
  maxSpeed)）。内核此前完全无此消耗面。

产出：battle_items.json 每件物品追加
  flicker_animation                bool（场景有 FlickerAnimation 子节点）
  flicker_min_dist / flicker_max_dist    float（默认 0.1 / 3.0，FlickerAnimation.gd:4-5）
  flicker_min_speed / flicker_max_speed  float（默认 0.3 / 1.0，:6-7）
  connector_ready_roll             bool（_ready 抽 randf_range(0.9,1.1)：types 含
                                   potion 的物品经 Potion._ready 动态挂
                                   PotionConnector（Potion.gd:22-28）；场景内嵌
                                   CardConnector.tscn 的卡牌物品（Ace of Spades/
                                   Darkest Lotus/Deck of Cards/Joker/Reverse/
                                   Holo Fire Lizard/The Fool）——两者 _ready 均
                                   modulate.g = randf_range(0.9,1.1)，各 +2 步）
  gem_roll                         bool（types 含 gem：Gem._ready →
                                   gemAnimation.advance(randf_range(0,10))，
                                   Gem.gd:24，+2 步）
边界值按各 .tscn 节点导出属性覆盖解析（实测仅 Flame 与 BurningSword 覆盖）。

用法：
  python tools/enrich_flicker_animation.py            # 写入（幂等）
  python tools/enrich_flicker_animation.py --check    # 只校验
"""
from __future__ import annotations

import io
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
# 与 enrich_animation_scene.py 同源的探测根（1.1.8 运行版反编译树）
ITEMS_ROOT = os.path.join(ROOT, "extracted_running", "decomp", "Items")
FLICKER_SCRIPT = "res://Items/Animations/FlickerAnimation.gd"

# 全部物品场景的 <name>.tscn 索引（大小写敏感，name = 文件名去扩展名）
_SCENES: dict = {}


def _scene_index() -> dict:
    global _SCENES
    if not _SCENES:
        for dp, _dn, fn in os.walk(ITEMS_ROOT):
            for f in fn:
                if f.endswith(".tscn"):
                    _SCENES.setdefault(os.path.splitext(f)[0], []).append(
                        os.path.join(dp, f))
    return _SCENES


def _parse_flicker(scene_path: str):
    """场景含 FlickerAnimation 子节点 → (True, minDist, maxDist, minSpeed, maxSpeed)。
    边界值取该子节点块的导出属性覆盖；无覆盖用 FlickerAnimation.gd:3-7 默认。"""
    txt = io.open(scene_path, encoding="utf-8", errors="replace").read()
    ext = dict((i, path) for path, i in re.findall(
        r'\[ext_resource path="(res://[^"]+)" type="Script" id=(\d+)\]', txt))
    flicker_ids = {i for i, p in ext.items() if p == FLICKER_SCRIPT}
    if not flicker_ids:
        return None
    hits = []
    for m in re.finditer(r'\[node name="[^"]*"[^\]]*\]', txt):
        block_end = txt.find("\n[", m.end())
        block = txt[m.end(): block_end if block_end != -1 else len(txt)]
        sm = re.search(r'script = ExtResource\( (\d+) \)', block)
        if sm and sm.group(1) in flicker_ids:
            props = dict(re.findall(r'^(\w+) = ([^\n]+)$', block, re.M))
            hits.append(props)
    if not hits:
        return None
    # 多个 Flicker 子节点取首个（实测 9 个场景均恰 1 个；多于 1 个时 fail-fast）
    if len(hits) > 1:
        raise SystemExit("%s 有 %d 个 FlickerAnimation 子节点（模型假设恰 1 个，"
                         "请先核对再放宽）" % (scene_path, len(hits)))
    p = hits[0]

    def _f(key, default):
        v = p.get(key)
        return float(v) if v is not None else float(default)

    return (True, _f("minDist", 0.1), _f("maxDist", 3.0),
            _f("minSpeed", 0.3), _f("maxSpeed", 1.0))


def flicker_of(key: str):
    """物品标识 → 场景解析结果。场景缺失（不可装配内部件等）→ None。"""
    name = key.replace(" ", "")
    for scene in _scene_index().get(name, []):
        parsed = _parse_flicker(scene)
        if parsed is not None:
            return parsed
    return None


# 场景内嵌 CardConnector.tscn 的物品（Items/**.tscn 逐文件 grep，本会话枚举）
CARD_CONNECTOR_SCENES = {
    "Ace of Spades", "Darkest Lotus", "Deck of Cards", "Joker", "Reverse",
    "Holo Fire Lizard", "The Fool",
}


def extra_ready_flags(key: str, entry: dict) -> dict:
    types = set(entry.get("types") or [])
    return {
        "connector_ready_roll": bool(types & {"potion"})
        or key in CARD_CONNECTOR_SCENES,
        "gem_roll": "gem" in types,
    }


def main() -> int:
    check_only = "--check" in sys.argv
    db = json.load(io.open(DB_PATH, encoding="utf-8"))
    changed = 0
    n_flicker = 0
    for key, entry in sorted(db["items"].items()):
        parsed = flicker_of(key)
        if parsed is None:
            want = {"flicker_animation": False}
        else:
            _, d0, d1, s0, s1 = parsed
            want = {"flicker_animation": True,
                    "flicker_min_dist": d0, "flicker_max_dist": d1,
                    "flicker_min_speed": s0, "flicker_max_speed": s1}
        want.update(extra_ready_flags(key, entry))
        if want["flicker_animation"]:
            n_flicker += 1
        cur = {k: entry.get(k) for k in want}
        normalized_cur = dict(cur)
        if isinstance(normalized_cur.get("flicker_animation"), bool) is False and \
                normalized_cur.get("flicker_animation") is not None:
            normalized_cur["flicker_animation"] = bool(
                normalized_cur["flicker_animation"])
        if cur != want and normalized_cur != want:
            entry.update(want)
            changed += 1
        elif not isinstance(entry.get("flicker_animation"), bool):
            entry["flicker_animation"] = bool(entry.get("flicker_animation"))
            changed += 1
    names = sorted(k for k, e in db["items"].items()
                   if e.get("flicker_animation"))
    print("FlickerAnimation：%d / %d 件物品场景带该子节点 %s；需更新 %d 件"
          % (n_flicker, len(db["items"]), names, changed))
    if check_only:
        return 1 if changed else 0
    if changed:
        with io.open(DB_PATH, "w", encoding="utf-8", newline="\n") as fh:
            json.dump(db, fh, ensure_ascii=False, indent=1)
            fh.write("\n")
        print("battle_items.json 已同步")
    else:
        print("battle_items.json 已同步")
    return 0


if __name__ == "__main__":
    sys.exit(main())
