extends Item
var manaNeeded
var regen
var spellSpeed

func canAffect(item):
	return item.hasType(CoreConst.Type.Spell)


func onPrepare():
	var speed = 0.0
	for item in getAffectedItems():
		if item.hasType(CoreConst.Type.Holy):
			speed += spellSpeed * 2
		else:
			speed += spellSpeed
	addSpeed(speed)


func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		giveRegeneration(regen, event)
		heal(getP_m("heal"), event)
	activate()

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("mana"))
	regen = int(getP("regen"))
	spellSpeed = int(getP("speed")) / 100.0
