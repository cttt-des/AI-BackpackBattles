extends Item

onready var manaNeeded: = int(getP("mana"))
onready var regen: = int(getP("regen"))
onready var spellSpeed: = int(getP("speed")) / 100.0

func canAffect(item):
	return item.hasType(Type.Spell)

func onPrepare():
	var speed = 0.0
	for item in getAffectedItems():
		if item.hasType(Type.Holy):
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
