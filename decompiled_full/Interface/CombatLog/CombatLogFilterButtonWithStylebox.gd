extends "res://Interface/CombatLog/CombatLogFilterButton.gd"

export var hoverPressedStylebox: StyleBox

onready var normalStylebox = get("custom_styles/normal")
onready var pressedStylebox = get("custom_styles/pressed")
onready var hoverNormalStylebox = get("custom_styles/hover")
onready var normalFontColor = get("custom_colors/font_color")
onready var pressedFontColor = get("custom_colors/font_color_pressed")

func _ready():
	set("custom_colors/font_color_pressed", null)
	updateStyleboxes()

func toggle():
	.toggle()
	updateStyleboxes()

func updateStyleboxes():
	if isPressed:
		set("custom_styles/normal", pressedStylebox)
		set("custom_styles/hover", hoverPressedStylebox)
		set("custom_styles/pressed", hoverPressedStylebox)
		set("custom_colors/font_color", pressedFontColor)
		set("custom_colors/font_color_hover", pressedFontColor)
		set("custom_colors/font_color_focus", pressedFontColor)
		set("custom_colors/font_color_pressed", pressedFontColor)
	else:
		set("custom_styles/normal", normalStylebox)
		set("custom_styles/hover", hoverNormalStylebox)
		set("custom_styles/pressed", hoverNormalStylebox)
		set("custom_colors/font_color", normalFontColor)
		set("custom_colors/font_color_hover", normalFontColor)
		set("custom_colors/font_color_focus", normalFontColor)
		set("custom_colors/font_color_pressed", normalFontColor)
		
