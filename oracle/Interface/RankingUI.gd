extends Node2D

onready var leagueProgressUI = $LeagueProgress
onready var switchModeIcon = $SwitchMode

func _ready() -> void :
	add_to_group("Localized")
	updateLocale()
	
	
	Game.connect("continue_loaded", self, "updateLocale")
	Game.connect("runstate_loaded", self, "updateLocale")
	Game.connect("return_to_title", self, "updateLocale")
	Game.connect("returned_to_title", self, "updateLocale")
	Game.connect("character_changed", self, "updateLocale")
	Game.connect("runstate_suspended", self, "updateLocale")
	
	
	
func updateLocale():
	if Game.state == Game.State.Title:
		visible = Game.isClassUnlocked()
	
	leagueProgressUI.updateUI(Game.curClass)
	
	switchModeIcon.visible = Game.isRankedSwitchMode()
