extends Control
class_name KeyBindButton

export var mouseAllowed = true
export var mouseWheelAllowed = false

onready var key1 = $Key1
onready var key2 = $Key2
onready var defaultButton = $Default
onready var actionLabel = $Label

var waitingForKey = 0

var key1Hovered = false
var key2Hovered = false

const NO_KEY = ""
const WAITING_FOR_INPUT = "..."



func _enter_tree():
	$Label.translationKey = "KEYBIND_" + name

func _ready() -> void :
	defaultButton.hide()
	updateKey()
	add_to_group("Localized")

func updateLocale():
	updateKey()


func updateKey():
	var configuredInputEvents = getMouseKeyboardActions()
	
	if configuredInputEvents.size() > 0:
		var inputEvent1 = configuredInputEvents[0]
		var key1Text = Util.getTextForEvent(inputEvent1, false)
		if key1Text.begins_with("KEY_") or key1Text.begins_with("MOUSE"):
			key1.setTranslationKey(key1Text)
		else:
			key1.text = key1Text
		
		if ((inputEvent1 is InputEventMouseButton and 
			(inputEvent1.button_index == BUTTON_LEFT or 
			inputEvent1.button_index == BUTTON_RIGHT)) or 
			inputEvent1.control):
			key1.disabled = true
	else:
		key1.text = NO_KEY

	
	if configuredInputEvents.size() > 1:
		var inputEvent2 = configuredInputEvents[1]
		var key2Text = Util.getTextForEvent(inputEvent2, false)
		if key2Text.begins_with("KEY_") or key2Text.begins_with("MOUSE"):
			key2.setTranslationKey(key2Text)
		else:
			key2.text = key2Text
	else:
		key2.text = NO_KEY
	


func getMouseKeyboardActions():
	var events = []
	for event in InputMap.get_action_list(name):
		if event is InputEventKey or event is InputEventMouseButton:
			events.push_back(event)
	return events


func key1Pressed():
	updateKey()
	if waitingForKey == 1:
		waitingForKey = 0
	else:
		
		waitingForKey = 1
		key1.text = WAITING_FOR_INPUT


func key2Pressed():
	updateKey()
	if waitingForKey == 2:
		waitingForKey = 0
	else:
		waitingForKey = 2
		key2.text = WAITING_FOR_INPUT

func onHoverKey1():
	key1Hovered = true

func onHoverKey2():
	key2Hovered = true

func onHoverKey1End():
	key1Hovered = false

func onHoverKey2End():
	key2Hovered = false








func isSameAsOther(index, event) -> bool:
	var configuredInputEvents = getMouseKeyboardActions()
	var otherEvent = null
	if index == 1 and configuredInputEvents.size() > 1:
		otherEvent = configuredInputEvents[1]
	elif index == 2 and configuredInputEvents.size() > 0:
		otherEvent = configuredInputEvents[0]
	
	if otherEvent:
		if event is InputEventKey and otherEvent is InputEventKey:
			return otherEvent.scancode == event.scancode
		elif event is InputEventMouseButton and otherEvent is InputEventMouseButton:
			return otherEvent.button_index == event.button_index
	
	return false

const allowedMouseButtons = {
	BUTTON_MIDDLE: true, 
	BUTTON_XBUTTON1: true, 
	BUTTON_XBUTTON2: true
}

func isMouseButtonOK(event: InputEventMouseButton):
	return event.button_index in allowedMouseButtons

func isMouseWheel(event: InputEventMouseButton):
	return (event.button_index == BUTTON_WHEEL_DOWN or 
			event.button_index == BUTTON_WHEEL_UP or 
			event.button_index == BUTTON_WHEEL_LEFT or 
			event.button_index == BUTTON_WHEEL_RIGHT)

func setKey(event: InputEvent, eventCode: String):
	var configuredInputEvents = getMouseKeyboardActions()
		
	var configKey
	if waitingForKey == 1:
		if configuredInputEvents.size() > 0:
			configuredInputEvents[0] = event
		else:
			configuredInputEvents.push_back(event)
		configKey = name + "_1"
	else:
		if isSameAsOther(2, event):
			key2.translationKey = NO_KEY
			key2.updateText()
			return
		
		if configuredInputEvents.size() > 1:
			configuredInputEvents[1] = event
		else:
			configuredInputEvents.push_back(event)
		configKey = name + "_2"
	
	eraseMouseKeyboardEvents()
	for _event in configuredInputEvents:
		InputMap.action_add_event(name, _event)
	
	Game.setConfigValue("Input", configKey, eventCode)
	cancelInput()
	
func _input(event: InputEvent) -> void :
	if waitingForKey != 0 and event.is_pressed():
		
		if event is InputEventKey:
			setKey(event, OS.get_scancode_string(event.scancode))
			
		elif event is InputEventMouseButton:
			if mouseAllowed and isMouseButtonOK(event):
				setKey(event, Util.mouseButtons[event.button_index])
				call_deferred("cancelInput")
			else:
				if waitingForKey == 1 and not key1Hovered:
					cancelInput()
				elif waitingForKey == 2 and not key2Hovered:
					cancelInput()

func eraseMouseKeyboardEvents():
	for event in InputMap.get_action_list(name):
		if event is InputEventKey or event is InputEventMouseButton:
			InputMap.action_erase_event(name, event)

func defaultPressed():
	
	eraseMouseKeyboardEvents()
	for event in InputMapping.defaultInputMappings[name]:
		InputMap.action_add_event(name, event)
	
	Game.eraseConfigValue("Input", name + "_1")
	Game.eraseConfigValue("Input", name + "_2")
	
	cancelInput()

func cancelInput():
	waitingForKey = 0
	updateKey()


func onHover():
	defaultButton.show()

func onHoverEnd():
	defaultButton.hide()
