extends Item

func canAffect(item):
	return item.hasStartofBattle()

func doCooldownEffect():
	for item in getAffectedItems():
		item.repeatCombatStart()
	onAfterEffectFinished()
