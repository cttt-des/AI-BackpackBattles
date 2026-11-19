from pathlib import Path
import shutil
import sys

repo = Path.cwd()
sys.path.insert(0, str(repo))
stage = repo / "output/_v1110"
sim = stage / "sim"
sim.mkdir(exist_ok=True)

def copy(rel):
    src, dst = repo / rel, sim / rel
    dst.parent.mkdir(parents=True, exist_ok=True)
    if src.is_dir():
        shutil.copytree(src, dst, dirs_exist_ok=True,
                        ignore=shutil.ignore_patterns("__pycache__", "gdre", "*.dll", "*.pck", "*.exe", ".import"))
    else:
        shutil.copyfile(src, dst)

for rel in ("simulator", "tools", "gd_core", "gd_core_items", "gd_core_test",
            "native_sim_cpp/gd_core", "native_sim_cpp/gd_core_items", "native_sim_cpp/README.md",
            "native_sim_cpp/tools", "native_sim_cpp/native_sim"):
    copy(rel)
for name in ("gd_core_runtime.json","battle_items.json","characters.json"):
    src = (stage / "assets" / name)
    if not src.is_file():
        src = repo / "assets" / name
    for dest in (sim/"assets",sim/"native_sim_cpp/assets"):
        dest.mkdir(exist_ok=True)
        shutil.copyfile(src, dest / name)
for extra in ("_item_wikidata_static.json", "item_index_map.json", "item_index_map_live.json"):
    if (repo / "assets" / extra).exists():
        copy(f"assets/{extra}")
for entry in ("Godot_v3.6-stable_win64.exe","wintab32.dll"):
    candidate = repo / "output/godot36" / entry
    if candidate.is_file() and (entry != "wintab32.dll" or candidate.read_bytes()[:2] == b"MZ"):
        copy(f"output/godot36/{entry}")

patches = {
    "CoreCharacter.gd": [
        ("if not damageRes.critical and item != null and item.getCritTokens() > 0:",
         "elif item != null and item.getCritTokens() > 0:"),
        ("if not damageRes.critical and opponent.getCritTokens() > 0:",
         "elif opponent.getCritTokens() > 0 and damageSource.isAttackOrEffect():"),
    ]
}
for area in (sim,sim/"gd_core_test",sim/"native_sim_cpp"):
    for name, changes in patches.items():
        path = area/"gd_core"/name
        text = path.read_text("utf8")
        for old, new in changes:
            if text.count(old) != 1:
                raise ValueError(f"Expected one old crit branch: {path} {old}")
            text = text.replace(old, new)
        path.write_text(text,encoding="utf8",newline="\n")

    chess = area/"gd_core_items/Exclusive/ChessMaster.gd"
    text = chess.read_text("utf8")
    text = text.replace("const firstRookRound = 6", "const firstRookRound = 5")
    text = text.replace("const firstQueenRound = 14", "const firstQueenRound = 13")
    chess.write_text(text,encoding="utf8",newline="\n")

# Oracle verification fixture generation needs only source scene data here.
link_items = sim / "oracle/Items"
if not link_items.exists():
    link_items.parent.mkdir(parents=True,exist_ok=True)
    shutil.copytree(stage / "decompiled/Items", link_items, dirs_exist_ok=True,
                    ignore=shutil.ignore_patterns("*.png", "*.mp3", "*.ogg", "*.wav"))
print("Staged GDScript, Python conversion input and C++ conversion input",sim)
