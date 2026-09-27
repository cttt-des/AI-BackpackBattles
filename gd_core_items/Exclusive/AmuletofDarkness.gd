extends Item
const amuletColor = Color(0.580392, 0.266667, 0.960784)
var damageAcc: int
var damageThreshold

func canAffect(item):
	return item.canActivate()


func onPrepare():
	damageAcc = 0
	connectForCombat(opponent(), "character_attacked", "onOpponentDamaged")
	
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")


func onItemActivated(event):
	pass

func onOpponentDamaged(damageRes: CoreDamageResult):
	if damageRes.hasHit() and damageRes.damageSource.isEffectDamage():
		damageAcc += damageRes.damage
		
		var proccs = damageAcc / damageThreshold
		if proccs > 0:
			damageAcc %= damageThreshold
			inflictRandomDebuffs(proccs)
			miniActivate()

func _readyInit():
	._readyInit()
	damageThreshold = int(getP("damt"))
	damageSource = CoreDamageSource.new().setItem(self)

