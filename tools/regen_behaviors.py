# -*- coding: utf-8 -*-
"""regen_behaviors.py — 用修复后的 transpile 规则从完整解密源码重新生成所有物品 behavior。
保留其他字段(effects/triggers/on_start/csv)，仅覆盖 behavior。
"""
import json, os, sys
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import simulator.extract_items as E

DB = os.path.join(os.path.dirname(__file__), "..", "assets", "battle_items.json")

def main():
    db = json.load(open(DB, encoding="utf-8"))
    items = db.get("items", db)
    idx = E.scan_scripts()
    print("script index:", len(idx))
    # 共享祖先条目缓存：基类（Item/Weapon/Bag…）条目只解析一次，
    # 结果与逐物品独立解析完全一致（条目只由脚本本身决定）
    shared_ancestors = {}
    matched = 0
    skipped = 0
    for key in items:
        scr = items[key].get("script")
        sp = None
        if scr:
            norm = scr[:-3].lower().replace(" ", "") if scr.endswith(".gd") else scr.lower().replace(" ", "")
            sp = idx.get(norm)
        if sp is None:
            sp = E.match_script_key(key, idx)
        if sp is None:
            skipped += 1
            continue
        try:
            beh = E.build_behavior(sp, ancestor_entries=shared_ancestors)
        except Exception as e:
            print("PARSE ERR", key, e)
            continue
        if beh["methods"] or beh["methods_raw"]:
            # 浅拷贝：条目可能来自共享缓存（同名脚本的多个品质变体），
            # script_file 的写入不得影响其他物品
            items[key]["behavior"] = dict(beh)
            items[key]["behavior"]["script_file"] = os.path.basename(sp)
            matched += 1
    print("matched(wrote behavior):", matched, "skipped(no script):", skipped)
    n_raw = sum(1 for v in items.values() if v.get("behavior", {}).get("methods_raw"))
    n_meth = sum(1 for v in items.values() if v.get("behavior", {}).get("methods"))
    total_meth = sum(len(v.get("behavior", {}).get("methods", {})) for v in items.values() if v.get("behavior"))
    total_raw = sum(len(v.get("behavior", {}).get("methods_raw", {})) for v in items.values() if v.get("behavior"))
    print("AFTER: items w/ methods=", n_meth, " w/ raw=", n_raw,
          " total compiled methods=", total_meth, " total raw methods=", total_raw)
    json.dump(db, open(DB, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    print("written", DB)

if __name__ == "__main__":
    main()
