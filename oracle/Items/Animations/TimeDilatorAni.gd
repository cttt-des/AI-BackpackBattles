extends "res://Utility/PooledScene.gd"

var animation

func preset():
	animation = $AnimationPlayer

func _ready():
	animation.stop()
	animation.play("SpeedUp")
