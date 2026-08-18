extends FocusGrabbingButton

const sound = preload("res://Assets/Sound/Thud3.wav")
const flySound = preload("res://Assets/Sound/Swoosh2.wav")

onready var animation = $AnimationPlayer
onready var umbrella = $Umbrella

var state = 0
var broken: = false

func _ready():
	Game.connect("switch_to_shop", self, "onEnteringShop")

func _on_UmbrellaBasket_button_down():
	var remainingTime = 0
	if animation.is_playing():
		remainingTime = animation.current_animation_length - animation.current_animation_position
	
	if remainingTime > 0.15: return
	animation.playback_speed = Util.rng.randf_range(0.9, 1.3)
	if state == 0:
		animation.play("Click1")
	else:
		animation.play("Click2")
	state = (state + 1) % 2
	Sound.playSound(sound, - 10)

func _gui_input(event):
	if Util.isRightClick(event) and not broken:
		broken = true
		animation.stop()
		
		Sound.playSound(flySound)
		
		
		var dur = 2.0
		var targetX = Util.rng.randf_range( - 2600, - 1700)
		var peakY = umbrella.position.y - Util.rng.randf_range(400, 900)
		var targetY = 500.0
		var timeToPeak = dur * 0.4
		
		var umbrellaTween = create_tween().set_parallel()
		umbrellaTween.tween_property(umbrella, "position:x", targetX, dur)
		umbrellaTween.tween_property(umbrella, "position:y", peakY, 
			timeToPeak).set_trans(Tween.TRANS_QUAD).set_ease(Tween.EASE_OUT)
		
		umbrellaTween.tween_property(umbrella, "position:y", targetY, 
			dur - timeToPeak).set_delay(timeToPeak).set_trans(
			Tween.TRANS_QUAD).set_ease(Tween.EASE_IN).from(peakY)
		
		umbrellaTween.tween_property(umbrella, "rotation", 
			Util.rng.randf_range( - 27, - 9), dur)
		
		umbrellaTween.tween_property(umbrella, "z_index", 50, 0.01).set_delay(0.05)
		
		
		
		Game.onDecorationDestructed()

func onEnteringShop():
	umbrella.z_index = 0
	broken = false
	animation.play("RESET")
	enable()
