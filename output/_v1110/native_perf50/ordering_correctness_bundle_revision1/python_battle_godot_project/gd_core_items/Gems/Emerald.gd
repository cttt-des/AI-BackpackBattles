extends Gem
const gemColor = Color(0.8, 3, 0.8)

func doCooldownEffect():
	giveRegeneration(getP3())
	onAfterEffectFinished()


func prepareWeapon():
	connectForCombat(socket.getItem(), "attacked", "onAttack")


func onAttack(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if rollChance():
			inflictPoison(getP1(), damageRes.event)
			miniActivate()


func prepareArmor():
	character().changeResistChance(CoreConst.EventType.Poison, getGemPower() * getP2())

func _readyInit():
	._readyInit()
	pass
