extends Area2D

onready var timer = $Timer
var itemsInside = 0

func onItemEntered(body):
	
	timer.stop()
	itemsInside += 1
	if itemsInside == 1:
		Game.startCombatButton.disable()

func onItemExited(body):
	
	itemsInside -= 1
	if itemsInside == 0:
		timer.start(0.2)
		

func onTimeout():
	Game.startCombatButton.enable()
