extends Item
var stackTypes: Array
var activated: bool
var bonusBuffs: int
var mana
var manaNeeded: int
var buffs
var light

func canAffect(item):
	return item.canActivate()


func onPrepare():
	bonusBuffs = 0
	setState(false)
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")
	connectForCombat(character(), "character_mana_changed", "onManaChanged")


func onItemActivated(event):
	if rollChance():
		miniActivate()
		giveMana(mana)


func onManaChanged(amount, triggerEvent):
	if not activated and amount > 0 and character().getMana() >= manaNeeded:
		setState(true)
		var event = useMana(manaNeeded, triggerEvent)
		giveRandomBuffs(buffs + bonusBuffs, event, stackTypes)
		activate()
		


func onShopEntered():
	onStateChanged(false)


func addBonusRandomBuffs(amount: int):
	bonusBuffs += amount


func onStateChanged(_activated: bool):
	activated = _activated

func _readyInit():
	._readyInit()
	mana = int(getP1())
	manaNeeded = getP2()
	buffs = int(getP3())
	stackTypes = CoreConst.getBuffs()
	stackTypes.erase(CoreConst.EventType.Mana)
	
