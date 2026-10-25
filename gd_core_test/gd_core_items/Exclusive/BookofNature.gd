extends Item
var regenNeeded
var lucky
var spikes
var spellSpeed

func canAffect(item):
	return item.hasType(CoreConst.Type.Spell)


func onPrepare():
	var speed = 0.0
	for item in getAffectedItems():
		if item.hasType(CoreConst.Type.Nature):
			speed += spellSpeed * 2
		else:
			speed += spellSpeed
	addSpeed(speed)


func doCooldownEffect():
	if character().getRegeneration() >= regenNeeded:
		var event = useRegeneration(regenNeeded)
		giveLucky(lucky, event)
		giveSpikes(spikes, event)
	activate()

func _readyInit():
	._readyInit()
	regenNeeded = int(getP("regen"))
	lucky = int(getP("luck"))
	spikes = int(getP("spikes"))
	spellSpeed = int(getP("speed")) / 100.0
