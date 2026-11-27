extends Weapon
var poison: int

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		var randomDebuff = ctx.util.pickRandomElement(CoreConst.getDebuffs())
		if randomDebuff == CoreConst.EventType.Poison:
			inflictPoison(poison + 1)
		else:
			inflictPoison(poison)
			giveStacks(opponent(), randomDebuff, 1)

func _readyInit():
	._readyInit()
	poison = getP1()
