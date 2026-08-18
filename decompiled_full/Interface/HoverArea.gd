extends Control

export (NodePath) var tooltipPath
onready var tooltip = get_node(tooltipPath)

func onHover():
	Game.onHoverInteractable(self)
	tooltip.show()

func onHoverEnd():
	Game.onHoverInteractableEnd(self)
	hideTooltip()

func hideTooltip():
	tooltip.hide()
