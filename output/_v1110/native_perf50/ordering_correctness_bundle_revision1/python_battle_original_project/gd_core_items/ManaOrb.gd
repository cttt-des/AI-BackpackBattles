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
	# ★ np25 evt105 f09 面 AFFL 探针（双门控零耗链）：ManaOrb 连接集定谳——
	#   夹具 affected=(5,3),(5,5),(7,3),(7,5)，gd 漏连 (7,5) Piggybank
	#   （BUS activated 0 listeners 铁证）。打印逐格命中与受影响物品集。
	if ctx.rng.oracle_trace and ctx.rng._stacktrace:
		var _cells = getAffectedCellsInInventory()
		var _hit = ""
		for _c in _cells:
			var _it = getOwnOrPlayerInventory().getItemInCell(_c)
			_hit += "[" + str(_c) + "=" + ("null" if _it == null else String(_it.descriptor.identifier) + "/ot" + str(int(_it.ownerType)) + " p" + str(int(_it.placed))) + "]"
		var _aff = getAffectedItems()
		var _aff_names = ""
		for _a in _aff:
			_aff_names += String(_a.descriptor.identifier) + ","
		ctx.rng.trace_diag("AFFL", String(descriptor.identifier) + "/ot" + str(int(ownerType)), str(_cells), _hit + " aff=" + _aff_names)
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
	
