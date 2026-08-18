extends Item
class_name Gem

const particlesScene = preload("res://Items/Animations/SocketParticles.tscn")
const dragParticlesScene = preload("res://Items/Gems/GemDragParticles.tscn")

onready var socketDetectionArea = $SocketDetectionArea
onready var gemAnimation = $GemAnimation

var hoveredSocket: Socket = null
var socket: Socket = null
var movebackSocket: Socket = null
var dropTween
var gemPower = 1.0

enum GemMode{
	Weapon = 0, 
	Armor = 1, 
	Inventory = 2, 
	Inactive
}

func _ready() -> void :
	gemAnimation.advance(Util.rng.randf_range(0, 10))
	if descriptor.gateItem == ItemBook.boxOfRichesDescriptor:
		if specificDragParticles.empty():
			var particles = dragParticlesScene.instance()
			sprite.add_child(particles)
			particles.amount = 3 + descriptor.rarity
			particles.self_modulate = self.gemColor
			specificDragParticles.push_back(particles)

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
		return Game.PLAYER
	elif getGemMode() == GemMode.Inventory:
		return .character()
	else:
		return getItem().character()

func _process(_delta):
	if dragged:
		
		if not draggedInsideItems.empty():
			return
		
		var previousSocket: Socket = hoveredSocket
		
		var sockets = []
		for area in socketDetectionArea.get_overlapping_areas():
			var s = area.get_parent()
			if s.item.visible:
				sockets.push_back(s)
		
		if sockets.empty():
			hoveredSocket = null
			if previousSocket == null:
				affectedCellsActive = true
		else:
			var closestSocket = null
			var closestDist = INF
			for s in sockets:
				if s.isAvailable():
					var dist = (s.global_position - global_position).length_squared()
					if dist < closestDist:
						closestSocket = s
						closestDist = dist
			
			if closestSocket:
				hoveredSocket = closestSocket
				affectedCellsActive = false
		
		if hoveredSocket != previousSocket:
			if previousSocket != null:
				previousSocket.onHoverEndWithGem()
			
			if hoveredSocket != null:
				hoveredSocket.onHoverWithGem()


func previewCellCollision():
	if ( not hoveredSocket and 
		( not movebackSocket or Util.frameCounter > pickupFrame + 1)):
		.previewCellCollision()

func gainFocus():
	if not canGainFocus(): return
	
	if draggedInsideItems.empty():
		Game.showSockets()
	.gainFocus()


func loseFocus():
	if not focus: return
	.loseFocus()
	if not Game.draggedItem:
		Game.hideSockets()
		

var dropPosition
var dropRotation
var quantizedRotation

func prepareLerpToSocket():
	dropPosition = global_position
	dropRotation = global_rotation
	quantizedRotation = stepify(rotation, PI * 0.5)

const socketSound = preload("res://Assets/Sound/Hammer3.wav")


func drop() -> int:
	dragged = false
	
	Game.hideSockets()
	if hoveredSocket != null:
		Sound.playSound(socketSound, - 5)
		
		var hotswap = hoveredSocket.getGem()
		addToSocket(hoveredSocket)
		placedByPlayer = true
		prepareLerpToSocket()
		
		killDropTween()
		dropTween = create_tween()
		dropTween.tween_method(self, "lerpToSocket", 0.0, 1.0, 0.1)
		
		sameOrientationAsPickup = (hoveredSocket == movebackSocket)
		
		hoveredSocket = null
		movebackSocket = null
		if hotswap:
			return DropResult.SocketHotswap
		else:
			return DropResult.Socketed
	else:
		var res = .drop()
		if wasAddedToInventory(res):
			movebackSocket = null
		return res

func lerpToSocket(interpolationPoint: float):
	global_position = lerp(dropPosition, socket.global_position, interpolationPoint)
	var targetRotation = socket.global_rotation + quantizedRotation
	global_rotation = lerp_angle(dropRotation, targetRotation, interpolationPoint)
	
func pickup(pickupType = PickupType.Grabbed):
	.pickup(pickupType)
	
	
	if socket != null:
		killDropTween()
		movebackSocket = socket
		hoveredSocket = socket
		Util.reparent(self, Game.playerNode)
		if socket.getItem().ownerType == Owner.PlayerStorageBox:
			setFaceDirection(FaceDirection.UP)
		else:
			faceDirection = getGlobalFaceDirection()
	
		socket.onPickupGem()

func addToSocket(_socket):
	socket = _socket
	ownerType = Owner.Socket
	socket.onDropGem(self)
	z_index = 0
	Util.reparent(self, socket)
	occupiedCells.clear()
	if getItem().ownerType == Owner.PlayerInventory:
		CraftingManager.itemAdded(self)




func unsocket():
	killDropTween()
	Util.reparent(self, Game.playerNode)
	var s = socket
	socket.onPickupGem()
	s.hideSocket()

func removeFromSocket():
	if not fusing and canCombine():
		CraftingManager.itemRemoved(self)
	socket = null
	

func killDropTween():
	Util.killTween(dropTween)
	clickArea.show()
	dropTween = null

func returnToSocket(movebackDur = 0.1):
	addToSocket(movebackSocket)
	prepareLerpToSocket()
	killDropTween()
	clickArea.hide()
	set_deferred("z_index", 32)
	dropTween = create_tween()
	dropTween.tween_method(self, "lerpToSocket", 0.0, 1.0, movebackDur)
	dropTween.tween_callback(self, "resetZ")
	dropTween.tween_callback(self, "showClickArea")
	movebackSocket = null

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
	var colors = [Util.inactiveColor, Util.inactiveColor, Util.inactiveColor]
	var gemMode = getGemMode()
	if gemMode != GemMode.Inactive:
		colors[gemMode] = Util.modifiedColor
	return getModeDescription(descr, colors, true, wrapInColor)

func onHotSwapHoverWithGem():
	gemAnimation.play("HotSwapHover")

func onHotSwapHoverWithGemEnd():
	gemAnimation.play("Sparkle")

func createGemParticles():
	var particles = ObjectPool.particleOneShot(particlesScene, self)
	particles.modulate = self.gemColor
	particles.amount = 5 + 2 * getRarity()

func canPreviewFusions():
	if socket:
		return socket.getItem().canPreviewFusions()
	else:
		return .canPreviewFusions()

func canModifyChance() -> bool:
	return false

func getNeighborItemsAndGems():
	if socket:
		if getItem().ownerType == Owner.PlayerStorageBox:
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
	if socket:
		return getItem().isMovingBack() or .isMovingBack() or Util.isTweenRunning(dropTween)
	else:
		return .isMovingBack()

func addToStorageBox(addImpulse = true, tweenBouncyness: bool = true, 
	checkCollisions = true, targetPos = global_position, speed = 1.0, secondCheck = false):
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
