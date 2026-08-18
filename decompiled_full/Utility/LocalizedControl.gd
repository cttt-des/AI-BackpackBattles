extends Control
class_name LocalizedControl

export var translationKey = ""
export var prefix = ""
export (String, MULTILINE) var suffix = ""
export var capslock = false
export var autoMaxSize: = false
export var maxSize = 0.0
export var maxSizeY = 0.0
export var removeBreaks = false
export var shrinkLimit = 4

var poolingHandle

var fonts = Dictionary()
var shrink: bool

var refPos: Vector2

var formatParams = null

func preset():
	pass

func setMaxSize(_maxSize):
	maxSize = _maxSize

func _init():
	set_message_translation(false)

func _ready() -> void :
	Util.localizeFonts(self)
	
	
	if (autoMaxSize or 
		("autowrap" in self and not get("autowrap"))
		or maxSize != 0):
		shrink = true
		if maxSize == 0:
			maxSize = rect_size.x
		if maxSizeY == 0:
			maxSizeY = rect_size.y
			
		var icon = get("custom_icons/checked")
		if icon:
			var iconSize = icon.get_size()
			
			maxSize -= iconSize.x
	else:
		shrink = false
	
	if autoMaxSize:
		rect_min_size = rect_size
	
	if grow_horizontal == GROW_DIRECTION_BEGIN:
		refPos.x = rect_position.x + rect_size.x
	elif grow_horizontal == GROW_DIRECTION_END:
		refPos.x = rect_position.x
	else:
		refPos.x = rect_position.x + rect_size.x * 0.5
	
	if grow_vertical == GROW_DIRECTION_BEGIN:
		refPos.y = rect_position.y + rect_size.y
	elif grow_vertical == GROW_DIRECTION_END:
		refPos.y = rect_position.y
	else:
		refPos.y = rect_position.y + rect_size.y * 0.5
	







	
	add_to_group("Localized")
	call_deferred("updateLocale")

func collectFonts():
	if "bbcode_text" in self and get("bbcode_enabled"):
		for path in ["custom_fonts/normal_font", "custom_fonts/bold_font"]:
			fonts[path] = get(path)
	elif "text" in self:
		fonts["custom_fonts/font"] = get("custom_fonts/font")

func updateLocale():
	collectFonts()
	updateText()

func setTranslationKey(_translationKey: String):
	translationKey = _translationKey
	updateText()

func updateText():
	if translationKey == "": return
	
	if "bbcode_text" in self and get("bbcode_enabled"):
		var newText = Util.tra(translationKey)
		
		if removeBreaks:
			newText = newText.replace("\n", "")
		if capslock:
			newText = newText.to_upper()
		
		if formatParams != null:
			newText = newText.format(formatParams)
		
		set("bbcode_text", prefix + newText + suffix)
		
		if shrink:
			shrinkIfTooBig(get("text"))
	
	elif "text" in self:
		
		var newText = Util.tra(translationKey)
		
		if removeBreaks:
			newText = newText.replace("\n", "")
		if capslock:
			newText = newText.to_upper()
		
		if formatParams != null:
			newText = newText.format(formatParams)
		
		var fullText = prefix + newText + suffix
		set("text", fullText)
		
		if shrink:
			shrinkIfTooBig(fullText)
		
		
		if grow_horizontal == GROW_DIRECTION_BEGIN:
			rect_position.x = refPos.x - rect_size.x
		elif grow_horizontal == GROW_DIRECTION_END:
			rect_position.x = refPos.x
		else:
			rect_position.x = refPos.x - rect_size.x * 0.5
		
		
		if grow_vertical == GROW_DIRECTION_BEGIN:
			rect_position.y = refPos.y - rect_size.y
		elif grow_vertical == GROW_DIRECTION_END:
			rect_position.y = refPos.y
		else:
			rect_position.y = refPos.y - rect_size.y * 0.5


func isAutoWrapping() -> bool:
	return ("autowrap" in self and get("autowrap")) or "bbcode_text" in self

func returnToObjectPool():
	
	for path in fonts:
		var font = fonts[path]
		if font == null: continue
		set(path, font)
	ObjectPool.returnInstance(self)

func shrinkIfTooBig(newText):
	for path in fonts:
		var font = fonts[path]
		if font == null: continue
		set(path, font)
		for i in shrinkLimit:
			var textSize
			if isAutoWrapping():
				textSize = font.get_wordwrap_string_size(newText, maxSize)
				
				var s = newText.replace(" ", "\n")
				var freeHeight = font.get_wordwrap_string_size(s, 10000).y
				var constrainedHeight = font.get_wordwrap_string_size(s, maxSize).y
				if constrainedHeight > freeHeight:
					textSize.x = maxSize + 10
			else:
				textSize = font.get_string_size(newText)
				
			
			if textSize.x > maxSize or textSize.y > maxSizeY:
				font = Util.getSizedFont(font, - 2)
				set(path, font)
			else:
				break

		rect_size.x = 0
		rect_size.y = 0

func _notification(what):
	if what == NOTIFICATION_PREDELETE:
		Util.removeLocalizedNode(self)
