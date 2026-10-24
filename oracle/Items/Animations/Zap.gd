extends Node2D

var poolingHandle
var sprite
var animation

const zapSize = [
	100.0, 100.0
]

const zapAnis = [
	"Zap", 
	"SmallZap"
]

enum ZapStyle{
	Large = 0, 
	Small = 1
}

func preset():
	sprite = $Sprite
	animation = $AnimationPlayer

func zap(startPos: Vector2, endPos: Vector2, style: int = ZapStyle.Large):
	global_position = startPos
	var dif = endPos - startPos
	sprite.scale.x = dif.length()
	sprite.scale.y = zapSize[style]
	look_at(endPos)
	sprite.material.set_shader_param("frequency", sprite.scale.x * 0.02)
	sprite.material.set_shader_param("speed", Util.rng.randf_range(4.0, 4.02))
	animation.play(zapAnis[style])

func returnToObjectPool():
	animation.stop()
	ObjectPool.returnInstance(self)
