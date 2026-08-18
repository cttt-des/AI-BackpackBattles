extends Node2D

onready var runDurationLabel = $RunDuration
onready var LOBBIES = RunDatabase.lobbies

func _ready():
	add_to_group("Localized")
	Util.localizeFonts(runDurationLabel)
	LOBBIES.connect("config_changed", self, "onSpeedChanged")
	onSpeedChanged()

func updateLocale():
	onSpeedChanged()

func onSpeedChanged():
	var minutes = LOBBIES.getRunDuration_Minutes()
	var average = LOBBIES.getAverageRoundDuration_seconds()
	
	runDurationLabel.text = Util.tra("FORMAT_LobbyDuration").format({
		"avrRound": average, "totalDur": minutes})
	
	
	
	
	
	
