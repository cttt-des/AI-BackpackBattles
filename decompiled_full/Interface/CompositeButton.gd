extends FocusGrabbingButton

export (NodePath) var labelPath
onready var hoverLabel = get_node_or_null(labelPath)
var hoverLabel_colorPath
var hoverLabel_defaultColor
const disabledColor = Color(0.693359, 0.65267, 0.601273)

export (NodePath) var iconPath
onready var hoverIcon = get_node_or_null(iconPath)
var iconNormal
export (Texture) var iconHovered
export (Texture) var iconDisabled
export (Texture) var iconPressed

func _ready():
	if hoverLabel != null:
		if hoverLabel is Label:
			hoverLabel_colorPath = "custom_colors/font_color"
		else:
			hoverLabel_colorPath = "custom_colors/default_color"
		
		hoverLabel_defaultColor = hoverLabel.get(hoverLabel_colorPath)
	
	if hoverIcon != null:
		iconNormal = hoverIcon.texture

func onHover():
	.onHover()
	if hoverLabel != null:
		hoverLabel.set(hoverLabel_colorPath, Util.paramColor)
	
	if hoverIcon != null:
		if iconHovered != null:
			hoverIcon.texture = iconHovered
	
func onHoverEnd():
	.onHoverEnd()
	if hoverLabel != null:
		hoverLabel.set(hoverLabel_colorPath, hoverLabel_defaultColor)
	
	if hoverIcon != null:
		if iconHovered != null:
			hoverIcon.texture = iconNormal

func onPressed():
	.onPressed()
	if hoverIcon != null:
		if iconPressed != null:
			if pressed:
				hoverIcon.texture = iconPressed
			else:
				hoverIcon.texture = iconNormal

func enable():
	.enable()
	if hoverIcon != null:
		if iconDisabled != null:
			hoverIcon.texture = iconNormal
	
	if hoverLabel != null:
		hoverLabel.set(hoverLabel_colorPath, hoverLabel_defaultColor)
	
func disable():
	.disable()
	if hoverIcon != null:
		if iconDisabled != null:
			hoverIcon.texture = iconDisabled
	
	if hoverLabel != null:
		hoverLabel.set(hoverLabel_colorPath, disabledColor)
