# -*- coding: utf-8 -*-
"""
构建《背包乱斗》物品知识图谱（KG）—— M0 数据层。

数据源：
  assets/battle_items.json   518 个物品（字段最全，见覆盖率统计）
  assets/characters.json     职业表（职业位序用于 classes 位掩码解码）

输出：
  assets/kg/items_kg.json    节点 + 边 + 边来源分级

边来源分级（schema 预留，对应架构文档 §5）：
  data   结构化字段直接抽取（本脚本产出）
  llm    LLM propose 的语义边（协同/克制），须模拟器 verify 后方可置 confidence
  stats  对局统计边（共现/胜率），由回放管线回填

M0 只产 data 边；CRAFTS_INTO / ADJACENT_SYNERGY / COUNTERS / CO_OCCURS
留空表并标注 TODO（配方散落在 CraftingManager.gd 逻辑里，需专项抽取）。
"""

import json
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ITEMS_JSON = ROOT / "assets" / "battle_items.json"
CHARS_JSON = ROOT / "assets" / "characters.json"
OUT_JSON = ROOT / "assets" / "kg" / "items_kg.json"

# classes 位掩码全 1 = 全职业可用（7 职业 → 127）
ALL_CLASSES_MASK = 0x7F

# KG 节点属性白名单（控制产物体积，行为脚本等大字段不进 KG）
ITEM_ATTRS = [
    "zh", "size", "category", "rarity", "price", "cd", "min_dam", "max_dam",
    "damage_type", "material", "accuracy", "crit", "stamina_cost", "block",
    "can_activate", "text_effect",
]


def load_json(path: Path) -> dict:
    with open(path, encoding="utf-8") as f:
        return json.load(f)


def build_nodes(items: dict, characters: list) -> tuple[list, list]:
    nodes, edges = [], []

    for key, it in items.items():
        attrs = {k: it.get(k) for k in ITEM_ATTRS if k in it}
        attrs["is_bag"] = it.get("category") == "bag"
        attrs["has_script"] = bool(it.get("script"))
        attrs["class_mask"] = it.get("classes", ALL_CLASSES_MASK)
        nodes.append({"id": f"item:{key}", "type": "item", "attrs": attrs})

        for t in it.get("types") or []:
            edges.append(("item", key, "SHARES_TYPE", "tag", t, "data", 1.0))
        for t in it.get("tags") or []:
            edges.append(("item", key, "HAS_TAG", "tag", t, "data", 1.0))
        for kw in (it.get("named_params") or {}).keys():
            edges.append(("item", key, "USES_KEYWORD", "keyword", kw, "data", 1.0))
        mat = it.get("material")
        if mat:
            edges.append(("item", key, "MADE_OF", "material", mat, "data", 1.0))

        # 职业专属：掩码不是全 1 且非 0 时，按位解码挂 EXCLUSIVE_TO 边
        mask = attrs["class_mask"]
        if mask not in (0, ALL_CLASSES_MASK):
            for idx, ch in enumerate(characters):
                if mask & (1 << idx):
                    edges.append(("item", key, "EXCLUSIVE_TO", "character", ch, "data", 1.0))

    for t in sorted({e[4] for e in edges if e[3] == "tag"}):
        nodes.append({"id": f"tag:{t}", "type": "tag", "attrs": {}})
    for kw in sorted({e[4] for e in edges if e[3] == "keyword"}):
        nodes.append({"id": f"keyword:{kw}", "type": "keyword", "attrs": {}})
    for m in sorted({e[4] for e in edges if e[3] == "material"}):
        nodes.append({"id": f"material:{m}", "type": "material", "attrs": {}})
    for ch in characters:
        nodes.append({"id": f"character:{ch}", "type": "character", "attrs": {}})

    return nodes, edges


def main() -> int:
    data = load_json(ITEMS_JSON)
    items = data["items"]

    # characters.json 结构防御式解析：list[str] 或 dict
    raw_chars = load_json(CHARS_JSON)
    if isinstance(raw_chars, dict):
        raw_chars = raw_chars.get("characters") or list(raw_chars.keys())
    characters = [c.get("name", str(c)) if isinstance(c, dict) else str(c) for c in raw_chars]

    nodes, raw_edges = build_nodes(items, characters)

    edges = [
        {
            "src": f"{st}:{sv}", "dst": f"{dt}:{dv}", "type": rel,
            "source": source, "confidence": conf,
        }
        for (st, sv, rel, dt, dv, source, conf) in raw_edges
    ]

    # 语义边占位（M0 留空，后续由 LLM propose / 回放 stats 回填）
    kg = {
        "meta": {
            "version": "m0",
            "game_version": "1.1.7",
            "item_count": len(items),
            "edge_sources": {"data": "字段直抽", "llm": "LLM propose + 模拟器 verify", "stats": "回放统计"},
            "todo": [
                "CRAFTS_INTO: 从 decompiled_full/Core/CraftingManager.gd + Sheets/CSV 抽取配方",
                "ADJACENT_SYNERGY: LLM 初标 + 模拟器共置实验 verify",
                "COUNTERS: LLM propose + 模拟器 verify（置信度起步低）",
                "CO_OCCURS: 自博弈回放统计（lift / 交互胜率差），带时间窗",
            ],
        },
        "nodes": nodes,
        "edges": edges,
        "semantic_edges": {"CRAFTS_INTO": [], "ADJACENT_SYNERGY": [], "COUNTERS": [], "CO_OCCURS": []},
    }

    OUT_JSON.parent.mkdir(parents=True, exist_ok=True)
    with open(OUT_JSON, "w", encoding="utf-8") as f:
        json.dump(kg, f, ensure_ascii=False, indent=1)

    # 统计输出
    node_types = Counter(n["type"] for n in nodes)
    edge_types = Counter(e["type"] for e in edges)
    print(f"物品: {len(items)}  职业: {len(characters)}")
    print(f"节点 {len(nodes)}: {dict(node_types)}")
    print(f"边   {len(edges)}: {dict(edge_types)}")
    top_kw = Counter(e["dst"] for e in edges if e["type"] == "USES_KEYWORD").most_common(8)
    print("高频 keyword:", top_kw)
    print(f"输出: {OUT_JSON}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
