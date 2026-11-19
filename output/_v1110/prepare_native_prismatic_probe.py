"""Observe Prismatic Sword's first hit rolls in a disposable original project."""
import hashlib
import json
from pathlib import Path
import sys

from stage_native_mega_clover_rng import replace_one


project = Path(sys.argv[1])
assert project.name.startswith("native_controlled_prismatic_")
relative = "Items/Exclusive/PrismaticSword.gd"
sword = project / relative
source = (project.parent / "decompiled" / relative).read_text("utf8")
source = replace_one(source, "\taffectedTypes = countTypes(getAffectedItems())\n", '''\tvar affected = getAffectedItems()
\taffectedTypes = countTypes(affected)
\tvar identifiers := []
\tfor item in affected:
\t\tvar sources := []
\t\tfor id in item.dynamicTypes.get(Type.Dark, []):
\t\t\tvar provider = instance_from_id(id)
\t\t\tif is_instance_valid(provider):
\t\t\t\tsources.append([provider.descriptor.identifier, str(provider.getTopLeftCell())])
\t\tidentifiers.append([item.descriptor.identifier, str(item.getTopLeftCell()),
\t\t\titem.hasType(Type.Dark), sources])
\tprint("[PRISM-PREPARE] ", JSON.print({"side": character().playerId,
\t\t"dark": affectedTypes[Type.Dark], "holy": affectedTypes[Type.Holy],
\t\t"magic": affectedTypes[Type.Magic], "vampiric": affectedTypes[Type.Vampiric],
\t\t"items": identifiers, "receiver": str(character().get_instance_id())}))
''')
source = replace_one(source, "\t\tif rollChance(getBaseChance2() * affectedTypes[Type.Dark]):\n", '''\t\tvar target = getBaseChance2() * affectedTypes[Type.Dark]
\t\tvar before = Util.rng.get_state()
\t\tvar expected = chanceRng.expectedWins
\t\tvar wins = chanceRng.wins
\t\tvar last = chanceRng.lastResult
\t\tvar success = rollChance(target)
\t\tif Game.combatTimer.combatTime < 2.0:
\t\t\tprint("[PRISM-ROLL] ", JSON.print({"side": character().playerId,
\t\t\t\t"combat_time": "%.17f" % Game.combatTimer.combatTime,
\t\t\t\t"target": target, "adjusted": applyBonusChance(target, 1),
\t\t\t\t"before": str(before), "after": str(Util.rng.get_state()),
\t\t\t\t"expected_wins": expected, "wins": wins, "last_result": last, "success": success}))
\t\tif success:
''')
sword.write_text(source, encoding="utf8", newline="\n")
manifest_path = project / "reference_manifest.json"
manifest = json.loads(manifest_path.read_bytes())
manifest["battle_script_sha256"][relative] = hashlib.sha256(sword.read_bytes()).hexdigest()
manifest["adaptations"].append("Read-only Prismatic Sword affected types and first-roll observer")
manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf8")
