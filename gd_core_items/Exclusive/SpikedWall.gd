extends "res://gd_core_items/SpikedShield.gd"
var spikesLimit
var staminaRegenMalus

func canBlockDamageRes(damageRes: CoreDamageResult) -> bool:
	return damageRes.triggerOnAttacked()


func onPrepare():
	.onPrepare()
	character().addBattleRageDuration(getP_m("dur_rage"))
	character().changeRangedSpikesLimit(spikesLimit)
	character().changeMeleeSpikesLimit(spikesLimit)
	var baseStaminaRegen = character().baseStaminaRegen
	character().giveStaminaRegeneration(staminaRegenMalus * baseStaminaRegen)

func _readyInit():
	._readyInit()
	spikesLimit = getP("spikedam") / 100.0
	staminaRegenMalus = - getP("staminaregen") / 100.0
