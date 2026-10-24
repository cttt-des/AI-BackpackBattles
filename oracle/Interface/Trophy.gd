extends Sprite

onready var trophy = $Trophy
onready var trail = $Trophy / Trail
onready var animation = $AnimationPlayer
onready var trailParticles = $Trophy / TrailParticles

const moveSound = preload("res://Assets/Sound/Swoosh3.wav")
const arriveSound = preload("res://Assets/Sound/Bell2.mp3")
const popinSound = preload("res://Assets/Sound/Bell2.mp3")

func setEmpty():
	trophy.position = Vector2.ZERO
	animation.play("RESET")
	animation.advance(1)

func setFull():
	trophy.position = Vector2.ZERO
	trophy.scale = Vector2(0.9, 0.9)

func popIn():
	trophy.position = Vector2.ZERO
	animation.play("Popin")
	Sound.playSound(popinSound)

func moveToPos(pos: Vector2):
	animation.play("Move")
	
	trailParticles.activate()
	var tween = create_tween()
	tween.set_ease(Tween.EASE_IN)
	tween.set_trans(Tween.TRANS_BACK)
	tween.tween_property(trophy, "global_position", pos, 1.0)
	tween.tween_callback(trail, "stop").set_delay(2)
	tween.tween_callback(trailParticles, "deactivate")
	Sound.playRising(moveSound)
	Util.callDelayed(Sound, "playRising", 1.0, [arriveSound])
