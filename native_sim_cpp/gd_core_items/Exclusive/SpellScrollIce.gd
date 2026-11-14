extends Item
var activated: bool
var coldInflicted: int
var cold
var maxCold

func canAffect(item):
	return item.hasType(CoreConst.Type.Shield) or (item.hasType(CoreConst.Type.Armor) and item.canActivate())


func onPrepare():
	activated = false
	connectForCombat(character(), "pre_take_damage_late", "onCharacterAttacked")
	
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onShieldOrArmorActivated")
	coldInflicted = 0


func onCharacterAttacked(damageRes):
	if not activated:
		if damageRes.willBeLethal(character()):
			var opponentCold = opponent().getCold()
			if opponentCold > 0:
				activated = true
				opponent().loseCold(opponentCold, self, damageRes.event)
				giveBlock(round(getBlock() * opponentCold), true, damageRes.event)
				consume()


func onShieldOrArmorActivated(event):
	if coldInflicted < maxCold and rollChance():
		coldInflicted = min(cold, maxCold - coldInflicted)
		inflictCold(cold, event)
		miniActivate()

func _readyInit():
	._readyInit()
	cold = getP("cold")
	maxCold = getP("max")
