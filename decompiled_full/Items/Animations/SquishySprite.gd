extends Sprite
class_name SquishySprite

onready var item = get_parent()
onready var baseScale = scale

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
	
	if item.pooled and item.ownerType != item.Owner.Title:
		reset()
		set_physics_process(false)
	else:
		call_deferred("ready_deferred")
		Util.callDelayed(self, "ready_deferred", 0.05)
		set_physics_process(true)
	
func ready_deferred():
	if item.ownerType == item.Owner.RecipeBook:
		set_physics_process(false)
		
	reset()

func reset():
	scale = baseScale
	squishIntensity = 0.0
	momentum = 0.0
	last_position = global_position
	last_posDif = Vector2.ZERO

func _physics_process(delta):
	
	var oversize = squishIntensity < - maxScale or squishIntensity > maxScale
	var posDif = last_position - global_position

	posDif = posDif.limit_length(moveLimit)
	var acceleration = posDif - last_posDif
	
	last_posDif = posDif
	last_position = global_position
	
	var curAccel = accelFactor
	if item.liesInStorage():
		curAccel *= 1.5
	
	if abs(acceleration.x) > abs(acceleration.y):
		momentum += acceleration.length() * curAccel * delta * sign(acceleration.x)
	else:
		momentum -= acceleration.length() * curAccel * delta * sign(acceleration.y)

	if oversize:
		if sign(squishIntensity) != sign(momentum):
			momentum *= - 0.05
	
	momentum += squishIntensity * delta * speed
	
	momentum *= friction
	squishIntensity -= momentum
		
	scale = baseScale
	
	if squishIntensity > 0:
		var x_scale = 1 + squishIntensity
		var y_scale = 1.0 / x_scale
		scale *= Vector2(x_scale, y_scale)
	else:
		var y_scale = 1 - squishIntensity
		var x_scale = 1.0 / y_scale
		scale *= Vector2(x_scale, y_scale)

func addMomentum(amount: float):
	if momentum > - 0.001:
		momentum += amount
	else:
		momentum -= amount
	
