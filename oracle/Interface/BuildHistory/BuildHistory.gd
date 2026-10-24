extends Node2D

const placeholderScene = preload("res://Interface/BuildHistory/BuildEntryPlaceholder.tscn")
const OpponentPoolAdapter = preload("res://Interface/BuildHistory/OpponentPoolAdapter.gd")
const ENCODE_URL = "http://8.153.197.44:7296/encode"
const DECODE_URL = "http://8.153.197.44:7296/decode"
const MODE_FILTER_OPPONENT_POOL: = 5

onready var animation = $AnimationPlayer
onready var scrollContainer = $ScrollContainer
onready var entryContainer = $ScrollContainer / VBoxContainer
onready var inventory = $Build / Items / Inventory
onready var itemsNode = $Build / Items
onready var roundLabel = $Build / Round
onready var cursor = $ScrollContainer / VBoxContainer / Cursor
onready var opponentMark = $ScrollContainer / VBoxContainer / OpponentMark
onready var goldValueLabel = $Build / GoldValue
onready var itemNumLabel = $Build / ItemNumber
onready var statusFeedbackLabel = $Build / StatusFeedback
onready var buildNode = $Build
onready var fightButton = $Build / FightButton
onready var fightWithClipboardButton = $CopyBuildUI / FightWithClipBoardButton
onready var copyBuildButton = $CopyBuildUI / CopyBuildButton
onready var copyPopUI = $CopyBuildUI / CopyPopUI
onready var copyBuildString = $CopyBuildUI / CopyPopUI / BuildString
onready var copyPopHeader = $CopyBuildUI / CopyPopUI / Header
onready var fightPopUI = $CopyBuildUI / FightPopUI
onready var fightInput = $CopyBuildUI / FightPopUI / TextEdit
onready var fightPopHeader = $CopyBuildUI / FightPopUI / Header
onready var fightPopFightButton = $CopyBuildUI / FightPopUI / FightButton
onready var fightPopPasteHint = $CopyBuildUI / FightPopUI / PasteHint
onready var tutorialAni = $Build / AnimationPlayer
onready var classList = $Filter / Classes
onready var modeList = $Filter / Modes
onready var resetFilterButton = $Filter / ResetFilters
onready var searchbar = $Searchbar
onready var emptyHint = $Empty
onready var closeButton = $CloseButton
onready var previousRoundButton = $Build / PreviousRound
onready var nextRoundButton = $Build / NextRound

var isOpen = false
var entries: Array
var curRoundNum: int
var curData = null
var curRunId: int
var fighting: = false
var activeEntry = null
var hasFought: = false
var classFilter: int = - 1
var modeFilter: int = - 1
var buildAniTween: SceneTreeTween
var feedbackTween: SceneTreeTween
var refreshing: bool = false
var suppressModeSelectionCallback: bool = false
var historyModeFilterBeforeOpponentPool: int = - 1
var statusFeedbackTimer: Timer
var searchDebounceTimer: Timer

var markedOpponentData = null
var markedOpponentRound = - 1
var opponentPoolData: Array = []
var searchTerm: String = ""
var pendingSearchTerm: String = ""

func _ready():
	Game.connect("warp_cursor_menu", self, "onCursorWarp")
	
	$ScrollContainer / VBoxContainer / BuildEntry.queue_free()
	
	var scrollBar = scrollContainer.get_v_scrollbar()
	scrollBar.connect("visibility_changed", self, "onScrollbarVisibilityChanged")
	
	opponentMark.hide()
	if is_instance_valid(copyPopUI):
		copyPopUI.visible = false
	if is_instance_valid(fightPopUI):
		fightPopUI.visible = false
	if is_instance_valid(statusFeedbackLabel):
		statusFeedbackLabel.visible = false
		statusFeedbackLabel.modulate = Color(1, 1, 1, 1)
	if is_instance_valid(searchbar):
		searchbar.visible = false
		searchbar.text = ""
	updateCopyPopupTexts()
	updateCopyBuildButtonState()
	if is_instance_valid(fightPopFightButton):
		fightPopFightButton.connect("hover_start", self, "onFightButtonHoverStart")
		fightPopFightButton.connect("hover_end", self, "onFightButtonHoverEnd")

	searchDebounceTimer = Timer.new()
	searchDebounceTimer.one_shot = true
	searchDebounceTimer.wait_time = 1.0
	add_child(searchDebounceTimer)
	searchDebounceTimer.connect("timeout", self, "_onSearchDebounceTimeout")

	statusFeedbackTimer = Timer.new()
	statusFeedbackTimer.one_shot = true
	add_child(statusFeedbackTimer)
	statusFeedbackTimer.connect("timeout", self, "_onStatusFeedbackTimeout")
	
	add_to_group("Localized")
	_updateOpponentPoolSearchbar()
	updateLocale()

func clear():
	for entry in entries:
		entry.returnToObjectPool()
	entries.clear()
	curData = null
	activeEntry = null
	inventory.reset()
	resetOpponentMark()
	updateCopyBuildButtonState()
	if is_instance_valid(copyPopUI):
		copyPopUI.visible = false
	if is_instance_valid(fightPopUI):
		fightPopUI.visible = false
	if is_instance_valid(statusFeedbackLabel):
		statusFeedbackLabel.visible = false
		statusFeedbackLabel.modulate = Color(1, 1, 1, 1)
	if is_instance_valid(statusFeedbackTimer):
		statusFeedbackTimer.stop()
	if is_instance_valid(searchDebounceTimer):
		searchDebounceTimer.stop()

func open(fromCombat = false):
	if not Game.draggedItem and not is_inside_tree():
		Game.UINode.add_child_below_node(Game.UINode.get_node("BuildHistoryPlaceholder"), self)
		isOpen = true
		
		Game.pause(Game.PauseSource.RecipeBook)
		Sound.playSound_process(Game.transitionSounds[2], 0, 0.9)
		
		
		
		animation.play("Open")
		InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.shopSceneNode)
		InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.playerNode)
		InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.titleScreen)
		for node in get_tree().get_nodes_in_group("PinnedControl"):
			InputBlocker.disableSingleControl(InputBlocker.Source.Popup, node)
		
		InputBlocker.activate(InputBlocker.Source.PopupAnimation, false)
		
		SteamHelper.updateRichPresence()
		
		hasFought = fromCombat
		
		if fromCombat:
			SteamHelper.unlockAchievement("HistoryMatch", true)
			Sound.playBGM(Sound.titleBGM, 0, 0)
		
		fightButton.disabled = Game.isOtherModesUIOpen()
		updateCopyPopupTexts()
		updateCopyBuildButtonState()
		
		if ( not fightButton.disabled and 
			Game.getNumStartedRuns() > 4 and 
			Game.getNumStartedRuns() < 10 and 
			not Game.isTutorialDone(Game.TutorialSteps.HistoryFight)):
		
			tutorialAni.play("Tutorial")
		
		
		modeFilter = - 1
		historyModeFilterBeforeOpponentPool = - 1
		_syncModeListSelection()
		_updateOpponentPoolSearchbar()
		addEntries()

func addEntries():
	if modeFilter == MODE_FILTER_OPPONENT_POOL:
		if _isOpponentPoolPermitted():
			_addOpponentPoolEntries()
			return
		modeFilter = - 1
		_syncModeListSelection()
	
	var runHistory = Game.buildHistoryDB.readRunHistory()
	if not runHistory.empty():
		
		var runIDs: Array = runHistory.keys()
		runIDs.sort()
		runIDs.invert()
		
		var entryIndex = 0
		for i in 1:
			for runID in runIDs:
				var run: BuildHistoryData = runHistory[runID]
				var numRounds = run.getRounds()
				if numRounds == 0 or not run.isValid():
					continue
				
				if classFilter != - 1 and run.classI != classFilter:
					continue
				
				if modeFilter != - 1:
					if modeFilter == Game.Mode.Ranked:
						if run.mode != Game.Mode.Ranked or run.customRules != "":
							continue
					elif modeFilter == Game.Mode.Unranked:
						if run.mode != Game.Mode.Unranked or run.customRules != "":
							continue
					elif modeFilter == 3:
						if run.customRules == "":
							continue
					else:
						if run.mode != modeFilter:
							continue
				
				var entry = ObjectPool.instance(placeholderScene)
				entryContainer.add_child(entry)
				entry.setHistoryData(run, entryIndex)
				entries.push_back(entry)
				entryIndex += 1
				
				if run.id == curRunId:
					if fighting:
						fighting = false
					updateBuild(curRoundNum, entry)
			
			if curData == null and not entries.empty():
				updateBuild(entries[0].data.getRounds(), entries[0])
			








	
	emptyHint.hide()
	if not entries.empty():
		buildNode.show()
		cursor.show()
		
	else:
		buildNode.hide()
		cursor.hide()
		if not runHistory.empty():
			emptyHint.show()
	
	Util.updateLocaleInSubtree(self)

func _addOpponentPoolEntries():
	opponentPoolData.clear()
	var sourceRuns = RunDatabase.getParsedRuns()
	if not sourceRuns.empty():
		var sortedRuns = sourceRuns.duplicate()
		sortedRuns.sort_custom(OpponentSorter, "sort_by_rating")
		var entryIndex = 0
		for i in sortedRuns.size():
			var run = sortedRuns[i]
			if run.getNumRounds() == 0:
				continue
			if classFilter != - 1 and run.characterClass != classFilter:
				continue
			if searchTerm != "":
				var playerName = Util.sharedBitstream.deserializeString(run.encodedName).to_lower()
				if playerName.findn(searchTerm) == - 1:
					continue

			var adapter = OpponentPoolAdapter.new(run, i)
			opponentPoolData.push_back(adapter)

			var entry = ObjectPool.instance(placeholderScene)
			entryContainer.add_child(entry)
			entry.setHistoryData(adapter, entryIndex)
			entries.push_back(entry)
			entryIndex += 1

			if adapter.id == curRunId:
				if fighting:
					fighting = false
				updateBuild(curRoundNum, entry)

		if curData == null and not entries.empty():
			updateBuild(entries[0].data.getRounds(), entries[0])

	emptyHint.hide()
	if not entries.empty():
		buildNode.show()
		cursor.show()
	else:
		buildNode.hide()
		cursor.hide()
		if not sourceRuns.empty():
			emptyHint.show()

	Util.updateLocaleInSubtree(self)

class OpponentSorter:
	static func sort_by_rating(a: RunData, b: RunData):
		return a.rating > b.rating


func opened():
	InputBlocker.deactivate(InputBlocker.Source.PopupAnimation, false)
	Game.openedMenu()
	Game.endHistoryRun()

func close(fight = false):
	animation.play("Close")
	Game.unhoverAndHideTooltips()
	Game.closeMenu()
	InputBlocker.activate(InputBlocker.Source.PopupAnimation, false)
	Sound.playSound_process(Game.transitionSounds[1], 0, 1.2)
	Game.unpause(Game.PauseSource.RecipeBook)
	if not fight and hasFought:
		Game.emit_signal("return_to_title")

func closed():
	InputBlocker.deactivate(InputBlocker.Source.PopupAnimation, false)
	InputBlocker.restoreAllControls(InputBlocker.Source.Popup)
	isOpen = false
	clear()
	get_parent().remove_child(self)
	SteamHelper.updateRichPresence()

func setOpponentMark(roundNum: int, buildEntry):
	if markedOpponentData == buildEntry.data and markedOpponentRound == roundNum:
		resetOpponentMark()
	else:
		markedOpponentData = buildEntry.data
		markedOpponentRound = roundNum
		opponentMark.show()
		opponentMark.global_position = buildEntry.roundButtons[roundNum - 1].rect_global_position + Vector2(10, 40)
		fightButton.modulate = Color(2, 1, 1)


func updateBuild(roundNum: int, buildEntry):
	if curRoundNum == roundNum and activeEntry == buildEntry:
		return
	
	curRunId = buildEntry.data.id
	buildEntry.initEntry()
	
	if activeEntry != null:
		activeEntry.entry.unselect()
	
	var sameEntry = activeEntry == buildEntry
	
	activeEntry = buildEntry
	activeEntry.entry.select()
	
	buildAniTween = Util.refreshTween(buildAniTween)
	buildAniTween.set_parallel()
	
	buildAniTween.tween_property(inventory, "position:y", inventory.position.y, 0.001)
	
	curData = buildEntry.data
	curRoundNum = roundNum
	
	roundLabel.translationKey = "UI_RoundCounter"
	roundLabel.formatParams = {"cur": roundNum, "max": curData.getRounds()}
	roundLabel.updateLocale()
	var items = curData.getRoundData(roundNum).items
	var itemDict = RunData.deserializeItems(items, curData.getVersionString())
	
	var itemsBefore: = {}
	if sameEntry:
		for item in inventory.getItems():
			
			Util.dictAppend(itemsBefore, item.getTopLeftCell(), 
				[item.descriptor, item.faceDirection])
	
	inventory.createFromItemTuples(itemDict["items"], Item.Owner.BuildViewer)
	
	
	var allItems = inventory.getItemsAndGems()
	var descriptorCounter: = {}
	for item in allItems:
		item.initBuildViewer()
		descriptorCounter[item.descriptor] = true
		if not item.isGem():
			var previousState = itemsBefore.get(item.getTopLeftCell(), [])
			var playAni = true
			for tuple in previousState:
				if (tuple[0] == item.descriptor and 
					tuple[1] == item.faceDirection):
					playAni = false
					break
			
			if playAni:
				addAni(item, item.isBag())
		
	
	
	goldValueLabel.formatParams = {"gold": inventory.countGold(), "icon": Util.getIcon("gold")}
	goldValueLabel.updateLocale()
	
	itemNumLabel.formatParams = {"items": allItems.size(), "types": descriptorCounter.size()}
	itemNumLabel.updateLocale()
	
	Util.callNextFrame(self, "scrollToEntry")
	updateCopyBuildButtonState()

func updateCopyPopupTexts():
	var loc = TranslationServer.get_locale().to_lower()
	var isChinese = loc.begins_with("zh")
	if is_instance_valid(copyPopHeader):
		copyPopHeader.translationKey = ""
		copyPopHeader.text = "阵容码" if isChinese else "Build Code"
	if is_instance_valid(fightPopHeader):
		fightPopHeader.translationKey = ""
		fightPopHeader.text = "开斗！" if isChinese else "Fight Rivals"
	if is_instance_valid(fightPopPasteHint):
		fightPopPasteHint.translationKey = ""
		fightPopPasteHint.text = "输入阵容码" if isChinese else "Enter Code"

func onFightButtonHoverStart():
	if has_node("CopyBuildUI/FightPopUI/PasteHint"):
		$CopyBuildUI / FightPopUI / PasteHint.hide()

func onFightButtonHoverEnd():
	if has_node("CopyBuildUI/FightPopUI/PasteHint"):
		$CopyBuildUI / FightPopUI / PasteHint.show()

func updateCopyBuildButtonState():
	var disabled = curData == null
	if is_instance_valid(copyBuildButton):
		copyBuildButton.disabled = disabled
	if is_instance_valid(fightWithClipboardButton):
		fightWithClipboardButton.disabled = Game.isOtherModesUIOpen() or disabled
	if is_instance_valid(fightPopFightButton):
		fightPopFightButton.disabled = Game.isOtherModesUIOpen() or disabled

func scrollToEntry():
	Util.callNextFrame(self, "scrollToEntry2")


func scrollToEntry2():
	if activeEntry != null:
		scrollContainer.ensure_control_visible(activeEntry)
		cursor.global_position = activeEntry.entry.roundButtons[curRoundNum - 1].rect_global_position - Vector2(3, 7)

func addAni(node, isBag):
	var delay = 0.1
	
	if isBag:
		delay *= Util.rng.randf_range(0.8, 1.2)
		var downDur = 0.07
		var upDur = 0.11
		var offsetPos = node.position.y + Util.rng.randf_range(1, 2)
		buildAniTween.tween_property(node, "position:y", offsetPos, 
			downDur).set_delay(delay).set_ease(Tween.EASE_IN)
		buildAniTween.tween_property(node, "position:y", node.position.y, 
			upDur).from(offsetPos).set_delay(downDur + delay).set_ease(Tween.EASE_OUT)
	else:
		delay *= Util.rng.randf_range(0.4, 1.6)
		var upDur = 0.07
		var downDur = 0.07
		var jumpFactor = Util.rng.randf_range(1, 2)
		var startPos: Vector2 = node.position - Vector2(0, 40 * jumpFactor)
		var bouncePos: Vector2 = node.position - Vector2(0, 2 * jumpFactor)
		buildAniTween.tween_property(node, "position", node.position, 
			delay).from(startPos).set_ease(Tween.EASE_OUT)
		
		buildAniTween.tween_property(node, "position", bouncePos, 
			upDur).set_delay(upDur + delay)
		buildAniTween.tween_property(node, "position", node.position, 
			upDur).set_delay(downDur + upDur + delay).from(bouncePos)


func fightBuild():
	if curData != null and not fighting:
		Game.unpause(Game.PauseSource.RecipeBook)
		close(true)
		
		fighting = true
		Game.suspendRunState(false)
		Game.startHistoryRun(curData, curRoundNum)
		Game.titleScreen.clearItems()
		Game.titleScreen.randomClassParticles.instantClear()
		
		Game.setTutorialDone(Game.TutorialSteps.HistoryFight)
		tutorialAni.play("RESET")

func fightBuildWithClipboard():
	if is_instance_valid(fightPopUI):
		var clip = OS.get_clipboard()
		if clip != null:
			fightInput.text = String(clip)
		if is_instance_valid(copyPopUI):
			copyPopUI.visible = false
		fightPopUI.visible = true

func onCopyBuildPressed():
	if curData == null:
		return
	var serialized = getCurrentBuildShareString()
	if serialized == "":
		return
	var code = yield(encodeBuildString(serialized), "completed")
	if code == null or code == "":
		code = serialized
	copyBuildString.translationKey = ""
	copyBuildString.text = code
	OS.set_clipboard(code)
	if is_instance_valid(fightPopUI):
		fightPopUI.visible = false
	copyPopUI.visible = true

func onFightPopupFightPressed():
	if curData == null or fighting:
		return
	var parsed = yield(parseBuildString(String(fightInput.text)), "completed")
	if parsed == null:
		return
	if is_instance_valid(fightPopUI):
		fightPopUI.visible = false
	Game.unpause(Game.PauseSource.RecipeBook)
	close(true)
	fighting = true
	Game.suspendRunState(false)
	Game.startHistoryRun(curData, curRoundNum, parsed, int(parsed.get("round", 1)))
	Game.titleScreen.clearItems()
	Game.titleScreen.randomClassParticles.instantClear()
	Game.setTutorialDone(Game.TutorialSteps.HistoryFight)
	tutorialAni.play("RESET")

func getCurrentBuildShareString() -> String:
	if curData == null or curRoundNum <= 0:
		return ""
	var roundData = curData.getRoundData(curRoundNum)
	if roundData == null:
		return ""
	var itemsString: String = roundData.items
	if itemsString == null or itemsString == "":
		return ""
	var itemsBytes = itemsString.to_utf8()
	var items_b64 = Marshalls.raw_to_base64(itemsBytes)
	var classI = curData.classI
	var loadout = curData.loadout
	var versionStr = curData.getVersionString()
	var name = Game.getPlayerName()
	var chibi = Game.getEffectiveChibiMode()
	var skins = getSkinsForClass(classI, chibi)
	var payload = {
		"version": versionStr, 
		"class": classI, 
		"loadout": loadout, 
		"round": curRoundNum, 
		"name": name, 
		"chibi": chibi, 
		"skins": skins, 
		"items_b64": items_b64
	}
	return to_json(payload)

func getSkinsForClass(classI: int, chibi: bool):
	var skins = []
	for slot in Game.SkinSlot.size():
		var key = Game.getSkinConfigKey(slot, classI, chibi)
		var skinId = Game.getConfigValue("Wardrobe", key, 0)
		skins.push_back(int(skinId))
	return normalizeSkins(skins, classI)

func parseBuildString(rawInput: String):
	if rawInput == null or String(rawInput).strip_edges() == "":
		return null
	var decoded = yield(decodeBuildString(String(rawInput)), "completed")
	var rawString = decoded if decoded != null and decoded != "" else String(rawInput)
	var parsed = JSON.parse(rawString)
	if parsed.error != OK or typeof(parsed.result) != TYPE_DICTIONARY:
		return null
	var dict: Dictionary = parsed.result
	if not dict.has("items_b64"):
		return null
	var classI = int(dict.get("class", Game.curClass))
	var loadout = int(dict.get("loadout", Game.Loadout.Loadout1))
	var versionStr = dict.get("version", Game.VERSION)
	var roundNum = int(dict.get("round", 1))
	var name = dict.get("name", tr("OPPONENT_PLACEHOLDER"))
	var chibi = dict.get("chibi", false)
	var skins = normalizeSkins(dict.get("skins", []), classI)
	var items_b64: String = dict.get("items_b64", "")
	if items_b64 == "":
		return null
	var itemsBytes = Marshalls.base64_to_raw(items_b64)
	if itemsBytes.empty():
		return null
	var itemsString = itemsBytes.get_string_from_utf8()
	if itemsString == null or itemsString == "":
		return null
	var decodedItems = RunData.deserializeItems(itemsString, versionStr)
	if decodedItems == null or not decodedItems.has("items"):
		return null
	var data = BuildHistoryData.new()
	data.id = - 1
	data.version = Game.versionToInt(versionStr)
	data.time = Time.get_unix_time_from_system()
	data.classI = classI
	data.loadout = loadout
	data.mode = Game.Mode.Unranked
	data.customRules = ""
	data.rating = - 1
	data.roundHistory = []
	var baseHealth = Game.getMaxHealthInRound(classI, roundNum)
	var baseStamina = Game.calculateMaxStaminaFromItemTuples(classI, decodedItems["items"])
	data.addRoundData(roundNum, Game.RoundResult.Win, Game.MAX_TRIES, baseHealth, baseStamina, itemsString)
	return {
		"run": data, 
		"round": roundNum, 
		"name": name, 
		"chibi": chibi, 
		"skins": skins
	}

func encodeBuildString(raw: String) -> String:
	var http = HTTPRequest.new()
	add_child(http)
	var headers = ["Content-Type: application/json"]
	var body = to_json({"value": raw})
	var err = http.request(ENCODE_URL, headers, true, HTTPClient.METHOD_POST, body)
	if err != OK:
		http.queue_free()
		return ""
	var res = yield(http, "request_completed")
	http.queue_free()
	if res.size() < 4:
		return ""
	var status = res[1]
	var bodyBytes = res[3]
	if status != 200:
		return ""
	var parsed = JSON.parse(bodyBytes.get_string_from_utf8())
	if parsed.error != OK or typeof(parsed.result) != TYPE_DICTIONARY:
		return ""
	return String(parsed.result.get("code", ""))

func decodeBuildString(code: String) -> String:
	var http = HTTPRequest.new()
	add_child(http)
	var headers = ["Content-Type: application/json"]
	var body = to_json({"code": code})
	var err = http.request(DECODE_URL, headers, true, HTTPClient.METHOD_POST, body)
	if err != OK:
		http.queue_free()
		return ""
	var res = yield(http, "request_completed")
	http.queue_free()
	if res.size() < 4:
		return ""
	var status = res[1]
	var bodyBytes = res[3]
	if status != 200:
		return ""
	var parsed = JSON.parse(bodyBytes.get_string_from_utf8())
	if parsed.error != OK or typeof(parsed.result) != TYPE_DICTIONARY:
		return ""
	return String(parsed.result.get("value", ""))

func normalizeSkins(inputSkins, classI):
	var skins = []
	var maxSlots = Game.SkinSlot.size()
	for i in maxSlots:
		var val = null
		if inputSkins is Array and i < inputSkins.size():
			val = inputSkins[i]
		if val == null:
			val = 0
		skins.push_back(int(val))
	return skins

func onPreviousRoundPressed():
	if activeEntry != null:
		var numRounds = curData.getRounds()
		if numRounds <= 1: return
		var newRound = ((curRoundNum - 2 + numRounds) % numRounds) + 1
		updateBuild(newRound, activeEntry)

func onNextRoundPressed():
	if activeEntry != null:
		var numRounds = curData.getRounds()
		if numRounds <= 1: return
		var newRound = (curRoundNum % numRounds) + 1
		updateBuild(newRound, activeEntry)

func selectPreviousEntry():
	if activeEntry != null and entries.size() > 1:
		var index = entries.find(activeEntry)
		var newEntry = entries[index - 1]
		updateBuild(newEntry.data.getRounds(), newEntry)
		

func selectNextEntry():
	if activeEntry != null and entries.size() > 1:
		var index = entries.find(activeEntry)
		var newEntry = entries[(index + 1) % entries.size()]
		updateBuild(newEntry.data.getRounds(), newEntry)


func _unhandled_input(event: InputEvent):
	if InputBlocker.isActive(): return
	
	if not isOpen:
		return

	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		var mouse_pos = get_viewport().get_mouse_position()
		if is_instance_valid(copyPopUI) and copyPopUI.visible:
			var copyPanel = copyPopUI.get_node("Panel")
			if not copyPanel.get_global_rect().has_point(mouse_pos):
				copyPopUI.visible = false
				get_tree().set_input_as_handled()
				return
		if is_instance_valid(fightPopUI) and fightPopUI.visible:
			var fightPanel = fightPopUI.get_node("Panel")
			if not fightPanel.get_global_rect().has_point(mouse_pos):
				fightPopUI.visible = false
				get_tree().set_input_as_handled()
				return

	if event is InputEventKey and event.is_pressed() and not event.is_echo():
		if event.control and event.shift and event.scancode == KEY_C:
			Game.historyPoolCheckEnabled = not Game.historyPoolCheckEnabled
			Game.setConfigValue("Options", "HistoryPoolCheckEnabled", Game.historyPoolCheckEnabled)
			_showHistoryPoolCheckFeedback(Game.historyPoolCheckEnabled)
			_refreshPoolChecks()
			get_tree().set_input_as_handled()
			return

		if event.control and event.shift and event.scancode == KEY_D:
			Game.historyDeleteModeEnabled = not Game.historyDeleteModeEnabled
			Game.setConfigValue("Options", "HistoryDeleteModeEnabled", Game.historyDeleteModeEnabled)
			_showHistoryDeleteModeFeedback(Game.historyDeleteModeEnabled)
			get_tree().set_input_as_handled()
			return

		if event.control and event.shift and event.scancode == KEY_DELETE:
			_deleteSelectedHistoryEntry()
			get_tree().set_input_as_handled()
			return

		if event.control and event.scancode == KEY_F:
			if modeFilter == MODE_FILTER_OPPONENT_POOL and is_instance_valid(searchbar) and searchbar.visible:
				searchbar.grab_focus()
				searchbar.select_all()
				get_tree().set_input_as_handled()
				return

		if event.scancode == KEY_BACKSLASH and not event.control and not event.shift and not event.alt:
			_enterOpponentPoolMode()
			get_tree().set_input_as_handled()
			return

		if event.scancode == KEY_F5:
			if modeFilter == MODE_FILTER_OPPONENT_POOL:
				refreshOpponentPool()
			else:
				refreshHistory()
			get_tree().set_input_as_handled()
			return
	
	if event.is_action_pressed("next_tab"):
		onNextRoundPressed()
	elif event.is_action_pressed("previous_tab"):
		onPreviousRoundPressed()
	elif event.is_action_pressed("tab_above"):
		selectPreviousEntry()
	elif event.is_action_pressed("tab_below"):
		selectNextEntry()
	elif Util.isActionPressed_event(event, "options"):
		if isOpen:
			get_tree().set_input_as_handled()
			close()

func _flashStatusLabel(text: String):
	if not is_instance_valid(statusFeedbackLabel):
		return
	statusFeedbackLabel.text = text
	statusFeedbackLabel.visible = true
	statusFeedbackLabel.modulate = Color(1, 1, 1, 1)
	Util.finishTween(feedbackTween)
	feedbackTween = create_tween()
	feedbackTween.tween_property(statusFeedbackLabel, "modulate:a", 0.3, 0.15)
	feedbackTween.tween_property(statusFeedbackLabel, "modulate:a", 1.0, 0.15)
	if is_instance_valid(statusFeedbackTimer):
		statusFeedbackTimer.stop()
		statusFeedbackTimer.start(1.2)

func _onStatusFeedbackTimeout():
	_hideStatusFeedback()

func _hideStatusFeedback():
	if not is_instance_valid(statusFeedbackLabel):
		return
	statusFeedbackLabel.visible = false
	statusFeedbackLabel.modulate = Color(1, 1, 1, 1)

func _showHistoryPoolCheckFeedback(enabled: bool):
	Sound.playSound_process(Game.transitionSounds[0], 0, 1.2)
	var loc = TranslationServer.get_locale().to_lower()
	var isChinese = loc.begins_with("zh")
	var msg = ""
	if enabled:
		msg = "进池检验已开启" if isChinese else "Pool Check enabled"
	else:
		msg = "进池检验已关闭" if isChinese else "Pool Check disabled"
	_flashStatusLabel(msg)

func _showHistoryDeleteModeFeedback(enabled: bool):
	Sound.playSound_process(Game.transitionSounds[0], 0, 1.2)
	var loc = TranslationServer.get_locale().to_lower()
	var isChinese = loc.begins_with("zh")
	var msg = ""
	if enabled:
		msg = "历史删除模式已开启" if isChinese else "History delete mode enabled"
	else:
		msg = "历史删除模式已关闭" if isChinese else "History delete mode disabled"
	_flashStatusLabel(msg)

func _showHistoryDeleteFeedback(success: bool):
	Sound.playSound_process(Game.transitionSounds[0], 0, 1.2)
	var loc = TranslationServer.get_locale().to_lower()
	var isChinese = loc.begins_with("zh")
	var msg = ""
	if success:
		msg = "已删除当前历史记录" if isChinese else "Selected history deleted"
	else:
		msg = "删除失败" if isChinese else "Delete failed"
	_flashStatusLabel(msg)

func _showHistoryDeleteUnavailableFeedback(reason: String):
	Sound.playSound_process(Game.transitionSounds[0], 0, 1.2)
	var loc = TranslationServer.get_locale().to_lower()
	var isChinese = loc.begins_with("zh")
	var msg = ""
	if reason == "disabled":
		msg = "请先开启删除模式" if isChinese else "Enable delete mode first"
	elif reason == "opponent_pool":
		msg = "对手池模式不可删除" if isChinese else "Cannot delete in Opponent Pool"
	else:
		msg = "未选中可删除历史" if isChinese else "No deletable history selected"
	_flashStatusLabel(msg)

func _deleteSelectedHistoryEntry():
	if not Game.historyDeleteModeEnabled:
		_showHistoryDeleteUnavailableFeedback("disabled")
		return

	if modeFilter == MODE_FILTER_OPPONENT_POOL:
		_showHistoryDeleteUnavailableFeedback("opponent_pool")
		return

	if curData == null or Game.buildHistoryDB == null:
		_showHistoryDeleteUnavailableFeedback("selection")
		return

	if curData is OpponentPoolAdapter:
		_showHistoryDeleteUnavailableFeedback("opponent_pool")
		return

	var runID = int(curData.id)
	if runID < 0:
		_showHistoryDeleteUnavailableFeedback("selection")
		return

	Game.buildHistoryDB.deleteRunHistory(runID)
	clear()
	addEntries()

	var deleted = true
	for entry in entries:
		if entry != null and entry.data != null and int(entry.data.id) == runID:
			deleted = false
			break

	_showHistoryDeleteFeedback(deleted)

func _refreshPoolChecks():
	for entry in entries:
		if entry != null and entry.entry != null:
			entry.entry.refreshPoolCheck()

func _showHistoryRefreshFeedback():
	Sound.playSound_process(Game.transitionSounds[0], 0, 1.2)
	var loc = TranslationServer.get_locale().to_lower()
	var isChinese = loc.begins_with("zh")
	var msg = "历史记录已刷新" if isChinese else "History Refreshed"
	_flashStatusLabel(msg)

func _showOpponentPoolRefreshFeedback():
	Sound.playSound_process(Game.transitionSounds[0], 0, 1.2)
	var loc = TranslationServer.get_locale().to_lower()
	var isChinese = loc.begins_with("zh")
	var msg = "对手池已刷新" if isChinese else "Opponent Pool Refreshed"
	_flashStatusLabel(msg)

func _showOpponentPoolAccessDeniedFeedback():
	Sound.playSound_process(Game.transitionSounds[0], 0, 1.2)
	var loc = TranslationServer.get_locale().to_lower()
	var isChinese = loc.begins_with("zh")
	var msg = ""
	if not RunDatabase.hasConnected():
		msg = "需联网后进入对手池" if isChinese else "Connect online to use Opponent Pool"
	else:
		msg = "对手池权限校验未通过" if isChinese else "Opponent Pool access denied"
	_flashStatusLabel(msg)

func _isOpponentPoolPermitted() -> bool:
	return RunDatabase.hasConnected() and Game.isOpponentPoolAllowed()

func _updateOpponentPoolSearchbar():
	if not is_instance_valid(searchbar):
		return

	var showSearch = modeFilter == MODE_FILTER_OPPONENT_POOL
	searchbar.visible = showSearch
	if not showSearch:
		if searchbar.text != "":
			searchbar.text = ""
		searchTerm = ""
		pendingSearchTerm = ""
		if is_instance_valid(searchDebounceTimer):
			searchDebounceTimer.stop()

func onSearchTextChanged(newText: String):
	if modeFilter != MODE_FILTER_OPPONENT_POOL:
		return
	if newText == "":
		_performSearch("")
		return
	pendingSearchTerm = newText
	if is_instance_valid(searchDebounceTimer):
		searchDebounceTimer.start()

func _onSearchDebounceTimeout():
	_performSearch(pendingSearchTerm)

func _performSearch(rawText: String):
	var lowered = rawText.to_lower()
	searchTerm = lowered
	searchTerm = searchTerm.replace("$", "")
	searchTerm = searchTerm.replace("[", "")
	searchTerm = searchTerm.replace("]", "")

	clear()
	addEntries()

func _syncModeListSelection():
	if is_instance_valid(modeList):
		var selectedMode = modeFilter
		if modeFilter == MODE_FILTER_OPPONENT_POOL:
			selectedMode = historyModeFilterBeforeOpponentPool
		selectedMode = int(clamp(selectedMode, - 1, 3))
		suppressModeSelectionCallback = true
		modeList.selectItemByIndex(selectedMode + 1)
		suppressModeSelectionCallback = false

func _enterOpponentPoolMode() -> bool:
	if modeFilter == MODE_FILTER_OPPONENT_POOL:
		modeFilter = historyModeFilterBeforeOpponentPool
		_syncModeListSelection()
		_updateOpponentPoolSearchbar()
		clear()
		addEntries()
		return true
	if not _isOpponentPoolPermitted():
		_showOpponentPoolAccessDeniedFeedback()
		return false
	historyModeFilterBeforeOpponentPool = modeFilter
	modeFilter = MODE_FILTER_OPPONENT_POOL
	_syncModeListSelection()
	_updateOpponentPoolSearchbar()
	clear()
	addEntries()
	return true

func refreshHistory():
	if refreshing:
		return

	refreshing = true
	clear()
	addEntries()
	_refreshPoolChecks()
	_showHistoryRefreshFeedback()
	RunDatabase.sendRunRequest()
	refreshing = false

func refreshOpponentPool():
	if refreshing:
		return
	if not _isOpponentPoolPermitted():
		_showOpponentPoolAccessDeniedFeedback()
		return

	refreshing = true
	clear()
	addEntries()
	_showOpponentPoolRefreshFeedback()
	RunDatabase.sendRunRequest()
	refreshing = false

func onScrollbarVisibilityChanged():
	if scrollContainer.get_v_scrollbar().visible:
		scrollContainer.rect_size.x = 1037
	else:
		scrollContainer.rect_size.x = 1012

func updateLocale():
	addDropDownClasses()
	updateCopyPopupTexts()

func addDropDownClasses():
	classList.clearList()
	classList.addItem(Util.tra("UI_AllClasses"))
	for c in Game.Classes_Full.size():
		if Game.isClassUnlocked(c):
			classList.addItem(Game.getClassName(c), Game.classIcons[c])
	classList.selectItemByIndex(classFilter + 1)
	
	modeList.clearList()
	modeList.addItem(Util.tra("UI_AllModes"))
	modeList.addItem(Util.tra("UI_Ranked"))
	modeList.addItem(Util.tra("UI_Unranked"))
	modeList.addItem(Util.tra("UI_Lobby"))
	modeList.addItem(Util.tra("UI_CustomRules"))
	_syncModeListSelection()
	

func onClassSelected(classI, _className):
	
	classFilter = classI - 1
	
	clear()
	addEntries()

func onModeSelected(modeI, _modeName):
	if suppressModeSelectionCallback:
		suppressModeSelectionCallback = false
		return

	var requestedMode = modeI - 1
	if requestedMode == modeFilter and modeFilter != MODE_FILTER_OPPONENT_POOL:
		return

	modeFilter = requestedMode
	historyModeFilterBeforeOpponentPool = requestedMode
	_updateOpponentPoolSearchbar()
	clear()
	addEntries()

func resetFilters():
	classFilter = - 1
	modeFilter = - 1
	historyModeFilterBeforeOpponentPool = - 1
	classList.selectItemByIndex(classFilter + 1)
	_syncModeListSelection()
	_updateOpponentPoolSearchbar()
	
	clear()
	addEntries()

func resetOpponentMark():
	markedOpponentData = null
	opponentMark.hide()
	fightButton.modulate = Color.white

func onCursorWarp():
	if not isOpen: return
	
	Game.addControlOfInterest(classList, Vector2(50, 0))
	Game.addControlOfInterest(modeList, Vector2(50, 0))
	Game.addControlOfInterest(resetFilterButton)
	Game.addControlOfInterest(closeButton)
	
	if curData != null:
		Game.addControlOfInterest(previousRoundButton)
		Game.addControlOfInterest(nextRoundButton)
		Game.addControlOfInterest(fightButton)
		for item in inventory.getItemsAndGems():
			Game.addItemOfInterest(item)
	
	for placeholder in entries:
		var entry = placeholder.entry
		if entry == null:
			Game.addPointOfInterest(
				placeholder.rect_global_position + placeholder.rect_size * 0.5, 
					scrollContainer, placeholder)
		else:
			for roundButton in entry.roundButtons:
				if roundButton.visible:
					Game.addPointOfInterest(
						roundButton.rect_global_position + roundButton.rect_size * 0.5, 
						scrollContainer, placeholder)
