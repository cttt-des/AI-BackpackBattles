extends "res://Items/SpikedShield.gd"

onready var spikesLimit = getP("spikedam") / 100.0
onready var staminaRegenMalus = - getP("staminaregen") / 100.0

func canBlockDamageRes(damageRes: DamageResult) -> bool:
	return damageRes.triggerOnAttacked()

func onPrepare():
	.onPrepare()
	character().addBattleRageDuration(getP_m("dur_rage"))
	character().changeRangedSpikesLimit(spikesLimit)
	character().changeMeleeSpikesLimit(spikesLimit)
	var baseStaminaRegen = character().baseStaminaRegen
	character().giveStaminaRegeneration(staminaRegenMalus * baseStaminaRegen)
