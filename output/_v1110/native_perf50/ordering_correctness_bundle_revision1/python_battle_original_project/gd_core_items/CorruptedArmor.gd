extends Item
var movedDebuffs: int

func canAffect(item):
	return item.hasType(CoreConst.Type.Dark) or item.hasType(CoreConst.Type.Holy)
	


func reactToItemTypeChange(item):
	if item in currentAffectedItems[CoreConst.Affected.Primary]:
		
		if not item.hasType(CoreConst.Type.Holy) and item.hasDynamicType(CoreConst.Type.Dark, self):
			currentAffectedItems[CoreConst.Affected.Primary].erase(item)
			onAffectedItemRemoved(item, CoreConst.Affected.Primary)
			return false
	return true


func onAffectedItemAdded(item, color: int):
	if item.hasType(CoreConst.Type.Holy) and not item.hasType(CoreConst.Type.Dark):
		item.addDynamicType(CoreConst.Type.Dark, self)


func onAffectedItemRemoved(item, color: int):
	item.removeDynamicType(CoreConst.Type.Dark, self)
	

func onCombatStart():
	giveBlock()
	var debuffProtectionChance = getChance() * getNumAffectedItems()
	opponent().changeDebuffProtectionChance(debuffProtectionChance)
	activate()


func doCooldownEffect():
	var cleansedDebuffs = pickRandomStacks(CoreConst.getDebuffs(), movedDebuffs, character())
	
	for debuff in cleansedDebuffs:
		var event = character().loseStacks(debuff, cleansedDebuffs[debuff], self)
		if event:
			var actuallyCleansed = - event.getAmount()
			giveStacks(opponent(), debuff, actuallyCleansed, event)
	
	activate()

func _readyInit():
	._readyInit()
	movedDebuffs = getP1()
