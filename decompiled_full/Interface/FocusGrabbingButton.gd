extends Button
class_name FocusGrabbingButton

export var playClickSound = true
export var releaseFocus = true
export (NodePath) var showOnHover = null
var hoverReactionNode
var isHovered: bool

func _ready() -> void :
	
	Util.tryConnect(self, "mouse_entered", self, "onHover")
	if releaseFocus:
		Util.tryConnect(self, "mouse_exited", self, "onHoverEnd")
	if has_signal("pressed") and playClickSound:
		Util.tryConnect(self, "pressed", self, "onPressed")
	
	if showOnHover != null:
		hoverReactionNode = get_node(showOnHover)
		hoverReactionNode.hide()

func onHover():
	if not Game.itemListOpened:
		isHovered = true
		Util.grabFocus(self)
		Game.onHoverInteractable(self)
		if hoverReactionNode != null:
			hoverReactionNode.show()

func onHoverEnd():
	if isHovered:
		isHovered = false
		Util.releaseFocus(self)
		Game.onHoverInteractableEnd(self)
		if hoverReactionNode != null:
			hoverReactionNode.hide()

func onPressed():
	Game.onClickButton()

func enable():
	self.disabled = false
	self.focus_mode = Control.FOCUS_ALL
	Util.tryConnect(self, "mouse_entered", self, "onHover")
	if releaseFocus:
		Util.tryConnect(self, "mouse_exited", self, "onHoverEnd")

func disable():
	self.disabled = true
	self.focus_mode = Control.FOCUS_NONE
	
	Util.tryDisconnect(self, "mouse_entered", self, "onHover")
	if releaseFocus:
		Util.tryDisconnect(self, "mouse_exited", self, "onHoverEnd")

func _notification(what):
	if what == NOTIFICATION_VISIBILITY_CHANGED:
		if isHovered and not is_visible_in_tree():
			onHoverEnd()
