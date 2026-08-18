extends Item

const pickupSound = preload("res://Assets/Sound/Toad1.wav")
const dropSound = preload("res://Assets/Sound/Toad2.wav")

onready var gainedThreshold: = int(getP("gained"))
onready var usedThreshold: = int(getP("used"))
onready var luck: = int(getP("luck"))
onready var mana: = int(getP("mana"))
onready var luck2: = int(getP("luck2"))
onready var mana2: = int(getP("mana2"))

var affectedItemsDict: Dictionary
var gainedBuffs: int
var usedBuffs: int

func canAffect(item):
	return item.gainsBuffs() or item.usesBuffs()

func onPrepare():
	affectedItemsDict = Util.arrayAsIndexDict(getAffectedItems())
	connectToCharacterBuffs("onBuffsChanged")
	gainedBuffs = 0
	usedBuffs = 0

func onGainThresholdReached(ticks, event):
	heal(ticks * getP_m("heal"), event)
	miniActivate()

func onUseThresholdReached(ticks, event):
	giveLucky(ticks * luck, event)
	giveMana(ticks * mana, event)
	miniActivate()

func onBuffsChanged(amount, event):
	if event.getOrigin() in affectedItemsDict:
		if amount > 0:
			gainedBuffs += amount
			var ticks = gainedBuffs / gainedThreshold
			if ticks > 0:
				onGainThresholdReached(ticks, event)
				gainedBuffs %= gainedThreshold
		else:
			
			usedBuffs += int(abs(amount))
			var ticks = usedBuffs / usedThreshold
			if ticks > 0:
				onUseThresholdReached(ticks, event)
				usedBuffs %= usedThreshold

func doCooldownEffect():
	giveLucky(luck2)
	giveMana(mana2)
	activate()

func playPickupSound():
	Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))
