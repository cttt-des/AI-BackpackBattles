extends Item
var manaNeeded
var cold
var mana

func canAffect(item):
	return item.isWeapon()


func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Shield) or (item.hasType(CoreConst.Type.Armor) and item.canActivate())


func onPrepare():
	for item in getAffectedItems(CoreConst.Affected.Primary):
		connectForCombat(item, "attacked", "onWeaponAttacked")
	
	for item in getAffectedItems(CoreConst.Affected.Secondary):
		connectForCombat(item, "activated", "onShieldOrArmorActivated")


func onWeaponAttacked(damageRes):
	if character().getMana() >= manaNeeded and rollChance():
		var event = useMana(manaNeeded)
		inflictCold(cold, event)
		miniActivate()


func onShieldOrArmorActivated(event):
	if rollChance2():
		giveMana(mana)
		giveBlock()
		miniActivate()

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	cold = int(getP("cold"))
	mana = int(getP("mana"))
