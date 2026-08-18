extends Node

const MAX_SKINS = 16

var skins = []

func getNumSkinsForClass(classI, style) -> int:
	return getSkinsForClass(classI, style).size()

func getSkinsForClass(classI, style) -> Array:
	return skins[classI][style]


func getSkinFromId(classI, style, id):
	return Util.nDimArrayGet(skins, [classI, style, id], 
		skins[classI][style][0])

func getRandomSkinFor(classI, style, slot):
	var possibleSkins = []
	for skin in skins[classI][style]:
		if skin.prices[slot] != - 1:
			possibleSkins.push_back(skin)
	
	return Util.pickRandomElement(possibleSkins)

const scenePathFormat = "res://CharacterClasses/{class}/Skins/{style}/{skin}/{skin}.tscn"
const iconPathFormat = "res://CharacterClasses/{class}/Skins/{style}/{skin}/{skin}.png"
const hoveredIconPathFormat = "res://CharacterClasses/{class}/Skins/{style}/{skin}/{skin}_hovered.png"


func _ready():
	for classI in Game.getNumClasses():
		skins.push_back([[], []])
	
	var table = Table.new().loadFromCsv("res://Sheets/CSV/SkinData.csv")

	var dir = Directory.new()
	for line in table.countRows() - 1:
		var exclusive: bool = (table.getStr("demo", line) == "no")
		var className: String = table.getStr("class", line)
		var classI = Game.getClassEnum().get(className, - 1)
		
		if classI == - 1 or not Game.isClassUnlocked(classI):
			continue
		
		if exclusive and not Game.showExclusiveContent():
			continue
		
		var skin: CharacterSkin = CharacterSkin.new()
		skin.skinName = table.getStr("name", line)
		
		var isChibi: bool = table.isEqual("style", line, "chibi")
		var style: String = "Chibi" if isChibi else "Normal"
		
		var params = {
			"class": className, 
			"style": style, 
			"skin": skin.skinName
			}
		var scenePath: String = scenePathFormat.format(params)
		
		skin.scene = load(scenePath)
		
		var iconPath: String = iconPathFormat.format(params)
		skin.icon = load(iconPath)
		
		var hoveredIconPath: String = hoveredIconPathFormat.format(params)
		skin.icon_hovered = load(hoveredIconPath)
		
		
		for slot in Game.SkinSlot:
			skin.prices[Game.SkinSlot[slot]] = table.getInt(slot, line)
		
		skin.id = table.getInt("id", line)
		skin.order = table.getInt("order", line)
		
		
		skins[classI][int(isChibi)].push_back(skin)
		
		
		


	
class OrderSorter:
	static func sort(skin1: CharacterSkin, skin2: CharacterSkin):
		return skin1.order < skin2.order
