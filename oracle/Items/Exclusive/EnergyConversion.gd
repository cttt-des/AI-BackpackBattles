extends Item

onready var heat: = int(getP("heat"))
onready var heatThreshold: = int(getP("heatt"))
onready var numBuffs: = int(getP("buffs"))
onready var speedPerFood: = getP("speed") / 100.0
var stackTypes

func canAffect(item):
	return item.hasType(Type.Food)

func _ready():
	stackTypes = Game.getBuffs()
	stackTypes.erase(Game.EventType.Heat)

func onPrepare():
	addSpeed(getNumAffectedItems() * speedPerFood)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		if character().getHeat() >= heatThreshold:
			giveRandomBuffs(numBuffs, null, stackTypes)
		else:
			giveHeat(heat)
		
		activate()
