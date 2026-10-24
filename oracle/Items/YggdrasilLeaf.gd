extends Item

onready var manaNeeded = int(getP3())
var manaUsed = 0

func canAffect(item):
	return item.hasType(Type.Nature)

func onPrepare():
	manaUsed = 0
	
	connectForCombat(character(), "character_mana_changed", "onManaChanged")

func onCombatStart():
	giveMana(getP1() * getAffectedItems().size())
	giveRegeneration(getP2() * getAffectedItems().size())
	activate()
	
func onManaChanged(amount, event: CombatEvent):
	if amount < 0 and event.getParam("used", false):
		manaUsed += - amount
		var activations = manaUsed / manaNeeded
		manaUsed %= manaNeeded
		if activations >= 1:
			heal(getP_m("heal") * activations, event)
			cleanseRandomDebuffs(getP5() * activations, event)
			activate()
