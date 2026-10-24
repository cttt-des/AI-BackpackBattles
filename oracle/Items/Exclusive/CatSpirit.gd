extends SpiritCompanion

const pickupSound = preload("res://Assets/Sound/Cat1.ogg")
const dropSound = preload("res://Assets/Sound/Cat2.ogg")

onready var manaNeeded: = int(getP("manat"))
onready var luck: = int(getP("luck"))
onready var empower: = int(getP("empower"))

func canAffect(item):
	return item.canDamage()

func onPrepare():
	for item in getAffectedItems():
		item.addCritChancePercent(getChance())

func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		giveLucky(luck, event)
		giveEmpower(empower, event)
	
	activate()


func playPickupSound():
	Sound.playSound_process(pickupSound, - 12, Util.randPitch(0.1))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 18, Util.randPitch(0.1))
