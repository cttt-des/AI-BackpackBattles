"""Run the critical-label timing contract in the stock Godot 3.6 runtime."""
from pathlib import Path
import sys


stage = Path(__file__).resolve().parent
repo = stage.parents[1]
sys.path.insert(0, str(repo))
from tools import godot_headless as gh

contract = (stage / "native_critical_shake_contract.gd").read_text("utf8")
schedule = (stage / "native_critical_shake.gd.inc").read_text("utf8")
assert schedule.count("\t\trandi()") == 1
schedule = schedule.replace("\t\trandi()", "\t\texpected += 1")
script = stage / "native_critical_shake_contract_generated.gd"
script.write_text(contract + "\n\n" + schedule, encoding="utf8", newline="\n")
command = gh.cmd("--fixed-fps", "60", "--disable-render-loop", project=str(stage / "sim_native/gd_core_test"),
                 script=str(script))
command[0] = str(repo / "output/godot36/Godot_v3.6-stable_win64.exe")
result, text, log = gh.run(command, label="native_critical_shake_contract", timeout=30, tag="native_critical_shake_contract")
print(log)
for line in text.splitlines():
    if "CRITICAL-SHAKE" in line or "SCRIPT ERROR" in line or "at: GDScript" in line:
        print(line)
raise SystemExit(result)
