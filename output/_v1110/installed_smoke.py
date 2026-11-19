import json
from pathlib import Path
import subprocess,sys

repo=Path.cwd();stage=repo/"output/_v1110";sim=stage/"sim"
root=stage/"full_corpus/expand";out=stage/"installed_smoke"
out.mkdir(exist_ok=True)
all_cases=json.loads((root/"cases.json").read_text("utf8"))["cases"]
selected=all_cases[::max(1,len(all_cases)//8)][:8]
ids=[c["case_id"] for c in selected]
(out/"cases.json").write_text(json.dumps({"cases":selected}),encoding="utf8")
common=["--fights-root",str(root/"fights"),"--align-root",str(out/"align"),
        "--cases-json",str(out/"fixtures.json")]
with (out/"verification.log").open("wb") as log:
    subprocess.run([sys.executable,"-u","-X","utf8","tools/verify_oracle.py",*common,
                    "--cases",",".join(ids),"--alignment-out",str(out/"alignment.json"),
                    "--history-db",str(repo/"output/oracle/expand/data/history.db"),
                    "--gd-jobs","1","--py-jobs","1","--compare-jobs","1"],
                   cwd=sim,stdout=log,stderr=subprocess.STDOUT,check=True)
    rc=subprocess.run([sys.executable,"-u","-X","utf8","tools/_cpp_verify_events.py",*common,
                       "--case-ids",str(out/"cases.json"),"--strict-gem-origins","--out",str(out/"cpp")],
                      cwd=sim,stdout=log,stderr=subprocess.STDOUT).returncode
print("Installed 1.1.10 smoke exit",rc,flush=True)
raise SystemExit(rc)
