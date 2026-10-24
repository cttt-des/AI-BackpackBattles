extends LocalizedControl
class_name FocusGrabbingControl

export var localized = true
export var playClickSound = true
export var releaseFocus = true
onready var me = self

func _ready() -> void :
	
	Util.tryConnect(self, "mouse_entered", self, "onHover")
	if releaseFocus:
		Util.tryConnect(self, "mouse_exited", self, "onHoverEnd")
	if has_signal("pressed") and playClickSound:
		Util.tryConnect(self, "pressed", self, "onPressed")

func updateLocale():
	if localized:
		.updateLocale()

func onHover():
	Util.grabFocus(self)
	Game.onHoverInteractable(self)

func onHoverEnd():
	Util.releaseFocus(self)
	Game.onHoverInteractableEnd(self)


func onPressed():
	Game.onClickButton()

func enable():
	self.disabled = false
	self.focus_mode = Control.FOCUS_ALL
	Util.tryConnect(self, "mouse_entered", self, "onHover")
	if releaseFocus:
		Util.tryConnect(self, "mouse_exited", self, "onHoverEnd")

func disable():
	self.disabled = true
	self.focus_mode = Control.FOCUS_NONE
	
	Util.tryDisconnect(self, "mouse_entered", self, "onHover")
	if releaseFocus:
		Util.tryDisconnect(self, "mouse_exited", self, "onHoverEnd")
