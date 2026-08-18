extends Node2D

const sparkScene1 = preload("res://Shader/LampSparkParticles.tscn")
const sparkScene2 = preload("res://Shader/LampSparkParticles2.tscn")
const sparkSound = preload("res://Assets/Sound/Shock1.wav")

const friction = 0.99
const backForce = 7.8
const impulse = 60.0
const offColor = Color(0.929688, 0.849792, 0.905372)

var momentum = 0.0
var broken: = false

onready var light = $ShopLight
onready var lamp = $Button
onready var defaultPos = position

func _ready():
	Game.connect("switch_to_shop", self, "onEnteringShop")

func _physics_process(delta):
	rotation_degrees += delta * momentum
	momentum -= rotation_degrees * backForce * delta
	momentum *= friction
	
	
	if is_equal_approx(rotation_degrees, 0) and is_equal_approx(momentum, 0):
		set_physics_process(false)
	
func onLampPressed():
	if momentum > 0:
		momentum += impulse
	else:
		momentum -= impulse
	set_physics_process(true)
	
	var particles = ObjectPool.particleOneShot(sparkScene1, self)
	
	if light.visible:
		if Util.flip(0.1):
			light.hide()
			lamp.modulate = offColor
	else:
		light.show()
		lamp.modulate = Color.white

func _gui_input(event):
	if Util.isRightClick(event) and not broken:
		broken = true
		lamp.disable()
		light.hide()
		lamp.modulate = offColor
		z_index = 50
		momentum = 0
		
		Sound.playSound(sparkSound)
		var particles = ObjectPool.particleOneShot(sparkScene2, self)
		
		var dur = 2.0
		var lampTween = create_tween().set_parallel()
		lampTween.tween_property(self, "position:y", 1300.0, dur
			).set_trans(Tween.TRANS_QUAD).set_ease(Tween.EASE_IN)
		lampTween.tween_property(self, "position:x", 
			position.x + Util.rng.randf_range( - 150, 150), dur)
		lampTween.tween_property(self, "rotation", 
			Util.rng.randf_range( - 3.0, 3.0), dur)
		
		
		
		Game.onDecorationDestructed()

func onEnteringShop():
	broken = false
	lamp.enable()
	z_index = 0
	position = defaultPos
	rotation = 0
	momentum = 0
