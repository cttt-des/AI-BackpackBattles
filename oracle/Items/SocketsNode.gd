tool
extends Node2D

func _ready() -> void :
	scale = Vector2.ONE / get_parent().scale
