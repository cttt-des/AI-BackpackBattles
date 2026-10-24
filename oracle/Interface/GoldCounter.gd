extends "res://Interface/MovingCounter.gd"

const positiveChangeColor = Color(0.639343, 1, 0.392578)
const negativeChangeColor = Color(1, 0.392578, 0.392578)

onready var bonusCounter = get_parent().get_node("GoldBonus")
onready var tooltipArea = $TooltipArea

var lastChangeTime = 0.0
var lastChange = 0

func _ready() -> void :
	Game.PLAYER.connect("class_changed", self, "updateInstant")
	Game.connect("gold_changed", self, "updateCounting")
	updateInstant()

func updateInstant():
	setCurrent(Game.getGold())

func updateCounting(change):
	if change == 0: return
	
	if Util.time <= lastChangeTime + 0.1:
		change += lastChange
	
	if change > 0:
		bonusCounter.prefix = "+"
		bonusCounter.set("custom_colors/font_color", positiveChangeColor)
	else:
		bonusCounter.prefix = ""
		bonusCounter.set("custom_colors/font_color", negativeChangeColor)
	
	bonusCounter.show()
	bonusCounter.setCurrent(change)
	bonusCounter.present()
	
	lastChangeTime = Util.time
	lastChange = change
	
	
	
	
	setTarget(Game.getGold())

func bonusFinishedCounting():
	bonusCounter.hide()


func showTooltip():
	var forRound = Game.curRound + 1

	if CustomRules.isSwitchMode():
		tooltipArea.keyword = "Gold_SwitchMode"
	else:
		tooltipArea.keyword = "Gold"
	tooltipArea.params = {"bonusGold": Util.wrapInColor(
		"+" + String(Game.getGoldGain(forRound)), Util.paramColor)}
