extends AnimationPlayer

func _process(delta):
	if Engine.time_scale == 0:
		playback_speed = 0
	else:
		playback_speed = 1 / Engine.time_scale
