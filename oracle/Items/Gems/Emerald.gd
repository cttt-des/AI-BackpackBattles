extends Gem

const gemColor = Color(0.8, 3, 0.8)

func doCooldownEffect():
	giveRegeneration(getP3())
	onAfterEffectFinished()

func prepareWeapon():
	connectForCombat(socket.getItem(), "attacked", "onAttack")

func onAttack(damageRes: DamageResult):
	if damageRes.hasHit():
		if rollChance():
			inflictPoison(getP1(), damageRes.event)
			miniActivate()

func prepareArmor():
	character().changeResistChance(Game.EventType.Poison, getGemPower() * getP2())
