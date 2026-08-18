extends Weapon

var stackTypes

func _ready():
	stackTypes = Game.getBuffs()
	stackTypes.erase(Game.EventType.Mana)

func onCombatStart():
	giveMana(getP1())
	activate(null, false)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		var event = tryUseMana(getP2())
		if event:
			giveBlock(getBlock(), true, event)
			giveRandomBuffs(1, event, stackTypes)
