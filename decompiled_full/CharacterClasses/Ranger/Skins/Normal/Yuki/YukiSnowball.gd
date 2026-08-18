extends Sprite

onready var baseScale = scale
var tween

func _ready():
	resize(true)
	Game.connect("shop_opened", self, "resize")
	Game.connect("continue_loaded", self, "resize")
	Game.connect("return_to_title", self, "resize")

func resize(instant: bool = false):
	var roundNum = Game.curRound
	if Game.hasArenaRunState():
		roundNum = Game.arenaRunState.get("round", 1)
	
	var size = baseScale * (1.0 + (roundNum - 1) * 0.05)
	
	if instant:
		scale = size
	else:
		tween = Util.refreshTween(tween)
		tween.tween_property(self, "scale", size, 0.3)
