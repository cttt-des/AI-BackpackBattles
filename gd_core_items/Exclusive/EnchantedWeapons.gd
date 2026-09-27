extends Item
var buffs

func canAffect(item):
	return item.hasAttackEffect()


func onPrepare():
	for item in getAffectedItems():
		item.giveDoubleAttackEffectChance(getChance())


func doCooldownEffect():
	giveLeastBuffs(buffs)
	activate()

func _readyInit():
	._readyInit()
	buffs = int(getP("buffs"))
