extends ScrollContainer

signal zoomed

const SCROLL_SPEED = 10.0

export var margin = 2
export var detectZoom: = false
export var scrollEnabled: = true

var scrollbarHovered: = false

onready var scrollBar = get_v_scrollbar()

func _ready():
	scrollBar.connect("mouse_entered", self, "onScrollbarHover")
	scrollBar.connect("mouse_exited", self, "onScrollbarHoverEnd")
	set_process(false)
	set_process_input(false)
	
	
	

func onScrollbarHover():
	scrollbarHovered = true
	
	set_process(true)

func onScrollbarHoverEnd():
	scrollbarHovered = false
	
	set_process(false)

func _process(delta):
	if Util.isActionPressed("ui_accept", false):
		var leftBorder = scrollBar.rect_global_position.y + margin
		var size = (scrollBar.rect_size.y * scrollBar.rect_scale.y) - 2 * margin
		var valueRange = scrollBar.max_value - scrollBar.min_value
		var relPos = (get_global_mouse_position().y - leftBorder) / size
		scrollBar.value = scrollBar.min_value + (valueRange * relPos)

func onOpen():
	set_physics_process(true)
	if detectZoom:
		set_process_input(true)

func onClose():
	set_physics_process(false)
	set_process_input(false)

func _input(event):
	if event is InputEventMouseButton and event.pressed and event.control:
		if event.button_index == BUTTON_WHEEL_UP:
			emit_signal("zoomed", - 1)
		elif event.button_index == BUTTON_WHEEL_DOWN:
			emit_signal("zoomed", 1)
	
func _physics_process(delta):
	if is_visible_in_tree() and scrollEnabled:
		var scroll = Input.get_axis("shift_up_controller", "shift_down_controller")
		scrollBar.value += scroll * SCROLL_SPEED
