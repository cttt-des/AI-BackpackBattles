extends FocusGrabbingControl

export var isPressed: = false

func _ready():
	connect("button_up", self, "onButtonUp")
	
func onButtonUp():
	
	if not Game.combatLog.movedDuringDrag:
		toggle()

func toggle():
	isPressed = not isPressed
	emit_signal("toggled", isPressed)
