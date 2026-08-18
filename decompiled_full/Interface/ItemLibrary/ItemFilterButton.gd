extends FocusGrabbingControl

var siblings = []

func _ready() -> void :
	for node in get_parent().get_children():
		if node != self:
			siblings.push_back(node)



func _toggled(button_pressed: bool) -> void :
	
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
	
	set("custom_colors/font_color_pressed", Util.paramColor)

func onHoverEnd():
	.onHoverEnd()
	set("custom_colors/font_color_pressed", Game.SOFTWHITE)


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
		set("custom_colors/font_color_pressed", Game.SOFTWHITE)
