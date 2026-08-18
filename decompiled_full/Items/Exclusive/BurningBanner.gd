extends Item

onready var regeneration: = int(getP("regen"))
onready var buffsToRemove: = int(getP("buffs"))

func canAffect(item):
	return item.hasType(Type.Holy) and item.canActivate()

func onPrepare():
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")
	
	opponent().changeDebuffProtectionChance(getChance2())
	character().changeBuffProtectionChance(getChance2())
	
func onItemActivated(event):
	if rollChance():
		giveStacksTemporary(opponent(), Game.EventType.Blind, 
			1, getP_m("dur_blind"))

func doCooldownEffect():
	removeRandomBuffs(buffsToRemove)
	giveRegeneration(regeneration)
	activate()





























