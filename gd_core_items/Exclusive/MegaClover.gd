extends Item
var stackTypes
var activated: bool
var sales
var luckNeeded: int
var numBuffs: int

func onShopEntered():
	pass

func onPrepare():
	connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")
	activated = false


func onLuckyChanged(amount, event):
	if not activated and character().getLucky() >= luckNeeded:
		activated = true
		
		giveRandomBuffs(numBuffs, event, stackTypes)
		activate()


func onSaleRoll(_item):
	pass

func _readyInit():
	._readyInit()
	sales = getP("sales") / 100.0
	luckNeeded = getP("luckneeded")
	numBuffs = getP("buffs")
	stackTypes = CoreConst.getBuffs()
	stackTypes.erase(CoreConst.EventType.Lucky)

