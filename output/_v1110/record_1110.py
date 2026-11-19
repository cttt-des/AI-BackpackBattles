import argparse
import json
from pathlib import Path
import shutil
import sys

repo = Path.cwd()
sys.path.insert(0, str(repo/"tools"))
import expand_run_oracle as runner

ap = argparse.ArgumentParser()
ap.add_argument("cohort", choices=("base", "expand"))
ap.add_argument("--stage", type=Path, default=repo / "output/_v1110")
ap.add_argument("--smoke", type=int, default=0)
ap.add_argument("--jobs", type=int, default=3)
ap.add_argument("--chunk", type=int, default=32)
args = ap.parse_args()
stage = args.stage.resolve()
manifest_path = stage / "source_manifest.json"
if not manifest_path.is_file():
    raise SystemExit(f"Missing source manifest: {manifest_path}")
manifest = json.loads(manifest_path.read_text("utf8"))
if manifest.get("version") != "1.1.10":
    raise SystemExit("Expected the installed 1.1.10 source")

out = stage/"full_corpus"/args.cohort
out.mkdir(parents=True, exist_ok=True)
if args.cohort == "expand":
    case_list = repo/"output/oracle/expand/cases.json"
    db = repo/"output/oracle/expand/data/history.db"
else:
    case_list = repo/"oracle/fights.json"
    db = repo/"oracle/data/history.db"
    
project = out/"project"
if not project.exists():
    shutil.copytree(stage / "oracle_project", project)
case_file = out/"cases.json"
shutil.copyfile(case_list, case_file)
runner.PROJ_DST = str(project)
sys.argv = ["expand_run_oracle.py","--cases",str(case_file),"--db",str(db),
            "--root",str(out/"fights"),"--jobs",str(args.jobs),"--chunk",str(args.chunk),
            "--smoke",str(args.smoke),"--max-rounds","50","--require-terminal"]
raise SystemExit(runner.main())

