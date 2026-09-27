extends Item
var manaNeeded
var cold
var spellSpeed

func canAffect(item):
	return item.hasType(CoreConst.Type.Spell)


func onPrepare():
	var speed = 0.0
	for item in getAffectedItems():
		if item.hasType(CoreConst.Type.Ice):
			speed += spellSpeed * 2
		else:
			speed += spellSpeed
	addSpeed(speed)


func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		inflictCold(cold, event)
	activate()

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("mana"))
	cold = int(getP("cold"))
	spellSpeed = int(getP("speed")) / 100.0
