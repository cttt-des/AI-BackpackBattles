extends FocusGrabbingTextureButton


const length = 160.0

const physicsRopeScene = preload("res://Interface/PhysicsRope.tscn")
const physicsRopeHint = preload("res://Interface/PhysicsRopeHint.tscn")

onready var ropeNode = get_parent()
onready var ropeHint = ropeNode.get_node("RopeHint")
onready var ropeHintLabel = ropeHint.get_node("RopeHint")
onready var labelPosition2D = ropeNode.get_node("LabelPosition")
onready var topY = rect_global_position.y
onready var animation = ropeNode.get_node("RerollRopeAnimation")
onready var tag = $Tag

var grabbed = false
var moveUpSpeed: = 500.0
var clickPos: float
var notEnoughGoldReadyTime: = 0.0
var rerollReadyTime: = 0.0
var tagTween: SceneTreeTween
var updatingTexture = false
var ropeTween
var physicsRope = null
var hintTimestamp = 0.0

func _ready() -> void :
	add_to_group("Localized")
	updateLocale()
	Game.connect("gold_changed", self, "goldChanged")
	Game.connect("switch_to_shop", self, "enteringShop")
	Game.connect("warp_cursor_shop", self, "onCursorWarp")

func isGrabbed():
	return grabbed

func _button_down():
	Game.cancelSwitch()
	if not Game.draggedItem and Util.time > rerollReadyTime:
		grabbed = true
		clickPos = Util.getMousePosInWindow().y - rect_global_position.y
	
func _button_up():
	grabbed = false


func _unhandled_input(event):
	if InputBlocker.isActive(): return
	
	if (Util.isActionPressed_event(event, "reroll") and 
		Game.isShopActive() and 
		not Game.isMenuOpen() and 
		Game.draggedItem == null and 
		Util.time > Game.lastItemDropTime + 0.5):
		
		Game.cancelSwitch()
		disabled = true
		onPulled()
		Util.killTween(ropeTween)
		ropeTween = create_tween()
		ropeTween.tween_property(self, "rect_global_position:y", topY + length, 0.1)
		ropeTween.tween_callback(self, "setDisabled", [false])

func _gui_input(event):
	if Util.isRightClick(event) and physicsRope == null:
		hide()
		if Util.clockTime > hintTimestamp:
			var hint = ObjectPool.instance(physicsRopeHint)
			get_parent().add_child(hint)
			hint.get_node("AnimationPlayer").play("ShowHint")
			hintTimestamp = Util.clockTime + 6
		instancePhysicsRope()

func instancePhysicsRope():
	if physicsRope != null:
		physicsRope.queue_free()
	physicsRope = physicsRopeScene.instance()
	Game.shopSceneNode.add_child(physicsRope)
	physicsRope.connect("reroll", self, "onPhysicsRopePulled")
	updateTagTexture()
	
	physicsRope.tag.sprite.material.set_shader_param("progress", Game.shopSceneNode.getRerollProgress())

func setDisabled(_disabled):
	disabled = _disabled

func onPulled():
	grabbed = false
	rerollReadyTime = Util.time + 0.2
	if Game.getGold() >= Game.shopSceneNode.getRerollCost():
		Game.shopSceneNode.reroll()
		updateLocale()
	else:
		if Util.time >= notEnoughGoldReadyTime:
			Game.shopSceneNode.notEnoughGold(labelPosition2D.global_position)
			notEnoughGoldReadyTime = Util.time + 1

func onPhysicsRopePulled():
	onPulled()

func switchToStiffRope():
	show()
	
	physicsRope.queue_free()
	physicsRope = null

func _process(delta: float) -> void :
	if not disabled:
		if grabbed:
			rect_global_position.y = Util.getMousePosInWindow().y - clickPos
		else:
			rect_global_position.y -= delta * moveUpSpeed
			
		rect_global_position.y = clamp(rect_global_position.y, topY, topY + length)
		
		if grabbed and rect_global_position.y == topY + length:
			onPulled()
		








func activate():
	animation.play("MoveDown")

func deactivate():
	ropeNode.position.y = - 600
	set_process(false)

func enteringShop():
	updateLocale()
	lastCost = Game.shopSceneNode.getRerollCost()
	updateTagTexture()

func updateLocale():
	goldChanged(0)
	updateCost()

var lastCost: int = 1

func goldChanged(_change):
	tag.onGoldChanged()
	if physicsRope != null:
		physicsRope.tag.onGoldChanged()

func updateCost():
	if updatingTexture:
		updateTagTexture()
	
	var cost = Game.shopSceneNode.getRerollCost()
	var progress = Game.shopSceneNode.getRerollProgress()
	
	Util.killTween(tagTween)
	tagTween = create_tween()
	tagTween.tween_property(tag.sprite.material, "shader_param/progress", progress, 0.5)
	
	if progress == 1 and lastCost != cost:
		lastCost = cost
		updatingTexture = true
		tagTween.tween_callback(self, "updateTagTexture", [true])

func updateTagTexture(increased = false):
	
	var cost = Game.shopSceneNode.getRerollCost()
	tag.onCostChanged(cost, increased)
	
	updatingTexture = false
	
	if physicsRope != null:
		physicsRope.tag.onCostChanged(cost, increased)

func onCursorWarp():
	var warpPoint = rect_global_position + Vector2(50, 800)
	Game.addPointOfInterest(warpPoint)
	if grabbed:
		Game.addPointOfInterest(warpPoint + Vector2(0, 200))
