extends Node2D

onready var animation = $AnimationPlayer
onready var label = $Label

func _ready() -> void :
	updateLabel()
	Game.connect("run_started", self, "updateLabel")
	Game.connect("shop_opened", self, "checkWins")

func checkWins():
	if Game.getLastRoundResult() == Game.RoundResult.Win:
		animation.play("Win")
	else:
		updateLabel()

func updateLabel():
	label.text = String(Game.getNumWins())
