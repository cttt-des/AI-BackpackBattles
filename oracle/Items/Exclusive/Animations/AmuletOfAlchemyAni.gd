extends "res://Utility/PooledScene.gd"

var particles1
var particles2

func preset():
	particles1 = $Particles2D
	particles2 = $Particles2D2

func moveTo(pos, duration):
	var tween = create_tween()
	particles1.emitting = true
	tween.tween_property(self, "global_position", pos, duration)
	tween.tween_callback(particles1, "set_emitting", [false])
	tween.tween_callback(particles2, "restart")
	tween.tween_callback(self, "returnToObjectPool").set_delay(particles1.lifetime)
