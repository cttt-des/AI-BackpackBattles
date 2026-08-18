extends Line2D

var tween
export var length = 30
export var active = false
onready var trailPosition = get_parent()

func _ready():
	set_as_toplevel(true)
	scale = Vector2(1, 1)
	clear_points()
	modulate = Color.transparent
	tween = Tween.new()
	add_child(tween)
	
	if active:
		activate()
	

func _physics_process(delta):
	if active:
		add_point(trailPosition.global_position)
	
		if points.size() > length:
			remove_point(0)
		

func activate():
	clear_points()
	active = true
	modulate = Color.white
	tween.remove_all()
	tween.stop_all()

func stop(free: bool = false):
	active = false
	tween.remove_all()
	tween.stop_all()
	tween.interpolate_property(self, "modulate", null, Color.transparent, 0.5)
	if free:
		tween.interpolate_callback(self, 0.5, "queue_free")
	tween.start()
