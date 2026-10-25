extends Bag
var salesRound1
var salesRound2
var salesChance
var salesParticles

func canApplyEffect(toItem):
	return toItem.hasType(CoreConst.Type.Nature)


func onPrepare():
	var healAmp = getP("healamp")
	healAmp += getP("ampbonus") * getNumAffectedInside()
	character().addHealingEfficiency(healAmp / 100.0)
	

func onShopOpened():
	if ctx.cur_round == salesRound1 or ctx.cur_round == salesRound2:
		pass
	

func onSaleRoll(_item):
	pass

func _readyInit():
	._readyInit()
	salesRound1 = int(getP("round1"))
	salesRound2 = int(getP("round2"))
	salesChance = getP("sales") / 100.0
	if ownerType == CoreConst.Owner.PlayerInventory:
		pass

