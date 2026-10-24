extends Node2D

signal close

onready var leagueProgressUI = $LeagueProgress

func _ready():
	$Hint.formatParams = {"gold": Util.getIcon("gold")}
	add_to_group("Localized")
	updateLocale()
	
func updateLocale():
	pass

func open():
	show()
	leagueProgressUI.updateUI(null)

func close():
	pass

func onCancelPressed():
	close()
	emit_signal("close", true)

func startGame():
	CustomRules.setSwitchMode(CustomRules.SwitchModeState.Ranked)
	Game.startFreshRun(Game.Mode.Unranked)
	Game.titleScreen.clearItems()
	
	close()
	emit_signal("close")
