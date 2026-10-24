
extends Node2D
class_name Eye

export (float, 0.0, 1.0) var friction = 0.04
export (float, 0.0, 2.0) var movementFactor = 0.5
export (float, 0.0, 0.1) var momentumFactor = 0.04
export (float, 0.0, 3.0) var returnFactor = 1.0
export var eyeRadius = 20.0
export (float, 0.0, 1.0) var mouseFollowStrength = 0.1
export (Vector2) var aspect = Vector2.ONE
export (float, 0.0, 20.0) var mouseLimit = 5.0
export (Vector2) var centerOffset = Vector2.ZERO
export (NodePath) var spriteOverride = null



onready var sprite = get_parent()
onready var oldPos = global_position
var item
onready var center = position
onready var centerWithOffset = position + centerOffset

var momentum: Vector2
var disabled = false

func _ready():
	if spriteOverride != null:
		sprite = get_node(spriteOverride)
	
	item = sprite.get_parent()
	
	set_physics_process(false)
	
	if item is Item and item.pooled:
		pass
	else:
		call_deferred("ready_deferred")
		Util.callDelayed(self, "checkRecipeBook", 0.05)
	
func ready_deferred():
	center = position
	centerWithOffset = position + centerOffset
	checkRecipeBook()

func checkRecipeBook():
	if item is Item and item.ownerType == Item.Owner.RecipeBook:
		pass
	else:
		set_physics_process(true)





func _physics_process(delta: float) -> void :
	
	var speedFactor: = delta * 60.0
	
	var curCenterOffset: = Vector2.ZERO
	if mouseFollowStrength > 0:
		curCenterOffset = (get_global_mouse_position() - global_position) * mouseFollowStrength
		curCenterOffset = curCenterOffset.rotated( - sprite.global_rotation)
		
		curCenterOffset = curCenterOffset.limit_length(mouseLimit)
	
	momentum += (centerWithOffset + curCenterOffset - position) * returnFactor * speedFactor
	momentum *= clamp(1.0 - friction * speedFactor, 0, 1)
	
	var eyeMovement = oldPos - global_position
	eyeMovement = eyeMovement.rotated(item.global_rotation)
	var unclampedMovement = eyeMovement * movementFactor
	unclampedMovement += momentum * momentumFactor * speedFactor
	
	
	
	
	var positionCandidate = position + unclampedMovement
	var difFromCenter = positionCandidate - center
	difFromCenter /= aspect
	position = center + difFromCenter.limit_length(eyeRadius) * aspect
	
	oldPos = global_position
	

func focusGlobalPoint(focusPoint: Vector2):
	center = global_position + (focusPoint - global_position) / 50.0





func deactivate():
	set_physics_process(false)


func activate():
	set_physics_process(true)




