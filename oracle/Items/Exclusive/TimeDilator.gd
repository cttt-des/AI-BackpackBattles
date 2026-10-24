extends Item

const timeDilatorAni = preload("res://Items/Animations/TimeDilatorAni.tscn")
const timeDilatorSound = preload("res://Assets/Sound/Tick2.wav")

onready var slow: = getP("slow") / 100.0
onready var speedUp: = getP("speed") / 100.0

var tickI: int

func onPrepare():
	tickI = 0
	var allItems = Game.PLAYER.INVENTORY.getItems() + Game.OPPONENT.INVENTORY.getItems()
	for item in allItems:
		if item.isWeapon():
			item.reduceSpeed(slow)

func doCooldownEffect():
	var slowestCd: = 0.0
	var slowestItem = null
	
	for item in inventory.getItems():
		if item.hasCooldown() and item.isCooldownActive():
			var cd = item.getModifiedCooldown()
			if cd > slowestCd:
				slowestCd = cd
				slowestItem = item
	
	
	slowestItem.addSpeed(speedUp)
	activate()
	var ani = ObjectPool.instance(timeDilatorAni)
	get_parent().add_child(ani)
	ani.global_position = slowestItem.global_position
	ani.z_index = z_index + 2
	tickI += 1

func playActivationSound():
	var pitch = 1.0 if tickI % 2 == 0 else 0.7
	Sound.playSound(timeDilatorSound, 5, pitch)
	
