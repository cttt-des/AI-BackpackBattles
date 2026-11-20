"""Require the same strict per-fight C++ event streams in two corpus gates."""
import argparse
import hashlib
import json
from pathlib import Path

from check_native_corpus_gate import load_receipts, reference_index


STAGE = Path(__file__).resolve().parent
FIELDS = ("category", "cpp_events_sha256", "original_events_sha256", "original_boundaries_sha256",
          "reference_manifest_sha256", "ring_placement_lineups_sha256", "winner", "winner_match",
          "natural_ending_match", "strict_item_first", "strict_gem_first")


def read_gate(path, prefix):
    gate = json.loads(path.read_bytes())
    if not gate["complete"]:
        raise ValueError(f"Incomplete corpus gate: {path}")
    jobs = json.loads((STAGE / "native_host_phases_reuse_plan.json").read_bytes())
    names = [row["name"].removeprefix("native_") for row in jobs]
    names.extend(("host_rng_phases_new_expand", "host_phases_observed_base_current",
                  "host_phases_observed_base_last"))
    reports = [STAGE / (prefix + name) / ("cpp" if name.endswith("observed_base_current") else "")
               for name in names]
    records, runtime = load_receipts(reports, gate["dll_sha256"])
    if runtime != gate["runtime_data_sha256"]:
        raise ValueError(f"Receipt runtime data differs from {path}")
    return gate, records


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baseline", type=Path, required=True)
    parser.add_argument("--candidate", type=Path, required=True)
    parser.add_argument("--baseline-prefix", required=True)
    parser.add_argument("--candidate-prefix", required=True)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    baseline, old = read_gate(args.baseline, args.baseline_prefix)
    candidate, new = read_gate(args.candidate, args.candidate_prefix)
    for field in ("runtime_data_sha256", "host_observed_plan_sha256", "ring_placement_lineups_sha256"):
        if baseline[field] != candidate[field]:
            raise ValueError(f"Gate provenance differs for {field}")

    references = reference_index(STAGE / "native_host_observed_reference_plan.json")
    counts, digest = {}, hashlib.sha256()
    for cohort, rows in references.items():
        for case_id, ref in sorted(rows.items()):
            before, after = old[ref["path"]][case_id], new[ref["path"]][case_id]
            if before["category"] != "pass" or not before["cpp_events_sha256"]:
                raise ValueError(f"Missing strict event stream for {case_id}")
            for field in FIELDS:
                if before.get(field) != after.get(field):
                    raise ValueError(f"{case_id} differs in {field}")
            digest.update(f"{case_id} {before['cpp_events_sha256']}\n".encode())
        counts[cohort] = len(rows)
    report = {"baseline_dll_sha256": baseline["dll_sha256"], "candidate_dll_sha256": candidate["dll_sha256"],
              "runtime_data_sha256": candidate["runtime_data_sha256"],
              "unchanged_cpp_event_streams": sum(counts.values()), "cohorts": counts,
              "ordered_case_and_cpp_event_hashes_sha256": digest.hexdigest()}
    result = json.dumps(report, indent=2)
    args.out.write_text(result + "\n", encoding="utf8")
    print(result)


if __name__ == "__main__":
    main()
