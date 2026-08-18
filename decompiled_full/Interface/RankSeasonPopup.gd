extends Node2D

onready var animation = $AnimationPlayer
onready var trophyLabel = $Node2D / TrophyLabel

func _ready():
	Game.pause(Game.PauseSource.PatchNotes)
	animation.play("Open")
	animation.advance(0.01)
	
	var bonusTrophies = 50
	
	for classNode in $Node2D / Classes.get_children():
		var classI = Game.getClassEnum()[classNode.name]
		
		var icon = classNode.get_node("ClassIcon")
		var rankLabel = classNode.get_node("Ranking")
		var emblem = classNode.get_node("LeagueEmblem")
		
		var rating = Game.getRunRating(classI, "1")
		var leagueExact = Game.getLeague_exact(rating)
		var league = int(leagueExact)
		
		bonusTrophies += league * 10
		
		classNode.setLeague(classI, leagueExact)
	
	trophyLabel.formatParams = {"num":
		str("[b]", Util.highlight(bonusTrophies), "[/b]")}
	trophyLabel.updateText()
	
	Game.giveTrophies(bonusTrophies)
	Game.saveGame()

func close():
	animation.play("Close")

func onClosed():
	Game.unpause(Game.PauseSource.PatchNotes)
	queue_free()
