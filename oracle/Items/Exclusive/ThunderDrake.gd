extends Weapon

const activationSound = preload("res://Assets/Sound/Electricity2.wav")

onready var numHits: = int(getP("hits"))
onready var buffSpeed: = getP("speed") / 100.0
onready var buffTimer = $BuffTimer
onready var buffParticles = $Icon / ActivationParticles

var active: bool
var curHitCount: int
var lightningMultiplicity: Dictionary

func canAffect_lightning(item):
	return item.hasCooldown() or item.reactsToCharges()

func onPrepare():
	setState(false)
	curHitCount = 0
	lightningMultiplicity = countItemsInAffectedCells_cached(Affected.Lightning)

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		curHitCount += 1
		
		if curHitCount == numHits:
			
			
			if active:
				for item in getAffectedItems(Affected.Lightning):
					item.chargeLeft(self)
					zapItem(item)
			else:
				setState(true)
				for item in getAffectedItems(Affected.Lightning):
					item.addSpeed(buffSpeed * lightningMultiplicity[item])
					zapItem(item)
				
			buffTimer.stop()
			buffTimer.start(getP_m("dur"))
			curHitCount = 0
			Sound.playSound(activationSound)

func zapItem(item):
	item.chargeReceived(self)
	if item.hasOnChargeReceivedEffect:
		var zap = ObjectPool.instance(Util.zapScene)
		get_parent().add_child(zap)
		var targetPos = item.getGlobalCenter()
		zap.zap(global_position, targetPos, zap.ZapStyle.Small)

func onBuffEnded():
	setState(false)
	
	for item in getAffectedItems(Affected.Lightning):
		item.reduceSpeed(buffSpeed * lightningMultiplicity[item])
		item.chargeLeft(self)

func onCombatEnd():
	buffTimer.stop()

func onShopEntered():
	onStateChanged(false)

func onStateChanged(chargeActive):
	active = chargeActive
	if chargeActive:
		buffParticles.activate()
	else:
		buffParticles.deactivate()

func getCraftingOffset(forDirection):
	match forDirection:
		FaceDirection.UP:
			return Vector2( - 1, - 1)
		FaceDirection.DOWN:
			return Vector2.ZERO
		FaceDirection.LEFT:
			return Vector2( - 1, 0)
		FaceDirection.RIGHT:
			return Vector2(0, - 1)
