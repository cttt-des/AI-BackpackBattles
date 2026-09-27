extends Item
var activated = false
var healthThreshold
var battleRageSpeed
var battleRageDamReduction

func onAddToInventory():
	pass

func onRemoveFromInventory():
	pass

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	activated = false
	connectForCombat(character(), "character_damaged", "onDamaged")
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")


func onDamaged(_damage, event):
	if not activated:
		if character().getRelativeHealth() < healthThreshold:
			activated = true
			character().startBattleRage(self, getP_m("dur"), event)
			activate()


func onBattleRageStarted(_event):
	character().changeDamageResistance(battleRageDamReduction)
	for item in getAffectedItems():
		item.addSpeed(battleRageSpeed)


func onBattleRageEnded(_event):
	character().changeDamageResistance( - battleRageDamReduction)
	for item in getAffectedItems():
		item.reduceSpeed(battleRageSpeed)


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 10


func getRelatedItems():
	pass

func _readyInit():
	._readyInit()
	healthThreshold = getP1() / 100.0 - 0.0001
	battleRageSpeed = getP3() / 100.0
	battleRageDamReduction = getP4()
