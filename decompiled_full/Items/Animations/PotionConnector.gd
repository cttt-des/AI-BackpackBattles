extends Sprite

onready var animation = $AnimationPlayer
onready var potion = get_parent()

onready var startScale = scale
	
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

func _physics_process(_delta: float) -> void :
	if potion.placed:
		var affected = potion.getAffectedItems()
		if not affected.empty():
			var affectedPoint = potion.getStarPosition()
			global_position = affectedPoint
			position.y += 40 * potion.global_scale.x
			global_rotation = 0
			global_scale = startScale * potion.global_scale
	
	z_index = Util.getGlobalZ(potion)

func disappear():
	active = false


func reset():
	animation.stop()
	hide()
	active = false
	visuallyActive = false
