extends Item
const chargeCells1 = [Vector2( - 1, - 1), Vector2(0, - 2), Vector2(1, - 3), Vector2(2, - 2), Vector2(2, - 1)]
const chargeCells2 = [Vector2( - 1, 0), Vector2( - 1, 1), Vector2(0, 2), Vector2(1, 1), Vector2(2, 1)]
var hasActivated: bool
var speedMalus
var cdAdvanceBase
var cdAdvanceBonus
var healthThreshold

func canAffect(item):
	return item.hasCooldown()


func canAffect_lightning(item):
	return item.gainsBuffs() or item.reactsToCharges()


func onPrepare():
	hasActivated = false
	var item = getFirstAffectedItem()
	if item != null:
		item.reduceSpeed(speedMalus)
	
	connectForCombat(character(), "character_damaged", "onDamaged")


func onDamaged(_damage, event):
	if hasActivated: return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		hasActivated = true
		
		emitCharge()
		ctx.bus.emitSignal(self, "charge_emitted", [self])
		
		var item = getFirstAffectedItem()
		if item != null:
			var cdAdvance = cdAdvanceBase
			if not item.isWeapon():
				cdAdvance += cdAdvanceBonus
			
			item.advanceCooldownSeconds(cdAdvance)


func emitCharge(speedFactor = 1.0):
	var event = activate()
	sendCharge(getP_m("dur"), chargeCells1, speedFactor, event)
	sendCharge(getP_m("dur"), chargeCells2, speedFactor, event)



func onChargeEnteredCell(charge, cellIndex):
	changeChargedItemStat(charge, cellIndex, getChance(), getChance2())


func chargedItemStatChange(item, value):
	item.changeAmplificiationChancePercent_allBuffs(value)
		

func getTextureSize() -> Vector2:
	return Vector2.ZERO

func getSpriteOffset() -> Vector2:
	return Vector2.ZERO

func _readyInit():
	._readyInit()
	speedMalus = getP("speed") / 100.0
	cdAdvanceBase = getP("cdadvance_base")
	cdAdvanceBonus = getP("cdadvance_bonus")
	healthThreshold = getP("healtht") / 100.0 - 0.0001
