extends Node
# =============================================================================
# SteamStub — 神谕桩（受控神谕工作流 Phase 2 桩化记录 #4）
# =============================================================================
# 原版游戏跑在带 GodotSteam 模块的定制导出模板上，`Steam` 是引擎级原生单例。
# 神谕用的是 vanilla Godot 3.6，没有该单例 → 所有引用 `Steam.xxx` 的脚本
# （Utility/SteamHelper.gd、Utility/Util.gd 等 5 个）在解析期直接报
# "identifier Steam isn't declared" 并连锁崩掉 autoload 装配。
# 这里以同名 autoload 提供最小表面：让 SteamHelper 走「初始化成功但功能空转」
# 的分支（IS_INIT=true 但一切 API 无副作用），绝无任何 Steamworks 调用。
# 红线：神谕不进 Steam 网络/排名；本桩永不与 Steam 客户端通信。
#
# 关键返回值依据 SteamHelper.gd 的分支：
#   steamInit(false) → {"status": 1}      # 否则 onInitFailed 会 quit()（:100-104）
#   isSubscribed()   → true               # 否则 family-sharing 分支 quit()（:108-112）
#   getAppID()       → 2427700 (MAIN_ID)  # 否则 AppID 校验分支 quit()（:116-124）
#   getSteamID()     → 0                  # 保持 isIDValid()==false，历史库走非 Steam 路径
# =============================================================================

const STEAM_APP_ID := 2427700   # Backpack Battles（SteamHelper.MAIN_ID）


func _ready() -> void :
	print("[ORACLE-STUB] Steam singleton stub active (no Steamworks)")


func steamInit(_async = false) -> Dictionary:
	return {"status": 1, "verbal": "oracle-stub"}


func loggedOn() -> bool:
	return false


func isSubscribed() -> bool:
	return true


func isSubscribedFromFamilySharing() -> bool:
	return false


func getAppID() -> int:
	return STEAM_APP_ID


func getSteamID() -> int:
	return 0


func getPersonaName() -> String:
	return "oracle"


func getCurrentGameLanguage() -> String:
	return "english"


func isSteamRunningOnSteamDeck() -> bool:
	return false


func requestCurrentStats() -> void:
	pass


func getStatInt(_name: String) -> int:
	return 0


func setStatInt(_name: String, _value: int) -> void:
	pass


func storeStats() -> void:
	pass


func getAchievement(_name: String) -> Dictionary:
	return {"ret": false, "achieved": false}


func setAchievement(_name: String) -> void:
	pass


func setRichPresence(_key: String, _value: String) -> void:
	pass


func run_callbacks() -> void:
	pass


func isSteamRunning() -> bool:
	return false


func showFloatingGamepadTextInput(_a, _b, _c, _d, _e) -> void:
	pass


func findLeaderboard(_name: String) -> void:
	pass


func downloadLeaderboardEntries(_a, _b, _c, _d) -> void:
	pass


func uploadLeaderboardScore(_a, _b, _c, _d, _e = null) -> void:
	pass


func getServerRealTime() -> int:
	return 0
