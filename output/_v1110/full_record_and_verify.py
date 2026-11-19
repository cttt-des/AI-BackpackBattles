import json
from pathlib import Path
import subprocess
import sys

repo=Path.cwd()
stage=repo/"output/_v1110"
sim=stage/"sim"
report={}
for cohort in ("expand","base"):
    root=stage/"full_corpus"/cohort
    with (stage/f"full_{cohort}.log").open("ab") as log:
        print(f"Starting {cohort} recording",flush=True)
        recorded=subprocess.run([sys.executable,"-u","-X","utf8",str(stage/"record_1110.py"),
                                 cohort,"--stage",str(stage),"--jobs","3","--chunk","36"],
                                cwd=repo,stdout=log,stderr=subprocess.STDOUT)
    report[cohort]={"recording_exit":recorded.returncode}
    (stage/"full_status.json").write_text(json.dumps(report,indent=2),encoding="utf8")
    if recorded.returncode:
        print(f"Recording needs diagnosis: {cohort} rc={recorded.returncode}",flush=True)
        continue
    expected=json.loads((root/"cases.json").read_text("utf8"))["cases"]
    assert len(expected)==(1690 if cohort=="expand" else 914)
    history=repo/("output/oracle/expand/data/history.db" if cohort=="expand" else "oracle/data/history.db")
    common=["--fights-root",str(root/"fights"),"--align-root",str(root/"align"),
            "--cases-json",str(root/"fixtures.json")]
    with (stage/f"verify_{cohort}.log").open("wb") as log:
        verify=subprocess.run([sys.executable,"-u","-X","utf8","tools/verify_oracle.py",*common,
                               "--alignment-out",str(root/"alignment.json"),"--history-db",str(history),
                               "--gd-jobs","2","--py-jobs","2","--compare-jobs","2"],
                              cwd=sim,stdout=log,stderr=subprocess.STDOUT)
        report[cohort]["three_way_exit"]=verify.returncode
        compare=subprocess.run([sys.executable,"-u","-X","utf8","tools/_cpp_verify_events.py",*common,
                                "--case-ids",str(root/"cases.json"),"--strict-gem-origins",
                                "--out",str(root/"cpp")],cwd=sim,stdout=log,stderr=subprocess.STDOUT)
        report[cohort]["four_way_exit"]=compare.returncode
    (stage/"full_status.json").write_text(json.dumps(report,indent=2),encoding="utf8")
    print(cohort,report[cohort],flush=True)
print("Both recording cohorts processed",flush=True)
