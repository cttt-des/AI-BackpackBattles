extends RichTextLabel
class_name CombatLogLine

var poolingHandle
var event: CombatEvent
var player: bool
var minimized: bool
var state: int
var cachedText: String

enum State{
	Normal, 
	Hovered, 
	Connected, 
	Tooltip
}


func preset():
	add_to_group("Localized")
	Util.localizeFonts(self)

func _ready() -> void :
	Util.localizeFonts(self)
	

func updateLocale():
	cachedText = event.asText()
	
	if not minimized:
		bbcode_text = cachedText

func getText() -> String:
	return cachedText

func setEvent(_event):
	event = _event
	player = event.getMainActor() == Character.ID.PLAYER
	
	setStylebox(State.Normal)
	updateLocale()

func setMinimized(_minimized):
	if minimized == _minimized: return
	
	minimized = _minimized
	
	if minimized:
		bbcode_text = ""
		fit_content_height = false
		rect_min_size.y = 5
		rect_size.y = 5
		
	else:
		bbcode_text = cachedText
		fit_content_height = true

func getItem():
	var origin = event.getOrigin()
	if origin and origin is Item:
		return origin
	return null

func getSource():
	var origin = event.getOrigin()
	if origin and typeof(origin) == TYPE_INT:
		return origin
	return null

func getType():
	return event.type

func onHovered():
	if Game.fightEnded and state != State.Tooltip:
		Game.combatLog.onLineHovered(self)
		setStylebox(State.Hovered)

func onConnectedHovered():
	setStylebox(State.Connected)

func onHoverEnd():
	setStylebox(State.Normal)
	if getItem() or getSource():
		Game.combatLog.unhighlightItem()

func onConnectedHoverEnd():
	setStylebox(State.Normal)
	Game.combatLog.onLineHoverEnd()

func setStylebox(_state: int):
	
	state = _state
	if not player:
		set("custom_colors/default_color", Color.white)
	else:
		set("custom_colors/default_color", Game.BROWN)
	
	var faded = false
	if state != State.Tooltip:
		if event.type == Game.EventType.Activation:
			faded = true
	
	set("custom_styles/normal", Game.combatLog.getStylebox(player, state, faded))





