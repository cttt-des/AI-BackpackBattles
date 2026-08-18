extends Node2D

var EDITOR = OS.has_feature("editor")
var isWeb = OS.has_feature("web")
var PLAYTEST = OS.has_feature("playtest")
var FULLVERSION = OS.has_feature("full_version") or Util.debugOnly(true)
var DEMO = not FULLVERSION and not PLAYTEST
var EXPO = OS.has_feature("expo")
var ENGINEER_TEST = OS.has_feature("engineertest")
var VERSION = "1.1.8"

const SUBVERSION = ""
const BETA = false
const PREVIEW = false
const leaderboardBreakingVersion = "1.1.5"
const runStateBreakingVersion = "1.1.0"

const ITEM_STATISTICS_ENABLED = true
const LOADOUTS_ENABLED = true
const SKILLS_ENABLED = true
const USE_ICONS = true
const BUILD_HISTORY_ENABLED = true
const RECIPE_TOOLTIPS_ENABLED = true
const LOBBIES_ENABLED = true
const STAT_DISPLAY_ENABLED = true
const ACHIEVEMENTS_ENABLED = true

signal gold_changed
signal trophies_changed
signal item_picked_up
signal item_dropped
signal inventory_changed
signal item_bought
signal special_item_bought
signal item_sold
signal item_crafted
signal crafting_finished
signal item_gained_focus

signal crafting_ready
signal continue_loaded
signal runstate_suspended
signal runstate_loaded
signal character_changed
signal random_character_changed
signal style_changed
signal chibi_setting_changed
signal input_changed
signal device_changed
signal records_updated
signal combat_start_pressed
signal switching_to_combat
signal combat_scene_entered
signal combat_scene_left
signal combat_start
signal combat_end


signal switch_to_shop
signal title_to_shop
signal shop_opened
signal pre_shop_opened_from_title
signal pre_shop_opened_from_combat
signal shop_closed
signal return_to_title
signal returned_to_title
signal return_to_history
signal round_result
signal round_start_gold_gained
signal round_start_health_gained
signal run_started
signal fresh_run_started
signal run_over
signal game_paused
signal game_unpaused
signal menu_open
signal menu_opened
signal menu_close
signal tutorial_done
signal loadout_changed
signal interactable_hovered
signal edit_mode_changed
signal item_list_closed
signal warp_cursor_shop
signal warp_cursor_combat
signal warp_cursor_title
signal warp_cursor_menu
signal get_rects_shop
signal get_rects_combat
signal get_rects_title
signal get_rects_menu

enum State{
	Title, 
	Shop, 
	Combat
}

enum PauseSource{
	Unpaused = 0, 
	Options = 1, 
	FocusLost = 2, 
	Ad = 4, 
	RecipeBook = 8, 
	PatchNotes = 16, 
	All = 31
}

enum ContinueState{
	NotContinued, 
	FromShop, 
	FromCombat
}

enum RoundResult{
	Win, 
	Loss, 
	Draw, 
	RunOver
}

enum Classes{
	Ranger = 0, 
	Reaper = 1
	Berserker = 2, 
	Pyromancer = 3
}

enum Classes_Full{
	Ranger = 0, 
	Reaper = 1
	Berserker = 2, 
	Pyromancer = 3, 
	Mage = 4, 
	Adventurer = 5, 
	Engineer = 6
}

enum Mode{
	Ranked = 0, 
	Unranked = 1, 
	Lobbies = 2, 
	Unselected = 3, 
	History = 4
}

enum Loadout{
	Loadout1 = 0, 
	Loadout2 = 1, 
	RandomLoadout = 2, 
	RandomCharacter = 3
}

enum Leagues{
	Bronze = 0, 
	Silver = 1, 
	Gold = 2, 
	Platinum = 3, 
	Diamond = 4, 
	Master = 5, 
	Grandmaster = 6, 
	Grandma = 7, 
	ImpossibleWoodRank = - 1
}

enum SkinSlot{
	Head = 0, 
	Weapon = 1, 
	Body = 2, 
	Special = 3, 
	Shoes = 4
}

const backup_format = "user://{ID}{build}backup"
const savefile_format = "user://{ID}{build}backpack.save"
const runstate_format = "user://{ID}{build}continue.save"
const lobby_runstate_format = "user://{ID}{build}lobby.save"
const config_format = "user://{ID}{build}backpack.cfg"
const baseDir_format = "user://{ID}{build}"
const offlinesave_format = "user://{ID}{build}backpack.ba"

const playerScene = preload("res://Core/Player.tscn")
const opponentScene = preload("res://Core/Opponent.tscn")
const playerMoveInSound = preload("res://Assets/Sound/Swoosh1.wav")

const MAX_WINS = 10
const MAX_ROUNDS = 18
const MAX_TRIES = 5
const MAX_HEALTH = 999
const MAX_STAMINA = 999
const MAX_NAME_LEN = 16
const COMBAT_DELAY = 2.5
const playerCombatPos = 350
const goldGain = [
	0, 13, 10, 10, 11, 11, 
	12, 12, 13, 13, 14, 
	14, 15, 15, 16, 
	16, 16, 16, 16, 16]
const BAG_PITY_TIMER = 9
const SUBCLASS_ROUND = 8
const SKILL_ROUND1 = 3
const SKILL_ROUND2 = 10
const MAX_WINS_TROPHIES = 10
const PERFECT_RUN_TROPHIES = 20
const SURVIVED_TROPHIES = 10
const PERFECT_SURVIVAL_TROPHIES = 20
const MAX_WINS_RATING = 5
const PERFECT_RUN_RATING = 7.5
const SURVIVED_RATING = 7
const PERFECT_SURVIVAL_RATING = 12
const RANK_UP_BONUS_RANKING = 10
const MAX_TRIES_LOBBIES = MAX_TRIES
const MAX_ROUNDS_LOBBIES = MAX_ROUNDS
const LOBBY_TIMEOUT_MINUTES = 20

const BROWN = Color(0.24, 0.15, 0.11)
const SOFTWHITE = Color(1, 0.92549, 0.831373)
const rarityColors = [
	Color(0.738144, 0.827926, 0.839844), 
	Color(0.230469, 0.549103, 1), 
	Color(0.769243, 0.028076, 0.898438), 
	Color(0.988281, 0.595056, 0.038605), 
	Color(1, 0.970215, 0.523438), 
	Color(0.530212, 0.929688, 0.630081)
]
const leagueColors = [
	Color(0.988281, 0.585254, 0.366745), 
	Color(0.796875, 0.756506, 0.734619), 
	Color(0.974609, 0.869506, 0.485401), 
	Color(0.848335, 0.9495, 0.980469), 
	Color(0.761719, 0.983246, 1), 
	Color(0.4, 0.7, 2), 
	Color(1.5, 0.8, 0.2), 
	Color(0.789063, 0.095551, 0.371872)
]

onready var root = get_parent()
onready var mainNode = root.get_node("Main")
onready var splashScreenAnimation = mainNode.get_node("SplashscreenAnimation")
onready var sceneAnimation = mainNode.get_node("SceneAnimation")
onready var combatSceneNode = mainNode.get_node("Combat")
onready var opponentNode = combatSceneNode.get_node("Opponent")
onready var combatUINode = combatSceneNode.get_node("UI")
onready var combatAnimationsNode = combatSceneNode.get_node("ItemAnimations")
onready var combatTimer = combatUINode.get_node("%CombatTimer")
onready var shopSceneNode = mainNode.get_node("Shop")
onready var shopItemYSort = shopSceneNode.get_node("Items")
onready var UINode = mainNode.get_node("UI")
onready var labelsNode = UINode.get_node("Labels")
onready var tooltipsNode = UINode.get_node("Tooltips")
onready var recipeTooltipsNode = UINode.get_node("RecipeTooltips")
onready var speechBubble = shopSceneNode.get_node("SpeechBubble")
onready var playerNode = mainNode.get_node("Player")
onready var playerNodeAnimation = mainNode.get_node("PlayerNodeAnimation")
onready var goldPos = shopSceneNode.get_node("GoldPos")
onready var connectingLabel = UINode.get_node("ConnectingLabel")
onready var startCombatButton = shopSceneNode.get_node("StartCombatButton")
onready var startCombatButtonAni = startCombatButton.get_node("AnimationPlayer")
onready var shopKeeper = shopSceneNode.get_node("ShopKeeper")
onready var combatLog = UINode.get_node("CombatLog/CombatLog")
onready var titleScreen = mainNode.get_node("TitleScreen")
onready var rerollRope = shopSceneNode.get_node("Reroll/RerollRope")
onready var itemLibraryTutorialAni = shopSceneNode.get_node("%ItemLibraryTutorial")
onready var undoStack = UINode.get_node("UndoStack")

var state = State.Title
var continueState = ContinueState.NotContinued
var activePauseSources = PauseSource.Unpaused
var gameSpeedBeforePause = 1.0
var PLAYER
var OPPONENT
var SELLBOX
var STORAGEBOX
var TRAILER = false
var DEVCHEATS = false
var TOOLTIPS = true
var SELECTING = false
var WRITE_OUT_STATE = false
var processTimer: Timer
var recipeBook
var itemLibrary
var otherModesUI = null
var lobbyScoreboard
var selectionBox
var wardrobe
var options
var warning = null
var versionButton
var patchNotes
var gridStorage

var locales = {"English": "en"}
var localeToLanguage: Dictionary
var steamAvailable = false
var leagueIcons = []


var curRound: int = 1
var wins: int
var losses: int
var tries: int
var triesBeforeFight: int
var survivalMode: bool
var justStartedSurvivalMode: bool
var gold: int
var gold_internal: int
var interactable: bool
var left_click = false
var draggedItem = null
var hoveredItems = []
var itemsAreFusing: bool
var craftingPriorities: = {}
var sortedCraftingPriorities: Array
var fightEnded: bool = true
var runStarted: bool
var curClass = Classes.Ranger
var curMode = Mode.Unselected
var roundResults = []
var persistent: Dictionary
var arenaRunState: Dictionary
var lobbyRunState: Dictionary
var chibiMode: Array
var curLoadout: = 1
var randomCharacter: = false

var runWasJustContinued = false
var runWasConceded = false
var lastRunMode: int = - 1
var lastRunConcedeRound: int = - 1
var bagPityCounter: int
var lastItemDropTime = 0.0
var numTimesOutOfStamina: int
var runsStartedThisSession: int
var roundsStartedThisSession: int
var canSwitchToCombat = false
var canCancelSwitch = false
var leaveLobbyPending: = false
var powerPreRun: float
var leaguePreRun: int
var leagueProgressPreRun: float
var trophiesPreRun: int
var rankingPreRun: int
var leagueExactPreRun: float
var wasRankedSwitchMode: bool
var endRunFrame: = - 1
var startedCombatWithoutGold = 0
var randnum: int
var draggingFinger = - 1
var itemsUnderMouse: = []
var replacementPending: = false
var showHintsIsPressed: = false
var itemsBeingCrafted = []

var lockedTooltipItem = null
var showHintsTimeStamp: int = - 1
var affectedLines = []

var stealLifeDamageSource: DamageSource
var unhealingDamageSource: DamageSource
var fatigueDamageSource: DamageSource
var ropeSpeedups: Dictionary
var cubeAdvanced: Dictionary
var sandbagActive: = false
var curOpponentData: Dictionary
var loadoutTween: SceneTreeTween
var characterTween: SceneTreeTween

var winNextRun = false
var loseNextRun = false
var winNextRound = false
var loseNextRound = false

var classResources: Array

const classIcons = [
	preload("res://Assets/TitleScreen/RangerIcon.png"), 
	preload("res://Assets/TitleScreen/ReaperIcon.png"), 
	preload("res://Assets/TitleScreen/BerserkerIcon.png"), 
	preload("res://Assets/TitleScreen/PyromancerIcon.png"), 
	preload("res://Assets/TitleScreen/MageIcon.png"), 
	preload("res://Assets/TitleScreen/AdventurerIcon.png"), 
	preload("res://Assets/TitleScreen/EngineerIcon.png")
]

const classNameBanners = [
	preload("res://Interface/Combat/NameBanner_Ranger.png"), 
	preload("res://Interface/Combat/NameBanner_Reaper.png"), 
	preload("res://Interface/Combat/NameBanner_Berserker.png"), 
	preload("res://Interface/Combat/NameBanner_Pyromancer.png"), 
	preload("res://Interface/Combat/NameBanner_Mage.png"), 
	preload("res://Interface/Combat/NameBanner_Adventurer.png"), 
	preload("res://Interface/Combat/NameBanner_Engineer.png")
]

const neutralClassIcon = preload("res://Assets/TitleScreen/NeutralIcon.png")
const randomClassIcon = preload("res://Interface/DiceIcon.png")
const transitionSounds = [
	preload("res://Assets/Sound/TurningPage1.wav"), 
	preload("res://Assets/Sound/TurningPage2.wav"), 
	preload("res://Assets/Sound/TurningPage3.wav")]

const winSound = preload("res://Assets/Sound/Win.ogg")
const loseSound = preload("res://Assets/Sound/Lose.ogg")

const rainbowRevealParticles = preload("res://Shader/RainbowRevealParticles.tscn")
const affectsLineScene = preload("res://Items/Exclusive/Animations/AffectsLine.tscn")

const rankSeason2Popup = preload("res://Interface/RankSeasonPopup.tscn")
const rankSeason3Popup = preload("res://Interface/RankSeason3Popup.tscn")
const electricalChargeScene = preload("res://Items/ElectricalCharge.tscn")
const notCraftingAnimation = preload("res://Items/Exclusive/Animations/NotCraftingAnimation.tscn")

enum EventType{
	Activation, 
	DealDamage, 
	CriticalDamage, 
	MissedAttack, 
	TakeDamage, 
	LoseHealth, 
	AttackSpeed, 
	InvulnerableStart, 
	InvulnerableEnd
	Stun, 
	StunResisted, 
	CriticalResisted, 
	Health, 
	Stamina, 
	DrainStamina, 
	OutofStamina, 
	DamageBuff, 
	DamReduction, 
	DamIncrease, 
	TemporaryMaxHealth, 
	TemporaryMaxStamina, 
	BattleRageStart, 
	BattleRageEnd, 
	Reincarnate, 
	CooldownAdvance, 
	Unhealing = 98, 
	Fatigue = 99, 
	Block = 100, 
	Lucky = 101, 
	Regeneration = 102, 
	Vampirism = 103, 
	Spikes = 104, 
	Mana = 105, 
	Empower = 106, 
	Heat = 107, 
	
	Poison = 108, 
	Blind = 109, 
	
	Cold = 110, 
	Win = 111, 
	Loss
}

var numStackTypes = getStacks().size()

enum ItemMetrics{
	Damage, 
	Heal, 
	Overheal, 
	Misses, 
	Activations, 
	DamageBlocked, 
	MaxHealth, 
	OutOfStamina, 
	
	Stamina, 
	
	Block, 
	Lucky, 
	Regeneration, 
	Vampirism, 
	Spikes, 
	Mana, 
	Empower, 
	Heat, 
	Poison, 
	Blind, 
	Cold
}
onready var eventTypeKeys = Util.invertDictionary(EventType)

const stackIdentifiers = {
	"spikes": EventType.Spikes, 
	"vampirism": EventType.Vampirism, 
	"poison": EventType.Poison, 
	"regen": EventType.Regeneration, 
	"bl": EventType.Block, 
	"lucky": EventType.Lucky, 
	"blind": EventType.Blind, 
	"mana": EventType.Mana, 
	"heat": EventType.Heat, 
	"cold": EventType.Cold, 
	"empower": EventType.Empower, 
}

enum ItemStatistic{
	SeenInShop = 0, 
	Acquired = 1, 
	BoughtOnSale = 2, 
	Survivals = 3, 
	MostWins = 4, 
	BestRankSurvival = 5
}

enum ItemRecordStar{
	Bronze, 
	Silver, 
	Gold, 
	Diamond
}

enum SaleMode{
	Roll, 
	Sale, 
	NoSale, 
	Free
}

enum InventoryEditMode{
	Default, 
	BagLayer, 
	ItemLayer
}

enum Cursor{
	HARDWARE_SMALL = 0, 
	HARDWARE_LARGE = 1, 
	SOFTWARE_SMALL = 2, 
	SOFTWARE_LARGE = 3, 
	DEFAULT = 4
}

enum CursorTypes{
	
	DEFAULT = 0, 
	CLICKED = 1, 
	GRABBABLE = 2, 
	GRABBED = 3, 
	CLICKABLE = 4, 
	CLICKABLE_CLICKED = 5
	VSIZE = 6, 
	VSIZE_CLICKED = 7
	HSIZE = 8, 
	HSIZE_CLICKED = 9
}

const defaultCursorOffset = Vector2(42, 42)

const cursorOffsets = {
	CursorTypes.DEFAULT: defaultCursorOffset, 
	CursorTypes.CLICKED: defaultCursorOffset, 
	CursorTypes.GRABBABLE: defaultCursorOffset, 
	CursorTypes.GRABBED: defaultCursorOffset, 
	CursorTypes.CLICKABLE: Vector2(45, 25), 
	CursorTypes.CLICKABLE_CLICKED: Vector2(45, 25), 
	CursorTypes.VSIZE: defaultCursorOffset, 
	CursorTypes.VSIZE_CLICKED: defaultCursorOffset, 
	CursorTypes.HSIZE: defaultCursorOffset, 
	CursorTypes.HSIZE_CLICKED: defaultCursorOffset
}

var cursor = Cursor.HARDWARE_SMALL
var softwareCursor = null
const softwareCursorScene = preload("res://Interface/Cursor.tscn")
var lastCursorType = CursorTypes.DEFAULT

var cursors = [
	preload("res://Assets/Cursor/Cursor_default.png"), 
	preload("res://Assets/Cursor/Cursor_default_clicked.png"), 
	preload("res://Assets/Cursor/Cursor_grabbable.png"), 
	preload("res://Assets/Cursor/Cursor_grabbed.png"), 
	preload("res://Assets/Cursor/Cursor_interactable.png"), 
	preload("res://Assets/Cursor/Cursor_interactable_clicked.png"), 
	preload("res://Assets/Cursor/ResizeArrow.png"), 
	preload("res://Assets/Cursor/ResizeArrow_active.png"), 
	preload("res://Assets/Cursor/HSizeArrow.png"), 
	preload("res://Assets/Cursor/HSizeArrow_active.png")
	]

var damageNumberFormats = {
	EventType.DealDamage: "[center]{amount}", 
	EventType.Health: "[center]+{amount}", 
	EventType.CriticalDamage: "[center][shake rate=20 level=50]{amount}[/shake]", 
	EventType.Poison: "[center]{amount}", 
	EventType.Spikes: "[center]{amount}", 
	EventType.Fatigue: "[center]{amount}", 
	EventType.Unhealing: "[center]{amount}", 
	EventType.LoseHealth: "[center]{amount}"
}

var damageNumberColors = {
	EventType.DealDamage: Color.white, 
	EventType.MissedAttack: Color.white, 
	EventType.Health: Color(0.22, 0.93, 0.22, 1), 
	EventType.CriticalDamage: Color(1, 0.1, 0.1, 1), 
	EventType.Poison: Color(0.507813, 1, 0.1), 
	EventType.Spikes: Color(0.231075, 0.726563, 0.195831), 
	EventType.Fatigue: Color(0.558566, 0.391388, 0.742188), 
	EventType.Unhealing: Color(0.759822, 0.40863, 0.804688), 
	EventType.LoseHealth: Color(0.884766, 0.470032, 0.470032), 
	EventType.TemporaryMaxHealth: Color(0.601852, 1, 0.474609), 
	EventType.Stamina: Color(1, 0.97805, 0.197266), 
	EventType.TemporaryMaxStamina: Color(1, 0.987717, 0.550781), 
	EventType.DamageBuff: Color.white, 
	EventType.CooldownAdvance: Color.white
}

var scaledCursors: Array = []
var hoverSoundReadyTime: float = 2.5
var hotswapBehaviorModified: bool = false
var focusDisableFrameCounter: int = 60
var tooltipDisableFrameCounter: int = 0
var lastShowItemTooltipFrame: = 0
var lastHideItemTooltipFrame: = 0
var lastTooltipWasBag: = false
var lastBagTooltipWasDelayed: = false
var hoverResponseDisabledFramecounter: int = 0
var reactToHoverEnd: = true
var usingController: bool = false
var activeControllerDevice: int = - 1
var usingTouchscreen: bool = false
var itemListOpened: bool = false
var buildHistoryDB = null
var buildHistory = null
var curHistoryData = null
var slotNames = SkinSlot.keys()
var inventoryEditMode = InventoryEditMode.Default

const statisticIncrements = {
	ItemStatistic.SeenInShop: 500, 
	ItemStatistic.Acquired: 100, 
	ItemStatistic.BoughtOnSale: 50, 
	ItemStatistic.Survivals: 10
}

enum TutorialSteps{
	Reserve = 1, 
	Lock = 2, 
	GoldCarryOver = 4, 
	BagMove = 8, 
	SendToStorage = 16, 
	Undo = 32, 
	ShowRecipes = 64, 
	Selection = 128, 
	Shift = 256, 
	Skill = 512, 
	Subclass = 1024, 
	Stars = 2048, 
	Wins = 4096, 
	Tries = 8192, 
	Rotate = 16384, 
	ShopSign = 32768, 
	ViewCombat = 65536, 
	CombatLog = 131072, 
	ItemLibrary = 262144, 
	CombatLogButtons = 524288, 
	Toolbar = 1048576, 
	HistoryFight = 2097152
}

const tutorialPriorities = [
	TutorialSteps.Reserve, 
	TutorialSteps.GoldCarryOver, 
	TutorialSteps.BagMove, 
	TutorialSteps.SendToStorage, 
	TutorialSteps.ShowRecipes, 
	TutorialSteps.Selection, 
	TutorialSteps.Shift, 
	TutorialSteps.Undo
]

var currentTutorialStep: = - 1
onready var tutorialEncodingToStep = Util.invertDictionary(TutorialSteps)

func versionToInt(ver: String = VERSION) -> int:
	var verAsInt: = 0
	var split = ver.split(".")
	verAsInt += int(split[0]) * 1000000
	verAsInt += int(split[1]) * 1000
	verAsInt += int(split[2])
	return verAsInt

func versionToString(ver: int) -> String:
	var major = ver / 1000000
	var minor = (ver % 1000000) / 1000
	var mini = (ver % 1000)
	return str(major) + "." + str(minor) + "." + str(mini)
	
	
func loadExclusiveContent() -> bool:
	return PLAYTEST or FULLVERSION or EDITOR

func showExclusiveContent() -> bool:
	return PLAYTEST or FULLVERSION or EDITOR

func loadUnreleasedClasses() -> bool:
	return FULLVERSION and (EDITOR or PLAYTEST or ENGINEER_TEST)

func loadUnreleasedContent() -> bool:
	return FULLVERSION and (EDITOR or PLAYTEST or ENGINEER_TEST)

func getClassEnum() -> Dictionary:
	if FULLVERSION:
		return Classes_Full
	else:
		return Classes

func getClassKeys() -> Array:
	return getClassEnum().keys()

func getNumClasses() -> int:
	return getClassEnum().size()

func isInLobby() -> bool:
	return RunDatabase.lobbies.isInLobby()

func getEffectiveMode() -> int:
	if curMode == Mode.History:
		return curHistoryData.mode
	else:
		return curMode

func isRankedSwitchMode() -> bool:
	return CustomRules.isRankedSwitchMode() and curMode == Mode.Unranked

func pause(pauseSource: int):
	if isInLobby(): return
	
	if activePauseSources == PauseSource.Unpaused:
		get_tree().paused = true
		gameSpeedBeforePause = Engine.time_scale
		Engine.time_scale = 1.0
		
		
		Sound.setMuffledSound(true)
		if pauseSource != PauseSource.RecipeBook:
			VisualServer.set_shader_time_scale(0)
		emit_signal("game_paused")
		
	if pauseSource == PauseSource.Ad:
		AudioServer.set_bus_mute(Sound.MASTER_BUS, true)
	
	activePauseSources |= pauseSource

func unpause(pauseSource: int):
	
	if activePauseSources == PauseSource.Unpaused: return
	
	activePauseSources &= ~ pauseSource
	
	if activePauseSources == PauseSource.Unpaused:
		get_tree().paused = false
		VisualServer.set_shader_time_scale(1)
		Engine.time_scale = gameSpeedBeforePause
		
		AudioServer.set_bus_mute(Sound.MASTER_BUS, false)
		
		
		Sound.setMuffledSound(false)
		emit_signal("game_unpaused")

func openMenu():
	cancelSwitch()
	emit_signal("menu_open")

var sceneVisibility: Dictionary

func openedMenu():
	emit_signal("menu_opened")
	for node in [shopSceneNode, titleScreen, combatSceneNode, playerNode]:
		sceneVisibility[node] = node.visible
		
		node.visible = false
		node.connect("visibility_changed", self, "onSceneVisibilityChanged", [node])

func closeMenu(restoreVisibility = true):
	emit_signal("menu_close")
	
	if restoreVisibility:
		for node in sceneVisibility:
			node.visible = sceneVisibility[node]
			
			node.disconnect("visibility_changed", self, "onSceneVisibilityChanged")

func onSceneVisibilityChanged(node):
	sceneVisibility[node] = node.visible

func isMenuOpen() -> bool:
	return (itemLibrary.isOpen or 
			recipeBook.isOpen or 
			options.isOpen or 
			buildHistory.isOpen or 
			patchNotes.visible)

func onItemListClosed():
	itemListOpened = false
	emit_signal("item_list_closed")

func isTouchScreenActive() -> bool:
	return usingTouchscreen



	

func globalPosToScreenPos(pos) -> Vector2:
	var translation: Vector2
	var scaling: Vector2
	var windowAspect = OS.window_size.x / float(OS.window_size.y)
	if windowAspect <= 16 / 9.0:
		
		
		var gameHeight = OS.window_size.x / (16 / 9.0)
		var borderTop = (OS.window_size.y - gameHeight) / 2.0
		translation = Vector2(0, borderTop)
		scaling = Vector2(OS.window_size.x, gameHeight) / Vector2(1920, 1080)
	else:
		
		var gameWidth = OS.window_size.y * (16 / 9.0)
		var borderLeft = (OS.window_size.x - gameWidth) / 2.0
		translation = Vector2(borderLeft, 0)
		scaling = Vector2(gameWidth, OS.window_size.y) / Vector2(1920, 1080)

	pos = pos * scaling + translation
	pos.x = round(pos.x)
	pos.y = round(pos.y)
	return pos

func moveMouse(by: Vector2):
	var curMousePos = globalPosToScreenPos(get_global_mouse_position())
	Input.warp_mouse_position(curMousePos + by)
	

func moveMouseTo(pos: Vector2):
	Input.warp_mouse_position(globalPosToScreenPos(pos))

func unhoverAndHideTooltips():
	
	unlockTooltip()
	unhoverAllItems()
	hideTooltips()
	hideSockets()

func hideTooltips():
	for node in get_tree().get_nodes_in_group("Tooltip"):
		node.hide()

func getMaxNumberOfRounds():
	return MAX_ROUNDS


func getLastRoundResult():
	return roundResults[curRound - 2]

func getTries():
	return tries

func giveTry():
	if tries < MAX_TRIES:
		tries += 1

func isSurvivalMode():
	return survivalMode

func canStartSurvivalMode():
	return ( not isSurvivalMode() and 
			isArenaMode() and 
			wins == MAX_WINS)

func startSurvivalMode():
	survivalMode = true
	justStartedSurvivalMode = true
	giveTry()

func cancelSurviveMode():
	endRun()

func wasPerfectRunBeforeSurvival():
	for i in MAX_WINS:
		if roundResults[i] != RoundResult.Win:
			return false
	return true

func getRoundsToSurvive():
	return MAX_ROUNDS + 1 - curRound

func getTrophies():
	return persistent["trophies"]

func giveTrophies(amount):
	if amount > 0:
		persistent["trophies"] += amount
		emit_signal("trophies_changed")
		
		var trophiesWon = SteamHelper.changeStat("TrophiesWon", amount)
		if trophiesWon > 10000:
			SteamHelper.unlockAchievement("Trophies")


func loseTrophies(amount):
	assert (amount <= persistent["trophies"])
	if amount > 0:
		persistent["trophies"] -= amount
		emit_signal("trophies_changed")

func getGainedGold(forClass, untilRound):
	var _gold = classResources[forClass].gold
	for i in range(1, untilRound + 1):
		_gold += getGoldGain(i)
	return _gold
	

func getGoldGain(inRound):
	var g = goldGain[inRound - 1]
	
	if inRound == SUBCLASS_ROUND:
		g += 10
	
	if SKILLS_ENABLED:
		if inRound == SKILL_ROUND1 or inRound == SKILL_ROUND2:
			g += 5
	
	return g

func getMaxHealthInRound(forClass, untilRound):
	var health = classResources[forClass].health
	for i in range(2, untilRound + 1):
		health += getHealthGain(i)
	
	return health
	
func getHealthGain(inRound):
	var curHealthGain: int
	if inRound >= 15:
		curHealthGain = 30
	elif inRound >= 10:
		curHealthGain = 20
	elif inRound >= 5:
		curHealthGain = 15
	else:
		curHealthGain = 10
	return curHealthGain

func getStartInventoryPrice(forClass, loadout = 0):
	var price = 0
	for item in classResources[forClass].getStartingItems(loadout):
		price += ItemBook.getDescriptor(item.itemName).price
	return price

func getNumWins():
	return wins

func getNumLosses():
	return losses

func getRoundResults():
	var results = []
	for i in range(RoundResult.size()):
		results.append(0)
	
	for result in roundResults:
		results[result] += 1
		
	return results

func getTotalRerolls():
	return persistent["rerolls"]

func saveGame():
	if not gameSaveQueued:
		gameSaveQueued = true
		call_deferred("actuallySaveGame")

func expandPath(format: String, steamID = null, full = false) -> String:
	var params = {
		"ID": "", 
		"build": ""
	}
	if steamID != null:
		params["ID"] = str(steamID) + "/"
	
	if PLAYTEST:
		params["build"] = "playtest/"
	elif full:
		params["build"] = "full/"
	
	if BETA:
		params["build"] += "beta/"
		
	
	var path = format.format(params)
	return path

func makeBaseDir():
	var dir: Directory = Directory.new()
	var err = dir.make_dir_recursive(getSavePath(baseDir_format))
	
	err = dir.make_dir(getSavePath(backup_format))
	
	
	var sharedDirPath = expandPath(baseDir_format)
	dir.make_dir(sharedDirPath)
	
	if SteamHelper.is_init() and SteamHelper.isIDValid():
		var oldConfigPath = expandPath(config_format)
		var newConfigPath = expandPath(config_format, SteamHelper.STEAM_ID)
		
		if FULLVERSION:
			var fullConfigPath = expandPath(config_format, SteamHelper.STEAM_ID, true)
			if not dir.file_exists(fullConfigPath):
				if dir.file_exists(newConfigPath):
					dir.copy(newConfigPath, fullConfigPath)
				elif dir.file_exists(oldConfigPath):
					dir.copy(oldConfigPath, fullConfigPath)
		else:
		
			if not dir.file_exists(newConfigPath) and dir.file_exists(oldConfigPath):
				dir.copy(oldConfigPath, newConfigPath)



func getLoadPath(format: String, isFile: bool = true) -> String:
	if SteamHelper.is_init() and SteamHelper.isIDValid():
		var dir: Directory = Directory.new()
		
		if FULLVERSION:
			var fullPath = expandPath(format, SteamHelper.STEAM_ID, true)
			if isFile:
				if dir.file_exists(fullPath):
					return fullPath
			else:
				if dir.dir_exists(fullPath):
					return fullPath
		
		var newPath = expandPath(format, SteamHelper.STEAM_ID)
		if isFile:
			if dir.file_exists(newPath):
				return newPath
		else:
			if dir.dir_exists(newPath):
				return newPath
	
	var oldPath = expandPath(format, null)
	return oldPath

func getSavePath(format: String) -> String:
	if SteamHelper.is_init() and SteamHelper.isIDValid():
		var newPath = expandPath(format, SteamHelper.STEAM_ID, FULLVERSION)
		return newPath
	else:
		var oldPath = expandPath(format, null, FULLVERSION)
		return oldPath

func actuallySaveGame():
	
	gameSaveQueued = false
	persistent["version"] = VERSION
	
	var savePath = getSavePath(savefile_format)
	
	var dir: Directory = Directory.new()
	if dir.file_exists(savePath):
		var backupNumbers = findBackups(false)
		var index = 1
		if not backupNumbers.empty():
			index = backupNumbers[0] + 1
		
		var backupFilePath = createBackupFilePath(index)
		dir.rename(savePath, backupFilePath)
	
		
		var numExisting = backupNumbers.size()
		var filesToDelete = numExisting - 5
		for i in filesToDelete:
			dir.remove(createBackupFilePath(backupNumbers[numExisting - 1 - i]))
			
	
	persistent.erase("cs")
	var dictHash = Util.hashDictionary(persistent)
	
	persistent["cs"] = dictHash
	
	Util.writeVarToFile(savePath, persistent)
	
	if SteamHelper.is_init():
		var offlinePath = getSavePath(offlinesave_format)
		dir.copy(savePath, offlinePath)

func findBackups(isLoad: bool):
	var numbers = []
	
	var dir: Directory = Directory.new()
	var backupDir: String
	if isLoad:
		backupDir = getLoadPath(backup_format, false)
	else:
		backupDir = getSavePath(backup_format)
		
	if dir.open(backupDir) == OK:
		var files = []
		var directories = []
		dir.list_dir_begin(true, true)
		Util.addDirectoryContents(dir, files, directories)
		for file in files:
			var fileName = file.get_file()
			var number = int(fileName)
			
			numbers.push_back(number)
		
		numbers.sort()
		numbers.invert()
		
	return numbers

func createBackupFilePath(number):
	var backupPath = getSavePath(backup_format)
	return backupPath.plus_file("backup_" + String(number) + ".save")

func createBackupFilePaths(backupNumbers):
	var backupFileNames = []
	
	for number in backupNumbers:
		
		var fileName = createBackupFilePath(number)
		backupFileNames.push_back(fileName)
	return backupFileNames

func loadGame():
	
	var defaultFileData = getFileContent(getLoadPath(savefile_format))
	if typeof(defaultFileData) == TYPE_DICTIONARY:
		persistent = defaultFileData
	else:
		var backupFiles = createBackupFilePaths(findBackups(true))
		for backupFileName in backupFiles:
			var fileData = getFileContent(backupFileName)
			if typeof(fileData) == TYPE_DICTIONARY:
				print("Successfully loaded from backup: ", backupFileName.get_file())
				persistent = fileData
				break
	
	if SteamHelper.is_init() and persistent.empty():
		var offlineFileData = getFileContent(getLoadPath(offlinesave_format))
		if typeof(offlineFileData) == TYPE_DICTIONARY:
			persistent = offlineFileData
			print("load from offline")
	
	if not persistent.empty() and persistent["version"] == VERSION:
		var cs = persistent["cs"]
		persistent.erase("cs")
		var new_cs = Util.hashDictionary(persistent)
		if cs != new_cs:
			persistent.clear()
			initPlayer()
	
	initPlayer()
	
	if steamAvailable:
		if persistent["id"] == 0:
			persistent["id"] = SteamHelper.STEAM_ID
		elif persistent["id"] != SteamHelper.STEAM_ID:
			persistent.clear()
			initPlayer()
			
	
	if not isWeb:
		calcTempPath()
	
	
	if ("version" in persistent and 
		versionToInt(persistent["version"]) < versionToInt("1.1.0") and 
		hasPlayedInSeason("2")):
		for classI in 6:
			var rating = getRunRating(classI, "2")
			var leagueExact = getLeague_exact(rating)
			var newLeagueExact = max((leagueExact - 0.5) * 0.9, 0.0)
			setRating(getRatingFromLeague(newLeagueExact), classI)

func getFileContent(path):
	var file = File.new()
	if file.file_exists(path):
		var err = file.open(path, File.READ)
		if err == OK:
			if file.get_len() > 10:
				var data = file.get_var()
				if typeof(data) == TYPE_DICTIONARY:
					return data
				else:
					print("Failed loading file from ", path.get_file())
			file.close()
		else:
			print("Failed loading file from ", path.get_file(), " with error ", err)
	
	return - 1

func setPatchNoteVersion(version):
	persistent["patchNotesVersion"] = version

func getPatchNoteVersion():
	return persistent["patchNotesVersion"]

var gameSaveQueued = false
var runSaveQueued = false
var tempName: String
var tempPath: String
var tempPath_lobbies: String
var loadTemp: bool

var canCommitRun = true

func calcTempPath():
	if OS.has_feature("Windows"):
		tempPath = OS.get_environment("temp")
		
		if OS.get_environment("STEAM_COMPAT_DATA_PATH") != "":
			canCommitRun = false
			print("(1) Proton ", OS.get_environment("STEAM_COMPAT_DATA_PATH"))
		elif OS.get_environment("TMPDIR") != "":
			canCommitRun = false
			print("(2) Proton ", OS.get_environment("TMPDIR"))
		
		if EXPO: canCommitRun = false

	
	
	
	
	
	
	if tempPath != "":
		loadTemp = true
		
		tempName = persistent["identifier"]
		if FULLVERSION:
			tempName += "full"
		if PLAYTEST:
			tempName += "playtest"
		elif BETA:
			tempName += "beta"
		var tempName_lobbies = (tempName + "t").md5_text().left(32)
		tempName = tempName.md5_text().left(32)
		var j = 0
		for i in [8, 12, 16, 20]:
			tempName = tempName.insert(i + j, "-")
			tempName_lobbies = tempName_lobbies.insert(i + j, "-")
			j += 1
		
		tempPath_lobbies = tempPath + "\\" + tempName_lobbies + ".tmp"
		tempPath += "\\" + tempName + ".tmp"

func getRunStateTmpPath(mode: int = curMode):
	if mode == Mode.Lobbies:
		return tempPath_lobbies
	else:
		return tempPath

func getRunStateFormat(mode: int = curMode):
	if mode == Mode.Lobbies:
		return lobby_runstate_format
	else:
		return runstate_format

func getRunState(mode: int = curMode):
	if mode == Mode.Lobbies:
		return lobbyRunState
	else:
		return arenaRunState

func setRunState(runState, mode: int = curMode):
	if mode == Mode.Lobbies:
		lobbyRunState = runState
	else:
		arenaRunState = runState

func saveRunState():
	Util.eassert(curMode != Mode.History)
	if not runSaveQueued:
		call_deferred("actuallySaveRunState")
		runSaveQueued = true

func actuallySaveRunState():
	runSaveQueued = false
	runWasJustContinued = false
	
	var runState = getRunState()
	if not "version" in runState:
		
		runState["version"] = VERSION
		runState["class"] = curClass
		runState["loadout"] = curLoadout
		runState["randomClass"] = randomCharacter
		runState["mode"] = curMode
		runState["id"] = getNumStartedRuns()
		
		if CustomRules.areCustomRulesActive() and curMode != Mode.Lobbies:
			runState["custom"] = CustomRules.serialize()
	
	runState["results"] = roundResults.duplicate()
	runState["round"] = curRound
	runState["wins"] = wins
	runState["losses"] = losses
	runState["tries"] = tries
	runState["bagcounter"] = bagPityCounter
	runState["rerolls"] = shopSceneNode.rerollsThisRound
	runState["gold"] = getGold()
	runState["maxHealth"] = PLAYER.getBaseMaxHealth()
	runState["maxStamina"] = PLAYER.getBaseMaxStamina()
	runState["priorRounds"] = RunDatabase.rounds.duplicate()
	runState["survival"] = isSurvivalMode()
	
	if not BETA:
		SteamHelper.incrementSequenceNumber(curMode)
		runState["sqn"] = SteamHelper.getSequenceNum(curMode)
	else:
		runState["sqn"] = 0

	var inventoryState = []
	var inventory
	
	if CustomRules.isSwitchMode() and not curOpponentData.empty():
		inventory = OPPONENT.INVENTORY
	else:
		inventory = PLAYER.INVENTORY
	
	var itemArr: Array = inventory.getItems()
	
	var floatingItems: = []
	
	for item in itemArr:
		if inventory.isItemFloating(item):
			floatingItems.push_back(item)
			continue
		
		var itemData = []
		itemData.push_back(ItemBook.getItemIndex(item))
		itemData.push_back(item.getTopLeftCell())
		itemData.push_back(item.getFaceDirection())
		itemData.push_back(item.getData())
		itemData.push_back(item.isLocked())
		if item.hasGems():
			itemData.push_back(item.getGemData())
		
		inventoryState.push_back(itemData)
		
	runState["inventory"] = inventoryState
	
	
	var storageState = []
	
	if CustomRules.isSwitchMode() and not curOpponentData.empty():
		pass
		
		
	else:
		var storageItems = STORAGEBOX.getItems().duplicate()
		
		if draggedItem != null:
			storageItems.push_back(draggedItem)
		
		for item in storageItems + floatingItems:
			var itemData = []
			itemData.push_back(ItemBook.getItemIndex(item))
			itemData.push_back(item.get_global_transform())
			itemData.push_back(item.getData())
			itemData.push_back(item.isLocked())
			if item.hasGems():
				itemData.push_back(item.getGemData())
			
			storageState.push_back(itemData)
	
	runState["storage"] = storageState
	
	var shopItems = []
	var shopItemData = {}
	var slotI = 0
	for item in shopSceneNode.getItems():
		if item != null:
			shopItems.push_back(ItemBook.getItemIndex(item))
			if item.persistDataInShop():
				var persistentData = item.getData()
				if persistentData != null:
					shopItemData[slotI] = persistentData
			
		else:
			
			shopItems.push_back(null)
		slotI += 1
	
	runState["shop"] = shopItems
	
	if not shopItemData.empty():
		runState["shopdata"] = shopItemData
	else:
		runState.erase("shopdata")
	
	runState["reserved"] = shopSceneNode.getReservedSlots()
	runState["sales"] = shopSceneNode.getSaleSlots()
	
	runState["stashedReserved"] = shopSceneNode.getStashedReservedItems()
	runState["stashedSales"] = shopSceneNode.getStashedSales()
	runState["stashedData"] = shopSceneNode.getStashedItemData()
	
	if SELLBOX.tradeNode.isTradeActive():
		runState["tradeWant"] = SELLBOX.tradeNode.wantItem.descriptor.itemIndex
		runState["tradeGive"] = SELLBOX.tradeNode.giveItem.descriptor.itemIndex
		var tradeData = SELLBOX.tradeNode.getTradeGiveData()
		if tradeData != null:
			runState["tradeGiveData"] = tradeData
	else:
		runState.erase("tradeWant")
		runState.erase("tradeGive")
		runState.erase("tradeGiveData")
	
	
	if curMode == Mode.Lobbies:
		
		runState["hostId"] = RunDatabase.lobbies.getHostId()
		
		
		runState["ugcId"] = RunDatabase.lobbies.getHostUgcId()
		runState["lobbyId"] = RunDatabase.lobbies.getLobbyId()
	
	runState.erase("cs")
	runState["cs"] = Util.hashDictionary(runState)
	
	Util.writeVarToFile(getSavePath(getRunStateFormat()), runState)
	
	if loadTemp:
		Util.writeVarToFile(getRunStateTmpPath(curMode), runState)
	
	runState.erase("cs")
	
	Util.eprint("runstate saved")









func wasRunContinued() -> bool:
	return continueState != ContinueState.NotContinued

func deleteRunStateAndRules(mode: int = curMode):
	CustomRules.reset()
	deleteRunState(mode)

func deleteRunState(mode: int = curMode):
	var runState = getRunState(mode)
	runState.clear()
	var dir = Directory.new()
	dir.remove(getLoadPath(getRunStateFormat(mode)))
	if loadTemp:
		dir.remove(getRunStateTmpPath(mode))




	Util.eprint("runstate deleted")

enum RunStateLoadResult{
	LoadedRun, 
	NoRun, 
	FileCorrupt
}

func loadRunStateFromPath(path, mode) -> bool:
	var res = RunStateLoadResult.FileCorrupt
	var save_game = File.new()
	
	if mode == Mode.Lobbies:
		var time = save_game.get_modified_time(path)
		var dif = OS.get_unix_time() - time
		Util.eprint("file time dif: ", dif)
		if dif > 60 * LOBBY_TIMEOUT_MINUTES or dif < 0:
			print("Lobby state timeout ", dif)
			return RunStateLoadResult.NoRun
	
	var err = save_game.open(path, File.READ)
	if err == OK:
		
		if save_game.get_len() > 3:
			var saveData = save_game.get_var()
			if typeof(saveData) == TYPE_DICTIONARY:
				setRunState(saveData, mode)
				res = RunStateLoadResult.LoadedRun
			else:
				print("Runstate loading error!")
		else:
			res = RunStateLoadResult.NoRun
		save_game.close()
	else:
		print("Runstate loading error: ", err)
	return res

func validateRun(mode: int) -> bool:
	var runState = getRunState(mode)
	
	
	var version = runState["version"]
	if not Util.laterOrEqual(version, runStateBreakingVersion):
		deleteRunState(mode)
		return false
	
	
	var cs = runState["cs"]
	runState.erase("cs")
	if cs != Util.hashDictionary(runState):
		print("Could not load run. 1")
		deleteRunState(mode)
		return false
	
	
	if not BETA:
		var sqn = runState["sqn"]
		if typeof(sqn) != TYPE_INT or sqn != SteamHelper.getSequenceNum(mode):
			if SteamHelper.getSequenceNum(mode) == 0:
				print("SQN 0")
			else:
				Util.eprint("load sequence num: ", sqn, " != ", SteamHelper.getSequenceNum(mode))
				print("Could not load run. 2")
				runState.clear()
				return false
	
	return true

var runStateFields = [
	"version", "class", "mode", "results", "round", "wins", "losses", "tries", 
	"bagcounter", "rerolls", "gold", "maxHealth", "maxStamina", "priorRounds", 
	"survival", "sqn", "inventory", "storage", "shop", "reserved", "sales", 
	"stashedReserved", "stashedSales", "incombat"]

func loadRunState(mode: int, instanceRunState: bool = true) -> bool:
	var loadedRun = false
	
	var save_game = File.new()
	var path = getRunStateTmpPath(mode)
	
	
	
	if loadTemp and save_game.file_exists(path):
		var res = loadRunStateFromPath(path, mode)
		if res == RunStateLoadResult.LoadedRun:
			
			loadedRun = validateRun(mode)
			
		
	if not loadedRun:
		path = getLoadPath(getRunStateFormat(mode))
		
		if save_game.file_exists(path):
			var res = loadRunStateFromPath(path, mode)
			if res == RunStateLoadResult.LoadedRun:
				loadedRun = validateRun(mode)
				
	
	
	if loadedRun:
		var runState = getRunState(mode)
		
		for key in runStateFields:
			if not key in runState:
				runState.clear()
				return false
		
		if runState["gold"] < 0:
			runState.clear()
			return false
			
		var selectedClass = runState["class"]
		if not isClassUnlocked(selectedClass):
			runState.clear()
			return false
		
		if not checkItemsValid(runState["inventory"]):
			runState.clear()
			return false
		
		if instanceRunState:
			initPlayerFromRunstate(mode)
		
			
			if runState["incombat"]:
				print("incombat runstate")
				runState["results"][runState["round"] - 1] = RoundResult.Loss
				runState["round"] += 1
				runState["tries"] -= 1
				runState["losses"] += 1
			
			readRoundResultsFromRunState(mode)
			
			
			if runOver():
				if mode == Mode.Lobbies:
					endRun_lobby()
				else:
					endRun(false, false)
				return false
	
	return loadedRun

func checkItemsValid(items: Array) -> bool:
	for itemData in items:
		for i in 3:
			if Util.getArrayElement(itemData, i, null) == null:
				print("Runstate loading error.")
				return false
	return true

func isArenaMode(mode = curMode) -> bool:
	return mode == Mode.Unranked or mode == Mode.Ranked

func hasArenaRunState() -> bool:
	return not arenaRunState.empty()

func suspendRunState(instanceLoadout = true):
	if hasArenaRunState():
		instanceCharacter(getSelectedClass())
		if instanceLoadout:
			setLoadout(getConfiguredLoadout())
		CustomRules.reset()
		emit_signal("runstate_suspended")

func restoreCustomRules(runState):
	var customRules = runState.get("custom", null)
	if customRules != null:
		CustomRules.fromString(customRules)

func deleteDraggedItem():
	if draggedItem != null:
		print("DELETE")
		hoveredItems.erase(draggedItem)
		draggedItem.discard()
		itemDropped(draggedItem, Item.DropResult.Failed)
		
		
		InputBlocker.restoreAllControls(InputBlocker.Source.ItemDragging)

func initPlayerFromRunstate(mode: int = curMode):
	var runState = getRunState(mode)
	if runState.empty():
		CustomRules.reset()
		return
	
	deleteDraggedItem()
	instanceCharacter(runState["class"])
	curLoadout = runState["loadout"]
	randomCharacter = runState.get("randomClass", false)
	restoreCustomRules(runState)
	setGold(runState["gold"])
	PLAYER.setMaxHealth(runState["maxHealth"])
	PLAYER.setMaxStamina(runState["maxStamina"])
	
	PLAYER.INVENTORY.reset()
	var inventoryState = runState["inventory"]
	for itemData in inventoryState:
		var itemId = itemData[0]
		var descriptor = ItemBook.getDescriptorFromIndex(itemId)
		if not descriptor.scene:
			runState.clear()
			return false
		var item = ItemBook.instantiateItem(descriptor)
		var topLeftCellPos = itemData[1]
		var faceDirection = itemData[2]
		PLAYER.INVENTORY.orientAndAddItem(item, topLeftCellPos, faceDirection)
		item.setData(itemData[3])
		var locked = itemData[4]
		if locked == null: locked = false
		item.setLocked(locked, false)
		if itemData.size() >= 6:
			item.setGemData(itemData[5])
	
	emit_signal("runstate_loaded")

func readRoundResultsFromRunState(mode: int):
	var runState = getRunState(mode)
	setMode(runState["mode"])
	curRound = runState["round"]
	wins = runState["wins"]
	losses = runState["losses"]
	tries = runState["tries"]
	survivalMode = runState["survival"]
	roundResults = runState["results"].duplicate()


func continueLastRun(mode):
	setMode(mode)
	var runState = getRunState(curMode)
	
	if curClass != runState["class"]:
		print("Class mismatch ", curClass, " ", runState["class"])
		get_tree().quit()
	
	startRun()
	
	
	if runState["incombat"]:
		continueState = ContinueState.FromCombat
	else:
		continueState = ContinueState.FromShop
	runWasJustContinued = true
	
	readRoundResultsFromRunState(curMode)
	
	bagPityCounter = runState["bagcounter"]
	
	STORAGEBOX.deleteItems()
	var storageState = runState["storage"]
	for itemData in storageState:
		var index = itemData[0]
		var item = ItemBook.instantiateItemFromIndex(index)
		STORAGEBOX.add_child(item)
		item.global_transform = itemData[1]
		item.global_position.x += shopSceneNode.global_position.x
		item.global_position = Util.clampToRect(item.global_position, STORAGEBOX.getStorageRect())
		item.addToStorageBox(false, false, false)
		item.setData(itemData[2])
		item.setLocked(itemData[3], false)
		if itemData.size() >= 5:
			item.setGemData(itemData[4])
	
	RunDatabase.rounds = runState["priorRounds"].duplicate()
	
	if runState["incombat"]:
		emit_signal("round_result")
	else:
		shopSceneNode.setStashedReservedItems(runState["stashedReserved"])
		shopSceneNode.setStashedSales(runState["stashedSales"])
		shopSceneNode.setStashedItemData(runState.get("stashedData", null))
		
		var shopItems = runState["shop"]
		for i in shopItems.size():
			if shopItems[i] != null:
				var item = ItemBook.instantiateItemFromIndex(shopItems[i])
				shopSceneNode.setItem(i, item)
			else:
				shopSceneNode.setBought(i)
		
		var reservedSlots = runState["reserved"]
		for i in reservedSlots.size():
			shopSceneNode.setReserved(i, reservedSlots[i])
		
		var onSaleSlots = runState["sales"]
		for i in onSaleSlots.size():
			shopSceneNode.setOnSale(i, onSaleSlots[i])
		
		var shopItemData = runState.get("shopdata", {})
		for slotI in shopItemData:
			shopSceneNode.slots[slotI].item.setData(shopItemData[slotI])
		
		if runState.has("tradeWant"):
			SELLBOX.tradeNode.setTrade(runState["tradeWant"], 
				runState["tradeGive"], runState.get("tradeGiveData", null))


func concedeLastRun():
	if Engine.get_physics_frames() == endRunFrame:
		Util.eassert(false)
		print("Duplicate end run (concede)")
		return
	
	readRoundResultsFromRunState(Mode.Unselected)
	losses = MAX_TRIES
	tries = 0
	runWasConceded = true
	endRun(false, false)
	curRound = 1
	setMode(Mode.Unselected)
	instanceCharacter(getSelectedClass())
	if LOADOUTS_ENABLED:
		setLoadout(getConfiguredLoadout())
	else:
		setLoadout(0)
		
func setMode(newMode):
	curMode = newMode

func initPlayer():
	
	defaultPersistentVar("name", "")
	defaultPersistentVar("identifier", Util.generateRandomString(16))
	
	if FULLVERSION:
		var varName = "rating" + getSeason()
		defaultPersistentVar(varName, {})
		for classI in getNumClasses():
			if not classI in persistent[varName]:
				persistent[varName][classI] = 0.0
	else:
		var ratings = []
		for classI in getNumClasses():
			ratings.push_back(0.0)
		defaultPersistentVar("rating", ratings)
	
	if ITEM_STATISTICS_ENABLED:
		for statistic in ItemStatistic.values():
			var key = getStatisticsKey(statistic)
			var arr = []
			arr.resize(ItemBook.getNumItems())
			defaultPersistentVar(key, arr)
			
	
	defaultPersistentVar("totalWins", 0)
	defaultPersistentVar("trophies", 0)
	defaultPersistentVar("runWins", 0)
	defaultPersistentVar("rerolls", 0)
	defaultPersistentVar("runsStarted", 0)
	defaultPersistentVar("runsFinished", 0)
	defaultPersistentVar("lastRandomClass", - 1)
	defaultPersistentVar("crafted", 0)
	defaultPersistentVar("craftedRecipes", {})
	defaultPersistentVar("selectedClass", Classes.Ranger)
	defaultPersistentVar("unlockedSkins", {})
	defaultPersistentVar("rotations", 0)
	
	
	
	
	defaultPersistentVar("tutorial", 0)
	defaultPersistentVar("smr", 0.0)
	
	defaultPersistentVar("id", 0)
	defaultPersistentVar("patchNotesVersion", "0.1.0")

func defaultPersistentVar(varName, defaultVal):
	
	
	if defaultVal is Array and varName in persistent:
		var existingArray = persistent[varName]
		for index in existingArray.size():
			defaultVal[index] = existingArray[index]
		
		persistent[varName] = defaultVal
	else:
		persistent[varName] = persistent.get(varName, defaultVal)

func limitName(_name: String) -> String:
	return _name.left(MAX_NAME_LEN)

func setPlayerName(_name: String):
	persistent["name"] = _name

func getPlayerName() -> String:
	if persistent["name"] == "":
		if steamAvailable:
			return limitName(SteamHelper.STEAM_NAME)
		else:
			return Util.tra("PLAYER_UNNAMED")
	return limitName(persistent["name"])

func getSavestateVersion():
	return persistent.get("version", null)

func getNumStartedRuns():
	return persistent["runsStarted"]

func getRunWins():
	return persistent["runWins"]

func getPlayerIdentifier():
	return persistent["identifier"]


func getClassInternalName(charClass = curClass) -> String:
	return getClassKeys()[charClass]


func getSubclass():
	var runState = getRunState(curMode)
	
	if "inventory" in runState:
		var indices = []
		for item in runState["inventory"]:
			indices.push_back(item[0])
		for item in runState["storage"]:
			indices.push_back(item[0])
		
		return ItemBook.getSubclassFromIndices(indices)
	else:
		return ItemBook.getPlayerSubclass()


func getClassOrSubclass() -> String:
	var className = getSubclass()
	if className == "":
		className = getClassInternalName()
	return className

func getClassOrSubclassTranslationKey() -> String:
	var subclass = getSubclass()
	if subclass != "":
		return "SUBCLASS_" + subclass + "_NAME"
	else:
		return getClassTranslationKey()

func getClassTranslationKey() -> String:
	return getClassInternalName() + "_NAME"


func getClassName(charClass = curClass) -> String:
	if isClassUnlocked(charClass):
		return Util.tra(getClassInternalName(charClass) + "_NAME")
	else:
		return Util.tra("LOCKED_CLASS")


func getTranslatedSubclassName(subclassName) -> String:
	return Util.tra("SUBCLASS_" + subclassName + "_NAME")

func isClassUnlocked(charClass = curClass) -> bool:
	if showExclusiveContent(): return true
	
	return (charClass == Classes.Ranger or 
		charClass == Classes.Reaper)

func isClassUnlockedStuffed(charClass: int) -> bool:
	return isClassUnlocked(Util.log2(charClass))

func isClassSelected(charClass) -> bool:


	return charClass == curClass

func getSeason() -> String:
	if Util.laterOrEqual(VERSION, "1.1.0"):
		return "3"
	elif FULLVERSION:
		return "2"
	else:
		return ""






func getSelectedClass() -> int:
	var selectedClass = persistent["selectedClass"]
	if not isClassUnlocked(selectedClass):
		selectedClass = Classes.Ranger
	return selectedClass







func setLoadout(loadout: int):
	curLoadout = loadout
	initStartInventory(loadout)
	emit_signal("loadout_changed")

func getConfiguredLoadout() -> int:
	return getConfigValue("Options", "Loadout_" + getClassInternalName(), 0)

func getClassesForRandom() -> Array:
	var classes = []
	for classI in getNumClasses():
		if isClassUnlocked(classI) and classI != persistent["lastRandomClass"]:
			classes.push_back(classI)
	return classes

const leagueThresholds = [
	0, 
	50, 
	120, 
	200, 
	300, 
	400, 
	480, 
	550, 
	850
]

func getLeague_exact(rating) -> float:
	rating = max(0, rating)
	var league = Leagues.ImpossibleWoodRank
	for threshold in leagueThresholds:
		if rating >= threshold:
			league += 1
		else:
			break
	
	var leftBorder = leagueThresholds[league]
	var rightBorder = leagueThresholds[league + 1]
	var bracketSize: float = rightBorder - leftBorder
	var interpolationPoint = (rating - leftBorder) / bracketSize
	
	
	return league + interpolationPoint

func getRatingFromLeague(leagueExact: float) -> float:
	var league: = int(leagueExact)
	var subrank: = leagueExact - league
	var leftBorder = leagueThresholds[league]
	var rightBorder = leagueThresholds[league + 1]
	var bracketSize: float = rightBorder - leftBorder
	return subrank * bracketSize + leftBorder

func getRatingDifference(leagueExact1: float, leagueExact2: float) -> float:
	return getRatingFromLeague(leagueExact1) - getRatingFromLeague(leagueExact2)

func getRatingDifference_forBonus(rating: float, leagueExact2: float) -> float:
	return getRatingFromLeague(leagueExact2) - rating

func getRanking(charClass) -> int:
	return int(getLeagueProgress(charClass) * 100)

func getLeague(charClass) -> int:
	return int(getLeague_exact(getPlayerRating(charClass)))
	
func getLeagueProgress(charClass) -> float:
	return fmod(getLeague_exact(getPlayerRating(charClass)), 1.0)

func getLeagueName(league):
	return Util.tra("LEAGUE_" + Leagues.keys()[league])

func isBelowLeague(league):
	return getLeague(curClass) < league

func isAtLeastInLeague(league):
	return getLeague(curClass) >= league

func getRankingDifForStats(classI, numWins: int, numLosses: int, 
	numTriesLeft: int, survival: bool):
	var curLeagueExact = getLeague_exact(getPlayerRating(classI))
	var ratingForStats = calcRunRatingForClass(classI, numWins, numLosses, numTriesLeft, survival)
	var newLeagueExact = getLeague_exact(ratingForStats)
	var dif = int(newLeagueExact * 100) - int(curLeagueExact * 100)
	return dif

func getRankingDifIfConceded():
	var classI = arenaRunState["class"]
	if "custom" in arenaRunState:
		if CustomRules.isSwitchModeNoLoad(arenaRunState["custom"]) == CustomRules.SwitchModeState.Ranked:
			classI = null
	
	return getRankingDifForStats(classI, arenaRunState["wins"], MAX_TRIES, 0, 
		arenaRunState["survival"])

func getRankingDif_noSurvival():
	return getRankingDifForStats(curClass, wins, losses, tries, false)

func getRankingDif_survival_worst():
	var maxLosses = MAX_TRIES
	if tries < MAX_TRIES:
		maxLosses += 1
	return getRankingDifForStats(curClass, wins, maxLosses, 0, true)

func getRankingDif_survival_best():
	var healedTries = tries
	if tries < MAX_TRIES:
		healedTries += 1
	return getRankingDifForStats(curClass, MAX_ROUNDS - losses, losses, healedTries, true)

func getSwitchModeRating():
	return persistent["smr"]

func setSwitchModeRating(rating):
	persistent["smr"] = rating

func _enter_tree():
	if not isWeb:
		locales["简体中文"] = "zh_Hans_CN"
		locales["日本語"] = "ja"
		locales["한국어"] = "ko"
		locales["Deutsch"] = "de"
		locales["繁體中文"] = "zh_Hant_TW"
		locales["Español latinoamericano"] = "es"
		locales["Français"] = "fr"
		locales["Русский"] = "ru"
		locales["Português Brasileiro"] = "pt_BR"

func _ready() -> void :
	pause_mode = Node.PAUSE_MODE_PROCESS
	
	print("VERSION ", VERSION, SUBVERSION)
	
	
	
	
	steamAvailable = ( not OS.has_feature("disable_steam_integration")
		and SteamHelper.is_init())
	
	
		
	localeToLanguage = Util.invertDictionary(locales)
	
	
	if useShell():
		processTimer = Timer.new()
		add_child(processTimer)
		processTimer.one_shot = true
		processTimer.connect("timeout", self, "checkProcesses_cyclic")
	
	makeBaseDir()
	
	if PLAYTEST:
		print("PLAYTEST")
	elif BETA:
		print("BETA")
	
	randnum = (Util.rng.randi() << 32) + Util.rng.randi()
	gold_internal = encode(0)
	
	loadGame()
	
	call_deferred("ready_deferred")
	
	for league in Leagues:
		var i = Leagues[league]
		if i != - 1:
			leagueIcons.push_back(load("res://Assets/Leagues/League_" + league + ".png"))
	
	var basePath = "res://CharacterClasses/"
	for className in Classes_Full:
		if isClassUnlocked(Classes_Full[className]):
			classResources.push_back(load(str(basePath, className, "/", className, ".tres")))
		else:
			classResources.push_back(null)
	
	for classIndex in getNumClasses():
		if isClassUnlocked(classIndex):
			classResources[classIndex].loadFiles(getClassKeys()[classIndex])
		chibiMode.push_back(getConfigValue("Options", "Chibi_" + getClassKeys()[classIndex], false))
	
	if BUILD_HISTORY_ENABLED and Util.hasDLL("libgdsqlite"):
		
		buildHistoryDB = load("res://Utility/BuildHistoryDB.gd").new()
	
	stealLifeDamageSource = DamageSource.new().init(null, DamageSource.Type.Effect)
	stealLifeDamageSource.flags = DamageSource.effectFlags
	
	unhealingDamageSource = DamageSource.new().init(null, DamageSource.Type.Unhealing)
	unhealingDamageSource.flags = DamageSource.unhealingFlags
	
	fatigueDamageSource = DamageSource.new().init(self, DamageSource.Type.Fatigue)
	fatigueDamageSource.flags = DamageSource.Flags.CanBeBlocked
	
	for argument in OS.get_cmdline_args():
		if argument == "-write_state":
			print("Writing out state.")
			WRITE_OUT_STATE = true
	
	for c in cursors:
		var c2 = ImageTexture.new()
		var img = Image.new()
		img.copy_from(c)
		c2.create_from_image(img)
		scaledCursors.push_back(c2)
	
	if EDITOR or OS.has_feature("debugging"):
		shopSceneNode.add_child(load("res://Utility/Debug/ShopDebug.tscn").instance())
	if EDITOR:
		titleScreen.add_child(load("res://Utility/Debug/DebugViewer.tscn").instance())
	

	

func ready_deferred():
	print("OS: ", OS.get_name())
	print("vsync on: ", Settings.getVal(Settings.Setting.vsync))
	
	var selectedClass = getSelectedClass()
	instanceCharacter(selectedClass)
	
	if is_instance_valid(MaterialCompiler):
		yield(MaterialCompiler, "finished_loading_materials")
	
	sceneAnimation.connect("animation_finished", self, "onSceneAnimationFinished")
	
	
	
	loadRunState(Mode.Unranked, false)
	
	
	if LOBBIES_ENABLED and loadRunState(Mode.Lobbies):
		
		
		RunDatabase.lobbies.connect("lobby_joined", self, "onReconnectedToLobby")
		RunDatabase.lobbies.connect("lobby_join_failed", self, "onReconnectTimeout")
		RunDatabase.lobbies.tryReconnect()
		
	else:
		deleteRunStateAndRules(Mode.Lobbies)
		loadArenaRunAndStartOnTitle()

func onReconnectedToLobby():
	RunDatabase.lobbies.disconnect("lobby_joined", self, "onReconnectedToLobby")
	RunDatabase.lobbies.disconnect("lobby_join_failed", self, "onReconnectTimeout")
	applySetSkins()
	splashScreenAnimation.play("FadeOut")
	playerNodeAnimation.play("Start")
	continueLastRun(Mode.Lobbies)
	call_deferred("onReconnectedToLobby_deferred")

func onReconnectedToLobby_deferred():
	sceneAnimation.advance(100)
	playerNodeAnimation.advance(100)

func onReconnectTimeout():
	
	print("Reconnect failed")
	deleteRunStateAndRules(Mode.Lobbies)
	RunDatabase.lobbies.disconnect("lobby_joined", self, "onReconnectedToLobby")
	RunDatabase.lobbies.disconnect("lobby_join_failed", self, "onReconnectTimeout")
	loadArenaRunAndStartOnTitle()

var leavingLobby = false

func leaveLobbyFromShop():
	leavingLobby = true
	
	returnToTitle_midRun()
	playerNodeAnimation.play("ReturnToTitle")
	RunDatabase.lobbies.leaveLobby()

func loadArenaRunAndStartOnTitle():
	var selectedClass = getSelectedClass()
	
	
	if not loadRunState(Mode.Unranked):
		instanceCharacter(selectedClass)
		if LOADOUTS_ENABLED:
			setLoadout(getConfiguredLoadout())
			if getConfigValue("Options", "RandomClass", false):
				randomCharacter = true
		else:
			setLoadout(0)
	
	applySetSkins()
	
	emit_signal("continue_loaded")
	
	splashScreenAnimation.play("FadeOut")
	sceneAnimation.play("StartOnTitle")
	playerNodeAnimation.play("Start")
	Util.callDelayed(Sound, "playSound", 1.5, [playerMoveInSound])
	Sound.playBGM(Sound.titleBGM, 0, 0)
	
	SteamHelper.updateRichPresence()

func instanceCharacter(characterClass: int):
	var before = curClass
	curClass = characterClass
	if isClassUnlocked() and curMode != Mode.History:
		persistent["selectedClass"] = curClass
	
	if not PLAYER:
		PLAYER = playerScene.instance()
		PLAYER.playerId = PLAYER.ID.PLAYER
		PLAYER.position = Vector2(playerCombatPos, 880)
		playerNode.add_child(PLAYER)
		PLAYER.setCharacterName(getPlayerName())
		PLAYER.connect("character_died", self, "endCombat")
	else:
		PLAYER.INVENTORY.reset()
	
	PLAYER.setClass(curClass, getEffectiveChibiMode())
	for slot in SkinSlot.values():
		Game.PLAYER.sprite.setSkin(slot, getSelectedSkin(slot))
	
	if before != curClass:
		Util.finishTween(characterTween)
		characterTween = Util.refreshTween(characterTween)
		var sprite = PLAYER.sprite.get_node("Body")
		var offsetPos1 = sprite.position.y - Util.rng.randf_range(80, 100)
		var offsetPos2 = sprite.position.y - Util.rng.randf_range(10, 20)
		var downDur1 = 0.2
		var upDur = 0.05
		var downDur2 = 0.1
		characterTween.tween_property(sprite, "position:y", sprite.position.y, 
			downDur1).from(offsetPos1).set_ease(Tween.EASE_IN)
		characterTween.tween_property(sprite, "position:y", offsetPos2, 
			upDur).from(sprite.position.y).set_ease(Tween.EASE_OUT)
		characterTween.tween_property(sprite, "position:y", sprite.position.y, 
			downDur2).from(offsetPos2).set_ease(Tween.EASE_IN)
	
	emit_signal("character_changed")

func setRandomCharacter(_randomCharacter: bool):
	randomCharacter = _randomCharacter
	emit_signal("random_character_changed")

func initStartInventory(loadout = 0):
	Util.finishTween(loadoutTween)
	loadoutTween = Util.refreshTween(loadoutTween)
	loadoutTween.set_parallel()
	
	deleteDraggedItem()
	
	if isClassUnlocked():
		
		var resource: CharacterClass = classResources[curClass]
		setGold(resource.gold)
		PLAYER.INVENTORY.reset()
		for itemRes in resource.getStartingItems(loadout):
			var item = ItemBook.instantiateItem(itemRes.itemName)
			item.ownerType = Item.Owner.PlayerInventory
			playerNode.add_child(item)
			item.setFaceDirectionInstant(itemRes.faceDirection)
			PLAYER.INVENTORY.addItemByTopLeft(item, itemRes.topLeftCell)
			if loadout == 2:
				addLoadoutAni_jump(item)
			else:
				addLoadoutAni(item, item.isBag())
		
		if loadout != 2:
			addLoadoutAni(PLAYER.INVENTORY, true)

func addLoadoutAni_jump(bag):
	var upDur = 0.05
	var downDur = 0.15
	var offset = Util.rng.randf_range(20, 50)
	
	for node in [bag, PLAYER.INVENTORY]:
		var offsetPos = node.position.y - offset
		loadoutTween.tween_property(node, "position:y", offsetPos, 
			upDur).set_ease(Tween.EASE_OUT)
		loadoutTween.tween_property(node, "position:y", node.position.y, 
			downDur).from(offsetPos).set_delay(upDur).set_ease(Tween.EASE_IN_OUT)

func addLoadoutAni(node, isBag):
	var delay = 0.1
	
	if isBag:
		delay *= Util.rng.randf_range(0.8, 1.2)
		var downDur = 0.05
		var upDur = 0.1
		var offsetPos = node.position.y + Util.rng.randf_range(5, 15)
		loadoutTween.tween_property(node, "position:y", offsetPos, 
			downDur).set_delay(delay).set_ease(Tween.EASE_IN)
		loadoutTween.tween_property(node, "position:y", node.position.y, 
			upDur).from(offsetPos).set_delay(downDur + delay).set_ease(Tween.EASE_OUT)
	else:
		delay *= Util.rng.randf_range(0.6, 1.4)
		var upDur = 0.05
		var downDur = 0.05
		var jumpFactor = Util.rng.randf_range(1, 2)
		var startPos: Vector2 = node.position - Vector2(0, 100 * jumpFactor)
		var bouncePos: Vector2 = node.position - Vector2(0, 10 * jumpFactor)
		loadoutTween.tween_property(node, "position", node.position, 
			delay).from(startPos).set_ease(Tween.EASE_OUT)
		
		loadoutTween.tween_property(node, "position", bouncePos, 
			upDur).set_delay(upDur + delay)
		loadoutTween.tween_property(node, "position", node.position, 
			upDur).set_delay(downDur + upDur + delay).from(bouncePos)

func startFreshRun(mode):
	runsStartedThisSession += 1
	runWasConceded = false
	setMode(mode)
	curRound = 1
	wins = 0
	losses = 0
	tries = MAX_TRIES
	survivalMode = false
	DEVCHEATS = false
	bagPityCounter = 0
	persistent["runsStarted"] += 1
	
	if winNextRun:
		if mode == Mode.Lobbies:
			wins = 17
			curRound = 18
		else:
			wins = MAX_WINS - 1
			curRound = 10
	elif loseNextRun:
		tries = 1
		curRound = 5
	
	if randomCharacter:
		var possibleClasses = getClassesForRandom()
		var classI = Util.pickRandomElement(possibleClasses)
		persistent["lastRandomClass"] = classI
		instanceCharacter(classI)
		initStartInventory(Loadout.RandomLoadout)
		var particles = ObjectPool.particleOneShot(rainbowRevealParticles, playerNode)
		particles.global_position = PLAYER.sprite.global_position
		var numTimesRandomed = SteamHelper.changeStat("Random", 1)
		if numTimesRandomed >= 50:
			SteamHelper.unlockAchievement("Dice")
		
	startRun()
	saveGame()
	
	emit_signal("fresh_run_started")
	
	print("New Game (", Util.enumToString(Mode, curMode), ") as ", Util.enumToString(Classes_Full, curClass))


func startHistoryRun(runData, roundNum: int, opponentData = null, opponentRoundNum = - 1):
	setMode(Mode.History)
	curHistoryData = runData
	curRound = roundNum
	wins = curHistoryData.getWins(roundNum - 1)
	losses = curHistoryData.getLosses(roundNum - 1)
	if roundNum == 1:
		tries = MAX_TRIES
	else:
		tries = curHistoryData.getTries(roundNum - 1)
		
	
	
	instanceCharacter(curHistoryData.classI)
	CustomRules.fromString(curHistoryData.customRules)
	var roundData = curHistoryData.getRoundData(roundNum)
	var items = RunData.deserializeItems(roundData.items, curHistoryData.getVersionString())["items"]
	PLAYER.INVENTORY.createFromItemTuples(items, Item.Owner.PlayerInventory)
	PLAYER.setMaxHealth(roundData.health)
	PLAYER.setMaxStamina(roundData.stamina)
	initRoundResults()
	
	
	sceneAnimation.play("TitleToShop")
	sceneAnimation.advance(1000)
	sceneAnimation.play("ShopToCombat")
	sceneAnimation.advance(3.5)
	
	emit_signal("switching_to_combat")
	print("Refighting from history.")

func endHistoryRun():
	if curHistoryData != null:
		curHistoryData = null
		sceneAnimation.play("CombatToTitle")
		sceneAnimation.advance(100)
		sceneAnimation.play("StartOnTitle")
		sceneAnimation.advance(100)
		playerNodeAnimation.play("ReturnToTitle")
		playerNodeAnimation.advance(100)
		combatSceneNode.clearParticles()
		PLAYER.combatToTitle()
		PLAYER.finishAnimations()
		for node in get_tree().get_nodes_in_group("CombatLabel"):
			node.delete()
		for item in OPPONENT.INVENTORY.getItems():
			item.combatToTitle()
		CustomRules.reset()
		returnedToTitle_afterRun()
		emit_signal("combat_scene_left")
		emit_signal("return_to_history")

func startLobbyRun():
	if randomCharacter:
		deleteDraggedItem()
	closeAllMenus()
	startFreshRun(Game.Mode.Lobbies)
	SteamHelper.unlockAchievement("LobbyStarted", true)

func addStarOfCourage():
	var star = ItemBook.generateItem(ItemBook.starOfCourageDescriptor)
	playerNode.add_child(star)
	var couldAdd = PLAYER.INVENTORY.addItemWherePossible(star)
	if couldAdd:
		star.popIn()
	else:
		star.global_rotation = 0
		star.global_position = STORAGEBOX.center()
		star.pushToStorage()

func initRoundResults():
	roundResults.resize(getMaxNumberOfRounds())
	roundResults.fill(RoundResult.RunOver)

func startRun():
	if LOBBIES_ENABLED and curMode != Mode.Lobbies and RunDatabase.lobbies.isInLobby():
		print("ERR: Mode mismatch")
		get_tree().quit()
	
	runStarted = true
	initRoundResults()
	
	STORAGEBOX.deleteItems()
	
	if curMode == Mode.Ranked:
		CustomRules.reset()
	
	RunDatabase.startRun()
	RunDatabase.sendRunRequest()
	
	call_deferred("titleToShop")
	call_deferred("emit_signal", "run_started")
	
	SteamHelper.call_deferred("updateRichPresence")

func titleToShop():
	sceneAnimation.playback_speed = 1
	sceneAnimation.play("TitleToShop")
	
	InputBlocker.activate(InputBlocker.Source.SceneSwitch)
	PLAYER.titleToShop()
	Sound.playSound(transitionSounds[0])
	playShopBGM()
	emit_signal("switch_to_shop")
	emit_signal("title_to_shop")


func isSoftballRound():
	
	if getRunRating(curClass) > 80:
		return false
	
	if getNumStartedRuns() == 1:
		return true
	elif getNumStartedRuns() == 2:
		return curRound % 4 != 0
	elif getNumStartedRuns() == 3 or getRunWins() == 0:
		return curRound % 2 != 0
	elif getNumStartedRuns() == 4 or getRunWins() == 1:
		return curRound % 4 == 0
	else:
		return false

func isSoftballStats():
	return ((wins == 0 and losses == 3) or 
			(wins <= 1 and losses == 4))

func isItemHandicapStats():
	return ((wins == 0 and losses == 2) or 
			(wins == 1 and losses == 3) or 
			(wins == 2 and losses == 4) or 
			(wins == 3 and losses == 4) or 
			(wins == 0 and losses == 4))

func isShopActive() -> bool:
	return state == State.Shop and canSwitchToCombat

func isSwitchToCombatPossible() -> bool:
	return (state == State.Shop and 
		canSwitchToCombat and 
		curMode != Mode.Lobbies and 
		draggedItem == null)

func cancelSwitch():
	if canCancelSwitch:
		
		var pos = sceneAnimation.current_animation_position
		sceneAnimation.stop()
		startCombatButtonAni.play_backwards("TurnAround")
		startCombatButtonAni.seek(pos)
		startCombatButton.cancelSwitch()
		canCancelSwitch = false

func switchToCombat():
	
	canCancelSwitch = true
	
	var pos = 0
	if startCombatButtonAni.current_animation == "TurnAround":
		pos = startCombatButtonAni.current_animation_position
	
	sceneAnimation.playback_speed = 1
	sceneAnimation.play("ShopToCombat")
	
	if pos == 0:
		sceneAnimation.advance(0.017)
	else:
		sceneAnimation.seek(pos)
	
	setInventoryEditMode(InventoryEditMode.Default)
	
	emit_signal("combat_start_pressed")

func finishSwitchingToCombat():
	closeAllMenus()
	setInventoryEditMode(InventoryEditMode.Default)
	
	canCancelSwitch = false
	canSwitchToCombat = false
	justStartedSurvivalMode = false
	InputBlocker.activate(InputBlocker.Source.SceneSwitch)
	
	call_deferred("unhoverAndHideTooltips")
	
	if not isTutorialDone(TutorialSteps.GoldCarryOver):
		if gold == 0:
			startedCombatWithoutGold += 1
		else:
			startedCombatWithoutGold = 0
			setTutorialDone(TutorialSteps.GoldCarryOver)
			
	
	if curMode != Mode.History:
		var runState = getRunState(curMode)
		runState["incombat"] = true
		if isArenaMode():
			RunDatabase.serializeCurrentRound()
		
		saveRunState()
		saveGame()
	
	Sound.playSound(transitionSounds[1])
	if survivalMode:
		Sound.playBGM(Sound.battleBGM_survival, 2)
	else:
		Sound.playBGM(Sound.battleBGM, 4)
	
	var roundReduction = 0
	var droppedItems = 0
	
	if not BETA and curMode != Mode.Lobbies and not CustomRules.isSwitchMode():
		if isBelowLeague(Leagues.Diamond) and isItemHandicapStats():
			droppedItems += 1
		if isSoftballRound():
			roundReduction += 1
			
		if isBelowLeague(Leagues.Diamond) and isSoftballStats():
			roundReduction += 1
		
		if roundReduction >= curRound:
			roundReduction = curRound - 1
			droppedItems += 1
	
	
	
	
	OPPONENT = opponentScene.instance()
	OPPONENT.playerId = OPPONENT.ID.OPPONENT
	
	PLAYER.setOpponent(OPPONENT)
	OPPONENT.setOpponent(PLAYER)
	OPPONENT.connect("character_died", self, "endCombat")
	
	OPPONENT.position = Vector2(1920 - playerCombatPos, 880)
	opponentNode.add_child(OPPONENT)
	
	if curMode == Mode.History and buildHistory.markedOpponentData != null:
		initHistoryOpponent()
	else:
		RunDatabase.sortOpponents()
		
		while true:
			var res = initOpponent(roundReduction, droppedItems)
			if res == 0:
				
				break
	
	fightEnded = false
	numTimesOutOfStamina = 0
	
	emit_signal("shop_closed")
	emit_signal("switching_to_combat")
	
	combatTimer.initialize()
	PLAYER.shopToCombat()
	
	var playerItems = PLAYER.INVENTORY.getItems().duplicate()
	playerItems.shuffle()
	playerItems.sort_custom(ItemSort, "sort_TriggerPriority")
	


	
	var opponentItems = OPPONENT.INVENTORY.getItems().duplicate()
	opponentItems.shuffle()
	opponentItems.sort_custom(ItemSort, "sort_TriggerPriority")
	
	
	call_deferred("prepareItems", playerItems + opponentItems)
	Util.callDelayed(self, "activateItems", COMBAT_DELAY, [playerItems + opponentItems])
	
	PLAYER.playSound(classResources[curClass].getRoundStartSound(), 4)
	
	Util.callDelayed(Sound, "playSound", 0.3, [combatSceneNode.combatStartSound])
	
	ItemBook.pausePrepare()
	
	print("Round ", curRound, " Battle start")

func closeAllMenus():
	if itemLibrary.isOpen:
		itemLibrary.close()
	if recipeBook.isOpen:
		recipeBook.close()
	if options.isOpen:
		options.close()
	if wardrobe.isOpen:
		wardrobe.close()
	if draggedItem != null:
		draggedItem.cancelDrag()

func forceSwitchToCombat():
	if not canSwitchToCombat:
		print("Attempted switch to combat")
		return
	closeAllMenus()
	unhoverAndHideTooltips()
	switchToCombat()
	canSwitchToCombat = false
	
	InputBlocker.activate(InputBlocker.Source.Lobby)
	for control in get_tree().get_nodes_in_group("PinnedControl"):
		InputBlocker.restoreControl(InputBlocker.Source.Lobby, control)
	
	RunDatabase.lobbies.prepareCombat()
	
	
	if not RunDatabase.lobbies.allOpponentsSubmitted():
		sceneAnimation.stop(false)
		RunDatabase.lobbies.connect("found_opponent", self, "finishForceSwitchToCombat", [], CONNECT_ONESHOT)
		Util.callDelayed_process(self, "onWaitingForMembersTimeout", 5)
	else:
		finishForceSwitchToCombat()

func finishForceSwitchToCombat():
	sceneAnimation.advance(COMBAT_DELAY)
	sceneAnimation.play()
	
	RunDatabase.lobbies.startCombat()

func onWaitingForMembersTimeout():
	if not RunDatabase.lobbies.isInLobby(): return
	
	var membersList = ""
	var missing = RunDatabase.lobbies.getMissingOpponentNames()
	if missing.empty():
		
		return
	
	for i in missing.size():
		membersList += missing[i]
		if i != missing.size() - 1:
			membersList += "\n"
	
	if RunDatabase.lobbies.isHost():
		Util.showPopupMessage("HINT_WaitingForMembers", {"members": membersList}, 5)
	else:
		print("Offline members: ", membersList)

func forceLeaveLobby():
	Util.tryDisconnect(RunDatabase.lobbies, "found_opponent", self, "finishForceSwitchToCombat")
	InputBlocker.deactivate(InputBlocker.Source.Lobby)
	
	if not RunDatabase.lobbies.isInLobby():
		print("not in lobby")
		return
	
	if sceneAnimation.current_animation != "":
		leaveLobbyPending = true
		print("forceLeaveLobby 1")
		return
	
	if state == State.Title:
		leaveLobbyPending = false
		RunDatabase.lobbies.leaveLobby()
		print("forceLeaveLobby 2")
		return
	
	closeAllMenus()
	
	if state == State.Shop:
		leaveLobbyFromShop()
		print("forceLeaveLobby 3")
	
	elif state == State.Combat:
		RunDatabase.lobbies.leaveLobby()
		if fightEnded:
			combatSceneNode.forceSwitchToTitle()
			print("forceLeaveLobby 4")
			
		else:
			leaveLobbyPending = true
			print("forceLeaveLobby 5")

func initOpponent(roundReduction, droppedItems):
	var roundData = RunDatabase.getNextOpponentData(roundReduction)
	OPPONENT.INVENTORY.reset()
	ItemBook.opponentItems.clear()
	OPPONENT.setMaxHealth(roundData["health"])
	OPPONENT.setMaxStamina(roundData["stamina"])
	OPPONENT.setClass(roundData["class"], getShowChibis() and roundData["chibi"])
	
	var dropIndex = - 1
	
	if not "reflection" in roundData:
		if droppedItems >= 1:
			dropIndex = Util.rng.randi_range(0, roundData["items"].size() - 1)
	else:
		pass
	
	roundData["items"].sort_custom(ItemSort, "sort_BagOrder")
	
	var itemIndex = 0
	var checkValidity = not "reflection" in roundData
	
	for tuple in roundData["items"]:
		var descriptor = tuple["d"]
		itemIndex += 1
		
		if itemIndex == dropIndex + 1:
			if descriptor.isBag() or descriptor.isWeapon():
				dropIndex += 1
			else:
				
				continue
		
		var item = ItemBook.instantiateItem(descriptor)
		var result = addOpponentItem(tuple, item, checkValidity)
		if result == - 1:
			return - 1
	
	for slot in roundData["skins"].size():
		var skinId = roundData["skins"][slot]
		
		if roundData["chibi"] and not getShowChibis():
			skinId = SkinBook.getRandomSkinFor(roundData["class"], 1, slot).id
		
		OPPONENT.sprite.setSkin(slot, skinId)
	
	OPPONENT.setCharacterName(roundData["name"])
	if Settings.getVal(Settings.Setting.hide_names):
		OPPONENT.hideCharacterName()
	
	curOpponentData = roundData
	return 0


func initHistoryOpponent():
	
	var data = buildHistory.markedOpponentData
	var roundI = buildHistory.markedOpponentRound
	
	var roundData: BuildHistoryData.RoundData = data.getRoundData(roundI)
	OPPONENT.INVENTORY.reset()
	OPPONENT.setMaxHealth(roundData.health)
	OPPONENT.setMaxStamina(roundData.stamina)
	OPPONENT.setClass(data.classI, false)
	
	var deserialized = RunData.deserializeItems(roundData.items, 
		data.getVersionString())
	
	var items = deserialized["items"]
	items.sort_custom(ItemSort, "sort_BagOrder")
	
	var itemIndex = 0
	for tuple in items:
		var descriptor = tuple["d"]
		var item = ItemBook.instantiateItem(descriptor)
		var result = addOpponentItem(tuple, item, true)
		if result == - 1:
			return - 1
	
	for slot in SkinSlot.size():
		OPPONENT.sprite.setSkin(slot, 0)
	
	OPPONENT.baseMaxStamina = 5
	OPPONENT.recalculateMaxStamina()
	OPPONENT.setCharacterName(Util.tra("BUTTON_BuildHistory"))
	return 0

func addOpponentItem(tuple, item, checkValidity: bool):
	item.ownerType = Item.Owner.Opponent
	opponentNode.add_child(item)
	var topLeftCellPos = tuple["c"]
	var faceDirection = tuple["f"]
	OPPONENT.INVENTORY.orientItem(item, topLeftCellPos, faceDirection)
	
	if checkValidity:
		if not OPPONENT.INVENTORY.canAddItemOrBag(item):
			if curMode == Mode.History and buildHistory.markedOpponentData != null:
				item.discard()
				print("History entry corrupted")
			else:
				item.discard()
				Util.eprint("Encountered sus run. 8")
				RunDatabase.notifyOpponentCorrupt()
				
				return - 1
	
	OPPONENT.INVENTORY.addItemByTopLeft(item, topLeftCellPos)
	item.disablePicking()
	
	
	if "g" in tuple:
		var gems = tuple["g"]
		for i in gems.size():
			var gemIndex = gems[i]
			if gemIndex != RunDatabase.emptySocketId:
				var gem = ItemBook.instanciateGemFromIndex(gemIndex)
				item.setGem(i, gem)
	
	if "pd" in tuple:
		item.setData(tuple["pd"])
		
	return 0

func prepareItems(items):
	PLAYER.prepare()
	OPPONENT.prepare()
	
	for item in items:
		item.prepare()

func activateItems(items):
	
	
	emit_signal("combat_start")
	combatTimer.start()
	
	PLAYER.combatStart()
	OPPONENT.combatStart()
	
	for item in items:
		item.preCombatStart()
	
	for item in items:
		item.combatStart()
	
	for item in items:
		item.postCombatStart()

func endCombat():
	if fightEnded:
		return
	
	Engine.time_scale = 1
	fightEnded = true
	triesBeforeFight = tries
	
	if ( not loseNextRound and not loseNextRun and 
		(OPPONENT.curHealth <= 0 or winNextRun or winNextRound)):
		roundResults[curRound - 1] = RoundResult.Win
		wins += 1
		PLAYER.playSound(classResources[curClass].getWinRoundSound(), 4, 1.0, true)
		PLAYER.win()
		Sound.playSound(winSound)
		OPPONENT.lose()
	
	else:
		roundResults[curRound - 1] = RoundResult.Loss
		losses += 1
		tries = max(0, tries - 1)
		PLAYER.playSound(classResources[curClass].getLoseRoundSound(), 4, 1.0, true)
		OPPONENT.win()
		PLAYER.lose()
		Sound.playSound(loseSound, 3)
	
	print("Round ", curRound, " Battle ended with ", Util.enumToString(RoundResult, roundResults[curRound - 1]))
	
	call_deferred("combatEndDeferred")

func combatEndDeferred():
	emit_signal("combat_end", roundResults[curRound - 1])
	
	EventBus.disconnectAll()
	PLAYER.combatEnd()
	OPPONENT.combatEnd()
	combatTimer.combatEnd()
	
	if roundResults[curRound - 1] == RoundResult.Win:
		OPPONENT.setCurrentHealth(0)
		PLAYER.setCurrentHealth(max(1, PLAYER.getCurrentHealth()))
	else:
		PLAYER.setCurrentHealth(0)
		OPPONENT.setCurrentHealth(max(1, OPPONENT.getCurrentHealth()))
	
	for item in PLAYER.INVENTORY.getItems() + OPPONENT.INVENTORY.getItems():
		item.combatEnd()
	
	ropeSpeedups.clear()
	cubeAdvanced.clear()
	sandbagActive = false
	
	curRound += 1
	if curMode != Mode.History:
		emit_signal("round_result")
	
	
	if SteamHelper.canUnlock():
		if getLastRoundResult() == RoundResult.Win:
			if combatTimer.combatTime < 3:
				SteamHelper.unlockAchievement("FastBattle")
			elif combatTimer.combatTime >= 45:
				SteamHelper.unlockAchievement("SlowBattle")
			
			var noWeapon = true
			for item in PLAYER.INVENTORY.getItems():
				if item.hasType(Item.Type.Weapon):
					noWeapon = false
					break
			if noWeapon:
				SteamHelper.unlockAchievement("NoWeapon")
			
			if PLAYER.getRelativeHealth() == 1:
				SteamHelper.unlockAchievement("FullHealth")
			elif PLAYER.getCurrentHealth() == 1:
				SteamHelper.unlockAchievement("1Health")
			
			checkForInventoryAchievements()
			
		if PLAYER.getBuffStacks() >= 100:
			SteamHelper.unlockAchievement("ManyBuffs")
		elif OPPONENT.getDebuffStacks() >= 100:
			SteamHelper.unlockAchievement("ManyDebuffs")
		
		if numTimesOutOfStamina >= 10:
			SteamHelper.unlockAchievement("OutOfStamina")
	
	
	
	Sound.fadeOutBGM(1)
	
	if runOver():
		if curMode == Mode.Lobbies:
			endRun_lobby()
		else:
			endRun(true, true)

func forceLoseCombat():
	Engine.time_scale = 1
	fightEnded = true
	roundResults[curRound - 1] = RoundResult.Loss
	losses += 1
	tries = max(0, tries - 1)
	print("Round ", curRound, " Battle timed out")
	call_deferred("combatEndDeferred")

func runOver():
	if curMode == Mode.History:
		return false
	
	if curMode == Mode.Lobbies:
		return curRound == MAX_ROUNDS_LOBBIES + 1
	
	if tries == 0:
		return true
		
	if isSurvivalMode():
		if curRound == MAX_ROUNDS + 1:
			return true
	
	
	return false

func _input(event: InputEvent) -> void :
	if event.is_echo(): return





	
	if not isWeb:
		if Util.isAction_event(event, "grab_item"):
	
			left_click = event.pressed
		
	
	
	if event is InputEventScreenTouch:
		usingTouchscreen = true
		
		if not event.pressed and event.index == draggingFinger:
			draggingFinger = - 1
		
		if event.pressed and draggingFinger == - 1 and draggedItem:
			draggingFinger = event.index
	
	if usingController:
		if (event is InputEventKey or event is InputEventMouseButton):
			usingController = false
			activeControllerDevice = - 1
			emit_signal("input_changed")

	if (event is InputEventJoypadButton or 
				(event is InputEventJoypadMotion and event.axis_value > 0.5)):
		if not usingController:
			usingController = true
			activeControllerDevice = event.device
			emit_signal("input_changed")
		elif activeControllerDevice != event.device:
			activeControllerDevice = event.device
			emit_signal("device_changed")
	





		
	if event.is_action_pressed("toggle_fullscreen"):
		if OS.is_window_fullscreen():
			Settings.setVal(Settings.Setting.window_mode, "windowed")
		else:
			Settings.setVal(Settings.Setting.window_mode, "fullscreen")
	
	if RECIPE_TOOLTIPS_ENABLED:
		if (lockedTooltipItem != null and event.is_pressed() and 
			(event is InputEventKey or event is InputEventMouseButton or event is InputEventJoypadButton)):
				
				if itemLibrary.isOpen:
					var focusItem = getFocusItem()
					if (focusItem != null and 
						focusItem.ownerType == Item.Owner.Tooltip and 
						focusItem.owningBuildIntoRecipesTooltip != null):
						itemLibrary.call_deferred("setSpotlightDescriptor", focusItem.descriptor)
						
				showHintsIsPressed = false
				unlockTooltip()
				get_tree().set_input_as_handled()
		
		if Util.isActionPressed_event(event, "show_hints") and tooltipsEnabled():
			showHintsIsPressed = true
			var focusItem = getFocusItem()
			if focusItem != null:
				focusItem.previewCanAffect()
				
				if focusItem.canShowBuildIntoRecipesTooltip():
					focusItem.showBuildIntoRecipesTooltip()
				
					if Util.getFrameCounter_process() - showHintsTimeStamp < 20:
						lockTooltip(focusItem)
					
					showHintsTimeStamp = Util.getFrameCounter_process()
			else:
				showAffectedLines()
		
		elif Util.isActionReleased_event(event, "show_hints"):
			clearAffectedLines()
			
			if lockedTooltipItem == null:
				showHintsIsPressed = false
				var focusItem = getFocusItem()
				if focusItem == null:
					focusItem = itemLibrary.getSpotlightItem()
				if focusItem != null:
					focusItem.clearCanAffectVisuals()
					if focusItem.canShowBuildIntoRecipesTooltip():
						focusItem.hideBuildIntoRecipesTooltip()
		
	









		













































	

































func showAffectedLines():
	
	if not affectedLines.empty(): return
	if lockedTooltipItem != null: return
	if combatSceneNode.isPostCombatScreenVisible() or isMenuOpen(): return
	
	var inventories = [PLAYER.INVENTORY]
	if OPPONENT != null:
		inventories.push_back(OPPONENT.INVENTORY)
	for inv in inventories:
		for item in inv.getItems():
			if not item.isBag():
				for color in Item.Affected.values():
					var affectedPoints = inv.getAffectedPoints(item, color)
					for point in affectedPoints:
						
						var line = ObjectPool.instance(affectsLineScene)
						
						line.setPositions(item, point)
						line.setColor(color)
						affectedLines.push_back(line)
	
	affectedLines.sort_custom(LineSort, "sort")
	for line in affectedLines:
		UINode.add_child(line)

func clearAffectedLines():
	for line in affectedLines:
		ObjectPool.returnInstance(line)
	affectedLines.clear()

func onInventoryShifted(shift: Vector2):
	cancelSwitch()
	
	for line in affectedLines:
		line.moveBy(shift)
	
	setTutorialDone(TutorialSteps.Shift)

const editModeAnimation = preload("res://Interface/EditModeAnimation.tscn")
var curEditModeAni = null

func setInventoryEditMode(editMode):
	if draggedItem != null: return
	if inventoryEditMode == editMode: return


	inventoryEditMode = editMode
	
	var items = ItemBook.getInventoryStorageShopItems()
	for item in items:
		setItemEditMode(item)
	
	if inventoryEditMode == InventoryEditMode.Default:
		PLAYER.INVENTORY.pushFloatingItemsToStorage()
	
	if EDITOR:
		if curEditModeAni != null:
			curEditModeAni.disappear()
		
		if not UINode.get_node("Toolbar").isOpen:
			curEditModeAni = ObjectPool.instance(editModeAnimation)
			UINode.add_child(curEditModeAni)
			curEditModeAni.onEditModeChanged(inventoryEditMode)
			curEditModeAni.position = Vector2(550, 1020)
		
	
	emit_signal("edit_mode_changed")

func onEditModeAniFinished(ani):
	if ani == curEditModeAni:
		curEditModeAni = null

func setItemEditMode(item, isInGridStorage = null):
	if isInGridStorage == null:
		isInGridStorage = item.isInGridStorage()
	if isInGridStorage: return
	
	if inventoryEditMode == InventoryEditMode.BagLayer:
		item.setEditMode(item.isBag())
	elif inventoryEditMode == InventoryEditMode.ItemLayer:
		item.setEditMode( not item.isBag())
	else:
		item.setEditMode(true)

func lockTooltip(item):
	lockedTooltipItem = item
	cancelSwitch()
	if lockedTooltipItem.buildIntoRecipesTooltip != null:
		lockedTooltipItem.buildIntoRecipesTooltip.onTooltipLocked()
	
	unhoverAllItems(false)
	
	InputBlocker.disableAllControls(InputBlocker.Source.LockedTooltip, shopSceneNode)
	InputBlocker.disableAllControls(InputBlocker.Source.LockedTooltip, playerNode)
	InputBlocker.disableAllControls(InputBlocker.Source.LockedTooltip, buildHistory)
	InputBlocker.disableAllControls(InputBlocker.Source.LockedTooltip, combatSceneNode)
	InputBlocker.disableAllControls(InputBlocker.Source.LockedTooltip, itemLibrary)


func unlockTooltip():
	if lockedTooltipItem == null: return
	
	var lockedTooltipItem_ = lockedTooltipItem
	lockedTooltipItem = null
	lockedTooltipItem_.hoverEnd()
	
	cancelSwitch()
	InputBlocker.restoreAllControls(InputBlocker.Source.LockedTooltip)
	
	for item in itemsUnderMouse:
		item.hover()

func onItemUnderMouse(item):
	itemsUnderMouse.push_back(item)
	

func onItemUnderMouseExited(item):
	if item in itemsUnderMouse:
		itemsUnderMouse.erase(item)
		

func addTranslation():
	for sheet in ["Keywords", "Items", "ExclusiveItems", "Unreleased", "Interface", "Full"]:
		for locale in ["en", "de"]:
			TranslationServer.add_translation(load("res://Sheets/CSV/" + sheet + "." + locale + ".translation"))

var processThread = null
var checkI = 0

func tagAllNodes():
	print("CHECKING FOR NEW NODES #", checkI)
	printNewNodes(get_tree().get_root())
	checkI += 1

func printNewNodes(node):
	for child in node.get_children():
		if child.has_meta("tag"):
			pass
			
			
		else:
			
			child.set_meta("tag", checkI)
			
			print(child.get_path())
		printNewNodes(child)
	
	
	
const clickParticles = preload("res://Interface/ClickParticles.tscn")


const clickSound = preload("res://Assets/Sound/Sand1.mp3")


func _unhandled_input(event: InputEvent) -> void :
	if InputBlocker.isActive(): return
	
	if ( not draggedItem and 
		Util.isActionPressed_event(event, "grab_item") and 
		not isMenuOpen() and 
		Engine.time_scale > 0):
		
		var particles = ObjectPool.particleOneShot(clickParticles, UINode)
		var pos = Util.getMousePosInWindow() - Vector2(10, 10)
		particles.global_position = pos
		Sound.playSound(clickSound, - 4, Util.rng.randf_range(0.8, 1.0))
		particles.self_modulate = Color.white
	
	if (event.is_action_pressed("open_library") and 
		not isMenuOpen() and state != State.Combat):
			itemLibrary.open()

func switchToShop():
	
	canSwitchToCombat = false
	InputBlocker.activate(InputBlocker.Source.SceneSwitch)
	PLAYER.combatToShop()
	OPPONENT.combatToShop()
	
	if CustomRules.isSwitchMode():
		becomeOpponent()
		STORAGEBOX.deleteItems()
	
	for item in PLAYER.INVENTORY.getItems():
		item.combatToShop()
	for item in OPPONENT.INVENTORY.getItems():
		item.combatToShop()
	call_deferred("unhoverAndHideTooltips")
	
	shopSceneNode.z_index = - 51
	sceneAnimation.playback_speed = 1
	sceneAnimation.play("CombatToShop")
	
	Util.setDelayed(self, "canSwitchToCombat", true, 2)
	Sound.playSound(transitionSounds[0])
	
	emit_signal("combat_scene_left")
	emit_signal("switch_to_shop")
	
	playShopBGM()
	
	roundsStartedThisSession += 1
	var runState = getRunState(curMode)
	runState["incombat"] = false


const oppoBonusOffset = 800.0
const switchAniParableOffset = 200.0
const switchAni = preload("res://Interface/SwitchAnimation.tscn")

func becomeOpponent():
	var dur = 0.5
	var offset = OPPONENT.INVENTORY.global_position.x - PLAYER.INVENTORY.global_position.x
	
	var inventoryTween = create_tween().set_parallel()
	addSwitchAniTween(inventoryTween, PLAYER, offset + oppoBonusOffset, switchAniParableOffset, dur)
	addSwitchAniTween(inventoryTween, OPPONENT, - offset, - switchAniParableOffset, dur)
	
	inventoryTween.tween_callback(self, "finishBecomeOpponent", [offset]).set_delay(dur)
	
	var ani = ObjectPool.instance(switchAni)
	UINode.add_child(ani)
	ani.get_node("AnimationPlayer").play("Switch")

func addSwitchAniTween(tween, character, xMovement: float, yOffset: float, dur):


	Util.moveParable(tween, character.INVENTORY, xMovement, yOffset, dur)
	
	for item in character.INVENTORY.getItems():


		Util.moveParable(tween, item, xMovement, yOffset, dur)
	

func finishBecomeOpponent(offset):
	
	PLAYER.INVENTORY.global_position.x -= offset + oppoBonusOffset
	OPPONENT.INVENTORY.global_position.x = 100000
	
	for item in OPPONENT.INVENTORY.getItems():
		item.global_position.x = 100000
	
	var oldItems = PLAYER.INVENTORY.getItems().duplicate()
	
	var itemTuples = curOpponentData["items"]
	PLAYER.INVENTORY.createFromItemTuples(itemTuples, Item.Owner.PlayerInventory)
	
	
	for item in oldItems:
		item.onRemoveFromInventory()

func becomeOpponent_old():
	
	var newInv = OPPONENT.INVENTORY
	var oldInv = PLAYER.INVENTORY
	
	var dif = oldInv.global_position - newInv.global_position
	
	OPPONENT.INVENTORY = oldInv
	PLAYER.INVENTORY = newInv
	opponentNode.remove_child(newInv)
	playerNode.add_child(newInv)
	newInv.position = Vector2(PLAYER.position.x - 300, 60)
	newInv.character = PLAYER
	
	for item in newInv.getItems():
		item.ownerType = Item.Owner.PlayerInventory
		opponentNode.remove_child(item)
		playerNode.add_child(item)
		item.position += dif
		item.resetZ()
	
	for item in oldInv.getItems():
		item.ownerType = Item.Owner.Opponent
		
enum ShopBGM{
	Default, 
	Lobby, 
	Survival, 
	SwitchMode, 
	Subclass, 
	LastTry
}

var lastShopBGM: int = - 1

func playShopBGM():
	var bgm: int
	if curRound == SUBCLASS_ROUND:
		bgm = ShopBGM.Subclass
	elif curMode == Mode.Lobbies:
		bgm = ShopBGM.Lobby
	elif (tries == 1 and lastShopBGM != ShopBGM.LastTry):
		bgm = ShopBGM.LastTry
	elif survivalMode:
		bgm = ShopBGM.Survival
	elif CustomRules.isSwitchMode():
		bgm = ShopBGM.SwitchMode
	else:
		if Util.flip(0.35) and lastShopBGM == ShopBGM.Default:
			bgm = Util.rng.randi_range(ShopBGM.Lobby, ShopBGM.SwitchMode)
		else:
			bgm = ShopBGM.Default
	
	lastShopBGM = bgm
	
	if bgm == ShopBGM.Subclass:
		Sound.playSubclassBGM( - 3)
	elif bgm == ShopBGM.Lobby:
		Sound.playLobbyBGM()
	elif bgm == ShopBGM.Survival:
		Sound.playSurvivalBGM( - 3)
	elif bgm == ShopBGM.SwitchMode:
		Sound.playSwitchModeBGM( - 3)
	elif bgm == ShopBGM.LastTry:
		Sound.playLastTryBGM( - 3)
	else:
		Sound.playBGM(Sound.shopBGM)

func freeOpponent():
	if OPPONENT:
		OPPONENT.INVENTORY.deleteItems()
		OPPONENT.INVENTORY.queue_free()
		OPPONENT.queue_free()
		OPPONENT = null
		ItemBook.opponentItems.clear()
		curOpponentData.clear()

func onSceneAnimationFinished(aniName):
	
	if aniName == "TitleToShop" and curMode != Mode.History:
		state = State.Shop
		canSwitchToCombat = true
		InputBlocker.deactivate(InputBlocker.Source.SceneSwitch)
		emit_signal("pre_shop_opened_from_title")
		if randomCharacter and not wasRunContinued():
			addStarOfCourage()
		var runState = getRunState(curMode)
		if runState.get("incombat", false):
			startRound()
		runState["incombat"] = false
		SteamHelper.updateRichPresence()
		emit_signal("shop_opened")
	
	elif aniName == "ShopToCombat":
		state = State.Combat
		if curMode == Mode.Lobbies:
			InputBlocker.deactivate(InputBlocker.Source.Lobby)
			closeAllMenus()
		
		InputBlocker.deactivate(InputBlocker.Source.SceneSwitch)
		writeoutState()
		emit_signal("combat_scene_entered")
	
	elif aniName == "CombatToShop":
		if leaveLobbyPending:
			leaveLobbyFromShop()
			leaveLobbyPending = false
		else:
			state = State.Shop
			InputBlocker.deactivate(InputBlocker.Source.SceneSwitch)
			emit_signal("pre_shop_opened_from_combat")
			
			freeOpponent()
			startRound()
			var runState = getRunState(curMode)
			runState["incombat"] = false
			
			call_deferred("emit_signal", "shop_opened")
			shopSceneNode.z_index = 10

func startRound():
	PLAYER.shopEntered()
	
	var curHealthGain = getHealthGain(curRound)
	var curGoldGain = getGoldGain(curRound)
	curGoldGain += CustomRules.getBonusGold()
	curGoldGain = max(0, curGoldGain)
	gainRoundGold(curGoldGain, curHealthGain)
	
	if curGoldGain > 0:
		var coinParticles_ = shootGold(goldPos.global_position, Game.PLAYER.getGoldPos(), curGoldGain)
		coinParticles_.z_index = Util.getGlobalZ(UINode)
	
	
	var itemsAndGems = PLAYER.INVENTORY.getItemsAndGems()
	
	itemsAreFusing = false
	craftingPriorities.clear()
	
	var boxofCogs = ItemBook.getItemsInInventoryOfType(ItemBook.boxofCogsDescriptor)
	var cogBadge = ItemBook.getItemsInInventoryOfType(ItemBook.classBadges[Classes_Full.Engineer])
	
	var hasCogBoxOrBadge = not boxofCogs.empty() or not cogBadge.empty()
	
	
	if hasCogBoxOrBadge:
		var itemsWantToFuse: = false
		
		for item in itemsAndGems:
			if item.readyToFuse():
				itemsWantToFuse = true
				break
		
		if itemsWantToFuse:
			var ani = notCraftingAnimation.instance()
			playerNode.add_child(ani)
			ani.get_node("AnimationPlayer").play("Turn")
			ani.get_node("AnimationPlayer").advance(0.01)
			if not boxofCogs.empty():
				ani.global_position = boxofCogs[0].global_position
			else:
				ani.global_position = cogBadge[0].global_position
			
	var craftOnShopEntered = not hasCogBoxOrBadge and not CustomRules.isSwitchMode()
	
	if craftOnShopEntered:
		for item in itemsAndGems:
			if item.readyToFuse():
				itemsAreFusing = true
				InputBlocker.activate(InputBlocker.Source.Fusing)
				Util.callDelayed(self, "onCraftingTimeout", Item.PRE_FUSE_DUR + Item.FUSE_DUR)
				break
		
		itemsBeingCrafted.clear()
		if itemsAreFusing:
			for item in itemsAndGems:
				if item.readyToFuse():
					if item.curRecipe != null:
						itemsBeingCrafted.push_back(item.curRecipe.fusedItem)
	
	var playerItems = PLAYER.INVENTORY.getItems().duplicate()
	playerItems.sort_custom(ItemSort, "sort_ShopPriority")
	for item in playerItems:
		item.shopEntered(craftOnShopEntered)
	
	sortedCraftingPriorities = Util.sortDict(craftingPriorities)
	
	for item in sortedCraftingPriorities:
		item.startFusing()
	
	
	if not itemsAreFusing:
		for item in itemsAndGems:
			if item.readyToTransform():
				itemsAreFusing = true
				InputBlocker.activate(InputBlocker.Source.Fusing)
				Util.callDelayed(self, "onCraftingTimeout", Item.TRANSFORMATION_DUR)
				break
	
	if CustomRules.isSwitchMode():
		var cogPos = Vector2(975, - 50)
		var cog = ItemBook.generateAndStorageItem(ItemBook.cogDescriptor, 
			cogPos, cogPos)
		var angle = deg2rad(20)
		var impulse = Vector2(0, 1500 * Util.rng.randf_range(0.8, 1.2)).rotated(
				Util.rng.randf_range( - angle, angle))
		cog.apply_impulse(Util.randInBox(10, 10), impulse)
	
	SteamHelper.updateRichPresence()
	
	
	if (getNumStartedRuns() > 4 and 
		getNumStartedRuns() < 10 and 
		not isTutorialDone(TutorialSteps.ItemLibrary)):
		
		itemLibraryTutorialAni.play("Tutorial")

func gainRoundGold(curGoldGain, curHealthGain):
	PLAYER.giveMaxHealth(curHealthGain)
	emit_signal("round_start_health_gained", curHealthGain)
	
	if CustomRules.isSwitchMode():
		setGold(curGoldGain)
	else:
		gainGold(curGoldGain)
	emit_signal("round_start_gold_gained", curGoldGain)

const ratingDecay = 0.96
const ratingVelo = 0.63

func calcRunRatingForClass(classI = curClass, numWins = wins, numLosses = losses, 
	triesLeft = tries, survival = survivalMode, 
	perfectRunBeforeSurvival = wasPerfectRunBeforeSurvival()):
	
	var curRating = getPlayerRating(classI)
	
	return calcRunRating(curRating, numWins, numLosses, triesLeft, survival, 
		perfectRunBeforeSurvival)


func calcRunRating(curRating, numWins = wins, numLosses = losses, 
	triesLeft = tries, survival = survivalMode, 
	perfectRunBeforeSurvival = wasPerfectRunBeforeSurvival()):
	
	var oldLeagueExact = getLeague_exact(curRating)
	
	var rating = 2 * numWins
	
	if triesLeft > 0:
		rating -= 0.5 * numLosses
	else:
		rating -= 1.0 * numLosses
	
	if survival:
		var survivalBonus = 0
		if perfectRunBeforeSurvival:
			survivalBonus += PERFECT_RUN_RATING * 0.5
		
		if numLosses == 0:
			survivalBonus += PERFECT_SURVIVAL_RATING
		elif triesLeft > 0:
			survivalBonus += SURVIVED_RATING
		
		if int(oldLeagueExact) >= Leagues.Master:
			survivalBonus *= 0.6
		
		rating += survivalBonus
	else:
		if numLosses == 0:
			rating += PERFECT_RUN_RATING
		elif triesLeft > 0:
			rating += MAX_WINS_RATING
	
	var oldRating = curRating
	curRating += rating
	curRating *= ratingDecay
	var change = curRating - oldRating
	if change < 0:
		change *= 0.6
	curRating = oldRating + change * ratingVelo
	
	var newLeagueExact = getLeague_exact(curRating)
	if int(newLeagueExact) > int(oldLeagueExact):


		var bonusRating = getRatingDifference_forBonus(curRating, newLeagueExact + RANK_UP_BONUS_RANKING / 100.0)
		
		curRating += bonusRating
	
	var clampVal = leagueThresholds[Leagues.Grandma + 1] - 0.5
	curRating = clamp(curRating, 0.0, clampVal)
	
	return curRating

func hasPlayedInSeason(season = getSeason()):
	return "rating" + season in persistent

func getRunRating(charClass, season = getSeason()):
	return persistent["rating" + season][charClass]

func setRating(rating, charClass = curClass):
	persistent["rating" + getSeason()][charClass] = rating

func getPlayerRating(charClass = null):
	if isRankedSwitchMode() or charClass == null:
		return getSwitchModeRating()
	else:
		return getRunRating(charClass)

func winRun():
	endRun()

func loseRun():
	endRun()

func wasMaxWins():
	return wins >= MAX_WINS

func wasPerfectRun():
	return wasMaxWins() and losses == 0

func hasSurvived():
	return curRound == MAX_ROUNDS + 1 and tries > 0

func wasPerfectSurvival():
	return hasSurvived() and losses == 0

func getBonusTrophies() -> int:
	if survivalMode:
		if wasPerfectSurvival():
			
			return PERFECT_SURVIVAL_TROPHIES
		elif hasSurvived():
			
			return SURVIVED_TROPHIES
	else:
		if wasPerfectRun():
			return PERFECT_RUN_TROPHIES
		elif wasMaxWins():
			return MAX_WINS_TROPHIES
	
	return 0

func endRun(commit = true, showAchievements = true):
	if Engine.get_physics_frames() == endRunFrame:
		Util.eassert(false)
		print("Duplicate end run")
		return
	
	endRunFrame = Engine.get_physics_frames()
	print("Game over")
	
	if survivalMode and hasSurvived():
		SteamHelper.unlockAchievement("Survived" + getClassInternalName(curClass))
		if getTries() == MAX_TRIES:
			SteamHelper.unlockAchievement("FullLifeSurvival")
		
	leagueExactPreRun = getLeague_exact(getPlayerRating(curClass))
	leaguePreRun = int(leagueExactPreRun)
	rankingPreRun = getRanking(curClass)
	leagueProgressPreRun = fmod(leagueExactPreRun, 1.0)
	trophiesPreRun = getTrophies()
	wasRankedSwitchMode = isRankedSwitchMode()
	
	
	
	
	if curMode == Mode.Ranked:
		setRating(calcRunRatingForClass())
	elif curMode == Mode.Unranked:
		if CustomRules.areCustomRulesActive():
			commit = false
		if CustomRules.isRankedSwitchMode():
			setSwitchModeRating(calcRunRating(getSwitchModeRating()))
	elif curMode == Mode.Lobbies:
		commit = false
	
	
	
	
	if ITEM_STATISTICS_ENABLED:
		for item in PLAYER.INVENTORY.getItemsAndGems():
			if hasSurvived():
				var newVal = incrementItemStatistic(ItemStatistic.Survivals, 
					item.descriptor)
				if newVal == 1:
					addRecord(ItemStatistic.Survivals, item.descriptor, 1)
				
				if curMode == Mode.Ranked:
					var highestRank = getItemStatistics(ItemStatistic.BestRankSurvival, item.descriptor, 0.0)
					var curRank = getLeague_exact(getRunRating(curClass))
					if stepify(curRank, 0.01) > stepify(highestRank, 0.01):
						setItemStatistic(ItemStatistic.BestRankSurvival, item.descriptor, curRank)
						addRecord(ItemStatistic.BestRankSurvival, item.descriptor, curRank)
						
			
			var mostWins = getItemStatistics(ItemStatistic.MostWins, item.descriptor, 0)
			if wins > mostWins:
				setItemStatistic(ItemStatistic.MostWins, item.descriptor, wins)
				addRecord(ItemStatistic.MostWins, item.descriptor, wins)
		
		if showAchievements:
			emit_signal("records_updated")
	
	persistent["totalWins"] += wins
	
	giveTrophies(wins + getBonusTrophies())
	
	if wasMaxWins():
		persistent["runWins"] += 1
	
	persistent["runsFinished"] += 1
	
	if (commit and 
		not runWasConceded and 
		not (lastRunConcedeRound == 1 and lastRunMode == Mode.Unranked) and 
		not wasRunContinued() and 
		not winNextRun and 
		not loseNextRun and 
		
		not PREVIEW and 
		not ENGINEER_TEST and 
		( not DEVCHEATS or EDITOR)):
		RunDatabase.pushRun()
	
	lastRunMode = curMode
	if runWasConceded:
		lastRunConcedeRound = curRound
	else:
		lastRunConcedeRound = - 1
	
	onRunEnded()

func endRun_lobby():
	print("Game over (Lobby)")
	trophiesPreRun = getTrophies()
	giveTrophies(wins + getBonusTrophies())
	persistent["totalWins"] += wins
	persistent["runsFinished"] += 1
	lastRunMode = curMode
	onRunEnded()

func onRunEnded():
	deleteRunStateAndRules()
	numTimesOutOfStamina = 0
	continueState = ContinueState.NotContinued
	saveGame()
	runStarted = false
	emit_signal("run_over")


func returnToTitle_afterRun():
	call_deferred("unhoverAndHideTooltips")
	
	if not showExclusiveContent() and persistent["runsFinished"] == 1:
		var wishlistPopup = load("res://Interface/WishlistPopup.tscn").instance()
		wishlistPopup.open()
		yield(wishlistPopup, "closed")
	
	InputBlocker.activate(InputBlocker.Source.SceneSwitch)
	
	emit_signal("combat_scene_left")
	emit_signal("return_to_title")
	
	
	sceneAnimation.playback_speed = 1
	sceneAnimation.play("StartOnTitle")
	sceneAnimation.seek(0, true)
	sceneAnimation.play("CombatToTitle")
	sceneAnimation.advance(0.01)
	sceneAnimation.queue("StartOnTitle")
	
	playerNodeAnimation.play("ReturnToTitle")
	Sound.playSound(playerMoveInSound, - 3, 0.7)
	Util.callDelayed(Sound, "playSound", 2, [playerMoveInSound])
	
	PLAYER.combatToTitle()
	
	for item in OPPONENT.INVENTORY.getItems():
		item.combatToTitle()
	
	Sound.playSound(transitionSounds[2])
	Sound.playBGM(Sound.titleBGM)
	
	Util.callDelayed(self, "returnedToTitle_afterRun", 1)

func returnedToTitle_afterRun():
	state = State.Title
	setMode(Mode.Unselected)
	curRound = 1
	
	
	if leavingLobby:
		deleteRunStateAndRules()
		numTimesOutOfStamina = 0
		continueState = ContinueState.NotContinued
		runStarted = false
	




	
	InputBlocker.deactivate(InputBlocker.Source.SceneSwitch)
	emit_signal("returned_to_title")
	freeOpponent()
	
	if hasArenaRunState():
		readRoundResultsFromRunState(Mode.Unranked)
		initPlayerFromRunstate()
	else:
		instanceCharacter(getSelectedClass())
		setLoadout(getConfiguredLoadout())
	
	SteamHelper.updateRichPresence()
	


func returnToTitle_midRun():
	saveRunState()
	
	hideTooltips()
	unhoverAllItems()
	setInventoryEditMode(InventoryEditMode.Default)
	
	InputBlocker.activate(InputBlocker.Source.SceneSwitch)
	
	
	for item in STORAGEBOX.getItems():
		Util.killTween(item.movebackTween)
		item.z_as_relative = false
		item.z_index = 20
	
	emit_signal("return_to_title")
	
	sceneAnimation.playback_speed = 1
	sceneAnimation.play("StartOnTitle")
	sceneAnimation.seek(0, true)
	sceneAnimation.play("ShopToTitle")
	sceneAnimation.advance(0.01)
	sceneAnimation.queue("StartOnTitle")
	
	PLAYER.shopToTitle()
	
	Sound.playSound(transitionSounds[2])
	Sound.playBGM(Sound.titleBGM)
	
	Util.callDelayed(self, "returnedToTitle_midRun", 1)
	
	runStarted = false
	justStartedSurvivalMode = false

func returnedToTitle_midRun():
	state = State.Title
	InputBlocker.deactivate(InputBlocker.Source.SceneSwitch)
	
	if leavingLobby:
		Util.eassert(curMode == Mode.Lobbies)
		onRunEnded()
		setMode(Mode.Unselected)
		curRound = 1
		
		if hasArenaRunState():
			readRoundResultsFromRunState(Mode.Unranked)
			initPlayerFromRunstate()
		else:
			instanceCharacter(getSelectedClass())
			setLoadout(getConfiguredLoadout())
		playerNodeAnimation.play("Start")
		leavingLobby = false
	
	emit_signal("returned_to_title")
	SteamHelper.updateRichPresence()

func isOtherModesUIOpen():
	return otherModesUI != null and otherModesUI.isOpen

func isLobbyUIOpen():
	return otherModesUI != null and (
		otherModesUI.joinLobbyUI.isOpen or otherModesUI.hostLobbyUI.isOpen)

func encode(g: int) -> int:
	return (g + (g << 32)) ^ randnum

func encode_static(g: int) -> int:
	return g ^ 2345345

func decode_static(g: int) -> int:
	return encode_static(g)

const decodeOffset = int(pow(2, 32))



func decode(g: int) -> int:
	var a = g ^ randnum
	var b = a % decodeOffset
	var c = a >> 32
	if b != c:
		print("ERROR_12")
		get_tree().quit()
	return b


func getGold() -> int:
	return decode(gold_internal)

func setGoldEncoded(amount):
	gold_internal = encode(amount)
	gold = decode(gold_internal)

func setGold(amount):
	var oldGold = decode(gold_internal)
	setGoldEncoded(amount)
	emit_signal("gold_changed", amount - oldGold)

func spendGold(amount):
	setGoldEncoded(decode(gold_internal) - amount)
	emit_signal("gold_changed", - amount)

func gainGold(amount):
	var newVal = decode(gold_internal) + amount
	setGoldEncoded(newVal)
	emit_signal("gold_changed", amount)
	if newVal >= 30:
		SteamHelper.unlockAchievement("Rich")

const coinParticles = preload("res://Interface/CoinParticles.tscn")

func shootGold(fromPos, toPos, amount):
	
	var particles = coinParticles.instance()
	UINode.add_child(particles)
	particles.global_position = fromPos
	particles.activate(amount, fromPos, toPos)
	Util.callDelayed(particles, "queue_free", 10)

	
	return particles

func getCoinPlayerLayer() -> int:
	return Game.playerNode.z_index + 20

func getCoinSellboxLayer() -> int:
	return Util.getGlobalZ(Game.SELLBOX) + 3



func itemPickedUp(item):
	cancelSwitch()
	draggedItem = item
	emit_signal("item_picked_up")
	if item.isBag():
		onBagMoved()

func itemDropped(item, dropResult):
	lastItemDropTime = Util.time
	emit_signal("item_dropped", item, dropResult)
	if draggedItem == item:
		draggedItem = null
	PLAYER.INVENTORY.cleanUp()
	
func onInventoryChanged():
	emit_signal("inventory_changed")

func getCombatOrReplayTime() -> float:
	if fightEnded:
		return combatLog.replayTime
	else:
		return combatTimer.combatTime

func tooltipsEnabled():
	return TOOLTIPS and not SELECTING and Util.getFrameCounter_process() > tooltipDisableFrameCounter

func disableTooltipsFor(frames):
	tooltipDisableFrameCounter = Util.getFrameCounter_process() + frames

func hoverResponseEnabled():
	return TOOLTIPS and not SELECTING and Util.getFrameCounter_process() > hoverResponseDisabledFramecounter

func disableHoverResponsesFor(frames):
	hoverResponseDisabledFramecounter = Util.getFrameCounter_process() + frames

func unhoverAllItems(clearItemsUnderMouse = true):
	reactToHoverEnd = false
	for item in hoveredItems.duplicate():
		item.hoverEnd()
	hoveredItems.clear()
	reactToHoverEnd = true
	if clearItemsUnderMouse:
		itemsUnderMouse.clear()
	

func refocusHoveredItem():
	if hoveredItems.empty(): return
	hoveredItems[0].gainFocus()
	emit_signal("item_gained_focus", hoveredItems[0])

func hasHoverFocus(item):
	
	if draggedItem != null:
		return draggedItem == item
	
	if hoveredItems.empty(): return false
	
	return hoveredItems[0] == item

func getFocusItem():
	if draggedItem != null:
		return draggedItem
	
	if not hoveredItems.empty():
		return hoveredItems[0]
	
	return null

func itemHovered(item):
	if Util.getFrameCounter_process() < focusDisableFrameCounter:
		return
	
	var focusItem = null
	if not hoveredItems.empty():
		focusItem = hoveredItems[0]
	
	hoveredItems.push_back(item)
	
	hoveredItems.sort_custom(ItemSort, "sort_HoverPriority")
	
	
	if hoveredItems[0] != focusItem:
		
		if focusItem != null:
			focusItem.loseFocus()
		
		emit_signal("item_gained_focus", hoveredItems[0])


func recalcHoverPriority():
	var focusItem = null
	if not hoveredItems.empty():
		focusItem = hoveredItems[0]
	
	hoveredItems.sort_custom(ItemSort, "sort_HoverPriority")
	
	if focusItem and hoveredItems[0] != focusItem:
		focusItem.loseFocus()
	
	refocusHoveredItem()

func itemHoverEnd(item):
	if reactToHoverEnd:
		if hasHoverFocus(item):
			if hoveredItems.size() >= 2:
				
				hoveredItems[1].gainFocus()
				emit_signal("item_gained_focus", hoveredItems[1])
		
		hoveredItems.erase(item)


func isInsideDraggedItem(item):
	return draggedItem and item in draggedItem.draggedInsideItems

func onItemBought(item, onSale):
	emit_signal("item_bought", item, onSale)
	if Util.rng.randf() < 0.1:
		PLAYER.playSound(classResources[curClass].getBuySound(), 4)
	
	incrementItemStatistic(Game.ItemStatistic.Acquired, item.descriptor)
	if onSale:
		incrementItemStatistic(Game.ItemStatistic.BoughtOnSale, item.descriptor)

const specialItemBoughtSound = preload("res://Assets/Sound/LevelUp2.ogg")

func onSpecialItemBought(item):
	
	SteamHelper.updateRichPresence()
	emit_signal("special_item_bought", item)
	
	PLAYER.levelUp()
	Sound.playSound(specialItemBoughtSound)

func onItemSold(item):
	emit_signal("item_sold", item)



func onItemRotated():
	persistent["rotations"] += 1
	setTutorialDone(TutorialSteps.Rotate)

func getTotalRotations():
	return persistent["rotations"]

func onItemLocked():
	setTutorialDone(TutorialSteps.Lock)
	




func onItemReserved():
	setTutorialDone(TutorialSteps.Reserve)
	




func onBagMoved():
	setTutorialDone(TutorialSteps.BagMove)
	




func getNumCrafted(itemName):
	var index = ItemBook.getItemIndex(itemName)
	return persistent["craftedRecipes"].get(index, 0)

const RECIPE_REVEALED = - 1

func onCraftingTimeout():
	for item in sortedCraftingPriorities:
		item.finishFusing()
	sortedCraftingPriorities.clear()
	itemsAreFusing = false
	emit_signal("crafting_finished")
	
	InputBlocker.deactivate(InputBlocker.Source.Fusing)
	

func onItemCrafted(itemDescriptor: ItemDescriptor):
	var index = itemDescriptor.getIndex()
	var prevAmount = persistent["craftedRecipes"].get(index, 0)
	if prevAmount == RECIPE_REVEALED:
		
		prevAmount = 0
	persistent["craftedRecipes"][index] = prevAmount + 1
	persistent["crafted"] += 1
	incrementItemStatistic(Game.ItemStatistic.Acquired, itemDescriptor)
	
	saveRunState()
	saveGame()
	emit_signal("item_crafted", itemDescriptor)
	
	if ( not itemDescriptor.getName() == "Goobert" and 
		not (itemDescriptor.gateItem == ItemBook.boxOfRichesDescriptor)):
		
		SteamHelper.unlockAchievement("Crafted" + str(itemDescriptor.itemIndex))

func onCraftingFinished():
	emit_signal("item_crafting_finished")

func getNumCraftedItems():
	return persistent["crafted"]


func revealRecipe(itemDescriptor):
	var index = ItemBook.getItemIndex(itemDescriptor.getName())
	persistent["craftedRecipes"][index] = RECIPE_REVEALED
	saveGame()

func isRecipeRevealed(itemName):
	var index = ItemBook.getItemIndex(itemName)
	return persistent["craftedRecipes"].get(index, 0) == RECIPE_REVEALED

func onCraftingReady(item):
	emit_signal("crafting_ready")

func isTutorialDone(step: int) -> bool:
	return (persistent["tutorial"] & step) > 0

func setTutorialDone(step: int):
	if persistent["tutorial"] & step == 0:
		persistent["tutorial"] |= step
		emit_signal("tutorial_done", step)

func getNextTutorialText():
	if getNumStartedRuns() > 10: return null
	
	for i in tutorialPriorities.size():
		currentTutorialStep += 1
		currentTutorialStep %= tutorialPriorities.size()
		var stepI = tutorialPriorities[currentTutorialStep]
		if not isTutorialDone(stepI):
			var stepName = tutorialEncodingToStep[stepI]
			var traKey = "TUTORIAL_" + stepName
			var formatParams = null
			var addController: = usingController
			var skip: = false
			
			if usingController:
				
				match stepI:
					TutorialSteps.Lock:
						formatParams = {"button": Util.getControllerIconBbcode("lock_combining_controller", 40)}
					TutorialSteps.Shift:
						pass
					TutorialSteps.Reserve:
						formatParams = {"uibutton": Util.getControllerIconBbcode("ui_accept"), 
						"reservebutton": Util.getControllerIconBbcode("reserve_controller")}
					TutorialSteps.Undo:
						skip = true
					TutorialSteps.ShowRecipes:
						skip = true
					TutorialSteps.SendToStorage:
						skip = true
					_:
						addController = false
			
			if skip: continue
			
			if addController:
				traKey += "_CONTROLLER"
			
			var translation: String = Util.tra(traKey)
			if translation != "":
				if formatParams != null:
					translation = translation.format(formatParams)
				
				return [translation, stepI]
	return null

func onDecorationDestructed():
	shopKeeper.onDecorationDestructed()
	SteamHelper.unlockAchievement("Destruct", true)



func changeArrowCursor(cursorTypeArrow):
	Input.set_custom_mouse_cursor(scaledCursors[cursorTypeArrow], 
		Input.CURSOR_ARROW, getCursorOffset(cursorTypeArrow))

func changeHandCursor(cursorTypeHand):
	Input.set_custom_mouse_cursor(scaledCursors[cursorTypeHand], 
	Input.CURSOR_POINTING_HAND, getCursorOffset(cursorTypeHand))

func changeVSizeCursor(cursorTypeVSize):
	Input.set_custom_mouse_cursor(scaledCursors[cursorTypeVSize], 
	Input.CURSOR_VSIZE, getCursorOffset(cursorTypeVSize))
	
func changeHSizeCursor(cursorTypeHSize):
	Input.set_custom_mouse_cursor(scaledCursors[cursorTypeHSize], 
	Input.CURSOR_HSIZE, getCursorOffset(cursorTypeHSize))

func getCursorOffset(cursorType) -> Vector2:
	return cursorOffsets[cursorType] * Settings.getVal(Settings.Setting.cursor_size)


func changeCursorSize(newSize: float):
	
	for i in cursors.size():

		var unscaledImg: Image = cursors[i]
		var scaledImgTex: ImageTexture = scaledCursors[i]
		var scaledImg: Image = scaledImgTex.get_data()
		scaledImg.copy_from(unscaledImg)
		
		scaledImg.resize(newSize * unscaledImg.get_width(), newSize * unscaledImg.get_height(), Image.INTERPOLATE_TRILINEAR)
		scaledCursors[i].create_from_image(scaledImg)
	recalculateCursor()




const hoverSound = preload("res://Assets/Sound/Click5.ogg")
const clickButtonSound = preload("res://Assets/Sound/Click3.wav")
var hoveredInteractable = null

func onHoverInteractable(control: Node):
	
	
	hoveredInteractable = control
	
	
	emit_signal("interactable_hovered")
	
	if Util.clockTime > hoverSoundReadyTime:
		
		Sound.playRising(hoverSound, - 6, 1, true)
		hoverSoundReadyTime = Util.clockTime + 0.1
	
	

func onHoverInteractableEnd(control):
	if hoveredInteractable == control:
		
		hoveredInteractable = null
	
	
	
	
	
	

func onClickButton():
	if Util.clockTime > 3.0:
		Sound.playSound_process(clickButtonSound, 3)

func recalculateCursor():
	if isWeb: return
	
	
	var cursorType = getCursorType()
	
	if lastCursorType == cursorType:
		return
	
	lastCursorType = cursorType
	
	if getSoftwareCursor():
		if softwareCursor == null:
			softwareCursor = softwareCursorScene.instance()
			add_child(softwareCursor)
			if not isWeb:
				Input.set_mouse_mode(Input.MOUSE_MODE_HIDDEN)
			
	else:
		if softwareCursor != null:
			softwareCursor.queue_free()
			softwareCursor = null
			Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
		
		if cursor == Cursor.HARDWARE_LARGE or cursor == Cursor.HARDWARE_SMALL:
			
				
			if Input.get_current_cursor_shape() == Input.CURSOR_ARROW:
				
				
				
				changeHandCursor(cursorType)
				changeArrowCursor(cursorType)
			elif Input.get_current_cursor_shape() == Input.CURSOR_VSIZE:
				changeArrowCursor(cursorType)
				changeVSizeCursor(cursorType)
			elif Input.get_current_cursor_shape() == Input.CURSOR_HSIZE:
				changeArrowCursor(cursorType)
				changeHSizeCursor(cursorType)
			else:
				changeArrowCursor(cursorType)
				changeHandCursor(cursorType)
			
		elif cursor == Cursor.DEFAULT:
			Input.set_custom_mouse_cursor(null, Input.CURSOR_ARROW)
			Input.set_custom_mouse_cursor(null, Input.CURSOR_POINTING_HAND)

func getCursorType():
	var cursorIndex = CursorTypes.DEFAULT
	
	if hoveredItems.empty() and not draggedItem:
		if Input.get_current_cursor_shape() == Input.CURSOR_VSIZE:
			if left_click:
				cursorIndex = CursorTypes.VSIZE_CLICKED
			else:
				cursorIndex = CursorTypes.VSIZE
		elif Input.get_current_cursor_shape() == Input.CURSOR_HSIZE:
			if left_click:
				cursorIndex = CursorTypes.HSIZE_CLICKED
			else:
				cursorIndex = CursorTypes.HSIZE
		elif Input.get_current_cursor_shape() == Input.CURSOR_POINTING_HAND:
			if left_click:
				cursorIndex = CursorTypes.CLICKABLE_CLICKED
			else:
				cursorIndex = CursorTypes.CLICKABLE
		else:
			if left_click:
				cursorIndex = CursorTypes.CLICKED
			else:
				cursorIndex = CursorTypes.DEFAULT
			
	else:
		if left_click:
			cursorIndex = CursorTypes.GRABBED
		else:
			cursorIndex = CursorTypes.GRABBABLE
		
	return cursorIndex
	
func _process(delta: float) -> void :
	recalculateCursor()

const CURSOR_SPEED = 600.0
const CONTROLLER_DEADZONE = 0.2

var warpTimestamp_rightStick: = 0
var warpTimestamp_dPad: = 0
var rightStickWarps: = 0
var cursorIsWarping: = false
const warpCDFrames_initial = 20
const warpCDFrames_rapid = 10


func _physics_process(delta):
	if usingController:
	
		var rightStickInput = Input.get_vector(
			"scroll_left", "scroll_right", 
			"scroll_up", "scroll_down")
		
		var rightStickInputLength = rightStickInput.length()
		
		if rightStickInputLength < 0.3:
			cursorIsWarping = false
			rightStickWarps = 0
			warpTimestamp_rightStick = 0
		
		elif rightStickInputLength > 0.5:
			cursorIsWarping = true
		
		if cursorIsWarping:
			if Engine.get_physics_frames() > warpTimestamp_rightStick:
				var hasWarped = warp(rightStickInput)
				if hasWarped:
					var cd = warpCDFrames_initial if rightStickWarps == 0 else warpCDFrames_rapid
					warpTimestamp_rightStick = Engine.get_physics_frames() + cd
					rightStickWarps += 1
			













		var leftStickInput = Input.get_vector(
			"move_cursor_left", "move_cursor_right", 
			"move_cursor_up", "move_cursor_down")



		
		if leftStickInput != Vector2.ZERO:
			if leftStickInput.length() > 0.99:
				leftStickInput *= 1.5
			moveMouse(1 / 60.0 * CURSOR_SPEED * leftStickInput * Settings.getVal(Settings.Setting.cursor_speed))
	
func getSoftwareCursor():
	return (cursor == Cursor.SOFTWARE_SMALL or 
			cursor == Cursor.SOFTWARE_LARGE or 
			SteamHelper.STEAMDECK)

const maxWarpAngle = deg2rad(50.0)
const cursorWarpTrail = preload("res://Interface/CursorWarpTrail.tscn")
var pointsOfInterest: Array
var pointsOfInterestInfo: Dictionary
var warpPointOcclusionRects: Array
const maxSliderSteps = 10



func addControlOfInterest(control: Control, offset: Vector2 = Vector2.ZERO, 
	scrollContainer = null, childToScrollTo = null, layer = 0):
	
	if control == null:
		Util.eassert()
		return
	
	if control is Slider:
		
		var basePos = control.rect_global_position
		basePos.x += control.margin
		basePos.y += control.rect_size.y * control.rect_scale.y * 0.5
		var sliderSteps = min(maxSliderSteps, (control.max_value - control.min_value) / control.step)
		var step = (control.rect_size.x * control.rect_scale.x - 2 * control.margin) / sliderSteps
		for i in sliderSteps + 1:
			addPointOfInterest(basePos + Vector2(step * i, 0), 
				scrollContainer, childToScrollTo, layer)
	else:
		addPointOfInterest(control.rect_global_position + (
			control.rect_size * 0.5 * control.rect_scale).rotated(deg2rad(control.rect_rotation)) + offset, 
			scrollContainer, childToScrollTo, layer)

func addPointOfInterest(pos: Vector2, scrollContainer = null, 
	childToScrollTo = null, layer = 0):
	
	for rect in warpPointOcclusionRects:
		if rect.layer >= layer and rect.rect.has_point(pos):
			return
	
	pointsOfInterest.push_back(pos)
	if scrollContainer != null:
		pointsOfInterestInfo[pointsOfInterest.size() - 1] = [scrollContainer, childToScrollTo]

func addItemOfInterest(item, layer = 0):
	if item.isBag() and item.placed and inventoryEditMode == InventoryEditMode.Default:
		var emptyPoints = item.getEmptyGlobalPositions()
		if not emptyPoints.empty():
			addPointOfInterest(emptyPoints[0], null, null, layer)
	else:
		addPointOfInterest(item.getGridStorageProxy().getLockPosition(), null, null, layer)

func addOcclusionRect(rect: OcclusionRect):
	warpPointOcclusionRects.push_back(rect)

func addOcclusion(topLeft: Vector2, size: Vector2, layer: int):
	warpPointOcclusionRects.push_back(OcclusionRect.new(topLeft, size, layer))

func connectToGetRectsSignals(receiver: Node, method: String):
	connect("get_rects_menu", receiver, method)
	connect("get_rects_shop", receiver, method)
	connect("get_rects_combat", receiver, method)
	connect("get_rects_title", receiver, method)

func connectToWarpCursorSignals(receiver: Node, method: String):
	connect("warp_cursor_menu", receiver, method)
	connect("warp_cursor_shop", receiver, method)
	connect("warp_cursor_combat", receiver, method)
	connect("warp_cursor_title", receiver, method)

func warp(input):
	warpPointOcclusionRects.clear()
	
	if isMenuOpen():
		emit_signal("get_rects_menu")
	elif state == State.Shop:
		emit_signal("get_rects_shop")
	elif state == State.Title:
		emit_signal("get_rects_title")
	elif state == State.Combat:
		emit_signal("get_rects_combat")
	
	pointsOfInterest.clear()
	pointsOfInterestInfo.clear()
	
	if isMenuOpen():
		emit_signal("warp_cursor_menu")
	
	elif state == State.Shop:
		var inv = PLAYER.INVENTORY
		if draggedItem != null:
			addPointOfInterest(STORAGEBOX.center + Vector2(0, 50))
			addPointOfInterest(STORAGEBOX.center - Vector2(0, 150))
			
			if draggedItem.canBeSold():
				addPointOfInterest(SELLBOX.global_position - Vector2(80, 120))
			
			if draggedItem.ownerType == Item.Owner.Shop:
				addPointOfInterest(draggedItem.pickupPosition)
			
			var oldPos = draggedItem.global_position
			var offset = oldPos - draggedItem.getTopLeftGlobal() - draggedItem.halfCellSize
			
			if draggedItem.isBag():
				for cell in inv.inventoryCells:
					inv.orientItem(draggedItem, cell, draggedItem.faceDirection)
					if inv.canAddBag(draggedItem, false):
						var cellPos = inv.cellToGlobalPos(cell, true)
						addPointOfInterest(cellPos + offset)
			else:
				var checkBags = (inventoryEditMode != InventoryEditMode.ItemLayer)
				
				
				for cell in inv.inventoryCells:
					inv.orientItem(draggedItem, cell, draggedItem.faceDirection)
					if inv.canAddItem(draggedItem, false, checkBags):
						var cellPos = inv.cellToGlobalPos(cell, true)
						addPointOfInterest(cellPos + offset)
				
				if draggedItem.isGem():
					for item in inv.getItems():
						for socket in item.sockets:
							addPointOfInterest(socket.global_position)
					if not gridStorage.visible:
						for item in STORAGEBOX.getItems():
							for socket in item.sockets:
								addPointOfInterest(socket.global_position)
			
			draggedItem.global_position = oldPos
		else:
			for item in ItemBook.getInventoryStorageShopItems():
				if inventoryEditMode == InventoryEditMode.ItemLayer:
					if item.isBag(): continue
				elif inventoryEditMode == InventoryEditMode.BagLayer:
					if not item.isBag(): continue
				
				addItemOfInterest(item)
			
			addControlOfInterest(versionButton, Vector2(50, 0))
			
			emit_signal("warp_cursor_shop")
	
	elif state == State.Title:
		for item in PLAYER.INVENTORY.getItemsAndGems():
			addItemOfInterest(item)
		
		emit_signal("warp_cursor_title")
	
	elif state == State.Combat:
		emit_signal("warp_cursor_combat")
	
	var curMousePos = get_global_mouse_position()
	var target: Vector2 = Vector2(960, 540)
	var bestScore: float = - INF
	var anglePunishmentFactor: = 2.0
	var targetIndex: = - 1
	var inputDir = input.normalized()
	
	for i in pointsOfInterest.size():
		var point = pointsOfInterest[i]
		var dif = point - curMousePos
		var dist = dif.length()
		if dist < 15:
			continue
		
		var angle = abs(dif.normalized().angle_to(inputDir))
		if angle > maxWarpAngle:
			continue
		
		
		var score = - (1 + (angle * anglePunishmentFactor) / maxWarpAngle)
		score *= dist
		
		if score > bestScore:
			target = point
			targetIndex = i
			bestScore = score
	
	if bestScore > - INF:
		if targetIndex in pointsOfInterestInfo:
			var info = pointsOfInterestInfo[targetIndex]
			var compensation = ensureScrollVisibility(
					info[0], info[1])
			target.y += compensation
		
		moveMouseTo(target)
		
		var trail = ObjectPool.instance(cursorWarpTrail)
		UINode.add_child(trail)
		trail.setPoints(curMousePos, target)
		return true
	return false

func ensureScrollVisibility(scrollContainer: ScrollContainer, child):
	var scrollBefore = scrollContainer.scroll_vertical
	
	if child is Control:
		scrollContainer.ensure_control_visible(child)
	
	elif child is Item:
		var rect = scrollContainer.get_global_rect()
		var containerTop = rect.position.y
		var containerBottom = rect.end.y
		var itemHeightRange = child.getHeightRange()
		var scroll = 0
		if itemHeightRange.x < containerTop:
			scroll = itemHeightRange.x - containerTop
		elif itemHeightRange.y > containerBottom:
			scroll = itemHeightRange.y - containerBottom
		scrollContainer.scroll_vertical += scroll
	
	var scrollAfter = scrollContainer.scroll_vertical
	return scrollBefore - scrollAfter

func setLocale(locale):
	print("SETTING LOCALE TO ", locale)
	TranslationServer.set_locale(locale)
	
	Util.updateLocale()
	updateLocale()

func updateLocale():
	var localizedNodes = get_tree().get_nodes_in_group("Localized")
	for node in localizedNodes:
		node.updateLocale()
	
	itemLibrary.updateSearchDescriptions()
	
	

func initLocale():
	setLocale(getConfigValue("Options", "language", getDefaultLocale()))

	
func setConfigValue(groupName, propertyName, propertyValue):
	var config = ConfigFile.new()
	var configPath = getSavePath(config_format)
	var err = config.load(configPath)
	
	config.set_value(groupName, propertyName, propertyValue)
	config.save(configPath)

func eraseConfigValue(groupName, propertyName):
	var config = ConfigFile.new()
	var configPath = getSavePath(config_format)
	var err = config.load(configPath)
	
	if config.has_section_key(groupName, propertyName):
		config.erase_section_key(groupName, propertyName)
		config.save(configPath)


func getConfigValue(groupName, propertyName, defaultValue):
	var config = ConfigFile.new()
	var configPath = getLoadPath(config_format)
	var err = config.load(configPath)
	if err != OK:
		return defaultValue
	
	if config.has_section_key(groupName, propertyName):
		return config.get_value(groupName, propertyName, defaultValue)
	else:
		return defaultValue
	
func applySetSkins():
	for slot in SkinSlot.size():
		PLAYER.sprite.setSkin(slot, getSelectedSkin(slot))

func setShowChibis(showChibis):
	if not showChibis:
		if getChibiMode():
			PLAYER.setSprite(classResources[curClass], false)
			emit_signal("style_changed")
	else:
		if getChibiMode():
			PLAYER.setSprite(classResources[curClass], true)
			emit_signal("style_changed")
	
	applySetSkins()
	emit_signal("chibi_setting_changed")

func getEffectiveChibiMode() -> bool:
	return getChibiMode() and getShowChibis()

func getShowChibis():
	return Settings.getVal(Settings.Setting.opponent_chibis)

func setChibiMode(_chibiMode):
	if chibiMode[curClass] == _chibiMode: return
	
	setConfigValue("Options", "Chibi_" + getClassInternalName(), _chibiMode)
	chibiMode[curClass] = _chibiMode
	PLAYER.setSprite(classResources[curClass], chibiMode[curClass])
	emit_signal("style_changed")

func getChibiMode():
	return chibiMode[curClass]

func getStacks() -> Array:
	return [EventType.Block] + getBuffs() + getDebuffs()


func getBuffs() -> Array:
	return range(EventType.Lucky, EventType.Heat + 1)

func getDebuffs() -> Array:
	return range(EventType.Poison, EventType.Cold + 1)
	

func isBuff(_type):
	return _type >= EventType.Block and _type <= EventType.Heat

func isDebuff(_type):
	return _type >= EventType.Poison and _type <= EventType.Cold

func isStack(_type):
	return _type >= EventType.Block and _type <= EventType.Cold

func typeToKeyword(_type):
	if _type == EventType.Block:
		return "bl"
	elif _type == EventType.Regeneration:
		return "regen"
	else:
		return eventTypeKeys[_type].to_lower()

func getDefaultLocale():
	if (SteamHelper.is_init() and 
		SteamHelper.LOCALE in localeToLanguage):
		return SteamHelper.LOCALE
	else:
		var osLocale = OS.get_locale_language()
		if osLocale in localeToLanguage:
			return osLocale
	
	return "en"

func showSockets():
	var sockets = get_tree().get_nodes_in_group("Socket")
	for s in sockets:
		s.showSocket()

func hideSockets():
	
	var sockets = get_tree().get_nodes_in_group("Socket")
	for s in sockets:
		s.hideSocket()

func getSkinConfigKey(slot: int, charClass = curClass, chibi = getEffectiveChibiMode()):
	var key = getClassKeys()[charClass]
	if chibi:
		key += "_Chibi_"
	else:
		key += "_Normal_"
	key += SkinSlot.keys()[slot]
	return key

func getSelectedSkin(slot):
	var key = getSkinConfigKey(slot)
	var configuredSkin = getConfigValue("Wardrobe", key, 0)
	if isSkinAvailable(configuredSkin):
		if isSkinUnlocked(slot, configuredSkin):
			return configuredSkin
	
	return 0

func selectSkin(slot, skinId):
	var key = getSkinConfigKey(slot)
	setConfigValue("Wardrobe", key, skinId)

func getSkinUnlockKey(slot: int, charClass = curClass, chibi = getEffectiveChibiMode()):
	var key = String(charClass) + "_"
	key += String(int(chibi)) + "_"
	key += String(slot)
	return key

func isSkinAvailable(skinId: int) -> bool:
	var numSkins = SkinBook.getNumSkinsForClass(curClass, int(getEffectiveChibiMode()))
	return skinId < numSkins

func isSkinUnlocked(slot: int, skinId: int):
	var skin = SkinBook.getSkinFromId(curClass, int(getEffectiveChibiMode()), skinId)
	if skin.prices[slot] == 0:
		return true
	
	
	var key = getSkinUnlockKey(slot)
	var unlocked = persistent["unlockedSkins"].get(key, [])
	return skinId in unlocked

func unlockSkin(slot: int, skinId: int):
	var key = getSkinUnlockKey(slot)
	var unlocked = persistent["unlockedSkins"].get(key, [])
	unlocked.push_back(skinId)
	persistent["unlockedSkins"][key] = unlocked
	saveGame()
	SteamHelper.unlockAchievement("OutfitUnlocked", true)

func getStatisticsKey(statistic: int) -> String:
	return "Stat" + String(statistic)

func getItemStatistics(statistic: int, descriptor: ItemDescriptor, default = null):
	if not ITEM_STATISTICS_ENABLED: return null
	var key = getStatisticsKey(statistic)
	var value = persistent[key][descriptor.getIndex()]
	if value == null:
		return default
	return value

func setItemStatistic(statistic: int, descriptor: ItemDescriptor, newValue):
	if not ITEM_STATISTICS_ENABLED: return
	var key = getStatisticsKey(statistic)
	persistent[key][descriptor.getIndex()] = newValue

func incrementItemStatistic(statistic: int, descriptor: ItemDescriptor, increment = 1):
	if not ITEM_STATISTICS_ENABLED: return
	
	
	var key = getStatisticsKey(statistic)
	var value = persistent[key][descriptor.getIndex()]
	var newValue = increment if value == null else value + increment
	persistent[key][descriptor.getIndex()] = newValue
	
	if statistic in statisticIncrements and value != null:
		var sIncrement = statisticIncrements[statistic]
		var before: int = value / sIncrement
		var after: int = newValue / sIncrement
		if after > before:
			addRecord(statistic, descriptor, after * sIncrement)
	
	return newValue

func addRecord(statistic: int, descriptor: ItemDescriptor, amount: int = 0):
	if not ITEM_STATISTICS_ENABLED: return
	
	
	var runState = getRunState()
	var recordQueue = runState.get("rq", [])
	recordQueue.push_back([descriptor.itemIndex, statistic, amount])
	runState["rq"] = recordQueue

func getRecordQueue():
	var runState = getRunState()
	return runState.get("rq", [])

func clearRecordQueue():
	var runState = getRunState()
	runState["rq"] = []

func showWarning(textKey, confirmKey, cancelKey):
	if warning == null:
		warning = load("res://Interface/BoughtNothingWarning.tscn").instance()
	
	if not warning.is_inside_tree():
		warning.open(textKey, confirmKey, cancelKey)

func onPatchNotesClosed():
	if PLAYTEST: return
	if not "version" in persistent: return
	
	if versionToInt(persistent["version"]) < versionToInt("1.0.0"):
		if hasPlayedInSeason("1"):
			var popup = rankSeason2Popup.instance()
			UINode.add_child(popup)
	elif versionToInt(persistent["version"]) < versionToInt("1.1.0"):
		if hasPlayedInSeason("2"):
			var popup = rankSeason3Popup.instance()
			UINode.add_child(popup)

func fuseAll():
	InputBlocker.activate(InputBlocker.Source.Fusing)
	Util.callDelayed(self, "onCraftingTimeout", Item.PRE_FUSE_DUR_COG + Item.FUSE_DUR)
	
	var playerItems = PLAYER.INVENTORY.getItemsAndGems()
	for item in playerItems:
		item.addToCraftingQueue()
	
	
	sortedCraftingPriorities = Util.sortDict(craftingPriorities)
	
	for item in sortedCraftingPriorities:
		item.startFusing_inShop()
	
	craftingPriorities.clear()


func checkForInventoryAchievements():
	var dragons: = {}
	var bows: = {}
	var books: = {}
	var classes: = 0
	var numBattleRage = 0
	var numPotions: = 0
	var numVampiric: = 0
	var numFood: = 0
	var numMagic: = 0
	var numStaminaWeapons: = 0
	var numGemstones: = 0
	var numPiggies: = 0
	var numAmulets: = 0
	
	for item in PLAYER.INVENTORY.getItems():
		if item.hasTag(Item.Tag.Dragon):
			Util.dictAdd(dragons, item.descriptor)
		
		if item.hasTag(Item.Tag.Bow):
			Util.dictAdd(bows, item.descriptor)
		
		if item.hasType(Item.Type.Book):
			Util.dictAdd(books, item.descriptor)
		
		if item.isBattleRageItem():
			numBattleRage += 1
		
		if item.hasType(Item.Type.Potion):
			numPotions += 1
		
		if item.hasType(Item.Type.Vampiric):
			numVampiric += 1
		
		if item.hasType(Item.Type.Food):
			numFood += 1
		
		if item.hasType(Item.Type.Magic):
			numMagic += 1
		
		if item.isWeapon() and item.canUseStamina():
			numStaminaWeapons += 1
		
		if item.descriptor.gateItem == ItemBook.amuletDescriptor:
			numAmulets += 1
		
		if item.descriptor in ItemBook.piggies:
			numPiggies += 1

		if item.descriptor.isClassItem():
			classes |= item.descriptor.classes
	
	for item in PLAYER.INVENTORY.getItemsAndGems():
		if item.isGem():
			numGemstones += 1
	
	if dragons.size() >= 4:
		SteamHelper.unlockAchievement("Dragons")
	
	if bows.size() >= 3:
		SteamHelper.unlockAchievement("Bows")
	
	if numBattleRage >= 8:
		SteamHelper.unlockAchievement("BattleRage")
	
	if books.size() >= 4:
		SteamHelper.unlockAchievement("Books")
	
	if Util.countOnes(classes, Classes_Full.size()) >= 4:
		SteamHelper.unlockAchievement("MixedClasses")
	
	if numPotions >= 6:
		SteamHelper.unlockAchievement("Potions")
	
	if numVampiric >= 8:
		SteamHelper.unlockAchievement("Vampire")
	
	if numFood >= 8:
		SteamHelper.unlockAchievement("Food")
	
	if numMagic >= 8:
		SteamHelper.unlockAchievement("Magic")
	
	if numStaminaWeapons >= 4:
		SteamHelper.unlockAchievement("ManyWeapons")
	
	if numAmulets >= 5:
		SteamHelper.unlockAchievement("Amulets")
	
	if numPiggies >= 5:
		SteamHelper.unlockAchievement("Piggies")
	
	if numGemstones >= 10:
		SteamHelper.unlockAchievement("Gems")
	
	var deckArr = ItemBook.getItemsInInventoryOfType(ItemBook.deckOfCardsDescriptor)
	if deckArr.size() == 1:
		if deckArr[0].cards.size() >= 8:
			SteamHelper.unlockAchievement("Cards")
	
	if ItemBook.getNumInventoryUniques() >= 3:
		SteamHelper.unlockAchievement("Treasure")


func writeoutState():
	if not WRITE_OUT_STATE:
		return
	
	var locale = TranslationServer.get_locale()
	if locale != "en":
		TranslationServer.set_locale("en")
	
	var json = {}
	json["inventory"] = []
	for item in PLAYER.INVENTORY.getItems():
		var entry = [item.getTranslatedName(), item.occupiedCells]
		json["inventory"].push_back(entry)
	
	if state == State.Shop:
		json["shop"] = []
		for item in shopSceneNode.getItems():
			if item == null:
				json["shop"].push_back("")
			else:
				json["shop"].push_back(item.getTranslatedName())
	elif state == State.Combat:
		json["opponent"] = []
		for item in OPPONENT.INVENTORY.getItems():
			var entry = [item.getTranslatedName(), item.occupiedCells]
			json["opponent"].push_back(entry)
	json["timestamp"] = Util.getFrameCounter_process()
	
	var file = File.new()
	var err = file.open("user://state.json", File.WRITE)
	if err == OK:
		file.store_string(to_json(json))
		file.close()
	else:
		print(err)
	
	if locale != "en":
		TranslationServer.set_locale(locale)



















var audioMutedBeforeFocusLost = false

func _notification(what: int) -> void :
	
	if what == MainLoop.NOTIFICATION_WM_FOCUS_OUT:
		clearAffectedLines()
		itemLibrary.hideRecordIcons()
		
		if lockedTooltipItem == null:
			showHintsIsPressed = false
			
			var focusItem = getFocusItem()
			if focusItem != null:
				focusItem.hideBuildIntoRecipesTooltip()
				focusItem.clearCanAffectVisuals()
		
		if Settings.getVal(Settings.Setting.reduce_fps_unfocused):
			OS.low_processor_usage_mode = true
			Engine.set_target_fps(20)
		
		if Settings.getVal(Settings.Setting.mute_unfocused):
			audioMutedBeforeFocusLost = AudioServer.is_bus_mute(Sound.MASTER_BUS)
			AudioServer.set_bus_mute(Sound.MASTER_BUS, true)
		
		if useShell():
			processTimer.start(Util.rng.randf_range(10, 30))

	elif what == MainLoop.NOTIFICATION_WM_FOCUS_IN:
		set_deferred("showHintsIsPressed", false)
		
		if Settings.getVal(Settings.Setting.reduce_fps_unfocused):
			OS.low_processor_usage_mode = false
			Engine.set_target_fps(Settings.getVal(Settings.Setting.fps_limit))
		
		if Settings.getVal(Settings.Setting.mute_unfocused):
			AudioServer.set_bus_mute(Sound.MASTER_BUS, audioMutedBeforeFocusLost)
		
		if useShell():
			processTimer.stop()
			checkProcesses_threaded()
			
	
	elif what == MainLoop.NOTIFICATION_WM_QUIT_REQUEST:
		saveWindowSettings()

func useShell():
	return not EDITOR

func saveWindowSettings():
	if not OS.window_fullscreen:
		var windowPos = OS.window_position
		var windowSize = OS.window_size
		var screen = OS.current_screen
		setConfigValue("Options", "window_position", windowPos)
		setConfigValue("Options", "window_size", windowSize)
		setConfigValue("Options", "screen", screen)


func quit():
	saveWindowSettings()
	get_tree().quit()

func joinProcessThread():
	processThread.wait_to_finish()

func checkProcesses_cyclic():
	checkProcesses_threaded()
	processTimer.start(Util.rng.randf_range(10, 30))

func checkProcesses_threaded():
	if OS.get_name() == "Windows":
		if processThread and processThread.is_active():
			return
		processThread = Thread.new()
		processThread.start(self, "checkProcesses")

func checkProcesses() -> bool:
	var output = []
	
	
	OS.execute("powershell.exe", ["/C", "get-process | Select-Object ProcessName, mainwindowtitle"], true, output)
	if output.empty() or output[0] == "":
		
		return false
	
	var foundProcess = false
	foundProcess = output[0].findn("cheatengine") != - 1
	if not foundProcess:
		foundProcess = output[0].findn("cheat engine") != - 1
	
	if foundProcess:
		print("ERROR_16")
		get_tree().quit()
	
	call_deferred("joinProcessThread")
	return foundProcess

class ItemSort:
	static func sort_HoverPriority(item1: Item, item2: Item):
		return item1.getHoverPriority() > item2.getHoverPriority()
	
	static func sort_ShopPriority(item1: Item, item2: Item):
		return item1.getShopPriority() > item2.getShopPriority()
	

	static func sort_TriggerPriority(item1: Item, item2: Item):
		return item1.getTriggerPriority() > item2.getTriggerPriority()

	static func sort_BagOrder(item1: Dictionary, item2: Dictionary):
		return int(item1["d"].isBag()) > int(item2["d"].isBag())

class LineSort:
	static func sort(line1, line2):
		return line1.getLength() > line2.getLength()

class OcclusionRect:
	var rect: Rect2
	var layer: int
	
	func _init(_topLeft: Vector2, _size: Vector2, _layer: int):
		rect = Rect2(_topLeft, _size)
		layer = _layer
