extends Item

onready var damagePerPoison: int = getP("damt")
onready var poison: int = getP("poison")
var damageAcc: int = 0

func canAffect(item):
	return item.canBeEmpowered()

func onPrepare():
	for weapon in getAffectedItems():
		connectForCombat(weapon, "attacked", "onWeaponAttacked")
	connectForCombat(character(), "character_lucky_changed", "onLuckChanged")
	
func onWeaponAttacked(damageRes: DamageResult):
	if damageRes.hasHit():
		damageAcc += damageRes.damage
		
		var poisonStacks = damageAcc / damagePerPoison
		if poisonStacks > 0:
			inflictPoison(poisonStacks * poison, damageRes.event)
			damageAcc %= damagePerPoison
			miniActivate()

func onLuckChanged(amount, event):
	opponent().changePoisonCritChancePercent(amount * getChance())
