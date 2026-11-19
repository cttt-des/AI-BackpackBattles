"""Measure exact per-frame CPU particle draws with the two replay engines."""
import hashlib
import json
from pathlib import Path
import shutil
import sys
import tempfile


stage = Path(__file__).resolve().parent
sys.path.insert(0, str(stage.parent.parent))
from tools import godot_headless

runs = {
    "physics": ("physics", -1),
    "idle_end": ("idle_end", -1),
    "same_physics_restart": ("physics", 0),
    "same_idle_restart": ("idle_end", 0),
    "mid_burst_restart": ("physics", 3),
    "idle_burst_physics_restart": ("idle_end", 1),
    "restart_before_hide": ("physics", 75),
    "restart_at_hide": ("physics", 76),
    "idle_restart_at_hide": ("idle_end", 76),
    "idle_restart_after_hide": ("idle_end", 77),
}
result = {}
for name, executable in {
    "shipping": stage / "source/BackpackBattles.exe",
    "vanilla": stage.parent / "godot36/Godot_v3.6-stable_win64.exe",
}.items():
    with tempfile.TemporaryDirectory(prefix="native_lovers_probe_", dir=stage,
                                     ignore_cleanup_errors=True) as temp:
        project = Path(temp)
        engine = project / "Godot_v3.6-stable_win64.exe"
        shutil.copyfile(executable, engine)
        if name == "shipping":
            for library in ("steam_api64.dll", "libgdsqlite.dll"):
                shutil.copyfile(executable.with_name(library), project / library)
        shutil.copyfile(stage / "native_lovers_particles_probe.gd", project / "probe.gd")
        (project / "project.godot").write_text('config_version=4\n\n[application]\nconfig/name="Native particle RNG probe"\n', "utf8")
        script = stage / "native_shipping_project/Utility/AutoHideCPUParticles.gd"
        shutil.copyfile(script, project / script.name)
        command = godot_headless.cmd("--fixed-fps", "60", "--disable-render-loop",
                                     project=str(project), script="res://probe.gd")
        command[0] = str(engine)
        rc, output, log = godot_headless.run(
            command, label="native_lovers_probe", tag=name, timeout=50, env_extra={
                "NATIVE_CPU_PARTICLE_SCRIPT": "res://" + script.name,
                "NATIVE_PARTICLE_CASES": json.dumps(runs),
            },
        )
        prefix = "[LOVERS-PARTICLES] "
        observations = [json.loads(line.split(prefix, 1)[1])
                        for line in output.splitlines() if prefix in line]
        capture = {row["profile"]: row["draws"] for row in observations}
        if rc not in (0, -9) or set(capture) != set(runs) or len(observations) != len(runs) or "SCRIPT ERROR" in output:
            raise RuntimeError(f"{name}: exit {rc}, incomplete probe ({log})\n{output}")
        for scenario, (_, restart) in runs.items():
            if len(capture[scenario]) != max(30, restart + 17):
                raise RuntimeError(f"{name} {scenario}: incomplete draw sequence ({log})")
        if rc:
            capture["shutdown_timed_out"] = True
        capture["restart_state"] = {row["profile"]: {"visible": row["visible"]} for row in observations
                                    if row["visible"] is not None}
        capture["engine_sha256"] = hashlib.sha256(executable.read_bytes()).hexdigest()
        result[name] = capture

path = stage / "native_lovers_particles_probe_result.json"
path.write_text(json.dumps(result, indent=2) + "\n", encoding="utf8")
for name, capture in result.items():
    print(name, capture["restart_state"])
