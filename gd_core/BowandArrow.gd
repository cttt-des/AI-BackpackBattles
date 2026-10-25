extends Bow
var bonusDmg: int
var bonusDmgPerHit: int
var maxDmg: int

func hasAttackEffect() -> bool:
	return true


func onPrepare():
	bonusDmg = 0
	setState(0)


func onWeaponAttacked(damageRes: CoreDamageResult):
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
		pass
	else:
		pass

func _readyInit():
	._readyInit()
	bonusDmgPerHit = getP1()
	maxDmg = getP2()
