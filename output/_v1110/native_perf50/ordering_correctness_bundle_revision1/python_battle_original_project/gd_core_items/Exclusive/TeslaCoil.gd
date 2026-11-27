extends Item
var itemsToAdvance: Array
var numCollectedCharges: = 0
var advanceItemCounter: = 0
var collectCharges: = true
var cdAdvance
var salesChance
var engineerWeight
var chargeCounter

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	setState(0)
	collectCharges = true
	numCollectedCharges = 0
	advanceItemCounter = 0
	itemsToAdvance = getAffectedItems().duplicate()
	ctx.rng.shuffleEngine(itemsToAdvance, "Exclusive/TeslaCoil.gd:26")
	
	var otherItems = []
	for item in inventory.getItems():
		if item != self and not item in itemsToAdvance:
			if item.hasCooldown():
				otherItems.push_back(item)
	
	ctx.rng.shuffleEngine(otherItems, "Exclusive/TeslaCoil.gd:34")
	itemsToAdvance.append_array(otherItems)


func onChargeReceived(_charge):
	if collectCharges:
		numCollectedCharges += 1
		setState(numCollectedCharges)
		miniActivate()
	else:
		advanceItem()


func doCooldownEffect():
	collectCharges = false
	for i in numCollectedCharges:
		advanceItem()
	
	onStateChanged(null)
	var done = (itemsToAdvance.size() < advanceItemCounter + 1)
	onAfterEffectFinished(done)
	if not done:
		activate()


func advanceItem():
	while true:
		if itemsToAdvance.size() < advanceItemCounter + 1:
			return
		
		var item = itemsToAdvance[advanceItemCounter]
		advanceItemCounter += 1
		
		if item.isCooldownActive():
			item.advanceCooldownSeconds(cdAdvance)
			# ★ np33（EATI 双侧对拍定谳，同 np27 zapItem 剥抽同构）：原版此处
			#   ObjectPool.instance(Util.zapScene)+zap.zap(...) → Zap.gd:32
			#   randf_range(4.0,4.02)=2 步——转写剥表现层时把 rng 消耗一并剥掉
			#   （隐形 +2/次）。补消耗（表现层照剥）。
			ctx.rng.randf_range(4.0, 4.02)
			
			
			if itemsToAdvance.size() < advanceItemCounter + 1:
				consumed = true
			
			miniActivate()
			return


func onStateChanged(_numCollectedCharges):
	if _numCollectedCharges == null:
		pass
	else:
		pass


func onShopEntered():
	onStateChanged(null)


func onSaleRoll(item):
	pass

func onItemRoll(descr):
	pass

func _readyInit():
	._readyInit()
	cdAdvance = getP("cdadvance")
	salesChance = getP("sales") / 100.0
	engineerWeight = getP("weight")
	pass

