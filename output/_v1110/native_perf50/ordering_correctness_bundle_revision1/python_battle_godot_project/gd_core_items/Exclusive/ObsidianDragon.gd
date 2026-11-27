extends Weapon
var heatCounter = 0
var affectedWeapon = null
var heatNeeded
var bonusDam

func canAffect(item):
	return item.canBeEmpowered()


func onPrepare():
	affectedWeapon = getFirstAffectedItem()
	heatCounter = 0
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")


func onHeatChanged(amount, event):
	if amount > 0:
		heatCounter += amount
		var proccs = heatCounter / heatNeeded
		if proccs > 0:
			heatCounter %= heatNeeded
			
			addBonusDamage(bonusDam * proccs)
			if affectedWeapon != null:
				affectedWeapon.addCritTokens(proccs)

func _readyInit():
	._readyInit()
	heatNeeded = int(getP1())
	bonusDam = int(getP2())
