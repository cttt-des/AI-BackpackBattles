extends Weapon

onready var manaCost = getP("mana")
onready var permDamBonus = getP("dam")
onready var poison = getP("poison")
onready var damageForPoison = int(getP("damforpoison"))

var damageAcc = 0
var manaUseEvents = []

func onPrepare():
	manaUseEvents.clear()
	opponent().changeResistChance(Game.EventType.Poison, - getChance())

func onPreDealDamage_early(damageRes: DamageResult):
	var manaUseEvent = tryUseMana(manaCost)
	if manaUseEvent != null:
		addBonusDamage(permDamBonus)
		manaUseEvents.push_back(manaUseEvent)

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit() and not manaUseEvents.empty():
		damageAcc += damageRes.damage
		var curPoison = damageAcc / damageForPoison
		if curPoison > 0:
			damageAcc %= damageForPoison
			inflictPoison(curPoison, damageRes.event)
		manaUseEvents.pop_back()

