extends Node2D

signal closed

const openSound = preload("res://Assets/Sound/Swoosh1.wav")
const buttonScene = preload("res://Interface/Wardrobe/SkinSlotButton.tscn")
const iconScene = preload("res://Interface/Wardrobe/SkinHeader.tscn")

var playerZ
onready var unlockHint = $UnlockHint
onready var unlockHintLabel = $UnlockHint / Hint
onready var priceTag = $UnlockHint / Price
onready var hboxContainer = $ScrollContainer / HBoxContainer
onready var animation = $AnimationPlayer
onready var trophyCounter = $TrophyCounter
onready var chibiButton = $ChibiButton

var selectedSkins: = []
var isOpen = false
var slotButtons: = []

func _ready():
	Game.connect("character_changed", self, "onCharacterSelected")
	Game.connect("style_changed", self, "onSwitchStyle")
	Game.connect("input_changed", self, "updateHint")





	playerZ = Game.PLAYER.spriteNode.z_index

func open():
	isOpen = true
	Game.UINode.add_child_below_node(Game.UINode.get_node("WardrobePlaceholder"), self)
	animation.play("Open")
	Sound.playSound(openSound, - 6)
	Sound.setMuffledSound(true)
	initSkins()
	Game.PLAYER.spriteNode.z_index = playerZ + 20
	Game.titleScreen.classButtonsNode.z_index = 2
	
	trophyCounter.updateValue()
	Util.updateLocaleInSubtree(self)

func close():
	if visible:
		emit_signal("closed")
		animation.play("Close")
		Sound.playSound(openSound, - 6, 1.2)
		Sound.setMuffledSound(false)

func finishedClosing():
	isOpen = false
	Game.PLAYER.spriteNode.z_index = playerZ
	Game.titleScreen.classButtonsNode.z_index = 0
	get_parent().remove_child(self)

func onCharacterSelected():
	if isOpen:
		initSkins()

func onSwitchStyle():
	if isOpen:
		initSkins()

func initSkins():
	for child in hboxContainer.get_children():
		child.name = "deleting"
		child.queue_free()
	
	slotButtons.clear()
	
	var skins = SkinBook.getSkinsForClass(Game.curClass, 
		int(Game.getEffectiveChibiMode())).duplicate()
	
	if not Game.isClassUnlocked(): return
	if skins.empty(): return
	
	skins.sort_custom(SkinBook.OrderSorter, "sort")
	
	selectedSkins.clear()
	for slot in Game.SkinSlot:
		var skinId = Game.getSelectedSkin(Game.SkinSlot[slot])
		selectedSkins.push_back(skinId)
	
	for skin in skins:
		var vbox = VBoxContainer.new()
		vbox.set("custom_constants/separation", 50)
		hboxContainer.add_child(vbox)
		vbox.name = String(skin.id)
		
		var icon = iconScene.instance()
		vbox.add_child(icon)
		icon.setSkin(skin)
		slotButtons.push_back(icon)
		
		for slot in Game.SkinSlot.size():
			var slotButton = buttonScene.instance()
			vbox.add_child(slotButton)
			slotButton.init(skin, slot)
			if Game.isSkinUnlocked(slot, skin.id):
				slotButton.setUnlocked()
			slotButtons.push_back(slotButton)
	
	selectAndPreviewSkinSlots()

func getSlotButtons():
	return slotButtons

func selectAndPreviewSkinSlots():
	for slot in selectedSkins.size():
		var button = getSkinSlotButton(slot, selectedSkins[slot])
		button.select()
		button.preview()

const skinSlotNodeFormat = "{skin}/{slot}"

func getSkinSlotButton(slot: int, skinId: int):
	return hboxContainer.get_node(skinSlotNodeFormat.format(
		{"skin": skinId, "slot": slot}))

func onSkinIconHovered(icon):
	if isOpen:
		for slot in Game.SkinSlot.size():
			var button = getSkinSlotButton(slot, icon.skin.id)
			button.onHover()

func onSkinIconUnhovered(icon):
	for slot in Game.SkinSlot.size():
		var button = getSkinSlotButton(slot, icon.skin.id)
		button.onHoverEnd()

func onSkinIconSelected(icon):
	for slot in Game.SkinSlot.size():
		if Game.isSkinUnlocked(slot, icon.skin.id):
			var button = getSkinSlotButton(slot, icon.skin.id)
			button.select()
			onSlotSelected(button)


func onSlotHovered(slotButton):
	unlockHint.global_position.y = min(slotButton.rect_global_position.y, 900)

func onSlotUnhovered(slotButton):
	getSkinSlotButton(slotButton.slot, selectedSkins[slotButton.slot]).preview()
	unlockHint.hide()

func onSlotSelected(slotButton):
	var slot = slotButton.slot
	if selectedSkins[slot] != slotButton.skin.id:
		
		var oldButton = getSkinSlotButton(slot, selectedSkins[slot])
		oldButton.unselect()
		selectedSkins[slot] = slotButton.skin.id
		Game.selectSkin(slot, slotButton.skin.id)

func showPriceTag(price: int):
	unlockHint.show()
	priceTag.bbcode_text = "[center]" + String(price)
	if Game.getTrophies() < price:
		priceTag.set("custom_colors/default_color", Color(1, 0.285156, 0.285156))
	else:
		priceTag.set("custom_colors/default_color", Game.SOFTWHITE)

func updateHint():
	pass
	
	
