extends Area2D



const RESETTIME: = 5

onready var indicatorTimer: = $IndicatorTimer

var ticks = 0
var exitTimes: Dictionary
var offscreenIndicatorActive: = false

func _ready():
	Game.connect("switch_to_shop", self, "onSwitchToShop")
	call_deferred("ready_deferred")

func ready_deferred():
	Game.gridStorage.connect("toggled", self, "updateIndicatorVisibility")



func onSwitchToShop():
	cleanUp()

func checkBodies():
	if Game.state == Game.State.Shop:
		ticks += 1
		cleanUp()

func cleanUp():
	var exitTimes_new = {}
	for body in exitTimes:
		if is_instance_valid(body) and body.ownerType == Item.Owner.PlayerStorageBox:
			exitTimes_new[body] = exitTimes[body]
			if not body.dragged:
				var ticksSinceExit = ticks - exitTimes[body]
				
				if exitTimes.size() > 3:
					if ticksSinceExit >= 5:
						body.global_position = Vector2(1000, - 500)
						body.rotation = 0
						print("resetting (full)", body.getName())
						
				else:
					if ticksSinceExit >= 2:
						body.global_position = Vector2(1000, - 200)
						body.linear_velocity.y = Util.rng.randf_range(300, 600)
						body.lastCollisionPos = body.global_position
						print("resetting ", body.getName())
				
	
	exitTimes = exitTimes_new
	updateIndicator()

func onBodyEntered(body):
	if body in exitTimes:
		exitTimes.erase(body)
		disconnectItem(body)
		updateIndicator()


func onBodyExited(body):
	if Game.isShopActive():
		if body is Item and body.ownerType == Item.Owner.PlayerStorageBox:
			
			if not body.dragged:
				exitTimes[body] = ticks
				
				indicatorTimer.start(5.0)
				
				
				body.connect("added_to_inventory", self, "onItemAddedToInventory", [body])
				body.connect("picked_up", self, "onItemPickedUp", [body])


func onItemAddedToInventory(item):
	exitTimes.erase(item)
	cleanUp()
	disconnectItem(item)

func onItemPickedUp(item):
	exitTimes.erase(item)
	cleanUp()
	disconnectItem(item)

func disconnectItem(item):
	Util.tryDisconnect(item, "added_to_inventory", self, "onItemAddedToInventory")
	Util.tryDisconnect(item, "picked_up", self, "onItemPickedUp")

func updateIndicator():
	
	if exitTimes.size() == 0:
		indicatorTimer.stop()
		offscreenIndicatorActive = false
		updateIndicatorVisibility()

func updateIndicatorVisibility():
	if Game.gridStorage.visible:
		Game.shopSceneNode.itemOffScreenIndicator.visible = false
	else:
		Game.shopSceneNode.itemOffScreenIndicator.visible = offscreenIndicatorActive

func onIndicatorTimeout():
	offscreenIndicatorActive = true
	updateIndicatorVisibility()

func onIndicatorPressed():
	Game.cancelSwitch()
	var item
	for offScreenItem in exitTimes.keys():
		if (is_instance_valid(offScreenItem) and 
			offScreenItem.ownerType == Item.Owner.PlayerStorageBox):
				item = offScreenItem
				break
	
	item.global_position = get_global_mouse_position()
	item.pickup()
	updateIndicator()
