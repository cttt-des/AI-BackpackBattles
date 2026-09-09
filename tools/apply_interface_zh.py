# -*- coding: utf-8 -*-
"""apply_interface_zh.py — 用 Interface.csv 的 en->zh 精确翻译替换 events.py 手写模板。

规则：TEMPLATES 每项 (en, zh)。若 en 文本在 Interface.csv 中有精确 zh_Hans_CN 行，
用官方译文替换（去掉首尾空格）。BattleRageEnd/Fatigue 等无 CSV 行的保留原样。
输出 diff 供人工核对。
"""
import csv
import re
import sys
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

INTERFACE = os.path.join(ROOT, "extracted", "Sheets", "CSV", "Interface.csv")
EVENTS = os.path.join(ROOT, "simulator", "events.py")


def load_pairs():
    with open(INTERFACE, encoding="utf-8-sig") as f:
        rows = list(csv.reader(f))
    hdr = rows[0]
    i_en, i_zh = hdr.index("en"), hdr.index("zh_Hans_CN")
    pairs = {}
    for r in rows[1:]:
        if len(r) > i_zh and r[i_en] and r[i_zh]:
            pairs[r[i_en].strip()] = r[i_zh].strip()
    return pairs


def main():
    pairs = load_pairs()
    src = open(EVENTS, encoding="utf-8").read()

    # 匹配 "KEY":  ("en...", "zh..."),
    pat = re.compile(r'("?[A-Z_0-9]+"?)\s*:\s*\(\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"\s*\)')

    replaced, kept, missing = [], [], []

    def repl(m):
        key, en, zh = m.group(1), m.group(2), m.group(3)
        exact = pairs.get(en)
        if exact is None:
            missing.append((key, en))
            kept.append((key, en, zh))
            return m.group(0)
        # 占位符一致性校验：en 中的 {} 占位集合必须与官方译文一致
        ph_en = re.findall(r'\{(\w+)\}', en)
        ph_zh = re.findall(r'\{(\w+)\}', exact)
        if sorted(ph_en) != sorted(ph_zh):
            missing.append((key, en + f"  [占位符不一致: {sorted(ph_en)} vs {sorted(ph_zh)}]"))
            kept.append((key, en, zh))
            return m.group(0)
        replaced.append((key, en, zh, exact))
        return f'{key}: ("{en}", "{exact}"),'

    # 替换后统一清理双逗号（原行尾逗号 + 补的逗号）

    # 仅作用于 TEMPLATES = { ... } 区块
    m0 = re.search(r'TEMPLATES = \{', src)
    m1 = re.search(r'\n\}\n', src[m0.end():])
    block_start, block_end = m0.end(), m0.end() + m1.start() + 1
    block = src[block_start:block_end]
    new_block = pat.sub(repl, block)
    new_block = re.sub(r'\),,\s*\n', '),\n', new_block)
    src = src[:block_start] + new_block + src[block_end:]

    print(f"替换 {len(replaced)} 项 / 保留 {len(kept)} 项")
    for key, en, zh, exact in replaced:
        mark = "*" if zh != exact else " "
        print(f"  {mark} {key}:")
        if zh != exact:
            print(f"      旧: {zh}")
            print(f"      新: {exact}")
    print("无官方译文（保留原状）:")
    for key, en in missing:
        print(f"  - {key}: {en[:60]}")

    with open(EVENTS, "w", encoding="utf-8") as f:
        f.write(src)
    print(f"已写回 {EVENTS}")


if __name__ == "__main__":
    main()
