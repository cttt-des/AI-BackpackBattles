extends PullButton

onready var collisionBody = $BottomCollisionBody

var lastPos: Vector2
var momentumStrength: float

func _ready():
	Game.connect("game_paused", self, "_button_up")
	collisionBody.linear_velocity.y = 0
	set_physics_process(false)






func _button_down():
	._button_down()
	lastPos = rect_global_position
	Game.cancelSwitch()


func _physics_process(delta):
	var dif = rect_global_position - lastPos
	var speed = dif.length() / delta
	momentumStrength = lerp(momentumStrength, speed / 60, 20 * delta)
	
	collisionBody.linear_velocity.y = - clamp(momentumStrength * 10, 0, 700)
	lastPos = rect_global_position

func deactivate():
	
	if collisionBody.linear_velocity.y < - 100:
		Game.STORAGEBOX.land()
	
	collisionBody.linear_velocity.y = 0
