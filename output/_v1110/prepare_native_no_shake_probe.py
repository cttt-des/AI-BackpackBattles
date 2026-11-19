"""Remove only critical-number BBCode shake in a controlled reference copy."""
from pathlib import Path
import argparse
import hashlib
import json
import shutil


stage = Path(__file__).resolve().parent
source = stage / "native_controlled_global_trace_project"
target = stage / "native_controlled_global_no_shake_project"
parser = argparse.ArgumentParser()
parser.add_argument("--remove-item-shake", action="store_true", help="Extend the completed character-only experiment")
args = parser.parse_args()
if not args.remove_item_shake:
    assert source.is_dir() and not target.exists()
    shutil.copytree(source, target)
manifest_path = target / "reference_manifest.json"
manifest = json.loads(manifest_path.read_text("utf8"))

if args.remove_item_shake:
    assert (stage / "native_controlled_global_no_shake/run100900_r15_o100932_r15/reference_manifest.json").is_file()
    script = target / "Interface/DamageNumbers/BuffLabel.gd"
    before = '[center][shake rate=20 level=30]'
    after = '[center]'
    key = "global_rng_trace_buff_label_sha256"
    note = "Critical item damage number BBCode shake omitted for source RNG diagnosis"
else:
    script = target / "Core/Game.gd"
    before = '[center][shake rate=20 level=50]{amount}[/shake]'
    after = '[center]{amount}'
    key = "global_rng_trace_game_sha256"
    note = "Critical character damage number BBCode shake omitted for source RNG diagnosis"
text = script.read_text("utf8")
assert text.count(before) == 1
script.write_text(text.replace(before, after), encoding="utf8", newline="\n")
manifest[key] = hashlib.sha256(script.read_bytes()).hexdigest()
manifest["adaptations"].append(note)
manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf8")
