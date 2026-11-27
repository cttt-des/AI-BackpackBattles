extends Item
var dragonArmorDescr
var dragonBootsDescr
var dragonClawsDescr
var armorDescr
var bootsDescr
var glovesDescr
var heat
var lifestealMax
var activeLight1
var activeLight2

func onItemAdded(item):
	.onItemAdded(item)
	checkItems()


func onItemRemoved(item):
	.onItemRemoved(item)
	checkItems()








func onRemoveFromInventory():
	pass


func checkItems():
	if countAllPlacedOfType(dragonArmorDescr) > 0:
		if countAllPlacedOfType(dragonBootsDescr) > 0:
			if countAllPlacedOfType(dragonClawsDescr) > 0:
				return
	


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


func onOpponentDamaged(damageRes: CoreDamageResult):
	if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
		var curLifesteal = min(getP_m("lifesteal") / 100.0 * character().getHeat(), 
								lifestealMax)
		heal(ceil(curLifesteal * damageRes.damage), damageRes.event)


func onItemRoll(descr):
	pass

func _readyInit():
	._readyInit()
	dragonArmorDescr = ctx.item_book.getDescriptor("Dragonscale Armor")
	dragonBootsDescr = ctx.item_book.getDescriptor("Dragonskin Boots")
	dragonClawsDescr = ctx.item_book.getDescriptor("Dragon Claws")
	armorDescr = ctx.item_book.getDescriptor("Leather Armor")
	bootsDescr = ctx.item_book.getDescriptor("Leather Boots")
	glovesDescr = ctx.item_book.getDescriptor("Gloves of Haste")
	heat = int(getP("heat"))
	lifestealMax = getP("max") / 100.0
