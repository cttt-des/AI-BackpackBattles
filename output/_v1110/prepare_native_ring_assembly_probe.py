"""Record pre-placement ring rolls in a separate recovered game project."""
import hashlib
import json
from pathlib import Path
import sys

from stage_native_mega_clover_rng import replace_one


def main():
    project = Path(sys.argv[1])
    if not project.name.startswith(("native_controlled_prismatic_", "native_ring_assembly_")):
        raise ValueError("Choose an isolated game project")
    relative = "Items/Exclusive/MagicRing.gd"
    ring = project / relative
    source = (project.parent / "decompiled" / relative).read_text("utf8")
    anchor = "\t\t\trandEffects()\n"
    ring.write_text(replace_one(source, anchor, anchor + '''\t\t\tif ownerType == Owner.PlayerInventory or ownerType == Owner.Opponent:
\t\t\t\tvar rolled := []
\t\t\t\tfor effect in effects:
\t\t\t\t\trolled.append({"triggerType": effect.triggerType, "stackType": effect.stackType})
\t\t\t\tset_meta("native_placement_effects", rolled)
'''), encoding="utf8", newline="\n")
    reader = project / "native_battle_reader.gd"
    source = reader.read_text("utf8")
    anchor = '\t\t"effects": effects,\n'
    reader.write_text(replace_one(source, anchor, anchor + '''\t\t"placement_effects": item.get_meta("native_placement_effects") if item.has_meta("native_placement_effects") else null,
'''), encoding="utf8", newline="\n")
    manifest_path = project / "reference_manifest.json"
    manifest = json.loads(manifest_path.read_bytes())
    manifest["battle_script_sha256"][relative] = hashlib.sha256(ring.read_bytes()).hexdigest()
    manifest["reader_sha256"] = hashlib.sha256(reader.read_bytes()).hexdigest()
    manifest["adaptations"].append("Read-only initial ring rolls recorded before saved effects are loaded")
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf8")


if __name__ == "__main__":
    main()
