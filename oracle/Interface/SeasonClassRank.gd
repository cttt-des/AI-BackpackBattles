extends Node2D

onready var icon = $ClassIcon
onready var rankLabel = $Ranking
onready var emblem = $LeagueEmblem

func setLeague(classI: int, leagueExact: float):
	icon.texture = Game.classIcons[classI]
	rankLabel.text = str(int(fmod(leagueExact, 1.0) * 100))
	var league = int(leagueExact)
	emblem.setLeague(league)
