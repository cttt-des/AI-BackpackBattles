extends Node2D

signal close

const buttonGroup = preload("res://Interface/Lobbies/MatchAgainstButtonGroup.tres")

var leagueButtons = []
var sandboxSelected = true
var hasSandboxOption = false

onready var customRulesInput = $Rules

func _ready():
	add_to_group("Localized")

	for button in $Leagues.get_children():
		leagueButtons.push_back(button)
		button.group = buttonGroup
		
		var league = Game.Leagues.get(button.name, - 1)
		var isSandbox = button.name == "Sandbox"
		if isSandbox:
			hasSandboxOption = true
		button.connect("pressed", self, "onLeagueSelected", [league, isSandbox])

	updateLocale()

func updateLocale():
	for button in leagueButtons:
		if button.name == "Sandbox":
			if TranslationServer.get_locale().begins_with("zh"):
				button.text = "创造模式"
			else:
				button.text = "Sandbox"
		elif button.name == "Unranked":
			button.text = Util.tra("UI_Unranked")
		else:
			button.text = Util.tra("LEAGUE_" + button.name)

func open():
	show()
	for button in leagueButtons:
		button.set_pressed_no_signal(false)
	var selectedLeague = CustomRules.getLeagueToMatch()
	var leagueOffset = 2 if hasSandboxOption else 1
	var defaultIndex = 0
	if selectedLeague != CustomRules.UNRANKED:
		defaultIndex = selectedLeague + leagueOffset
	sandboxSelected = hasSandboxOption and selectedLeague == CustomRules.UNRANKED
	CustomRules.setSandboxMode(sandboxSelected)
	defaultIndex = clamp(defaultIndex, 0, leagueButtons.size() - 1)
	leagueButtons[defaultIndex].set_pressed_no_signal(true)
	if sandboxSelected:
		CustomRules.setLeagueToMatch(CustomRules.UNRANKED)
	customRulesInput.onOpen()

func close():
	pass

func onCancelPressed():
	close()
	emit_signal("close", true)

func onLeagueSelected(league, isSandbox = false):
	sandboxSelected = isSandbox
	CustomRules.setSandboxMode(isSandbox)
	CustomRules.setLeagueToMatch(league)

func startGame():
	Game.startFreshRun(Game.Mode.Unranked)
	Game.titleScreen.clearItems()
	
	close()
	emit_signal("close")
