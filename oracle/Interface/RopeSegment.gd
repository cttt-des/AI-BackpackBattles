extends RigidBody2D

var LENGTH = 50
const WIDTH = 100
onready var start = $Start
onready var end = $End

onready var collisionShape = $CollisionShape2D
onready var clickArea = $ClickArea

var rope
var hovered: bool = false
var dragged: bool = false
var startTransform: Transform2D
var resetPending: bool = false

export var ending = false

func _ready():
	if not ending:
		
		start.position.y = - LENGTH * 0.5
		end.position.y = LENGTH * 0.5
		
		collisionShape.shape.extents = Vector2(WIDTH * 0.5, LENGTH * 0.5 - 2)
		clickArea.rect_size = Vector2(WIDTH, LENGTH)
	
	call_deferred("ready_deferred")

func ready_deferred():
	startTransform = global_transform

func getLength():
	if ending:
		return end.position.y - start.position.y
	return LENGTH

func getStartPos() -> Vector2:
	return position + start.position

func getEndPos() -> Vector2:
	return position + end.position

func onMouseEntered():
	hovered = true
	rope.onHovered(self)

func onMouseExited():
	hovered = false
	rope.onHoveredEnd(self)

func startDrag():
	sleeping = false
	dragged = true
	

func endDrag():
	dragged = false
	

func _integrate_forces(state: Physics2DDirectBodyState):
	if dragged:
		var difToMouse = rope.getClampedMousePos() - global_position
		linear_velocity = difToMouse * 5.0
	
	elif resetPending:
		
		applied_force = Vector2.ZERO
		applied_torque = 0
		state.linear_velocity = Vector2.ZERO
		state.angular_velocity = 0
		state.transform = startTransform
		resetPending = false

func reset():
	resetPending = true
