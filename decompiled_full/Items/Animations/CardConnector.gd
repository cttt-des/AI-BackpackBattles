extends Sprite

onready var animation = $AnimationPlayer
onready var card = get_parent()
onready var localPosition = position
	
var active = false
var visuallyActive = false

func _ready() -> void :
	modulate.g = Util.rng.randf_range(0.9, 1.1)
	set_as_toplevel(true)

func checkState():
	if visuallyActive and not active:
		animation.play("Disappear")
	elif not visuallyActive and active:
		animation.play("Appear")
	
	visuallyActive = active
	
func appear():
	active = true

func _physics_process(delta: float) -> void :
	global_position = card.global_position + localPosition.rotated(card.rotation)
	rotation = card.rotation
	z_index = Util.getGlobalZ(card) - 1

func disappear():
	active = false
