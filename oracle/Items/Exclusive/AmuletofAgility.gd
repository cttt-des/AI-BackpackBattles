extends Item

const amuletColor = Color(0.639216, 0.635294, 0.215686)

onready var bonusSpeed = getP("speed") / 100.0
onready var buffTimer = $BuffTimer
onready var refund = getP("refund") / 100.0

var usedStacks: Dictionary

func _ready():
	specificDragParticles[0].self_modulate = amuletColor

func onPrepare():
	connectToCharacterBuffs("onBuffChanged")
	for buff in Game.getBuffs():
		usedStacks[buff] = 0.0

func canAffect(item):
	return item.hasCooldown()

func onCombatStart():
	buffTimer.start(getP_m("dur"))
	for item in getAffectedItems():
		item.addSpeed(bonusSpeed)
	activate()

func onBuffTimeout():
	for item in getAffectedItems():
		item.reduceSpeed(bonusSpeed)

func onBuffChanged(amount, event):
	if amount < 0 and event.getParam("used", false):
		var used = - amount
		var buffType = event.getType()
		usedStacks[buffType] += used * refund
		var toRefund = int(round(usedStacks[buffType]))
		
		if toRefund > 0:
			usedStacks[buffType] -= toRefund
			giveStacks(character(), buffType, toRefund, event)
			miniActivate()

func onCombatEnd():
	buffTimer.stop()
