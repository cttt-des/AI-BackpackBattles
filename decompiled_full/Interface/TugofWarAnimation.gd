extends Sprite

var oppoSword
var startRot: float
var oppoStartRot: float
var displayAdvantage: float

const STEP = 0.05
const MAX_ANGLE = 74.0
const DISADVANTAGE_FACTOR = 2.0

func _ready():
	set_physics_process(false)
	Game.connect("combat_scene_left", self, "leavingCombat")

func activate():
	oppoSword = Game.OPPONENT.get_node("CombatUI/Sheet/Sword")
	set_physics_process(true)
	startRot = rotation_degrees
	oppoStartRot = oppoSword.rotation_degrees
	displayAdvantage = 0.5

func _physics_process(delta):
	var playerStrength = Game.PLAYER.getCurrentHealth()
	if playerStrength > 0:
		playerStrength += Game.PLAYER.getBlock()
	playerStrength = max(playerStrength, 0)
	
	var oppoStrength = Game.OPPONENT.getCurrentHealth()
	if oppoStrength > 0:
		oppoStrength += Game.OPPONENT.getBlock()
	oppoStrength = max(oppoStrength, 0)
	
	if playerStrength == 0 and oppoStrength == 0:
		playerStrength = 1
	
	var playerAdvantage = float(playerStrength) / (playerStrength + oppoStrength)
	displayAdvantage = lerp(displayAdvantage, playerAdvantage, STEP)
	
	var offsetAdvantage = displayAdvantage - 0.5
	
	if offsetAdvantage > 0:
		rotation_degrees = startRot + offsetAdvantage * MAX_ANGLE
		oppoSword.rotation_degrees = oppoStartRot + offsetAdvantage * MAX_ANGLE * DISADVANTAGE_FACTOR
	else:
		rotation_degrees = startRot + offsetAdvantage * MAX_ANGLE * DISADVANTAGE_FACTOR
		oppoSword.rotation_degrees = oppoStartRot + offsetAdvantage * MAX_ANGLE
	
	

func leavingCombat():
	set_physics_process(false)
