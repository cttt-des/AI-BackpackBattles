extends Button
class_name PullButton

export var pullVector = Vector2(200, 100)
export var movebackTime = 0.5

export var moveBackAfterTrigger = true

onready var defaultPos = rect_global_position
onready var endPos = defaultPos + pullVector
onready var pullLength = pullVector.length()

var grabbed = false
var progress = 0.0
var clickOffset: Vector2

func _ready():
	connect("button_down", self, "_button_down")
	connect("button_up", self, "_button_up")

func isGrabbed():
	return grabbed

func _button_down():
	if not Game.draggedItem:
		
		grabbed = true
		clickOffset = Util.getMousePosInWindow() - rect_global_position
		set_physics_process(true)

func _button_up():
	grabbed = false

func _physics_process(delta):
	if disabled: return
	
	if grabbed:
		var projection = (Util.getMousePosInWindow() - clickOffset - defaultPos).project(pullVector)
		
		progress = projection.x / pullVector.x
	else:
		progress -= delta / movebackTime
	
	progress = clamp(progress, 0, 1)
	rect_global_position = defaultPos + progress * pullVector
	
	if grabbed and progress >= 1:
		if moveBackAfterTrigger:
			grabbed = false
		trigger()
	elif not grabbed and progress == 0:
		set_physics_process(false)
		deactivate()

func trigger():
	pass
	

func deactivate():
	pass

func onHover():
	Util.grabFocus(self)
	Game.onHoverInteractable(self)

func onHoverEnd():
	Util.releaseFocus(self)
	Game.onHoverInteractableEnd(self)
