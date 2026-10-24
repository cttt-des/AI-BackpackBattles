extends Item

onready var dragonArmorDescr = ItemBook.getDescriptor("Dragonscale Armor")
onready var dragonBootsDescr = ItemBook.getDescriptor("Dragonskin Boots")
onready var dragonClawsDescr = ItemBook.getDescriptor("Dragon Claws")
onready var armorDescr = ItemBook.getDescriptor("Leather Armor")
onready var bootsDescr = ItemBook.getDescriptor("Leather Boots")
onready var glovesDescr = ItemBook.getDescriptor("Gloves of Haste")

onready var heat: = int(getP("heat"))
onready var lifestealMax: = getP("max") / 100.0

onready var activeLight1 = $Icon / Active1
onready var activeLight2 = $Icon / Active2





func onItemAdded(item):
	.onItemAdded(item)
	checkItems()

func onItemRemoved(item):
	.onItemRemoved(item)
	checkItems()







func onRemoveFromInventory():
	activeLight1.hide()
	activeLight2.hide()

func checkItems():
	if countAllPlacedOfType(dragonArmorDescr) > 0:
		if countAllPlacedOfType(dragonBootsDescr) > 0:
			if countAllPlacedOfType(dragonClawsDescr) > 0:
				activeLight1.show()
				activeLight2.show()
				return
	
	activeLight1.hide()
	activeLight2.hide()

func onPrepare():
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")
	
	if countAllInInventoryOfType(dragonArmorDescr) > 0:
		if countAllInInventoryOfType(dragonBootsDescr) > 0:
			if countAllInInventoryOfType(dragonClawsDescr) > 0:
					connectForCombat(opponent(), "character_attacked", "onOpponentDamaged")

func preCombatStart():
	.preCombatStart()
	deactivateCooldown()

func onBattleRageStarted(_event):
	
	activateCooldown()

func onBattleRageEnded(_event):
	
	deactivateCooldown()

func doCooldownEffect():
	giveHeat(heat)
	activate()

func onOpponentDamaged(damageRes: DamageResult):
	if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
		var curLifesteal = min(getP_m("lifesteal") / 100.0 * character().getHeat(), 
								lifestealMax)
		heal(ceil(curLifesteal * damageRes.damage), damageRes.event)

func onItemRoll(descr):
	if (descr == armorDescr and 
		not ItemBook.isItemOwned(dragonArmorDescr) and 
		not ItemBook.isItemOwned(armorDescr)):
			ItemBook.multiplyWeight(1.3)
	
	if (descr == bootsDescr and 
		not ItemBook.isItemOwned(dragonBootsDescr) and 
		not ItemBook.isItemOwned(bootsDescr)):
			ItemBook.multiplyWeight(1.3)
	
	if (descr == glovesDescr and 
		not ItemBook.isItemOwned(dragonClawsDescr) and 
		not ItemBook.isItemOwned(glovesDescr)):
			ItemBook.multiplyWeight(1.3)
