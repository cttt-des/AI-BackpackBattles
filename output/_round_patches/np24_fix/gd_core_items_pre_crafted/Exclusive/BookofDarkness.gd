extends Item
var healthNeeded
var mana
var blind
var spellSpeed

func canAffect(item):
	return item.hasType(CoreConst.Type.Spell)


func onPrepare():
	var speed = 0.0
	for item in getAffectedItems():
		if item.hasType(CoreConst.Type.Dark):
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

func _readyInit():
	._readyInit()
	healthNeeded = int(getP("health"))
	mana = int(getP("mana"))
	blind = int(getP("blind"))
	spellSpeed = int(getP("speed")) / 100.0
