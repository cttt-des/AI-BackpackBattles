extends Node2D

signal close

const confirmationParticles = preload("res://Interface/Lobbies/UIConfirmationParticles.tscn")
const buttonGroup = preload("res://Interface/Lobbies/MatchmakingButtonGroup.tres")
const successSound = preload("res://Assets/Sound/Chime2.mp3")
const teamSwitchValidationPopupScene = preload("res://Interface/Lobbies/TeamSwitchValidationPopup.tscn")

var isOpen = false

onready var LOBBIES = RunDatabase.lobbies
onready var createLobbyButton = $CreateLobbyButton
onready var lobbyCodeLabel = $LobbyCode / LobbyCode
onready var statusLabel = $StatusLabel
onready var startGameButton = $StartGameButton
onready var cancelButton = $CancelButton
onready var cancelButtonLabel = $CancelLabel
onready var lobbyCodeNode = $LobbyCode
onready var copyButton = $LobbyCode / CopyButton
onready var startTimer = $StartTimer
onready var speedSlider = $Settings / LobbySpeed / Speed
onready var runDurationLabel = $Settings / LobbySpeed / RunDuration
onready var memberLimitApplyTimer = $Settings / ApplyTimer
onready var memberLimitSpinbox = $Settings / MemberLimit

onready var customRulesTooltip = $CustomRulesTooltip
onready var customRulesInput = $CustomRulesTooltip / VBoxContainer
onready var customRulesTimer = $Settings / CustomRulesTimer
onready var customRulesIcon = $Settings / CustomIcon

onready var matchmakingTooltip = $MatchmakingTooltip
onready var matchmakingModes = $MatchmakingTooltip / Modes
var matchmakingButtons: Array

onready var prioritizeHostButton = $MatchmakingTooltip / PrioritizeHost / Button

var teamSwitchValidationPopup = null

func _ready():
	for button in matchmakingModes.get_children():
		matchmakingButtons.push_back(button)
		button.group = buttonGroup
		Util.localizeFonts(button)
		var mode = LOBBIES.MatchMaking[button.name]
		button.connect("pressed", self, "onMatchmakingSelected", [mode])
	
	speedSlider.connect("value_changed", self, "onSpeedChanged")

func setConnected(connected: bool):
	Util.setConnected(connected, LOBBIES, "lobby_created", self, "onLobbyCreated")
	Util.setConnected(connected, startTimer, "countdown_ended", self, "onCountdownEnded")
	Util.setConnected(connected, customRulesTimer, "timeout", self, "applyCustomRules")

func setStatus(status):
	statusLabel.setTranslationKey(status)

func open():
	show()
	isOpen = true
	lobbyCodeNode.hide()
	startGameButton.hide()
	
	cancelButton.enable()
	cancelButtonLabel.setTranslationKey("BUTTON_Cancel")
	createLobbyButton.disabled = false
	createLobbyButton.show()
	statusLabel.hide()
	speedSlider.editable = true
	speedSlider.max_value = LOBBIES.SpeedLevel.size()
	speedSlider.tick_count = LOBBIES.SpeedLevel.size()
	speedSlider.set_value_no_signal(LOBBIES.getSpeed())
	
	memberLimitSpinbox.editable = true
	memberLimitSpinbox.max_value = LOBBIES.MAX_MEMBERS
	memberLimitSpinbox.min_value = LOBBIES.MIN_MEMBERS
	memberLimitSpinbox.set_value_no_signal(LOBBIES.getLobbySize())
	memberLimitSpinbox.apply()
	
	customRulesIcon.texture = CustomRules.defaultIcon
	customRulesTooltip.hide()
	
	for button in matchmakingButtons:
		button.set_pressed_no_signal(false)
	matchmakingButtons[LOBBIES.matchMaking].set_pressed_no_signal(true)
	matchmakingTooltip.hide()
	
	prioritizeHostButton.set_pressed_no_signal(LOBBIES.prioritizeHost)
	
	startTimer.hide()
	setConnected(true)
	Game.suspendRunState()

func onCreateLobbyPressed():
	
	createLobbyButton.hide()
	statusLabel.show()
	setStatus("STATUS_CreatingLobby")
	LOBBIES.createParty()

func onLobbyCreated(lobbyId: String):
	statusLabel.show()
	setStatus("STATUS_LobbyCreated")
	lobbyCodeNode.show()
	lobbyCodeLabel.bbcode_text = "[center]" + lobbyId.to_upper()
	cancelButtonLabel.setTranslationKey("BUTTON_CloseLobby")
	
	startGameButton.show()
	Sound.playSound(successSound)

func onSpeedChanged(value: float):
	LOBBIES.setSpeed_Host(int(value))

func onMemberLimitChanged(value: float):
	memberLimitApplyTimer.start(0.3)

func updateMemberLimit():
	LOBBIES.setLobbySize_Host(int(memberLimitSpinbox.value))

func onCopyButtonPressed():
	OS.set_clipboard(lobbyCodeLabel.text)
	var particles = ObjectPool.particleOneShot(confirmationParticles, self)
	particles.global_position = copyButton.rect_global_position + copyButton.rect_size * 0.5

func onStartGamePressed():
	Game.onClickButton()
	
	if CustomRules.isTeamSwitchMode():
		var result = LOBBIES.calculateTeams()
		var lines = []
		
		
		for teamName in result.teams:
			var members = result.teams[teamName]
			lines.append(teamName + " 队队员：")
			for steamId in members:
				lines.append("  - " + LOBBIES.memberData[steamId].playerName)
		
		
		if result.unassigned.size() > 0:
			lines.append("无组队：")
			for steamId in result.unassigned:
				lines.append("  - " + LOBBIES.memberData[steamId].playerName)
		
		if LOBBIES.isSingleTeamMatchPoolResult(result):
			lines.append("将使用个人职业段位匹配池，对内继续交换背包")

		showTeamSwitchValidationPopup(lines)
		return
	
	actuallyStartGame()

func actuallyStartGame():
	startGameButton.hide()
	cancelButton.disable()
	speedSlider.editable = false
	memberLimitSpinbox.editable = false
	LOBBIES.startCountdown()
	startTimer.startCountdown(LOBBIES.STARTGAME_COUNTDOWN)
	
	Util.finishTimer(customRulesTimer)
	
	InputBlocker.disableAllControls(InputBlocker.Source.Lobby, self)
	InputBlocker.disableAllControls(InputBlocker.Source.Lobby, Game.titleScreen)
	InputBlocker.enableControls(InputBlocker.Source.Lobby, Game.titleScreen.classAndLoadoutNode)

func showTeamSwitchValidationPopup(issues: Array):
	if teamSwitchValidationPopup != null:
		teamSwitchValidationPopup.queue_free()
	
	teamSwitchValidationPopup = teamSwitchValidationPopupScene.instance()
	add_child(teamSwitchValidationPopup)
	teamSwitchValidationPopup.preset()
	teamSwitchValidationPopup.setContent(issues)
	teamSwitchValidationPopup.showPopup()
	teamSwitchValidationPopup.connect("force_start", self, "onTeamSwitchForceStart")
	teamSwitchValidationPopup.connect("cancel", self, "onTeamSwitchCancel")
	teamSwitchValidationPopup.connect("tree_exited", self, "onTeamSwitchPopupClosed")

func onTeamSwitchForceStart():
	actuallyStartGame()

func onTeamSwitchCancel():
	startGameButton.show()
	cancelButton.enable()

func onTeamSwitchPopupClosed():
	teamSwitchValidationPopup = null

func onCountdownEnded():
	InputBlocker.restoreAllControls(InputBlocker.Source.Lobby)
	Game.startLobbyRun()
	Game.titleScreen.clearItems()
	
	close()
	emit_signal("close")

func close():
	isOpen = false
	setConnected(false)

func onCancelPressed():
	close()
	
	LOBBIES.leaveLobby()
	Game.initPlayerFromRunstate()
	
	emit_signal("close", true)

func onCustomRulesPressed():
	if customRulesTooltip.visible:
		hideCustomRules()
	else:
		showCustomRules()

func showCustomRules():
	customRulesTooltip.show()
	customRulesInput.onOpen()

func hideCustomRules():
	customRulesTooltip.hide()

func onCustomRulesChanged():
	print("[CreateLobbyUI] onCustomRulesChanged, areCustomRulesChanged=", CustomRules.areCustomRulesChanged(), " isTeamSwitchMode=", CustomRules.isTeamSwitchMode())
	customRulesTimer.start(0.5)
	if CustomRules.areCustomRulesChanged():
		customRulesIcon.texture = CustomRules.activeIcon
	else:
		customRulesIcon.texture = CustomRules.defaultIcon

func applyCustomRules():
	print("[CreateLobbyUI] applyCustomRules called, areCustomRulesChanged=", CustomRules.areCustomRulesChanged(), " serialize=", CustomRules.serialize())
	if CustomRules.areCustomRulesChanged():
		LOBBIES.setCustomRules_Host(CustomRules.serialize())
	else:
		LOBBIES.setCustomRules_Host("")

func onMatchmakingPressed():
	if matchmakingTooltip.visible:
		matchmakingTooltip.hide()
	else:
		matchmakingTooltip.show()

func onMatchmakingSelected(mode: int):
	LOBBIES.setMatchMaking_Host(mode, LOBBIES.prioritizeHost)

func onPrioritizeHostToggled(pressed):
	LOBBIES.setMatchMaking_Host(LOBBIES.matchMaking, pressed)
