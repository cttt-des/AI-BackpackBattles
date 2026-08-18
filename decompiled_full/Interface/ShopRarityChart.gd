extends Node2D

onready var bars = $HBoxContainer.get_children()

const ANI_DUR = 0.5

var alphaTween

func _ready():
	reset()
	Game.connect("shop_opened", self, "onShopOpened")
	Game.connect("fresh_run_started", self, "reset")








func reset():
	for bar in bars:
		bar.self_modulate.a = 0
		bar.rect_scale.y = 0
		bar.rect_min_size.y = 0

func onShopOpened():
	var odds = Game.shopSceneNode.getRarityOddsForCurRound()
	var normalizedOdds = odds.duplicate()
	var maxOdd = odds.max()
	for i in normalizedOdds.size():
		normalizedOdds[i] /= maxOdd
	
	var tween = create_tween().set_parallel()
	
	for rarity in range(5):
		var bar = bars[rarity]
		if odds[rarity] == 0:
			pass


		else:
			bar.self_modulate.a = 1
			
			var ySize = 5 + 46 * normalizedOdds[rarity]
			
			tween.tween_property(bar, "rect_scale:y", 1.0, ANI_DUR)
			tween.tween_property(bar, "rect_min_size:y", ySize, ANI_DUR)
		

func appear():
	alphaTween = Util.refreshTween(alphaTween)
	alphaTween.tween_property(self, "modulate:a", 1.0, 0.2)

func disappear():
	alphaTween = Util.refreshTween(alphaTween)
	alphaTween.tween_property(self, "modulate:a", 0.0, 0.2)



