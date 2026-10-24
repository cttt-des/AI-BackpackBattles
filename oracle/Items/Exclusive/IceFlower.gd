extends Item

onready var manaNeeded: = int(getP("manat"))
onready var cold: = int(getP("cold"))
onready var mana: = int(getP("mana"))

func canAffect(item):
	return item.isWeapon()

func canAffect_secondary(item):
	return item.hasType(Type.Shield) or (item.hasType(Type.Armor) and item.canActivate())

func onPrepare():
	for item in getAffectedItems(Affected.Primary):
		connectForCombat(item, "attacked", "onWeaponAttacked")
	
	for item in getAffectedItems(Affected.Secondary):
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
