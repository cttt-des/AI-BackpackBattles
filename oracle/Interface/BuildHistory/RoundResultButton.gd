extends FocusGrabbingTextureButton
class_name HistoryRoundButton

var normalTextures = {
	Game.RoundResult.Win: preload("res://Interface/BuildHistory/RoundResultTriangle.png"), 
	Game.RoundResult.Loss: preload("res://Interface/BuildHistory/RoundResultTriangle_Loss.png"), 
	Game.RoundResult.RunOver: null
}

enum Validity{
	None, 
	Ok, 
	Questionable, 
	Invalid, 
	TooManyUniques
}

const BORDER_OUTSET = 2
const BORDER_INSET_X = 1.5

var currentValidity = Validity.None
var borderRect: ColorRect = null

func _ready():
	if borderRect == null:
		borderRect = ColorRect.new()
		borderRect.mouse_filter = Control.MOUSE_FILTER_IGNORE
		add_child(borderRect)
		borderRect.show_behind_parent = true

		borderRect.anchor_left = 0
		borderRect.anchor_top = 0
		borderRect.anchor_right = 1
		borderRect.anchor_bottom = 1
		borderRect.margin_left = BORDER_INSET_X
		borderRect.margin_right = - BORDER_INSET_X
		borderRect.margin_top = - BORDER_OUTSET
		borderRect.margin_bottom = BORDER_OUTSET
		borderRect.color = Color.transparent


func setResult(res: int, validity = Validity.None):
	match res:
		Game.RoundResult.Win:
			show()


		Game.RoundResult.Loss:
			show()
			
			
		Game.RoundResult.RunOver:
			hide()
		
	texture_normal = normalTextures[res]
	setValidity(validity)

func setValidity(validity: int):
	currentValidity = validity

	if borderRect == null:
		return

	match validity:
		Validity.None:
			borderRect.color = Color.transparent
		Validity.Ok:
			borderRect.color = Color(0.3, 0.92, 0.38, 1.0)
		Validity.Questionable:
			borderRect.color = Color(1.0, 1.0, 0.0, 1.0)
		Validity.Invalid:
			borderRect.color = Color(0.98, 0.34, 0.34, 1.0)
		Validity.TooManyUniques:
			borderRect.color = Color(1.0, 0.65, 0.22, 1.0)
		_:
			borderRect.color = Color.transparent

func onHover():
	.onHover()
	self_modulate = Color(1.2, 1.2, 1.2)

	if borderRect != null and currentValidity != Validity.None:
		match currentValidity:
			Validity.Ok:
				borderRect.color = Color(0.45, 1.0, 0.52, 1.0)
			Validity.Questionable:
				borderRect.color = Color(1.0, 1.0, 0.4, 1.0)
			Validity.Invalid:
				borderRect.color = Color(1.0, 0.46, 0.46, 1.0)
			Validity.TooManyUniques:
				borderRect.color = Color(1.0, 0.76, 0.35, 1.0)

func onHoverEnd():
	.onHoverEnd()
	self_modulate = Color.white
	setValidity(currentValidity)
