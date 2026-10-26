extends Item
var lifestealActive: = false
var lifestealParticles
var lifestealLight
var vampirism1
var luckNeeded
var luckUsed
var vampirism2

func canAffect(item):
	return item.canDamage()


func doCooldownEffect():
	var numVamp: = 0
	if character().getLucky() >= luckNeeded:
		useLucky(luckUsed)
		numVamp += vampirism2
	
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		numVamp += vampirism1
	
	if numVamp > 0:
		giveVampirism(numVamp)
		activate()


func onPrepare():
	setState(false)
	connectForCombat(opponent(), "character_attacked", "onOpponentDamaged")


func onOpponentDamaged(damageRes: CoreDamageResult):
	if lifestealActive:
		if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
			if damageRes.damageSource.origin in getAffectedItems():
				heal(ceil(damageRes.damage * getP_m("lifesteal") / 100.0), damageRes.event)


func onChargeReceived(_charge):
	if numCharges == 1:
		setState(true)


func onChargeLeft(_charge):
	if numCharges == 0:
		setState(false)


func onShopEntered():
	onStateChanged(false)


func onStateChanged(_lifestealActive):
	lifestealActive = _lifestealActive
	if lifestealActive:
		pass
	else:
		pass

func _readyInit():
	._readyInit()
	vampirism1 = int(getP("vampirism"))
	luckNeeded = int(getP("luckt"))
	luckUsed = int(getP("luck"))
	vampirism2 = int(getP("vampirism2"))
