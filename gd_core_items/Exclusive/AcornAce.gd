extends Item
var affectedDescriptors
var boostedCollars: = 0
var collarDescriptors
var acornCollarDescriptor
var critwoodStaffDescriptor
var staminaReduction

func getData():
	return boostedCollars


func setData(data):
	if data != null:
		boostedCollars = data


func onBought():
	boostedCollars = 1


func canAffect_global(item):
	return item.descriptor in affectedDescriptors


func onItemInstantiated(item):
	if (placed and 
		item is RangerCollar and 
		
		item.isOwnable()):
			item.activateExtendedAffectedCells()


func onAddToInventory():
	call_deferred("onAddToInventory_deferred")


func onAddToInventory_deferred():
	pass

func onRemoveFromInventory():
	call_deferred("onRemoveFromInventory_deferred")


func onRemoveFromInventory_deferred():
	pass

func onPrepare():
	for staff in getAllInInventoryOfType(critwoodStaffDescriptor):
		staff.changeStaminaFactor(staminaReduction)



func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if descr == acornCollarDescriptor:
		boostedCollars -= 1

func _readyInit():
	._readyInit()
	collarDescriptors = [
	ctx.item_book.getDescriptor("Acorn Collar"), 
	ctx.item_book.getDescriptor("Magic Collar"), 
	ctx.item_book.getDescriptor("Holy Collar"), 
	ctx.item_book.getDescriptor("Vampiric Collar")
]
	acornCollarDescriptor = collarDescriptors[0]
	critwoodStaffDescriptor = ctx.item_book.getDescriptor("Critwood Staff")
	staminaReduction = - getP("stamina2")
	affectedDescriptors = ctx.util.arrayAsIndexDict(collarDescriptors)
	affectedDescriptors[critwoodStaffDescriptor] = 4

