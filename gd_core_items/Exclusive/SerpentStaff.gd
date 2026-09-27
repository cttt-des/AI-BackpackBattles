extends Weapon
var damageAcc = 0
var manaUseEvents = []
var manaCost
var permDamBonus
var poison
var damageForPoison

func onPrepare():
	manaUseEvents.clear()
	opponent().changeResistChance(CoreConst.EventType.Poison, - getChance())


func onPreDealDamage_early(damageRes: CoreDamageResult):
	var manaUseEvent = tryUseMana(manaCost)
	if manaUseEvent != null:
		addBonusDamage(permDamBonus)
		manaUseEvents.push_back(manaUseEvent)


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit() and not manaUseEvents.empty():
		damageAcc += damageRes.damage
		var curPoison = damageAcc / damageForPoison
		if curPoison > 0:
			damageAcc %= damageForPoison
			inflictPoison(curPoison, damageRes.event)
		manaUseEvents.pop_back()

func _readyInit():
	._readyInit()
	manaCost = getP("mana")
	permDamBonus = getP("dam")
	poison = getP("poison")
	damageForPoison = int(getP("damforpoison"))
