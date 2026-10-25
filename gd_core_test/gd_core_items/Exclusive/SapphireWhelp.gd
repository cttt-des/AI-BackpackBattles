extends Weapon
var stackTypes

func onCombatStart():
	giveMana(getP1())
	activate(null, false)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		var event = tryUseMana(getP2())
		if event:
			giveBlock(getBlock(), true, event)
			giveRandomBuffs(1, event, stackTypes)

func _readyInit():
	._readyInit()
	stackTypes = CoreConst.getBuffs()
	stackTypes.erase(CoreConst.EventType.Mana)

