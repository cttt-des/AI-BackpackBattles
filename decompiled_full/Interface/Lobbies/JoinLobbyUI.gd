extends Node2D

signal close

const confirmationParticles = preload("res://Interface/Lobbies/UIConfirmationParticles.tscn")

var isOpen = false
var curLobbyCode: String

onready var LOBBIES = RunDatabase.lobbies

onready var lobbySearchbar = $Searchbar
onready var statusLabel = $StatusLabel
onready var joinButton = $JoinButton
onready var startTimer = $StartTimer
onready var cancelButton = $CancelButton
onready var lobbyInfo = $LobbyInfo
onready var speedSlider = $LobbyInfo / LobbySpeed / Speed
onready var runDurationLabel = $LobbyInfo / LobbySpeed / RunDuration
onready var customRulesIcon = $LobbyInfo / CustomRulesIcon
onready var matchmakingLabel = $LobbyInfo / Matchmaking
onready var matchmakingTooltipArea = $LobbyInfo / TooltipArea
onready var prioritizeHostNode = $LobbyInfo / PrioritizeHost

func _ready():
	add_to_group("Localized")
	Util.localizeFonts(lobbySearchbar)
	speedSlider.editable = false

func setConnected(connected: bool):
	Util.setConnected(connected, LOBBIES, "join_result", self, "onJoinResult")
	Util.setConnected(connected, LOBBIES, "lobby_join_confirmed", self, "onConnected")
	Util.setConnected(connected, LOBBIES, "config_changed", self, "onConfigChanged")
	Util.setConnected(connected, LOBBIES, "kicked", self, "onKickedFromLobby")
	Util.setConnected(connected, LOBBIES, "lobby_closed", self, "onLobbyClosed")
	Util.setConnected(connected, LOBBIES, "start_countdown", self, "startCountdown")
	Util.setConnected(connected, startTimer, "countdown_ended", self, "onCountdownEnded")

func isLobbyCodeWellFormated(code) -> bool:
	return code.length() >= 5

func onSearchbarInput(event):
	if lobbySearchbar.has_focus() and Util.isClickEvent(event):
		Util.showScreenKeyboard(lobbySearchbar)
		Game.onClickButton()

func onSearchbarTextChanged(newText):
	var caretPosition = lobbySearchbar.caret_position
	var cleanedCode = ""
	newText = newText.to_lower()
	for i in newText.length():
		var character = newText[i]
		if character in LOBBIES.symbolDict:
			cleanedCode += character
		else:
			if i < caretPosition:
				caretPosition -= 1
	
	curLobbyCode = cleanedCode
	lobbySearchbar.text = cleanedCode.to_upper()
	lobbySearchbar.caret_position = caretPosition
	
	joinButton.disabled = not isLobbyCodeWellFormated(cleanedCode)

func onSearchbarTextEnter(_newText):
	onJoinPressed()

func onJoinPressed():
	statusLabel.setTranslationKey("STATUS_Connecting")
	LOBBIES.joinParty(curLobbyCode)
	joinButton.disabled = true
	lobbySearchbar.editable = false

func onJoinResult(res):
	print("res: ", Util.enumToString(LOBBIES.JoinResult, res))
	
	if res == LOBBIES.JoinResult.Unconfirmed:
		statusLabel.setTranslationKey("STATUS_LobbyFound")
	
	elif res == LOBBIES.JoinResult.Restricted_AlreadyStarted:
		reset()







	else:
		
		reset()
		




	
func onConnected():
	statusLabel.setTranslationKey("STATUS_LobbyJoined")
	lobbyInfo.show()
	onConfigChanged()

func reset():
	lobbySearchbar.editable = true
	lobbySearchbar.text = ""
	joinButton.disabled = true
	cancelButton.enable()
	startTimer.hide()
	lobbyInfo.hide()
	statusLabel.setTranslationKey("STATUS_EnterCode")
	customRulesIcon.onHoverEnd()

func open():
	show()
	isOpen = true
	reset()
	
	Game.suspendRunState()
	setConnected(true)
	Util.localizeFonts(self)
	updateLocale()

func opened():
	InputBlocker.deactivate(InputBlocker.Source.Popup)

func close():
	isOpen = false
	
	setConnected(false)

func onKickedFromLobby(_responseCode):
	
	onRemovedFromLobby()

func onLobbyClosed():
	
	onRemovedFromLobby()


func onRemovedFromLobby():
	startTimer.stop()
	InputBlocker.restoreAllControls(InputBlocker.Source.Lobby)
	reset()
	
	
func cancel():
	close()
	LOBBIES.leaveLobby()
	Game.initPlayerFromRunstate()
	
	emit_signal("close", true)

func startCountdown():
	startTimer.startCountdown(LOBBIES.STARTGAME_COUNTDOWN)
	cancelButton.disable()
	InputBlocker.disableAllControls(InputBlocker.Source.Lobby, Game.titleScreen)
	InputBlocker.enableControls(InputBlocker.Source.Lobby, Game.titleScreen.classAndLoadoutNode)

func onCountdownEnded():
	InputBlocker.restoreAllControls(InputBlocker.Source.Lobby)
	Game.startLobbyRun()
	Game.titleScreen.clearItems()
	
	close()
	emit_signal("close")

func onConfigChanged():
	
	speedSlider.editable = true
	speedSlider.set_value_no_signal(LOBBIES.getSpeed())
	speedSlider.editable = false
	
	if LOBBIES.customRules != "":
		customRulesIcon.onCustomRulesChanged()
		customRulesIcon.show()
	else:
		customRulesIcon.hide()
		customRulesIcon.onHoverEnd()
	
	var matchmakingName = LOBBIES.MatchMaking.keys()[LOBBIES.getMatchmaking()]
	matchmakingLabel.setTranslationKey("MATCHING_" + matchmakingName + "_NAME")
	matchmakingTooltipArea.keyword = "MATCHING_" + matchmakingName
	prioritizeHostNode.visible = LOBBIES.getPrioritizeHost()

func updateLocale():
	lobbySearchbar.placeholder_text = Util.tra("UI_EnterCode")
