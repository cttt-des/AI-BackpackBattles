extends Item
var regen
var mana
var speedPerGold
var maxGoldDif
var equilibriumSpeed
var leftCounter
var rightCounter
var leftCounterDefaultPos
var rightCounterDefaultPos

func ready_deferred():
	.ready_deferred()
	updateCounterPositions()


func canAffect(item):
	return true
	

func canAffect_secondary(item):
	return true


func getCounterValue(color = CoreConst.Affected.Primary) -> int:
	var gold = 0
	if placed:
		for item in getAffectedItems(color):
			gold += item.getPrice()
	else:
		for item in getAffectedItems_nocache(color):
			gold += item.getPrice()
	return gold


func getCounterValue2() -> int:
	return getCounterValue(CoreConst.Affected.Secondary)


func onPrepare():
	var c1 = getCounterValue()
	var c2 = getCounterValue2()
	addSpeed(speedPerGold * min(c1, c2))
	if abs(c1 - c2) <= maxGoldDif:
		for item in getAffectedItems():
			item.addSpeed(equilibriumSpeed)
		for item in getAffectedItems(CoreConst.Affected.Secondary):
			item.addSpeed(equilibriumSpeed)


func doCooldownEffect():
	var curRegen = character().getRegeneration()
	var curMana = character().getMana()
	if curMana < curRegen:
		giveMana(mana)
	elif curRegen < curMana:
		giveRegeneration(regen)
	else:
		if ctx.util.flip():
			giveMana(mana)
		else:
			giveRegeneration(regen)
	activate()


func updateScale():
	var c1 = getCounterValue()
	var c2 = getCounterValue2()
	if abs(c1 - c2) <= maxGoldDif:
		pass
	elif c1 > c2:
		pass
	else:
		pass


func onAffectedItemAdded(item, color: int):
	updateScale()


func onAffectedItemRemoved(item, color: int):
	updateScale()


func onAddToInventory():
	updateScale()


func onRemoveFromInventory():
	pass


func updateCounterPositions():
	pass


func rotateTo(targetRotation, duration = 0.15):
	.rotateTo(targetRotation, duration)
	updateCounterPositions()


func onDraggedWithParentEnd():
	.onDraggedWithParentEnd()
	updateCounterPositions()


func onCalcTradeChance():
	pass

func _readyInit():
	._readyInit()
	regen = int(getP("regen"))
	mana = int(getP("mana"))
	speedPerGold = getP("speed") / 100.0
	maxGoldDif = int(getP("gold"))
	equilibriumSpeed = getP("speed2") / 100.0
