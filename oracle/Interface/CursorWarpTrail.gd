extends Line2D

var poolingHandle
var animation

func preset():
	animation = $AnimationPlayer

func setPoints(startPos, endPos):
	points[0] = startPos
	points[1] = endPos
	animation.play("Fade")

func _physics_process(delta):
	animation.advance(1 / 60.0)

func returnToObjectPool():
	ObjectPool.returnInstance(self)
