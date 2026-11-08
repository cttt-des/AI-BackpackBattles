"""Archive stable opponent caches with content deduplication and pinned decoding.

sync_opponents reads only the supplied game caches. Filtered snapshots preserve complete eligible records and source digests; a single SQLite transaction imports observations and incremental interpretations.
"""

import hashlib
import json
import os
import sqlite3
import time
from collections.abc import Mapping
from contextlib import closing, nullcontext
from dataclasses import dataclass, field
from datetime import datetime, timezone
from functools import cache
from importlib.resources import files
from pathlib import Path
from typing import Any

from bpb_research.builds import Build, CodecContext, decode_build, encode_build
from bpb_research.builds.model import build_to_dict
from bpb_research.godot.variant import decode_stored_variant, encode_stored_variant
from bpb_research.items.catalog import load_item_catalog
from bpb_research.items.model import ItemCatalog, ItemDefinition
from bpb_research.opponent_lock import opponent_lock
from bpb_research.opponents.acceptance import acceptance_fingerprint, assess_record
from bpb_research.opponents.decisions import filter_cohort, read_decision, save_decision
from bpb_research.opponents.encoding import decode_json, encode_json
from bpb_research.opponents.policy import utc_timestamp
from bpb_research.opponents.rules import (
    ValidationRules,
    current_rules,
)
from bpb_research.sources.retention import filter_pool

DECODER_VERSION: str = "build-v2"


@dataclass
class _ImportLookup:
    """Prefetch small content and observation indexes under the shared writer lock."""

    origins: dict[tuple[str, str], dict[str, Any]] = field(default_factory=dict)
    members: dict[str, list[tuple[int, str, int]]] = field(default_factory=dict)
    snapshots: dict[str, tuple[str, str, str]] = field(default_factory=dict)
    observations: dict[int, tuple[str, str, str]] = field(default_factory=dict)
    runs: dict[str, int] = field(default_factory=dict)
    rounds: dict[int, dict[int, tuple[str, int]]] = field(default_factory=dict)
    builds: set[str] = field(default_factory=set)
    checked_runs: set[int] = field(default_factory=set)

    def complete(self, run_id: int, row: list[Any]) -> bool:
        """Check round content once after the complete source record digest has matched."""
        if run_id in self.checked_runs:
            return True
        expected: dict[int, tuple[str, int]] = {
            number + 1: (_digest([row[7], text]), row[4][number])
            for number, text in enumerate(row[6])
        }
        existing: dict[int, tuple[str, int]] = self.rounds.get(run_id, {})
        if any(expected.get(number) != value for number, value in existing.items()):
            raise ValueError("Archived run rounds differ from their content")
        if existing != expected:
            return False
        self.checked_runs.add(run_id)
        return True

    def covered(self, snapshot_id: str, observed_at: str, time_source: str) -> bool:
        snapshot: tuple[str, str, str] | None = self.snapshots.get(snapshot_id)
        if snapshot is None:
            return False
        values: list[tuple[str, str, str] | None] = [snapshot]
        values.extend(
            self.observations.get(run_id)
            for _, _, run_id in self.members.get(snapshot_id, [])
        )
        return all(
            value is not None
            and (
                time_source != "server"
                or (value[2] == "server" and value[0] <= observed_at <= value[1])
            )
            for value in values
        )

    def observe(self, snapshot_id: str, observed_at: str, time_source: str) -> None:
        def updated(previous: tuple[str, str, str] | None) -> tuple[str, str, str]:
            if previous is None or (
                time_source == "server" and previous[2] != "server"
            ):
                return observed_at, observed_at, time_source
            if time_source != "server":
                return previous
            return (
                min(previous[0], observed_at),
                max(previous[1], observed_at),
                "server",
            )

        self.snapshots[snapshot_id] = updated(self.snapshots.get(snapshot_id))
        for _, _, run_id in self.members.get(snapshot_id, []):
            self.observations[run_id] = updated(self.observations.get(run_id))


def _import_lookup(
    connection: sqlite3.Connection, rules: ValidationRules
) -> _ImportLookup:
    lookup: _ImportLookup = _ImportLookup()
    if (
        connection.execute(sql("read", "version")).fetchone()[0] >= 5
        and connection.execute(sql("validation", "has_state")).fetchone()
    ):
        lookup.origins = {
            (row["source"], row["original_sha256"]): dict(row)
            for row in connection.execute(
                sql("validation", "known_origins"),
                {"fingerprint": acceptance_fingerprint(rules)},
            )
        }
    for row in connection.execute(sql("observations", "all_members")):
        lookup.members.setdefault(row["snapshot_id"], []).append(
            (row["cache_index"], row["record_sha256"], row["run_id"])
        )
    lookup.snapshots = {
        row["snapshot_id"]: (row["first_seen"], row["last_seen"], row["time_source"])
        for row in connection.execute(sql("observations", "snapshot_times"))
    }
    lookup.observations = {
        row["run_id"]: (row["first_seen"], row["last_seen"], row["time_source"])
        for row in connection.execute(sql("observations", "all"))
    }
    lookup.runs = {
        row["record_sha256"]: row["run_id"]
        for row in connection.execute(sql("read", "content_runs"))
    }
    for row in connection.execute(sql("read", "content_rounds")):
        lookup.rounds.setdefault(row["run_id"], {})[row["round_number"]] = (
            row["build_id"],
            row["result"],
        )
    lookup.builds = {
        row[0] for row in connection.execute(sql("read", "content_builds"))
    }
    return lookup


def sync_downloaded_opponents(
    *,
    database_dir: Path,
    catalog_path: Path | None = None,
    assets_manifest: Path | None = None,
    retention_days: int | None = None,
    as_of: datetime | None = None,
    validation_rules: ValidationRules | None = None,
    batch_id: str | None = None,
) -> dict[str, Any]:
    """Import all verified Steam download batches using the existing content keys.

    Args:
        database_dir: Archive root containing downloads/, snapshots/, and opponents.sqlite.
        catalog_path: Optional verified decoding catalog.
        assets_manifest: Optional resource manifest paired with the catalog.
        batch_id: Optional verified local batch identity to import exclusively.

    Returns:
        Aggregate additions, duplicates, batch count, final totals and decoding status.
    """
    rules: ValidationRules = validation_rules or current_rules()
    from bpb_research.opponents.retention import enforce_validation
    from bpb_research.runtime.opponents import _opponent_batch_session

    phase: float = time.perf_counter()
    with _opponent_batch_session():
        enforce_validation(database_dir, rules)
        with opponent_lock(database_dir):
            result: dict = _sync_downloaded_opponents(
                database_dir,
                catalog_path,
                assets_manifest,
                retention_days,
                as_of,
                rules,
                batch_id,
            )
    import_seconds: float = time.perf_counter() - phase
    phase = time.perf_counter()
    result.pop("_revision", None)
    result["retention"] = {
        "status": "manual_only",
        "removed": {key: 0 for key in ("runs", "rounds", "builds")},
        "reclaimed_bytes": 0,
    }
    result["timings"] = {
        "import_seconds": import_seconds,
        "maintenance_seconds": time.perf_counter() - phase,
    }
    result.pop("_revision", None)
    return result


def _sync_downloaded_opponents(
    database_dir: Path,
    catalog_path: Path | None,
    assets_manifest: Path | None,
    retention_days: int | None = None,
    as_of: datetime | None = None,
    validation_rules: ValidationRules | None = None,
    batch_id: str | None = None,
) -> dict[str, Any]:
    from bpb_research.opponents.batches import batch_receipt, cleanup_committed
    from bpb_research.runtime.opponents import downloaded_batches

    cleanup_committed(database_dir)

    from bpb_research.opponents.raw_batches import refresh_pending

    refresh_pending(database_dir, validation_rules or current_rules())

    manifests: dict[Path, dict[str, Any]] = {}
    batches: tuple[Path, ...] = downloaded_batches(database_dir, _manifests=manifests)
    if batch_id is not None:
        batches = tuple(batch for batch in batches if batch.name == batch_id)
    if not batches and not (database_dir / "opponents.sqlite").exists():
        raise ValueError(
            "No verified opponent downloads; run Download & Import Opponents first"
        )
    summary: dict[str, Any] = {
        "processed_batches": len(batches),
        "added": {key: 0 for key in ("snapshots", "runs", "rounds", "builds")},
        "observed_records": 0,
        "duplicate_records": 0,
        "discarded_records": 0,
        "unchanged_snapshots": 0,
        "imported_batches": 0,
        "skipped_batches": 0,
    }
    summary["processed_batches"] = len(batches)
    database: Path = database_dir / "opponents.sqlite"
    with closing(connect(database, writable=True)) as connection:
        before: dict = dict(connection.execute(sql("read", "counts")).fetchone())
        lookup: _ImportLookup = _import_lookup(
            connection, validation_rules or current_rules()
        )
        _verify_persistent_records(connection, lookup)
        for index, batch in enumerate(batches):
            last: bool = index == len(batches) - 1
            changes: int = connection.total_changes
            previous: sqlite3.Row | None = connection.execute(
                sql("storage", "latest_batch")
            ).fetchone()
            receipt: dict = batch_receipt(
                batch, manifests[batch], dict(previous) if previous else None
            )
            from bpb_research.opponents.evidence import read_batch_evidence

            evidence: list[dict] = read_batch_evidence(
                batch,
                minimum_rating=(
                    validation_rules or current_rules()
                ).policy.minimum_rating,
                receipt=receipt,
            )
            result: dict = _sync_opponents(
                sources={"full/steam": batch / "runs_steam.cache"},
                database=database,
                snapshots=database_dir / "snapshots",
                catalog_path=catalog_path if last else None,
                assets_manifest=assets_manifest if last else None,
                observed_at=manifests[batch]["completed_at"],
                validation_rules=validation_rules,
                _connection=connection,
                _count_totals=False,
                _lookup=lookup,
                _batch=receipt,
                _evidence=evidence,
            )
            summary[
                "imported_batches"
                if connection.total_changes != changes
                else "skipped_batches"
            ] += 1
            for key in (
                "observed_records",
                "duplicate_records",
                "discarded_records",
                "unchanged_snapshots",
            ):
                summary[key] += result[key]
            for key in (
                "resource_id",
                "decoded_builds",
                "tagged_runs",
                "decode_counts",
            ):
                if key in result:
                    summary[key] = result[key]
        if not batches and catalog_path:
            with connection:
                summary.update(_decode(connection, catalog_path, assets_manifest))
        if not batches:
            latest: sqlite3.Row | None = connection.execute(
                sql("storage", "latest_batch")
            ).fetchone()
            if latest is not None:
                counts: dict = json.loads(latest["summary_json"])["counts"]
                summary.update(
                    processed_batches=1,
                    skipped_batches=1,
                    unchanged_snapshots=1,
                    observed_records=counts["runs"],
                    duplicate_records=counts["runs"],
                )
                if summary.get("decoded_builds") or summary.get("tagged_runs"):
                    summary.update(imported_batches=1, skipped_batches=0)
        after: dict = dict(connection.execute(sql("read", "counts")).fetchone())
        summary["totals"] = after
        summary["added"] = {key: after[key] - before[key] for key in before}
        summary["_revision"] = connection.execute(
            sql("observations", "revision")
        ).fetchone()[0]
    cleanup_committed(database_dir)
    return summary


def _verify_persistent_records(
    connection: sqlite3.Connection, lookup: _ImportLookup
) -> None:
    """Check database-owned source evidence and repair only missing normalized rounds."""
    missing: list[tuple[dict, list]] = []
    records: dict[int, list] = {}
    for record in connection.execute(sql("read", "content_runs")):
        row: list = json.loads(record["raw_record_json"])
        if _digest([record["source"], row]) != record["record_sha256"]:
            raise ValueError("Archived original record checksum mismatch")
        records[record["run_id"]] = row
        if not lookup.complete(record["run_id"], row):
            missing.append((dict(record), row))
    for snapshot in connection.execute(sql("retention", "snapshots")):
        rows: list = [
            records[run_id]
            for _, _, run_id in lookup.members.get(snapshot["snapshot_id"], [])
        ]
        data: bytes = encode_stored_variant(rows)
        if hashlib.sha256(data).hexdigest() != snapshot["file_sha256"]:
            raise ValueError("Archived snapshot membership checksum mismatch")
        if (
            snapshot["archive_path"]
            and _stable_bytes(Path(snapshot["archive_path"])) != data
        ):
            raise ValueError("Corrupt archived snapshot")
    if not missing:
        return
    with connection:
        for record, row in missing:
            run_id: int = record["run_id"]
            connection.execute(sql("insert", "incomplete_run"), {"run_id": run_id})
            connection.execute(sql("insert", "repair_revision"))
            for index, code in enumerate(row[6]):
                if index + 1 in lookup.rounds.get(run_id, {}):
                    continue
                build_id: str = _digest([row[7], code])
                if build_id not in lookup.builds:
                    connection.execute(
                        sql("insert", "build"),
                        {
                            "build_id": build_id,
                            "record_version": row[7],
                            "encoded_build": code,
                        },
                    )
                connection.execute(
                    sql("insert", "round"),
                    {
                        "run_id": run_id,
                        "round_number": index + 1,
                        "build_id": build_id,
                        "result": row[4][index],
                    },
                )


@cache
def sql(group: str, name: str) -> str:
    """Read one named statement from packaged SQL resources."""
    text: str = files("bpb_research.opponents.sql").joinpath(group + ".sql").read_text()
    sections: list[str] = text.split("-- name: ")
    return next(
        section.split("\n", 1)[1]
        for section in sections[1:]
        if section.split("\n", 1)[0] == name
    )


def connect(
    database: Path, *, writable: bool = False, migrate_decisions: bool = True
) -> sqlite3.Connection:
    """Open a schema-checked archive, initializing only explicitly writable databases."""
    if writable:
        database.parent.mkdir(parents=True, exist_ok=True)
    connection: sqlite3.Connection = sqlite3.connect(
        database.resolve().as_uri() + ("?mode=rwc" if writable else "?mode=ro"),
        uri=True,
        timeout=30,
    )
    connection.row_factory = sqlite3.Row
    connection.create_function("decoded_text", 1, decode_json, deterministic=True)
    version: int = connection.execute(sql("read", "version")).fetchone()[0]
    if version not in (0, 1, 2, 3, 4, 5, 6, 7, 8, 9) or (version == 0 and not writable):
        connection.close()
        raise ValueError(f"Unsupported opponent database schema: {version}")
    if writable and version == 0:
        connection.executescript(
            files("bpb_research.opponents.sql").joinpath("schema.sql").read_text()
        )
    if writable and version < 2:
        connection.executescript(
            files("bpb_research.opponents.sql").joinpath("migrate_v2.sql").read_text()
        )
    if writable and version < 3:
        try:
            connection.executescript(
                files("bpb_research.opponents.sql")
                .joinpath("migrate_v3.sql")
                .read_text()
            )
            _restore_server_observations(connection, database.parent)
        except Exception:
            connection.rollback()
            connection.close()
            raise
    if writable and version < 4:
        connection.executescript(
            files("bpb_research.opponents.sql").joinpath("migrate_v4.sql").read_text()
        )
    if writable and version < 5:
        connection.executescript(
            files("bpb_research.opponents.sql").joinpath("migrate_v5.sql").read_text()
        )
    if writable and version < 6:
        connection.executescript(
            files("bpb_research.opponents.sql").joinpath("migrate_v6.sql").read_text()
        )
    if writable and version < 7 and migrate_decisions:
        connection.executescript(
            files("bpb_research.opponents.sql").joinpath("migrate_v7.sql").read_text()
        )
    if writable and version < 8 and (version >= 7 or migrate_decisions):
        connection.executescript(
            files("bpb_research.opponents.sql").joinpath("migrate_v8.sql").read_text()
        )
    if writable and version < 9 and (version >= 7 or migrate_decisions):
        connection.executescript(
            files("bpb_research.opponents.sql").joinpath("migrate_v9.sql").read_text()
        )
    connection.execute(sql("read", "foreign_keys"))
    return connection


def _observe(
    connection: sqlite3.Connection,
    snapshot_id: str,
    observed_at: str,
    time_source: str,
    lookup: _ImportLookup | None = None,
) -> None:
    params: dict = {
        "snapshot_id": snapshot_id,
        "observed_at": utc_timestamp(observed_at),
        "time_source": time_source,
    }
    connection.execute(sql("observations", "snapshot"), params)
    connection.execute(sql("observations", "runs"), params)
    if lookup is not None:
        lookup.observe(snapshot_id, params["observed_at"], time_source)


def _restore_server_observations(connection: sqlite3.Connection, root: Path) -> None:
    from bpb_research.runtime.opponents import verify_opponent_batch

    with connection:
        for row in connection.execute(sql("observations", "snapshot_times")).fetchall():
            first: str = utc_timestamp(row["first_seen"])
            last: str = utc_timestamp(row["last_seen"])
            if (first, last) != (row["first_seen"], row["last_seen"]):
                connection.execute(
                    sql("observations", "normalize_snapshot"),
                    {
                        "snapshot_id": row["snapshot_id"],
                        "first_seen": first,
                        "last_seen": last,
                    },
                )
        connection.execute(sql("observations", "restore_legacy_runs"))
        for path in sorted((root / "downloads").glob("*/manifest.json")):
            if path.parent.is_symlink():
                continue
            manifest: dict = json.loads(path.read_text())
            if manifest.get("status") != "complete":
                continue
            manifest = verify_opponent_batch(path.parent)
            params: dict = {
                "source": "full/steam",
                "original_sha256": manifest["files"]["runs_steam.cache"]["sha256"],
            }
            row: sqlite3.Row | None = connection.execute(
                sql("observations", "known_origin"), params
            ).fetchone()
            if row is None:
                row = connection.execute(
                    sql("observations", "known_snapshot"), params
                ).fetchone()
            if row is not None:
                _observe(connection, row[0], manifest["completed_at"], "server")


def _json(value: Any) -> str:
    return json.dumps(
        value,
        ensure_ascii=False,
        separators=(",", ":"),
        sort_keys=True,
        allow_nan=False,
    )


def _digest(value: Any) -> str:
    return hashlib.sha256(_json(value).encode()).hexdigest()


def _stable_bytes(path: Path) -> bytes:
    for _attempt in range(3):
        before: os.stat_result = path.stat()
        data: bytes = path.read_bytes()
        after: os.stat_result = path.stat()
        if (before.st_size, before.st_mtime_ns, before.st_ino) == (
            after.st_size,
            after.st_mtime_ns,
            after.st_ino,
        ) and data == path.read_bytes():
            return data
        time.sleep(0.1)
    raise RuntimeError(f"Cache changed during capture: {path}")


def item_tags(item_id: int, catalog: ItemCatalog) -> tuple[tuple[str, str], ...]:
    """Identify observed skill/subclass items using verified ItemBook rules."""
    item: ItemDefinition = catalog.get(item_id)
    attributes: dict[str, str] = dict(item.attributes)
    shop: str = attributes.get("shop", "")
    if item.identifier in ("Chrome Cube", "Gold Cube", "Plastic Cube", "Bismuth Cube"):
        shop = next(
            dict(value.attributes)["shop"]
            for value in catalog.items
            if value.identifier == "Hypercube"
        )
    tags: list[tuple[str, str]] = []
    if ">" in shop:
        tags.append(("subclass", shop.split(">", 1)[1]))
    if "Skill" in attributes.get("type", "").split():
        tags.append(("skill", str(item_id)))
    return tuple(tags)


def _decode(
    connection: sqlite3.Connection, catalog_path: Path, assets_manifest: Path | None
) -> dict[str, Any]:
    catalog: ItemCatalog = load_item_catalog(catalog_path)
    asset_path: str = str(assets_manifest.resolve()) if assets_manifest else ""
    if assets_manifest:
        manifest: dict = json.loads(assets_manifest.read_text())
        if (
            manifest["pck_sha256"] != catalog.pck_sha256
            or manifest["status"] != "complete"
        ):
            raise ValueError("Assets and catalog must share a verified PCK")
    resource_id: str = _digest(
        [
            catalog_path.read_text(),
            hashlib.sha256(assets_manifest.read_bytes()).hexdigest()
            if assets_manifest
            else "",
        ]
    )
    params: dict[str, Any] = {
        "resource_id": resource_id,
        "decoder_version": DECODER_VERSION,
        "assets_manifest_path": asset_path,
        "record_version": catalog.game_version,
    }
    if connection.execute(sql("read", "resource_exists"), params).fetchone() is None:
        connection.execute(
            sql("insert", "resource"),
            {
                **params,
                "game_version": catalog.game_version,
                "pck_sha256": catalog.pck_sha256,
                "catalog_path": str(catalog_path.resolve()),
                "assets_manifest_path": asset_path,
            },
        )
    pending: list[sqlite3.Row] = connection.execute(
        sql("read", "undecoded"), params
    ).fetchall()
    for row in pending:
        data: str | None = None
        error: str | None = None
        status: str = "decoded"
        try:
            context: CodecContext = CodecContext(row["record_version"], catalog)
            build: Build = decode_build(row["encoded_build"], context=context)
            if encode_build(build, context=context) != row["encoded_build"]:
                raise ValueError("Build round trip differs from original")
            data = _json(build_to_dict(build))
        except (ValueError, TypeError, IndexError) as exc:
            status = (
                "unsupported" if "Unsupported or unverified" in str(exc) else "failed"
            )
            error = str(exc)
        connection.execute(
            sql("insert", "decode"),
            {
                **params,
                "build_id": row["build_id"],
                "status": status,
                "decoded_json": encode_json(data),
                "error": error,
            },
        )
        connection.execute(
            sql("insert", "tag_invalidate"), {**params, "build_id": row["build_id"]}
        )
    untagged: list[sqlite3.Row] = connection.execute(
        sql("read", "untagged"), params
    ).fetchall()
    for run in untagged:
        run_params: dict = {**params, "run_id": run["run_id"]}
        connection.execute(sql("insert", "tag_clear"), run_params)
        for row in connection.execute(sql("read", "tag_rows"), run_params):
            for item in json.loads(row["decoded_json"])["items"]:
                for kind, value in item_tags(item["item_id"], catalog):
                    connection.execute(
                        sql("insert", "tag"),
                        {
                            **run_params,
                            "kind": kind,
                            "value": value,
                            "first_observed_round": row["round_number"],
                        },
                    )
        connection.execute(sql("insert", "tag_complete"), run_params)
    bindings: list = (
        connection.execute(sql("read", "unbound_runs"), params).fetchall()
        + connection.execute(sql("read", "repair_bindings"), params).fetchall()
    )
    for row in bindings:
        connection.execute(
            sql("insert", "binding"), {**params, "run_id": row["run_id"]}
        )
    return {
        "resource_id": resource_id,
        "decoded_builds": len(pending),
        "tagged_runs": len(untagged),
        "decode_counts": {
            row["status"]: row["count"]
            for row in connection.execute(sql("read", "failures"), params)
        },
    }


def sync_opponents(
    *,
    sources: dict[str, Path],
    database: Path,
    snapshots: Path,
    catalog_path: Path | None = None,
    assets_manifest: Path | None = None,
    retention_days: int | None = None,
    as_of: datetime | None = None,
    validation_rules: ValidationRules | None = None,
) -> dict[str, Any]:
    """Capture current candidate caches and merge them without importing local history.

    Args:
        sources: Source namespaces (such as full/steam) and downloaded cache files.
        database: Cumulative SQLite destination.
        snapshots: Content-addressed archive directory.
        catalog_path: Optional immutable catalog used to fill pending interpretations.
        assets_manifest: Optional completed visual resources paired with that catalog.

    Returns:
        Counts of new objects, repeated observations, and decoding outcomes.
    """
    rules: ValidationRules = validation_rules or current_rules()
    from bpb_research.opponents.retention import enforce_validation

    enforce_validation(database.parent, rules)
    with opponent_lock(database.parent):
        result: dict = _sync_opponents(
            sources=sources,
            database=database,
            snapshots=snapshots,
            catalog_path=catalog_path,
            assets_manifest=assets_manifest,
            cutoff=None,
            validation_rules=rules,
        )
    result["retention"] = {"status": "manual_only", "reclaimed_bytes": 0}
    return result


def _sync_opponents(
    *,
    sources: dict[str, Path],
    database: Path,
    snapshots: Path,
    catalog_path: Path | None = None,
    assets_manifest: Path | None = None,
    observed_at: str | None = None,
    cutoff: str | None = None,
    validation_rules: ValidationRules | None = None,
    _connection: sqlite3.Connection | None = None,
    _count_totals: bool = True,
    _lookup: _ImportLookup | None = None,
    _batch: dict | None = None,
    _evidence: list[dict] | None = None,
) -> dict[str, Any]:
    from bpb_research.runtime.opponents import (
        _verified_archive_bytes,
        _verified_cache_bytes,
    )

    captured: list[tuple[str, bytes, Path, Any, str, list[int], str, bool]] = []
    identities: dict[Path, tuple[int, ...]] = {}
    from bpb_research.runtime.resources import _identity

    rules: ValidationRules = validation_rules or current_rules()
    discarded: int = 0
    if rules.policy.api_only and _batch is None and sources:
        raise ValueError(
            "Formal opponent intake requires a verified Steam leaderboard batch receipt"
        )
    for source, path in sources.items():
        identities[path] = _identity(path)
        cache_time: str = utc_timestamp(
            datetime.fromtimestamp(path.stat().st_mtime, timezone.utc)
        )
        if cutoff and not observed_at and cache_time < cutoff:
            continue
        verified: bytes | None = _verified_cache_bytes(path)
        original: bytes = verified if verified is not None else _stable_bytes(path)
        original_digest: str = hashlib.sha256(original).hexdigest()
        known: Mapping[str, Any] | None = None
        if _lookup is not None:
            known = _lookup.origins.get((source, original_digest))
        elif database.is_file():
            with (
                closing(connect(database))
                if _connection is None
                else nullcontext(_connection) as lookup
            ):
                if (
                    lookup.execute(sql("read", "version")).fetchone()[0] >= 5
                    and lookup.execute(sql("validation", "has_state")).fetchone()
                ):
                    known = lookup.execute(
                        sql("validation", "known_origin"),
                        {
                            "fingerprint": acceptance_fingerprint(rules),
                            "source": source,
                            "original_sha256": original_digest,
                        },
                    ).fetchone()
        original_rows: list = decode_stored_variant(original)
        if rules.policy.api_only:
            receipt_summary: dict = json.loads(_batch["summary_json"])
            evidenced: set[str] = set(receipt_summary.get("source_records", [])) | set(
                json.loads(_batch["players_json"]).values()
            )
            if source != "full/steam" or any(
                _digest([source, row]) not in evidenced for row in original_rows
            ):
                raise ValueError(
                    "Opponent input is not covered by its Steam batch receipt"
                )
        if known is not None:
            indices = json.loads(known["original_indices_json"])
            rows = [original_rows[index] for index in indices]
        else:
            rows, indices = filter_pool(original, rules.policy.minimum_rating)
            kept, accepted_indices, _ = filter_cohort(rows, rules)
            indices = [indices[index] for index in accepted_indices]
            rows = kept
        discarded += len(original_rows) - len(rows)
        data: bytes = encode_stored_variant(rows)
        digest: str = hashlib.sha256(data).hexdigest()
        target: Path = snapshots / digest / path.name
        if known is not None and known["archive_path"]:
            archive: Path = Path(known["archive_path"])
            if not archive.is_file() or _verified_archive_bytes(archive) != data:
                raise ValueError(f"Corrupt archived snapshot: {archive}")
            identities[archive] = _identity(archive)
        covered: bool = False
        if known is not None:
            snapshot_id: str = _digest([source, digest])
            if known["snapshot_id"] != snapshot_id or known["file_sha256"] != digest:
                raise ValueError("Archived snapshot origin differs from its content")
            if _lookup is not None:
                members: list[tuple[int, str]] = [
                    (index, digest)
                    for index, digest, _ in _lookup.members.get(snapshot_id, [])
                ]
                covered = _lookup.covered(
                    snapshot_id,
                    utc_timestamp(observed_at or cache_time),
                    "server" if observed_at else "local_cache",
                )
            else:
                with (
                    closing(connect(database))
                    if _connection is None
                    else nullcontext(_connection) as lookup
                ):
                    members = [
                        tuple(row)
                        for row in lookup.execute(
                            sql("observations", "members"), {"snapshot_id": snapshot_id}
                        )
                    ]
                    covered = bool(
                        lookup.execute(
                            sql("observations", "covered"),
                            {
                                "snapshot_id": snapshot_id,
                                "observed_at": utc_timestamp(observed_at or cache_time),
                                "time_source": "server"
                                if observed_at
                                else "local_cache",
                            },
                        ).fetchone()[0]
                    )
            if members != [
                (index, _digest([source, row])) for index, row in enumerate(rows)
            ]:
                raise ValueError(
                    "Archived snapshot membership differs from its content"
                )
            if _lookup is not None:
                complete: bool = all(
                    [
                        _lookup.complete(run_id, row)
                        for (_, _, run_id), row in zip(
                            _lookup.members.get(snapshot_id, []), rows, strict=True
                        )
                    ]
                )
                covered = covered and complete
        captured.append(
            (
                source,
                data,
                target,
                rows,
                original_digest,
                indices,
                cache_time,
                covered,
            )
        )
    if not captured and not database.exists():
        raise FileNotFoundError("No opponent cache or existing database was found")
    for path in sources.values():
        _verified_cache_bytes(
            path, _check_only=True
        )  # Recheck the verified file identities before writing.
    if any(_identity(path) != identity for path, identity in identities.items()):
        raise ValueError("Opponent input changed before database import")
    connection: sqlite3.Connection = _connection or connect(database, writable=True)
    try:
        before: dict = (
            dict(connection.execute(sql("read", "counts")).fetchone())
            if _count_totals
            else {}
        )
        added: dict[str, int] = {
            key: 0 for key in ("snapshots", "runs", "rounds", "builds")
        }
        skipped: int = 0
        with connection:
            for (
                source,
                data,
                target,
                rows,
                original_digest,
                indices,
                cache_time,
                covered,
            ) in captured:
                if covered:
                    skipped += 1
                    continue
                digest = hashlib.sha256(data).hexdigest()
                snapshot_id: str = _digest([source, digest])
                exists: bool = (
                    connection.execute(
                        sql("read", "snapshot_exists"), (snapshot_id,)
                    ).fetchone()
                    is not None
                )
                captured_at: str = utc_timestamp(observed_at or cache_time)
                added["snapshots"] += connection.execute(
                    sql("insert", "snapshot"),
                    {
                        "snapshot_id": snapshot_id,
                        "source": source,
                        "file_sha256": digest,
                        "captured_at": captured_at,
                        "archive_path": "",
                    },
                ).rowcount
                connection.execute(
                    sql("insert", "origin"),
                    {
                        "source": source,
                        "original_sha256": original_digest,
                        "snapshot_id": snapshot_id,
                        "captured_at": captured_at,
                        "original_indices_json": _json(indices),
                        "validation_fingerprint": acceptance_fingerprint(rules),
                    },
                )
                if _lookup is not None:
                    _lookup.origins[(source, original_digest)] = {
                        "original_indices_json": _json(indices),
                        "snapshot_id": snapshot_id,
                        "archive_path": "",
                        "file_sha256": digest,
                    }
                if exists:
                    skipped += 1
                    if _lookup is None:
                        _observe(
                            connection,
                            snapshot_id,
                            captured_at,
                            "server" if observed_at else "local_cache",
                        )
                        continue
                for index, row in enumerate(rows):
                    record: dict = {
                        "record_sha256": _digest([source, row]),
                        "source": source,
                        "record_version": row[7],
                        "character_class": row[5],
                        "rating": row[2],
                        "raw_record_json": _json(row),
                    }
                    run_id: int | None = (
                        _lookup.runs.get(record["record_sha256"])
                        if _lookup is not None
                        else None
                    )
                    existing_run: bool = run_id is not None
                    if run_id is None:
                        added["runs"] += connection.execute(
                            sql("insert", "run"), record
                        ).rowcount
                        run_id = connection.execute(
                            sql("insert", "run_id"), record
                        ).fetchone()[0]
                        if _lookup is not None:
                            _lookup.runs[record["record_sha256"]] = run_id
                    decision: dict | None = read_decision(connection, run_id)
                    if decision is None or decision[
                        "fingerprint"
                    ] != acceptance_fingerprint(rules):
                        save_decision(connection, run_id, assess_record(row, rules))
                    if not exists:
                        connection.execute(
                            sql("insert", "membership"),
                            {
                                "snapshot_id": snapshot_id,
                                "cache_index": index,
                                "run_id": run_id,
                            },
                        )
                    if _lookup is not None and not exists:
                        _lookup.members.setdefault(snapshot_id, []).append(
                            (index, record["record_sha256"], run_id)
                        )
                    if _lookup is not None and _lookup.complete(run_id, row):
                        continue
                    if _lookup is not None and existing_run:
                        connection.execute(
                            sql("insert", "incomplete_run"), {"run_id": run_id}
                        )
                        connection.execute(sql("insert", "repair_revision"))
                    expected: dict[int, tuple[str, int]] = {
                        number + 1: (_digest([row[7], text]), row[4][number])
                        for number, text in enumerate(row[6])
                    }
                    existing: dict[int, tuple[str, int]] = (
                        _lookup.rounds.get(run_id, {}) if _lookup is not None else {}
                    )
                    if any(
                        expected.get(number) != value
                        for number, value in existing.items()
                    ):
                        raise ValueError(
                            "Archived run rounds differ from their content"
                        )
                    for round_index, text in enumerate(row[6]):
                        build_id: str = expected[round_index + 1][0]
                        if round_index + 1 in existing:
                            continue
                        if _lookup is None or build_id not in _lookup.builds:
                            added["builds"] += connection.execute(
                                sql("insert", "build"),
                                {
                                    "build_id": build_id,
                                    "record_version": row[7],
                                    "encoded_build": text,
                                },
                            ).rowcount
                            if _lookup is not None:
                                _lookup.builds.add(build_id)
                        added["rounds"] += connection.execute(
                            sql("insert", "round"),
                            {
                                "run_id": run_id,
                                "round_number": round_index + 1,
                                "build_id": build_id,
                                "result": row[4][round_index],
                            },
                        ).rowcount
                    if _lookup is not None:
                        _lookup.rounds[run_id] = expected
                        _lookup.checked_runs.add(run_id)
                _observe(
                    connection,
                    snapshot_id,
                    captured_at,
                    "server" if observed_at else "local_cache",
                    _lookup,
                )
            decoded: dict = (
                _decode(connection, catalog_path, assets_manifest)
                if catalog_path
                else {}
            )
            if _batch is not None:
                connection.execute(sql("storage", "commit_batch"), _batch)
                if _evidence:
                    from bpb_research.opponents.evidence import store_evidence

                    store_evidence(connection, _batch["batch_id"], _evidence)
            from bpb_research.opponents.public_identities import (
                ensure_public_identities,
            )

            ensure_public_identities(connection)
            if not captured or not all(entry[-1] for entry in captured):
                connection.execute(
                    sql("retirement", "validation_version"),
                    {
                        "version": rules.game_version,
                        "fingerprint": acceptance_fingerprint(rules),
                        "resource_path": str(rules.snapshot.resolve()),
                    },
                )
                connection.execute(sql("validation", "create_state"))
                current: sqlite3.Row | None = connection.execute(
                    sql("validation", "state")
                ).fetchone()
                if current is None or current[0] != acceptance_fingerprint(rules):
                    connection.execute(
                        sql("validation", "complete"),
                        {"fingerprint": acceptance_fingerprint(rules)},
                    )
        after: dict = (
            dict(connection.execute(sql("read", "counts")).fetchone())
            if _count_totals
            else {}
        )
        observed: int = sum(len(entry[3]) for entry in captured)
        return {
            **({"totals": after} if _count_totals else {}),
            "added": {key: after[key] - before[key] for key in before}
            if _count_totals
            else added,
            "unchanged_snapshots": skipped,
            "observed_records": observed,
            "discarded_records": discarded,
            "duplicate_records": observed - added["runs"],
            **decoded,
        }
    finally:
        if _connection is None:
            connection.close()
