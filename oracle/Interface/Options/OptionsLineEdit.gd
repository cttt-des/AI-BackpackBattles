extends LineEdit

export var translationKey = ""

onready var label = $Label
onready var applyTimer = $ApplyTimer

func _ready():
	label.translationKey = translationKey
	connect("mouse_entered", self, "onHover")
	connect("mouse_exited", self, "onHoverEnd")
	connect("text_changed", self, "onTextChanged")
	call_deferred("updateText")

func updateText():
	text = String(Settings.getValStr(name))

func onTextChanged(newText) -> void :
	applyTimer.stop()
	applyTimer.start(1)

func applySetting():
	Settings.setValStr(name, int(text))
	updateText()

func onHover():
	Game.onHoverInteractable(self)

func onHoverEnd():
	Game.onHoverInteractableEnd(self)
