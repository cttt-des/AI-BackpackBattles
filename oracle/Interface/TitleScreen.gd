extends Node2D

const rainbowOutlineMaterial = preload("res://Shader/RainbowShiftOutline.material")
const TRAILER = false
const MAX_ITEMS = 30
const offset = 200
const impulse = 200
const rarityOdds = [0.6, 0.2, 0.11, 0.06, 0.03, 0.03]
const continueBanner_ranked = preload("res://Assets/TitleScreen/ContinueBanner_Ranked.png")
const continueBanner_unranked = preload("res://Assets/TitleScreen/ContinueBanner_Unranked.png")
const continueBanner_custom = preload("res://Assets/TitleScreen/ContinueBanner_CustomUnranked.png")


onready var itemNode = $ItemNode
onready var rankedButton = $"%RankedButton"
onready var unrankedButton = $"%UnrankedButton"
onready var continueButton = $"%ContinueButton"
onready var continueNode = $TitleNode / Continue
onready var customRulesIcon = $TitleNode / Continue / CustomRulesIcon
onready var concedeAnimation = $TitleNode / Concede / AnimationPlayer
onready var concedeButton = $"%ConcedeButton"


onready var quitGlow = $Node2D / Background / Quit / QuitSign / QuitSignGlow
onready var smokeParticles = $Node2D / Background / SmokeParticles2D
onready var itemDropTimer = $ItemDropTimer
onready var itemDropTimer2 = $ItemDropTimer
onready var classAndLoadoutNode = $AboveBlackLayer / Class
onready var classButtonsNode = $AboveBlackLayer / Class / ClassButtons
onready var classNodes = Util.getNodesForAllClasses(self, "AboveBlackLayer/Class/ClassButtons/{class}")
onready var randomClassButton = $AboveBlackLayer / Class / ClassButtons / Random
onready var randomClassHint = $AboveBlackLayer / Class / Loadouts / RandomHint
onready var randomClassNodes = [
	$TitleNode / RankedButton / RandomBorder, 
	$TitleNode / UnrankedButton / RandomBorder, 
	$TitleNode / Lobbies / OtherGameButton / RandomBorder]


onready var loadoutButtons = [
	$AboveBlackLayer / Class / Loadouts / VBoxContainer / LoadoutButton, 
	$AboveBlackLayer / Class / Loadouts / VBoxContainer / LoadoutButton2, 
	$AboveBlackLayer / Class / Loadouts / VBoxContainer / LoadoutButton3
]



onready var otherModesButton = $TitleNode / Lobbies / OtherGameButton
onready var loadoutInputBlocker = Game.UINode.get_node("InputBlocker")

var randomClassParticles = null
var selectedClassButton = null
var xPos = 1200.0
var itemsScheduled = 0
var warpPointNodes: Array


func _ready() -> void :
	$TitleNode / Lobbies.visible = Game.LOBBIES_ENABLED
	$"%Quit".visible = not OS.has_feature("web")
	
	$"%RankedBannerHovered".hide()
	$"%UnrankedBannerHovered".hide()
	
	Game.connect("continue_loaded", self, "checkSavedRunState")
	Game.connect("return_to_title", self, "checkSavedRunState")
	Game.connect("runstate_suspended", self, "onRunstateSuspended")
	Game.connect("item_picked_up", self, "onItemPickedUp")
	Game.connect("item_dropped", self, "onItemDropped")
	
	for classI in classNodes.size():
		var classNode = classNodes[classI]
		if Game.isClassUnlocked(classI):
			classNode.connect("pressed", self, "selectClass", [classI])
		else:
			classNode.hide()
	
	add_to_group("Localized")
	Util.localizeFonts($TitleNode / Concede / ConcedeLabel)
	updateSocialButtons()
	
	if Game.LOADOUTS_ENABLED:
		randomClassButton.connect("toggled", self, "toggleRandomClass")
		
		for i in loadoutButtons.size():
			loadoutButtons[i].connect("toggled", self, "onLoadoutButtonToggled", [i])
			Util.localizeFonts(loadoutButtons[i])
	else:
		$AboveBlackLayer / Class / Loadouts.queue_free()
		randomClassButton.queue_free()
	
	loadoutInputBlocker.hide()
	call_deferred("ready_deferred")

func ready_deferred():
	warpPointNodes = Util.getInteractableNodes($ButtonsNode)
	Util.walkInteractableNodes($AboveBlackLayer / Class, warpPointNodes)
	warpPointNodes.push_back(continueButton)
	warpPointNodes.push_back(rankedButton)
	warpPointNodes.push_back(unrankedButton)
	warpPointNodes.push_back(otherModesButton)
	warpPointNodes.push_back(concedeButton)
	warpPointNodes.push_back($Node2D / Background / Quit / QuitButton)
	warpPointNodes.push_back(Game.versionButton)
	Game.connect("warp_cursor_title", self, "onCursorWarp")

func updateClassNodes(curClass, randomCharacter):
	for classI in classNodes.size():
		var classNode = classNodes[classI]
		classNode.disabled = not Game.isClassUnlocked(classI)
	
	if Game.LOADOUTS_ENABLED:
		updateLoadoutLocale(curClass)
		updateLoadoutButtons(false)
		onRandomClassToggled(randomCharacter)

func updateLoadoutLocale(classI):
	if Game.LOADOUTS_ENABLED:
		for i in loadoutButtons.size():
			loadoutButtons[i].text = Game.classResources[classI].getStartingItems(i)[0].getTranslatedItemName()

func showSocialButtons():
	return not Game.TRAILER and not SteamHelper.STEAMDECK

func updateSocialButtons():
	var showButtons = showSocialButtons()
	var curLocale = TranslationServer.get_locale()
	var isSimplifiedChinese = curLocale == "zh_Hans_CN"
	$ButtonsNode / DiscordButton.visible = showButtons and not isSimplifiedChinese
	$ButtonsNode / YoutubeButton.visible = showButtons and not isSimplifiedChinese
	$ButtonsNode / WikiButton.visible = showButtons
	$WishlistButton.visible = showButtons and not Game.showExclusiveContent()
	$ButtonsNode / QQButton.visible = showButtons
	$ButtonsNode / ChineseItemSearch.visible = showButtons and isSimplifiedChinese
	
	
	$Node2D / Background / StaticBody2D2 / CollisionPolygon2D.disabled = TRAILER
	$StaticBody2D / CollisionShape2D2.disabled = TRAILER
	$StaticBody2D / CollisionShape2D3.disabled = TRAILER

	$Paper1.visible = TRAILER
	$ItemNode.z_index = 200 if TRAILER else - 2
	

func selectClass(classI, randomCharacter = Game.randomCharacter, 
	visualOnly = false):
		
	if Game.draggedItem:
		return
	
	if selectedClassButton != null:
		selectedClassButton.get_node("Particles").deactivate()
		selectedClassButton.get_node("Glow").hide()
	
	var classButton = classNodes[classI]
	classButton.get_node("Particles").activate()
	classButton.get_node("Glow").show()
	selectedClassButton = classButton
	
	if not Game.isClassSelected(classI):
		if visualOnly:
			updateClassNodes(classI, randomCharacter)
			loadoutButtons[Game.getConfiguredLoadout()].set_pressed(true)
		else:
			Game.instanceCharacter(classI)
			updateClassNodes(classI, randomCharacter)
			
			if Game.LOADOUTS_ENABLED:
				var loadout = Game.getConfiguredLoadout()
				if loadoutButtons[loadout].pressed:
					Game.setLoadout(loadout)
				else:
					loadoutButtons[loadout].set_pressed(true)
			else:
				Game.initStartInventory(0)

func toggleRandomClass(pressed):
	Game.setRandomCharacter(pressed)
	Game.setConfigValue("Options", "RandomClass", pressed)
	onRandomClassToggled(pressed)

func onRandomClassToggled(pressed):
	if pressed:
		randomClassHint.show()
		randomClassButton.set_material(rainbowOutlineMaterial)
		randomClassButton.get_node("Particles").activate()
		if randomClassParticles != null:
			randomClassParticles.activate()
		for node in randomClassNodes:
			node.show()
	else:
		randomClassHint.hide()
		randomClassButton.set_material(null)
		randomClassButton.get_node("Particles").deactivate()
		if randomClassParticles != null:
			randomClassParticles.deactivate()
		for node in randomClassNodes:
			node.hide()

func onQuitPressed():
	Game.quit()

func startRankedPressed() -> void :
	if ( not Game.draggedItem and 
		not Game.runStarted and 
		not continueNode.visible):
		if not Game.isClassUnlocked():
			Game.instanceCharacter(Game.Classes.Ranger)
			Game.initStartInventory()
		
		Game.startFreshRun(Game.Mode.Ranked)
		clearItems()

func startUnrankedPressed() -> void :
	if ( not Game.draggedItem and 
		not Game.runStarted and 
		not continueNode.visible):
		if not Game.isClassUnlocked():
			Game.instanceCharacter(Game.Classes.Ranger)
			Game.initStartInventory()
		
		Game.startFreshRun(Game.Mode.Unranked)
		clearItems()

var numTrailerItems = 500

func showTitle() -> void :
	if TRAILER:
		print("trailer")
		var items = []
		var itemList = []
		for itemName in ItemBook.items:
			if ItemBook.items[itemName].version == Game.versionToInt("1.1.0"):
				itemList.push_back(ItemBook.items[itemName])
		
		itemList.shuffle()
		numTrailerItems = itemList.size()
		for i in numTrailerItems:
			items.push_back(ItemBook.instantiateItem(itemList[i]))
		for i in numTrailerItems:
			Util.callDelayed(self, "dropItem", 3 + i * 0.02, [items[i]])
		itemsScheduled = numTrailerItems
	else:
		itemDropTimer.start(1)
		
		smokeParticles.emitting = true

func spawnItem():
	if itemNode.get_child_count() < MAX_ITEMS:
		dropItem()
	
	if Game.state == Game.State.Title:
		itemDropTimer.start(Util.rng.randf_range(0.4, 1.0))

func dropItem(_item = null):
	itemsScheduled = max(0, itemsScheduled - 1)
	if (Game.state != Game.State.Title or 
		(Game.sceneAnimation.current_animation != "" and 
		Game.sceneAnimation.current_animation != "StartOnTitle")):
		return
	
	var item = _item
	if not item:
		var descriptor = ItemBook.getRandomItemWithRarityOdds(rarityOdds)
		
		item = descriptor.instantiate_pooled()
	
	item.ownerType = Item.Owner.Title
	itemNode.add_child(item)
	item.initTitle()
	
	if TRAILER:
		
		item.position = Vector2(xPos, - 900)
		xPos += Util.rng.randf_range(200, 300)
		if xPos > 1400:
			xPos = 400
	else:
		item.position = Vector2(xPos, - 200)
		xPos += Util.rng.randf_range(100, 300)
		
		if xPos > 1600:
			xPos -= 400
	
	positionItem(item)
	
	
	if Util.rng.randf() < 0.1:
		item.impactSoundVolume = - 5
	else:
		item.impactSoundVolume = - 12
		
	Util.callDelayed(self, "applyImpulse", 0.01, [item])

func _unhandled_key_input(event):
	if TRAILER and event.is_pressed() and event.scancode == KEY_B and Util.debugOnly():
		showTitle()


func positionItem(item):
	item.global_position = item.findFreeSpace(item.global_position)
	

func applyImpulse(item):
	item.apply_impulse(Vector2(Util.rng.randf_range( - offset, offset), 
								Util.rng.randf_range( - offset, offset)), 
								Vector2(Util.rng.randf_range( - impulse, impulse), 
									Util.rng.randf_range( - impulse, impulse)))

func onItemReachedBottom(item) -> void :
	if item.ownerType == Item.Owner.Title:
		item.discard()

func checkSavedRunState() -> void :
	if randomClassParticles == null:
		randomClassParticles = Game.PLAYER.randomClassParticles
	
	disableButtons(false)
	
	if Game.hasArenaRunState():
		rankedButton.disable()
		unrankedButton.disable()
		var runClass: int = Game.arenaRunState["class"]
		var isRandomCharacter: bool = Game.arenaRunState["randomClass"]
		
		
		updateClassNodes(runClass, isRandomCharacter)
		
		continueNode.show()
		continueButton.enable()
		concedeAnimation.play("RESET")
		
		updateLocale()
		
		$"%LastRunRound".text = String(Game.arenaRunState["round"])
		$"%LastRunWins".text = String(Game.arenaRunState["wins"])
		$"%LastRunTries".text = String(Game.arenaRunState["tries"])
		
		if "custom" in Game.arenaRunState:
			customRulesIcon.show()
			continueButton.texture_normal = continueBanner_custom
			$"%ContinueBannerHovered".modulate = Color(0.321569, 0.937255, 0.47451, 0.458824)
		elif Game.arenaRunState["mode"] == Game.Mode.Unranked:
			customRulesIcon.hide()
			continueButton.texture_normal = continueBanner_unranked
			$"%ContinueBannerHovered".modulate = Color(0.321569, 0.562071, 0.937255, 0.458824)
		else:
			customRulesIcon.hide()
			continueButton.texture_normal = continueBanner_ranked
			$"%ContinueBannerHovered".modulate = Color(0.937255, 0.321569, 0.321569, 0.458824)
			
		
		selectClass(runClass, isRandomCharacter, true)
		for classI in classNodes.size():
			if classI != runClass:
				classNodes[classI].disabled = true
		
		if Game.LOADOUTS_ENABLED:
			updateLoadoutButtons(true, Game.arenaRunState["loadout"])
			randomClassButton.set_pressed_no_signal(isRandomCharacter)
			onRandomClassToggled(isRandomCharacter)
	else:
		updateClassNodes(Game.curClass, Game.randomCharacter)
		continueNode.hide()
		continueButton.disable()
		
		concedeAnimation.play("Hide")
		selectClass(Game.getSelectedClass())
		
		if Game.LOADOUTS_ENABLED:
			updateLoadoutButtons(false)
			randomClassButton.set_pressed_no_signal(Game.randomCharacter)
			onRandomClassToggled(Game.randomCharacter)


func onRunstateSuspended():
	updateClassNodes(Game.curClass, Game.randomCharacter)

func onLoadoutButtonToggled(pressed, index):
	if pressed and Game.draggedItem == null:
		
		
		Game.setConfigValue("Options", "Loadout_" + Game.getClassInternalName(), index)
		Game.setLoadout(index)

func updateLoadoutButtons(disabled: bool, loadout = Game.getConfiguredLoadout()):
	for i in loadoutButtons.size():
		loadoutButtons[i].disabled = disabled
		loadoutButtons[i].setPressed(i == loadout)
	
	randomClassButton.disabled = disabled



func onItemPickedUp():
	if Game.state == Game.State.Title:
		loadoutInputBlocker.show()

func onItemDropped(item, dropResult):
	if Game.state == Game.State.Title:
		if dropResult != Item.DropResult.Hotswap:
			loadoutInputBlocker.hide()

func updateLocale():
	if Game.hasArenaRunState() and Game.arenaRunState["mode"] == Game.Mode.Ranked or Game.isRankedSwitchMode():
		var rankDifStr = Util.addPlus(Game.getRankingDifIfConceded())
		$"%ConcedeLabel".text = Util.tra("BUTTON_ConcedeRanked").format({"rankDif": rankDifStr})
	else:
		$"%ConcedeLabel".text = Util.tra("BUTTON_ConcedeUnranked")
	
	updateSocialButtons()
	updateLoadoutLocale(Game.curClass)

func clearItems():
	itemDropTimer.stop()
	itemDropTimer2.stop()
	Util.callDelayed(self, "discardAllItems", 1)
	
	onRankedHoverEnd()
	onContinueHoverEnd()
	onUnrankedHoverEnd()
	smokeParticles.emitting = false
	
	
	

func discardAllItems():
	for item in itemNode.get_children():
		item.discard()

func onContinuePressed():
	if not Game.draggedItem and not Game.runStarted:
		Game.continueLastRun(Game.Mode.Unranked)
		clearItems()

func onConcedePressed():
	if not Game.draggedItem:
		concedeAnimation.play("Concede")
		Game.concedeLastRun()
		continueNode.hide()
		continueButton.disable()
		rankedButton.enable()
		unrankedButton.enable()
		updateClassNodes(Game.curClass, Game.randomCharacter)
		

const hoverColor = Color(1.3, 1.3, 1.3)

func onRankedHover() -> void :
	if not rankedButton.disabled:
		$"%RankedBannerHovered".show()
		rankedButton.modulate = hoverColor

func onRankedHoverEnd() -> void :
	$"%RankedBannerHovered".hide()
	rankedButton.modulate = Color.white

func onUnrankedHover() -> void :
	if not unrankedButton.disabled:
		$"%UnrankedBannerHovered".show()
		unrankedButton.modulate = hoverColor

func onUnrankedHoverEnd() -> void :
	$"%UnrankedBannerHovered".hide()
	unrankedButton.modulate = Color.white

func onContinueHover() -> void :
	if not continueButton.disabled:
		$"%ContinueBannerHovered".show()
		continueButton.modulate = hoverColor

func onContinueHoverEnd() -> void :
	$"%ContinueBannerHovered".hide()
	continueButton.modulate = Color.white
	
func onQuitHover():
	quitGlow.show()

func onQuitHoverEnd():
	quitGlow.hide()

func onConcedeHover():
	if not concedeButton.disabled:
		$"%ConcedeBannerHovered".show()
		concedeButton.modulate = hoverColor
	
func onConcedeHoverEnd():
	$"%ConcedeBannerHovered".hide()
	concedeButton.modulate = Color.white

func _on_SteamButton_pressed() -> void :
	var res = OS.shell_open("steam://advertise/2427700")
	
	if res != OK:
		OS.shell_open("https://store.steampowered.com/app/2427700")

func _on_TwitterButton_pressed() -> void :
	OS.shell_open("https://twitter.com/TweetFurcifer")

func _on_YoutubeButton_pressed() -> void :
	OS.shell_open("https://www.youtube.com/@PlayWithFurcifer/videos")

func _on_DiscordButton_pressed() -> void :
	OS.shell_open("https://discord.gg/sbEkqeUKNr")

func _on_QQButton_pressed():
	
	
	
	
	
	OS.shell_open("http://qm.qq.com/cgi-bin/qm/qr?_wv=1027&k=6zssjoGDmapnJG6q3CkXuwrg2S1JzG2n&authKey=bonULiTLCoSD3jcuZ1NVDLtjqXoeWj0JrZOxxbkMkFH3mMzSDVtX3zyFNp%2B%2F5WZN&noverify=0&group_code=490799286")

func _on_WikiButton_pressed():
	if TranslationServer.get_locale() == "zh_Hans_CN":
		OS.shell_open("https://backpackbattles.wiki.gg/zh/")
	else:
		OS.shell_open("https://backpackbattles.wiki.gg/")

func _on_ChineseWikiButton_pressed():
	OS.shell_open("https://wiki.17173.com/backpackbattles/首页")

func _on_ChineseItemSearch_pressed():
	OS.shell_open("https://www.iyingdi.com/tz/tool/backpackBattles?lang=zh-cn")



func otherModesUIPressed():
	if not Game.draggedItem and not Game.runStarted:
		
		if Game.otherModesUI == null:
			Game.otherModesUI = load("res://Interface/Lobbies/OtherModesUI.tscn").instance()
			Game.otherModesUI.connect("cancel", self, "onOtherModeClosed")
			
		
		Game.otherModesUI.open()
		disableButtons(true)

func onOtherModeClosed():
	checkSavedRunState()


func disableButtons(disabled: bool):


	rankedButton.disabled = disabled
	unrankedButton.disabled = disabled
	concedeButton.disabled = disabled
	continueButton.disabled = disabled
	otherModesButton.disabled = disabled
	customRulesIcon.disabled = disabled

func onCursorWarp():
	if Game.wardrobe.isOpen:
		for button in classButtonsNode.get_children():
			if not button.disabled and button.visible:
				Game.addControlOfInterest(button)
		
		for slotButton in Game.wardrobe.getSlotButtons():
			Game.addControlOfInterest(slotButton)
		
		if Game.wardrobe.chibiButton.visible:
			Game.addControlOfInterest(Game.wardrobe.chibiButton, Vector2( - 30, 0))
		
		
		Game.addPointOfInterest(Vector2(850, 700))
	else:
		for button in warpPointNodes:
			if not button.disabled and button.visible:
				Game.addControlOfInterest(button)
	
	
