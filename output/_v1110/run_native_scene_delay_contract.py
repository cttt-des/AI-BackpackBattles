"""Exercise the delayed callback model against stock Godot 3.6."""
from pathlib import Path
import sys


stage = Path(__file__).resolve().parent
repo = stage.parents[1]
sys.path.insert(0, str(repo))
from tools import godot_headless as gh


command = gh.cmd("--fixed-fps", "60", "--disable-render-loop",
                 project=str(stage / "sim_native/gd_core_test"),
                 script=str(stage / "native_scene_delay_contract.gd"))
command[0] = str(repo / "output/godot36/Godot_v3.6-stable_win64.exe")
result, output, log = gh.run(command, label="native_scene_delay", timeout=30,
                             tag="native_scene_delay", env_extra={
                                 "NATIVE_SCENE_DELAY_MODEL": str(stage / "native_scene_delay.gd.inc")})
print(log)
print(output)
raise SystemExit(result or ("SceneTreeTimer contract:" not in output or "SCRIPT ERROR" in output))
