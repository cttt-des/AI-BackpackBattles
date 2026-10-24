extends Reference
class_name CombatSnapshot

var playerData
var opponentData

func _init(playerDamageMeter, opponentDamageMeter) -> void :
	playerData = CombatStats.new(Game.PLAYER, playerDamageMeter)
	opponentData = CombatStats.new(Game.OPPONENT, opponentDamageMeter)

func apply():
	playerData.apply(Game.PLAYER)
	opponentData.apply(Game.OPPONENT)
	
	

class CombatStats:
	var health: int
	var stamina: float
	var stacks: Dictionary
	var damageMeter: Dictionary

	func _init(character: Character, _damageMeter) -> void :
		health = character.getCurrentHealth()
		stamina = character.getCurrentStamina()
		for stackType in range(Game.EventType.Block, Game.EventType.Cold + 1):
			stacks[stackType] = character.getStacks(stackType)
		
		damageMeter = _damageMeter
	
	func apply(character: Character):
		
		character.setCurrentStamina(stamina)
		
		
