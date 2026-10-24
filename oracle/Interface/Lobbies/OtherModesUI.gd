extends Node2D

signal closed
signal cancel

var isOpen = false
var activeUI = null
var warpPointNodes: Array

onready var animation = $AnimationPlayer
onready var joinLobbyUI = $JoinLobbyUI
onready var hostLobbyUI = $CreateLobbyUI
onready var customUnrankedUI = $CustomUnrankedUI
onready var switchModeRankedUI = $SwitchModeRankedUI
onready var switchModeUnrankedUI = $SwitchModeUnrankedUI
onready var buttons = $Buttons
onready var customUnrankedButton = $Buttons / CustomUnranked / CustomUnrankedButton
onready var switchModeRankedButton = $Buttons / SwitchModeRanked / Button
onready var switchModeUnrankedButton = $Buttons / SwitchModeUnranked / Button
onready var switchModeRankedLeague = $Buttons / SwitchModeRanked / LeagueProgress

onready var UIs = [joinLobbyUI, hostLobbyUI, customUnrankedUI, 
	switchModeRankedUI, switchModeUnrankedUI]

func _ready():
	for ui in UIs:
		ui.connect("close", self, "close")
		ui.hide()
	
	Game.connect("warp_cursor_title", self, "onCursorWarp")
	add_to_group("Localized")
	
	Util.callNextFrame(self, "ready_deferred")

func ready_deferred():
	warpPointNodes = Util.getInteractableNodes(buttons)
	for ui in UIs:
		Util.walkInteractableNodes(ui, warpPointNodes)

func open():
	if not Game.draggedItem and not is_inside_tree():
		
		Game.titleScreen.add_child(self)
		isOpen = true
		animation.play("Open")
		for ui in UIs:
			ui.hide()
		buttons.show()
		
		if Game.hasArenaRunState():
			customUnrankedButton.disable()
			switchModeRankedButton.disable()
			switchModeUnrankedButton.disable()
		else:
			customUnrankedButton.enable()
			switchModeRankedButton.enable()
			switchModeUnrankedButton.enable()
			switchModeRankedLeague.updateUI(null)
		
		Util.updateLocaleInSubtree(self)

func updateLocale():
	switchModeRankedLeague.updateUI(null)

func opened():
	InputBlocker.deactivate(InputBlocker.Source.Popup)

func close(cancel: bool = false):
	if cancel:
		CustomRules.reset()
		if Game.hasArenaRunState():
			Game.restoreCustomRules(Game.arenaRunState)
		
		emit_signal("cancel")
		
	animation.play("Close")
	Game.unhoverAndHideTooltips()
	InputBlocker.activate(InputBlocker.Source.Popup)
	Sound.playSound_process(Game.transitionSounds[1], 0, 1.2)
	emit_signal("closed")

func closed():
	InputBlocker.deactivate(InputBlocker.Source.Popup)
	
	showButtons()
	isOpen = false
	get_parent().remove_child(self)

func showButtons():
	if activeUI != null:
		activeUI.close()
		activeUI = null
	buttons.show()
	
func hideButtons():
	if activeUI != null:
		activeUI.close()
	buttons.hide()

func onJoinLobbyPressed():
	hideButtons()
	activeUI = joinLobbyUI
	joinLobbyUI.open()

func onHostLobbyPressed():
	hideButtons()
	activeUI = hostLobbyUI
	hostLobbyUI.open()

func onCustomUnrankedPressed():
	hideButtons()
	activeUI = customUnrankedUI
	customUnrankedUI.open()

func onCancelPressed():
	close(true)


func onSwitchModeRankedPressed():
	hideButtons()
	activeUI = switchModeRankedUI
	switchModeRankedUI.open()


func onSwitchModeUnrankedPressed():
	hideButtons()
	activeUI = switchModeUnrankedUI
	switchModeUnrankedUI.open()

func onCursorWarp():
	for node in warpPointNodes:
		if node.is_visible_in_tree() and Util.isControlEnabled(node):
			Game.addControlOfInterest(node)

