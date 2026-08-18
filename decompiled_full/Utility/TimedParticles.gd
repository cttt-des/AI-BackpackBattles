extends Particles2D

func activate(duration: float):
	restart()
	Util.callDelayed(self, "deactivate", duration)

func deactivate():
	emitting = false
	
