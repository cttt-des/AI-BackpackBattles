extends Weapon
var luckNeeded
var regenNeeded
var dam
var buffs
var speedBonus
var distortion

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if character().getLucky() >= luckNeeded:
			useLucky(luckNeeded)
			damageRes.damage += dam
			addBonusDamage(dam)
			
		if character().getRegeneration() >= regenNeeded:
			useRegeneration(regenNeeded)
			removeRandomBuffs(buffs)
			if opponent().getBuffStacks() == 0:
				addSpeed(speedBonus)
			


func pickup(pickupType = PickupType.Grabbed):
	.pickup(pickupType)


func drop():
	var res = .drop()
	return res

func _readyInit():
	._readyInit()
	luckNeeded = int(getP("luckt"))
	regenNeeded = int(getP("regent"))
	dam = int(getP("dam"))
	buffs = int(getP("buffs"))
	speedBonus = getP("speed") / 100.0
	pass

