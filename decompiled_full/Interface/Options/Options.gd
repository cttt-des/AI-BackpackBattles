extends Node2D

onready var titleButton = $Sheet / TitleButton
onready var closeLobbyButton = $Sheet / CloseLobbyButton
onready var animation = $AnimationPlayer
onready var languageButton = $Sheet / language
onready var chibiHint = $Sheet / ChibiHint
onready var windowModeButton = $Sheet / window_mode
onready var resolutionButton = $Sheet / resolution
onready var damageNumbersButton = $Sheet / damage_numbers

onready var credits = $Credits
onready var keyboardRebinds = $Sheet / Keybinds / Keyboard
onready var keyboardRebindsContainer = $Sheet / Keybinds / Keyboard / ScrollContainer
onready var controllerRebinds = $Sheet / Keybinds / Controller
onready var controllerRebindsContainer = $Sheet / Keybinds / Controller / ScrollContainer
onready var controllerRebindButtons = $Sheet / Keybinds / Controller / ScrollContainer / GridContainer.get_children()

const openSound = preload("res://Assets/Sound/TurningPage1.wav")

var isOpen: = false
var cursorWarpNodes: Array

func _ready() -> void :
	Game.connect("input_changed", self, "onInputChanged")
	Game.connect("warp_cursor_menu", self, "onCursorWarp")
	
	cursorWarpNodes = Util.getInteractableNodes(self)
	
	var showWindowMode = not Game.isWeb and not SteamHelper.STEAMDECK
	
	if showWindowMode:
		for mode in Settings.windowModes:
			windowModeButton.addItem("UI_" + mode)
		for resolution in Settings.resolutions:
			resolutionButton.addItem(resolution)
	else:
		windowModeButton.queue_free()
		windowModeButton = null
		resolutionButton.queue_free()
		resolutionButton = null
		$Sheet / mute_unfocused.queue_free()
		$Sheet / reduce_fps_unfocused.queue_free()
	
	var showLanguages = not Game.isWeb
	
	if showLanguages:
		$Sheet / SteamButton.hide()
		languageButton.show()
		Util.addFallbackFonts(languageButton.itemList.get("custom_fonts/font"))
		for language in Game.locales:
			languageButton.addItem(language)
	else:
		languageButton.queue_free()
		languageButton = null
		$Sheet / SteamButton.show()
	
	if SteamHelper.STEAMDECK:
		$Sheet / software_cursor.hide()
	
	onInputChanged()
	
	for mode in [Settings.DMG_NR_ALL, Settings.DMG_NR_CHAR, Settings.DMG_NR_ITEMS, Settings.DMG_NR_NONE]:
		damageNumbersButton.addItem(str("UI_DMG_NR_", mode))
	damageNumbersButton.selectItemByIndex(Settings.getVal(Settings.Setting.damage_numbers))

func onInputChanged():
	if SteamHelper.STEAMDECK or Game.usingController:
		switchToControllerBinds()
	else:
		switchToKeyboardBinds()

func switchToKeyboardBinds():
	controllerRebinds.hide()
	keyboardRebinds.show()
	

func switchToControllerBinds():
	controllerRebinds.show()
	keyboardRebinds.hide()
	for rebindButton in controllerRebindButtons:
		if rebindButton.has_method("updateButton"):
			rebindButton.updateButton()

func canOpen():
	return ( not is_inside_tree() and 
		Util.clockTime >= 2.3 and 
		not Game.draggedItem and 
		( not InputBlocker.isActive()
			or InputBlocker.isOnlySourceActive(InputBlocker.Source.Lobby)))
	
func open():
	isOpen = true
	
	Game.UINode.add_child_below_node(Game.UINode.get_node("OptionsPlaceholder"), self)
	Game.pause(Game.PauseSource.Options)
	Game.openMenu()
	
	Sound.playSound_process(openSound)
	animation.play("Open")
	chibiHint.hide()
	closeLobbyButton.visible = (Game.state == Game.State.Shop and Game.curMode == Game.Mode.Lobbies)
	titleButton.visible = (Game.state == Game.State.Shop and Game.curMode != Game.Mode.Lobbies)
	
	if languageButton:
		languageButton.selectItem(Game.localeToLanguage[TranslationServer.get_locale()])
		
	if windowModeButton:
		var selected = Settings.getVal(Settings.Setting.window_mode)


		windowModeButton.selectItemByIndex(Settings.windowModes.find(selected))
		resolutionButton.selectItem(Settings.getVal(Settings.Setting.resolution))

func opened():
	Game.openedMenu()

func _unhandled_input(event: InputEvent) -> void :
	if Util.isActionPressed_event(event, "options"):
		close()

func close():
	if visible and animation.current_animation == "":
		animation.play("Close")
		Sound.playSound_process(openSound, 0, 1.3)
		Game.onClickButton()
		chibiHint.hide()
		Game.closeMenu()

func closed():
	Game.unpause(Game.PauseSource.Options)
	get_parent().remove_child(self)
	isOpen = false

func onTitlePressed():
	if visible and animation.current_animation == "":
		Game.returnToTitle_midRun()
		close()

func _on_CreditsButton_pressed() -> void :
	if not credits.visible:
		animation.play("OpenCredits")

func _on_CloseCreditsButton_pressed() -> void :
	if credits.visible:
		animation.play("CloseCredits")

func onLanguageSelected(_index, language):
	Settings.setVal(Settings.Setting.language, Game.locales[language])











	
func onChibiButtonToggled(toggled):
	if toggled: chibiHint.show()

func onWindowModeSelected(index, _windowMode):
	Settings.setVal(Settings.Setting.window_mode, Settings.windowModes[index])

func onDamageNumberModeSelected(index, _mode):
	Settings.setVal(Settings.Setting.damage_numbers, index)

func onResolutionSelected(index, resolution):
	Settings.setVal(Settings.Setting.resolution, resolution)

func onCloseLobbyButtonPressed():
	
	if visible and animation.current_animation == "":
		InputBlocker.deactivate(InputBlocker.Source.Lobby)
		Game.leaveLobbyFromShop()
		close()

func onCursorWarp():
	for node in cursorWarpNodes:
		if node.is_visible_in_tree() and Util.isControlEnabled(node):
			if node is Slider:
				Game.addControlOfInterest(node)
			else:
				var pos = node.rect_global_position
				pos.x += min(40, node.rect_size.x * 0.5)
				pos.y += node.rect_size.y * 0.8
				var parent = node.get_parent()
				if parent is ControllerBindButton:
					Game.addPointOfInterest(pos, controllerRebindsContainer, node)
				elif parent is KeyBindButton:
					Game.addPointOfInterest(pos, keyboardRebindsContainer, node)
				else:
					Game.addPointOfInterest(pos)
