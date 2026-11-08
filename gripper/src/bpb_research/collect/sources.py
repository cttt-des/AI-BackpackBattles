"""数据源适配：Steam 排行榜 / bpb2 公开 API / 本地文件。"""
from __future__ import annotations

import json
import time
import urllib.error
import urllib.request
from pathlib import Path
from typing import Any, Callable

UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0 Safari/537.36"


def http_get(url: str, *, timeout: int = 45, retries: int = 2) -> bytes:
    last: Exception | None = None
    for attempt in range(retries + 1):
        try:
            req = urllib.request.Request(url, headers={"User-Agent": UA, "Accept": "application/json"})
            with urllib.request.urlopen(req, timeout=timeout) as response:
                return response.read()
        except urllib.error.HTTPError as error:
            if error.code in (400, 401, 403, 404):
                raise
            last = error
        except Exception as error:
            last = error
        time.sleep(1 + attempt)
    raise RuntimeError(f"HTTP 失败: {url}: {last}")


def bpb2_matches(page_size: int = 20, max_pages: int | None = None) -> Callable[[], bytes]:
    """bpb2 逐场对局（公开 API，无鉴权）。"""
    base = "https://bpb-builds.exp0.dev/api/matches"

    def fetch() -> bytes:
        records: list[dict[str, Any]] = []
        offset = 0
        pages = 0
        while True:
            page = json.loads(http_get(f"{base}?limit={page_size}&offset={offset}"))
            data = page.get("data") or []
            records.extend(data)
            pagination = page.get("pagination") or {}
            total = int(pagination.get("total") or 0)
            offset += page_size
            pages += 1
            if not data or offset >= total or (max_pages is not None and pages >= max_pages):
                break
            time.sleep(0.2)
        return json.dumps(records, ensure_ascii=False).encode("utf-8")

    return fetch


def bpb2_builds(page_size: int = 20, max_pages: int | None = None) -> Callable[[], bytes]:
    base = "https://bpb-builds.exp0.dev/api/builds"

    def fetch() -> bytes:
        records: list[dict[str, Any]] = []
        offset = 0
        pages = 0
        while True:
            page = json.loads(http_get(f"{base}?limit={page_size}&offset={offset}"))
            data = page.get("data") or []
            records.extend(data)
            total = int((page.get("pagination") or {}).get("total") or 0)
            offset += page_size
            pages += 1
            if not data or offset >= total or (max_pages is not None and pages >= max_pages):
                break
            time.sleep(0.2)
        return json.dumps(records, ensure_ascii=False).encode("utf-8")

    return fetch


def steam_leaderboard(*, app_id: int = 2427700, board: str = "bpb-runs3",
                      start: int = 1, end: int = 2000) -> Callable[[], bytes]:
    """Steam 排行榜：需要 Steamworks 游戏进程或 publisher key，当前标记为不可用。"""

    def fetch() -> bytes:
        raise RuntimeError(
            "Steam 排行榜需要游戏进程上下文或 Web API publisher key；"
            "ctypes 直连实测 io=true（handle=0）"
        )

    return fetch


def local_file(path: Path) -> Callable[[], bytes]:
    def fetch() -> bytes:
        return Path(path).read_bytes()

    return fetch
