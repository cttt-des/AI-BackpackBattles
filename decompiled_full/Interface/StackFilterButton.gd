extends FocusGrabbingTextureButton

var siblings = []

func _ready() -> void :
	for node in get_parent().get_children():
		if node != self:
			siblings.push_back(node)
	
	if name in Game.Classes_Full or name == "Neutral":
		tooltipKey = name + "_NAME"
		tooltipOffset = Vector2(0, - 5)
		
	else:
		tooltipKey = Game.typeToKeyword(Game.EventType[name]) + "_NAME"
		tooltipOffset = Vector2(0, - 20)





func _toggled(button_pressed: bool) -> void :
	
	Game.onClickButton()
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
	if isHovered:
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
