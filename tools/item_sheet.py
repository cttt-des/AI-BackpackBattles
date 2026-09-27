# -*- coding: utf-8 -*-
"""item_sheet.py — 读取原版权威物品表 Sheets/CSV/ItemData_e.csv（自动解密 GDEC）

原版把物品表以 **GDEC 容器**（AES-256-ECB，密钥见 tools/csv_key.txt）加密后随包
发布。早先各消费方直接 `open(CSV_PATH, encoding='utf-8')` —— 对加密文件会**静默
读到乱码**（DictReader 解析出 2 列、名字全空），于是「生成器跑通了但产物是空的」
这种最难查的失败会出现。本模块把「解密 + 解析」收在一处。

★ `params` 必须**按列对齐**（NUM_PARAMS = 10）
--------------------------------------------------
原版 `ItemBook.gd:855-875` 对 p1..p10 **每一列**取值 push_back（空列 push 默认
0），故 `ItemDescriptor.params` 的长度恒为 10 且 `params[i]` 恒等于第 (i+1) 列：

    getP1() = getP_check(0) = params[0] = p1     …     getP10() = params[9] = p10

早先的实现**跳过空列**（紧凑数组），会让「前面有空列」的物品整体错位。实证：

    Carrot          CSV: p2=4:luckt               紧凑 [4.0]   → getP2() 越界、getP1() 错得 4.0
    Poison Ivy      CSV: p1,p2,p4                 紧凑 [18,25,2] → getP4() 错得 2.0（真值 p4=2 尚对，getP3() 错得 2）
    Dark Lantern    CSV: p1,p2,p3,p5              紧凑 [50,50,1.3,7] → getP5() 错得 0.0、getP4() 错得 7.0
    Brass Knuckles  CSV: p1,p2,p4                 紧凑 [0.3,5,50] → getP4() 错得 50.0

用 `aligned_params(row)` 取参数，不要自己拼。

用法
----
    from item_sheet import load_rows, aligned_params, NUM_PARAMS
    rows = load_rows()               # {显示名: {列名: 值}}
    params = aligned_params(rows['Carrot'])   # [0.0, 4.0, 0.0, ...]（长度 10）
"""
from __future__ import annotations

import csv
import io
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV_PATH = os.path.join(ROOT, "extracted", "Sheets", "CSV", "ItemData_e.csv")
KEY_PATH = os.path.join(ROOT, "tools", "csv_key.txt")

# 对齐 ItemBook.gd:8 `const NUM_PARAMS = 10`
NUM_PARAMS = 10

GDEC_MAGIC = b"GDEC"


def csv_key() -> bytes:
    """从 tools/csv_key.txt 取 64 位十六进制密钥（注释行忽略）。"""
    with open(KEY_PATH, encoding="utf-8") as fh:
        m = re.search(r"\b[0-9a-fA-F]{64}\b", fh.read())
    if not m:
        raise ValueError(f"{KEY_PATH} 中找不到 64 位十六进制密钥")
    return bytes.fromhex(m.group(0))


def decrypt_if_needed(data: bytes, key: bytes | None = None) -> bytes:
    """GDEC 容器 → 明文；已是明文则原样返回。

    容器布局（同 .gde）：
        [4 "GDEC"][4 ver][16 MD5(明文)][8 LE 明文长度][AES-256-ECB 密文]
    """
    if data[:4] != GDEC_MAGIC:
        return data
    try:
        from Crypto.Cipher import AES
    except ImportError as exc:  # pragma: no cover
        raise ImportError(
            "读取加密的 ItemData_e.csv 需要 pycryptodome，"
            "请用含该依赖的解释器（如 binaries/python/envs/default）运行") from exc

    import hashlib

    key = key or csv_key()
    md5_expected = data[8:24]
    plain_len = int.from_bytes(data[24:32], "little")
    plain = AES.new(key, AES.MODE_ECB).decrypt(data[32:])[:plain_len]
    if hashlib.md5(plain).digest() != md5_expected:
        raise ValueError("ItemData_e.csv 解密后 MD5 与容器头不一致（密钥错）")
    return plain


def read_text(path: str = CSV_PATH) -> str:
    """读表为文本（自动解密）。表内含非 UTF-8 字节，故用 replace 容错。"""
    with open(path, "rb") as fh:
        raw = fh.read()
    return decrypt_if_needed(raw).decode("utf-8", errors="replace")


def load_rows(path: str = CSV_PATH) -> dict:
    """{显示名: {列名: 原始字符串}} —— 保留原样字符串，由消费方自行转型。"""
    out = {}
    for row in csv.DictReader(io.StringIO(read_text(path))):
        name = (row.get("name") or "").strip()
        if name:
            out[name] = row
    return out


def aligned_params(row: dict) -> list:
    """p1..p10 → **定长 10 的列对齐数组**（对齐 ItemBook.gd:855-875）。

    ★ 不要改回「跳过空列」：`params[i]` 的下标语义就是列号-1，
      跳列会让 getP1()..getP10() 全部错位（见模块 docstring 的实测表）。
    """
    out = []
    for i in range(1, NUM_PARAMS + 1):
        raw = (row.get(f"p{i}") or "").strip()
        val = raw.split(":", 1)[0].strip() if ":" in raw else raw
        try:
            out.append(float(val) if val else 0.0)
        except ValueError:
            out.append(0.0)
    return out


def named_params(row: dict) -> dict:
    """`4:luckt` → {'luckt': 4.0}（对齐 ItemDescriptor.addNamedParam）。"""
    out = {}
    for i in range(1, NUM_PARAMS + 1):
        raw = (row.get(f"p{i}") or "").strip()
        if ":" not in raw:
            continue
        val, name = raw.split(":", 1)
        name = name.strip()
        try:
            out[name] = float(val.strip())
        except ValueError:
            pass
    return out


if __name__ == "__main__":
    rows = load_rows()
    print(f"ItemData_e.csv: {len(rows)} 物品")
    for probe in ("Carrot", "Poison Ivy", "Dark Lantern", "Brass Knuckles"):
        if probe in rows:
            print(f"  {probe:16s} params={aligned_params(rows[probe])} "
                  f"named={named_params(rows[probe])}")
