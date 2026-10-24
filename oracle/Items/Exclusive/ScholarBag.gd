extends Bag

onready var mana: = int(getP("mana"))

func canApplyEffect(toItem):
	return toItem.gainsStack(Stack.Mana)

func onPrepare():
	for item in getAffectedItemsInside():
		item.changeAmplificiationChancePercent(Game.EventType.Mana, getChance())
	
	character().changeProtectionChance(Game.EventType.Mana, getChance2())

func onCombatStart():
	giveMana(mana)
	activate()
