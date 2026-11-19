"""Validate durable products from one native recording process."""
import json


def check_battle_products(folder, cid, expected, started_ns=None):
    paths = [folder / cid / name for name in ("events.json", "lineups.json", "boundaries.json")]
    if started_ns is not None and any(path.stat().st_mtime_ns < started_ns for path in paths):
        raise ValueError(f"Stale output for {cid}")
    events, lineups, boundaries = [json.loads(path.read_bytes()) for path in paths]
    identity = {key: int(expected[key]) for key in ("seed", "run_id", "round_id")}
    identity["opp_run_id"] = int(expected.get("opp_run_id", identity["run_id"]))
    identity["opp_round_id"] = int(expected.get("opp_round_id", identity["round_id"]))
    rows = events["events"]
    winner = {"player": 111, "opponent": 112}.get(events["winner"])
    if (not rows or winner is None or events["event_count"] != len(rows) or rows[-1]["type"] != winner
            or round(rows[-1]["timestamp"] * 60) != round(events["combat_time"] * 60)
            or any(doc.get("case_id", cid) != cid or any(doc[key] != value for key, value in identity.items())
                   for doc in (events, lineups))
            or any(key not in boundaries for key in
                   ("prepare", "before_activate", "idle_animation_timers", "flicker_states"))):
        raise ValueError(f"Invalid battle products for {cid}")


def check_completed_products(folder, case_ids, lines, started_ns, case_rows):
    errors = [line for line in lines if "SCRIPT ERROR" in line or "Debugger Break" in line]
    if errors:
        raise ValueError("Script errors: " + "\n".join(errors))
    missing = [cid for cid in case_ids if not any(f"[NATIVE] Recorded {cid} " in line for line in lines)]
    if missing and f"[NATIVE-BATCH] completed={len(case_ids)}" not in lines:
        raise ValueError(f"Missing completion marker for {missing}")

    by_id = {row["case_id"]: row for row in case_rows}
    for cid in case_ids:
        check_battle_products(folder, cid, by_id[cid], started_ns)
    return missing
