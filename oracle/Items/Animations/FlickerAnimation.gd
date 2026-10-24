extends AnimationPlayer

export var ani = "Flicker"
export var minDist = 0.1
export var maxDist = 3.0
export var minSpeed = 0.3
export var maxSpeed = 1.0

func _ready():
	connect("animation_finished", self, "onAnimationEnded")
	onAnimationEnded(ani)

func onAnimationEnded(aniName):
	Util.callDelayed(self, "playAni", Util.rng.randf_range(minDist, maxDist))

func playAni():
	playback_speed = Util.rng.randf_range(minSpeed, maxSpeed)
	play(ani)
