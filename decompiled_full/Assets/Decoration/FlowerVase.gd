extends FocusGrabbingButton

const sound = preload("res://Assets/Sound/Ceramic1.mp3")
const shatterSound = preload("res://Assets/Sound/JarBreaking.ogg")
const shatterParticles = preload("res://Assets/Decoration/VaseBreakParticles.tscn")

onready var animation = $AnimationPlayer
onready var vase = $Vase
onready var flower = $Vase / Flower

var state = 0
var broken: = false

func _ready():
	Game.connect("switch_to_shop", self, "onEnteringShop")

func _on_FlowerVase_button_down():
	
	var remainingTime = Util.getRemainingAnimationTime(animation)
	if remainingTime > 0.2: return
	animation.playback_speed = Util.rng.randf_range(0.9, 1.1)
	if state == 0:
		animation.play("Click")
		Sound.playSound(sound, - 6, 1.3)
	elif state == 1:
		animation.play("Click2")
		Sound.playSound(sound, - 3, 1.1)
	else:
		animation.play("Click3")
		Sound.playSound(sound, 0, 0.9)
	state = (state + 1) % 3

func _gui_input(event):
	if Util.isRightClick(event) and not broken:
		disable()
		broken = true
		animation.stop()
		
		vase.z_index = 50
		vase.self_modulate.a = 0
		
		Sound.playSound(shatterSound, 4)
		
		var particles = ObjectPool.particleOneShot(shatterParticles, self)
		particles.position = Vector2(47, 107)
		
		var dur = 2.0
		var targetX = flower.position.x + Util.rng.randf_range( - 500, 1000)
		var peakY = flower.position.y - Util.rng.randf_range(200, 600)
		var timeToPeak = dur * 0.4
		var flowerTween = create_tween().set_parallel()
		flowerTween.tween_property(flower, "position:x", targetX, dur)
		flowerTween.tween_property(flower, "position:y", peakY, 
		timeToPeak).set_trans(Tween.TRANS_QUAD).set_ease(Tween.EASE_OUT)

		flowerTween.tween_property(flower, "position:y", 250.0, 
			dur - timeToPeak).set_trans(Tween.TRANS_QUAD).set_ease(
			Tween.EASE_IN).from(peakY).set_delay(timeToPeak)
		
		flowerTween.tween_property(flower, "rotation", 
			Util.rng.randf_range( - 9, 9), dur)
		
		
		
		Game.onDecorationDestructed()
		
func onEnteringShop():
	broken = false
	vase.z_index = - 1
	vase.self_modulate.a = 1.0
	animation.play("RESET")
	enable()












