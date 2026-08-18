extends Node2D

const placeholderScene = preload("res://Interface/BuildHistory/BuildEntryPlaceholder.tscn")

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
onready var buildNode = $Build
onready var fightButton = $Build / FightButton
onready var tutorialAni = $Build / AnimationPlayer
onready var classList = $Filter / Classes
onready var modeList = $Filter / Modes
onready var resetFilterButton = $Filter / ResetFilters
onready var emptyHint = $Empty
onready var closeButton = $CloseButton
onready var previousRoundButton = $Build / PreviousRound
onready var nextRoundButton = $Build / NextRound

var isOpen = false
var entries: Array
var curRoundNum: int
var curData: BuildHistoryData = null
var curRunId: int
var fighting: = false
var activeEntry = null
var hasFought: = false
var classFilter: int = - 1
var modeFilter: int = - 1
var buildAniTween: SceneTreeTween

var markedOpponentData: BuildHistoryData = null
var markedOpponentRound = - 1

func _ready():
	Game.connect("warp_cursor_menu", self, "onCursorWarp")
	
	$ScrollContainer / VBoxContainer / BuildEntry.queue_free()
	
	var scrollBar = scrollContainer.get_v_scrollbar()
	scrollBar.connect("visibility_changed", self, "onScrollbarVisibilityChanged")
	
	opponentMark.hide()
	
	add_to_group("Localized")
	updateLocale()

func clear():
	for entry in entries:
		entry.returnToObjectPool()
	entries.clear()
	curData = null
	activeEntry = null
	inventory.reset()
	resetOpponentMark()

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
		
		if ( not fightButton.disabled and 
			Game.getNumStartedRuns() > 4 and 
			Game.getNumStartedRuns() < 10 and 
			not Game.isTutorialDone(Game.TutorialSteps.HistoryFight)):
		
			tutorialAni.play("Tutorial")
		
		
		addEntries()

func addEntries():
	
	var runHistory = Game.buildHistoryDB.readRunHistory()
	if not runHistory.empty():
		
		var runIDs: Array = runHistory.keys()
		runIDs.sort()
		runIDs.invert()
		
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
				entry.setHistoryData(run)
				entries.push_back(entry)
				
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


func opened():
	InputBlocker.deactivate(InputBlocker.Source.PopupAnimation, false)
	Game.openedMenu()
	Game.endHistoryRun()

func close(fight = false):
	if animation.current_animation == "":
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
	if curData != null and not fighting and animation.current_animation == "":
		Game.unpause(Game.PauseSource.RecipeBook)
		close(true)
		
		fighting = true
		Game.suspendRunState(false)
		Game.startHistoryRun(curData, curRoundNum)
		Game.titleScreen.clearItems()
		Game.titleScreen.randomClassParticles.instantClear()
		
		Game.setTutorialDone(Game.TutorialSteps.HistoryFight)
		tutorialAni.play("RESET")

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

func onScrollbarVisibilityChanged():
	if scrollContainer.get_v_scrollbar().visible:
		scrollContainer.rect_size.x = 1037
	else:
		scrollContainer.rect_size.x = 1012

func updateLocale():
	addDropDownClasses()

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
	modeList.selectItemByIndex(modeFilter + 1)
	

func onClassSelected(classI, _className):
	
	classFilter = classI - 1
	
	clear()
	addEntries()

func onModeSelected(modeI, _modeName):
	modeFilter = modeI - 1
	clear()
	addEntries()

func resetFilters():
	classFilter = - 1
	modeFilter = - 1
	classList.selectItemByIndex(classFilter + 1)
	modeList.selectItemByIndex(modeFilter + 1)
	
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
