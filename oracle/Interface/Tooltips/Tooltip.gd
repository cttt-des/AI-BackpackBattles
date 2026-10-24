extends Control
class_name ToolTip

enum Alignment{
	Top, 
	Center, 
	Bottom
}

const keywords = [
	"spikes", "vampirism", "poison", "regen", "bl", "lucky", 
	"stun", "blind", "blindingLight", "reflect", "mana", "heat", 
	"cold", "empower", "rage", "empty", "affected", "fatigue", 
	"treasure", "charge"
]

const centerStr = "[center]"
const referenceTextFormat = "{prefix}[sc len={length} color=#{color}]{replacement}[/sc]{suffix}"
const referenceImageFormat = "{prefix}{img}{suffix}"

var triggerColor_html = Util.triggerColor.to_html(false)


onready var vboxcontainer = $VBoxContainer
onready var nameLabel = get_node_or_null("VBoxContainer/Name")

const Y_OFFSET = 0
export var Y_BORDER = 120
var MARGIN = 8
export var SCREEN_MARGIN = Vector2.ZERO

func _ready():
	hide()


func updateSize():
	
	var ySize = vboxcontainer.rect_size.y + Y_BORDER
	set_end(rect_position + Vector2(rect_size.x, 0))
	set_end(rect_position + Vector2(rect_size.x, ySize))


func forceUpdate():
	var parent = get_parent()
	parent.remove_child(self)
	parent.add_child(self)
	show()
	updateSize()
	Util.callNextFrame(self, "updateSize")
	
func align(toolPos: Vector2, toolSize: Vector2, alignment):
	if not is_inside_tree(): return
	
	
	rect_global_position = toolPos + Vector2(toolSize.x + MARGIN, Y_OFFSET)
	
	var viewportRect = get_viewport_rect()
	var cameraTopLeft = viewportRect.position
	var cameraBottomRight = viewportRect.end
	var rightMargin = SCREEN_MARGIN.x
	if Game.itemLibrary.isOpen:
		rightMargin = 450
	
	
	if (rect_global_position.x + rect_size.x >= cameraBottomRight.x - rightMargin):
		rect_global_position.x = toolPos.x - rect_size.x - MARGIN
		rect_global_position.x = max(rect_global_position.x, - 7)
	
	
	if alignment == Alignment.Center:
		rect_global_position.y -= (rect_size.y - toolSize.y) / 2
	
	
		
	var highestRectY = cameraTopLeft.y + SCREEN_MARGIN.y
	var lowestRectY = cameraBottomRight.y - SCREEN_MARGIN.y - rect_size.y
	
	if (rect_global_position.y <= highestRectY):
		rect_global_position.y = highestRectY
		
	elif (rect_global_position.y >= lowestRectY):
		rect_global_position.y = lowestRectY


func setPosition(toolPos: Vector2, toolSize: Vector2, alignment = Alignment.Center):
	updateSize()
	align(toolPos, toolSize, alignment)
	updateSize()



func forceUpdatePosition(toolPos: Vector2, toolSize: Vector2, alignment = Alignment.Center):
	setPosition(toolPos, toolSize, alignment)
	forceUpdate()
	
	
	call_deferred("setPosition", toolPos, toolSize, alignment)

func onTagHoverStart(_tag):
	pass
	
func onTagHoverEnd(_tag):
	pass


func replaceReferences(text, iconSize = null):
	



		
	var iterations = 0
	var dollarPos = - 1
	while true:
		if iterations == 100:
			print("Endless loop, probably } missing")
			Util.eassert()
			break
		iterations += 1
		
		dollarPos = text.find("$", dollarPos + 1)
		if dollarPos == - 1:
			break
		
		
		
		var refEndPos = Util.findFirstNonLatinLetterOrNumber(text, dollarPos + 1)
		if refEndPos == - 1:
			refEndPos = text.length()
		var reference = text.substr(dollarPos + 1, refEndPos - dollarPos - 1)
		
		
		var img = ""
		if reference in Util.icons:
			img = Util.getIcon(reference, iconSize)
			text = referenceImageFormat.format({
				"prefix": text.substr(0, dollarPos), 
				"suffix": text.substr(refEndPos), 
				"img": img
			})
			continue
		
		var replace = false
		var color = Util.paramColor_html
		var linebreaks = 0
		
		if reference in keywords:
			replace = true
		


			
		elif reference in Util.getTypeEnum():
			replace = true
		
		elif reference == "h":
			replace = true

		elif reference == "t":
			replace = true
			color = triggerColor_html
			if dollarPos != 0:
				linebreaks = 2
		
		
		elif reference == "m":
			replace = true
			color = triggerColor_html
		
		elif reference == "t1":
			replace = true
			color = triggerColor_html
			if dollarPos != 0:
				linebreaks = 1
		
		elif reference == "red":
			replace = true
			color = Util.red.to_html(false)
		
		elif reference.capitalize() in Util.getRarityEnum():
			var rarity = Util.getRarityEnum()[reference.capitalize()]
			replace = true
			color = Game.rarityColors[rarity].lightened(0.3).to_html(false)
		
		
		if replace:
			var replacement = ""
			for i in linebreaks:
				replacement += "\n"
			if linebreaks > 0:
				
				if text[refEndPos] == " ":
					refEndPos += 1
			
			if refEndPos < text.length() and text[refEndPos] == "[":
				
				var closingBracketPos = findClosingBracket(text, refEndPos + 1)
				if not reference in Util.icons:
					replacement += Util.substr(text, refEndPos + 1, closingBracketPos - 1)
				
				refEndPos = closingBracketPos + 1
			
			
			text = referenceTextFormat.format({
				"prefix": text.substr(0, dollarPos), 
				"suffix": text.substr(refEndPos), 
				"color": color, 
				"length": replacement.length(), 
				"replacement": replacement
			})
		
	
	return text

static func findClosingBracket(inText: String, fromPos: int) -> int:
	var bracketCounter = 1
	for i in range(fromPos, inText.length()):
		if inText[i] == "[":
			bracketCounter += 1
		elif inText[i] == "]":
			bracketCounter -= 1
		if bracketCounter == 0:
			return i
	return - 1

static func highlight(text: String, wave = false, bold = false) -> String:
	var iterations = 0
	var dollarPos = - 1
	while true:
		if iterations == 100:
			print("Endless loop, probably } missing ", text)
			Util.eassert()
			break
		iterations += 1
		
		dollarPos = text.find("$h[", dollarPos + 1)
		if dollarPos == - 1:
			break
		
		var refStartPos = dollarPos + 3
		var closingBracketPos = findClosingBracket(text, refStartPos)
		var reference = text.substr(refStartPos, closingBracketPos - refStartPos)
		
		var replacement = Util.wrapInColor(reference, Util.paramColor)
		if wave:
			replacement = str("[wave]", replacement, "[/wave]")
		if bold:
			replacement = str("[b]", replacement, "[/b]")
		
		
		text = Util.replaceSubstr(text, dollarPos, closingBracketPos, replacement)
		
	return text

func discard():
	Util.removeLocalizedNode(self)
	queue_free()


