extends Item
var regeneration
var buffsToRemove

func canAffect(item):
	return item.hasType(CoreConst.Type.Holy) and item.canActivate()


func onPrepare():
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")
	
	opponent().changeDebuffProtectionChance(getChance2())
	character().changeBuffProtectionChance(getChance2())
	

func onItemActivated(event):
	if rollChance():
		giveStacksTemporary(opponent(), CoreConst.EventType.Blind, 
			1, getP_m("dur_blind"))


func doCooldownEffect():
	removeRandomBuffs(buffsToRemove)
	giveRegeneration(regeneration)
	activate()





























func _readyInit():
	._readyInit()
	regeneration = int(getP("regen"))
	buffsToRemove = int(getP("buffs"))
