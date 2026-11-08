"""Fetch and verify high-rank Steam opponent batches with durable request pacing.

``fetch_opponents`` validates the full transport before retaining eligible metadata and a transport digest. ``verify_opponent_batch`` and ``downloaded_batches`` validate successful batches before reuse or archive import. Private operation sessions bound verified batch and archive bytes to 64 MiB, preserving file identity checks and full validation after eviction. Game files and saves are inputs only.
"""

import hashlib
import json
import os
import sys
import time
from collections import Counter, OrderedDict
from contextlib import contextmanager
from contextvars import ContextVar, Token
from dataclasses import dataclass, field
from datetime import datetime, timezone
from importlib.resources import files
from pathlib import Path
from typing import Any, Iterator

from bpb_research.datasets.provenance import fingerprint
from bpb_research.godot.pck import PckArchive, write_probe_pck
from bpb_research.godot.variant import decode_stored_variant, encode_stored_variant
from bpb_research.opponent_lock import opponent_lock
from bpb_research.opponents.acceptance import acceptance_fingerprint
from bpb_research.opponents.comparison import _compare_players, _player_records
from bpb_research.opponents.decisions import filter_cohort
from bpb_research.opponents.leaderboard import analyze_leaderboard
from bpb_research.opponents.policy import LeaderboardRange, collection_range
from bpb_research.opponents.rules import (
    ValidationRules,
    current_rules,
)
from bpb_research.runtime.assets import DEFAULT_USER_DIR
from bpb_research.runtime.engine import _run_probe
from bpb_research.sources import read_opponent_pool
from bpb_research.sources.opponent_pool import parse_opponent_pool
from bpb_research.sources.retention import POLICY, retained_rating
from bpb_research.sources.steam_metadata import convert_metadata, metadata_rating

_FORMAT: int = 3
_SUCCESS_DELAY: int = 1200
_FAILURE_DELAY: int = 300
_BATCH_CACHE_BYTES: int = 64 * 1024 * 1024


@dataclass(frozen=True)
class _VerifiedBatch:
    """Keep detached verified bytes and immutable filesystem identities for one batch."""

    manifest: bytes
    cache: bytes
    identities: tuple[tuple[Path, tuple[int, ...]], ...]


@dataclass
class _BatchSession:
    """Bound per-operation byte reuse without trusting results from an earlier round."""

    entries: OrderedDict[Path, _VerifiedBatch] = field(default_factory=OrderedDict)
    identities: dict[Path, tuple[tuple[Path, tuple[int, ...]], ...]] = field(
        default_factory=dict
    )
    archive_inodes: dict[tuple[int, int], Path] = field(default_factory=dict)
    archive_identities: dict[Path, tuple[int, ...]] = field(default_factory=dict)
    size: int = 0
    verified_batches: int = 0
    reused_batches: int = 0
    reused_payloads: int = 0

    def discard(self, path: Path) -> None:
        previous: _VerifiedBatch | None = self.entries.pop(path, None)
        if previous is not None:
            self.size -= len(previous.manifest) + len(previous.cache)

    def remember(self, path: Path, value: _VerifiedBatch) -> None:
        self.discard(path)
        size: int = len(value.manifest) + len(value.cache)
        if size > _BATCH_CACHE_BYTES:
            return
        while self.entries and self.size + size > _BATCH_CACHE_BYTES:
            first: Path = next(iter(self.entries))
            self.discard(first)
        self.entries[path] = value
        self.size += size


_BATCH_SESSION: ContextVar[_BatchSession | None] = ContextVar(
    "opponent_batch_session", default=None
)


@contextmanager
def _opponent_batch_session() -> Iterator[_BatchSession]:
    previous: _BatchSession | None = _BATCH_SESSION.get()
    if previous is not None:
        yield previous
        return
    session: _BatchSession = _BatchSession()
    token: Token[_BatchSession | None] = _BATCH_SESSION.set(session)
    try:
        yield session
    finally:
        _BATCH_SESSION.reset(token)


def _batch_identities(path: Path) -> tuple[tuple[Path, tuple[int, ...]], ...]:
    from bpb_research.runtime.resources import _identity

    return tuple(
        (candidate, _identity(candidate))
        for candidate in (
            path,
            path / "manifest.json",
            *(path / n for n in _REQUIRED),
            *(
                (path / "raw-response.json.gz",)
                if (path / "raw-response.json.gz").exists()
                else ()
            ),
        )
    )


def _verified_cache_bytes(path: Path, *, _check_only: bool = False) -> bytes | None:
    session: _BatchSession | None = _BATCH_SESSION.get()
    if session is None:
        return None
    actual: Path = path.parent.absolute()
    entry: _VerifiedBatch | None = session.entries.get(actual)
    identity: tuple[tuple[Path, tuple[int, ...]], ...] | None = session.identities.get(
        actual
    )
    if identity is not None and identity != _batch_identities(actual):
        session.discard(actual)
        raise ValueError("Opponent batch changed before archive import")
    if entry is None:
        if identity is not None and not _check_only:
            verify_opponent_batch(
                actual
            )  # Evicted bytes require full evidence validation.
            entry = session.entries.get(actual)
        if entry is None:
            return None
    session.entries.move_to_end(actual)
    session.reused_payloads += 1
    return entry.cache


def _verified_archive_bytes(path: Path) -> bytes:
    from bpb_research.runtime.resources import _identity

    actual: Path = path.absolute()
    identity: tuple[tuple[Path, tuple[int, ...]], ...] = ((actual, _identity(actual)),)
    session: _BatchSession | None = _BATCH_SESSION.get()
    if session is not None:
        previous_identity: tuple[int, ...] | None = session.archive_identities.get(
            actual
        )
        if previous_identity is not None and previous_identity != identity[0][1]:
            raise ValueError("Archived snapshot changed before import")
        session.archive_identities[actual] = identity[0][1]
    entry: _VerifiedBatch | None = session.entries.get(actual) if session else None
    if entry is not None:
        if entry.identities != identity:
            session.discard(actual)
            raise ValueError("Archived snapshot changed before import")
        session.entries.move_to_end(actual)
        session.reused_payloads += 1
        return entry.cache
    inode: tuple[int, int] = identity[0][1][
        5:7
    ]  # Target dev/inode follows the five link fields.
    previous: Path | None = session.archive_inodes.get(inode) if session else None
    shared: _VerifiedBatch | None = (
        session.entries.get(previous) if session and previous else None
    )
    if shared is not None and shared.identities[0][1][5:] == identity[0][1][5:]:
        if shared.identities != ((previous, _identity(previous)),):
            raise ValueError("Archived snapshot changed before import")
        session.entries.move_to_end(previous)
        session.reused_payloads += 1
        return shared.cache
    data: bytes = actual.read_bytes()
    if identity != ((actual, _identity(actual)),):
        raise ValueError("Archived snapshot changed during verification")
    if session is not None:
        session.remember(actual, _VerifiedBatch(b"", data, identity))
        session.archive_inodes[inode] = actual
    return data


_STEAM_RESULTS: dict[int, str] = {
    1: "k_EResultOK",
    2: "k_EResultFail",
    3: "k_EResultNoConnection",
    8: "k_EResultInvalidParam",
    9: "k_EResultFileNotFound",
    10: "k_EResultBusy",
    15: "k_EResultAccessDenied",
    16: "k_EResultTimeout",
    17: "k_EResultBanned",
    20: "k_EResultServiceUnavailable",
    21: "k_EResultNotLoggedOn",
    24: "k_EResultInsufficientPrivilege",
    25: "k_EResultLimitExceeded",
    26: "k_EResultRevoked",
    35: "k_EResultConnectFailed",
    37: "k_EResultIOFailure",
    38: "k_EResultRemoteDisconnect",
    43: "k_EResultAccountDisabled",
    84: "k_EResultRateLimitExceeded",
    105: "k_EResultIPBanned",
}
_DIAGNOSTIC_STAGES: tuple[str, ...] = (
    "initialization",
    "session",
    "leaderboard",
    "entries",
    "ugc",
    "complete",
    "output",
)
_DIAGNOSTIC_ERRORS: tuple[str, ...] = (
    "Invalid opponent request manifest",
    "Missing, duplicate, or out-of-range leaderboard positions",
    "Steam initialization failed",
    "Expected an online Steam session for AppID 2427700",
    "Steam query timed out",
    "Leaderboard bpb-runs3 not found",
    "Leaderboard returned no usable UGC references",
    "Could not create UGC details query",
    "Could not request UGC metadata",
    "UGC request failed or returned an incomplete page",
    "Cannot write opponent response",
)
_PCK: str = "db6748170c3173bb8c6a9b91370465bfc86fb30341a7a0ddc8bfc8d3381f4817"
_SCRIPTS: tuple[tuple[str, str], ...] = (
    (
        "res://Core/Game.gde",
        "1a3261b09a6d98ad3556a8a307bedf0b6bf4e23185f639fc32517b8ab456b6b7",
    ),
    (
        "res://Core/RunDatabase.gde",
        "d5a23a5e8174496a308a7207236ffa0b0f2f65f91b154340ca8940bf8b7d43f0",
    ),
    (
        "res://Core/SteamWorkshop.gde",
        "d80b1a356aeada21f621b48fa78a89baefcdbe5ea3e332cacd17fc49239a0be8",
    ),
    (
        "res://Utility/RunData.gde",
        "ca42cf88ea808a988b26a56e8a2b394b55c4984f5b96b69efa5cecc8e86f601d",
    ),
    (
        "res://Utility/BitStream.gde",
        "f0b28eb183331fbddc0656661f2c4a46ee8a68793d509b762f82b9f224d0acb3",
    ),
    (
        "res://Utility/SkinBook.gde",
        "8e76efb26eb4db1aad70f30d09302b2121e127c1f8d03a28afd3647e260c772b",
    ),
)
_REQUEST: dict[str, Any] = {
    "app_id": 2427700,
    "board": "bpb-runs3",
    "start": 1,
    "end": 2000,
    "type": 0,
}
_REQUIRED: tuple[str, ...] = (
    "response.json",
    "entries.json",
    "metadata.json",
    "records.json",
    "runs_steam.cache",
    "export.log",
    "probe.pck",
    "run_engine.py",
    "steam_appid.txt",
)


def _validate_request(request: dict) -> LeaderboardRange:
    if (
        not isinstance(request, dict)
        or set(request) != set(_REQUEST)
        or any(request[key] != _REQUEST[key] for key in ("app_id", "board", "type"))
        or type(request["app_id"]) is not int
        or type(request["type"]) is not int
    ):
        raise ValueError("Unexpected Steam leaderboard request")
    return LeaderboardRange(request["start"], request["end"])


def _batch_request(output: Path) -> dict:
    manifest_path: Path = output / "manifest.json"
    manifest: dict = (
        json.loads(manifest_path.read_text()) if manifest_path.exists() else {}
    )
    request: dict = (
        manifest["request"]
        if manifest.get("schema_version") == _FORMAT
        else manifest.get("request", dict(_REQUEST))
    )
    _validate_request(request)
    return request


def _batch_summary(manifest: dict) -> dict:
    summary: dict = {"request": manifest.get("request", dict(_REQUEST))}
    if "leaderboard_analysis" in manifest:
        summary["leaderboard_analysis"] = manifest["leaderboard_analysis"]
    if "recovery" in manifest:
        summary["recovery"] = manifest["recovery"]
    return summary


def _write_json(path: Path, value: Any) -> None:
    temporary: Path = path.with_suffix(path.suffix + ".tmp")
    temporary.write_text(
        json.dumps(value, ensure_ascii=False, indent=2, allow_nan=False) + "\n",
        encoding="utf-8",
    )
    os.replace(temporary, path)


@contextmanager
def _locked(root: Path) -> Iterator[None]:
    root.mkdir(parents=True, exist_ok=True)
    import fcntl  # Keep offline archive imports usable outside the WSL fetch environment.

    with (root / ".fetch.lock").open("a") as stream:
        try:
            fcntl.flock(stream, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError as error:
            raise RuntimeError("Another opponent fetch is running") from error
        try:
            yield
        finally:
            fcntl.flock(stream, fcntl.LOCK_UN)


def _protocol(game_dir: Path, windows_python: Path) -> dict[str, Any]:
    from bpb_research.runtime.resources import _game_input_fingerprints

    inputs: dict[str, Any] = _game_input_fingerprints(game_dir)
    if not windows_python.is_file():
        raise FileNotFoundError(f"Windows Python not found: {windows_python}")
    if inputs["pck"]["sha256"] != _PCK:
        raise ValueError(
            "Unverified game PCK; opponent protocol verification is required"
        )
    archive: PckArchive = PckArchive(game_dir / "BackpackBattles.pck")
    scripts: dict[str, str] = {
        name: hashlib.sha256(archive.read(name)).hexdigest() for name, _ in _SCRIPTS
    }
    if scripts != dict(_SCRIPTS):
        raise ValueError("Opponent protocol script fingerprint mismatch")
    inputs["scripts"] = scripts
    return inputs


def _prepare_probe(output: Path) -> None:
    config: bytes = b'config_version=4\n[application]\nconfig/name="BPB Opponent Research"\n[logging]\nfile_logging/enable_file_logging=false\n'
    write_probe_pck(
        output / "probe.pck",
        {
            "res://project.godot": config,
            "res://fetch_opponents.gd": files("bpb_research.runtime")
            .joinpath("probes/fetch_opponents.gd")
            .read_bytes(),
        },
    )
    (output / "steam_appid.txt").write_text("2427700\n", encoding="ascii")


def _ugc_id(entry: dict[str, Any]) -> str | None:
    details: list = entry.get("details", [])
    if len(details) < 2:
        return None
    upper, lower = (int(value) for value in details[:2])
    value: int = (upper << 32) | (lower & 0xFFFFFFFF)
    return str(value) if 0 < value < 1 << 63 else None


def _validate_response(response: dict, request: dict | None = None) -> None:
    selected: dict = _REQUEST if request is None else request
    interval: LeaderboardRange = _validate_request(selected)
    entries: list[dict] = response.get("entries", [])
    metadata: list[dict] = response.get("metadata", [])
    if (
        response.get("status") != "complete"
        or int(response.get("app_id", 0)) != 2427700
        or response.get("leaderboard_name") != "bpb-runs3"
    ):
        raise ValueError("Incomplete or unexpected Steam response")
    sort_method: int = int(response.get("sort_method", {}).get("result", 0))
    if sort_method not in (1, 2):
        raise ValueError("Missing Steam leaderboard sort method")
    if response.get("entries_message") != "Leaderboard entries successfully retrieved":
        raise ValueError("Steam leaderboard download did not report success")
    ranks: list[int] = [int(entry["global_rank"]) for entry in entries]
    total: int = int(response["leaderboard_entry_count"])
    expected: int = max(0, min(interval.end, total) - interval.start + 1)
    if (
        total < 0
        or ranks != list(range(interval.start, interval.start + len(entries)))
        or len(entries) != expected
        or ("request" in response and response["request"] != selected)
    ):
        raise ValueError("Missing, duplicate, or out-of-range leaderboard positions")
    ids: list[str] = list(
        dict.fromkeys(value for entry in entries if (value := _ugc_id(entry)))
    )
    pages: list[dict] = response.get("pages", [])
    requested: list[str] = []
    for page in pages:
        page_ids: list[str] = page["requested_ids"]
        if (
            int(page["result"]) != 1
            or int(page["count"]) != len(page_ids)
            or not 1 <= len(page_ids) <= 1000
        ):
            raise ValueError("Failed or incomplete UGC page")
        requested.extend(page_ids)
    if requested != ids or len(metadata) != len(ids):
        raise ValueError("UGC pages do not cover all leaderboard references")
    by_id: dict[str, dict] = {}
    for record in metadata:
        details: dict = record["details"]
        identifier: str = str(details["file_id"])
        page_index: int = int(record["page"])
        if (
            not 0 <= page_index < len(pages)
            or identifier not in pages[page_index]["requested_ids"]
            or identifier in by_id
            or int(details["result"]) != 1
        ):
            raise ValueError("Duplicate, unexpected, or failed UGC item")
        by_id[identifier] = record
    if set(by_id) != set(ids):
        raise ValueError("UGC response identities differ from requested identities")


def _metadata_rating(record: dict) -> Any:
    try:
        return metadata_rating(record["metadata"])
    except (ValueError, TypeError, KeyError, AttributeError):
        return None


def _diagnostic_record(value: Any) -> dict[str, Any]:
    """Keep only bounded operational fields, excluding opponent payloads and IDs."""
    if not isinstance(value, dict):
        return {}
    record: dict[str, Any] = {}
    if value.get("stage") in _DIAGNOSTIC_STAGES:
        record["stage"] = value["stage"]
    if value.get("error") in _DIAGNOSTIC_ERRORS:
        record["error"] = value["error"]
    for key in (
        "result",
        "initialization_status",
        "page",
        "attempt",
        "requested",
        "returned",
        "elapsed_ms",
        "request_offset",
        "request_elapsed_ms",
        "request_count",
        "split_count",
    ):
        raw: Any = value.get(key)
        if (
            isinstance(raw, str)
            and raw.isascii()
            and raw.isdecimal()
            and len(raw) <= 10
        ):
            raw = int(raw)
        if type(raw) is int and 0 <= raw < 2**31:
            record[key] = raw
    if "result" in record:
        record["error_name"] = _STEAM_RESULTS.get(record["result"], "Unknown")
    return record


def _transport_diagnostics(response: Any) -> dict[str, Any]:
    """Project a probe's diagnostics without retaining arbitrary response fields."""
    if not isinstance(response, dict):
        return {}
    source: Any = response.get("diagnostics", {})
    if not source and isinstance(response.get("transport"), dict):
        source = response["transport"].get("diagnostics", {})
    record: dict[str, Any] = _diagnostic_record(source)
    if isinstance(source, dict) and isinstance(source.get("attempts"), list):
        record["attempts"] = [
            projected
            for attempt in source["attempts"][-8:]
            if (projected := _diagnostic_record(attempt))
        ]
    return record


def _fetch_failure_reason(batch: Path, error: BaseException) -> str:
    """Combine the retained probe failure with the process or verification error."""
    reason: str = str(error) or type(error).__name__
    try:
        response: dict = json.loads((batch / "response.json").read_text())
    except (OSError, ValueError):
        return reason
    transport: Any = response.get("transport", {}) if isinstance(response, dict) else {}
    diagnostic: dict = _diagnostic_record(
        transport.get("diagnostics") if isinstance(transport, dict) else None
    )
    if not diagnostic:
        return reason
    context: str = ", ".join(
        f"{key}={diagnostic[key]}"
        for key in (
            "stage",
            "result",
            "error_name",
            "initialization_status",
            "page",
            "attempt",
            "requested",
            "returned",
            "elapsed_ms",
            "request_offset",
            "request_elapsed_ms",
            "request_count",
            "split_count",
        )
        if key in diagnostic
    )
    return f"{diagnostic.get('error', reason)} [{context}]; {reason}"


def _project_response(
    response: dict,
    raw: bytes,
    *,
    verified: bool,
    rules: ValidationRules | None = None,
    request: dict | None = None,
) -> tuple[dict, list, list, list, dict]:
    started: float = time.perf_counter()
    request = dict(_REQUEST) if request is None else request
    analysis: dict = analyze_leaderboard(
        response,
        request,
        captured_at=datetime.fromtimestamp(
            int(response.get("entries_at_unix", time.time())), timezone.utc
        ).isoformat(),
        complete=verified,
    )
    selected: ValidationRules = rules or current_rules()
    entries: list[dict] = response.get("entries", [])
    metadata: list[dict] = response.get("metadata", [])
    by_id: dict[str, dict] = {
        str(item.get("details", {}).get("file_id")): item for item in metadata
    }
    kept_metadata: list[dict] = [
        item
        for item in metadata
        if retained_rating(_metadata_rating(item), selected.policy.minimum_rating)
    ]
    kept_entries: list[dict] = []
    rows: list[list[Any]] = []
    records: list[dict] = []
    discarded: int = 0
    unconverted: int = 0
    for index, entry in enumerate(entries):
        identifier: str | None = _ugc_id(entry)
        record: dict[str, Any] = {
            "entry_index": index,
            "workshop_id": identifier,
            "global_rank": int(entry["global_rank"]),
            "score": int(entry["score"]),
        }
        try:
            if identifier is None:
                raise ValueError("Entry has no valid Workshop reference")
            text: str = by_id[identifier]["metadata"]
            if metadata_rating(text) < selected.policy.minimum_rating:
                discarded += 1
                continue
            row, loadout = convert_metadata(text)
            kept_entries.append(entry)
            record.update(status="converted", cache_index=len(rows), loadout=loadout)
            rows.append(row)
        except (ValueError, TypeError, KeyError) as error:
            unconverted += 1
            record.update(status="unconverted", error=str(error))
        records.append(record)
    counts: dict = {
        "entries": len(entries),
        "ugc_items": len(by_id),
        "pages": len(response.get("pages", [])),
        "runs": len(rows),
        "rounds": sum(len(row[6]) for row in rows),
        "discarded": discarded,
        "unconverted": unconverted,
        "versions": dict(Counter(row[7] for row in rows)),
        "sort_method": int(response.get("sort_method", {}).get("result", 0)),
    }
    from bpb_research.opponents.store import _digest

    source_records: list[str] = sorted({_digest(["full/steam", row]) for row in rows})
    conversion_seconds: float = time.perf_counter() - started
    screening_started: float = time.perf_counter()
    accepted, indices, reasons = filter_cohort(rows, selected)
    from bpb_research.opponents.screening_maintenance import rejection_evidence

    exclusions: list[dict] = rejection_evidence(rows, [], selected)
    exclusions = [
        row
        for row in exclusions
        if row["categories"] or row["policy_reasons"] or row["hard_reasons"]
    ]
    screening_seconds: float = time.perf_counter() - screening_started
    accepted_ids: set[str] = {_ugc_id(kept_entries[index]) for index in indices}
    kept_entries = [kept_entries[index] for index in indices]
    converted_records: list[dict] = [
        record for record in records if record["status"] == "converted"
    ]
    records = [converted_records[index] for index in indices]
    for index, record in enumerate(records):
        record["cache_index"] = index
    kept_metadata = [
        item
        for item in kept_metadata
        if str(item["details"]["file_id"]) in accepted_ids
    ]
    counts.update(
        runs=len(accepted),
        rounds=sum(len(row[6]) for row in accepted),
        discarded=discarded + len(rows) - len(accepted),
        versions=dict(Counter(row[7] for row in accepted)),
    )
    counts["validation"] = reasons
    rows = accepted
    projection: dict = {
        "format": "retained-opponents-v3",
        "policy": POLICY,
        "transport": {
            "verified": verified,
            "original_sha256": hashlib.sha256(raw).hexdigest(),
            "original_bytes": len(raw),
            "request": dict(request),
        },
        "counts": counts,
        "validation": reasons,
        "leaderboard_analysis": analysis,
        "source_records": source_records,
        "rejections": exclusions,
        "phase_metrics": {
            "conversion_seconds": conversion_seconds,
            "screening_seconds": screening_seconds,
            "screening_input_runs": len(source_records),
            "screening_output_runs": len(accepted),
        },
    }
    diagnostics: dict = _transport_diagnostics(response)
    if diagnostics:
        projection["transport"]["diagnostics"] = diagnostics
    return projection, kept_entries, kept_metadata, records, rows


def _retain_response(
    output: Path, *, verified: bool = False, rules: ValidationRules | None = None
) -> dict:
    path: Path = output / "response.json"
    raw: bytes = path.read_bytes()
    response: dict = json.loads(raw)
    if response.get("format") in {"retained-opponents-v2", "retained-opponents-v3"}:
        if rules is not None and "counts" in response:
            refilter_opponent_batch(output, rules)
            response = json.loads(path.read_text())
        return response["counts"]
    compression_started: float = time.perf_counter()
    if verified:
        from bpb_research.opponents.raw_batches import capture_response

        capture_response(output, raw)
    compression_seconds: float = time.perf_counter() - compression_started
    projection, entries, metadata, records, rows = _project_response(
        response, raw, verified=verified, rules=rules, request=_batch_request(output)
    )
    projection["phase_metrics"].update(
        compression_seconds=compression_seconds,
        raw_bytes=len(raw),
        compressed_bytes=(output / "raw-response.json.gz").stat().st_size
        if verified
        else 0,
    )
    _write_json(output / "entries.json", entries)
    _write_json(output / "metadata.json", metadata)
    _write_json(output / "records.json", records)
    (output / "runs_steam.cache").write_bytes(encode_stored_variant(rows))
    _write_json(path, projection)
    return projection["counts"]


def refilter_opponent_batch(output: Path, rules: ValidationRules) -> None:
    """Reproject original evidence into both Master-cohort decision states."""
    response_path: Path = output / "response.json"
    projection: dict = json.loads(response_path.read_text())
    if projection.get("format") not in {
        "retained-opponents-v2",
        "retained-opponents-v3",
    }:
        _retain_response(output, verified=True, rules=rules)
        projection = json.loads(response_path.read_text())
    if projection.get("format") == "retained-opponents-v3" and projection.get(
        "validation", {}
    ).get("fingerprint") == acceptance_fingerprint(rules):
        return
    raw_path: Path = output / "raw-response.json.gz"
    if raw_path.is_file():
        import gzip

        raw: bytes = gzip.decompress(raw_path.read_bytes())
        if (
            hashlib.sha256(raw).hexdigest()
            != projection["transport"]["original_sha256"]
        ):
            raise ValueError("Original response changed before revalidation")
        response: dict = json.loads(raw)
        _validate_response(response, _batch_request(output))
        original_analysis: dict = projection["leaderboard_analysis"]
        projection, entries, metadata, records, accepted = _project_response(
            response, raw, verified=True, rules=rules, request=_batch_request(output)
        )
        projection["leaderboard_analysis"]["captured_at"] = original_analysis[
            "captured_at"
        ]  # A replay is not a new observation, including legacy responses without timestamps.
        if projection["leaderboard_analysis"] != original_analysis:
            raise ValueError(
                "Original leaderboard evidence changed during revalidation"
            )
        for name, data in (
            ("response.json", projection),
            ("entries.json", entries),
            ("records.json", records),
            ("metadata.json", metadata),
        ):
            _write_json(output / name, data)
        (output / "runs_steam.cache").write_bytes(encode_stored_variant(accepted))
        return
    rows: list = decode_stored_variant((output / "runs_steam.cache").read_bytes())
    accepted, indices, reasons = filter_cohort(rows, rules)
    entries: list = json.loads((output / "entries.json").read_text())
    records: list = json.loads((output / "records.json").read_text())
    metadata: list = json.loads((output / "metadata.json").read_text())
    entries = [entries[index] for index in indices]
    records = [records[index] for index in indices]
    ids: set[str] = {_ugc_id(entry) for entry in entries}
    for index, record in enumerate(records):
        record["cache_index"] = index
    metadata = [item for item in metadata if str(item["details"]["file_id"]) in ids]
    counts: dict = projection["counts"]
    counts.update(
        runs=len(accepted),
        rounds=sum(len(row[6]) for row in accepted),
        discarded=counts["discarded"] + len(rows) - len(accepted),
        versions=dict(Counter(row[7] for row in accepted)),
    )
    projection["format"] = "retained-opponents-v3"
    projection["validation"] = reasons
    counts["validation"] = reasons
    for name, data in (
        ("response.json", projection),
        ("entries.json", entries),
        ("records.json", records),
        ("metadata.json", metadata),
    ):
        _write_json(output / name, data)
    (output / "runs_steam.cache").write_bytes(encode_stored_variant(accepted))


def sanitize_failed_batch(output: Path, rules: ValidationRules | None = None) -> None:
    """Preserve original failed transport before rebuilding diagnostic projections."""
    path: Path = output / "response.json"
    if not path.is_file():
        return
    from bpb_research.opponents.raw_batches import RAW_NAME, capture_response

    if not (output / RAW_NAME).exists():
        capture_response(output, path.read_bytes())
    try:
        _retain_response(output, rules=rules)
    except (ValueError, TypeError, KeyError, AttributeError, IndexError):
        raw: bytes = path.read_bytes()
        diagnostics: dict = {}
        try:
            diagnostics = _transport_diagnostics(json.loads(raw))
        except ValueError:
            pass
        transport: dict = {
            "verified": False,
            "original_sha256": hashlib.sha256(raw).hexdigest(),
            "original_bytes": len(raw),
        }
        if diagnostics:
            transport["diagnostics"] = diagnostics
        _write_json(
            path,
            {
                "format": "retained-opponents-v3",
                "policy": POLICY,
                "transport": transport,
                "error": "Malformed transport retained in raw-response.json.gz",
            },
        )
        for name in ("entries.json", "metadata.json", "records.json"):
            _write_json(output / name, [])
        (output / "runs_steam.cache").write_bytes(encode_stored_variant([]))
    for path in output.glob("*.tmp"):
        if path.name.removesuffix(".tmp") in _REQUIRED:
            path.unlink()


def _convert_response(
    output: Path, rules: ValidationRules | None = None
) -> dict[str, Any]:
    try:
        response: dict = json.loads((output / "response.json").read_text())
        _validate_response(response, _batch_request(output))
    except (ValueError, TypeError, KeyError, AttributeError, IndexError):
        sanitize_failed_batch(output, rules=rules)
        raise
    counts: dict = _retain_response(output, verified=True, rules=rules)
    if counts["unconverted"]:
        raise ValueError(
            f"Steam metadata conversion failed for {counts['unconverted']} entries"
        )
    read_opponent_pool(output / "runs_steam.cache")
    return counts


def verify_opponent_batch(path: Path) -> dict[str, Any]:
    """Check a complete batch's protocol, required files, hashes, and cache counts."""
    path = path.absolute()
    session: _BatchSession | None = _BATCH_SESSION.get()
    entry: _VerifiedBatch | None = session.entries.get(path) if session else None
    if entry is not None:
        if entry.identities == _batch_identities(path):
            session.entries.move_to_end(path)
            session.reused_batches += 1
            return json.loads(entry.manifest)
        session.discard(path)
    before: tuple[tuple[Path, tuple[int, ...]], ...] = _batch_identities(path)
    if session is not None:
        session.verified_batches += 1
    manifest_bytes: bytes = (path / "manifest.json").read_bytes()
    manifest: dict = json.loads(manifest_bytes)
    if (
        manifest.get("status") != "complete"
        or manifest.get("schema_version") not in (1, 2, _FORMAT)
        or (
            manifest.get("schema_version") in (1, 2)
            and manifest.get("request") != _REQUEST
        )
    ):
        raise ValueError(f"Incomplete or incompatible opponent batch: {path}")
    interval: LeaderboardRange = _validate_request(manifest.get("request"))
    if manifest.get("inputs", {}).get("pck", {}).get("sha256") != _PCK or manifest[
        "inputs"
    ].get("scripts") != dict(_SCRIPTS):
        raise ValueError("Opponent batch protocol fingerprint mismatch")
    if set(manifest.get("files", {})) not in (
        set(_REQUIRED),
        {*_REQUIRED, "raw-response.json.gz"},
    ):
        raise ValueError("Opponent batch missing required evidence files")
    payloads: dict[str, bytes] = {}
    for name in _REQUIRED:
        payload: bytes = (path / name).read_bytes()
        if hashlib.sha256(payload).hexdigest() != manifest["files"][name]["sha256"]:
            raise ValueError(f"Opponent batch checksum mismatch: {name}")
        payloads[name] = payload
    cache: bytes = payloads["runs_steam.cache"]
    if "raw-response.json.gz" in manifest["files"]:
        raw_compressed: bytes = (path / "raw-response.json.gz").read_bytes()
        if (
            hashlib.sha256(raw_compressed).hexdigest()
            != manifest["files"]["raw-response.json.gz"]["sha256"]
        ):
            raise ValueError("Opponent original response checksum mismatch")
    if cache != (path / "runs_steam.cache").read_bytes():
        raise ValueError("Opponent cache changed during verification")
    runs = parse_opponent_pool(cache)
    if len(runs) != manifest["counts"]["runs"] or (
        manifest["schema_version"] == 1 and not runs
    ):
        raise ValueError("Opponent batch run count mismatch")
    if manifest["schema_version"] >= 2:
        projection: dict = json.loads(payloads["response.json"])
        if "raw-response.json.gz" in manifest["files"]:
            import gzip

            original: bytes = gzip.decompress(raw_compressed)
            if (
                len(original) != projection["transport"]["original_bytes"]
                or hashlib.sha256(original).hexdigest()
                != projection["transport"]["original_sha256"]
            ):
                raise ValueError(
                    "Compressed response differs from verified original input"
                )
        if (
            manifest.get("policy") != POLICY
            or projection.get("policy") != POLICY
            or not projection.get("transport", {}).get("verified")
            or projection.get("counts") != manifest["counts"]
            or projection.get("transport", {}).get("request") != manifest["request"]
            or any(not retained_rating(run.rating) for run in runs)
        ):
            raise ValueError(
                "Opponent batch retention or transport verification mismatch"
            )
        if manifest["schema_version"] == _FORMAT:
            analysis: dict = manifest.get("leaderboard_analysis", {})
            total: Any = analysis.get("leaderboard_entry_count")
            if (
                analysis.get("complete") is not True
                or analysis.get("ranks_contiguous") is not True
                or type(total) is not int
                or total < 0
                or analysis.get("entries")
                != max(0, min(interval.end, total) - interval.start + 1)
                or analysis.get("request") != manifest["request"]
                or analysis.get("entries") != manifest["counts"]["entries"]
                or analysis.get("sort_method") not in (1, 2)
                or analysis.get("sort_method") != manifest["counts"]["sort_method"]
                or projection.get("leaderboard_analysis") != analysis
            ):
                raise ValueError("Opponent batch leaderboard analysis mismatch")
        counts: dict = manifest["counts"]
        if (
            counts["entries"]
            != counts["runs"] + counts["discarded"] + counts["unconverted"]
            or counts["unconverted"]
        ):
            raise ValueError("Opponent batch processing counts mismatch")
        metadata: list = json.loads(payloads["metadata.json"])
        if any(not retained_rating(_metadata_rating(item)) for item in metadata):
            raise ValueError("Opponent batch contains non-retained metadata")
        records: list = json.loads(payloads["records.json"])
        entries: list = json.loads(payloads["entries.json"])
        by_id: dict = {str(item["details"]["file_id"]): item for item in metadata}
        rows: list = decode_stored_variant(cache)
        if len(records) != len(rows) or len(entries) != len(rows):
            raise ValueError("Opponent batch evidence count mismatch")
        if len(by_id) != len(metadata) or set(by_id) != {
            _ugc_id(entry) for entry in entries
        }:
            raise ValueError("Opponent batch retained identities mismatch")
        for index, (record, entry, row) in enumerate(zip(records, entries, rows)):
            identifier: str | None = _ugc_id(entry)
            original, loadout = convert_metadata(by_id[identifier]["metadata"])
            if (
                record["status"] != "converted"
                or record["cache_index"] != index
                or record["workshop_id"] != identifier
                or record["global_rank"] != int(entry["global_rank"])
                or not interval.start <= int(entry["global_rank"]) <= interval.end
                or record["loadout"] != loadout
                or original != row
            ):
                raise ValueError("Opponent batch original metadata differs from cache")
        if counts["rounds"] != sum(len(row[6]) for row in rows) or counts[
            "versions"
        ] != dict(Counter(row[7] for row in rows)):
            raise ValueError("Opponent batch retained counts mismatch")
    if before != _batch_identities(path):
        raise ValueError("Opponent batch changed during verification")
    if session is not None:
        session.identities[path] = before
        session.remember(path, _VerifiedBatch(manifest_bytes, cache, before))
    return manifest


def downloaded_batches(
    database_dir: Path, *, _manifests: dict[Path, dict[str, Any]] | None = None
) -> tuple[Path, ...]:
    """Return every verified successful download in capture order; reject corruption."""
    batches: list[Path] = []
    from bpb_research.opponents.raw_batches import transport_root

    paths: list[Path] = [
        *(database_dir / "downloads").glob("*/manifest.json"),
        *transport_root(database_dir).glob("*/manifest.json"),
    ]
    for manifest_path in sorted(paths, key=lambda p: p.parent.name):
        if manifest_path.parent.is_symlink() or manifest_path.parent.name.startswith(
            "."
        ):
            continue
        manifest: dict = json.loads(manifest_path.read_text())
        if manifest.get("status") == "complete":
            manifest = verify_opponent_batch(manifest_path.parent)
            if _manifests is not None:
                _manifests[manifest_path.parent] = manifest
            batches.append(manifest_path.parent)
    return tuple(batches)


def _batch_players(path: Path) -> dict[str, str] | None:
    manifest: dict = verify_opponent_batch(path)
    before: tuple[tuple[Path, tuple[int, ...]], ...] = _batch_identities(path)
    entries: bytes = (path / "entries.json").read_bytes()
    cache: bytes | None = _verified_cache_bytes(path / "runs_steam.cache")
    if cache is None:
        cache = (path / "runs_steam.cache").read_bytes()
    for name, data in (("entries.json", entries), ("runs_steam.cache", cache)):
        if hashlib.sha256(data).hexdigest() != manifest["files"][name]["sha256"]:
            raise ValueError(f"Opponent batch checksum mismatch: {name}")
    if before != _batch_identities(path):
        raise ValueError("Opponent batch changed during comparison")
    return _player_records(json.loads(entries), decode_stored_variant(cache))


def fetch_opponents(
    *,
    game_dir: Path,
    database_dir: Path,
    windows_python: Path,
    resume_batch: str | None = None,
) -> dict[str, Any]:
    """Download one Steam pool or reuse a checked batch during its 20-minute cooldown.

    Args:
        game_dir: Read-only installed game directory.
        database_dir: Project archive root; independent batches use downloads/.
        windows_python: Windows Python executable reachable through WSL.
        resume_batch: Optional local batch identity to recover without Steam requests.

    Returns:
        Batch path, downloaded/reused status, processing counts, and retained-player changes against the preceding successful batch.

    Raises:
        RuntimeError: A concurrent fetch, cooldown, or failed probe prevents completion.
        ValueError: A protocol or evidence validation fails.
    """
    interval: LeaderboardRange = collection_range(Path(__file__).resolve().parents[3])
    if database_dir.resolve().is_relative_to(
        game_dir.resolve()
    ) or database_dir.resolve().is_relative_to(DEFAULT_USER_DIR.resolve()):
        raise ValueError(
            "Opponent downloads must not write to game or save directories"
        )
    from bpb_research.opponents.rules import load_rules
    from bpb_research.runtime.resources import (
        _OPPONENT_SESSION,
        _OpponentResourceSession,
        require_game_resources,
    )

    print("正在准备并验证对手资源...", file=sys.stderr, flush=True)
    started: float = time.perf_counter()
    snapshot: Path = require_game_resources(
        game_dir=game_dir,
        output_root=database_dir / "resources",
    )
    rules: ValidationRules = load_rules(snapshot)
    session: _OpponentResourceSession | None = _OPPONENT_SESSION.get()
    if session is not None:
        session.snapshot = snapshot.resolve()
        session.rules = rules
    from bpb_research.opponents.retention import enforce_validation

    resources_seconds: float = time.perf_counter() - started
    recovered: dict | None = None
    if resume_batch is not None:
        from bpb_research.runtime.opponent_recovery import resume_opponent_batch

        with opponent_lock(database_dir):
            recovered = resume_opponent_batch(
                database_dir,
                resume_batch,
                rules=rules,
                inputs=_protocol(game_dir, windows_python),
            )
    validation_started: float = time.perf_counter()
    enforce_validation(database_dir, rules)
    validation_seconds: float = time.perf_counter() - validation_started
    with opponent_lock(database_dir):
        download_started: float = time.perf_counter()
        result: dict = (
            recovered
            if recovered is not None
            else _fetch_opponents(
                game_dir=game_dir,
                database_dir=database_dir,
                windows_python=windows_python,
                rules=rules,
                interval=interval,
            )
        )
    result["timings"] = {
        "resources_seconds": resources_seconds,
        "interpretation_repair_seconds": validation_seconds,
        "download_seconds": time.perf_counter() - download_started,
    }
    return result


def _fetch_opponents(
    *,
    game_dir: Path,
    database_dir: Path,
    windows_python: Path,
    rules: ValidationRules | None = None,
    interval: LeaderboardRange = LeaderboardRange(),
) -> dict[str, Any]:
    request: dict = {**_REQUEST, "start": interval.start, "end": interval.end}
    game_dir = game_dir.resolve()
    from bpb_research.opponents.raw_batches import transport_root

    root: Path = transport_root(database_dir.resolve())
    if root.is_relative_to(game_dir) or root.is_relative_to(DEFAULT_USER_DIR.resolve()):
        raise ValueError(
            "Opponent downloads must not write to game or save directories"
        )
    root.mkdir(parents=True, exist_ok=True)
    with _locked(root):
        from bpb_research.runtime.opponent_recovery import finish_recovery

        finish_recovery(root)
        for unfinished in root.glob("*/manifest.json"):
            if unfinished.parent.is_symlink():
                continue
            interrupted: dict = json.loads(unfinished.read_text())
            if (
                interrupted.get("schema_version") in (2, _FORMAT)
                and interrupted.get("status") == "running"
            ):
                sanitize_failed_batch(unfinished.parent, rules=rules)
                interrupted.update(
                    status="failed",
                    error="Interrupted transport sanitized; unclassified payloads discarded",
                    files={
                        name: fingerprint(unfinished.parent / name)
                        for name in _REQUIRED
                        if (unfinished.parent / name).is_file()
                    },
                )
                _write_json(unfinished, interrupted)
        from bpb_research.opponents.batches import cleanup_committed, committed_batches

        cleanup_committed(database_dir)
        if rules is not None:
            from bpb_research.opponents.raw_batches import refresh_pending

            refresh_pending(database_dir, rules)
        committed: dict[str, dict] = committed_batches(
            database_dir / "opponents.sqlite"
        )
        previous: dict | None = (
            next(reversed(committed.values())) if committed else None
        )
        pending: tuple[Path, ...] = downloaded_batches(database_dir)
        if pending:
            batch: Path = pending[0]
            manifest: dict = verify_opponent_batch(batch)
            return {
                "status": "reused",
                "batch_id": batch.name,
                "counts": manifest["counts"],
                **_batch_summary(manifest),
                "requested_request": request,
                "pending_import": True,
                "comparison": _compare_players(
                    _batch_players(batch),
                    json.loads(previous["players_json"]) if previous else None,
                    previous_batch_id=previous["batch_id"] if previous else None,
                    reused=True,
                ),
            }
        now: float = time.time()
        state_path: Path = root / "state.json"
        state_source: Path = (
            state_path if state_path.exists() else database_dir / "downloads/state.json"
        )
        state: dict = (
            json.loads(state_source.read_text()) if state_source.exists() else {}
        )
        latest: Path = root / "latest-success"
        if latest.exists() and not latest.is_symlink():
            raise FileExistsError("Refusing to replace non-symlink latest-success")
        if (
            previous is not None
            and now
            < datetime.fromisoformat(previous["completed_at"]).timestamp()
            + _SUCCESS_DELAY
        ):
            summary: dict = json.loads(previous["summary_json"])
            previous_request: dict = summary.get("request", dict(_REQUEST))
            if previous_request != request:
                remaining: int = (
                    int(
                        datetime.fromisoformat(previous["completed_at"]).timestamp()
                        + _SUCCESS_DELAY
                        - now
                    )
                    + 1
                )
                raise RuntimeError(
                    f"Opponent fetch cooldown after range change (local; no Steam request sent): wait {remaining} seconds"
                )
            return {
                **summary,
                "request": previous_request,
                "status": "reused",
                "comparison": _compare_players(
                    json.loads(previous["players_json"]),
                    None,
                    previous_batch_id=previous["batch_id"],
                    reused=True,
                ),
            }
        wait: float = float(state.get("next_allowed_at", 0)) - now
        if wait > 0:
            raise RuntimeError(
                f"Opponent fetch cooldown (local; no Steam request sent): wait {int(wait) + 1} seconds"
            )
        inputs: dict = _protocol(game_dir, windows_python)
        for failed in root.glob("*/manifest.json"):
            if failed.parent.is_symlink():
                continue
            prior: dict = json.loads(failed.read_text())
            if prior.get("status") == "failed":
                children: list[Path] = list(failed.parent.iterdir())
                if any(
                    child.is_symlink()
                    or not child.is_file()
                    or child.name
                    not in (*_REQUIRED, "manifest.json", "raw-response.json.gz")
                    for child in children
                ):
                    raise ValueError(
                        "Unrecognized failed batch evidence; refusing another download"
                    )
                _write_json(
                    root / "last-failure.json",
                    {
                        "batch_id": failed.parent.name,
                        "error": prior.get("error"),
                        "failed_at": prior.get("failed_at", prior.get("created_at")),
                        **_batch_summary(prior),
                    },
                )
        batch = root / datetime.now(timezone.utc).strftime("%Y%m%d_%H%M%S_%fZ")
        batch.mkdir()
        manifest = {
            "schema_version": _FORMAT,
            "policy": POLICY,
            "status": "running",
            "created_at": datetime.now(timezone.utc).isoformat(),
            "request": request,
            "inputs": inputs,
        }
        _write_json(batch / "manifest.json", manifest)
        _write_json(
            state_path,
            {"last_attempt_at": now, "next_allowed_at": now + _FAILURE_DELAY},
        )
        (batch / "export.log").write_text("Starting isolated Steam opponent fetch\n")
        temporary: Path = root / f".latest-success-{batch.name}"
        verified: bool = False
        try:
            print("正在下载 Steam 对手...", file=sys.stderr, flush=True)
            _prepare_probe(batch)
            probe_options: dict = (
                {"timeout_seconds": interval.timeout_seconds}
                if interval.timeout_seconds != 120
                else {}
            )
            _run_probe(
                game_dir / "BackpackBattles.exe",
                windows_python,
                batch,
                "fetch_opponents.gd",
                batch / "response.json",
                **probe_options,
            )
            counts: dict = _convert_response(batch, rules=rules)
            from bpb_research.runtime.resources import _clear_game_input_fingerprints

            _clear_game_input_fingerprints(game_dir)
            if _protocol(game_dir, windows_python) != inputs:
                raise ValueError("Game inputs changed during opponent fetch")
            manifest.update(
                status="complete",
                completed_at=datetime.now(timezone.utc).isoformat(),
                counts=counts,
                leaderboard_analysis=json.loads((batch / "response.json").read_text())[
                    "leaderboard_analysis"
                ],
                files={
                    name: fingerprint(batch / name)
                    for name in (*_REQUIRED, "raw-response.json.gz")
                },
            )
            _write_json(batch / "manifest.json", manifest)
            verify_opponent_batch(batch)
            verified = True
            comparison: dict = _compare_players(
                _batch_players(batch),
                json.loads(previous["players_json"]) if previous else None,
                previous_batch_id=previous["batch_id"] if previous else None,
                range_changed=previous is not None
                and json.loads(previous["summary_json"]).get("request", _REQUEST)
                != request,
            )
            _write_json(
                state_path,
                {
                    "last_attempt_at": now,
                    "next_allowed_at": time.time() + _SUCCESS_DELAY,
                },
            )
            if latest.exists() and not latest.is_symlink():
                raise FileExistsError("Refusing to replace non-symlink latest-success")
            temporary.symlink_to(batch.name, target_is_directory=True)
            os.replace(temporary, latest)
            return {
                "status": "downloaded",
                "batch_id": batch.name,
                "counts": counts,
                **_batch_summary(manifest),
                "comparison": comparison,
            }
        except (Exception, KeyboardInterrupt) as error:
            if verified:
                if isinstance(error, KeyboardInterrupt):
                    raise
                raise RuntimeError(
                    f"Verified opponent batch retained for retry: {error}"
                ) from error
            sanitize_failed_batch(batch, rules=rules)
            reason: str = _fetch_failure_reason(batch, error)
            manifest.update(
                status="failed",
                failed_at=datetime.now(timezone.utc).isoformat(),
                error=reason,
                files={
                    name: fingerprint(batch / name)
                    for name in _REQUIRED
                    if (batch / name).is_file()
                },
            )
            response_path: Path = batch / "response.json"
            if response_path.exists():
                analysis: dict | None = json.loads(response_path.read_text()).get(
                    "leaderboard_analysis"
                )
                if analysis is not None:
                    manifest["leaderboard_analysis"] = analysis
            _write_json(batch / "manifest.json", manifest)
            _write_json(
                state_path,
                {
                    "last_attempt_at": now,
                    "next_allowed_at": time.time() + _FAILURE_DELAY,
                },
            )
            if isinstance(error, KeyboardInterrupt):
                raise
            raise RuntimeError(
                f"Opponent fetch failed: {reason}; log: {batch / 'export.log'}"
            ) from error
        finally:
            if temporary.is_symlink():
                temporary.unlink()
