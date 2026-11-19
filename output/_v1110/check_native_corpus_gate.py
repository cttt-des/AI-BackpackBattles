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


def reference_index(host_observed_plan=None):
    base = "native_shipping_base_pilot/base"
    base_tail = "native_shipping_base_tail/base"
    expand = "native_shipping_expand_live/expand"
    base_ids = case_ids(STAGE / "native_shipping_full_base/fights.json", 914)
    base_tail_plan = STAGE / "native_shipping_base_tail_work.json"
    tail = read_json(base_tail_plan) if base_tail_plan.is_file() else []
    tail_ids = set(tail)
    if len(tail) != len(tail_ids) or not tail_ids <= base_ids:
        raise ValueError("Base tail contains cases outside the fixed 914-case table")
    expand_ids = case_ids(STAGE / "native_shipping_full_expand/fights.json", 1690)
    retained = read_json(STAGE / "native_shipping_expand_retained.json")
    new = set(read_json(STAGE / "native_shipping_expand_work.json"))
    if len(retained) != 809 or len(new) != 881 or set(retained) & new or set(retained) | new != expand_ids:
        raise ValueError("Expanded reference groups do not partition the fixed 1690-case table")
    if case_ids(STAGE / expand / "cases.json", 881) != new:
        raise ValueError("Expanded recorder case table differs from the reference plan")
    rules = STAGE / "native_shipping_expand_runtime_overrides.json"
    if rules.is_file():
        for cid, entry in read_json(rules).items():
            previous = entry["previous"]
            if (retained.get(cid) != previous
                    or digest(STAGE / previous["path"] / cid / "events.json") != previous["events_sha256"]):
                raise ValueError(f"Original retained reference differs for {cid}")
            retained[cid] = entry["reference"]
    index = {
        "base": {cid: {"path": base_tail if cid in tail_ids else base} for cid in base_ids},
        "expand": retained | {cid: {"path": expand} for cid in new},
    }
    if host_observed_plan is not None:
        baseline_path = STAGE / "native_lovers_restart_full_corpus_gate.json"
        plan = read_json(host_observed_plan)
        if plan["baseline_gate_sha256"] != digest(baseline_path):
            raise ValueError("Host capture plan differs from its frozen full-corpus baseline")
        baseline = read_json(baseline_path)
        for cohort, refs in index.items():
            rows = plan["cases"][cohort]
            by_id = {row["case_id"]: row for row in rows}
            pending = baseline["cohorts"][cohort]["pending"]
            if len(rows) != len(by_id) or by_id.keys() != pending.keys():
                raise ValueError(f"Host capture plan must include all the previously nonpassing {cohort} cases")
            engine = read_json(STAGE / f"native_shipping_full_{cohort}" / "reference_manifest.json")
            for cid, row in by_id.items():
                previous = refs[cid]["path"]
                if (row["previous_reference"] != previous or row["previous_category"] != pending[cid]
                        or row["previous_events_sha256"] != digest(STAGE / previous / cid / "events.json")):
                    raise ValueError(f"Original reference changed for host capture case {cid}")
                refs[cid] = {"path": f"native_host_observed_{cohort}/{cohort}",
                             "engine_sha256": engine["engine_sha256"], "host_rng_observed": True}
    return index


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
        receipts = {}
        for path in folder.glob("run*.json"):
            row = read_json(path)
            if path.stem != row["caseId"]:
                raise ValueError(f"Receipt case ID differs from its filename in {path}")
            receipts[row["caseId"]] = row
        if len(receipts) != summary["total"]:
            raise ValueError(f"Receipt count differs from the summary in {folder}")
        previous = by_reference.setdefault(source, {})
        if previous.keys() & receipts.keys():
            raise ValueError(f"Two reports cover the same case in {source}")
        previous.update(receipts)
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
        if "engine_sha256" in expected:
            manifest = read_json(marker)
            if manifest.get("engine_sha256") != expected["engine_sha256"] or not manifest.get("shipping_engine"):
                raise ValueError(f"Replacement recording uses a different executable for {cid}")
        boundary_hash = None
        if expected.get("host_rng_observed"):
            boundaries = root / "boundaries.json"
            if not manifest.get("host_rng_game_sha256") or not isinstance(read_json(boundaries).get("host_rng_draws"), list):
                raise ValueError(f"Reference lacks the host observation for {cid}")
            boundary_hash = digest(boundaries)
        counts["recorded"] += 1
        raw_hash = digest(root / "events.json")
        if expected.get("events_sha256", raw_hash) != raw_hash:
            raise ValueError(f"Immutable recording changed for {cid}")
        row = reports.get(expected["path"], {}).get(cid)
        if row is None:
            pending[cid] = "verification_pending"
            continue
        if (row.get("original_events_sha256") != raw_hash
                or row.get("reference_manifest_sha256") != digest(marker)
                or (boundary_hash is not None and row.get("original_boundaries_sha256") != boundary_hash)):
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
    ap.add_argument("--report", type=Path, nargs="+", required=True, help="Disjoint strict C++ result directories")
    ap.add_argument("--host-observed-plan", type=Path, help="Use the preregistered host-observed reference recordings")
    ap.add_argument("--out", type=Path)
    args = ap.parse_args()
    dll_hash = digest(args.dll)
    reports, runtime_hash = load_receipts(args.report, dll_hash)
    cohorts = {name: check_cohort(index, reports) for name, index in reference_index(args.host_observed_plan).items()}
    complete = all(result["passed"] == result["expected"] for result in cohorts.values())
    data = {"complete": complete, "dll_sha256": dll_hash, "runtime_data_sha256": runtime_hash, "cohorts": cohorts}
    if args.host_observed_plan is not None:
        data["host_observed_plan_sha256"] = digest(args.host_observed_plan)
    if args.out:
        args.out.write_text(json.dumps(data, indent=2) + "\n", encoding="utf8")
    for name, result in cohorts.items():
        print(name, {key: value for key, value in result.items() if key != "pending"})
    return 0 if complete else 1


if __name__ == "__main__":
    raise SystemExit(main())
