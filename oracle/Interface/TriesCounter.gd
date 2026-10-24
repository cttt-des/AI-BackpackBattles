extends Node2D

onready var animation = $AnimationPlayer
onready var label = $Label

func _ready() -> void :
	updateLabel()
	Game.connect("run_started", self, "updateLabel")
	Game.connect("shop_opened", self, "checkTries")

func checkTries():
	if Game.getLastRoundResult() == Game.RoundResult.Loss:
		animation.play("Lose")
	updateLabel()

func updateLabel():
	label.text = String(Game.getTries())
