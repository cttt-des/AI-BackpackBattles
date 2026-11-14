# -*- coding: utf-8 -*-
"""export_lineups.py — 从训练报告导出最佳摆盘为 lineups/*.json（可被模拟器直接加载）

用法：
  python -I trainer/export_lineups.py trainer/p2_search_report.json
"""
from __future__ import annotations

import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

OUT_DIR = os.path.join(ROOT, "lineups")


def _safe_fn(s: str) -> str:
    """Windows 文件名清洗（: 是 NTFS 备用数据流分隔符，绝不能出现在文件名里）。"""
    for ch in r'<>:"/\|?*':
        s = s.replace(ch, "-")
    return s


def main(report_path: str):
    with open(report_path, encoding="utf-8") as f:
        rep = json.load(f)
    os.makedirs(OUT_DIR, exist_ok=True)
    n = 0
    for i, r in enumerate(rep.get("results", [])):
        lu = r.get("final_lineup")
        if not lu:
            continue
        lu = {k: v for k, v in lu.items() if not k.startswith("_")}
        base_tag = _safe_fn(os.path.basename(r.get("base", "base")).replace(".db", ""))
        lu["name"] = f"trained_{i}_{base_tag}_A{r.get('final_wr', 0):.3f}"
        out = os.path.join(OUT_DIR, f"{lu['name']}.json")
        with open(out, "w", encoding="utf-8") as f:
            json.dump(lu, f, ensure_ascii=False, indent=1)
        n += 1
        print(f"  {out}  (A wr={r.get('final_wr'):.3f}, "
              f"B {r.get('valB_final')}, C {r.get('valC_final')})")
    print(f"exported {n} lineups -> {OUT_DIR}")


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "trainer/p2_search_report.json")
