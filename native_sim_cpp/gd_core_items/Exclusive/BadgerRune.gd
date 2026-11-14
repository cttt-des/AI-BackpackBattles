extends Gem
const gemColor = Color(0.845703, 0.420593, 0.062767)
var attackSpeedBonus
var damageReduction: int
var staminaReduction

func isBattleRageItem() -> bool:
	return getGemMode() == GemMode.Armor


func prepareWeapon():
	connectForCombat(getItem(), "attacked", "onAttack")


func onAttack(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		getItem().addSpeed(attackSpeedBonus)
		miniActivate()


func prepareArmor():
	connectForCombat(character(), "pre_take_damage", "preTakeDamage")


func preTakeDamage(damageRes: CoreDamageResult):
	if damageRes.triggerOnAttacked() and character().isBattleRaging():
		damageRes.applyDamageReduction(round(getGemPower() * damageReduction), self)
		miniActivate()


func hasCooldown():
	return false


func prepareInventory():
	for item in inventory.getItems():
		
		item.changeStaminaFactor( - staminaReduction)
	










func onHotSwapHoverWithGemEnd():
	pass

func _readyInit():
	._readyInit()
	attackSpeedBonus = getP("attackspeed") / 100.0
	damageReduction = getP("damreduction")
	staminaReduction = getP("stamina")
