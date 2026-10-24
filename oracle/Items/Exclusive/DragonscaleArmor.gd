extends Item

func onPrepare():
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")

func onBattleRageStarted(event):
	giveBlock(getBlock(), true, event)
	character().changeDamageResistance(getP1())
	activate()

func onBattleRageEnded(_event):
	character().changeDamageResistance( - getP1())
