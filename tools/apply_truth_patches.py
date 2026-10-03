# -*- coding: utf-8 -*-
"""
对 godot_project 运行副本一次性应用全部真值机补丁（幂等，可重复执行）。

用法：
  python tools/apply_truth_patches.py <godot_project路径>

补丁清单（只改运行副本，repo-review/decompiled_full 真值树永不触碰）：
 1. 写 Stub/Steam.gd（GodotSteam 离线桩）
 2. project.godot autoload 注册 Steam
 3. Core/Game.gd：
    - var EDITOR = false（生产配置；防 validateResources 重写工程文件）
    - const TRUTH_HEADLESS = true
    - startRun / isInLobby 两处 lobbies 空值守卫
    - _ready 顶部 call_deferred("truth_late_init") + initPlayer() 提前
    - ready_deferred：跳过 MaterialCompiler 等待 + loadRunState×2 门控
    - 追加 truth_late_init()（30 个 onready 重取）
    - 27 个 onready 赋值空安全化（get_node_or_null，防 _ready 整体中止）
 4. Sheets/ItemBook.gd：ItemData_e.csv 明文加载（7z 内已是解密明文）
 5. 从 .assets 补 6 个 raw CSV 到 Sheets/CSV/
"""
import re
import shutil
import sys
from pathlib import Path

STEAM_STUB = '''# Steam API 离线桩（headless 真值机用，自动生成于 apply_truth_patches）
extends Node

signal current_stats_received
signal item_created
signal item_updated
signal leaderboard_find_result
signal leaderboard_scores_downloaded
signal leaderboard_score_uploaded
signal leaderboard_ugc_set
signal lobby_chat_update
signal lobby_created
signal lobby_data_update
signal lobby_joined
signal lobby_message
signal lobby_match_list
signal p2p_session_request
signal persona_state_change

var app_id: int = 2427700

func isSteamRunning() -> bool: return false
func isSteamRunningOnSteamDeck() -> bool: return false
func isSubscribed() -> bool: return false
func isSubscribedFromFamilySharing() -> bool: return false
func loggedOn() -> bool: return false
func getSteamID() -> int: return 0
func getAppID() -> int: return app_id
func getPersonaName() -> String: return "offline_truth"
func getCurrentGameLanguage() -> String: return "english"
func getServerRealTime() -> int: return OS.get_unix_time()
func requestCurrentStats() -> bool: return false
func run_callbacks() -> void: pass
func getStatInt(_s: String) -> int: return 0
func setStatInt(_s: String, _v: int) -> bool: return false
func getAchievement(_n: String) -> bool: return false
func setAchievement(_n: String) -> bool: return false
func clearAchievement(_n: String) -> bool: return false
func storeStats() -> bool: return false
func findLeaderboard(_n: String) -> void: pass
func downloadLeaderboardEntries(_s: int, _e: int, _t: int = 0, _h: int = 0) -> void: pass
func uploadLeaderboardScore(_s: int, _k: bool = true, _d: Array = [], _h: int = 0) -> void: pass
func createLobby(_t: int, _m: int) -> void: pass
func joinLobby(_l: int) -> void: pass
func leaveLobby(_l: int) -> void: pass
func getLobbyOwner(_l: int) -> int: return 0
func getLobbyData(_l: int, _k: String) -> String: return ""
func setLobbyData(_l: int, _k: String, _v: String) -> bool: return false
func getLobbyMemberData(_l: int, _m: int, _k: String) -> String: return ""
func setLobbyMemberData(_l: int, _k: String, _v: String) -> bool: return false
func sendLobbyChatMsg(_l: int, _m: String) -> bool: return false
func createItem(_a: int, _f: int) -> void: pass
func setItemTitle(_h: int, _t: String) -> bool: return false
func setItemDescription(_h: int, _d: String) -> bool: return false
func setItemMetadata(_h: int, _m: String) -> bool: return false
func setItemContent(_h: int, _f: String) -> bool: return false
func setItemPreview(_h: int, _p: String) -> bool: return false
func setItemTags(_h: int, _t: Array) -> bool: return false
func setItemVisibility(_h: int, _v: int) -> bool: return false
func setItemUpdateLanguage(_h: int, _l: String) -> bool: return false
func submitItemUpdate(_h: int, _c: String) -> void: pass
func createQueryUGCDetailsRequest(_i: Array) -> void: pass
func sendQueryUGCRequest(_h: int) -> void: pass
func getQueryUGCMetadata(_h: int, _i: int = 0, _k: String = "") -> String: return ""
func releaseQueryUGCRequest(_h: int) -> void: pass
func destroyResult(_h: int) -> void: pass
func steamInit(_retrieve_stats: bool = true) -> Dictionary: return {"status": 0, "verbal": "offline stub"}
'''


def patch(path: Path, old: str, new: str, count: int = 1) -> bool:
    t = path.read_text(encoding="utf-8")
    if new in t:
        return True  # 幂等
    if t.count(old) != count:
        print(f"  !! 锚点不符: {path.name}: {old[:60]!r} x{t.count(old)}")
        return False
    path.write_text(t.replace(old, new, count), encoding="utf-8")
    return True


def main() -> int:
    root = Path(sys.argv[1]).resolve()
    game_gd = root / "Core" / "Game.gd"
    itembook_gd = root / "Sheets" / "ItemBook.gd"
    godot = root / "project.godot"
    ok = True

    # 1. Steam 桩
    stub = root / "Stub"
    stub.mkdir(exist_ok=True)
    (stub / "Steam.gd").write_text(STEAM_STUB, encoding="utf-8")

    # 2. autoload
    ok &= patch(godot, '[autoload]\n\nControllerIcons=',
                '[autoload]\n\nSteam="*res://Stub/Steam.gd"\nControllerIcons=')

    # 3. Game.gd
    ok &= patch(game_gd, "const LOBBIES_ENABLED = true",
                "const LOBBIES_ENABLED = true\nconst TRUTH_HEADLESS = true")
    ok &= patch(game_gd,
                "if LOBBIES_ENABLED and curMode != Mode.Lobbies and RunDatabase.lobbies.isInLobby():",
                "if LOBBIES_ENABLED and RunDatabase.lobbies != null and curMode != Mode.Lobbies and RunDatabase.lobbies.isInLobby():")
    ok &= patch(game_gd,
                "func isInLobby() -> bool:\n\treturn RunDatabase.lobbies.isInLobby()",
                "func isInLobby() -> bool:\n\treturn RunDatabase.lobbies != null and RunDatabase.lobbies.isInLobby()")
    ok &= patch(game_gd,
                "func _ready() -> void :\n\tpause_mode = Node.PAUSE_MODE_PROCESS",
                "func _ready() -> void :\n\tpause_mode = Node.PAUSE_MODE_PROCESS\n\tcall_deferred(\"truth_late_init\")")
    ok &= patch(game_gd, "\tcall_deferred(\"ready_deferred\")",
                "\tinitPlayer()  # 真值机补丁：persistent 默认值须先于 ready_deferred 就位\n\tcall_deferred(\"ready_deferred\")")
    ok &= patch(game_gd,
                "\tif is_instance_valid(MaterialCompiler):\n\t\tyield(MaterialCompiler, \"finished_loading_materials\")",
                "\t# 真值机补丁：headless 下 MaterialCompiler 永不发完成信号，跳过等待\n\tif is_instance_valid(MaterialCompiler) and not TRUTH_HEADLESS:\n\t\tyield(MaterialCompiler, \"finished_loading_materials\")")
    ok &= patch(game_gd, "\tloadRunState(Mode.Unranked, false)",
                "\t# 真值机补丁：loadRunState 触发存档/网络链，headless 下永远新开一局\n\tif not TRUTH_HEADLESS:\n\t\tloadRunState(Mode.Unranked, false)")
    ok &= patch(game_gd, "\tif LOBBIES_ENABLED and loadRunState(Mode.Lobbies):",
                "\tif LOBBIES_ENABLED and not TRUTH_HEADLESS and loadRunState(Mode.Lobbies):")

    # onready 空安全化（仅在尚未处理时）
    t = game_gd.read_text(encoding="utf-8")
    if "get_node_or_null(\"SplashscreenAnimation\")" not in t:
        lines = t.split("\n")
        out, n = [], 0
        for l in lines:
            m = re.match(r"onready var (\w+) = (\w+)\.get_node\((.+)\)\s*$", l)
            if m:
                name, recv, p = m.groups()
                out.append(f"onready var {name} = ({recv}.get_node_or_null({p}) if {recv} != null else null)")
                n += 1
            else:
                out.append(l)
        game_gd.write_text("\n".join(out), encoding="utf-8")
        print(f"  onready 空安全化 {n} 处")

    # truth_late_init 追加
    t = game_gd.read_text(encoding="utf-8")
    if "func truth_late_init" not in t:
        onready = [l for l in t.split("\n") if l.startswith("onready var ")]
        assign = "\n".join("\t" + l.replace("onready var ", "", 1) for l in onready)
        method = ("\n# 真值机补丁：autoload _ready 先于主场景，onready 落空；Main 入树后延迟重取（幂等）\n"
                  "func truth_late_init() -> void:\n"
                  "\t# 确定性：ready_deferred 的初始物品/loadout 抽取须在播种后消费 RNG\n"
                  "\tUtil.rng.seed = TRUTH_SEED\n"
                  "\tseed(TRUTH_SEED)\n" + assign + "\n")
        game_gd.write_text(t.rstrip("\n") + "\n" + method, encoding="utf-8")
        print(f"  truth_late_init 追加（{len(onready)} 变量）")

    # 3b. validateResources 写保护（EDITOR=true 时会重写工程文件，headless 下禁止）
    ok &= patch(itembook_gd,
                "func validateResources():\n\tfor i in 32:\n\t\tsheetKey.append(i)\n\tif Game.EDITOR:",
                "func validateResources():\n\tfor i in 32:\n\t\tsheetKey.append(i)\n\tif Game.EDITOR and not Game.TRUTH_HEADLESS:")

    # 4. ItemBook 明文加载
    ok &= patch(itembook_gd,
                'table = Table.new().loadFromCsv("res://Sheets/CSV/ItemData_e.csv", sheetKey)',
                'table = Table.new().loadFromCsv("res://Sheets/CSV/ItemData_e.csv")  # 真值机补丁：7z 内为解密明文')

    # 5. 补 CSV
    for f in ["Items", "Full", "ExclusiveItems", "Flavor", "Keywords", "Interface"]:
        src = root / ".assets" / "Sheets" / "CSV" / f"{f}.csv"
        dst = root / "Sheets" / "CSV" / f"{f}.csv"
        if src.exists() and not dst.exists():
            shutil.copy(src, dst)

    print("全部补丁应用完成" if ok else "有补丁失败，见上方 !! 行")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
