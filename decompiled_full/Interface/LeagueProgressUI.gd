extends Node2D

onready var rankingLabel = $Ranking
onready var leagueLabel = $League
onready var leagueProgressBar = $LeagueProgressBar
onready var emblem = $LeagueEmblem

func _ready():
	leagueProgressBar.material = leagueProgressBar.material.duplicate()
	Util.localizeFonts(leagueLabel)

func updateUI(charClass):
	rankingLabel.text = String(Game.getRanking(charClass))
	var league = Game.getLeague(charClass)
	leagueLabel.text = Game.getLeagueName(league)
	leagueLabel.set("custom_colors/font_color", Game.leagueColors[league])
	leagueProgressBar.material.set_shader_param("progress", Game.getLeagueProgress(charClass))
	emblem.setLeague(league)
	leagueProgressBar.modulate = Game.leagueColors[league]
