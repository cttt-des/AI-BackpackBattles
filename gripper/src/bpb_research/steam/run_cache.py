"""把 runs_steam.cache 切成完整 run（health 递增 + 最多 18 轮规则）。

实测规律：
- 同一 run 内 health 单调不减，常见步长 0/5/10/15
- 新 run 从更低 health 重新开始
- 每 run 最多 18 轮，1~5 轮的碎片多为切分噪声，入库时过滤
"""
from __future__ import annotations

import hashlib
import os
import struct
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

from bpb_research.stream.bitstream import ItemMap, decode_round

OK_MIN, OK_MAX = 62, 125
MAX_ROUNDS = 18
MIN_ROUNDS = 6


@dataclass
class Run:
    offset: int
    rounds: list[dict[str, Any]] = field(default_factory=list)

    @property
    def round_count(self) -> int:
        return len(self.rounds)


def locate_default_cache() -> Path | None:
    appdata = os.environ.get("APPDATA")
    if not appdata:
        return None
    candidate = Path(appdata) / "Godot" / "app_userdata" / "Backpack Battles" / "runs_steam.cache"
    return candidate if candidate.exists() else None


def cache_signature(path: Path | None = None) -> dict[str, Any]:
    path = Path(path) if path else locate_default_cache()
    if path is None or not Path(path).exists():
        return {"available": False}
    data = Path(path).read_bytes()
    return {
        "available": True,
        "path": str(path),
        "bytes": len(data),
        "sha256": hashlib.sha256(data).hexdigest(),
        "mtime": Path(path).stat().st_mtime,
    }


def _iter_raw(buffer: bytes):
    i, n = 0, len(buffer)
    while i < n - 5:
        length = struct.unpack_from("<I", buffer, i)[0]
        start = i + 4
        if 4 <= length <= 65536 and start + length <= n:
            seg = buffer[start:start + length]
            if all(OK_MIN <= b <= OK_MAX for b in seg):
                yield i, seg
                i = start + length
                continue
        i += 1


def parse_runs(path: Path | None = None, *, imap: ItemMap | None = None,
               min_rounds: int = MIN_ROUNDS) -> list[Run]:
    path = Path(path) if path else locate_default_cache()
    if path is None or not Path(path).exists():
        raise FileNotFoundError("找不到 runs_steam.cache")
    imap = imap or ItemMap()
    data = Path(path).read_bytes()
    runs: list[Run] = []
    current: list[dict[str, Any]] = []
    offset = 0
    for pos, seg in _iter_raw(data):
        try:
            decoded = decode_round(seg.decode("ascii"), imap)
        except Exception:
            continue
        if not decoded or decoded.get("health") is None:
            continue
        health = decoded["health"]
        items = decoded.get("items") or []
        if not isinstance(health, int) or not 0 < health <= 999 or len(items) > 40:
            continue
        if current and (health <= current[-1]["health"] or len(current) >= MAX_ROUNDS):
            runs.append(Run(offset=offset, rounds=current))
            current = []
        if not current:
            offset = pos
        current.append({"health": health, "stamina": decoded.get("stamina"), "items": items})
    if current:
        runs.append(Run(offset=offset, rounds=current))
    return [run for run in runs if run.round_count >= min_rounds]
