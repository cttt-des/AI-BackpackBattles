extends FocusGrabbingButton

const emptyStylebox = preload("res://Interface/EmptyStylebox.tres")

export var url = ""

func _ready():
	mouse_default_cursor_shape = Control.CURSOR_POINTING_HAND
	set("custom_styles/focus", emptyStylebox)

func _pressed() -> void :
	var res = OS.shell_open(url)
