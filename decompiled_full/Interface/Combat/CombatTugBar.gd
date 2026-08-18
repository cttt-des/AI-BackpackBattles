extends ProgressBar

func _ready():
	
	
	set_process(false)

func _process(delta):
	var playerStrength = Game.PLAYER.getCurrentHealth() + Game.PLAYER.getBlock()
	var oppoStrength = Game.OPPONENT.getCurrentHealth() + Game.OPPONENT.getBlock()
	
	max_value = playerStrength + oppoStrength
	value = playerStrength
	

func onCombatStart():
	set_process(true)

func onCombatEnd(result):
	set_process(false)
