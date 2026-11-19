"""Compact, hashed evidence for a fixed native-reference timer comparison."""
from pathlib import Path
import hashlib
import json

stage = Path(__file__).resolve().parent
roots = [stage / name for name in ("native_kernel_baseline", "native_kernel_timers")]
alignments = [json.loads((root / "alignment.json").read_text("utf8")) for root in roots]
cpp = [json.loads((root / "cpp/summary.json").read_text("utf8")) for root in roots]
maps = [{row["caseId"]: row for row in alignment["perCase"]} for alignment in alignments]
assert set(maps[0]) == set(maps[1]) and len(maps[0]) == 100

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

cases = []
for cid, before in maps[0].items():
    after = maps[1][cid]
    reports = [json.loads((root / "cpp" / (cid + ".json")).read_text("utf8")) for root in roots]
    assert all(report["events_cpp_vs_gd"]["first_divergence"] is None for report in reports), cid
    row = {"case_id": cid, "before_pass": reports[0]["category"] == "pass", "after_pass": reports[1]["category"] == "pass",
           "native_winner": before["winner"]["oracle"], "before_winner": before["winner"]["gdcore"],
           "after_winner": after["winner"]["gdcore"], "native_event_count": before["oracleEvents"],
           "before_event_count": before["gdcoreEvents"], "after_event_count": after["gdcoreEvents"],
           "inputs_identical": sha(roots[0] / "fights" / cid / "lineups.json") == sha(roots[1] / "fights" / cid / "lineups.json"),
           "native_event_sha256": sha(stage / "native_corpus/expand" / cid / "events.json"),
           "native_boundary_sha256": sha(stage / "native_corpus/expand" / cid / "boundaries.json")}
    assert row["inputs_identical"]
    divergence = after.get("firstDivergence")
    if divergence:
        row["first"] = {"index": divergence.get("index"), "pair": divergence.get("pair"),
                        "native": divergence.get("oracle", {}).get("at_idx"),
                        "core": divergence.get("gdcore", {}).get("at_idx")}
    cases.append(row)

result = {"scope": "Recovered native 1.1.10 versus GD/pure Python/C++; the independent Oracle batch is separate, installation EXE cross-check pending",
          "cases": 100, "native_strict_event_passes": [report["passed"] for report in cpp],
          "native_winner_mismatches": [report["winner_mismatch"] for report in cpp],
          "fixed": [row["case_id"] for row in cases if not row["before_pass"] and row["after_pass"]],
          "regressed": [row["case_id"] for row in cases if row["before_pass"] and not row["after_pass"]],
          "gd_py_cpp_event_match": 100, "details": cases,
          "cpp_summary_sha256": [sha(root / "cpp/summary.json") for root in roots],
          "dll_sha256": [sha(roots[0] / "bin/libgdcore.dll"), sha(stage / "sim_native/native_sim_cpp/native_sim/libgdcore.dll")],
          "gd_core_source_lines": {name: {"v1": len((stage / "sim/gd_core" / name).read_text("utf8").splitlines()),
                                          "candidate": len((stage / "sim_native/gd_core" / name).read_text("utf8").splitlines())}
                                   for name in ("CoreTimer.gd", "CoreBuff.gd", "CoreCharacter.gd")},
          "recipe_sha256": {name: sha(stage / name) for name in ("stage_native_core.py", "stage_native_metadata.py", "stage_native_timers.py", "optimize_native_float.py")}}
(roots[1] / "compact_report.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
print(json.dumps({key: value for key, value in result.items() if key not in ("details", "recipe_sha256")}, ensure_ascii=False, indent=2))
