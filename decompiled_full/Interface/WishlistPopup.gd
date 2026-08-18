extends Node2D

signal closed

onready var animation = $AnimationPlayer

const openSound = preload("res://Assets/Sound/TurningPage1.wav")

func open():
	Game.UINode.add_child(self)
	Game.pause(Game.PauseSource.Options)
	animation.play("Open")
	Sound.playSound_process(openSound)

func close():
	if animation.current_animation == "":
		animation.play("Close")
		Sound.playSound_process(openSound, 0, 1.3)
		yield(animation, "animation_finished")
		Game.unpause(Game.PauseSource.Options)
		emit_signal("closed")
		queue_free()
