extends Item

onready var buffs: = int(getP("buffs"))

func canAffect(item):
	return item.hasAttackEffect()

func onPrepare():
	for item in getAffectedItems():
		item.giveDoubleAttackEffectChance(getChance())

func doCooldownEffect():
	giveLeastBuffs(buffs)
	activate()
