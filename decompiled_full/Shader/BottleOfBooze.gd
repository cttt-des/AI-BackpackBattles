tool
extends Sprite

export var friction = 0.95
export var foamDecay = 0.99
export var backForce = 3.0

export var momentum = 0.0
export var baseFoaminess = 0.05
export var maxFoaminess = 0.9
export var rotationFoam = 0.05
export var baseScroll = 0.03
export var levelModification = 0.0
export (Curve) var levelCurve

onready var angle = PI / 2 - global_rotation
onready var last_target_angle = PI / 2 - global_rotation
onready var last_position = global_position

var targetAngle = 0.0
var foaminess = 0.0
var foamOffset = Vector2(0, 0)
var last_posDif = Vector2.ZERO
var acceleration = Vector2.ZERO

const MAX_MOMENTUM = 0.3

static func angle_to_angle(from, to):
	return fposmod(to - from + PI, PI * 2) - PI

func _physics_process(delta):
	
	var speedScale = delta * 60.0
	targetAngle = - global_rotation + PI / 2
	
	var posDif = last_position - global_position
	posDif = posDif.limit_length(50)
	acceleration = posDif - last_posDif
	momentum += acceleration.x * 0.0015 * speedScale
	foaminess += (acceleration.x * 0.001 + acceleration.y * 0.002) * speedScale
	
	last_posDif = posDif
	last_position = global_position
	

	var angleChange = angle_to_angle(targetAngle, angle)
	foaminess = clamp(foaminess * foamDecay + angleChange * rotationFoam, 0, maxFoaminess)
	last_target_angle = targetAngle

	var angleDiff = angle_to_angle(targetAngle, angle)
	momentum -= angleDiff * backForce * delta
	momentum *= 1 - ((1 - friction) * speedScale)
	angle = fposmod(angle, 2 * PI)
	targetAngle = fposmod(targetAngle, 2 * PI)
	
	
	momentum = clamp(momentum, - MAX_MOMENTUM, MAX_MOMENTUM)
	
	angle += momentum * speedScale
	foamOffset += Vector2.DOWN * 0.01 * (foaminess + baseScroll) * speedScale

	var screenUV = global_position / Vector2(1920, 1080) * Vector2(1, - 1)

	var totalLevel = levelModification
	totalLevel += levelCurve.interpolate(fposmod(angle / (PI * 2) - 0.25, 1))

	material.set_shader_param("levelOffset", totalLevel)
	material.set_shader_param("angle", angle)
	material.set_shader_param("foaminess", foaminess + baseFoaminess)
	material.set_shader_param("foamOffset", foamOffset + screenUV)

func createFoam(amount):
	foaminess += amount
