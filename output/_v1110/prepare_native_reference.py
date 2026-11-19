import json
import hashlib
from pathlib import Path
import re
import shutil
import sys
import argparse

root = Path.cwd()
parser = argparse.ArgumentParser()
parser.add_argument("stage", nargs="?", default="output/_v1110")
parser.add_argument("--rng-probe", action="store_true")
parser.add_argument("--cohort", choices=("expand", "base"), default="expand")
parser.add_argument("--project-name", default="native_reference")
args = parser.parse_args()
stage = Path(args.stage).resolve()
source = stage / "decompiled"
rng_probe = args.rng_probe
dest = (stage / args.project_name).resolve()
if dest.parent != stage:
    parser.error("The isolated project must be a direct child of the stage directory")
manifest = json.loads((stage / "source_manifest.json").read_text("utf8"))
if manifest.get("version") != "1.1.10":
    raise SystemExit("Expected the installed 1.1.10 source")
if not dest.exists():
    shutil.copytree(source, dest)
# The editor binary reports editor=true while running an exported project.
# Supply the recovered plaintext table for its native CSV import branch.
shutil.copyfile(stage / "ItemData_1.1.10.csv", dest / "Sheets/CSV/ItemData.csv")
shutil.copyfile(stage / "raw/Sheets/CSV/ItemData_e.csv", dest / "Sheets/CSV/ItemData_e.csv")
shutil.copyfile(source / "Utility/DataValidator.gd", dest / "Utility/DataValidator.gd")
item_book = (source / "Sheets/ItemBook.gd").read_text("utf8")
encrypted_load = 'Table.new().loadFromCsv("res://Sheets/CSV/ItemData_e.csv", sheetKey)'
assert item_book.count(encrypted_load) == 1
item_book = item_book.replace(encrypted_load, 'Table.new().loadFromCsv("res://Sheets/CSV/ItemData.csv")')
(dest / "Sheets/ItemBook.gd").write_text(item_book, encoding="utf8")
util = (source / "Utility/Util.gd").read_text("utf8")
for function, process in (("callDelayed", "false"), ("callDelayed_process", "true")):
    anchor = f"func {function}(target, methodName, delay, binds = []):\n\tvar timer = get_tree().create_timer(delay, {process})\n"
    assert util.count(anchor) == 1
    util = util.replace(anchor, anchor + '''\tvar observer = get_tree().root.get_node_or_null("NativeBattleReader")
	if observer != null:
		observer.on_delayed_timer(timer, target, methodName)
''')
if rng_probe:
    anchor = "var rng = RandomNumberGenerator.new()"
    assert util.count(anchor) == 1
    util = util.replace(anchor, 'var rng = preload("res://native_rng_observer.gd").new()')
    shutil.copyfile(stage / "native_rng_observer.gd", dest / "native_rng_observer.gd")
(dest / "Utility/Util.gd").write_text(util, encoding="utf8")
game = (source / "Core/Game.gd").read_text("utf8")
game = game.replace('var EDITOR = OS.has_feature("editor")', 'var EDITOR = false')
# Read-only observations at the source's preparation and activation boundaries.
# The source still owns ordering, random draws, timers and battle transitions.
for function, observer in (("prepareItems", "on_prepare"), ("activateItems", "on_activate")):
    anchor = f"func {function}(items):\n"
    assert game.count(anchor) == 1
    game = game.replace(anchor, anchor + f'\tget_node("/root/NativeBattleReader").{observer}(items)\n')
for name in ("requestOpponentPoolAccessCheck", "_startModUpdateChecks"):
    start = re.search(rf"(?m)^func {name}\([^\n]*\n", game)
    next_function = re.search(r"(?m)^func ", game[start.end():])
    end = start.end() + next_function.start() if next_function else len(game)
    game = game[:start.end()] + "\t# Plugin service requests are omitted in offline replay.\n\treturn\n\n" + game[end:]
(dest / "Core/Game.gd").write_text(game, encoding="utf8")
runtime = dest / "runtime"
runtime.mkdir(exist_ok=True)
shutil.copyfile(root / "output/godot36/Godot_v3.6-stable_win64.exe", runtime / "Godot_v3.6-stable_win64.exe")
for name in ("libgdsqlite.dll", "steam_api64.dll"):
    shutil.copyfile(stage / "source" / name, runtime / name)
project = (source / "project.godot").read_text("utf8")
project = re.sub(r'(?m)^config/name=.*$', 'config/name="BackpackBattlesNative_' + args.project_name + '"', project)
stubs = {"Steam": "SteamStub", "SilentWolf": "SilentWolfStub",
         "RunDatabase": "RunDatabaseStub", "CrazySDK": "CrazySDKStub"}
(dst_stubs := dest / "oracle_stubs").mkdir(exist_ok=True)
for autoload, file in stubs.items():
    shutil.copyfile(root / "oracle/oracle_stubs" / f"{file}.gd", dst_stubs / f"{file}.gd")
    if autoload == "Steam":
        steam = (dst_stubs / f"{file}.gd").read_text("utf8")
        for name in ("storeStats", "showFloatingGamepadTextInput"):
            steam, count = re.subn(rf"(func {name}\([^\n]*\)) -> void:\n\tpass", r"\1 -> bool:\n\treturn false", steam)
            assert count == 1
        (dst_stubs / f"{file}.gd").write_text(steam, encoding="utf8")
        with (dst_stubs / f"{file}.gd").open("a", encoding="utf8") as stream:
            stream.write("\nsignal current_stats_received(game, results, user)\n")
    elif autoload == "RunDatabase":
        text = (dst_stubs / f"{file}.gd").read_text("utf8")
        text = text.replace("var lobbies = null", "class OfflineLobby:\n\textends Reference\n\tsignal all_end_results_received\n\tfunc isInLobby() -> bool:\n\t\treturn false\n\nvar lobbies = OfflineLobby.new()")
        (dst_stubs / f"{file}.gd").write_text(text, encoding="utf8")
    line = f'{autoload}="*res://oracle_stubs/{file}.gd"'
    if autoload == "Steam":
        project = project.replace("[autoload]\n", f"[autoload]\n\n{line}\n", 1)
    else:
        project, count = re.subn(fr'(?m)^{autoload}=.*$', line, project)
        if count != 1:
            raise ValueError(f"Missing autoload: {autoload}")
project = project.replace("\n[debug]", '\nNativeBattleReader="*res://native_battle_reader.gd"\n\n[debug]', 1)
(dest / "project.godot").write_text(project,encoding="utf8")
(dst_db := dest / "data").mkdir(exist_ok=True)
history = root / ("output/oracle/expand/data/history.db" if args.cohort == "expand" else "oracle/data/history.db")
case_list = root / ("output/oracle/expand/cases.json" if args.cohort == "expand" else "oracle/fights.json")
shutil.copyfile(history, dst_db / "history.db")
shutil.copyfile(case_list, dest / "fights.json")
for src in (root / "oracle/addons/godot-sqlite").rglob("*.dll"):
    dst = dest / src.relative_to(root / "oracle")
    if not dst.exists():
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(src, dst)

harness = (root / "oracle/oracle_fight.gd").read_text("utf8")
def get_function(name):
    start = re.search(rf"(?m)^func {name}\(",harness).start()
    end = re.search(r"(?m)^func ",harness[start+5:])
    fragment = harness[start:start+5+end.start()] if end else harness[start:]
    return fragment.rstrip() + "\n"
reader = (stage / "native_battle_reader.header.gd").read_text("utf-8-sig")
body = reader + "\n\n" + "\n".join(get_function(name) for name in (
    "load_history_runs", "_jsonable", "_jsonable_impl", "dump_events", "dump_lineups",
    "_item_snapshot", "snapshot_side"))
(dest / "native_battle_reader.gd").write_text(body,encoding="utf8")
combat_files = ["Core/Character.gd", "Core/Buff.gd", "Core/CombatLog.gd",
                "Items/Item.gd", "Interface/CombatTimer/CombatTimer.gd"]
hashes = {}
for relative in combat_files:
    original_bytes = (source / relative).read_bytes()
    if (dest / relative).read_bytes() != original_bytes:
        raise ValueError(f"Native reference battle script has changed: {relative}")
    hashes[relative] = hashlib.sha256(original_bytes).hexdigest()
(dest / "reference_manifest.json").write_text(json.dumps({
    "version": manifest["version"], "source_provenance": manifest.get("provenance"),
    "cohort": args.cohort,
    "case_list_sha256": hashlib.sha256(case_list.read_bytes()).hexdigest(),
    "history_snapshot_sha256": hashlib.sha256(history.read_bytes()).hexdigest(),
    "reader_sha256": hashlib.sha256((dest / "native_battle_reader.gd").read_bytes()).hexdigest(),
    "engine": "vanilla Godot 3.6; full recovered Main scene; native frame scheduling",
    "battle_script_sha256": hashes,
    "adaptations": ["Offline Steam, leaderboard, SDK and plugin service stubs",
                    "Recovered plaintext table and full-version runtime DLL discovery",
                    "Preparation, activation and pending visual timer observers; no manual combat tick",
                    "Global engine PCG position observed and restored at preparation and activation",
                    "Batches return through the source history menu; adapter selects records and resets its UI fight guard",
                    "Read-only RNG call observer enabled" if rng_probe else "Native RNG object unchanged"],
    "scope": "Independent recovered-source reference, not the installed shipping EXE"
}, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
print(dest)
