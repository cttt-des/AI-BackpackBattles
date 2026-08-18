extends Item

const revealPulseScene = preload("res://Items/Animations/RevealPulse.tscn")
const revealSound = preload("res://Assets/Sound/Reveal.ogg")

func _ready():
	connect("dropped", self, "onDropped")

func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		call_deferred("identifyAmulet", dropRes)

func identifyAmulet(dropResult):
	
	var amulet = ItemBook.generateItem(Util.pickRandomElement(ItemBook.amulets))
	if wasAddedToInventory(dropResult):
		inventory.replaceItem(self, amulet)
	else:
		Game.STORAGEBOX.removeItem(self)
		collisionShape.disabled = true
		discard()
		Game.playerNode.add_child(amulet)
		
		amulet.global_position = global_position
		amulet.addToStorageBox(true, true, true, global_position)
	
	Sound.playSound(revealSound, 6)
	var pulse = ObjectPool.instance(revealPulseScene)
	pulse.self_modulate = amulet.amuletColor
	Game.playerNode.add_child(pulse)
	pulse.global_position = global_position
	pulse.get_node("AnimationPlayer").play("Activate")
	Game.saveRunState()
	finishReplacement()

func getRelatedItemColumns() -> int:
	return 4

func getRelatedItemHeight() -> int:
	return 100
