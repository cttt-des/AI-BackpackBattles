"""Use the original ItemBook's resolved class masks in the 1.1.10 kernels."""
from pathlib import Path
import hashlib
import json


STAGE = Path(__file__).resolve().parent
SIM = STAGE / "sim_native"
METADATA = STAGE / "native_classes_audit/descriptor_metadata.json"
CLASSES = STAGE / "native_descriptor_classes.json"


def read(path):
    return json.loads(path.read_bytes())


def write(path, doc, *, indent=None):
    payload = json.dumps(doc, ensure_ascii=False, indent=indent, separators=None if indent else (",", ":"))
    path.write_text(payload + "\n", encoding="utf8", newline="\n")


def class_snapshot():
    if not METADATA.is_file():
        snapshot = read(CLASSES)
    else:
        metadata = read(METADATA)
        assert metadata["count"] == len(metadata["items"]) == 519
        snapshot = {
            "version": metadata["version"],
            "locale": metadata["locale"],
            "metadata_sha256": hashlib.sha256(METADATA.read_bytes()).hexdigest(),
            "items": {key: row["classes"] for key, row in sorted(metadata["items"].items())},
        }
    assert snapshot["version"] == "1.1.10" and snapshot["locale"] == "en"
    assert len(snapshot["items"]) == 519
    assert all(type(mask) is int and -1 <= mask <= 127 for mask in snapshot["items"].values())
    if CLASSES.exists():
        assert read(CLASSES)["items"] == snapshot["items"], "Native masks changed"
    else:
        write(CLASSES, snapshot, indent=2)
    return snapshot["items"]


def main():
    masks = class_snapshot()
    runtime = SIM / "assets/gd_core_runtime.json"
    cpp_runtime = SIM / "native_sim_cpp/assets/gd_core_runtime.json"
    gd_runtime = SIM / "gd_core_test/item_battle_fixture.json"
    battle_items = SIM / "assets/battle_items.json"
    assert runtime.read_bytes() == cpp_runtime.read_bytes()
    data, gd_data, items = (read(path) for path in (runtime, gd_runtime, battle_items))
    assert masks.keys() == data["items"].keys() == gd_data["items"].keys() == items["items"].keys()
    changes = []
    for key, value in masks.items():
        descriptor = data["items"][key]["descr"]
        gd_descriptor = gd_data["items"][key]["descr"]
        old = descriptor["classes"]
        assert gd_descriptor["classes"] == old == (items["items"][key].get("classes") or 0), key
        if old != value:
            changes.append({"item": key, "before": old, "after": value})
            descriptor["classes"] = gd_descriptor["classes"] = value
            items["items"][key]["classes"] = value
    write(runtime, data)
    write(cpp_runtime, data)
    write(gd_runtime, gd_data)
    write(battle_items, items)
    print(json.dumps(changes, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
