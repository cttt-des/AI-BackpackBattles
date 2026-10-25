extends Weapon
var manaNeeded
var numBuffs
var damPerBuff

func onPrepare():
	connectToCharacterBuffs("onBuffsChanged")


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		giveMostBuffs(numBuffs, event)


func onBuffsChanged(amount, event):
	changeVaryingDamage(amount * damPerBuff)




















func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	numBuffs = int(getP("buffs"))
	damPerBuff = getP("dam")
