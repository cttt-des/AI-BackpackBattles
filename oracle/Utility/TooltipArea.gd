extends Control

export (String) var keyword
export (Array, NodePath) var highlightingNodes
export (PackedScene) var tooltipScene = preload("res://Interface/Tooltips/SimpleTooltip.tscn")

var tooltip
var params = {}
var nameParams = {}
var highlightedNodes = []

func _ready() -> void :
	tooltip = tooltipScene.instance()
	Game.tooltipsNode.add_child(tooltip)
	Game.connect("switch_to_shop", self, "hideTooltip")
	Game.connect("return_to_title", self, "hideTooltip")
	connect("mouse_entered", self, "onHover")
	connect("mouse_exited", self, "onHoverEnd")
	for nodePath in highlightingNodes:
		highlightedNodes.push_back(get_node(nodePath))

func onHover():
	Game.onHoverInteractable(self)
	
	var headerText = Util.tra(keyword + "_NAME").format(nameParams)
	var descrText = Util.tra(keyword + "_DESCR").format(params)
	
	tooltip.setParams(headerText, descrText)
	
	tooltip.forceUpdatePosition(rect_global_position, rect_size + Vector2(30, 0))
	for highlightedNode in highlightedNodes:
		highlightedNode.modulate = Color(1.3, 1.3, 1.3, 1)
	
func onHoverEnd():
	Game.onHoverInteractableEnd(self)
	hideTooltip()
	for highlightedNode in highlightedNodes:
		if is_instance_valid(highlightedNode):
			highlightedNode.modulate = Color.white

func hideTooltip():
	tooltip.hide()

func _notification(what):
	if what == NOTIFICATION_PREDELETE:
		if is_instance_valid(tooltip):
			onHoverEnd()
			tooltip.discard()
	elif what == NOTIFICATION_VISIBILITY_CHANGED:
		if not is_visible_in_tree() and is_instance_valid(tooltip):
			onHoverEnd()
