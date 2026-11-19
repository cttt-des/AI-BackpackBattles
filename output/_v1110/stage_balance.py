import json
from pathlib import Path
import sys

repo = Path.cwd()
sys.path.insert(0, str(repo))
from tools import enrich_oracle_params as enrich
from tools import gen_gd_core_data as runtime

stage = repo / "output/_v1110"
out = stage / "assets"
out.mkdir(exist_ok=True)
old_rows = enrich.load_csv(repo / "oracle/Sheets/CSV/ItemData.csv")
new_rows = enrich.load_csv(stage / "ItemData_1.1.10.csv")
db = json.loads((repo / "assets/battle_items.json").read_text("utf8"))
balance = json.loads((stage / "item_balance_diff.json").read_text("utf8"))
changes = balance["changes"]
columns = set(enrich.P_COLS) | set(enrich.INT_COLS) | set(enrich.FLOAT_COLS) | set(enrich.CHANCE_COLS) | {"cd","accuracy","weight"}
if set(balance["changed_columns"]) - columns:
    raise ValueError("Unhandled CSV columns")
log = []
errors = []
for item, cells in changes.items():
    try:
        entry = db["items"][item]
        enrich.sync_item(item, entry, old_rows[item], new_rows[item], log)
        if "accuracy" in cells:
            old, new = (float(r[item]["accuracy"] or 100) for r in (old_rows, new_rows))
            if float(entry["accuracy"]) not in (old,new):
                raise ValueError(f"Unexpected stored accuracy: {entry['accuracy']}")
            entry["accuracy"] = new
            log.append(f"{item}.accuracy: {old} -> {new}")
        if "weight" in cells:
            # The weight feeds the game's shop table. It is not in the simulator
            # battle descriptor, so the full official sheet preserves the change.
            log.append(f"{item}.weight: preserved in official item sheet")
    except (SystemExit, KeyError, ValueError) as err:
        errors.append(str(err))
(stage/"item_data_stage_log.json").write_text(json.dumps(dict(log=log,errors=errors),indent=2,ensure_ascii=False),encoding="utf8")
if errors:
    for err in errors:
        print(err)
    raise SystemExit(1)

items_file = out / "battle_items.json"
items_file.write_text(json.dumps(db,ensure_ascii=False,separators=(",",":")),encoding="utf8")
runtime.DB_PATH = str(items_file)
runtime.GF.EXTRACTED_ITEMS = str(stage / "decompiled/Items")
runtime.GF.SOCKETS = runtime.GF.scan_socket_counts()
result = runtime.build()
path = out / "gd_core_runtime.json"
path.write_text(json.dumps(result,ensure_ascii=False,separators=(",",":")),encoding="utf8")
print(f"Updated balance from {len(changes)} items, {len(log)} reported changes")
print(f"Runtime item descriptors: {len(result['items'])}")
