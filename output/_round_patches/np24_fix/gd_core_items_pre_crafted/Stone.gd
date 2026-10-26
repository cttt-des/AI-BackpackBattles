extends Item
var ammunition: int
var bonusDamage: int

func combatEnd():
	.combatEnd()
	ammunition = 1


func setBagOfStones():
	ammunition = 9000


func onPreDealDamage_late(damageRes):
	
	preHit()



func preHit():
	removeBlock(getP1())


func doCooldownEffect():
	if ammunition >= 1 and useStamina() == CoreConst.StaminaResult.Sufficient:
		ammunition -= 1
		
		var res = dealDamage()
		
		if ammunition == 0:
			onAfterEffectFinished(false)
			consume(res)
		else:
			activate(res)


func onDealtDamage(damageRes):
	if damageRes.hasHit():
		onHit()



func onHit():
	pass

func _readyInit():
	._readyInit()
	damageSource = CoreDamageSource.new().setItem(self)
	ammunition = 1

