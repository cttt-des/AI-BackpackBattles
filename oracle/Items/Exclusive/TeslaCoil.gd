extends Item

onready var cdAdvance: = getP("cdadvance")
onready var salesChance: = getP("sales") / 100.0
onready var engineerWeight: = getP("weight")
onready var chargeCounter = $ChargeCounter

var itemsToAdvance: Array
var numCollectedCharges: = 0
var advanceItemCounter: = 0
var collectCharges: = true

func _ready():
	chargeCounter.hide()

func canAffect(item):
	return item.hasCooldown()

func onPrepare():
	chargeCounter.rect_rotation = - global_rotation_degrees
	setState(0)
	collectCharges = true
	numCollectedCharges = 0
	advanceItemCounter = 0
	itemsToAdvance = getAffectedItems().duplicate()
	itemsToAdvance.shuffle()
	
	var otherItems = []
	for item in inventory.getItems():
		if item != self and not item in itemsToAdvance:
			if item.hasCooldown():
				otherItems.push_back(item)
	
	otherItems.shuffle()
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
			
			var zap = ObjectPool.instance(Util.zapScene)
			get_parent().add_child(zap)
			zap.zap(specificDragParticles[0].global_position, item.global_position)
			
			if itemsToAdvance.size() < advanceItemCounter + 1:
				consumed = true
			
			miniActivate()
			return

func onStateChanged(_numCollectedCharges):
	if _numCollectedCharges == null:
		chargeCounter.hide()
	else:
		chargeCounter.show()
		chargeCounter.text = str(_numCollectedCharges)

func onShopEntered():
	onStateChanged(null)

func onSaleRoll(item):
	if item != null and item.isClassItem(Game.Classes_Full.Engineer):
		Game.shopSceneNode.addBonusSalesChance(salesChance)

func onItemRoll(descr):
	if descr.isClassItem() and descr.isAvailableFor(Game.Classes_Full.Engineer):
		ItemBook.multiplyWeight(engineerWeight)
