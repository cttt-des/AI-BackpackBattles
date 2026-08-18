extends VBoxContainer

onready var rect = $ItemRect
onready var nameLabel = $ItemName
onready var nameFont = nameLabel.get("custom_fonts/font")
onready var typeIcon = $ItemRect / Icon
var item

const X_MARGIN = 0
const Y_MARGIN = 10
const catalystColor = Color(0.227451, 1, 0.439216)

func setType(type: String):
	setName(tr("INGREDIENT_" + type))
	nameLabel.set("custom_colors/font_color", catalystColor)
	
	typeIcon.show()
	typeIcon.texture = Util.getIconTexture(type.to_lower())

func setItem(descriptor, catalyst: bool):
	item = descriptor.instantiate_pooled()
	item.ownerType = item.Owner.Tooltip
	rect.add_child(item)
	item.initTooltip()
	item.scaleToFit(Vector2(180, 200), 0.9)
	var itemSize = item.getTextureSize()
	
	rect.rect_min_size.x = max(rect.rect_min_size.x, itemSize.x + X_MARGIN)
	rect.rect_min_size.y = max(rect.rect_min_size.y, itemSize.y + Y_MARGIN)
	item.z_index = 2
	
	setName(item.getTranslatedName())
	
	if catalyst:
		nameLabel.set("custom_colors/font_color", catalystColor)

func setName(text):
	Util.localizeFonts(nameLabel)
	nameFont = nameLabel.get("custom_fonts/font")
	var split = text.split(" ")
	for word in split:
		for i in 3:
			var size = nameFont.get_string_size(word)
			if size.x > 180:
				nameFont = Util.getSizedFont(nameFont, - 4)
				nameFont.extra_spacing_top += 3
				nameLabel.set("custom_fonts/font", nameFont)
			else:
				break
			
	nameLabel.text = text


func positionItem():
	
	item.position = rect.rect_size * 0.5 - item.sprite.offset * 0.5

func discard():
	if item != null:
		item.discard()
