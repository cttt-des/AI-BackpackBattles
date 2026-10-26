# -*- coding: utf-8 -*-
"""enrich_oracle_params.py — battle_items.json 战斗参数面同步到 oracle 语料版 CSV

背景（np23 data_r1）
====================
battle_items.json 的参数生产链源自 decompiled_full/Sheets/CSV/ItemData_e.csv
（反编译版本），而新语料由 oracle 1.1.9 工程录制，其物品表为
oracle/Sheets/CSV/ItemData.csv。两份 CSV 列结构全等、行集仅差 oracle 多
"Time Pendant"（语料 lineups 零引用），但有 53 行的战斗参数列存在版本差
（铁证：Snake p3 40:maxhealth vs 38:maxhealth → run584/591 TMH 80/160 vs
76/152；Katana cd 1.7 vs 1.5；Onion Cutter 12:speed vs 15:speed …）。
双核（gd_core / gd_core_py）共读同一份数据，故 py≡gd 一起偏。

修复方式（外科手术，非全量重建）
================================
只对「两 CSV 同名列不一致」的物品、且只对不一致的列落笔：
  cd / minDam / maxDam / block / staminaCost / chance / chance2 / p1..p10
    * p 列按 ItemBook.gd:855-875 语义解析（逗号格=多具名参数）：
        - positional params[i]（battle_items 惯例：每列一槽=首段值，空列 0）
        - named_params：删该列旧段名、按 oracle 段序写入新段名
    * cd 列按 ItemBook.gd:821-826 逗号拆分：首段=cd，其余=extra_cds
    * chance/chance2 存原始串（parse_chance 消费前导浮点，'40:manadup'→40.0；
      manadup 名部经全仓 grep 无任何 getP_m 消费者，仅数值生效）
每格写入前先**对账**：该列 _e 侧解析值必须与 battle_items 当前值一致
（浮点相等），对不上即中止不写库——保证唯一的 delta 来自 oracle 版本差，
不会覆盖其它 enrich 工具的手工修正。

不碰：shopChance（Furcifer Prime 唯一差异列；shop 生成面，battle_items 无
此字段）、gain/use/remove（enrich_stack_flags.py 专职，且两 CSV 该三列全等）、
两 CSV 一致的行（battle_items 可能带 align_item_params 等手工修正，全量重建
会误伤）。

改完须重生成：
    python tools/gen_gd_core_data.py      # assets/gd_core_runtime.json（py 侧）
    python tools/gen_lineup_fixture.py    # gd_core_test/item_battle_fixture.json（gd 侧）

用法：
  python tools/enrich_oracle_params.py            # 写库（自动 .bak 备份）
  python tools/enrich_oracle_params.py --check    # 只报告差异计划与对账结果
"""
from __future__ import annotations

import csv
import json
import os
import re
import shutil
import sys
from datetime import datetime

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
E_CSV = os.path.join(ROOT, "decompiled_full", "Sheets", "CSV", "ItemData_e.csv")
O_CSV = os.path.join(ROOT, "oracle", "Sheets", "CSV", "ItemData.csv")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

P_COLS = ["p%d" % i for i in range(1, 11)]
INT_COLS = {"minDam": "min_dam", "maxDam": "max_dam", "block": "block"}
FLOAT_COLS = {"staminaCost": "stamina_cost"}
CHANCE_COLS = {"chance": "csv_chance", "chance2": "csv_chance2"}


def _f(x: float) -> float:
    return float(x)


def _feq(a, b) -> bool:
    return abs(float(a) - float(b)) < 1e-9


def parse_p_cell(cell: str):
    """ItemBook.gd:855-875：逗号格=多段 (值,名)；空格=None；裸值=（值,''）。"""
    cell = (cell or "").strip()
    if cell == "":
        return None
    out = []
    if "," in cell:
        for seg in cell.split(","):
            parts = seg.split(":")
            out.append((float(parts[0]), parts[1] if len(parts) > 1 else ""))
    else:
        parts = cell.split(":")
        out.append((float(parts[0]), parts[1] if len(parts) > 1 else ""))
    return out


def parse_cd_cell(cell: str):
    """ItemBook.gd:821-826：逗号拆分，首段 cd 其余 extraCds；空列=无值。"""
    cell = (cell or "").replace(" ", "")
    if cell == "":
        return None
    return [float(x) for x in cell.split(",") if x != ""]


def lead_float(raw) -> float:
    """gen_lineup_fixture.parse_chance 同口径：前导数字。"""
    m = re.match(r"[-+]?\d*\.?\d+", str(raw or "").strip())
    return float(m.group(0)) if m else 0.0


def load_csv(path: str) -> dict:
    with open(path, encoding="utf-8-sig") as f:
        return {r["name"]: r for r in csv.DictReader(f)}


def sync_item(key: str, entry: dict, re_: dict, ro: dict, log: list) -> bool:
    """对单个物品做外科同步。返回是否有写入。对账失败抛 SystemExit。"""
    touched = False

    # ---- p1..p10：params 槽 + named_params ----
    np_ = entry.setdefault("named_params", {})
    params = entry["params"]
    if len(params) != 10:
        raise SystemExit("%s：battle_items params 长度 %d≠10，先跑 align_item_params"
                         % (key, len(params)))
    for i, col in enumerate(P_COLS):
        ce, co = (re_.get(col) or "").strip(), (ro.get(col) or "").strip()
        if ce == co:
            continue
        pe, po = parse_p_cell(ce), parse_p_cell(co)
        # 对账：_e 侧解析 == 当前库值
        want_slot = pe[0][0] if pe else 0.0
        if not _feq(params[i], want_slot):
            raise SystemExit(
                "%s.%s：当前 params[%d]=%r 与 _e 解析 %r 不符（拒绝盲写）"
                % (key, col, i, params[i], want_slot))
        for val, name in (pe or []):
            if name and (name not in np_ or not _feq(np_[name], val)):
                raise SystemExit(
                    "%s.%s：当前 named_params[%r]=%r 与 _e 段 %r 不符（拒绝盲写）"
                    % (key, col, name, np_.get(name), (val, name)))
        # 写入
        params[i] = _f(po[0][0]) if po else 0.0
        o_names = {name for _v, name in (po or [])}
        for _val, name in (pe or []):
            if name and name not in o_names:
                np_.pop(name, None)
        for val, name in (po or []):
            if name:
                np_[name] = _f(val)
        log.append("  %s.%s: %r → %r" % (key, col, ce, co))
        touched = True

    # ---- cd（+extra_cds）----
    if (re_.get("cd") or "") != (ro.get("cd") or ""):
        cde, cdo = parse_cd_cell(re_.get("cd")), parse_cd_cell(ro.get("cd"))
        cur = [_f(entry.get("cd") or 0.0)] + [
            _f(x) for x in (entry.get("extra_cds") or [])]
        if cde is None:
            if not _feq(entry.get("cd") or 0.0, 0.0) or (entry.get("extra_cds") or []):
                raise SystemExit("%s.cd：当前值 %r 与 _e 空列不符（拒绝盲写）"
                                 % (key, cur))
        elif len(cde) != len(cur) or any(not _feq(a, b) for a, b in zip(cde, cur)):
            raise SystemExit("%s.cd：当前值 %r 与 _e 解析 %r 不符（拒绝盲写）"
                             % (key, cur, cde))
        if cdo is None:
            entry["cd"], entry["extra_cds"] = 0.0, []
        else:
            entry["cd"] = _f(cdo[0])
            entry["extra_cds"] = [_f(x) for x in cdo[1:]]
        log.append("  %s.cd: %r → %r" % (key, re_.get("cd"), ro.get("cd")))
        touched = True

    # ---- 整数列 / 浮点列 ----
    for col, field in INT_COLS.items():
        ve, vo = (re_.get(col) or "").strip(), (ro.get(col) or "").strip()
        if ve == vo:
            continue
        if int(entry.get(field) or 0) != int(float(ve or 0)):
            raise SystemExit("%s.%s：当前 %r 与 _e %r 不符（拒绝盲写）"
                             % (key, col, entry.get(field), ve))
        entry[field] = int(float(vo or 0))
        log.append("  %s.%s: %r → %r" % (key, col, ve, vo))
        touched = True
    for col, field in FLOAT_COLS.items():
        ve, vo = (re_.get(col) or "").strip(), (ro.get(col) or "").strip()
        if ve == vo:
            continue
        if not _feq(entry.get(field) or 0.0, float(ve or 0)):
            raise SystemExit("%s.%s：当前 %r 与 _e %r 不符（拒绝盲写）"
                             % (key, col, entry.get(field), ve))
        entry[field] = _f(float(vo or 0))
        log.append("  %s.%s: %r → %r" % (key, col, ve, vo))
        touched = True

    # ---- chance/chance2：原始串（名部无消费者，仅前导浮点生效）----
    for col, field in CHANCE_COLS.items():
        ve, vo = (re_.get(col) or "").strip(), (ro.get(col) or "").strip()
        if ve == vo:
            continue
        if not _feq(lead_float(entry.get(field)), lead_float(ve)):
            raise SystemExit("%s.%s：当前 %r 与 _e %r 不符（拒绝盲写）"
                             % (key, col, entry.get(field), ve))
        entry[field] = vo
        log.append("  %s.%s: %r → %r" % (key, col, ve, vo))
        touched = True

    return touched


def main() -> int:
    check_only = "--check" in sys.argv
    e_rows, o_rows = load_csv(E_CSV), load_csv(O_CSV)
    print("ItemData_e.csv %d 行 / oracle ItemData.csv %d 行" % (len(e_rows), len(o_rows)))
    only_o = sorted(set(o_rows) - set(e_rows))
    if only_o:
        print("oracle 独有行（不在同步范围）：%s" % ", ".join(only_o))

    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)

    log, n_items = [], 0
    skipped = []
    for key in sorted(items):
        if key not in e_rows or key not in o_rows:
            skipped.append(key)
            continue
        row_log = []
        if sync_item(key, items[key], e_rows[key], o_rows[key], row_log):
            n_items += 1
            log.extend(row_log)
    print("\n".join(log))
    print("同步物品 %d 件 / 落笔格 %d 处 / CSV 缺行跳过 %d 件"
          % (n_items, len(log), len(skipped)))

    if check_only:
        print("ENRICH_ORACLE_PARAMS: CHECK-ONLY")
        return 0
    if n_items:
        stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        shutil.copy2(DB_PATH, "%s.bak_%s" % (DB_PATH, stamp))
        json.dump(db, open(DB_PATH, "w", encoding="utf-8"),
                  ensure_ascii=False, indent=1)
        print("已写出 %s（备份 .bak_%s）" % (DB_PATH, stamp))
    else:
        print("无变更，不写库")
    return 0


if __name__ == "__main__":
    sys.exit(main())
