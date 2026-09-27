extends Weapon
var active: bool
var curHitCount: int
var lightningMultiplicity: Dictionary
var numHits
var buffSpeed
var buffTimer
var buffParticles

func canAffect_lightning(item):
	return item.hasCooldown() or item.reactsToCharges()


func onPrepare():
	setState(false)
	curHitCount = 0
	lightningMultiplicity = countItemsInAffectedCells_cached(CoreConst.Affected.Lightning)


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		curHitCount += 1
		
		if curHitCount == numHits:
			
			
			if active:
				for item in getAffectedItems(CoreConst.Affected.Lightning):
					item.chargeLeft(self)
					zapItem(item)
			else:
				setState(true)
				for item in getAffectedItems(CoreConst.Affected.Lightning):
					item.addSpeed(buffSpeed * lightningMultiplicity[item])
					zapItem(item)
				
			buffTimer.stop()
			buffTimer.start(getP_m("dur"))
			curHitCount = 0


func zapItem(item):
	item.chargeReceived(self)
	if item.hasOnChargeReceivedEffect:
		var targetPos = item.getGlobalCenter()


func onBuffEnded():
	setState(false)
	
	for item in getAffectedItems(CoreConst.Affected.Lightning):
		item.reduceSpeed(buffSpeed * lightningMultiplicity[item])
		item.chargeLeft(self)


func onCombatEnd():
	buffTimer.stop()


func onShopEntered():
	onStateChanged(false)


func onStateChanged(chargeActive):
	active = chargeActive
	if chargeActive:
		pass
	else:
		pass


func getCraftingOffset(forDirection):
	match forDirection:
		CoreConst.FaceDirection.UP:
			return Vector2( - 1, - 1)
		CoreConst.FaceDirection.DOWN:
			return Vector2.ZERO
		CoreConst.FaceDirection.LEFT:
			return Vector2( - 1, 0)
		CoreConst.FaceDirection.RIGHT:
			return Vector2(0, - 1)

func _readyInit():
	._readyInit()
	numHits = int(getP("hits"))
	buffSpeed = getP("speed") / 100.0
	buffTimer = newItemTimer("BuffTimer", "onBuffEnded", false)
