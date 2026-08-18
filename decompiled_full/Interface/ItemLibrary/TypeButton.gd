extends FocusGrabbingTextureButton

var siblings = []

onready var outline = $Pressed

func _ready() -> void :
	call_deferred("ready_deferred")

func ready_deferred():
	for node in get_parent().get_children():
		if node != self and "pressed" in node and node.visible:
			siblings.push_back(node)
	
	tooltipKey = "TYPE_" + name + "_NAME"
	tooltipOffset = Vector2(0, - 25)





func _toggled(button_pressed: bool) -> void :
	
	Game.onClickButton()
	outline.visible = button_pressed
	if Game.itemLibrary:
		Game.itemLibrary.filterChanged()

func _gui_input(event):
	if (event is InputEventMouseButton and 
		event.button_index == BUTTON_RIGHT and 
		not event.pressed):
		
		toggleGroup()

func isOn() -> bool:
	return self.pressed

func onHover():
	.onHover()
	modulate = Color(1.3, 1.3, 1.3, 1)

func onHoverEnd():
	.onHoverEnd()
	modulate = Color.white

func toggleGroup():
	var invertMode = self.pressed
	
	
	if self.pressed:
		for sibling in siblings:
			if sibling.pressed:
				invertMode = false
				break
	if invertMode:
		self.pressed = false
		for sibling in siblings:
			sibling.pressed = true
	else:
		self.pressed = true
		for sibling in siblings:
			sibling.pressed = false
		
func _notification(what):
	if what == NOTIFICATION_EXIT_TREE:
		modulate = Color.white
	elif what == NOTIFICATION_VISIBILITY_CHANGED:
		if isHovered and not is_visible_in_tree():
			onHoverEnd()
