extends ResizableControl

const activationButtonKeys = [
	"CombatLog_HideActivations", 
	"CombatLog_MinimizeActivations", 
	"CombatLog_ShowActivations"
	]

var isOpen: bool = false
var buttonsReset: bool = false


onready var searchBar = $Searchbar
onready var openButton = $OpenButton
onready var activationsButton = $Activations
onready var playButton = $PlayButton
onready var playFromStartButton = $PlayFromStartButton
onready var playBackwardsButton = $PlayBackButton
onready var playFromEndButton = $PlayFromEndButton

onready var filterButtons = [
	searchBar, activationsButton, 
	playButton, playFromStartButton, playBackwardsButton, playFromEndButton
]

onready var replayButtons = [
	playButton, playFromStartButton, playBackwardsButton, playFromEndButton
]

onready var MARGIN_TOP_OPEN = margin_top
onready var MARGIN_RIGHT_OPEN = margin_right

func _ready() -> void :
	close()
	Game.connect("returned_to_title", self, "reset")
	Game.connect("shop_opened", self, "reset")
	Game.connect("combat_end", self, "onCombatEnd")
	Game.combatLog.connect("replay_finished", self, "onReplayFinished")
	Util.localizeFonts(activationsButton)
	add_to_group("Localized")
	updateActivationsButton()
	setReplayButtonsDisabled(true)

func open():
	isOpen = true
	for button in filterButtons:
		button.show()
	
	margin_top = MARGIN_TOP_OPEN
	margin_right = MARGIN_RIGHT_OPEN
	openButton.flip_h = false
	
	if not Game.isTutorialDone(Game.TutorialSteps.CombatLogButtons):
		Game.setTutorialDone(Game.TutorialSteps.CombatLogButtons)
		Game.combatLog.buttonTutorialAni.play("RESET")

func close():
	isOpen = false
	for button in filterButtons:
		button.hide()
	for button in replayButtons:
		button.pressed = false
	
	margin_top = - 52
	margin_right = 83
	openButton.flip_h = true

func setReplayButtonsDisabled(disabled):
	for button in replayButtons:
		button.disabled = disabled

func _on_OpenButton_pressed() -> void :
	if isOpen:
		close()
	else:
		open()

func reset():
	if searchBar.text != "":
		searchBar.clear()
	setReplayButtonsDisabled(true)

func updateLocale():
	updateActivationsButton()

func updateActivationsButton():
	activationsButton.translationKey = activationButtonKeys[Game.combatLog.activationsState]
	activationsButton.updateLocale()

func onActivationsButtonPressed(_pressed):
	var newState = (Game.combatLog.activationsState + 1) % 3
	Game.combatLog.setActivationState(newState)
	updateActivationsButton()

func onPlayButtonToggled(pressed):
	if not buttonsReset:
		resetReplayButtons(playButton)
		if pressed:
			Game.combatLog.replayCombat(false)
		else:
			Game.combatLog.stopReplay()
	
func onPlayFromStartButtonToggled(pressed):
	if not buttonsReset:
		resetReplayButtons(playFromStartButton)
		if pressed:
			Game.combatLog.replayCombat(true)
		else:
			Game.combatLog.stopReplay()
		
func onPlayBackwardsButtonToggled(pressed):
	if not buttonsReset:
		resetReplayButtons(playBackwardsButton)
		if pressed:
			Game.combatLog.replayCombat(false, - 1.0)
		else:
			Game.combatLog.stopReplay()

func onPlayFromEndButtonToggled(pressed):
	if not buttonsReset:
		resetReplayButtons(playFromEndButton)
		if pressed:
			Game.combatLog.replayCombat(true, - 1.0)
		else:
			Game.combatLog.stopReplay()


func resetReplayButtons(except):
	buttonsReset = true
	for button in replayButtons:
		if button != except:
			button.pressed = false
	buttonsReset = false

func onReplayFinished():
	resetReplayButtons(null)

func onCombatEnd(_roundResult):
	setReplayButtonsDisabled(false)
