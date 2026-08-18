extends Node2D

var poolingHandle
var animation

func preset():
	animation = $AnimationPlayer
	Util.localizeFonts($RichTextLabel)

func _ready() -> void :
	animation.stop()
	animation.play("Show")

func returnToObjectPool():
	ObjectPool.returnInstance(self)
