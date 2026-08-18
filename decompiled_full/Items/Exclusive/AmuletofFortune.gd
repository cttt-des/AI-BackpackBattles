extends Item

const amuletColor = Color(0.266667, 0.960784, 0.667953)

onready var bonusChance: = getP("chance")
onready var numBuffs: = int(getP("buffs"))

func _ready():
	specificDragParticles[0].self_modulate = amuletColor

func canAffect(item):
	return item.canModifyChance()

func onPrepare():
	for item in getAffectedItems():
		item.addBonusChance(bonusChance)

func doCooldownEffect():
	giveMostBuffs(numBuffs)
	onAfterEffectFinished()

func getTriggerPriority() -> int:
	return Priority.High + 5
