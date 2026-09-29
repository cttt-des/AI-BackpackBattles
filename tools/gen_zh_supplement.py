# -*- coding: utf-8 -*-
"""gen_zh_supplement.py — 从游戏内置翻译资源生成物品中文名映射资产。

真值源：运行中游戏 pck 的 Sheets/CSV/*.translation（PHashTranslation，
用 gdre_tools --bin-to-txt 转成 .tres 后解析）。物品跨版本改名导致
descriptor 的 identifier（旧名）与当前翻译键不一致，但**描述文本稳定**，
且翻译表字符串区保持 CSV 行序（名字行与其描述行相邻）——据此构建：

  names         en名 → zh名（哈希键直接配对）
  desc_name_zh  zh描述 → zh名（相邻关系；描述唯一且稳定，运行时用
                descriptor 里的 zh 描述反查官方译名，绕开改名问题）
  desc_name_en  en描述 → en名
  keywords      关键词(spikes/vampirism/..) → zh名

前置：先运行
  gdre_tools --headless --bin-to-txt=<pck提取的 *.translation> --output=...
并把 .tres 放到 extracted_running/txt/。用法：
  python tools/gen_zh_supplement.py
输出：assets/item_zh_official.json
"""
import json
import re
import sys
from pathlib import Path

PROJECT = Path(__file__).resolve().parent.parent
TXT = PROJECT / "extracted_running" / "txt"
OUT = PROJECT / "assets" / "item_zh_official.json"

TABLES = ("Items", "ExclusiveItems", "Full", "Interface", "Keywords")


def parse_tres(path: Path):
    d = path.read_text(encoding="utf-8")
    m = re.search(r"strings = PoolByteArray\(([^)]*)\)", d, re.S)
    if not m:
        return [], b""
    strings = bytes(int(x) for x in m.group(1).replace("\n", " ").split(",")
                    if x.strip())
    bt = []
    mb = re.search(r"bucket_table = PoolIntArray\(([^)]*)\)", d, re.S)
    if mb:
        bt = [int(x) for x in mb.group(1).replace("\n", " ").split(",")
              if x.strip()]
    return bt, strings


def collect(bt, S):
    """桶遍历 → {哈希键: 文本}。zh 表明文，en 表 smaz 压缩。"""
    out = {}
    o = 0
    while o + 2 <= len(bt):
        size, func = bt[o], bt[o + 1]
        if not (0 <= size <= 2000 and func <= 5000):
            break
        o += 2
        for _ in range(size):
            key, soff, cs, us = bt[o:o + 4]
            o += 4
            raw = S[soff:soff + cs]
            try:
                txt = raw.decode("utf-8", "replace") if cs == us \
                    else smaz_decompress(raw).decode("utf-8")
            except Exception:  # noqa: BLE001
                continue
            txt = txt.replace("\x00", "").strip()
            if txt:
                out[key] = txt
    return out


def is_name_like(s: str) -> bool:
    return 1 <= len(s) <= 20 and "$" not in s and "[" not in s \
        and "\n" not in s and not s.endswith((".", "。", ":", "："))


def desc_name_map(strings: bytes):
    """字符串区（CSV 行序）→ {描述: 名字}。名字行紧邻其描述行之前。"""
    seq = [p.decode("utf-8", "replace").replace("\x00", "").strip()
           for p in strings.split(b"\x00") if p.strip()]
    out = {}
    for i, s in enumerate(seq):
        if is_name_like(s) or len(s) < 12:
            continue
        for j in range(i - 1, max(-1, i - 4), -1):
            if is_name_like(seq[j]):
                out.setdefault(s, seq[j])
                break
    return out


def main():
    sys.path.insert(0, str(PROJECT / "tools"))
    from smaz_dict import smaz_decompress  # noqa: E402

    names = {}          # en名 → zh名（哈希键配对）
    desc_zh = {}        # zh描述 → zh名
    desc_en = {}        # en描述 → en名
    keywords = {}       # 关键词 → zh名
    # 旧版（v1.1.7 .bak）翻译先合入补缺，新版表后合入覆盖（改名/新物品）
    for src, tables in (("v1.1.7", ("Items", "ExclusiveItems", "Full",
                                    "Interface", "Keywords")),
                        ("当前版", TABLES)):
        base = TXT if src == "当前版" else PROJECT / "extracted_v117" / "Sheets" / "CSV"
        for name in tables:
            en_p = base / f"{name}.en.translation"
            zh_p = base / f"{name}.zh_Hans_CN.translation"
            if not (en_p.exists() and zh_p.exists()):
                print(f"跳过 {src}/{name}（缺文件）")
                continue
            bt_en, S_en = parse_tres(en_p)
            bt_zh, S_zh = parse_tres(zh_p)
            en, zh = collect(bt_en, S_en), collect(bt_zh, S_zh)
            for k, e in en.items():
                z = zh.get(k)
                if e and z and not e.endswith("_NAME"):
                    names[e] = z
            desc_zh.update(desc_name_map(S_zh))
            desc_en.update(desc_name_map(S_en))
            if name == "Keywords":
                for k, e in en.items():
                    z = zh.get(k)
                    if e and z:
                        keywords[e.lower()] = z
            print(f"{src}/{name}: en={len(en)} zh={len(zh)}")

    data = {"names": names, "desc_name_zh": desc_zh,
            "desc_name_en": desc_en, "keywords": keywords}
    OUT.write_text(json.dumps(data, ensure_ascii=False, indent=0),
                   encoding="utf-8")
    print(f"写入 {OUT}: names={len(names)} desc_name_zh={len(desc_zh)} "
          f"desc_name_en={len(desc_en)} keywords={len(keywords)}")
    # 验证改名物品
    for probe in ("辉耀王冠", "国王王冠", "月光盾", "阿拉丁神灯"):
        rev = [en for en, z in names.items() if z == probe]
        print(f"  {probe} <- {rev[:3]}")
    for en, z in names.items():
        if en in ("Crown", "Steel Dragon", "Evil Hat", "Rainbow Orb",
                  "Deer Totem", "Book of Darkness", "Berserker Bag"):
            print(f"  直接命中: {en} -> {z}")


if __name__ == "__main__":
    main()
