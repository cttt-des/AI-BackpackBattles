extends FocusGrabbingTextureButton

const tooltipScene = preload("res://Interface/Tooltips/CustomRulesTooltip.tscn")

export var lobbyMode = false

var tooltip = null
var customRules = CustomRules

func onHover():
	.onHover()
	if isHovered:
		tooltip = tooltipScene.instance()
		Game.tooltipsNode.add_child(tooltip)
		tooltip.setRules(customRules, lobbyMode)
		tooltip.forceUpdatePosition(rect_global_position, rect_size)

func onHoverEnd():
	.onHoverEnd()
	if tooltip != null:
		tooltip.queue_free()
		tooltip = null
	
func onCustomRulesChanged():
	if tooltip != null:
		tooltip.updateRules(customRules)
		tooltip.forceUpdatePosition(rect_global_position, rect_size)
