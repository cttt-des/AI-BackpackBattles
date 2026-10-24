extends Control
class_name ResizableControl

signal drag_start
signal drag_end

onready var vResizeButton: Button = get_node_or_null("VerticalResizeButton")
onready var hResizeButton: Button = get_node_or_null("HorizontalResizeButton")
export var draggable = false
								

var dragPosition = null
var verticalResizing: = false
var horizontalResizing: = false
var resizeOffset = null
var dragging: = false
var movedDuringDrag: = false
var globalDragStartPosition: Vector2

func _ready() -> void :
	set_process(false)
	set_process_input(false)
	
	if vResizeButton:
		vResizeButton.connect("button_down", self, "onVerticalResizeButtonDown")
		
	if hResizeButton:
		hResizeButton.connect("button_down", self, "onHorizontalResizeButtonDown")
		

func _notification(what):
	if what == NOTIFICATION_VISIBILITY_CHANGED:
		set_process_input(visible)


func _process(delta):
	if verticalResizing:
		var globalEndPos = Util.clampToScreen(get_global_mouse_position() + resizeOffset)
		rect_size.y = globalEndPos.y - rect_global_position.y
			
	elif horizontalResizing:
		var globalEndPos = Util.clampToScreen(get_global_mouse_position() + resizeOffset)
		rect_size = globalEndPos - rect_global_position
	
	elif dragPosition != null:
		var topLeftPoint = get_global_mouse_position() - dragPosition
		rect_global_position = Util.clampToScreen(topLeftPoint)
		rect_global_position = Util.clampToScreen(rect_global_position + rect_size) - rect_size
		if rect_global_position.distance_to(globalDragStartPosition) > 10:
			movedDuringDrag = true
			
		
func startDragging():
	
	movedDuringDrag = false
	globalDragStartPosition = rect_global_position
	dragPosition = get_global_mouse_position() - rect_global_position
	set_process(true)


func endDragging():
	dragPosition = null
	set_process(false)

func canDrag():
	return true

func _input(event: InputEvent) -> void :
	if (is_visible_in_tree() and 
		not verticalResizing and 
		not horizontalResizing and 
		(Input.get_current_cursor_shape() == CURSOR_ARROW or 
			Input.get_current_cursor_shape() == CURSOR_POINTING_HAND)):
		
		if (Util.isAction_event(event, "grab_item") or event is InputEventScreenTouch):
			if event.is_pressed():
				var clickPos = get_global_mouse_position()
				var rect = get_global_rect()
				if rect.has_point(clickPos):
					if canDrag():
						dragging = true
						if draggable:
							startDragging()
						emit_signal("drag_start")
	
	if ((Util.isAction_event(event, "grab_item") or event is InputEventScreenTouch)
		and not event.is_pressed()):
		verticalResizing = false
		horizontalResizing = false
		set_process(false)
		if dragging:
			dragging = false
			if draggable:
				endDragging()
			emit_signal("drag_end")

func onVerticalResizeButtonDown():
	if dragging: return
	verticalResizing = true
	resizeOffset = (rect_global_position + rect_size) - (get_global_mouse_position())
	set_process(true)
	
func onVerticalResizeButtonUp():
	if not verticalResizing: return
	verticalResizing = false
	set_process(false)

func onHorizontalResizeButtonDown() -> void :
	if dragging: return
	horizontalResizing = true
	resizeOffset = (rect_global_position + rect_size) - (get_global_mouse_position())
	set_process(true)

func onHorizontalResizeButtonUp() -> void :
	if not horizontalResizing: return
	horizontalResizing = false
	set_process(false)

