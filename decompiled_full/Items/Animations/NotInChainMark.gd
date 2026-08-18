extends Node2D

var poolingHandle

func preset():
	pass

func _ready() -> void :
	hide()

func appear():
	show()
	global_rotation = 0

func disappear():
	hide()

