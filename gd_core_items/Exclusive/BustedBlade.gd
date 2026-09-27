extends "res://gd_core_items/Greatsword.gd"
var bonusDamPerEmpower

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
		ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.StaminaCost)


func onBattleRageEnded(_event):
	if buffed:
		setState(false)
		baseCooldownOverride = getBaseCooldown()
		updateBaseCooldown()
		ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.StaminaCost)

func _readyInit():
	._readyInit()
	bonusDamPerEmpower = getP1()
