extends PullButton

const arrow = preload("res://Interface/ArrowButton2.png")
const arrow_hovered = preload("res://Interface/ArrowButton2_hovered.png")
const windParticles = preload("res://Interface/WindParticles.tscn")
const windSound = preload("res://Assets/Sound/Swoosh1.wav")

onready var hint = get_parent().get_node("PushToStorageHint")
var particleReadyTime = 0.0

var pullTween: SceneTreeTween

func _ready():
	connect("mouse_entered", self, "onHover")
	connect("mouse_exited", self, "onHoverEnd")

func _unhandled_input(event):
	if InputBlocker.isActive(): return
	
	if (Game.draggedItem == null and 
		Game.isShopActive() and 
		Util.isActionPressed_event(event, "push_all_to_storage")):
		
		Game.cancelSwitch()
		trigger()
		disabled = true
		grabbed = false
		Util.killTween(pullTween)
		pullTween = create_tween()
		pullTween.tween_property(self, "rect_global_position", endPos, 0.1)
		pullTween.tween_callback(self, "tweenFinished")

func _button_down():
	if not Game.draggedItem:
		Game.cancelSwitch()
	._button_down()

func tweenFinished():
	setDisabled(false)
	progress = 1
	set_physics_process(true)

func setDisabled(_disabled):
	disabled = _disabled

func onHover():
	if not Game.draggedItem:
		.onHover()
		hint.show()
		self.icon = arrow_hovered

func onHoverEnd():
	.onHoverEnd()
	hint.hide()
	self.icon = arrow

func trigger():
	onHoverEnd()
	if not Game.draggedItem:
		Game.cancelSwitch()
		Game.STORAGEBOX.pushAllToStorage()
		Sound.playSound(windSound)
		if Util.time >= particleReadyTime:
			ObjectPool.particleOneShot(windParticles, get_parent())
			particleReadyTime = Util.time + 0.2
