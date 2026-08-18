extends Node2D

signal countdown_ended

const tickSound = preload("res://Assets/Sound/ClockTicking1.ogg")

onready var timerLabel = $TimerLabel
onready var timer = $Timer
onready var animation = $AnimationPlayer
var timeLeft: int

func _ready():
	hide()

func startCountdown(time: int):
	show()
	timeLeft = time
	timerLabel.text = str(timeLeft)
	timer.start(1.0)
	Sound.playSound(tickSound)
	Game.closeAllMenus()

func stop():
	timer.stop()

func onTimeout():
	animation.play("Count")
	timeLeft -= 1
	if timeLeft > 0:
		timer.start(1.0)
		Sound.playSound(tickSound)
	else:
		emit_signal("countdown_ended")
	
	timerLabel.text = str(timeLeft)

