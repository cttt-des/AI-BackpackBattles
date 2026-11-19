"""Freeze the remaining case IDs before collecting the missing host input."""
import hashlib
import json
from pathlib import Path

from check_native_corpus_gate import reference_index


stage = Path(__file__).resolve().parent
gate_path = stage / "native_lovers_restart_full_corpus_gate.json"
gate = json.loads(gate_path.read_bytes())
refs = reference_index()
head = stage / "native_lovers_restart_base_head_cpp/cpp"
tail = stage / "native_lovers_restart_base_tail_cpp/cpp"
plan = {
    "baseline_gate_sha256": hashlib.sha256(gate_path.read_bytes()).hexdigest(),
    "selection": "All nonpassing cases in the complete frozen C++ baseline, selected before recording",
    "recording": "Recovered 1.1.10 Main on the shipping executable; observe host RNG state without changing callbacks",
    "cases": {},
}
for cohort, counts in (("base", (914, 132)), ("expand", (1690, 19))):
    expected, remaining = counts
    status = gate["cohorts"][cohort]
    assert status["verified"] == status["recorded"] == expected
    assert len(status["pending"]) == remaining
    rows = []
    for cid, category in status["pending"].items():
        source = refs[cohort][cid]["path"]
        case = stage / source / cid
        assert "host_rng_draws" not in json.loads((case / "boundaries.json").read_bytes())
        winner_mismatch = False
        if cohort == "base":
            report = (head if source.endswith("base_pilot/base") else tail) / f"{cid}.json"
            winner_mismatch = json.loads(report.read_bytes()).get("winner_match") is False
        rows.append({
            "case_id": cid, "previous_category": category, "winner_mismatch": winner_mismatch,
            "previous_reference": source,
            "previous_events_sha256": hashlib.sha256((case / "events.json").read_bytes()).hexdigest(),
        })
    rows.sort(key=lambda row: (not row["winner_mismatch"], row["case_id"]))
    plan["cases"][cohort] = rows
    (stage / f"native_host_observed_{cohort}_ids.json").write_text(
        json.dumps([row["case_id"] for row in rows], indent=2) + "\n", encoding="utf8",
    )
(stage / "native_host_observed_reference_plan.json").write_text(
    json.dumps(plan, indent=2) + "\n", encoding="utf8",
)
print({key: len(value) for key, value in plan["cases"].items()})
