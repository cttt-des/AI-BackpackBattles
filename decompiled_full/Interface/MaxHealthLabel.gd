extends "res://Interface/MovingCounter.gd"

onready var bonusCounter = get_parent().get_node("HealthBonus")
onready var tooltipArea = $TooltipArea

func _ready() -> void :
	Game.PLAYER.connect("class_changed", self, "updateInstant")
	Game.PLAYER.connect("max_health_changed_ui", self, "updateInstant")
	
	Game.connect("round_start_health_gained", self, "showBonus")
	Game.connect("run_over", self, "updateTooltip", [2])
	updateInstant()
	Game.connect("continue_loaded", self, "updateFromRunstate")

func updateFromRunstate():
	if Game.hasArenaRunState():
		updateTooltip(Game.arenaRunState["round"] + 1)
		updateInstant()
	else:
		updateTooltip(2)
		
		
func updateInstant():
	setCurrent(Game.PLAYER.getMaxHealth())




func updateTooltip(forRound):
	tooltipArea.params = {"bonusHealth": Util.wrapInColor(
		"+" + String(Game.getHealthGain(forRound)), Util.paramColor)}
	

func showBonus(amount):
	updateTooltip(Game.curRound + 1)
	bonusCounter.show()
	bonusCounter.setCurrent(amount)
	bonusCounter.present()
	
	
	
	

	setTarget(Game.PLAYER.getMaxHealth())

func bonusFinishedCounting() -> void :
	bonusCounter.hide()
