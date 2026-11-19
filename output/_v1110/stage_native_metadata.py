"""Synchronize the original game's descriptor metadata into the isolated kernels."""
from pathlib import Path
import copy
import hashlib
import json
import sys

repo = Path(__file__).resolve().parents[2]
stage = repo / "output/_v1110"
sim = stage / "sim_native"
observed_path = stage / "native_descriptor_audit/descriptor_metadata.json"
observed = json.loads(observed_path.read_text("utf8"))
assert observed["version"] == "1.1.10" and observed["locale"] == "en"
assert observed["count"] == len(observed["items"]) == 519
assert all(isinstance(row["translated_name"], str) and row["has_battle_rage_effect"] == row["description_mentions_rage"]
           for row in observed["items"].values())
old_runtime = json.loads((sim / "assets/gd_core_runtime.json").read_text("utf8"))
database = json.loads((stage / "sim/assets/battle_items.json").read_text("utf8"))
assert database["items"].keys() == observed["items"].keys()
for key, entry in database["items"].items():
    entry["display_name_en"] = observed["items"][key]["translated_name"]
    entry["has_battle_rage_effect"] = observed["items"][key]["has_battle_rage_effect"]
(sim / "assets/battle_items.json").write_text(json.dumps(database, ensure_ascii=False, separators=(",", ":")), encoding="utf8")

generator = (stage / "sim/tools/gen_lineup_fixture.py").read_text("utf8")
assert generator.count('        "name": key,\n') == 1
generator = generator.replace('        "name": key,\n', '        "name": entry.get("display_name_en", key),\n')
(sim / "tools/gen_lineup_fixture.py").write_text(generator, encoding="utf8", newline="\n")
sys.path[:0] = [str(sim)]
from tools import gen_gd_core_data as runtime

runtime.GF.EXTRACTED_ITEMS = str(stage / "decompiled/Items")
runtime.GF.SOCKETS = runtime.GF.scan_socket_counts()
data = runtime.build()
table = runtime.GF.build_item_table()
assert data["items"].keys() == old_runtime["items"].keys() == table["items"].keys()
changes = []
for key, row in data["items"].items():
    before = copy.deepcopy(old_runtime["items"][key])
    after = copy.deepcopy(row)
    for field in ("name", "hasBattleRageEffect"):
        previous = before["descr"].pop(field)
        current = after["descr"].pop(field)
        if previous != current:
            changes.append({"item": key, "field": field, "before": previous, "after": current})
    assert before == after, (key, "Unexpected gameplay data change")
    assert row["descr"] == table["items"][key]["descr"], key
payload = json.dumps(data, ensure_ascii=False, separators=(",", ":"))
for root in (sim, sim / "native_sim_cpp"):
    (root / "assets/gd_core_runtime.json").write_text(payload, encoding="utf8")
(sim / "gd_core_test/item_battle_fixture.json").write_text(
    json.dumps(table, ensure_ascii=False, sort_keys=True, separators=(",", ":")) + "\n", encoding="utf8")
(stage / "native_metadata_sync.json").write_text(json.dumps({
    "version": observed["version"], "locale": observed["locale"], "items": len(data["items"]),
    "original_metadata_sha256": hashlib.sha256(observed_path.read_bytes()).hexdigest(),
    "changes": changes,
    "battle_rage_items": [key for key, row in data["items"].items() if row["descr"]["hasBattleRageEffect"]],
    "scope": "Original descriptor fields; numeric stats, grids and socket data unchanged"
}, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
print("Native descriptor metadata synchronized:", len(changes), "changed fields")
