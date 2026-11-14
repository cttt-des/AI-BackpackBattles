extends Gem
const gemColor = Color(0.466766, 0.625994, 0.742188)
var stunReadyTime = 0.0
var debuffResistChance: float
var debuffResistTimer
var stunCd

func prepareWeapon():
	connectForCombat(getItem(), "attacked", "onAttack")


func onAttack(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		if ctx.time >= stunReadyTime:
			stunReadyTime = ctx.time + stunCd
			stun(getP_m("dur_stun"), damageRes.event)
			miniActivate()


func prepareArmor():
	debuffResistChance = getGemPower() * getChance2()
	character().changeDebuffResistChances(debuffResistChance)


func combatStartArmor():
	debuffResistTimer.start(getP_m("dur_resist"))


func removeDebuffResistance():
	character().changeDebuffResistChances( - debuffResistChance)


func combatEndArmor():
	debuffResistTimer.stop()



func hasCooldown():
	return false


func combatStartInventory():
	giveMaxHealth()
	consume()
	

func onHotSwapHoverWithGemEnd():
	pass


func hasInventoryDuration() -> bool:
	return false

func _readyInit():
	._readyInit()
	debuffResistTimer = newItemTimer("DebuffResistTimer", "removeDebuffResistance", false)
	stunCd = getBaseCooldown()
