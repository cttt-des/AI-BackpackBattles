extends Node2D

onready var animation = $AnimationPlayer
onready var label = $Label

func _ready() -> void :
	updateLabel()
	Game.connect("run_started", self, "updateLabel")
	Game.connect("shop_opened", self, "incrementRound")

func incrementRound():
	animation.play("Increment")

func updateLabel():
	label.text = String(Game.curRound)
