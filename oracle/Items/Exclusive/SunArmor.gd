extends Item

onready var heatNeeded: int = getP2()
onready var debuffsCleansed: int = getP4()

func canAffect(item):
	return item.hasType(Type.Fire) or item.hasType(Type.Holy)

func reactToItemTypeChange(item):
	if item in currentAffectedItems[Affected.Primary]:
		
		if not item.hasType(Type.Fire) and item.hasDynamicType(Type.Holy, self):
			currentAffectedItems[Affected.Primary].erase(item)
			onAffectedItemRemoved(item, Affected.Primary)
			return false
	return true

func onAffectedItemAdded(item, color: int):
	if item.hasType(Type.Fire):
		item.addDynamicType(Type.Holy, self)

func onAffectedItemRemoved(item, color: int):
	item.removeDynamicType(Type.Holy, self)

func doCooldownEffect():
	if character().getHeat() >= heatNeeded:
		var event = useHeat(heatNeeded)
		heal(getP_m("heal"), event)
		cleanseRandomDebuffs(debuffsCleansed, event)
		EventBus.emitSignal(self, "used_heat", [event])
	activate()
	
func onCombatStart():
	giveBlock()
	giveHeat(getNumAffectedItems() * getP1())
	activate()
