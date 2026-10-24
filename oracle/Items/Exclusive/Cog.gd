extends Item

const cogWheelAnimation = preload("res://Items/Exclusive/Animations/CogCraftingAnimation.tscn")
const craftingSound = preload("res://Assets/Sound/Gears.mp3")

func canAffect(item):
	return item.isCrafted()

func onCombatStart():
	var numAffected = getNumAffectedItems()
	if numAffected > 0:
		giveBlock(getBlock() * numAffected)
		activate()

func onSold():
	var ani = cogWheelAnimation.instance()
	Game.playerNode.add_child(ani)
	ani.get_node("AnimationPlayer").play("Turn")
	Sound.playSound(craftingSound, 4)
	Game.fuseAll()

func getSellPrice():
	return 0
