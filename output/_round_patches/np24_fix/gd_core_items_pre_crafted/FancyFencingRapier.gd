extends Weapon
var luckNeeded
var bonusDam
var luck

func onDealtDamage(damageRes: CoreDamageResult):
	
	if damageRes.hasHit():
		if tryUseLucky(luckNeeded, damageRes.event):
			addBonusDamage(bonusDam)
	else:
		giveLucky(luck, damageRes.event)
	

func _readyInit():
	._readyInit()
	luckNeeded = int(getP("luckt"))
	bonusDam = getP("dam")
	luck = int(getP("luck"))
