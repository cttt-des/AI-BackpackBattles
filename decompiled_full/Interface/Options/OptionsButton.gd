extends FocusGrabbingTextureButton

func _ready():
	Game.options = load("res://Interface/Options/Options.tscn").instance()
	Game.connect("warp_cursor_shop", self, "onCursorWarp")
	Game.connect("warp_cursor_title", self, "onCursorWarp")
	Game.connect("warp_cursor_combat", self, "onCursorWarp")

func onPressed():
	.onPressed()
	if Game.options.canOpen():
		Game.options.open()
		hideHoverNodeAndTooltip()

func _unhandled_input(event: InputEvent) -> void :
	if InputBlocker.isActive(): return
	
	if Util.isActionPressed_event(event, "options"):
		if Game.options.canOpen():
			Game.options.open()

func onCursorWarp():
	Game.addPointOfInterest(rect_global_position + rect_size * 0.5)
