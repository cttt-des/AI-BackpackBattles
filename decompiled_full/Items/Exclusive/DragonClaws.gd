extends Item

func canAffect(item):
	return item.hasCooldown()

func onPrepare():
	
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")
	
	
	character().changeResistChance(Game.EventType.Poison, 
		getChance())

func onBattleRageStarted(_event):
	for item in getAffectedItems():
		item.addSpeed(getP1() / 100)

func onBattleRageEnded(_event):
	for item in getAffectedItems():
		item.reduceSpeed(getP1() / 100)
