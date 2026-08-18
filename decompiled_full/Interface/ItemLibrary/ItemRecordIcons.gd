extends Node2D

onready var leagueSprite = $League
onready var rankLabel = $Rank
onready var rankLight = $RankLight
onready var star = $Star

func setItem(item: Item):
	star.setItem(item)
	







	
	var bestRankSurvival = Game.getItemStatistics(Game.ItemStatistic.BestRankSurvival, 
		item.descriptor)
	
	if bestRankSurvival != null:
		rankLabel.show()
		leagueSprite.show()
		rankLight.show()
		var ranking = stepify(bestRankSurvival, 0.01)
		rankLabel.text = String(int(fmod(ranking, 1.0) * 100.0))
		leagueSprite.texture = Game.leagueIcons[int(ranking)]
		rankLight.self_modulate = Game.leagueColors[int(ranking)]




