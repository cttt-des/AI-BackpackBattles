extends Sprite

onready var item = get_parent()
onready var basePos = position.y / scale.y
onready var spring = $Spring
onready var springBasePos = spring.position.y
onready var sockets = $Sockets

export var speed = 3.0
export var friction = 0.95
export var accelFactor = 0.2
export var maxScale = 0.5
const moveLimit = 30


var squishIntensity = 0.0
var momentum = 0.0
var last_position = Vector2.ZERO
var last_posDif = Vector2.ZERO

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
	
	squishIntensity = 0.0
	momentum = 0.0
	last_position = global_position
	last_posDif = Vector2.ZERO

func _physics_process(delta):
	
	var oversize = squishIntensity < - maxScale or squishIntensity > maxScale
	var posDif = last_position - item.global_position

	posDif = posDif.limit_length(moveLimit)
	var acceleration = posDif - last_posDif
	
	acceleration = acceleration.project(Vector2.UP.rotated(global_rotation))
	var strength = acceleration.rotated( - global_rotation).y
	
	last_posDif = posDif
	last_position = item.global_position
	
	var curAccel = accelFactor
	if item.liesInStorage():
		curAccel *= 1.5
	
	momentum += strength * curAccel * delta
	





	if oversize:
		if sign(squishIntensity) != sign(momentum):
			momentum *= - 0.05
	
	momentum += squishIntensity * delta * speed
	
	momentum *= friction
	squishIntensity -= momentum
	
	var displacement = 100 * squishIntensity
	offset.y = basePos + displacement * 2.0
	sockets.position.y = offset.y
	
	spring.scale.y = 0.9 - displacement / 225.0
	spring.scale.x = lerp(1.0, 1.0 / spring.scale.x, 0.5)
	
	spring.position.y = springBasePos + basePos + displacement
	

	









func addMomentum(amount: float):
	if momentum > - 0.001:
		momentum += amount
	else:
		momentum -= amount
