extends SpiritCompanion

const pickupSound = preload("res://Assets/Sound/Badger1.ogg")
const dropSound = preload("res://Assets/Sound/Badger2.ogg")

onready var healthThreshold = getP("healtht") / 100.0
onready var manaNeeded: = int(getP("manat"))
var activated: bool

func canAffect(item):
	return item.hasType(Type.Nature)

func onPrepare():
	activated = false
	connectForCombat(character(), "character_damaged", "onDamaged")

func onDamaged(_healthChange, event):
	if not activated and character().getRelativeHealth() < healthThreshold:
		activated = true
		heal(character().getMaxHealth() * getP_m("heal") / 100.0, event)

func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		giveMaxHealth(getP_m("maxhealth") + getNumAffectedItems() * 
			getP_m("maxhealth_bonus"), event)
	activate()

func playPickupSound():
	Sound.playSound_process(pickupSound, - 12, Util.randPitch(0.1))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 6, Util.randPitch(0.1))
