extends Weapon
const chargeCells = [Vector2(0, - 2), Vector2(1, - 2), Vector2(2, - 1), Vector2(3, - 2), Vector2(4, - 1), Vector2(5, 0), Vector2(4, 1)]
var attackCounter: = 0
var manaCost
var permDamBonus
var chargeDamBase
var chargeDamPerTile
var numAttacks

func onPrepare():
	attackCounter = 0


func onPreDealDamage_early(damageRes: CoreDamageResult):
	var event = tryUseMana(manaCost)
	if event != null:
		addBonusDamage(permDamBonus)
	
	attackCounter += 1
	
	if attackCounter == numAttacks:
		emitCharge()
		ctx.bus.emitSignal(self, "charge_emitted", [self])
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

func _readyInit():
	._readyInit()
	manaCost = int(getP("manat"))
	permDamBonus = getP("dam")
	chargeDamBase = getP("dam_flat")
	chargeDamPerTile = getP("dam_tile")
	numAttacks = getP("num")
