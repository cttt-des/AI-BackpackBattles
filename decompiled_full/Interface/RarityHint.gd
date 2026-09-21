extends Node2D

var raritiesLabel
var fractionsLabel
var saleUniqueLabel
onready var shopSign = Game.shopSceneNode.get_node("ShopSign")
onready var tutorialAni = Game.shopSceneNode.get_node("ShopSign/AnimationPlayer")

func _ready():
	hide()
	Game.connect("shop_opened", self, "onShopOpened")
	Game.connect("inventory_changed", self, "onInventoryChanged")
	Game.connect("item_picked_up", self, "onItemChanged")
	Game.connect("item_dropped", self, "onItemChanged")
	Game.connect("item_sold", self, "onItemChanged")
	Game.connect("warp_cursor_shop", self, "onCursorWarp")
	call_deferred("readyDeferred")

func readyDeferred():
	Util.localizeFonts(self)
	updateLocale()
	if fractionsLabel != null:
		var font = fractionsLabel.get_font("normal_font")
		if font:
			var neededWidth = font.get_string_size("100.0%").x + 8
			if fractionsLabel.rect_min_size.x < neededWidth:
				fractionsLabel.rect_min_size.x = neededWidth

func updateLocale():
	raritiesLabel = $Rarities
	fractionsLabel = $Fractions
	saleUniqueLabel = $SaleUnique
	
	var text = ""
	for rarityI in range(0, Item.Rarity.Unique):
		text += Util.wrapInColor(Item.getRarityName(rarityI), 
			Game.rarityColors[rarityI].lightened(0.2))
		if TranslationServer.get_locale() == "fr":
			text += Util.nonBreakingSpace
		text += ":\n"
	text = text.trim_suffix("\n")
	raritiesLabel.bbcode_text = text
	
func onShopOpened():
	updateFractions()
	
	if (Game.getNumStartedRuns() >= 3 and 
		Game.getNumStartedRuns() < 10 and 
		not Game.isTutorialDone(Game.TutorialSteps.ShopSign)):
		
		tutorialAni.play("Tutorial")

func updateFractions():
	if Game.shopSceneNode == null:
		return
	var odds = Game.shopSceneNode.getDisplayRarityOdds()
	var lines = []
	var numLines = Item.Rarity.Unique
	var showDecimals = false
	for i in range(numLines):
		var fraction = 0.0
		if i < odds.size():
			fraction = odds[i]
		var percentRaw = fraction * 100.0
		if abs(percentRaw - round(percentRaw)) > 0.001:
			showDecimals = true
			break

	for i in range(numLines):
		var fraction = 0.0
		if i < odds.size():
			fraction = odds[i]
		var percentRaw = fraction * 100.0
		var percent
		if showDecimals:
			percent = stepify(percentRaw, 0.1)
		else:
			percent = stepify(percentRaw, 1.0)
		var percentStr
		if showDecimals:
			percentStr = "%.1f" % percent
		else:
			percentStr = String(int(round(percent)))
		lines.push_back(percentStr + "%")
	fractionsLabel.bbcode_text = "[right]" + "\n".join(lines)

func onInventoryChanged():
	if Game.state != Game.State.Shop:
		return
	updateFractions()

func onItemChanged(_item = null, _dropResult = null):
	if Game.state != Game.State.Shop:
		return
	updateFractions()

func show():
	if Game.state != Game.State.Shop:
		return
	.show()
	var uniqueColor = Game.rarityColors[Item.Rarity.Unique].lightened(0.2)
	var saleChance = stepify(Game.shopSceneNode.getSaleChance() * 100.0, 1)
	var uniqueChance = stepify(Game.shopSceneNode.getUniqueChance() * 100.0, 1)
	saleUniqueLabel.bbcode_text = Util.tr("HINT_SaleUniqueChances").format({
		
		"Unique": Util.getIcon("treasure"), 
		"saleChance": saleChance, 
		"uniqueChance": uniqueChance, 
		"maxUniques": ItemBook.getMaxUniques(), 
		"curUniques": ItemBook.getNumUniques(false)
	})
	
	Game.setTutorialDone(Game.TutorialSteps.ShopSign)
	tutorialAni.stop()
	shopSign.modulate = Color(1.1, 1.1, 1.1)

func hide():
	.hide()
	shopSign.modulate = Color.white

func onCursorWarp():
	Game.addPointOfInterest(Vector2(1480, 70))
