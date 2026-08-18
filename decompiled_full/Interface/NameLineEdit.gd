extends LineEdit

signal search_text_changed

export var placeholderKey = "UI_EnterName"

var framesUntilApply: int

func _ready() -> void :
	set_physics_process(false)
	
	connect("text_changed", self, "onTextChanged")
	connect("mouse_entered", self, "onHover")
	connect("mouse_exited", self, "onHoverEnd")
	connect("focus_exited", self, "onFocusLost")

	Util.localizeFonts(self)
	add_to_group("Localized")
	updateLocale()

func updateLocale():
	placeholder_text = tr(placeholderKey)

func onHover():
	modulate = Color(1.2, 1.1, 0.35)
	if Game.usingController:
		grab_focus()
		Game.onHoverInteractable(self)

func onHoverEnd():
	modulate = Color.white
	if Game.usingController:
		release_focus()
		Game.onHoverInteractableEnd(self)

func onFocusLost():
	deselect()

func _gui_input(event):
	if has_focus() and Util.isClickEvent(event):
		Util.showScreenKeyboard(self)
		Game.onClickButton()

func onTextChanged(_newText: String):
	framesUntilApply = 12
	set_physics_process(true)

func _physics_process(delta):
	framesUntilApply -= 1
	if framesUntilApply <= 0:
		apply()

func apply():
	set_physics_process(false)
	emit_signal("search_text_changed", text)
