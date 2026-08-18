extends TextureButton
class_name FocusGrabbingTextureButton

signal hover_start
signal hover_end

const tooltipLabelScene = preload("res://Interface/TooltipLabel.tscn")

export var playClickSound = true
export var releaseFocus = true
export var tooltipKey: String
export var tooltipOffset: Vector2
export (NodePath) var showOnHover = null
export var showTooltipWhenDisabled: = false

var hoverReactionNode
var tooltipLabel = null
var isHovered: bool

func _ready() -> void :
	
	Game.connect("interactable_hovered", self, "onInteractableHovered")
	connect("visibility_changed", self, "onVisibilityChanged")
	connect("mouse_entered", self, "onHover")
	if releaseFocus:
		connect("mouse_exited", self, "onHoverEnd")
	if has_signal("pressed") and playClickSound:
		connect("pressed", self, "onPressed")
	
	if showOnHover != null:
		hoverReactionNode = get_node(showOnHover)
		hoverReactionNode.hide()
	
	call_deferred("ready_deferred")
	
func ready_deferred():
	if tooltipKey != "" or showOnHover != null:
		add_to_group("ButtonWithTooltip")

func onHover():
	if not Game.itemListOpened:
		if not disabled or showTooltipWhenDisabled:
			isHovered = true
			Util.grabFocus(self)
			Game.onHoverInteractable(self)
			
			if tooltipKey != "":
				tooltipLabel = ObjectPool.instance(tooltipLabelScene)
				Game.tooltipsNode.add_child(tooltipLabel)
				tooltipLabel.init(tooltipKey, self, tooltipOffset)
			
			if hoverReactionNode != null:
				hoverReactionNode.show()
			
			emit_signal("hover_start")

func onHoverEnd():
	if isHovered:
		isHovered = false
		Util.releaseFocus(self)
		Game.onHoverInteractableEnd(self)
		hideHoverNodeAndTooltip()
		emit_signal("hover_end")
		
	

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

func hideHoverNodeAndTooltip():
	if tooltipLabel != null:
		tooltipLabel.returnToObjectPool()
		tooltipLabel = null
	
	if hoverReactionNode != null and is_instance_valid(hoverReactionNode):
		hoverReactionNode.hide()

func _notification(what):
	if what == NOTIFICATION_PREDELETE:
		hideHoverNodeAndTooltip()

func onInteractableHovered():
	if Game.hoveredInteractable != self:
		if isHovered:
			onHoverEnd()

func onVisibilityChanged():
	if not is_visible_in_tree():
		if isHovered:
			onHoverEnd()
