# -*- coding: utf-8 -*-
"""align_item_params.py — 把 assets/battle_items.json 的 `params` 校正为**列对齐**

背景
----
原版 `ItemBook.gd:855-875` 对 p1..p10 **每一列**取值并 push_back（空列 push 默认
0），故 `ItemDescriptor.params` 长度恒为 `NUM_PARAMS = 10`，且 `params[i]` 恒等于
第 (i+1) 列 —— `getP1() = params[0]` … `getP10() = params[9]`。

早先的提取**跳过空列**（紧凑数组），于是「前面有空列」的物品 `getP1..getP10`
整体错位。实测（见 tools/item_sheet.py 的对照表）：

    Carrot          p2=4:luckt        紧凑 [4.0]         → getP2() 越界、getP1() 错得 4.0
    Dark Lantern    p1,p2,p3,p5        紧凑 [50,50,1.3,7] → getP5() 错得 0.0、getP4() 错得 7.0
    Brass Knuckles  p1,p2,p4           紧凑 [0.3,5,50]     → getP4() 错得 50.0

为什么单独一支工具而不是重跑 build_data.py
----------------------------------------
`assets/battle_items.json` 是**多段流水线**的产物：build_data 之后还有
enrich_types / enrich_classes / enrich_linkage / regen_behaviors 等就地补字段的
步骤。整文件重生成会把它们全部抹掉，故此处只**定点重写 `params`** 一个字段。
（`simulator/build_data.py` 里的生成逻辑也一并修正了，将来重跑同样正确。）

★ 只改 `params`，不碰 `named_params` / `effects` / `behavior` 等任何其它字段，
  且写出格式（indent=1 / ensure_ascii=False / CRLF）与既有文件逐字节一致 ——
  保证 diff 里只有参数数组这一处。

用法
----
    python tools/align_item_params.py            # 就地校正
    python tools/align_item_params.py --check    # 只校验，不改（不一致则退出码 1）

依赖：读取加密物品表需 pycryptodome（用 binaries/python/envs/default 运行）。
"""
from __future__ import annotations

import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import item_sheet  # noqa: E402

DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")


def dump_like_original(data) -> bytes:
    """与既有文件同格式写出：indent=1 / 不转义非 ASCII / CRLF 换行。"""
    return json.dumps(data, ensure_ascii=False, indent=1).encode("utf-8") \
        .replace(b"\n", b"\r\n")


def main() -> int:
    check_only = "--check" in sys.argv

    rows = item_sheet.load_rows()
    raw = open(DB_PATH, "rb").read()
    db = json.loads(raw.decode("utf-8"))
    items = db["items"]

    fixed, missing, unchanged = [], [], 0
    for key, entry in items.items():
        row = rows.get(key)
        if row is None:
            missing.append(key)
            continue
        want = item_sheet.aligned_params(row)
        if entry.get("params") == want:
            unchanged += 1
        else:
            fixed.append((key, entry.get("params"), want))
            entry["params"] = want

    print(f"battle_items.json: {len(items)} 物品；"
          f"列已对齐 {unchanged}，需修正 {len(fixed)}，表中缺行 {len(missing)}")
    for key, old, new in fixed[:10]:
        print(f"   {key:22s} {old} → {new}")
    if len(fixed) > 10:
        print(f"   … 其余 {len(fixed) - 10} 件")
    if missing:
        print(f"   表中缺行（保留原值）：{missing[:10]}")

    if check_only:
        if fixed:
            print("\n[校验失败] params 未按列对齐；跑 `python tools/align_item_params.py` 校正。")
            return 1
        print("\n[校验通过] 全部物品 params 均已按列对齐。")
        return 0

    if not fixed:
        print("无需改动。")
        return 0

    out = dump_like_original(db)
    with open(DB_PATH, "wb") as fh:
        fh.write(out)
    print(f"已写回 {DB_PATH}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
