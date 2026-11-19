"""Re-run preverified fixtures in a compiled Python build and compare raw events."""
from pathlib import Path
import argparse
import hashlib
import json
import sys


stage = Path(__file__).resolve().parent
parser = argparse.ArgumentParser()
parser.add_argument("--fixtures", required=True)
parser.add_argument("--compiled", required=True)
parser.add_argument("--out", required=True)
args = parser.parse_args()
fixtures = stage / args.fixtures
compiled = stage / args.compiled
out = stage / args.out
assert (fixtures / "fixtures.json").is_file() and (compiled / "tools/verify_oracle.py").is_file()
assert not out.exists(), out
sys.path[:0] = [str(compiled), str(compiled / "tools")]
import verify_oracle

verify_oracle.CASES_JSON = str(fixtures / "fixtures.json")
verify_oracle.FIGHTS_DIR = str(fixtures / "fights")
verify_oracle.GD_OUT = str(fixtures / "align/gdcore")
verify_oracle.LINEUP_OUT = str(fixtures / "align/lineups")
verify_oracle.PY_OUT = str(out / "py")
cases = json.loads((fixtures / "fixtures.json").read_text("utf8"))["cases"]
assert cases and verify_oracle.run_py(cases) == 0

modules = {}
for name, module in sys.modules.copy().items():
    if name.startswith("gd_core_py"):
        path = Path(str(getattr(module, "__file__", "")))
        if path.suffix == ".pyd" and path.is_relative_to(compiled):
            modules[path.relative_to(compiled).as_posix()] = hashlib.sha256(path.read_bytes()).hexdigest()
assert len(modules) == 9, modules

rows = []
for case in cases:
    path = Path(case["case_id"]) / "events.json"
    pure = json.loads((fixtures / "align/py" / path).read_text("utf8"))
    accelerated = json.loads((out / "py" / path).read_text("utf8"))
    fields = ("events", "event_count", "winner", "combat_time", "replay_initial")
    assert all(pure[field] == accelerated[field] for field in fields), case["case_id"]
    end = accelerated["events"][-1]
    assert end["type"] == {"player": 111, "opponent": 112}[accelerated["winner"]]
    rows.append({"case_id": case["case_id"], "event_count": accelerated["event_count"], "winner": accelerated["winner"]})

summary = {"cases": rows, "total": len(rows), "passed": len(rows),
           "fixtures_sha256": hashlib.sha256((fixtures / "fixtures.json").read_bytes()).hexdigest(),
           "compiled_modules_sha256": modules}
(out / "verification_summary.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf8")
print("Raw Python events and replay states matched", len(rows), "cases with", len(modules), "compiled modules")
