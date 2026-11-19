import subprocess
import sys
from pathlib import Path

runner = Path(__file__).with_name("record_1110.py")
stage = Path(sys.argv[1] if len(sys.argv) > 1 else "output/_v1110").resolve()
if not (stage / "source_manifest.json").is_file():
    raise SystemExit(f"Missing release manifest in {stage}")
statuses = {}
for cohort in ("expand", "base"):
    log_path = stage / f"record_{cohort}.log"
    with log_path.open("ab") as log:
        print(f"Recording {cohort}: {log_path}", flush=True)
        result = subprocess.run([sys.executable, "-u", "-X", "utf8", str(runner),
                                 cohort, "--stage", str(stage), "--jobs", "3", "--chunk", "36"],
                                stdout=log, stderr=subprocess.STDOUT)
    statuses[cohort] = result.returncode
    print(f"{cohort} exit={result.returncode}", flush=True)
raise SystemExit(max(statuses.values()))
