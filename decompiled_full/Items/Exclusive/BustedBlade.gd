extends "res://Items/Greatsword.gd"

onready var bonusDamPerEmpower = getP1()

func onPrepare():
	setState(false)
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")
	connectForCombat(character(), "character_empower_changed", "onEmpowerChanged")

func onEmpowerChanged(amount, _event):
	changeVaryingDamage(amount * bonusDamPerEmpower)

func onBattleRageStarted(_event):
	if not buffed:
		setState(true)
		baseCooldownOverride = getP3()
		updateBaseCooldown()
		Game.combatLog.snapshotItemTooltipStat(self, Stat.StaminaCost)

func onBattleRageEnded(_event):
	if buffed:
		setState(false)
		baseCooldownOverride = getBaseCooldown()
		updateBaseCooldown()
		Game.combatLog.snapshotItemTooltipStat(self, Stat.StaminaCost)
