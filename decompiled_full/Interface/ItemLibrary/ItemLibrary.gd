extends Node2D

signal open_library
signal items_initialized

enum Tab{
	Filter = 0, 
	Info = 1
}

onready var tabHeaders = [$Tabs / Tab_Filter, $Tabs / Tab_Statistics]
onready var tabs = [$Filter, $InfoPanel]

const defaultMaxWidth = 20
const defaultScale = 0.8
const recordIconScene = preload("res://Interface/ItemLibrary/ItemRecordIcons.tscn")

var maxSize: = Vector2(20, 10000)

onready var animation = $AnimationPlayer
onready var tilemap = $TileMap
onready var tilemapMargin = tilemap.position
onready var bounds = Rect2(Vector2.ZERO, maxSize)
onready var itemsNode = $Items
onready var margin = itemsNode.position

onready var scrollContainer = $ScrollContainer
onready var scrollContainerExtender = $ScrollContainer / Control

onready var defaultTileMapPos = tilemap.position
onready var offsetToTilemap = (itemsNode.position - defaultTileMapPos) / defaultScale

onready var starHint = $InfoPanel / StarHint

onready var groupingMenu = $Filter / Grouping
onready var searchbar = $Filter / Searchbar
onready var resultNumberLabel = $Filter / ResultNumber
onready var grouping_compact = $Filter / Compact

onready var classFilters: Array = Util.getNodesForAllClasses(self, "Filter/Classes/{class}")

onready var filter_Neutral = $Filter / Classes / Neutral

onready var filter_rarity = [
	$Filter / Rarities / Common, 
	$Filter / Rarities / Rare, 
	$Filter / Rarities / Epic, 
	$Filter / Rarities / Legendary, 
	$Filter / Rarities / Godly
]
onready var filter_ClassItems = $Filter / Rarities / ClassItems
onready var filter_UniqueShopItems = $Filter / Rarities / UniqueShopItems

onready var filter_ShopItems = $Filter / Conditions / ShopItems
onready var filter_CraftedItems = $Filter / Conditions / CraftedItems
onready var filter_GatedItems = $Filter / Conditions / GatedItems
onready var treasureItemsLabel = $Filter / Rarities / UniqueShopItems / Label

onready var filter_stacks = {
	Game.EventType.Poison: $Filter / Debuffs / Poison, 
	Game.EventType.Blind: $Filter / Debuffs / Blind, 
	Game.EventType.Cold: $Filter / Debuffs / Cold, 
	Game.EventType.Block: $Filter / Buffs / Block, 
	Game.EventType.Heat: $Filter / Buffs / Heat, 
	Game.EventType.Regeneration: $Filter / Buffs / Regeneration, 
	Game.EventType.Lucky: $Filter / Buffs / Lucky, 
	Game.EventType.Spikes: $Filter / Buffs / Spikes, 
	Game.EventType.Vampirism: $Filter / Buffs / Vampirism, 
	Game.EventType.Mana: $Filter / Buffs / Mana, 
	Game.EventType.Empower: $Filter / Buffs / Empower
}

var filter_types: = {}
var warpPointNodes: Array

var activeTab = - 1
var curPos = Vector2.ZERO
var resetPos = Vector2.ZERO
var items: Dictionary
var sortedDescriptors: Array

var filledCells: Dictionary
const cellSize = 80
var isOpen = false
var maxY: int
var lastRarity: int
var lastPrice: int
var lastVersion
var lastClass: int
var refreshQueued: bool = false

enum Grouping{
	None = 0, 
	Rarity = 1, 
	Price = 2, 
	Version = 3, 
	Class = 4
}

var grouping = Grouping.None
var searchTerm = ""
var numResults = 0
var shownItems = []


func init():
	position = Vector2(3000, 0)
	set_process(false)
	
	
	itemsNode = $Items
	for descriptor in ItemBook.items.values():
		if descriptor.scene != null:
		
			var item = descriptor.instantiate_pooled()
			items[descriptor] = item
			sortedDescriptors.push_back(descriptor)

	sortItems()
	
	Game.UINode.add_child(self)
	
	Util.callNextFrame(Game.UINode, "remove_child", [self])
	
	if Game.USE_ICONS:
		for typeButton in $Filter / Types.get_children():
			if typeButton.name in Item.Type:
				filter_types[Item.Type[typeButton.name]] = typeButton
	else:
		$Filter / Types.hide()
	
	warpPointNodes = Util.getInteractableNodes($Filter)
	Util.walkInteractableNodes($Tabs, warpPointNodes)

var sortingScoreDict: Dictionary

func sortItems():
	sortingScoreDict = {}
	for descr in sortedDescriptors:
		sortingScoreDict[descr] = getSortScore(descr)
	
	Util.sortArrayByDict_reverse(sortedDescriptors, sortingScoreDict)
	
func updateSearchDescriptions():
	for descriptor in items:
		var description = items[descriptor].getDescription(false)
		descriptor.searchDescription = Util.removeDollarCommands(description)
		
		
		

func onGroupingSelected(index, _text):
	grouping = index
	
	sortItems()
	refresh(true)

func updateGroupingList():
	groupingMenu.clearList()
	groupingMenu.addItem(Util.tra("GROUPING_None"))
	groupingMenu.addItem(Util.tra("GROUPING_Rarity"))
	groupingMenu.addItem(Util.tra("GROUPING_Price"))
	groupingMenu.addItem(Util.tra("GROUPING_Version"))
	groupingMenu.addItem(Util.tra("GROUPING_Class"))
	groupingMenu.selectItemByIndex(grouping)
	

func updateStarHint():
	var params = Dictionary()
	if Game.usingController:
		params["button"] = Util.imageToBbcode(
			ControllerIcons.getIconFromAction("show_hints_controller"), 40)
	else:
		params["button"] = Util.tra("KEY_Alt")
	starHint.formatParams = params
	starHint.updateLocale()

func _ready():
	switchToTab(Tab.Filter)
	
	spotlightBlocker.mouse_filter = Control.MOUSE_FILTER_IGNORE
	nextSpotlightButton.hide()
	previousSpotlightButton.hide()
	
	if Game.ITEM_STATISTICS_ENABLED:
		Game.connect("item_gained_focus", self, "onItemGainedFocus")
		
		Game.connect("input_changed", self, "updateStarHint")
		Game.connect("device_changed", self, "updateStarHint")
	
	Game.connect("warp_cursor_menu", self, "onCursorWarp")
	
	updateGroupingList()
	updateStarHint()
	
	
	for classI in Game.Classes_Full.values():
		if Game.isClassUnlocked(classI):
			classFilters[classI].pressed = true
		else:
			classFilters[classI].hide()
	
	var itemInstances = items.values()
	for item in itemInstances:
		item.ownerType = Item.Owner.ItemLibrary
		itemsNode.add_child(item)
		item.initItemLibrary()
		item.hide()
		var res = item.getNormalizedCollisionCells()
		var offset = res[1]
		var icons = recordIconScene.instance()
		item.add_child(icons)
		icons.position = offset + Vector2(20, 24)
		icons.setItem(item)
	
	emit_signal("items_initialized")
	
	updateSearchDescriptions()
	
	
	tabs[Tab.Info].setItem(itemInstances[0])
	
	
	
	
	if not Game.ITEM_STATISTICS_ENABLED:
		$Tab_Filter.hide()
		$Tab_Statistics.hide()
		$TextureRect2.hide()
	
	refresh(false)

func resetFilters():
	filter_ClassItems.set_pressed(true)
	filter_ShopItems.set_pressed(true)
	filter_CraftedItems.set_pressed(true)
	filter_GatedItems.set_pressed(true)
	filter_Neutral.set_pressed(true)
	filter_UniqueShopItems.set_pressed(true)
	for rarityFilter in filter_rarity:
		rarityFilter.set_pressed(true)
	for classFilter in classFilters:
		classFilter.set_pressed(true)
	for stack in filter_stacks:
		filter_stacks[stack].set_pressed(false)
	for type in filter_types:
		filter_types[type].set_pressed(false)
	searchbar.clear()
	searchbar.apply()
	maxSize.x = defaultMaxWidth
	updateZoom()

func sortAndRefresh(popIn: bool = true):
	refreshQueued = false
	sortItems()
	refresh(popIn)

func refresh(popIn: bool):
	clear()
	Game.unhoverAndHideTooltips()
	
	numResults = 0
	maxY = 0
	lastRarity = Item.Rarity.Common - 1
	lastPrice = 0
	lastVersion = null
	lastClass = ItemDescriptor.StuffedClasses.None
	
	var classesStuffed = ItemDescriptor.StuffedClasses.None
	for classI in classFilters.size():
		if classFilters[classI].isOn():
			classesStuffed += ItemDescriptor.stuffClassIndex(classI)
		
	var rarityFilter = {}
	for filterI in filter_rarity.size():
		if filter_rarity[filterI].isOn():
			rarityFilter[filterI] = true
	
	for descriptor in sortedDescriptors:












		
		var originValid = false
		
		if filter_CraftedItems.isOn() and descriptor.isCraftedItem():
			originValid = true
		
		if filter_ShopItems.isOn() and descriptor.isShopItem():
			originValid = true
		
		if filter_GatedItems.isOn() and descriptor.isGatedItem():
			originValid = true
		
		if not originValid:
			continue
		
		var classesValid = false
		if descriptor.classes == ItemDescriptor.StuffedClasses.Neutral:
			if filter_Neutral.isOn():
				classesValid = true
		else:
			if (descriptor.classes & classesStuffed) > 0:
				classesValid = true
		
		if not classesValid:
			continue
		
		var rarityOk = descriptor.rarity in rarityFilter
		var uniqueOk = descriptor.isTreasure() and filter_UniqueShopItems.isOn()
		var classItemOk = ( not descriptor.isTreasure() and 
						descriptor.rarity == Item.Rarity.Unique and 
						filter_ClassItems.isOn())
		
		if not rarityOk and not uniqueOk and not classItemOk:
			continue
		
		
		var stacksOkay = true
		for stack in filter_stacks:
			if filter_stacks[stack].pressed:
				if not stack in descriptor.mentionedStacks:
					stacksOkay = false
		if not stacksOkay:
			continue
		
		
		var typesOkay = true
		for type in filter_types:
			if filter_types[type].pressed:
				if not type in descriptor.types and not type in descriptor.mentionedTypes:
					typesOkay = false
		if not typesOkay:
			continue
		
		if searchTerm != "":
			var inTypes = false
			for type in descriptor.getTranslatedTypes():
				inTypes = (type.findn(searchTerm) != - 1)
				if inTypes: break
			
			var inName = false
			if not inTypes:
				inName = (descriptor.getTranslatedName().findn(searchTerm) != - 1)
			
			
			if not inTypes and not inName:
				if descriptor.searchDescription.findn(searchTerm) == - 1:
					continue



		
		addItem(items[descriptor], popIn)
		numResults += 1
		shownItems.push_back(items[descriptor])
		
	
	scrollContainerExtender.rect_min_size.y = maxY * cellSize * tilemap.scale.y + 50
	updateResultNumber()

func updateResultNumber():
	resultNumberLabel.text = Util.tra("ITEMLIBRARY_NumResults").format({"num": numResults})
	
func incrementCursor():
	curPos.x += 1
	if curPos.x == maxSize.x:
		curPos.x = 0
		curPos.y += 1

func addLineBreak():
	curPos.x = 0
	curPos.y = maxY + 1
	resetPos = curPos
	
	

func addItem(item, popIn: bool):
	
	if grouping == Grouping.Rarity and item.getRarity() > lastRarity:
		if lastRarity != Item.Rarity.Common - 1:
			addLineBreak()
		lastRarity = item.getRarity()
	
	elif grouping == Grouping.Price and item.getPrice() > lastPrice:
		if lastPrice != 0:
			addLineBreak()
		lastPrice = item.getPrice()
	
	elif grouping == Grouping.Version and item.descriptor.version != lastVersion:
		if lastVersion != null:
			addLineBreak()
		lastVersion = item.descriptor.version
	
	elif grouping == Grouping.Class and item.descriptor.classes != lastClass:
		if lastClass != ItemDescriptor.StuffedClasses.None:
			addLineBreak()
		lastClass = item.descriptor.classes
	
	var res = item.getNormalizedCollisionCells()
	var cells = res[0]
	
	findPos(cells)
	updateTilemap(item, cells)
	
	var offset = res[1]
	item.position = curPos * cellSize - offset
	if popIn:
		item.appearInLibrary()
	
	
	
	incrementCursor()
	
	if cells.size() == 1:
		resetPos = curPos
	
	if grouping_compact.isOn():
		curPos = resetPos

func findPos(cells):
	while true:
		var canAdd = true
		for cell in cells:
			var globalCell = cell + curPos
			if not bounds.has_point(globalCell):
				canAdd = false
				break
			else:
				if globalCell in filledCells:
					canAdd = false
					break
		
		if canAdd:
			break
		else:
			incrementCursor()

func updateTilemap(item, cells):
	var tile = item.getRarity() + 10
	for cell in cells:
		var globalCell = cell + curPos
		if globalCell.y > maxY:
			maxY = globalCell.y
		
		filledCells[globalCell] = true
		tilemap.set_cellv(globalCell, tile)

func clear():
	Util.finishTween(spotlightTween)
	var i = 1
	for item in itemsNode.get_children():
		
		
		item.global_position = Vector2( - 10000 * i, 0)
		i += 1
		
	
	tilemap.clear()
	filledCells.clear()
	shownItems.clear()
	curPos = Vector2.ZERO
	resetPos = Vector2.ZERO

func filterChanged():
	if not refreshQueued:
		refreshQueued = true
		call_deferred("sortAndRefresh")

func updateLocale():
	
	for child in get_children() + tabs[Tab.Filter].get_children():
		if child.is_in_group("Localized"):
			child.updateLocale()
		for grandchild in child.get_children():
			if grandchild.is_in_group("Localized"):
				grandchild.updateLocale()
	
	treasureItemsLabel.updateLocale()
	tabs[Tab.Info].updateLocale()
	
	updateGroupingList()
	updateResultNumber()


func open():
	if not Game.draggedItem and not is_inside_tree():
		Game.UINode.add_child_below_node(Game.UINode.get_node("ItemLibraryPlaceholder"), self)
		isOpen = true
		Game.openMenu()
		Game.pause(Game.PauseSource.RecipeBook)
		Sound.playSound_process(Game.transitionSounds[2], 0, 0.9)
		
		animation.play("Open")
		InputBlocker.activate(InputBlocker.Source.PopupAnimation, false)
		for itemDescr in items:
			items[itemDescr].deactivateParticles()
		starHint.hide()
		
		
		Util.callNextFrame(self, "open_late1")
		
		if not Game.isTutorialDone(Game.TutorialSteps.ItemLibrary):
			Game.setTutorialDone(Game.TutorialSteps.ItemLibrary)
			Game.itemLibraryTutorialAni.play("RESET")
		
		emit_signal("open_library")

func open_late1():
	Util.callNextFrame(self, "open_late2")

func open_late2():
	for item in items:
		items[item].get_node("RecordIcons").setItem(items[item])
	
	for child in get_children():
		if child != itemsNode:
			Util.localizeFonts(child)
	updateLocale()
	Util.callNextFrame(self, "open_late3")

func open_late3():
	InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.shopSceneNode)
	InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.playerNode)
	InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.titleScreen)
	for node in get_tree().get_nodes_in_group("PinnedControl"):
		InputBlocker.disableSingleControl(InputBlocker.Source.Popup, node)

func opened():
	InputBlocker.deactivate(InputBlocker.Source.PopupAnimation, false)
	Game.openedMenu()

func close():
	if animation.current_animation == "":
		endSpotlight()
		animation.play("Close")
		Game.unhoverAndHideTooltips()
		InputBlocker.activate(InputBlocker.Source.PopupAnimation, false)
		Sound.playSound_process(Game.transitionSounds[1], 0, 1.2)
		get_tree().call_group("RecordIcon", "hide")
		get_tree().call_group("ButtonWithTooltip", "onHoverEnd")
		Game.closeMenu()

func closed():
	Game.unpause(Game.PauseSource.RecipeBook)
	InputBlocker.deactivate(InputBlocker.Source.PopupAnimation, false)
	InputBlocker.restoreAllControls(InputBlocker.Source.Popup)
	isOpen = false
	get_parent().remove_child(self)

func spotlightBlocker_gui_input(event: InputEvent):
	cancelSpotlight(event)

func cancelSpotlight(event: InputEvent):
	if (Util.isClickEvent(event) and spotlightItem != null and 
		Util.getFrameCounter_process() > spotlightStartFrame + 10):
		endSpotlight()

func _unhandled_input(event: InputEvent):
	if InputBlocker.isActive(): return
	
	if not isOpen: return
	
	if ( not previousSpotlightButton.isHovered and 
		not nextSpotlightButton.isHovered):
		
		cancelSpotlight(event)
	
	if event is InputEventMouseButton and event.is_pressed():
		if spotlightItem == null:
			if event.button_index == BUTTON_WHEEL_UP:
				if event.control:
					zoomIn()
				else:
					scrollContainer.scroll_vertical -= 30
					updateScroll()
				
			if event.button_index == BUTTON_WHEEL_DOWN:
				if event.control:
					zoomOut()
				else:
					scrollContainer.scroll_vertical += 30
					updateScroll()
	
	elif Util.isActionPressed_event(event, "options"):
		get_tree().set_input_as_handled()
		close()
	
	elif Util.isActionPressed_event(event, "open_library"):
		get_tree().set_input_as_handled()
		close()
	
	elif event.is_action_pressed("next_tab"):
		if spotlightItem == null:
			if Game.ITEM_STATISTICS_ENABLED:
				toggleTab()
		else:
			onNextSpotlightPressed()
	
	elif event.is_action_pressed("previous_tab"):
		if spotlightItem == null:
			if Game.ITEM_STATISTICS_ENABLED:
				toggleTab()
		else:
			onPreviousSpotlightPressed()
		
	elif Util.isActionPressed_event(event, "show_hints") and Game.ITEM_STATISTICS_ENABLED:
		get_tree().call_group("RecordIcon", "show")
		
	elif Util.isActionReleased_event(event, "show_hints") and Game.ITEM_STATISTICS_ENABLED:
		hideRecordIcons()
	
	elif (spotlightItem == null and 
		event is InputEventKey and 
		event.pressed):
		var unicode = event.get_unicode()
		if unicode != 0:
			searchbar.append_at_cursor(char(unicode))
			searchbar.onTextChanged("")
		elif event.scancode == KEY_BACKSPACE:
			searchbar.delete_char_at_cursor()
			












func hideRecordIcons():
	if isOpen:
		get_tree().call_group("RecordIcon", "hide")

func _process(_delta):
	updateScroll()

func updateScroll():
	itemsNode.position.y = margin.y - scrollContainer.scroll_vertical
	tilemap.position.y = tilemapMargin.y - scrollContainer.scroll_vertical

func onScrollStarted():
	set_process(true)

func onScrollEnded():
	set_process(false)

func zoomIn():
	maxSize.x -= 1
	updateZoom()

func zoomOut():
	maxSize.x += 1
	updateZoom()

func updateZoom():
	maxSize.x = clamp(maxSize.x, 7, 46)
	
	var scaling: float = (defaultMaxWidth / maxSize.x) * defaultScale
	itemsNode.scale = Vector2(scaling, scaling)
	itemsNode.position = defaultTileMapPos + offsetToTilemap * itemsNode.scale
	margin = itemsNode.position
	tilemap.scale = itemsNode.scale
	bounds = Rect2(Vector2.ZERO, maxSize)
	updateScroll()
	sortAndRefresh(false)

func onSearchTextChanged(newText):
	searchTerm = newText
	searchTerm = searchTerm.replace("$", "")
	searchTerm = searchTerm.replace("[", "")
	searchTerm = searchTerm.replace("]", "")
	refresh(true)

func onItemGainedFocus(item):
	if not isOpen: return
	if not item.ownerType == Item.Owner.ItemLibrary: return
	
	if spotlightItem != null: return
	
	tabs[Tab.Info].setItem(item)


func _on_Tab_Filter_toggled(button_pressed):
	toggleTab()

func _on_Tab_Statistics_toggled(button_pressed):
	toggleTab()

func toggleTab():
	if activeTab == Tab.Filter:
		switchToTab(Tab.Info)
	else:
		switchToTab(Tab.Filter)

func switchToTab(tab: int):
	if tab == activeTab: return
	
	if spotlightItem != null and tab != Tab.Info:
		endSpotlight()
	
	activeTab = tab
	
	for i in tabs.size():
		if i != activeTab:
			tabs[i].visible = false
			tabHeaders[i].set_pressed_no_signal(false)
	
	tabs[tab].visible = true
	tabHeaders[tab].set_pressed_no_signal(true)


onready var spotlightBlocker = $Spotlight / Blocker
onready var spotLightDarkLayer = $Spotlight / DarkLayer
onready var nextSpotlightButton = $Spotlight / AboveItem / NextItem
onready var previousSpotlightButton = $Spotlight / AboveItem / PreviousItem

var spotlightItem = null
var spotlightTween: SceneTreeTween
var spotlightTooltipTween: SceneTreeTween
var spotlightStartPos: Vector2
var spotlightOffscreenPos
var spotlightStartScale: Vector2
var spotlightStartZ: int
var spotlightStartFrame: int
var spotlightStartTab: int

const SPOTLIGHT_POS = Vector2(985, 555)
const SPOTLIGHT_DUR = 0.3
const SPOTLIGHT_BACK_DUR = 0.4

func getSpotlightItem():
	return spotlightItem

func setSpotlightDescriptor(descriptor):
	setSpotlightItem(getInstance(descriptor))

func setSpotlightItem(item):
	if item == spotlightItem:
		return
	
	
	if spotlightStartFrame == Util.getFrameCounter_process():
		return
	
	
	if spotlightItem != null:
		
		movebackSpotlightItem(true)
	else:
		Util.finishTween(spotlightTween)
		spotlightTween = Util.refreshTween(spotlightTween).set_parallel(true)
		spotlightTween.set_trans(Tween.TRANS_QUAD)
		spotlightStartTab = activeTab
	
	switchToTab(Tab.Info)
	nextSpotlightButton.show()
	previousSpotlightButton.show()
	scrollContainer.scrollEnabled = false
	
	spotlightStartFrame = Util.getFrameCounter_process()
	spotlightItem = item
	tabs[Tab.Info].setItem(spotlightItem)
	
	var tooltipExists = item.tooltip != null
	spotlightItem.setSpotlight(true)
	spotlightItem.clickArea.hide()
	spotlightItem.playPickupSound()
	
	
	if spotlightItem.position.x < 0:
		spotlightOffscreenPos = spotlightItem.position
		spotlightItem.position = Vector2(1130, - 200)
	else:
		spotlightOffscreenPos = null
	
	spotlightStartPos = spotlightItem.position
	spotlightStartScale = spotlightItem.global_scale
	spotlightStartZ = spotlightItem.z_index
	
	spotlightBlocker.mouse_filter = Control.MOUSE_FILTER_STOP
	
	var offset = spotlightItem.getSpriteOffset() / spotlightItem.sprite.global_scale
	var adjustedPos = SPOTLIGHT_POS + offset
	
	spotlightTween.tween_property(spotLightDarkLayer, 
		"modulate", Color.white, SPOTLIGHT_DUR)
	spotlightTween.tween_property(spotlightItem, 
		"global_position", adjustedPos, SPOTLIGHT_DUR)
	spotlightTween.tween_property(spotlightItem, 
		"global_scale", Vector2.ONE, SPOTLIGHT_DUR)
	spotlightItem.z_index = 4

	call_deferred("setSpotlightItem_deferred", tooltipExists)

func setSpotlightItem_deferred(tooltipExists):
	
	
	var tooltipTopLeft = Vector2(20, SPOTLIGHT_POS.y - spotlightItem.tooltip.rect_size.y * 0.5)
	if tooltipExists:
		spotlightTooltipTween = Util.refreshTween(spotlightTooltipTween)
		spotlightTooltipTween.tween_property(spotlightItem.tooltip, "rect_global_position", 
			tooltipTopLeft, SPOTLIGHT_DUR)
	else:
		spotlightItem.tooltip.rect_global_position = tooltipTopLeft
	
	if spotlightItem.buildIntoRecipesTooltip != null:
		var recipeTooltipTop = SPOTLIGHT_POS.y - spotlightItem.buildIntoRecipesTooltip.rect_size.y * 0.5
		
		spotlightTooltipTween = Util.ensureTween(spotlightTooltipTween)
		spotlightTooltipTween.tween_property(spotlightItem.buildIntoRecipesTooltip, 
			"rect_global_position:y", recipeTooltipTop, SPOTLIGHT_DUR)
	
func endSpotlight():
	if spotlightItem == null: return
	movebackSpotlightItem(false)
	
	spotlightItem = null
	nextSpotlightButton.hide()
	previousSpotlightButton.hide()
	scrollContainer.scrollEnabled = true
	
	switchToTab(spotlightStartTab)

func movebackSpotlightItem(nextItemQueued: bool):
	
	
	Util.finishTween(spotlightTween)
	
	spotlightTween = Util.refreshTween(spotlightTween).set_parallel(true)
	spotlightTween.set_trans(Tween.TRANS_QUAD)
	if not nextItemQueued:
		spotlightTween.tween_property(spotLightDarkLayer, "modulate", Color.transparent, SPOTLIGHT_BACK_DUR)
	spotlightTween.tween_property(spotlightItem, "position", spotlightStartPos, SPOTLIGHT_BACK_DUR)
	spotlightTween.tween_property(spotlightItem, "global_scale", spotlightStartScale, SPOTLIGHT_BACK_DUR)
	spotlightTween.tween_callback(self, "resetSpotlightItem", [spotlightItem, spotlightStartZ, spotlightOffscreenPos]).set_delay(SPOTLIGHT_BACK_DUR)
	
	spotlightItem.setSpotlight(false)
	spotlightItem.z_index = 4
	spotlightBlocker.mouse_filter = Control.MOUSE_FILTER_IGNORE

func resetSpotlightItem(item, z, offscreenPos):
	item.z_index = z
	item.resetZ()
	item.clickArea.show()
	if offscreenPos != null:
		item.position = offscreenPos

func onNextSpotlightPressed():
	var index = shownItems.find(spotlightItem)
	var numShownItems = shownItems.size()
	setSpotlightItem(shownItems[(index + 1) % numShownItems])
	get_tree().set_input_as_handled()

func onPreviousSpotlightPressed():
	var index = shownItems.find(spotlightItem)
	var numShownItems = shownItems.size()
	setSpotlightItem(shownItems[(index + numShownItems - 1) % numShownItems])
	get_tree().set_input_as_handled()

func getInstance(descriptor: ItemDescriptor) -> Item:
	return items[descriptor]

func getSortScore(item: ItemDescriptor):
	var score = 0.0
	
	if grouping == Grouping.Price:
		score += item.getPrice() * 1000000
	
	elif grouping == Grouping.Version:
		score += - item.version * 1000000
	
	score += item.rarity * 100000
	
	if item.hasType(Item.Type.Bag):
		score += 20000
	
	if grouping == Grouping.Class:
		score += item.classes * 1000000
	else:
		if item.hasType(Item.Type.Skill):
			if item.classes != ItemDescriptor.StuffedClasses.Neutral:
				score += item.classes * 0.01
		else:
			if item.classes != ItemDescriptor.StuffedClasses.Neutral:
				score += item.classes * 1000
	
	if item.isCraftedItem():
		score += 100
	
	if item.isGatedItem():
		score += 90
		
	if item.isMeleeWeapon():
		score -= 2
	elif item.isRangedWeapon():
		score -= 1
	elif item.hasType(Item.Type.Shield):
		score += 1
	elif item.hasType(Item.Type.Armor):
		score += 2
	elif item.hasType(Item.Type.Accessory):
		score += 4
	elif item.hasType(Item.Type.Skill):
		if item.appearRounds[0] == Game.SKILL_ROUND1:
			if item.appearRounds.size() == 2:
				score -= 2
			else:
				score -= 3
		else:
			
			score -= 1
	else:
		score += 3
	
	score += (item.itemIndex / float(ItemBook.getNumItems())) * 0.1
	
	return score

func onCursorWarp():
	if isOpen:
		if spotlightItem != null:
			Game.addControlOfInterest(nextSpotlightButton)
			Game.addControlOfInterest(previousSpotlightButton)
			Game.addControlOfInterest($Tabs / CloseButton)
		else:
			for descriptor in items:
				var item = items[descriptor]
				if item.position.x >= 0:
					Game.addPointOfInterest(item.global_position, scrollContainer, item)
				
			for node in warpPointNodes:
				if node.is_visible_in_tree():
					Game.addControlOfInterest(node)
		
		
		
