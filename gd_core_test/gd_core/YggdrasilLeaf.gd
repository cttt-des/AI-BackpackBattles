extends Item
var manaUsed = 0
var manaNeeded

func canAffect(item):
	return item.hasType(CoreConst.Type.Nature)


func onPrepare():
	manaUsed = 0
	
	connectForCombat(character(), "character_mana_changed", "onManaChanged")


func onCombatStart():
	giveMana(getP1() * getAffectedItems().size())
	giveRegeneration(getP2() * getAffectedItems().size())
	activate()
	

func onManaChanged(amount, event):
	if amount < 0 and event.getParam("used", false):
		manaUsed += - amount
		var activations = manaUsed / manaNeeded
		manaUsed %= manaNeeded
		if activations >= 1:
			heal(getP_m("heal") * activations, event)
			cleanseRandomDebuffs(getP5() * activations, event)
			activate()

func _readyInit():
	._readyInit()
	manaNeeded = int(getP3())
