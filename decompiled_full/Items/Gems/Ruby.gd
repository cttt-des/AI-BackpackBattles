extends Gem

const gemColor = Color(3, 0.8, 0.8)

func doCooldownEffect():
	stealLife(getP3(), getP_m("lifesteal_factor") / 100.0)
	onAfterEffectFinished()

func prepareWeapon():
	connectForCombat(socket.getItem(), "attacked", "onAttack")

func onAttack(damageRes: DamageResult):
	if damageRes.hasHit():
		heal(ceil(damageRes.damage * getP_m("lifesteal_weapon") / 100.0), damageRes.event)
		miniActivate()

func prepareArmor():
	character().addHealingEfficiency(getGemPower() * getP2() / 100.0)
