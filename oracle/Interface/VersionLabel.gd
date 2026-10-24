extends FocusGrabbingButton

const patchNotesScene = preload("res://Interface/PatchNotes.tscn")

const previewVersion = ""


func _ready() -> void :
	if Game.TRAILER:
		hide()
	
	set_message_translation(false)
	
	text = ""
	
	if Game.ENGINEER_TEST:
		text = "TGS 2025"
	elif Game.PREVIEW:
		text = Game.VERSION + " LQA"
	elif Game.PLAYTEST:
		
		
		
		
		text = "1.1 Preview " + previewVersion
		if SteamHelper.STEAMDECK:
			text += " (Deck)"
		print(text)
	else:
		if not Game.FULLVERSION:
			text = "DEMO "
		text += Game.VERSION + Game.SUBVERSION
		if Game.BETA:
			text += " BETA"
	
	Game.patchNotes = patchNotesScene.instance()
	Game.patchNotes.init()
	Game.versionButton = self

func onPressed():
	Game.patchNotes.open()
