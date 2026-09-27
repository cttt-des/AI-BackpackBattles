extends Bag
var activated = false
var healthThreshold
var battleRageSpeed
var damageResistance

func canApplyEffect(toItem):
	return toItem.hasCooldown()


func onPrepare():
	activated = false
	connectForCombat(character(), "character_damaged", "onDamaged")
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")


func onDamaged(_damage, event):
	if not activated:
		if character().getRelativeHealth() < healthThreshold:
			activated = true
			character().startBattleRage(self, getP_m("dur_rage"), event)
			activate()


func onBattleRageStarted(_event):
	character().changeDamageResistance(damageResistance)
	for item in getItemsInside():
		if canApplyEffect(item):
			item.addSpeed(battleRageSpeed)


func onBattleRageEnded(_event):
	character().changeDamageResistance( - damageResistance)
	for item in getItemsInside():
		if canApplyEffect(item):
			item.reduceSpeed(battleRageSpeed)


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 10

func _readyInit():
	._readyInit()
	healthThreshold = getP("healtht") / 100.0 - 0.0001
	battleRageSpeed = getP("speed_rage") / 100.0
	damageResistance = getP("damresistance")
