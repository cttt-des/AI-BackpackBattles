extends Node2D

onready var animation = $AnimationPlayer




func _on_Button_button_down():
	animation.play("RESET")
	animation.advance(1)
	animation.play("Click", - 1, Util.rng.randf_range(0.5, 1.5))

func onRoll():
	animation.play("RESET")
	animation.advance(1)
	animation.play("Roll", - 1, Util.rng.randf_range(0.8, 1.2))
