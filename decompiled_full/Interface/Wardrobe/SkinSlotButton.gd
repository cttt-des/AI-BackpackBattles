extends Control

const notEnoughTrophiesLabel = preload("res://Interface/NotEnoughTrophiesLabel.tscn")
const normalTex = preload("res://Interface/Wardrobe/SkinSlotButton.png")
const hoverTex = preload("res://Interface/Wardrobe/SkinSlotButton_hovered.png")

const trophyParticles = preload("res://Interface/TrophyParticles.tscn")
const buySound1 = preload("res://Assets/Sound/Glitter.wav")
const buySound2 = preload("res://Assets/Sound/Bell.wav")
const notEnoughTrophiesSound = preload("res://Assets/Sound/Fanfare_sadtoot.ogg")

onready var icon = $Icon
onready var button = $Button
onready var lock = $Locked

var skin: CharacterSkin
var slot: int
var notEnoughTrophiesReadyTime = 0.0

var hovered = false
var selected = false
var unlocked = false

func init(_skin: CharacterSkin, _slot: int):
	skin = _skin
	slot = _slot
	icon.texture = skin.icon
	name = str(slot)
	icon.hide()
	
	if skin.prices[slot] == - 1:
		
		button.hide()
		lock.hide()
	
	

func setDisabled():
	icon.hide()
	lock.hide()

func preview():
	Game.PLAYER.sprite.setSkin(slot, skin.id)

func select():
	
	selected = true
	icon.show()

func unselect():
	selected = false
	icon.hide()

func onMouseEntered():
	onHover()
	if not unlocked:
		Game.wardrobe.showPriceTag(skin.prices[slot])

func onHover():
	preview()
	button.texture_normal = hoverTex
	Game.wardrobe.onSlotHovered(self)

func onHoverEnd():
	button.texture_normal = normalTex
	Game.wardrobe.onSlotUnhovered(self)

func onPressed():
	
	if unlocked:
		select()
		Game.wardrobe.onSlotSelected(self)
	else:
		if Game.getTrophies() < skin.prices[slot]:
			if Util.time >= notEnoughTrophiesReadyTime:
				var label = ObjectPool.instance(notEnoughTrophiesLabel)
				Game.UINode.add_child(label)
				label.global_position = lock.global_position - Vector2(0, 80)
				notEnoughTrophiesReadyTime = Util.time + 1.0
				Sound.playSound(notEnoughTrophiesSound, - 8)
		else:
			unlock()

func setLocked():
	unlocked = false
	lock.show()

func setUnlocked():
	unlocked = true
	lock.hide()

func unlock():
	Game.loseTrophies(skin.prices[slot])
	Game.unlockSkin(slot, skin.id)
	var particles = ObjectPool.particleOneShot(trophyParticles, Game.UINode)
	particles.global_position = lock.global_position
	Sound.playSound(buySound1)
	Sound.playSound(buySound2)
	unlocked = true
	lock.hide()
	select()
	Game.wardrobe.onSlotSelected(self)
