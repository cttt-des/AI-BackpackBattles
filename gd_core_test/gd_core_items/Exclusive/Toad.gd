extends Item
var affectedItemsDict: Dictionary
var gainedBuffs: int
var usedBuffs: int
var gainedThreshold
var usedThreshold
var luck
var mana
var luck2
var mana2

func canAffect(item):
	return item.gainsBuffs() or item.usesBuffs()


func onPrepare():
	affectedItemsDict = ctx.util.arrayAsIndexDict(getAffectedItems())
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
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

func _readyInit():
	._readyInit()
	gainedThreshold = int(getP("gained"))
	usedThreshold = int(getP("used"))
	luck = int(getP("luck"))
	mana = int(getP("mana"))
	luck2 = int(getP("luck2"))
	mana2 = int(getP("mana2"))
