extends RichTextLabel

export var margin = 2

const SCROLL_SPEED = 10.0

var scrollbarHovered = false
onready var scrollBar = get_v_scroll()

	
func _ready():
	scrollBar.connect("mouse_entered", self, "onScrollbarHover")
	scrollBar.connect("mouse_exited", self, "onScrollbarHoverEnd")

func onScrollbarHover():
	scrollbarHovered = true
	Util.grabFocus(scrollBar)
	set_process(true)

func onScrollbarHoverEnd():
	scrollbarHovered = false
	Util.releaseFocus(scrollBar)
	set_process(false)

func _process(delta):
	if Util.isActionPressed("ui_accept", false):
		var leftBorder = scrollBar.rect_global_position.y + margin
		var size = (scrollBar.rect_size.y * scrollBar.rect_scale.y) - 2 * margin
		var valueRange = scrollBar.max_value - scrollBar.min_value
		var relPos = (get_global_mouse_position().y - leftBorder) / size
		scrollBar.value = scrollBar.min_value + (valueRange * relPos)

func _physics_process(delta):
	if is_visible_in_tree():
		var scroll = Input.get_axis("shift_up_controller", "shift_down_controller")
		scrollBar.value += scroll * SCROLL_SPEED
