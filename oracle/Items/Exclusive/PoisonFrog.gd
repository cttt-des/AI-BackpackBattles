extends Item

const pickupSound = preload("res://Assets/Sound/Toad1.wav")
const dropSound = preload("res://Assets/Sound/Toad2.wav")

onready var gainedThreshold: int = getP("gained")
onready var usedThreshold: int = getP("used")
onready var poison: = int(getP("poison"))
onready var mana: = int(getP("mana"))

var affectedItemsDict: Dictionary
var gainedBuffs: int
var usedBuffs: int

func canAffect(item):
	return item.gainsBuffs() or item.usesBuffs()

func onPrepare():
	affectedItemsDict.clear()
	for item in getAffectedItems():
		affectedItemsDict[item] = true
	connectToCharacterBuffs("onBuffsChanged")
	gainedBuffs = 0
	usedBuffs = 0
	
func onBuffsChanged(amount, event):
	if event.getOrigin() in affectedItemsDict:
		if amount > 0:
			gainedBuffs += amount
			var ticks = gainedBuffs / gainedThreshold
			if ticks > 0:
				heal()
				
				
				gainedBuffs %= gainedThreshold
				miniActivate()
				
		else:
			
			usedBuffs += int(abs(amount))
			var ticks = usedBuffs / usedThreshold
			if ticks > 0:
				inflictPoison(ticks * poison, event)
				giveMana(ticks * mana, event)
				usedBuffs %= usedThreshold
				miniActivate()

func doCooldownEffect():
	inflictPoison(getP("poison2"))
	giveMana(getP("mana2"))
	activate()

func playPickupSound():
	var pitch = Util.rng.randf_range(0.9, 1.1)
	Sound.playSound_process(pickupSound, - 4, pitch)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = Util.rng.randf_range(0.9, 1.1)
	Sound.playSound(dropSound, volume - 4, pitch)
