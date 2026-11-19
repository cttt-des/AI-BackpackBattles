"""Count strict C++ receipts against the fixed 914 + 1690 original recordings."""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path


STAGE = Path(__file__).resolve().parent


def read_json(path):
    return json.loads(path.read_bytes())


def digest(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def case_ids(path, expected):
    rows = read_json(path)["cases"]
    ids = {row["case_id"] for row in rows}
    if len(rows) != expected or len(ids) != expected:
        raise ValueError(f"{path} has {len(rows)} rows and {len(ids)} unique cases, expected {expected}")
    return ids


def reference_index():
    base = "native_shipping_base_pilot/base"
    expand = "native_shipping_expand_live/expand"
    base_ids = case_ids(STAGE / base / "cases.json", 914)
    expand_ids = case_ids(STAGE / "native_shipping_full_expand/fights.json", 1690)
    retained = read_json(STAGE / "native_shipping_expand_retained.json")
    new = set(read_json(STAGE / "native_shipping_expand_work.json"))
    if len(retained) != 809 or len(new) != 881 or set(retained) & new or set(retained) | new != expand_ids:
        raise ValueError("Expanded reference groups do not partition the fixed 1690-case table")
    if case_ids(STAGE / expand / "cases.json", 881) != new:
        raise ValueError("Expanded recorder case table differs from the reference plan")
    return {
        "base": {cid: {"path": base} for cid in base_ids},
        "expand": retained | {cid: {"path": expand} for cid in new},
    }


def load_receipts(directories, dll_hash):
    by_reference = {}
    runtime_hashes = set()
    for folder in directories:
        summary = read_json(folder / "summary.json")
        if (summary["reference_mode"] != "native-only" or not summary["strict_gem_origins"]
                or not summary["strict_item_origins"] or summary["dll_sha256"] != dll_hash):
            raise ValueError(f"Receipt mode, identity checks or candidate hash differs in {folder}")
        runtime_hashes.add(summary["runtime_data_sha256"])
        source = Path(summary["original_dir"]).resolve().relative_to(STAGE).as_posix()
        if source in by_reference:
            raise ValueError(f"Multiple reports supplied for {source}")
        receipts = {}
        for path in folder.glob("run*.json"):
            row = read_json(path)
            if path.stem != row["caseId"]:
                raise ValueError(f"Receipt case ID differs from its filename in {path}")
            receipts[row["caseId"]] = row
        if len(receipts) != summary["total"]:
            raise ValueError(f"Receipt count differs from the summary in {folder}")
        by_reference[source] = receipts
    if len(runtime_hashes) != 1:
        raise ValueError("The reports use different runtime data")
    return by_reference, next(iter(runtime_hashes))


def check_cohort(index, reports):
    counts = Counter(expected=len(index))
    pending = {}
    for cid, expected in sorted(index.items()):
        root = STAGE / expected["path"] / cid
        marker = root / "reference_manifest.json"
        if not marker.is_file():
            pending[cid] = "recording_pending"
            continue
        counts["recorded"] += 1
        raw_hash = digest(root / "events.json")
        if expected.get("events_sha256", raw_hash) != raw_hash:
            raise ValueError(f"Immutable recording changed for {cid}")
        row = reports.get(expected["path"], {}).get(cid)
        if row is None:
            pending[cid] = "verification_pending"
            continue
        if (row.get("original_events_sha256") != raw_hash
                or row.get("reference_manifest_sha256") != digest(marker)):
            pending[cid] = "receipt_source_mismatch"
            continue
        counts["verified"] += 1
        if row.get("winner_match") is False:
            counts["winner_mismatch"] += 1
        if (row["category"] == "pass" and row.get("winner_match") is True
                and row.get("natural_ending_match") is True and row.get("cpp_events_sha256")
                and row.get("strict_gem_first") is None and row.get("strict_item_first") is None):
            counts["passed"] += 1
        else:
            pending[cid] = row["category"]
    return {key: counts[key] for key in ("expected", "recorded", "verified", "passed", "winner_mismatch")} | {
        "pending": pending
    }


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--dll", type=Path, required=True)
    ap.add_argument("--report", type=Path, nargs="+", required=True, help="One strict C++ output directory per reference source")
    ap.add_argument("--out", type=Path)
    args = ap.parse_args()
    dll_hash = digest(args.dll)
    reports, runtime_hash = load_receipts(args.report, dll_hash)
    cohorts = {name: check_cohort(index, reports) for name, index in reference_index().items()}
    complete = all(result["passed"] == result["expected"] for result in cohorts.values())
    data = {"complete": complete, "dll_sha256": dll_hash, "runtime_data_sha256": runtime_hash, "cohorts": cohorts}
    if args.out:
        args.out.write_text(json.dumps(data, indent=2) + "\n", encoding="utf8")
    for name, result in cohorts.items():
        print(name, {key: value for key, value in result.items() if key != "pending"})
    return 0 if complete else 1


if __name__ == "__main__":
    raise SystemExit(main())
