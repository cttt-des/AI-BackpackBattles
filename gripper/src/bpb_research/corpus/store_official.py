"""语料入库：基于官方解码器的完整 schema。

相比早期版本，这里保留**逐轮棋盘快照**（rounds）与物品宝石（g/gems），
这是训练摆盘 AI 真正需要的数据。schema：

  corpus_runs     : 一局一行（rating/class/版本/来源/逐轮价值…）
  corpus_rounds   : 一局的一轮一行（health/stamina/物品数）
  corpus_items    : 一局一轮的一件物品一行（gid/x/y/f/gems）

去重键 record_key = corpus_key（undated 的 run_id 是占位值，不能用）。
"""
from __future__ import annotations

import json
import sqlite3
from datetime import datetime, timezone
from pathlib import Path
from typing import Iterable, Iterator

from bpb_research.corpus.official import iter_corpus, row_key

# 精简后的 schema：只保留有信息量的字段。
# 已删除（全空或常量，无分析价值）：
#   player_name(全空) / run_id, corpus_key（与 record_key 等价）
#   entry_version(全 1.1.9) / pool(全 ranked) / source, sources_json(全 sw)
#   problems(全 0) / meta_ok(全 1) / main_pool（可由 rating>=300 推导）
SCHEMA = """
CREATE TABLE IF NOT EXISTS corpus_runs (
    record_key     TEXT PRIMARY KEY,
    rating         REAL,
    rating_bucket  TEXT,
    class_id       INTEGER,
    class_name     TEXT,
    snapshots_json TEXT,
    results_json   TEXT,
    values_json    TEXT,
    rounds_played  INTEGER,
    round_snapshots INTEGER,
    items_total    INTEGER,
    score_seq      INTEGER,
    shard          TEXT
);
CREATE TABLE IF NOT EXISTS corpus_rounds (
    record_key TEXT NOT NULL,
    round_no   INTEGER NOT NULL,
    health     INTEGER,
    stamina    INTEGER,
    item_count INTEGER,
    PRIMARY KEY (record_key, round_no)
);
CREATE TABLE IF NOT EXISTS corpus_items (
    record_key TEXT NOT NULL,
    round_no   INTEGER NOT NULL,
    seq        INTEGER NOT NULL,
    gid        INTEGER NOT NULL,
    x          INTEGER,
    y          INTEGER,
    face       INTEGER,
    gems_json  TEXT,
    pd         TEXT,
    PRIMARY KEY (record_key, round_no, seq)
);
CREATE INDEX IF NOT EXISTS idx_runs_rating ON corpus_runs(rating);
CREATE INDEX IF NOT EXISTS idx_runs_class ON corpus_runs(class_id);
CREATE INDEX IF NOT EXISTS idx_runs_bucket ON corpus_runs(rating_bucket);
CREATE INDEX IF NOT EXISTS idx_rounds_key ON corpus_rounds(record_key);
CREATE INDEX IF NOT EXISTS idx_items_gid ON corpus_items(gid);
CREATE INDEX IF NOT EXISTS idx_items_pos ON corpus_items(x, y);
CREATE INDEX IF NOT EXISTS idx_items_key ON corpus_items(record_key, round_no);
"""

CLASS_NAMES = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer",
               4: "Mage", 5: "Adventurer", 6: "Engineer"}
LEAGUE_THRESHOLDS = [(0, "Bronze"), (50, "Silver"), (120, "Gold"),
                     (200, "Platinum"), (300, "Diamond"), (400, "Master"),
                     (480, "Grandmaster"), (550, "Grandma")]
UNRANKED = -1000


def bucket_of(rating) -> str | None:
    if rating is None:
        return None
    try:
        v = float(rating)
    except (TypeError, ValueError):
        return None
    if v == UNRANKED:
        return "Unranked"
    name = "ImpossibleWood"
    for th, label in LEAGUE_THRESHOLDS:
        if v >= th:
            name = label
    return name


def connect(path: Path) -> sqlite3.Connection:
    path.parent.mkdir(parents=True, exist_ok=True)
    conn = sqlite3.connect(path)
    conn.executescript(SCHEMA)
    conn.execute("PRAGMA journal_mode=WAL")
    conn.execute("PRAGMA synchronous=NORMAL")
    return conn


def _row_to_tuples(row: dict, shard: str) -> tuple[tuple | None, list[tuple], list[tuple]]:
    """把一局拆成 (run_tuple, round_tuples, item_tuples)，便于批量 executemany。"""
    key = row_key(row)
    if not key:
        return None, [], []
    rounds = row.get("rounds") or []
    results = row.get("results") or []
    items_total = sum(len(rd.get("items") or []) for rd in rounds)
    cls = row.get("class")

    # 精简 schema：只写有信息量的字段（见 SCHEMA 注释）
    run_tuple = (
        key, row.get("rating"), bucket_of(row.get("rating")),
        cls, CLASS_NAMES.get(cls),
        json.dumps(row.get("snapshots") or [], ensure_ascii=False),
        json.dumps(results), json.dumps(row.get("values") or []),
        sum(1 for r in results if r != 3), len(rounds), items_total,
        row.get("score_seq"), shard,
    )

    round_tuples = []
    item_tuples = []
    for ri, rd in enumerate(rounds, start=1):
        items = rd.get("items") or []
        round_tuples.append((key, ri, rd.get("health"), rd.get("stamina"), len(items)))
        for si, it in enumerate(items):
            gems = it.get("g")
            item_tuples.append((key, ri, si, it.get("gid"), it.get("x"), it.get("y"),
                                it.get("f"), json.dumps(gems) if gems else None, it.get("pd")))
    return run_tuple, round_tuples, item_tuples


SQL_RUN = """INSERT OR IGNORE INTO corpus_runs(
    record_key, rating, rating_bucket, class_id, class_name, snapshots_json,
    results_json, values_json, rounds_played, round_snapshots, items_total,
    score_seq, shard)
    VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)"""

SQL_ROUND = ("INSERT OR IGNORE INTO corpus_rounds"
             "(record_key, round_no, health, stamina, item_count) VALUES (?,?,?,?,?)")

SQL_ITEM = ("INSERT OR IGNORE INTO corpus_items"
            "(record_key, round_no, seq, gid, x, y, face, gems_json, pd)"
            " VALUES (?,?,?,?,?,?,?,?,?)")


def ingest_corpus(conn: sqlite3.Connection, corpus_dir: Path, *,
                  include_parts: bool = False,
                  dated_only: bool = True,
                  limit_runs: int | None = None,
                  batch: int = 2000,
                  defer_indexes: bool = True) -> dict:
    """把语料写入数据库（批量 executemany）。

    dated_only=True（默认）只处理 YYYY-MM-DD 分片，跳过 undated 与 undated_parts。
    如需 undated，显式传 dated_only=False。

    性能要点：
    - 用 executemany 批量插入（逐条 execute 慢一个数量级）
    - defer_indexes=True 时先删二级索引、插完再建，可显著提速
    - batch 局提交一次事务
    """
    stats = {"runs": 0, "inserted": 0, "rounds": 0, "items": 0}
    started = datetime.now(timezone.utc)

    base = Path(corpus_dir)
    files = sorted(base.glob("*.bin.gz"))
    if dated_only:
        # 只保留 YYYY-MM-DD.bin.gz；排除 undated.bin.gz 与 undated_parts
        files = [f for f in files if not f.name.startswith("undated")]
    if include_parts and (base / "undated_parts").is_dir():
        files += sorted((base / "undated_parts").glob("*.bin.gz"))

    indexes = ("idx_runs_rating", "idx_runs_class", "idx_rounds_key",
               "idx_items_gid", "idx_items_pos")
    if defer_indexes:
        for name in indexes:
            conn.execute(f"DROP INDEX IF EXISTS {name}")
        conn.commit()

    run_rows: list[tuple] = []
    round_rows: list[tuple] = []
    item_rows: list[tuple] = []
    seen_keys: set[str] = set()

    def flush() -> None:
        nonlocal run_rows, round_rows, item_rows
        if not run_rows:
            return
        with conn:
            conn.executemany(SQL_RUN, run_rows)
            if round_rows:
                conn.executemany(SQL_ROUND, round_rows)
            if item_rows:
                conn.executemany(SQL_ITEM, item_rows)
        run_rows, round_rows, item_rows = [], [], []

    for f in files:
        for row in iter_corpus_one(f):
            if limit_runs is not None and stats["runs"] >= limit_runs:
                break
            stats["runs"] += 1
            run_tuple, rt, it = _row_to_tuples(row, f.name)
            if run_tuple is None:
                continue
            key = run_tuple[0]
            if key in seen_keys:
                continue
            seen_keys.add(key)
            run_rows.append(run_tuple)
            round_rows.extend(rt)
            item_rows.extend(it)
            stats["inserted"] += 1
            stats["rounds"] += len(rt)
            stats["items"] += len(it)
            if len(run_rows) >= batch:
                flush()
        flush()
        if limit_runs is not None and stats["runs"] >= limit_runs:
            break
    flush()

    if defer_indexes:
        for ddl in (
            "CREATE INDEX IF NOT EXISTS idx_runs_rating ON corpus_runs(rating)",
            "CREATE INDEX IF NOT EXISTS idx_runs_class ON corpus_runs(class_id)",
            "CREATE INDEX IF NOT EXISTS idx_rounds_key ON corpus_rounds(record_key)",
            "CREATE INDEX IF NOT EXISTS idx_items_gid ON corpus_items(gid)",
            "CREATE INDEX IF NOT EXISTS idx_items_pos ON corpus_items(x, y)",
        ):
            conn.execute(ddl)
        conn.commit()

    stats["elapsed_seconds"] = round((datetime.now(timezone.utc) - started).total_seconds(), 1)
    return stats


def iter_corpus_one(path: Path) -> Iterator[dict]:
    from bpb_research.corpus.official import iter_rows
    yield from iter_rows(path)


def summary(conn: sqlite3.Connection) -> dict:
    def one(sql: str, *a):
        r = conn.execute(sql, a).fetchone()
        return r[0] if r else 0

    return {
        "runs": one("SELECT COUNT(*) FROM corpus_runs"),
        "rounds": one("SELECT COUNT(*) FROM corpus_rounds"),
        "items": one("SELECT COUNT(*) FROM corpus_items"),
        "distinct_gid": one("SELECT COUNT(DISTINCT gid) FROM corpus_items"),
        "with_gems": one("SELECT COUNT(*) FROM corpus_items WHERE gems_json IS NOT NULL"),
        "master_plus": one("SELECT COUNT(*) FROM corpus_runs WHERE rating >= 400"),
        "by_bucket": {r[0] or "?": r[1] for r in conn.execute(
            "SELECT rating_bucket, COUNT(*) FROM corpus_runs GROUP BY rating_bucket ORDER BY COUNT(*) DESC")},
        "by_class": {r[0] or "?": r[1] for r in conn.execute(
            "SELECT class_name, COUNT(*) FROM corpus_runs GROUP BY class_name ORDER BY COUNT(*) DESC")},
    }