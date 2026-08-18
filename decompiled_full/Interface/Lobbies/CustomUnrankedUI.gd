extends Node2D

signal close

const buttonGroup = preload("res://Interface/Lobbies/MatchAgainstButtonGroup.tres")

var leagueButtons = []

onready var customRulesInput = $Rules

func _ready():
	for button in $Leagues.get_children():
		leagueButtons.push_back(button)
		button.group = buttonGroup
		
		var league = Game.Leagues.get(button.name, - 1)
		button.connect("pressed", self, "onLeagueSelected", [league])

func open():
	show()
	for button in leagueButtons:
		button.set_pressed_no_signal(false)
	var selectedLeague = CustomRules.getLeagueToMatch()
	leagueButtons[selectedLeague + 1].set_pressed_no_signal(true)
	customRulesInput.onOpen()

func close():
	pass

func onCancelPressed():
	close()
	emit_signal("close", true)

func onLeagueSelected(league):
	CustomRules.setLeagueToMatch(league)

func startGame():
	Game.startFreshRun(Game.Mode.Unranked)
	Game.titleScreen.clearItems()
	
	close()
	emit_signal("close")
