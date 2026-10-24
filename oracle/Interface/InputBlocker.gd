extends Node2D

signal inputs_blocked

onready var rect = $Rect

enum Source{
	Inactive = 0, 
	SceneSwitch = 1, 
	Popup = 2, 
	Fusing = 4, 
	Lobby = 8, 
	CombatUI = 16, 
	PopupAnimation = 32, 
	Scoreboard = 64, 
	BoxSelect = 128, 
	ItemDragging = 256, 
	LockedTooltip = 512
}

var curSources = Source.Inactive
var mouseFilters: Dictionary
var disableSources: Dictionary

func activate(source, disableTreeControls = true):
	
	if curSources == Source.Inactive:
		rect.show()
		emit_signal("inputs_blocked")
		
	curSources |= source
	if disableTreeControls:
		disableAllControls(source, Game.mainNode)

func deactivate(source, restoreTreeControls = true):
	curSources &= ~ source
	
	if curSources == Source.Inactive:
		rect.hide()
		
		
	if restoreTreeControls:
		restoreAllControls(source)

func isActive():
	return rect.visible

func isOnlySourceActive(source: int) -> bool:
	return curSources == source



func disableAllControls(source, rootNode):
	if rootNode.visible:
		rootNode.visible = false
		rootNode.visible = true
	disableAllControls_traverse(source, rootNode)
	
func disableAllControls_traverse(source, rootNode):
	for child in rootNode.get_children():
		if child is Control:
			disableControl(source, child)
		disableAllControls_traverse(source, child)

func disableControl(source: int, control: Control):
	if control in mouseFilters:
		disableSources[control] |= source





		
	else:
		if control.mouse_filter != Control.MOUSE_FILTER_IGNORE:
			mouseFilters[control] = control.mouse_filter
			disableSources[control] = source
			control.mouse_filter = Control.MOUSE_FILTER_IGNORE


func disableSingleControl(source: int, control: Control):
	if control.visible:
		control.visible = false
		control.visible = true
	disableControl(source, control)

func restoreAllControls(source: int):
	var mouseFilters_new: = {}
	var disableSources_new: = {}
	
	for control in disableSources:
		if is_instance_valid(control):
			var newValue = disableSources[control] & ~ source
			if newValue == Source.Inactive:
				
				
				control.mouse_filter = mouseFilters[control]
			else:
				mouseFilters_new[control] = mouseFilters[control]
				disableSources_new[control] = newValue
	
	disableSources = disableSources_new
	mouseFilters = mouseFilters_new

func restoreControl(source, control: Control):
	if control in disableSources and is_instance_valid(control):
		disableSources[control] &= ~ source
		if disableSources[control] == Source.Inactive:
			
			
			control.mouse_filter = mouseFilters[control]
			disableSources.erase(control)
			mouseFilters.erase(control)


func enableControls(source, rootNode):
	for child in rootNode.get_children():
		if child is Control:
			restoreControl(source, child)
		enableControls(source, child)

func onMouseFilterChanged(control, newMouseFilter):
	if control in mouseFilters:
		mouseFilters[control] = newMouseFilter

func setMouseFilter(control, newMouseFilter):
	control.mouse_filter = newMouseFilter
	onMouseFilterChanged(control, newMouseFilter)
