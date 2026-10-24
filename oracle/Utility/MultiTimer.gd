extends Timer

signal multi_timeout

var timestamps = []

func _ready():
	one_shot = true
	process_mode = Timer.TIMER_PROCESS_PHYSICS
	connect("timeout", self, "onTimeout")

func start(time: float = - 1):
	if is_stopped():
		.start(time)
	else:
		timestamps.push_back(Util.time + time)








func stop():
	timestamps.clear()
	.stop()







func isFinished() -> bool:
	return timestamps.empty()

func onTimeout():
	emit_signal("multi_timeout")
	
	if not isFinished():
		var nextTimestamp = timestamps.pop_front()
		var dif = nextTimestamp - Util.time
		if dif > 0.05:
			start(dif)
		else:
			onTimeout()
	
	
