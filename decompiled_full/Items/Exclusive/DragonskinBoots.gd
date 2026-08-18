extends Item

var hasActivated: bool

func onPrepare():
	hasActivated = false
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	
	character().changeResistChance(Game.EventType.Cold, getChance())

func onBattleRageStarted(event):
	cleanseRandomDebuffs(getP1(), event)
	giveEmpower(getP2(), event)
	giveBlock(getBlock(), true, event)
