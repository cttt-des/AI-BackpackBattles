extends Label

signal counting_finished

var currentValue: float = 0
var targetValue: int = 0

onready var animation = $AnimationPlayer

export (String) var prefix = ""
export (float, 0, 0.1, 0.001) var constantSpeed = 0.024
export (float, 0, 0.1, 0.01) var linearSpeed = 0.04

func _ready() -> void :
	set_message_translation(false)

func updateLabel():
	text = prefix + String(round(currentValue))

func _physics_process(_delta):
	var dif: float = targetValue - currentValue
	
	if abs(dif) < 1:
		currentValue = targetValue
		
		emit_signal("counting_finished")
		set_physics_process(false)
	else:
		var step = linearSpeed * dif + sign(dif) * constantSpeed
		currentValue += step
	
	updateLabel()

func setTarget(target: int):
	animation.play("RESET")
	targetValue = target
	set_physics_process(true)

func setCurrent(current):
	
	animation.play("RESET")
	currentValue = current
	updateLabel()
	set_physics_process(false)
	
	

func change(amount: int):
	
	animation.play("RESET")
	targetValue = currentValue + amount
	
	set_physics_process(true)

func fade():
	animation.play("Hide")

func present():
	animation.play("Present")
	
