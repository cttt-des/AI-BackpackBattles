extends Item
const amuletColor = Color(0.639216, 0.635294, 0.215686)
var usedStacks: Dictionary
var bonusSpeed
var buffTimer
var refund

func onPrepare():
	connectToCharacterBuffs("onBuffChanged")
	for buff in CoreConst.getBuffs():
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

func _readyInit():
	._readyInit()
	bonusSpeed = getP("speed") / 100.0
	buffTimer = newItemTimer("BuffTimer", "onBuffTimeout", true)
	refund = getP("refund") / 100.0
	pass

