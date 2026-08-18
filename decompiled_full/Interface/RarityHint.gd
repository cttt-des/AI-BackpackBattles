extends Node2D

var raritiesLabel
var fractionsLabel
var saleUniqueLabel
onready var shopSign = Game.shopSceneNode.get_node("ShopSign")
onready var tutorialAni = Game.shopSceneNode.get_node("ShopSign/AnimationPlayer")

func _ready():
	hide()
	Game.connect("shop_opened", self, "onShopOpened")
	Game.connect("warp_cursor_shop", self, "onCursorWarp")
	call_deferred("readyDeferred")

func readyDeferred():
	Util.localizeFonts(self)
	updateLocale()

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
	fractionsLabel.bbcode_text = "[right]"
	for fraction in Game.shopSceneNode.getRarityOddsForCurRound():
		fractionsLabel.bbcode_text += String(fraction * 100.0) + "%\n"
	fractionsLabel.bbcode_text = fractionsLabel.bbcode_text.trim_suffix("\n")
	
	if (Game.getNumStartedRuns() >= 3 and 
		Game.getNumStartedRuns() < 10 and 
		not Game.isTutorialDone(Game.TutorialSteps.ShopSign)):
		
		tutorialAni.play("Tutorial")

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
