extends Particles2D

var timer

func _ready() -> void :
	timer = Timer.new()
	timer.one_shot = true
	timer.connect("timeout", self, "timeout")
	add_child(timer)
	hide()

func activate():
	timer.stop()
	
	
	show()
	
	if one_shot:
		restart()
		startTimer()
	else:
		emitting = true

func deactivate():
	if visible:
		emitting = false
		startTimer()

func startTimer():
	timer.start(lifetime * (1 + (1 - explosiveness) / speed_scale))

func timeout():
	hide()

func instantClear():
	timer.stop()
	restart()
	emitting = false
	hide()
