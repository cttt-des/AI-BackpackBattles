extends Item

onready var healthNeeded: = int(getP("health"))
onready var mana: = int(getP("mana"))
onready var blind: = int(getP("blind"))
onready var spellSpeed: = int(getP("speed")) / 100.0

func canAffect(item):
	return item.hasType(Type.Spell)

func onPrepare():
	var speed = 0.0
	for item in getAffectedItems():
		if item.hasType(Type.Dark):
			speed += spellSpeed * 2
		else:
			speed += spellSpeed
	addSpeed(speed)

func doCooldownEffect():
	if character().getCurrentHealth() > healthNeeded:
		var event = character().loseHealth(healthNeeded, self)
		giveMana(mana, event)
		inflictBlind(blind, event)
	activate()
