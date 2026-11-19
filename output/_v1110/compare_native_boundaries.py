"""Diagnostic: compare real frame replay using its observed battle inputs.

This imports two observed PCG states and the actual activation permutation.
It does not claim that a seed alone reproduces UI and animation RNG draws.
The underlying native recording is read-only; all candidate output is isolated.
"""
import argparse
import json
from pathlib import Path
import sys
import subprocess

repo = Path.cwd()
sys.path.insert(0, str(repo))
sys.path.insert(0, str(repo / "tools"))
from tools import godot_headless as gh
from verify_oracle import canonical_stream, _tuple_of, _et_names

parser = argparse.ArgumentParser()
parser.add_argument("case_id")
parser.add_argument("--reference", default="native_observed_clean")
parser.add_argument("--physics-first", action="store_true")
args = parser.parse_args()
stage = repo / "output/_v1110"
reference = stage / args.reference / args.case_id
data = json.loads((reference / "boundaries.json").read_text("utf8"))
out = stage / "native_boundary_comparison" / args.reference / ("physics_first" if args.physics_first else "current")
out.mkdir(parents=True, exist_ok=True)
source = (repo / "oracle/oracle_fight.gd").read_text("utf8")
if args.physics_first:
    assert source.count("\tdrive_timers(true, dt)\n") == 1
    source = source.replace("\tdrive_timers(true, dt)\n", "")
    source = source.replace("func tick_battle(dt: float, n := 0) -> void :\n",
                            "func tick_battle(dt: float, n := 0) -> void :\n\tdrive_timers(true, dt)\n")
    assert source.count("\t\t\te[0] = eng            #") == 1
    source = source.replace("\t\t\te[0] = eng            #", "\t\t\te[0] = eng - dt if physics_pass else eng  #")
assert source.count("\tG.prepareItems(playerItems + opponentItems)\n") == 1
before_prepare = '''
	if not warmup:
		var native_order = %s
		var ordered_player := []
		var ordered_opponent := []
		var available = playerItems + opponentItems
		for descriptor in native_order:
			var found = null
			for item in available:
				var cell = item.getTopLeftCell()
				if item.getName() == descriptor["name"] and item.ownerType == int(descriptor["owner"]) and cell == Vector2(descriptor["top_left"][0], descriptor["top_left"][1]):
					found = item
					break
			assert(found != null)
			available.erase(found)
			if found.ownerType == 1:
				ordered_player.append(found)
			else:
				ordered_opponent.append(found)
		assert(available.empty())
		playerItems = ordered_player
		opponentItems = ordered_opponent
		U.rng.set_state(%s)
''' % (json.dumps(data["prepare"]["order"], ensure_ascii=False), data["prepare"]["state"])
source = source.replace("\tG.prepareItems(playerItems + opponentItems)\n",
                        before_prepare + "\tG.prepareItems(playerItems + opponentItems)\n")
source = source.replace("\tG.activateItems(playerItems + opponentItems)\n",
                        "\tif not warmup:\n\t\tU.rng.set_state(%s)\n" % data["before_activate"]["state"]
                        + "\tG.activateItems(playerItems + opponentItems)\n")
script = out / "oracle_fight.gd"
script.write_text(source, encoding="utf8")
p, log, handle = gh.spawn(gh.cmd(project=str(stage / "full_corpus/expand/project"), script=str(script)),
                         label="native_boundary_compare", tag="native_boundary_compare",
                         env_extra={"ORACLE_ONLY_CASES": args.case_id,
                                    "ORACLE_FIGHTS_ROOT": str(out / "fights"),
                                    "ORACLE_REQUIRE_TERMINAL": "1", "ORACLE_FIGHT_CHUNK": "1"})
print("pid", p.pid, "log", log, flush=True)
try:
    rc = p.wait(timeout=240)
except subprocess.TimeoutExpired:
    p.kill()
    p.wait()
    raise
finally:
    handle.close()
if rc:
    raise SystemExit(rc)
streams = [canonical_stream(str(path), _et_names()) for path in (
    reference / "events.json", out / "fights" / args.case_id / "events.json")]
first = next((i for i, (a, b) in enumerate(zip(*streams)) if _tuple_of(a) != _tuple_of(b)), None)
result = {"case_id": args.case_id, "counts": list(map(len, streams)), "first": first,
          "match": first is None and len(streams[0]) == len(streams[1]),
          "native": streams[0][first] if first is not None else None,
          "oracle": streams[1][first] if first is not None else None,
          "scope": "Imported native preparation and activation states and permutation"}
(out / "comparison.json").write_text(json.dumps(result, indent=2, ensure_ascii=False), encoding="utf8")
print(json.dumps(result, indent=2, ensure_ascii=False))
raise SystemExit(0 if result["match"] else 1)
