extends Node2D

const trophyRainParticles = preload("res://Interface/TrophyRainParticles.tscn")

onready var animation = $AnimationPlayer
onready var trophyLabel = $Node2D / TrophyLabel

var particles

func _ready():
	Game.pause(Game.PauseSource.PatchNotes)
	animation.play("Open")
	animation.advance(0.01)
	
	particles = trophyRainParticles.instance()
	get_parent().add_child(particles)
	
	var bonusTrophies = 50
	
	for oldRankEmblem in $Node2D / OldRanks.get_children():
		var classI = Game.getClassEnum()[oldRankEmblem.name]
		var newRankEmblem = $Node2D / NewRanks.get_node(oldRankEmblem.name)
		
		var rating = Game.getRunRating(classI, "2")
		var leagueExact = Game.getLeague_exact(rating)
		var league = int(leagueExact)
		
		bonusTrophies += league * 10
		
		var rating2 = Game.getRunRating(classI, "3")
		var newLeagueExact = Game.getLeague_exact(rating2)
		
		oldRankEmblem.setLeague(classI, leagueExact)
		newRankEmblem.setLeague(classI, newLeagueExact)
		
	
	trophyLabel.formatParams = {"num":
		str("[b]", Util.highlight(bonusTrophies), "[/b]")}
	trophyLabel.updateText()
	
	Game.giveTrophies(bonusTrophies)
	Game.saveGame()

func close():
	animation.play("Close")
	particles.emitting = false
	
	var tween = create_tween()
	tween.tween_property(particles, "speed_scale", 3.0, 0.5)
	
	Util.callDelayed(particles, "queue_free", 10)

func onClosed():
	Game.unpause(Game.PauseSource.PatchNotes)
	queue_free()
