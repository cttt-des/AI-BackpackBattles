extends Node2D

export (String) var aniName = "Attack"
export (float) var minSpeed = 0.8
export (float) var maxSpeed = 1.2
export (Vector2) var positionRandom = Vector2(30, 100)
export (float) var angleRandom = 5.0
export (bool) var showOnSelf = false

var poolingHandle
var animation
var missAniName: String

func preset():
	animation = $AnimationPlayer
	var character = get_node_or_null("FoxArcher")
	if character:
		character.hide()
		character.queue_free()
	missAniName = aniName + "Miss"
	
func returnToObjectPool():
	ObjectPool.returnInstance(self)

func randomizePosition():
	position.x += Util.rng.randf_range( - positionRandom.x, positionRandom.x)
	position.y += Util.rng.randf_range( - positionRandom.y, positionRandom.y)
	rotation_degrees = Util.rng.randf_range( - angleRandom, angleRandom)

func intialize(hit: bool):
	randomizePosition()
	
	animation.stop()
	animation.playback_speed = Util.rng.randf_range(minSpeed, maxSpeed)
	if hit:
		animation.play(aniName)
	else:
		animation.play(missAniName)
