extends Item

onready var movedDebuffs: int = getP1()

func canAffect(item):
	return item.hasType(Type.Dark) or item.hasType(Type.Holy)
	

func reactToItemTypeChange(item):
	if item in currentAffectedItems[Affected.Primary]:
		
		if not item.hasType(Type.Holy) and item.hasDynamicType(Type.Dark, self):
			currentAffectedItems[Affected.Primary].erase(item)
			onAffectedItemRemoved(item, Affected.Primary)
			return false
	return true

func onAffectedItemAdded(item, color: int):
	if item.hasType(Type.Holy) and not item.hasType(Type.Dark):
		item.addDynamicType(Type.Dark, self)

func onAffectedItemRemoved(item, color: int):
	item.removeDynamicType(Type.Dark, self)
	
func onCombatStart():
	giveBlock()
	var debuffProtectionChance = getChance() * getNumAffectedItems()
	opponent().changeDebuffProtectionChance(debuffProtectionChance)
	activate()

func doCooldownEffect():
	var cleansedDebuffs = pickRandomStacks(Game.getDebuffs(), movedDebuffs, character())
	
	for debuff in cleansedDebuffs:
		var event = character().loseStacks(debuff, cleansedDebuffs[debuff], self)
		if event:
			var actuallyCleansed = - event.getAmount()
			giveStacks(opponent(), debuff, actuallyCleansed, event)
	
	activate()
