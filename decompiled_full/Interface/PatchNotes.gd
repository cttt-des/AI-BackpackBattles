extends Node2D

onready var label = $RichTextLabel
onready var animation = $AnimationPlayer
onready var titleLabel = get_node_or_null("Label4")
onready var hintLabel = get_node_or_null("Label5")
onready var versionLabel = get_node_or_null("Version")
onready var closeButton = $CloseButton
onready var updateButton = get_node_or_null("UpdateButton")
onready var ignoreButton = get_node_or_null("IgnoreButton")
onready var english = label.bbcode_text

export (String, MULTILINE) var demoPatchnotes
export (String, MULTILINE) var chinese
export (String, MULTILINE) var japanese

var customPopupActive = false
var customPopupMessage = ""
var customPopupTitle = ""
var customPopupVersion = ""
var customPopupUpdateUrl = ""
var customPopupUpdateText = ""
var customPopupCloseText = ""
var customPopupCloseUrl = ""
var customPopupIgnoreText = ""
var customPopupIgnoreVersion = ""
var customPopupQuitOnClose = false
var customPopupCloseOnUpdate = true
var customPopupQuitScheduled = false
var closeButtonDefaultPos = null
const AUTO_SHOW_RELEASE_PATCHNOTES = false

func _getPatchNoteVersionMarker() -> String:
	return String(Game.VERSION) + String(Game.SUBVERSION)

func init() -> void :
	resetCustomPopup()
	if is_instance_valid(versionLabel):
		versionLabel.text = "Version " + String(Game.VERSION) + Game.SUBVERSION
	
	label = $RichTextLabel
	
	if Game.PREVIEW:
		label.bbcode_text = "This is still a preview version. The changelog is coming soon! :)"
	elif Game.BETA:
		label.bbcode_text = "Have fun testing! If you encounter bugs, let us know on our Discord."


	elif Game.DEMO:
		label.bbcode_text = demoPatchnotes
	else:
		var patchMarker = _getPatchNoteVersionMarker()
		if AUTO_SHOW_RELEASE_PATCHNOTES and Util.later(patchMarker, Game.getPatchNoteVersion()):
			if Game.getNumStartedRuns() > 0:
				InputBlocker.activate(InputBlocker.Source.Popup)
				Util.callDelayed(self, "open", 3.0)
		
		Game.setPatchNoteVersion(patchMarker)
	
	Game.connect("warp_cursor_menu", self, "onCursorWarp")

func resetCustomPopup():
	customPopupActive = false
	customPopupMessage = ""
	customPopupTitle = ""
	customPopupVersion = ""
	customPopupUpdateUrl = ""
	customPopupUpdateText = ""
	customPopupCloseText = ""
	customPopupCloseUrl = ""
	customPopupIgnoreText = ""
	customPopupIgnoreVersion = ""
	customPopupQuitOnClose = false
	customPopupCloseOnUpdate = true
	customPopupQuitScheduled = false
	if closeButtonDefaultPos == null and is_instance_valid(closeButton):
		closeButtonDefaultPos = closeButton.rect_position
	if is_instance_valid(updateButton):
		updateButton.hide()
	if is_instance_valid(ignoreButton):
		ignoreButton.hide()
	if is_instance_valid(hintLabel):
		hintLabel.show()

func openCustom(message: String, titleText: String, versionText: String, updateUrl: String, updateText: String, closeText: String, quitOnClose: bool, closeOnUpdate: bool = true, closeUrl: String = "", ignoreText: String = "", ignoreVersion: String = ""):
	customPopupActive = true
	customPopupMessage = message
	customPopupTitle = titleText
	customPopupVersion = versionText
	customPopupUpdateUrl = updateUrl
	customPopupUpdateText = updateText
	customPopupCloseText = closeText
	customPopupCloseUrl = closeUrl
	customPopupIgnoreText = ignoreText
	customPopupIgnoreVersion = ignoreVersion
	customPopupQuitOnClose = quitOnClose
	customPopupCloseOnUpdate = closeOnUpdate
	open()

func _applyCustomPopup():
	if not is_instance_valid(label):
		return
	Util.localizeFonts(label)
	if is_instance_valid(titleLabel) and customPopupTitle != "":
		titleLabel.text = customPopupTitle
	if is_instance_valid(hintLabel):
		hintLabel.hide()
	if is_instance_valid(versionLabel):
		if customPopupVersion == "":
			versionLabel.hide()
		else:
			versionLabel.show()
			versionLabel.text = customPopupVersion
	label.bbcode_text = customPopupMessage
	if is_instance_valid(closeButton):
		closeButton.translationKey = ""
		closeButton.text = customPopupCloseText
	if is_instance_valid(updateButton):
		if customPopupUpdateUrl != "":
			updateButton.translationKey = ""
			updateButton.text = customPopupUpdateText
			updateButton.show()
		else:
			updateButton.hide()
	if is_instance_valid(ignoreButton):
		if customPopupIgnoreText != "":
			ignoreButton.translationKey = ""
			ignoreButton.text = customPopupIgnoreText
			ignoreButton.show()
		else:
			ignoreButton.hide()
	_updateCloseButtonLayout()

func _updateCloseButtonLayout():
	if not is_instance_valid(closeButton):
		return
	if closeButtonDefaultPos == null:
		closeButtonDefaultPos = closeButton.rect_position
	var hasUpdate = is_instance_valid(updateButton) and updateButton.visible
	var hasIgnore = is_instance_valid(ignoreButton) and ignoreButton.visible
	if not hasUpdate and not hasIgnore:
		var viewportWidth = get_viewport_rect().size.x
		var width = closeButton.rect_size.x
		if width <= 0:
			width = closeButton.rect_min_size.x
		closeButton.rect_position.x = (viewportWidth - width) * 0.5
		closeButton.rect_position.y = closeButtonDefaultPos.y
	else:
		closeButton.rect_position = closeButtonDefaultPos

func open():
	if not Game.draggedItem and not is_inside_tree():
		Game.UINode.add_child(self)
		Game.openMenu()
		Game.pause(Game.PauseSource.PatchNotes)
		animation.play("Open")
		if customPopupActive:
			call_deferred("_applyCustomPopup")
		else:
			Util.localizeFonts(label)
			if Game.PLAYTEST:
				label.bbcode_text = english
			else:
				if TranslationServer.get_locale() == "zh_Hans_CN":
					label.bbcode_text = chinese
				elif TranslationServer.get_locale() == "ja":
					label.bbcode_text = japanese
				else:
					label.bbcode_text = english

func animationFinished(_aniName):
	InputBlocker.deactivate(InputBlocker.Source.Popup)

func onClosePressed():
	if animation.current_animation == "":
		animation.play("Close")
		Game.onClickButton()
		Game.closeMenu(false)
		InputBlocker.activate(InputBlocker.Source.Popup)
		if customPopupCloseUrl != "":
			OS.shell_open(customPopupCloseUrl)
		if customPopupQuitOnClose and not customPopupQuitScheduled:
			customPopupQuitScheduled = true
			Util.callDelayed(get_tree(), "quit", 0.2)
	
func onCloseFinished():
	Game.unpause(Game.PauseSource.PatchNotes)
	Game.onPatchNotesClosed()
	get_parent().remove_child(self)
	if customPopupQuitOnClose:
		get_tree().quit()

func onUpdatePressed():
	if customPopupUpdateUrl != "":
		OS.shell_open(customPopupUpdateUrl)
	if customPopupCloseOnUpdate:
		onClosePressed()

func onIgnorePressed():
	if customPopupIgnoreVersion != "":
		Game.setConfigValue("Mod", "IgnoreUpdateVersion", customPopupIgnoreVersion)
	onClosePressed()

func onCursorWarp():
	if is_inside_tree() and closeButton != null:
		Game.addControlOfInterest(closeButton)
	if is_inside_tree() and is_instance_valid(updateButton) and updateButton.visible:
		Game.addControlOfInterest(updateButton)
	if is_inside_tree() and is_instance_valid(ignoreButton) and ignoreButton.visible:
		Game.addControlOfInterest(ignoreButton)
