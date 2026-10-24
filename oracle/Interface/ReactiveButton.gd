extends BaseButton

func _ready() -> void :
	connect("mouse_entered", self, "onHover")
	connect("mouse_exited", self, "onHoverEnd")
	connect("pressed", self, "onClicked")

func onHover():
	modulate = Color(1.3, 1.3, 1.3, 1)
	Game.onHoverInteractableEnd(self)
	Util.grabFocus(self)
	
func onHoverEnd():
	modulate = Color.white
	Game.onHoverInteractable(self)
	Util.releaseFocus(self)

func onClicked():
	modulate = Color.white
	Game.onClickButton()
