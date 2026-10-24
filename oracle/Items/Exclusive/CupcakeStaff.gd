extends Weapon

onready var manaNeeded: = int(getP("manat"))
onready var numBuffs: = int(getP("buffs"))
onready var damPerBuff: = getP("dam")

func onPrepare():
	connectToCharacterBuffs("onBuffsChanged")

func onPreDealDamage_early(damageRes: DamageResult):
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		giveMostBuffs(numBuffs, event)

func onBuffsChanged(amount, event):
	changeVaryingDamage(amount * damPerBuff)




















