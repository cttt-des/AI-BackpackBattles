extends Gem

const gemColor = Color(0.132813, 0.132813, 0.132813)

func canBlock():
	return false

func prepareWeapon():
	connectForCombat(socket.getItem(), "pre_deal_damage_early", "preAttack")

func preAttack(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		damageRes.damage += getP1()
		miniActivate()

func prepareArmor():
	character().changeDebuffResistStacks(round(getGemPower()))

func combatStartArmor():
	giveBlock(round(getGemPower() * getBlock()))
	miniActivate()

func doCooldownEffect():
	giveRandomBuffs(1)
	inflictRandomDebuffs(1)
	onAfterEffectFinished()

func onHotSwapHoverWithGemEnd():
	gemAnimation.play("NoSparkle")
