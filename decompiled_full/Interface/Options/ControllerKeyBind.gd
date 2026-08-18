extends Control
class_name ControllerBindButton

export var addControllerTag: bool = true






onready var actionLabel = $Label
onready var iconButton = $Key1
onready var defaultButton = $Default




var buttonHovered = false
var actionName: String

func _enter_tree():
	$Label.translationKey = "KEYBIND_" + name

func _ready() -> void :
	actionName = name
	if addControllerTag:
		actionName += "_controller"
	
	updateButton()
	
	Game.connect("device_changed", self, "updateButton")
	




func updateButton():
	var eventList = InputMap.get_action_list(actionName)
	if eventList.empty():
		iconButton.icon = null
	else:
		var configuredInputEvent = eventList[0]
		
		iconButton.icon = ControllerIcons.parse_event(configuredInputEvent)





const hoverColor = Color(0.962891, 0.914862, 0.40401)

func onHoverIconButton():
	buttonHovered = true
	iconButton.modulate = hoverColor
	actionLabel.modulate = hoverColor
	

func onHoverIconButtonEnd():
	buttonHovered = false
	iconButton.modulate = Color.white
	actionLabel.modulate = Color.white
	
	

func onDefaultPressed():
	eraseConfiguredEvent()
	var defaultMappings = InputMapping.defaultInputMappings[actionName]
	if not defaultMappings.empty():
		InputMap.action_add_event(actionName, defaultMappings[0])
	
	updateButton()
	












func eraseConfiguredEvent():
	var actionList = InputMap.get_action_list(actionName)
	if not actionList.empty():
		var configuredInputEvent = actionList[0]
		InputMap.action_erase_event(actionName, configuredInputEvent)
		Game.eraseConfigValue("Input", actionName)




func _input(event: InputEvent) -> void :
	if (buttonHovered and 
		event is InputEventJoypadButton):


		
		
		eraseConfiguredEvent()
		
		event.device = - 1
		InputMap.action_add_event(actionName, event)
		
		updateButton()
		
		Game.setConfigValue("Input", actionName, event.button_index)
		
		
		get_tree().set_input_as_handled()
