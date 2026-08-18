extends Item

var stackTypes: Array
onready var bonusChance: = getP("chance")
onready var luckNeeded: = int(getP("luckt"))

func _ready():
	stackTypes = Game.getBuffs()
	stackTypes.erase(Game.EventType.Lucky)
	
func canAffect(item):
	return item.canModifyChance()

func onPrepare():
	for item in getAffectedItems():
		item.addBonusChance(bonusChance)

func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		giveRandomBuffs(1, null, stackTypes)
	else:
		giveLucky(1)
	activate()

func getTriggerPriority() -> int:
	return Priority.High + 5
