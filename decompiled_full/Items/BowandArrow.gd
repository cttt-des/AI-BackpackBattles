extends Bow

onready var bonusDmgPerHit: int = getP1()
onready var maxDmg: int = getP2()
var bonusDmg: int



func hasAttackEffect() -> bool:
	return true

func onPrepare():
	bonusDmg = 0
	setState(0)

func onWeaponAttacked(damageRes: DamageResult):
	if damageRes.hasHit():
		var dmgAdded: = false
		var attackEffectCount = 1 + rollDoubleAttackEffect()
		for i in attackEffectCount:
			if bonusDmg < maxDmg:
				bonusDmg += bonusDmgPerHit
				addBonusDamage(bonusDmgPerHit)
				dmgAdded = true
		
		if dmgAdded:
			setState(bonusDmg, false, damageRes.event)

func onShopEntered():
	onStateChanged(0)

func onStateChanged(_bonusDmg):
	if _bonusDmg > 0:
		activationParticles.activate()
		activationParticles.scale = Vector2.ONE * min(3, 1.5 + 0.1 * _bonusDmg)
		light.show()
		light.scale = activationParticles.scale * 0.15
	else:
		activationParticles.deactivate()
		light.hide()
