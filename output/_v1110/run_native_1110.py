import argparse
import json
import shutil
from pathlib import Path
import subprocess
import sys

repo=Path.cwd()
sys.path.insert(0,str(repo))
from tools import godot_headless as gh

ap=argparse.ArgumentParser()
ap.add_argument("case_id")
ap.add_argument("--out",default="native_settled")
ap.add_argument("--timeout",type=int,default=240)
ap.add_argument("--disable-render-loop", action="store_true")
args=ap.parse_args()
stage=repo/"output/_v1110"
subprocess.run([sys.executable,"-u","-X","utf8",str(stage/"prepare_native_reference.py"),str(stage)],check=True)
command=gh.cmd("--fixed-fps","60",project=str(stage/"native_reference"))
if args.disable_render_loop:
    command.append("--disable-render-loop")
command[0]=str(stage/"native_reference/runtime/Godot_v3.6-stable_win64.exe")
p,log,h=gh.spawn(command,label="native_settled",tag="native_settled",
                 env_extra={"NATIVE_BATTLE_CASE":args.case_id,"NATIVE_BATTLE_OUT":str(stage/args.out)})
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
    errors=[s for s in lines if "SCRIPT ERROR" in s]
    target=stage/args.out/args.case_id
    if errors:
        print("Reference recording rejected because of script errors:", "\n".join(errors), flush=True)
        rc=1
    elif not all((target/name).is_file() for name in ("events.json", "lineups.json", "boundaries.json")):
        print("Reference recording rejected: missing output", flush=True)
        rc=1
    else:
        events=json.loads((target/"events.json").read_text("utf8"))
        if events.get("event_count") != len(events.get("events",[])) or not events["events"] or events["events"][-1]["type"] not in (111,112):
            print("Reference recording rejected: missing natural terminal", flush=True)
            rc=1
        else:
            shutil.copyfile(stage/"native_reference/reference_manifest.json",target/"reference_manifest.json")
raise SystemExit(rc)
