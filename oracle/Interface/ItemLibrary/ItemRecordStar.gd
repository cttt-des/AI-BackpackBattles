extends Node2D

export var showEmptyStar = false

var lightColors = {
	Game.ItemRecordStar.Bronze: Color(1, 0.842957, 0.675781), 
	Game.ItemRecordStar.Silver: Color(0.84235, 0.846648, 0.857422), 
	Game.ItemRecordStar.Gold: Color(0.96875, 0.893547, 0.618713), 
	Game.ItemRecordStar.Diamond: Color(0.992188, 0.773209, 0.91948)
}

var stars = {
	Game.ItemRecordStar.Bronze: preload("res://Interface/BronzeStar.png"), 
	Game.ItemRecordStar.Silver: preload("res://Interface/SilverStar.png"), 
	Game.ItemRecordStar.Gold: preload("res://Interface/GoldStar.png"), 
	Game.ItemRecordStar.Diamond: preload("res://Interface/Diamond.png")
}

const noStarModulate = Color(0.054902, 0.039216, 0.031373, 0.333333)

onready var starSprite = $Sprite
onready var starLight = $Light

func setStarType(starType: int):
	if starType != - 1:
		starSprite.show()
		starLight.show()
		starSprite.texture = stars[starType]
		starSprite.modulate = Color.white
		starLight.self_modulate = lightColors[starType]
	else:
		if showEmptyStar:
			starLight.hide()
			starSprite.show()
			starSprite.texture = stars[Game.ItemRecordStar.Bronze]
			starSprite.modulate = noStarModulate



func setItem(item: Item):
	





	var wins = Game.getItemStatistics(Game.ItemStatistic.MostWins, 
		item.descriptor, 0)
	if wins == Game.MAX_ROUNDS:
		setStarType(Game.ItemRecordStar.Diamond)
	elif wins == Game.MAX_ROUNDS - 1:
		setStarType(Game.ItemRecordStar.Gold)
	else:
		var survivals = Game.getItemStatistics(Game.ItemStatistic.Survivals, 
			item.descriptor, 0)
		if survivals > 0:
			setStarType(Game.ItemRecordStar.Silver)
		elif wins >= Game.MAX_WINS:
			setStarType(Game.ItemRecordStar.Bronze)
		else:
			setStarType( - 1)
	
	
	
