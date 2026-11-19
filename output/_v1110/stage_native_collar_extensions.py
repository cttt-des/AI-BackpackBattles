"""Use the source TileMap's extended collar coverage when Acorn Ace is equipped."""
import json
from pathlib import Path
import re
import sys

from stage_native_mega_clover_rng import SIM, replace_one


COLLARS = ("Acorn Collar", "Magic Collar", "Holy Collar", "Vampiric Collar")
TILE_AFFECTED_EXTENSION = 8


def main():
    sys.path.insert(0, str(SIM))
    from simulator.extract_grid import decode_tile
    from tools.gen_lineup_fixture import placement_of

    changes = {}
    original = SIM.parent / "decompiled/Items"
    runtime = json.loads((SIM / "assets/gd_core_runtime.json").read_bytes())
    for name in COLLARS:
        scene, = original.rglob(name.replace(" ", "") + ".tscn")
        text = scene.read_text("utf8")
        map_data = re.search(r"(?ms)^\[node name=\"CollisionMap\"[^\n]*\]\n.*?^tile_data = PoolIntArray\(([^)]+)\)", text)
        assert map_data, scene
        words = [int(value) for value in re.findall(r"-?\d+", map_data[1])]
        assert len(words) % 3 == 0
        tiles = [(decode_tile(at), tile) for at, tile in zip(words[::3], words[1::3])]
        collision = [cell for cell, tile in tiles if tile == 3]
        normal = [cell for cell, tile in tiles if tile == 4]
        extended = [cell for cell, tile in tiles if tile in (4, TILE_AFFECTED_EXTENSION)]
        assert collision and normal and len(extended) > len(normal)
        for angle, shape in runtime["items"][name]["rot"].items():
            def projected(coverage):
                grid = {"collision_cells": collision, "affected_cells": coverage}
                return placement_of(name, {"grid": grid}, 0, 0, int(angle))["affected"][0]

            assert projected(normal) == shape["affected"]["0"], (name, angle)
            shape["affected"][str(TILE_AFFECTED_EXTENSION)] = projected(extended)

    payload = json.dumps(runtime, indent=2, ensure_ascii=False) + "\n"
    for root in (SIM, SIM / "native_sim_cpp"):
        changes[root / "assets/gd_core_runtime.json"] = payload

        script = root / "gd_core_items/RangerCollar.gd"
        source = script.read_text("utf8")
        anchor = "\taffectedItems = getAffectedItems()\n\tvar numAces = countAllInInventoryOfType(acornAceDescriptor)\n"
        changes[script] = replace_one(source, anchor, """\tvar numAces = countAllInInventoryOfType(acornAceDescriptor)
	# Group 8 contains the original TileMap after Acorn Ace enables its extra stars.
	if numAces > 0 and affectedTileCells.has(8):
		affectedTileCells[CoreConst.Affected.Primary] = affectedTileCells[8]
		cacheAffectedCells()
	affectedItems = getAffectedItems()
""")

    binding = SIM / "native_sim_cpp/native_sim/sim.py"
    source = binding.read_text("utf8")
    anchor = '            aff = it.get("affected") or {}\n'
    collar_names = "{" + ", ".join(repr(name) for name in COLLARS) + "}"
    guard = f'            if key in {collar_names} and occ and 8 not in aff and "8" not in aff:\n'
    changes[binding] = replace_one(source, anchor, anchor + guard + '''                geometry = self.data["items"].get(key, {}).get("rot", {}).get(str(pi.rotation), {})
                extended = geometry.get("affected", {}).get("8")
                if extended:
                    left = min(int(c[0]) for c in occ)
                    top = min(int(c[1]) for c in occ)
                    aff = {**aff, 8: [(x + left, y + top) for x, y in extended]}
''')

    for path, source in changes.items():
        path.write_text(source, encoding="utf8", newline="\n")


if __name__ == "__main__":
    main()
