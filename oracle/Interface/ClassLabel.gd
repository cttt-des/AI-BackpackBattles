extends LocalizedControl

onready var tooltipArea = get_node_or_null("TooltipArea")
onready var subclassParticles = $SubclassParticles
onready var icon = $ClassIcon

func _ready() -> void :
	Game.connect("character_changed", self, "updateText")
	Game.connect("item_bought", self, "onItemBought")
	Game.connect("pre_shop_opened_from_combat", self, "updateText")
	
	
	
	Util.callNextFrame(self, "updateText")

func updateText(subclass = ""):
	if Game.PLAYER.INVENTORY == null: return
	
	icon.texture = Game.classIcons[Game.curClass]
	
	if Game.isLobbyUIOpen():
		translationKey = Game.getClassTranslationKey()
	elif subclass != "":
		translationKey = "SUBCLASS_" + subclass + "_NAME"
	else:
		translationKey = Game.getClassOrSubclassTranslationKey()
	
	set("custom_colors/font_color", Game.classResources[Game.curClass].color)
	
	if tooltipArea:
		if Game.isClassUnlocked():











			var items = "\n\n" + Util.tr("UI_Subclasses")
			tooltipArea.params = {"items": items}
			tooltipArea.keyword = Game.getClassKeys()[Game.curClass]
		
			tooltipArea.show()
		else:
			tooltipArea.hide()
	
	.updateText()
	
	if TranslationServer.get_locale() == "de":
		set("text", get("text").replace("- ", "-"))

func onItemBought(item, _onSale):
	if item.descriptor.startsSubclass != "":
		
		subclassParticles.modulate = Game.classResources[Game.curClass].color
		subclassParticles.activate()
		updateText(item.descriptor.startsSubclass)
