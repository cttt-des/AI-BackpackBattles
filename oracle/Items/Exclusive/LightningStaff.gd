extends Weapon

const activationParticleScene = preload("res://Items/Exclusive/Particles/LightningStaffActivationParticles.tscn")
const chargeCells = [Vector2(0, - 2), Vector2(1, - 2), Vector2(2, - 1), Vector2(3, - 2), Vector2(4, - 1), Vector2(5, 0), Vector2(4, 1)]

onready var manaCost: = int(getP("manat"))
onready var permDamBonus = getP("dam")
onready var chargeDamBase = getP("dam_flat")
onready var chargeDamPerTile = getP("dam_tile")
onready var numAttacks = getP("num")

var attackCounter: = 0

func onPrepare():
	attackCounter = 0

func onPreDealDamage_early(damageRes: DamageResult):
	var event = tryUseMana(manaCost)
	if event != null:
		addBonusDamage(permDamBonus)
		var activationParticles = ObjectPool.particleOneShot(activationParticleScene, self)
		activationParticles.global_position = specificDragParticles[0].global_position
	
	attackCounter += 1
	
	if attackCounter == numAttacks:
		emitCharge()
		EventBus.emitSignal(self, "charge_emitted", [self])
		attackCounter = 0

func canAffect_lightning(item):
	return item.canBeEmpowered() or item.reactsToCharges()

func emitCharge(speedFactor = 1.0):
	var event = activate(null, false)
	sendCharge(getP_m("dur"), chargeCells, speedFactor, event)

func onChargeEnteredCell(charge, cellIndex):
	changeChargedItemStat(charge, cellIndex, chargeDamBase, chargeDamPerTile)

func chargedItemStatChange(item, value):
	item.addBonusDamage(value, false)
