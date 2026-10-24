extends "res://Utility/PooledScene.gd"

var animation

func preset():
	.preset()
	animation = $AnimationPlayer

func _ready():
	animation.play("PopIn")
