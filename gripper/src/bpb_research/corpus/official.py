"""语料解析：直接复用作者的官方解码器 decode_corpus.py。

为什么不自研：
  语料是「自定义二进制帧容器 + gzip」，帧内是 TLV（field_id + value）。
  早期我们靠猜（把 0x10+face 当物品标志）得出过错误结论——那其实是
  packed(16) + face(0..3) 的巧合位组合，遇到带宝石/带附加字段的物品就错位。
  作者提供了权威解析器，直接用，别再猜。

官方格式（decode_corpus.py）：
  BPBCRP01 | 版本(1B) | 'B' | 行数(varint) | [TLV 字段...]
  字段表见 FIELDS（22 个），field_id 从 1 开始，0 表示行结束。
"""
from __future__ import annotations

import sys
from pathlib import Path
from typing import Iterator

ROOT = Path(__file__).resolve().parents[4]
OFFICIAL_DIR = ROOT / "output" / "corpus_official"

if str(OFFICIAL_DIR) not in sys.path:
    sys.path.insert(0, str(OFFICIAL_DIR))

import decode_corpus as _dc  # noqa: E402  官方解码器

CorpusDecodeError = _dc.CorpusDecodeError

#: 官方字段表（field_id -> 名称）
FIELD_NAMES: tuple[str, ...] = tuple(name for name, _kind in _dc.FIELDS)


def iter_rows(path: Path) -> Iterator[dict]:
    """逐局产出官方解码后的字典（流式，内存不随文件增长）。"""
    yield from _dc.iter_shard_rows(str(path))


def iter_corpus(corpus_dir: Path, *, include_parts: bool = False) -> Iterator[dict]:
    """遍历语料目录。

    默认只读顶层 *.bin.gz（日期分片 + undated.bin.gz）。
    undated_parts 与 undated.bin.gz 是同一份数据的两种形态，故默认跳过，
    避免重复统计。
    """
    base = Path(corpus_dir)
    for f in sorted(base.glob("*.bin.gz")):
        yield from iter_rows(f)
    if include_parts:
        parts = base / "undated_parts"
        if parts.is_dir():
            for f in sorted(parts.glob("*.bin.gz")):
                yield from iter_rows(f)


def row_key(row: dict) -> str:
    """去重键：优先 corpus_key，退化到 run_id。

    undated 分片的 run_id 恒为占位值 "1"，必须用 corpus_key。
    """
    key = row.get("corpus_key") or ""
    if key:
        return str(key)
    rid = row.get("run_id") or ""
    return f"run_id:{rid}" if rid else ""


def summarize(row: dict) -> dict:
    """把一局压缩成便于统计的摘要（不含逐轮盘面）。"""
    rounds = row.get("rounds") or []
    results = row.get("results") or []
    return {
        "key": row_key(row),
        "rating": row.get("rating"),
        "class": row.get("class"),
        "version": row.get("entry_version"),
        "pool": row.get("pool"),
        "main_pool": row.get("main_pool"),
        "source": row.get("source"),
        "rounds_played": sum(1 for r in results if r != 3),
        "round_snapshots": len(rounds),
        "items_total": sum(len(rd.get("items") or []) for rd in rounds),
        "problems": row.get("problems"),
        "meta_ok": row.get("meta_ok"),
        "score_seq": row.get("score_seq"),
        "snapshots": row.get("snapshots") or [],
        "values": row.get("values") or [],
    }
