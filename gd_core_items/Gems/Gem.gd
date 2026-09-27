extends Item
class_name Gem
var hoveredSocket = null
var socket = null
var movebackSocket = null
var dropTween
var gemPower = 1.0
enum GemMode{
	Weapon = 0, 
	Armor = 1, 
	Inventory = 2, 
	Inactive
}
var dropPosition
var dropRotation
var quantizedRotation
var socketDetectionArea
var gemAnimation

func isGem():
	return true


func isOwnable() -> bool:
	if socket != null:
		return socket.getItem().isOwnable()
	else:
		return .isOwnable()


func isOwnedByOpponent() -> bool:
	if socket != null:
		return socket.getItem().isOwnedByOpponent()
	else:
		return .isOwnedByOpponent()


func getEffectiveOwnerType() -> int:
	if socket != null:
		return socket.getItem().getEffectiveOwnerType()
	else:
		return .getEffectiveOwnerType()


func getInventory():
	if socket != null:
		return socket.getItem().getInventory()
	else:
		return .getInventory()


func getItem():
	if socket != null:
		return socket.getItem()
	else:
		return null


func isPlaced() -> bool:
	if socket != null:
		return socket.getItem().isPlaced()
	else:
		return placed


func isInInventory() -> bool:
	if socket != null:
		return socket.getItem().isInInventory()
	else:
		return .isInInventory()


func getGemMode():
	if socket != null:
		if getItem().isWeapon():
			return GemMode.Weapon
		else:
			return GemMode.Armor
	else:
		if placed:
			return GemMode.Inventory
		else:
			return GemMode.Inactive


func getGemPower() -> float:
	return max(0.0, gemPower)


func changeGemPower(amount: float):
	gemPower += amount


func getHoverPriority():
	if dragged: return DRAG_PRIORITY
	else: return 1


func character():
	if getGemMode() == GemMode.Inactive:
		return ctx.player
	elif getGemMode() == GemMode.Inventory:
		return .character()
	else:
		return getItem().character()


func _process(_delta):
	pass

func previewCellCollision():
	if ( not hoveredSocket and 
		( not movebackSocket or ctx.frame_counter > pickupFrame + 1)):
		.previewCellCollision()


func gainFocus():
	.gainFocus()

func loseFocus():
	.loseFocus()

func prepareLerpToSocket():
	pass

func drop() -> int:
	return 0

func lerpToSocket(interpolationPoint: float):
	pass

func pickup(pickupType = PickupType.Grabbed):
	.pickup(pickupType)
	
	
	if socket != null:
		killDropTween()
		movebackSocket = socket
		hoveredSocket = socket
		if socket.getItem().ownerType == CoreConst.Owner.PlayerStorageBox:
			setFaceDirection(CoreConst.FaceDirection.UP)
		else:
			faceDirection = getGlobalFaceDirection()
	
		socket.onPickupGem()


func addToSocket(_socket):
	pass

func unsocket():
	killDropTween()
	var s = socket
	socket.onPickupGem()
	s.hideSocket()


func removeFromSocket():
	pass

func killDropTween():
	pass

func returnToSocket(movebackDur = 0.1):
	pass

func hasCooldown() -> bool:
	var gemMode = getGemMode()
	return ((gemMode == GemMode.Inventory or 
				gemMode == GemMode.Inactive) and 
				.hasCooldown())


func miniActivate():
	.miniActivate()
	playActivationAnimation_Scale(1.5)


func prepareInventory():
	pass


func prepareWeapon():
	pass


func prepareArmor():
	pass


func onPrepare():
	
	match getGemMode():
		GemMode.Inventory:
			prepareInventory()
		GemMode.Weapon:
			prepareWeapon()
		GemMode.Armor:
			prepareArmor()


func combatStartInventory():
	pass
	

func combatStartWeapon():
	pass


func combatStartArmor():
	pass


func combatStart():
	.combatStart()
	iterationCooldown = adjustCooldown()
	triggerTime = iterationCooldown
	
	match getGemMode():
		GemMode.Inventory:
			combatStartInventory()
		GemMode.Weapon:
			combatStartWeapon()
		GemMode.Armor:
			combatStartArmor()
	

func combatEndInventory():
	pass


func combatEndWeapon():
	pass


func combatEndArmor():
	pass


func combatEnd():
	.combatEnd()
	match getGemMode():
		GemMode.Inventory:
			combatEndInventory()
		GemMode.Weapon:
			combatEndWeapon()
		GemMode.Armor:
			combatEndArmor()


func shopEntered(craft: bool):
	.shopEntered(craft)
	gemPower = 1.0


func getBaseDescription(wrapInColor = true) -> String:
	return .getDescription(wrapInColor)


func getDescription(wrapInColor = true):
	var descr = getBaseDescription(wrapInColor)
	var colors = [ctx.util.inactiveColor, ctx.util.inactiveColor, ctx.util.inactiveColor]
	var gemMode = getGemMode()
	if gemMode != GemMode.Inactive:
		colors[gemMode] = ctx.util.modifiedColor
	return getModeDescription(descr, colors, true, wrapInColor)


func onHotSwapHoverWithGem():
	pass


func onHotSwapHoverWithGemEnd():
	pass


func createGemParticles():
	pass


func canPreviewFusions():
	if socket:
		return socket.getItem().canPreviewFusions()
	else:
		return .canPreviewFusions()


func canModifyChance() -> bool:
	return false


func getNeighborItemsAndGems():
	if socket:
		if getItem().ownerType == CoreConst.Owner.PlayerStorageBox:
			return []
		
		
		
		var neighbors = [getItem()]
		neighbors.append_array(getItem().getNeighborItemsAndGems())
		neighbors.erase(self)
		return neighbors
	else:
		return .getNeighborItemsAndGems()


func canCombine() -> bool:
	if socket:
		return true
	else:
		return .canCombine()


func shift(direction: Vector2):
	if not socket:
		.shift(direction)


func isMovingBack() -> bool:
	return false

func addToStorageBox(addImpulse = true, tweenBouncyness: bool = true, 
	checkCollisions = true, targetPos = null, speed = 1.0, secondCheck = false):
	if socket:
		var s = socket
		.addToStorageBox(addImpulse, tweenBouncyness, 
			checkCollisions, targetPos, speed, secondCheck)
		s.onPickupGem()
		s.hideSocket()
	else:
		.addToStorageBox(addImpulse, tweenBouncyness, 
			checkCollisions, targetPos, speed, secondCheck)


func discard(discardGems = true):
	.discard(discardGems)
	if socket != null:
		socket.gem = null
		socket.hideSocket()
		socket = null
		movebackSocket = null

func _readyInit():
	._readyInit()
	if descriptor.gateItem == ctx.item_book.getDescriptor("Box of Riches"):
		if specificDragParticles.empty():
			pass

