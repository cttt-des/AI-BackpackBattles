"""入库：把解码后的 run 写入独立 SQLite（幂等）。

run 身份 = (缓存 sha256, run 在缓存中的偏移)，重复导入自动跳过。
内容指纹 content_sha 相同者只入一次（跨批次去重）。
"""
from __future__ import annotations

import hashlib
import json
import sqlite3
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Iterable

from bpb_research.stream.bitstream import BitStream, ItemMap, decode_round

SCHEMA = """
CREATE TABLE IF NOT EXISTS runs (
    run_id TEXT PRIMARY KEY,
    source TEXT NOT NULL,
    captured_at TEXT NOT NULL,
    rounds INTEGER NOT NULL,
    meta_json TEXT,
    content_sha TEXT,
    rating REAL,
    rating_bucket TEXT,
    player_name TEXT,
    record_version TEXT,
    outcome_json TEXT,
    class_id INTEGER,
    class_name TEXT,
    chibi INTEGER,
    skins_json TEXT,
    player_id TEXT,
    player_name_decoded TEXT
);
CREATE TABLE IF NOT EXISTS rounds (
    run_id TEXT NOT NULL,
    round_no INTEGER NOT NULL,
    health INTEGER,
    stamina INTEGER,
    items_json TEXT NOT NULL,
    result INTEGER,
    PRIMARY KEY (run_id, round_no)
);
CREATE TABLE IF NOT EXISTS items (
    run_id TEXT NOT NULL,
    round_no INTEGER NOT NULL,
    slot INTEGER NOT NULL,
    name TEXT NOT NULL,
    x INTEGER, y INTEGER, face INTEGER, gid INTEGER,
    gems_json TEXT
);
CREATE INDEX IF NOT EXISTS idx_items_name ON items(name);
CREATE INDEX IF NOT EXISTS idx_items_run ON items(run_id, round_no);
CREATE INDEX IF NOT EXISTS idx_runs_rating ON runs(rating);
"""

# Game.leagueThresholds：0,50,120,200,300,400,480,550,850
LEAGUE_THRESHOLDS = [
    (0, "Bronze"), (50, "Silver"), (120, "Gold"), (200, "Platinum"),
    (300, "Diamond"), (400, "Master"), (480, "Grandmaster"),
    (550, "Grandma"), (850, "Grandma+"),
]
UNRANKED_RATING = -1000

# Game.gd 的 Classes_Full 枚举：flag5 存的就是职业 ID
CLASS_NAMES = {
    0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer",
    4: "Mage", 5: "Adventurer", 6: "Engineer",
}


def class_name_of(flag5: Any) -> str | None:
    if flag5 is None:
        return None
    try:
        return CLASS_NAMES.get(int(flag5))
    except (TypeError, ValueError):
        return None


def rating_bucket(rating: Any) -> str | None:
    """把 rating 映射成游戏内段位名。"""
    if rating is None:
        return None
    try:
        value = float(rating)
    except (TypeError, ValueError):
        return None
    if value == UNRANKED_RATING:
        return "Unranked"
    name = "ImpossibleWood"
    for threshold, label in LEAGUE_THRESHOLDS:
        if value >= threshold:
            name = label
    return name


def connect(path: Path) -> sqlite3.Connection:
    path.parent.mkdir(parents=True, exist_ok=True)
    conn = sqlite3.connect(path)
    conn.executescript(SCHEMA)
    _migrate(conn)
    return conn


def _migrate(conn: sqlite3.Connection) -> None:
    """给老库补列（新库由 SCHEMA 建好，这里只是兜底）。"""
    cols = {row[1] for row in conn.execute("PRAGMA table_info(runs)")}
    for name, ddl in (
        ("rating", "REAL"), ("rating_bucket", "TEXT"), ("player_name", "TEXT"),
        ("record_version", "TEXT"), ("outcome_json", "TEXT"),
        ("class_id", "INTEGER"), ("class_name", "TEXT"),
        ("chibi", "INTEGER"), ("skins_json", "TEXT"), ("player_id", "TEXT"),
        ("player_name_decoded", "TEXT"),
    ):
        if name not in cols:
            conn.execute(f"ALTER TABLE runs ADD COLUMN {name} {ddl}")
    rcols = {row[1] for row in conn.execute("PRAGMA table_info(rounds)")}
    if "result" not in rcols:
        conn.execute("ALTER TABLE rounds ADD COLUMN result INTEGER")
    conn.commit()


def decode_player_name(encoded: Any) -> str | None:
    """玩家名是 BitStream 序列化的 UTF-8 字符串（6bit + 62 偏移）。"""
    if not isinstance(encoded, str) or not encoded:
        return None
    try:
        bs = BitStream(encoded)
        out = bytearray()
        while bs.bits_left() >= 8:
            byte = bs.pull(256)
            if byte < 0:
                break
            out.append(byte)
        text = out.decode("utf-8", "replace").strip()
        return text or None
    except Exception:
        return None


def _content_sha(rounds: list[dict[str, Any]]) -> str:
    payload = json.dumps(rounds, ensure_ascii=False, sort_keys=True)
    return hashlib.sha256(payload.encode("utf-8")).hexdigest()


def ingest_export(conn: sqlite3.Connection, records: Iterable[dict[str, Any]], *,
                  source: str, cache_sha: str, imap: ItemMap | None = None,
                  captured_at: str | None = None) -> dict[str, int]:
    """入库 Godot 导出的结构化记录（含 rating）。

    每条 record 形如：
    {name_raw, rating, metadata, version, flag0, flag5, flag8, arr4, arr6_len, arr9_len}
    metadata 是逐轮 bitstream 的 JSON 串。
    """
    imap = imap or ItemMap()
    stats = {"records": 0, "runs_new": 0, "runs_skipped": 0, "runs_dup_content": 0,
             "rounds": 0, "items": 0, "errors": 0, "no_rating": 0}
    stamp = captured_at or datetime.now(timezone.utc).isoformat()

    for index, record in enumerate(records):
        stats["records"] += 1
        # arr6 是逐轮 bitstream 串数组（实测），每轮一个
        streams = record.get("arr6") or []
        if not streams:
            stats["errors"] += 1
            continue
        good = []
        for i, text in enumerate(streams):
            if not isinstance(text, str) or not text:
                continue
            try:
                decoded = decode_round(text, imap)
            except Exception:
                continue
            if decoded and "items" in decoded:
                good.append((i + 1, decoded))
        if not good:
            stats["errors"] += 1
            continue

        rating = record.get("rating")
        if rating is None:
            stats["no_rating"] += 1
        content = _content_sha([r for _, r in good])
        run_id = f"{source}:{cache_sha[:12]}:{index}"

        if conn.execute("SELECT 1 FROM runs WHERE run_id=?", (run_id,)).fetchone():
            stats["runs_skipped"] += 1
            continue
        if conn.execute("SELECT 1 FROM runs WHERE content_sha=?", (content,)).fetchone():
            stats["runs_dup_content"] += 1
            continue

        outcomes = record.get("arr4") or []
        bucket = rating_bucket(rating)
        class_id = record.get("flag5")
        chibi = record.get("flag8")
        skins = record.get("arr9") or []
        player_id = record.get("f3") or None
        with conn:
            conn.execute(
                """INSERT INTO runs(run_id, source, captured_at, rounds, meta_json, content_sha,
                                    rating, rating_bucket, player_name, record_version,
                                    outcome_json, class_id, class_name, chibi, skins_json, player_id,
                                    player_name_decoded)
                   VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)""",
                (run_id, source, stamp, len(good), json.dumps({"i": index}, ensure_ascii=False),
                 content, rating, bucket, record.get("name_raw"), record.get("version"),
                 json.dumps(outcomes, ensure_ascii=False), class_id, class_name_of(class_id),
                 1 if chibi else 0, json.dumps(skins, ensure_ascii=False), player_id,
                 decode_player_name(record.get("name_raw"))),
            )
            for round_no, data in good:
                result = outcomes[round_no - 1] if round_no - 1 < len(outcomes) else None
                conn.execute(
                    "INSERT INTO rounds(run_id, round_no, health, stamina, items_json, result)"
                    " VALUES (?,?,?,?,?,?)",
                    (run_id, round_no, data.get("health"), data.get("stamina"),
                     json.dumps(data["items"], ensure_ascii=False), result),
                )
                stats["rounds"] += 1
                for slot, item in enumerate(data["items"]):
                    conn.execute(
                        "INSERT INTO items(run_id, round_no, slot, name, x, y, face, gid, gems_json)"
                        " VALUES (?,?,?,?,?,?,?,?,?)",
                        (run_id, round_no, slot, item.get("id"), item.get("x"), item.get("y"),
                         item.get("face"), item.get("gid"),
                         json.dumps(item.get("gems") or [], ensure_ascii=False)),
                    )
                    stats["items"] += 1
        stats["runs_new"] += 1
    return stats


def summary(conn: sqlite3.Connection) -> dict[str, Any]:
    def one(sql: str):
        row = conn.execute(sql).fetchone()
        return row[0] if row else 0

    by_bucket = {
        row[0] or "unknown": row[1]
        for row in conn.execute(
            "SELECT rating_bucket, COUNT(*) FROM runs GROUP BY rating_bucket ORDER BY COUNT(*) DESC")
    }
    return {
        "runs": one("SELECT COUNT(*) FROM runs"),
        "rounds": one("SELECT COUNT(*) FROM rounds"),
        "items": one("SELECT COUNT(*) FROM items"),
        "distinct_items": one("SELECT COUNT(DISTINCT name) FROM items"),
        "with_rating": one("SELECT COUNT(*) FROM runs WHERE rating IS NOT NULL"),
        "master_plus": one("SELECT COUNT(*) FROM runs WHERE rating >= 400"),
        "by_bucket": by_bucket,
        "by_class": {
            row[0] or "unknown": row[1]
            for row in conn.execute(
                "SELECT class_name, COUNT(*) FROM runs GROUP BY class_name ORDER BY COUNT(*) DESC")
        },
        "distinct_players": one("SELECT COUNT(DISTINCT player_name_decoded) FROM runs WHERE player_name_decoded IS NOT NULL"),
        "chibi_runs": one("SELECT COUNT(*) FROM runs WHERE chibi = 1"),
        "avg_rating": round(one("SELECT AVG(rating) FROM runs WHERE rating IS NOT NULL AND rating > -1000") or 0, 1),
    }
