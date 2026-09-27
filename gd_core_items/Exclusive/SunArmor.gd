extends Item
var heatNeeded: int
var debuffsCleansed: int

func canAffect(item):
	return item.hasType(CoreConst.Type.Fire) or item.hasType(CoreConst.Type.Holy)


func reactToItemTypeChange(item):
	if item in currentAffectedItems[CoreConst.Affected.Primary]:
		
		if not item.hasType(CoreConst.Type.Fire) and item.hasDynamicType(CoreConst.Type.Holy, self):
			currentAffectedItems[CoreConst.Affected.Primary].erase(item)
			onAffectedItemRemoved(item, CoreConst.Affected.Primary)
			return false
	return true


func onAffectedItemAdded(item, color: int):
	if item.hasType(CoreConst.Type.Fire):
		item.addDynamicType(CoreConst.Type.Holy, self)


func onAffectedItemRemoved(item, color: int):
	item.removeDynamicType(CoreConst.Type.Holy, self)


func doCooldownEffect():
	if character().getHeat() >= heatNeeded:
		var event = useHeat(heatNeeded)
		heal(getP_m("heal"), event)
		cleanseRandomDebuffs(debuffsCleansed, event)
		ctx.bus.emitSignal(self, "used_heat", [event])
	activate()
	

func onCombatStart():
	giveBlock()
	giveHeat(getNumAffectedItems() * getP1())
	activate()

func _readyInit():
	._readyInit()
	heatNeeded = getP2()
	debuffsCleansed = getP4()
