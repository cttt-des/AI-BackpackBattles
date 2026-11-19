import argparse
import hashlib
import json
import shutil
from pathlib import Path
import subprocess
import sys

repo=Path.cwd()
sys.path.insert(0,str(repo))
from tools import godot_headless as gh

ap=argparse.ArgumentParser()
ap.add_argument("case_id", nargs="?", help="One case ID or a comma-separated list")
ap.add_argument("--case-ids", type=Path, help="JSON list or a cases table; preserve listed order")
ap.add_argument("--out",default="native_settled")
ap.add_argument("--timeout",type=int,default=240)
ap.add_argument("--disable-render-loop", action="store_true")
ap.add_argument("--rng-probe", action="store_true")
ap.add_argument("--engine-seed", type=int, help="Set controlled Godot global RNG inputs for experiments; use a separate output and project")
ap.add_argument("--cohort", choices=("expand", "base"), default="expand")
ap.add_argument("--project-name", default="native_reference")
ap.add_argument("--reuse-prepared", action="store_true", help="Use a frozen previously prepared project")
ap.add_argument("--shipping-engine", action="store_true", help="Use the copied shipping EXE with this recovered project")
args=ap.parse_args()
if args.engine_seed is not None:
    if not 0 <= args.engine_seed < 2**63 - 1:
        ap.error("Engine seed is outside the supported signed 64-bit range")
    if not args.out.startswith("native_controlled_") or not args.project_name.startswith("native_controlled_"):
        ap.error("Controlled inputs require separate native_controlled_ project and output names")
if bool(args.case_id) == bool(args.case_ids):
    ap.error("Supply either case_id or --case-ids")
if args.case_ids:
    selected=json.loads(args.case_ids.read_text("utf8"))
    selected=selected["cases"] if isinstance(selected,dict) else selected
    case_ids=[case if isinstance(case,str) else case["case_id"] for case in selected]
else:
    case_ids=[case.strip() for case in args.case_id.split(",") if case.strip()]
if not case_ids or len(case_ids) != len(set(case_ids)):
    ap.error("Case IDs must be nonempty and unique within a batch")
stage=repo/"output/_v1110"
project = (stage/args.project_name).resolve()
if project.parent != stage.resolve():
    ap.error("The isolated project must be a direct child of the stage directory")
if not args.reuse_prepared:
    subprocess.run([sys.executable,"-u","-X","utf8",str(stage/"prepare_native_reference.py"),str(stage),
                    "--cohort",args.cohort,"--project-name",args.project_name,
                    *(["--rng-probe"] if args.rng_probe else []),
                    *(["--shipping-engine"] if args.shipping_engine else [])],check=True)
manifest = json.loads((project / "reference_manifest.json").read_text("utf8"))
if (manifest.get("cohort") != args.cohort or manifest.get("version") != "1.1.10"
        or bool(manifest.get("shipping_engine")) != args.shipping_engine):
    ap.error("Prepared project version, cohort or executable differs from this recording")
executable = project / "runtime/Godot_v3.6-stable_win64.exe"
if "engine_sha256" in manifest and hashlib.sha256(executable.read_bytes()).hexdigest() != manifest["engine_sha256"]:
    raise SystemExit("The executable differs from the reference manifest")
command=gh.cmd("--fixed-fps","60",project=str(project))
if args.disable_render_loop:
    command.append("--disable-render-loop")
if args.rng_probe:
    command.append("--debug")  # Godot exposes get_stack() only with a debugger.
command[0]=str(executable)
p,log,h=gh.spawn(command,label="native_settled",tag="native_settled",
                 env_extra={"NATIVE_BATTLE_CASE":",".join(case_ids),"NATIVE_BATTLE_OUT":str(stage/args.out),
                            "NATIVE_BATTLE_ENGINE_SEED": "" if args.engine_seed is None else str(args.engine_seed)})
print("pid",p.pid,"log",log,flush=True)
try:
    rc=p.wait(timeout=args.timeout)
except subprocess.TimeoutExpired:
    p.kill()
    rc=p.wait()
finally:
    h.close()
lines=gh.read_log(log).splitlines()
selected=[s for s in lines if any(x in s for x in ("SCRIPT ERROR","[NATIVE]","VERSION","Round "))]
print("\n".join(selected[:12]+selected[-8:]),flush=True)
print("return",rc,flush=True)
if not rc:
    errors=[s for s in lines if "SCRIPT ERROR" in s or "Debugger Break" in s]
    if errors:
        print("Reference recording rejected because of script errors:", "\n".join(errors), flush=True)
        rc=1
    elif not all(any(f"[NATIVE] Recorded {cid} " in s for s in lines) for cid in case_ids):
        print("Reference recording rejected: missing a current-run completion marker", flush=True)
        rc=1
    else:
        for cid in case_ids:
            target=stage/args.out/cid
            if not all((target/name).is_file() for name in ("events.json", "lineups.json", "boundaries.json")):
                print("Reference recording rejected: missing output for",cid,flush=True)
                rc=1
                break
            events=json.loads((target/"events.json").read_text("utf8"))
            if events.get("event_count") != len(events.get("events",[])) or not events["events"] or events["events"][-1]["type"] not in (111,112):
                print("Reference recording rejected: missing natural terminal for",cid,flush=True)
                rc=1
                break
            if args.engine_seed is None:
                shutil.copyfile(project/"reference_manifest.json",target/"reference_manifest.json")
            else:
                boundaries = json.loads((target / "boundaries.json").read_text("utf8"))
                observed = [boundaries[key].get("engine_seed") for key in ("prepare", "before_activate")]
                if observed != [str(args.engine_seed), str(args.engine_seed + 1)]:
                    print("Reference recording rejected: engine RNG experiment inputs differ for", cid, flush=True)
                    rc = 1
                    break
                experiment = json.loads((project / "reference_manifest.json").read_text("utf8"))
                experiment["controlled_engine_seeds"] = observed
                experiment["scope"] = "Recovered-source reference with controlled global RNG at preparation and activation"
                (target / "reference_manifest.json").write_text(json.dumps(experiment, indent=2) + "\n", encoding="utf8")
raise SystemExit(rc)
