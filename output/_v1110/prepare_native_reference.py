import json
import hashlib
from pathlib import Path
import re
import shutil
import sys

root = Path.cwd()
stage = Path(sys.argv[1] if len(sys.argv) > 1 else "output/_v1110").resolve()
source = stage / "decompiled"
dest = stage / "native_reference"
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
project = re.sub(r'(?m)^config/name=.*$', 'config/name="BackpackBattlesNativeReference"', project)
stubs = {"Steam": "SteamStub", "SilentWolf": "SilentWolfStub",
         "RunDatabase": "RunDatabaseStub", "CrazySDK": "CrazySDKStub"}
(dst_stubs := dest / "oracle_stubs").mkdir(exist_ok=True)
for autoload, file in stubs.items():
    shutil.copyfile(root / "oracle/oracle_stubs" / f"{file}.gd", dst_stubs / f"{file}.gd")
    if autoload == "Steam":
        with (dst_stubs / f"{file}.gd").open("a", encoding="utf8") as stream:
            stream.write("\nsignal current_stats_received(game, results, user)\n")
    elif autoload == "RunDatabase":
        text = (dst_stubs / f"{file}.gd").read_text("utf8")
        text = text.replace("var lobbies = null", "class OfflineLobby:\n\textends Reference\n\tsignal all_end_results_received\n\nvar lobbies = OfflineLobby.new()")
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
shutil.copyfile(root / "output/oracle/expand/data/history.db", dst_db / "history.db")
shutil.copyfile(root / "output/oracle/expand/cases.json", dest / "fights.json")
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
    "engine": "vanilla Godot 3.6; full recovered Main scene; native frame scheduling",
    "battle_script_sha256": hashes,
    "adaptations": ["Offline Steam, leaderboard, SDK and plugin service stubs",
                    "Recovered plaintext table and full-version runtime DLL discovery",
                    "Preparation and activation observers; no manual combat tick"],
    "scope": "Independent recovered-source reference, not the installed shipping EXE"
}, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
print(dest)
