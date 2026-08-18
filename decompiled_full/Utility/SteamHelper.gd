extends Node

const achievementPopupScene = preload("res://Interface/AchievementPopup.tscn")


var IS_INIT: bool = false
var IS_OWNED: bool = false
var IS_ONLINE: bool = false
var IS_FREE_WEEKEND: bool = false
var STEAM_ID: int = 0
var STEAM_NAME: String = ""
var GAME_LANG: String
var LOCALE: String
var STATS_RECEIVED = false
var SEQUENCE_NUM: = 0
var SEQUENCE_NUM_LOBBIES: = 0
var STORESTATS_READYTIME = 0.0
var APP_ID: int
var STEAMDECK: bool = false

var achievementQueue: = []
var achievementTimer
var unlockedThisSession: = {}

const MAIN_ID = 2427700
const DEMO_ID = 2444170
const PLAYTEST_ID = 2747170

const langCodes = {
	"english": "en", 
	"schinese": "zh_Hans_CN", 
	"japanese": "ja", 
	"koreana": "ko", 
	"german": "de", 
	"tchinese": "zh_Hant_TW", 
	"french": "fr", 
	"brazilian": "pt", 
	"russian": "ru", 
	"latam": "es"
}

func is_init():
	return IS_INIT

func _process(_delta: float) -> void :
	
	Steam.run_callbacks()

func isIDValid():
	return STEAM_ID != 0

func _ready() -> void :
	pause_mode = Node.PAUSE_MODE_PROCESS
	set_process(false)
	if OS.has_feature("disable_steam_integration"):
		return
	
	if not Game.EDITOR:
		var exePath = OS.get_executable_path()
		var exeDir = exePath.get_base_dir()
		var dir = Directory.new()
		if dir.open(exeDir) == OK:
			if OS.has_feature("Windows"):



				
				var dll2 = dir.file_exists("steam_api64.dll")
				if not dll2:
					print("[STEAM] Failed to initialize Steam - steam_api64.dll missing")
				
				if not dll2 and not Game.loadExclusiveContent():
					return
			else:
				



				
				var dll2 = dir.file_exists("libsteam_api.so")
				if not dll2:
					print("[STEAM] Failed to initialize Steam - libsteam_api.so missing")
				
				if not dll2 and not Game.loadExclusiveContent():
					return
				
		else:
			print("[STEAM] Failed to initialize Steam - cannot open executable dir")
			if not Game.loadExclusiveContent():
				return
	
	
	
	var INIT: Dictionary = Steam.steamInit(false)
	print("[STEAM] Did Steam initialize?: " + str(INIT))
	
	if INIT["status"] != 1:
		
		print("[STEAM] Failed to initialize Steam. " + str(INIT["verbal"]))
		onInitFailed()
	else:
		IS_ONLINE = Steam.loggedOn()
		IS_OWNED = Steam.isSubscribed()
		if not IS_OWNED:
			var FAMILY_SHARED = Steam.isSubscribedFromFamilySharing()
			if not FAMILY_SHARED:
				get_tree().quit()
		
		IS_INIT = true
		set_process(true)
		
		APP_ID = Steam.getAppID()
		
		
		if APP_ID == MAIN_ID:
			if not Game.FULLVERSION or Game.PLAYTEST:
				get_tree().quit()
		elif APP_ID == DEMO_ID:
			if Game.FULLVERSION:
				get_tree().quit()
		elif APP_ID == PLAYTEST_ID:
			if not Game.PLAYTEST:
				get_tree().quit()
		else:
			print("Launching ", APP_ID)
			get_tree().quit()
			
		STEAM_ID = Steam.getSteamID()
		STEAM_NAME = Steam.getPersonaName()
		
	
		
		GAME_LANG = Steam.getCurrentGameLanguage()
		if GAME_LANG in langCodes:
			LOCALE = langCodes[GAME_LANG]
		
		STEAMDECK = Steam.isSteamRunningOnSteamDeck()
		
		Steam.connect("current_stats_received", self, "onStatsReceived")
		Steam.requestCurrentStats()
		
		achievementTimer = Timer.new()
		add_child(achievementTimer)
		achievementTimer.one_shot = true
		achievementTimer.connect("timeout", self, "showNextAchievement")

func onInitFailed():
	if (Game.PLAYTEST or Game.FULLVERSION) and not Game.EDITOR:
		get_tree().quit()

func onStatsReceived(game, results, user):
	
	
	
	
	getAllStats()
	
	
	

func getAllStats():
	SEQUENCE_NUM = Steam.getStatInt("sequence_num")
	SEQUENCE_NUM_LOBBIES = Steam.getStatInt("sqn2")
	Util.eprint("sequence num: ", SEQUENCE_NUM)
	STATS_RECEIVED = true

func getSequenceNum(mode) -> int:
	if mode == Game.Mode.Lobbies:
		return SEQUENCE_NUM_LOBBIES
	else:
		return SEQUENCE_NUM

func incrementSequenceNumber(mode) -> void :
	if STATS_RECEIVED:
		if mode == Game.Mode.Lobbies:
			SEQUENCE_NUM_LOBBIES += 1
			Steam.setStatInt("sqn2", SEQUENCE_NUM_LOBBIES)
			
		else:
			SEQUENCE_NUM += 1
			Steam.setStatInt("sequence_num", SEQUENCE_NUM)
			
			
		
		storeStats()
		







func storeStats():
	var res = Steam.storeStats()
	Util.eprint("store stats ", res)


















func updateRichPresence():
	if not IS_INIT:
		return
	
	if Game.buildHistory.isOpen or Game.curMode == Game.Mode.History:
		addRichPresence("steam_display", "#History")
	elif Game.state == Game.State.Title:
		addRichPresence("steam_display", "#status_Menu")
	else:
		addRichPresence("gamemode", Game.Mode.keys()[Game.curMode])
		addRichPresence("class", Game.getClassOrSubclass())
		addRichPresence("numwins", String(Game.getNumWins()))
		addRichPresence("roundnum", String(Game.curRound))
		addRichPresence("steam_display", "#status_Ingame")

func addRichPresence(key, value):
	Steam.setRichPresence(key, value)

func canUnlock(allowInCustom = false) -> bool:
	return (allowInCustom or (
			not CustomRules.areCustomRulesActive() and 
			Game.curMode != Game.Mode.Lobbies and 
			Game.curMode != Game.Mode.History))

func unlockAchievement(aName: String, allowInCustom = false):
	if Game.ACHIEVEMENTS_ENABLED and STATS_RECEIVED:
		if canUnlock(allowInCustom):
			
			var curState = Steam.getAchievement(aName)
			if curState.ret and not curState.achieved:
				Steam.setAchievement(aName)
				Util.eprint("Achievement unlocked: ", aName)
				storeStats()
				
				achievementQueue.push_back(aName)
				if achievementTimer.is_stopped():
					showNextAchievement()
				
	if Game.EDITOR and canUnlock(allowInCustom) and not aName in unlockedThisSession:
		unlockedThisSession[aName] = true
		Util.eprint("Would unlocked achievement ", aName)




func showNextAchievement():
	if achievementQueue.empty(): return
	
	var achievementName = achievementQueue.pop_front()
	var popup = ObjectPool.instance(achievementPopupScene)
	Game.UINode.add_child(popup)
	popup.showPopup(10)
	achievementTimer.start(3)
	Game.giveTrophies(10)

func hasAchievement(aName: String) -> bool:
	if not STATS_RECEIVED: return true
	
	var curState = Steam.getAchievement(aName)
	return curState.achieved

func changeStat(statName: String, amount: int):
	if STATS_RECEIVED and Game.ACHIEVEMENTS_ENABLED and canUnlock():
		var cur = Steam.getStatInt(statName)
		var new = cur + amount
		Steam.setStatInt(statName, new)
		return new
	return - 1

func dropItem():
	var grantedItem = Steam.triggerItemDrop(10000)
	if grantedItem != 0:
		Util.eprint("inventory handle: ", grantedItem)
		Steam.destroyResult(grantedItem)
