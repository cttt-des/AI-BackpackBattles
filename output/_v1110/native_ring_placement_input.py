"""Validate placement observations against an immutable original fight."""
import hashlib
import json


def read_placement_input(original, observed):
    original_events = (original / "events.json").read_bytes()
    if (observed / "events.json").read_bytes() != original_events:
        raise ValueError(f"Ring observer did not reproduce the frozen event file for {original.name}")

    original_manifest = json.loads((original / "reference_manifest.json").read_bytes())
    observed_manifest = json.loads((observed / "reference_manifest.json").read_bytes())
    for key in ("version", "cohort", "shipping_engine", "engine_sha256", "case_list_sha256",
                "history_snapshot_sha256"):
        if original_manifest[key] != observed_manifest[key]:
            raise ValueError(f"Ring observer disagrees on {key} for {original.name}")

    frozen = json.loads((original / "lineups.json").read_bytes())
    payload = (observed / "lineups.json").read_bytes()
    updated = json.loads(payload)
    additions = []
    for side in ("player", "opponent"):
        frozen_items = frozen[side]["items"]
        observed_items = updated[side]["items"]
        if len(frozen_items) != len(observed_items):
            raise ValueError(f"Ring observer changed the number of items for {original.name}")
        for entry, snapshot in zip(frozen_items, observed_items):
            effects = snapshot.pop("placement_effects", None)
            if entry != snapshot:
                raise ValueError(f"Ring observer changed a frozen item for {original.name}")
            if effects is not None:
                if (not isinstance(effects, list) or len(effects) not in (2, 3)
                        or len(effects) != len(entry.get("effects") or [])
                        or entry["identifier"] not in ("Magic Ring", "Superior Ring")
                        or any(set(row) != {"triggerType", "stackType"}
                               or row["triggerType"] not in range(4)
                               or row["stackType"] not in range(100, 111) for row in effects)):
                    raise ValueError(f"Invalid observed ring rolls for {original.name}")
                additions.append((entry, effects))
    if not additions or frozen != updated:
        raise ValueError(f"Ring observer changed lineup metadata or yielded no rolls for {original.name}")
    for entry, effects in additions:
        entry["placement_effects"] = effects
    return frozen, hashlib.sha256(payload).hexdigest()
