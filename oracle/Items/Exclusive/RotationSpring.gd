extends Sprite

var item
onready var baseRotation = rotation
onready var parent = get_parent()

export var speed = 3.0
export var friction = 0.95
export var accelFactor = 0.2
export var maxScale = 0.5
export var rotationFactor = 0.0
export var autoAlign: = false
const moveLimit = 30


var rotationOffset = 0.0
var momentum = 0.0
var last_position = Vector2.ZERO
var last_posDif = Vector2.ZERO
onready var last_rotation = parent.rotation

func _ready():
	item = get_parent()
	while not item is Item:
		item = item.get_parent()
	init()

func init():
	
	if item.pooled and item.ownerType != Item.Owner.Title:
		reset()
		set_physics_process(false)
	else:
		call_deferred("ready_deferred")
		Util.callDelayed(self, "ready_deferred", 0.05)
		set_physics_process(true)
	
func ready_deferred():
	if (item.ownerType == Item.Owner.RecipeBook or 
		item.ownerType == Item.Owner.ItemLibrary):
		set_physics_process(false)
		
	

func reset():
	
	rotationOffset = 0.0
	momentum = 0.0
	last_position = global_position
	last_posDif = Vector2.ZERO
	last_rotation = parent.rotation

func deactivate():
	set_physics_process(false)

func activate():
	set_physics_process(true)

func _physics_process(delta):
	if autoAlign:
		setRotationTarget( - parent.global_rotation)
	
	var oversize = rotationOffset < - maxScale or rotationOffset > maxScale
	var posDif = last_position - item.global_position

	posDif = posDif.limit_length(moveLimit)
	var acceleration = posDif - last_posDif
	
	acceleration = acceleration.project(Vector2.UP.rotated(global_rotation))
	var strength = acceleration.rotated( - global_rotation).y
	
	last_posDif = posDif
	last_position = item.global_position
	
	var curAccel = accelFactor
	if item.liesInStorage():
		curAccel *= 5.0
	
	momentum += strength * curAccel * delta
	
	if rotationFactor != 0:
		var rotationDif = Util.rotDif(last_rotation, parent.rotation)
		last_rotation = parent.rotation
		momentum += rotationDif * rotationFactor
	





	if oversize:
		if sign(rotationOffset) != sign(momentum):
			momentum *= - 0.05
	
	momentum += rotationOffset * delta * speed
	
	momentum *= friction
	rotationOffset -= momentum
	
	rotation = baseRotation + rotationOffset
	
	









func setRotationTarget(rot: float):
	var dif = Util.rotDif(baseRotation, rot)
	baseRotation = rot
	rotationOffset += dif

func setRotationInstant(rot: float):
	baseRotation = rot
	rotationOffset = 0
	rotation = rot

func addMomentum(amount: float):
	if momentum > - 0.001:
		momentum += amount
	else:
		momentum -= amount
