extends Item

const baseSprite = preload("res://Items/Exclusive/Sprites/Scale.png")
const leftSprite = preload("res://Items/Exclusive/Sprites/Scale_left.png")
const rightSprite = preload("res://Items/Exclusive/Sprites/Scale_right.png")

onready var regen: = int(getP("regen"))
onready var mana: = int(getP("mana"))
onready var speedPerGold: = getP("speed") / 100.0
onready var maxGoldDif: = int(getP("gold"))
onready var equilibriumSpeed: = getP("speed2") / 100.0
onready var leftCounter = $GoldCounter
onready var rightCounter = $GoldCounter2
onready var leftCounterDefaultPos = leftCounter.position
onready var rightCounterDefaultPos = rightCounter.position

func ready_deferred():
	.ready_deferred()
	updateCounterPositions()

func canAffect(item):
	return true
	
func canAffect_secondary(item):
	return true

func getCounterValue(color = Affected.Primary) -> int:
	var gold = 0
	if placed:
		for item in getAffectedItems(color):
			gold += item.getPrice()
	else:
		for item in getAffectedItems_nocache(color):
			gold += item.getPrice()
	return gold

func getCounterValue2() -> int:
	return getCounterValue(Affected.Secondary)

func onPrepare():
	var c1 = getCounterValue()
	var c2 = getCounterValue2()
	addSpeed(speedPerGold * min(c1, c2))
	if abs(c1 - c2) <= maxGoldDif:
		for item in getAffectedItems():
			item.addSpeed(equilibriumSpeed)
		for item in getAffectedItems(Affected.Secondary):
			item.addSpeed(equilibriumSpeed)

func doCooldownEffect():
	var curRegen = character().getRegeneration()
	var curMana = character().getMana()
	if curMana < curRegen:
		giveMana(mana)
	elif curRegen < curMana:
		giveRegeneration(regen)
	else:
		if Util.flip():
			giveMana(mana)
		else:
			giveRegeneration(regen)
	activate()

func updateScale():
	var c1 = getCounterValue()
	var c2 = getCounterValue2()
	if abs(c1 - c2) <= maxGoldDif:
		sprite.texture = baseSprite
	elif c1 > c2:
		sprite.texture = leftSprite
	else:
		sprite.texture = rightSprite
	shadows[0].texture = sprite.texture

func onAffectedItemAdded(item, color: int):
	updateScale()

func onAffectedItemRemoved(item, color: int):
	updateScale()

func onAddToInventory():
	updateScale()

func onRemoveFromInventory():
	sprite.texture = baseSprite

func updateCounterPositions():
	leftCounter.offset = leftCounterDefaultPos.rotated(rotation)
	rightCounter.offset = rightCounterDefaultPos.rotated(rotation)

func rotateTo(targetRotation, duration = 0.15):
	.rotateTo(targetRotation, duration)
	updateCounterPositions()

func onDraggedWithParentEnd():
	.onDraggedWithParentEnd()
	updateCounterPositions()

func onCalcTradeChance():
	Game.SELLBOX.tradeChance += getShopChance() / 100.0
