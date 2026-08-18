extends HBoxContainer

const defaultSize = 230.0

var nameLabel
var poolingHandle
var valueLabel
var perSecondLabel
var iconSprite

func preset():
	nameLabel = $Name
	valueLabel = $Value
	perSecondLabel = $PerSecond
	iconSprite = $IconRect / Icon

func _ready():
	
	nameLabel.rect_min_size.x = defaultSize


func setTuple(_name: String, _value: String, modified: int, iconTex: Texture):
	if TranslationServer.get_locale() == "fr":
		nameLabel.text = str(_name, Util.nonBreakingSpace, ":")
	else:
		nameLabel.text = _name + ":"
	
	valueLabel.text = _value
	valueLabel.set("custom_colors/font_color", Util.statColors[modified])
	
	perSecondLabel.hide()
	
	iconSprite.texture = iconTex
	call_deferred("positionIcon")

func positionIcon():
	iconSprite.position.y = rect_size.y * 0.5

func setPerSecond(_value: String, modified: int):
	perSecondLabel.show()
	perSecondLabel.text = _value
	perSecondLabel.set("custom_colors/font_color", Util.statColors[modified])
	
	var width = valueLabel.get("custom_fonts/font").get_string_size(valueLabel.text + _value)
	if width.x > 185:
		shrink(width.x - 185)

func shrink(amount):
	nameLabel.rect_min_size.x = defaultSize - amount
	nameLabel.rect_size.x = nameLabel.rect_min_size.x
