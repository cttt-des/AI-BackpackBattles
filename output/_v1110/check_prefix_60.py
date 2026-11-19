import json
from pathlib import Path
import random
import subprocess
import sys

repo=Path.cwd();stage=repo/"output/_v1110";root=stage/"full_corpus/expand"
sys.path.insert(0,str(repo/"tools"))
import expand_run_oracle as runner
cases=json.loads((root/"cases.json").read_text("utf8"))["cases"]
complete=[c for c in cases if runner.case_done(str(root/"fights"),c["case_id"],True)]
selected=random.Random(1110).sample(complete,min(60,len(complete)))
out=stage/"prefix_60";out.mkdir(exist_ok=True)
(out/"cases.json").write_text(json.dumps({"cases":selected}),encoding="utf8")
common=["--fights-root",str(root/"fights"),"--align-root",str(out/"align"),
        "--cases-json",str(out/"fixtures.json")]
with (out/"verification.log").open("wb") as log:
    rc=subprocess.run([sys.executable,"-u","-X","utf8","tools/verify_oracle.py",*common,
                       "--cases",",".join(c["case_id"] for c in selected),
                       "--alignment-out",str(out/"alignment.json"),
                       "--history-db",str(repo/"output/oracle/expand/data/history.db"),
                       "--gd-jobs","1","--py-jobs","1","--compare-jobs","1"],
                      cwd=stage/"sim",stdout=log,stderr=subprocess.STDOUT).returncode
    print("Three-way",rc,flush=True)
    cpp=subprocess.run([sys.executable,"-u","-X","utf8","tools/_cpp_verify_events.py",*common,
                        "--case-ids",str(out/"cases.json"),"--strict-gem-origins","--out",str(out/"cpp")],
                       cwd=stage/"sim",stdout=log,stderr=subprocess.STDOUT)
    print("Four-way",cpp.returncode,flush=True)
raise SystemExit(cpp.returncode)
