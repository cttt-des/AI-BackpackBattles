extends Node2D

onready var label = $RichTextLabel
onready var animation = $AnimationPlayer
onready var closeButton = $CloseButton
onready var english = label.bbcode_text

export (String, MULTILINE) var demoPatchnotes
export (String, MULTILINE) var chinese
export (String, MULTILINE) var japanese

func init() -> void :
	$Version.text = "Version " + String(Game.VERSION) + Game.SUBVERSION
	
	label = $RichTextLabel
	
	if Game.PREVIEW:
		label.bbcode_text = "This is still a preview version. The changelog is coming soon! :)"
	elif Game.BETA:
		label.bbcode_text = "Have fun testing! If you encounter bugs, let us know on our Discord."


	elif Game.DEMO:
		label.bbcode_text = demoPatchnotes
	elif Util.later(Game.VERSION, Game.getPatchNoteVersion()):
		
		Game.setPatchNoteVersion(Game.VERSION)
		
		if Game.getNumStartedRuns() > 0:
			InputBlocker.activate(InputBlocker.Source.Popup)
			Util.callDelayed(self, "open", 3.0)
	
	Game.connect("warp_cursor_menu", self, "onCursorWarp")

func open():
	if not Game.draggedItem and not is_inside_tree():
		Game.UINode.add_child(self)
		Game.openMenu()
		Game.pause(Game.PauseSource.PatchNotes)
		animation.play("Open")
		
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
	
func onCloseFinished():
	Game.unpause(Game.PauseSource.PatchNotes)
	Game.onPatchNotesClosed()
	get_parent().remove_child(self)

func onCursorWarp():
	if is_inside_tree() and closeButton != null:
		Game.addControlOfInterest(closeButton)
