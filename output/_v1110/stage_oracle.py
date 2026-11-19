import json
import re
from pathlib import Path
import shutil
import subprocess
from tempfile import TemporaryDirectory

repo = Path.cwd()
stage = repo / "output/_v1110"
base = repo / "output/_re_extract/gdre119"
recording = repo / "oracle"
clean = stage / "decompiled"
target = stage / "oracle_project"
source_diff = json.loads((stage / "game_source_diff.json").read_text("utf8"))

merge_dir = stage / "oracle_overlays"
conflicts = []
for rel in source_diff["harness_changed"]:
    orig, harness, newer = (p / rel for p in (base, recording, clean))
    result = harness.read_bytes()
    if rel == "Utility/DataValidator.gd":
        # Its original hash matches the new encrypted CSV in the copied release.
        result = newer.read_bytes()
    elif rel == "Items/Item.gd":
        nonblank = lambda p: [ln for ln in p.read_text("utf8").splitlines() if ln.strip()]
        if nonblank(orig) != nonblank(newer):
            raise ValueError("Unexpected gameplay edits in Item.gd")
        # The new game only changes empty lines in this file.
    elif rel in source_diff["version_changed"] or rel == "project.godot":
        with TemporaryDirectory(dir=stage) as temp:
            inputs = []
            for name, path in (("harness", harness), ("ancestor", orig), ("new", newer)):
                normalized = Path(temp) / name
                normalized.write_text(path.read_text("utf8"), encoding="utf8", newline="\n")
                inputs.append(str(normalized))
            merge = subprocess.run(["git", "merge-file", "--stdout", "--diff3",
                                    "-L", "recorder-119", "-L", "game-119", "-L", "game-1110",
                                    *inputs], capture_output=True)
        if merge.returncode:
            conflicts.append(rel)
        result = merge.stdout
    dst = merge_dir / rel
    dst.parent.mkdir(parents=True, exist_ok=True)
    dst.write_bytes(result)
if conflicts:
    print("Resolve 3-way merge:", conflicts, flush=True)
    raise SystemExit(2)

shutil.copytree(clean, target, dirs_exist_ok=True)
for rel in (*source_diff["harness_changed"], *source_diff["harness_added"]):
    src = (merge_dir if rel in source_diff["harness_changed"] else recording) / rel
    dst = target / rel
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(src, dst)
for path in ("fight_config.json","fights.json","data/history.db"):
    dst = target / path
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(recording / path, dst)
for src in (recording / "addons/godot-sqlite").rglob("*.dll"):
    dst = target / src.relative_to(recording)
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(src, dst)
shutil.copyfile(stage / "ItemData_1.1.10.csv", target / "Sheets/CSV/ItemData.csv")

# The unguarded stamina prints were temporary comparison probes. Removing the
# prints preserves calculations and keeps the large replay bounded.
ch = target / "Core/Character.gd"
text = ch.read_text("utf8")
probe_prefixes = ('print("[ADD-O]', 'print("[USE-O]', 'print("[RECALC-O]')
original = text.splitlines(keepends=True)
filtered = [ln for ln in original if not ln.strip().startswith(probe_prefixes)]
ch.write_text("".join(filtered), encoding="utf8")
print("Removed stamina trace prints", len(original)-len(filtered), flush=True)
game_path = target / "Core/Game.gd"
game = game_path.read_text("utf8")
for name in ("requestOpponentPoolAccessCheck", "_startModUpdateChecks"):
    start = re.search(rf"(?m)^func {name}\([^\n]*\n", game)
    following = re.search(r"(?m)^func ", game[start.end():])
    end = start.end() + following.start() if following else len(game)
    game = game[:start.end()] + "\t# Plugin services are omitted in offline replay.\n\treturn\n\n" + game[end:]
game_path.write_text(game, encoding="utf8")
print("Staged Oracle project", target, flush=True)

