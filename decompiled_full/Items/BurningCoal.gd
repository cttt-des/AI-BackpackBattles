extends Gem

const gemColor = Color(1.5, 1, 0.7)

func canBlock():
	return false

func prepareWeapon():
	connectForCombat(socket.getItem(), "pre_deal_damage_early", "preAttack")

func preAttack(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		damageRes.damage += getP1()
		giveHeat(getP2())
		miniActivate()

func prepareArmor():
	character().changeResistStacks(Game.EventType.Cold, round(getP3() * getGemPower()))

func combatStartArmor():
	giveBlock(getBlock() * getGemPower())
	miniActivate()

func doCooldownEffect():
	giveHeat(getP4())
	cleanseRandomDebuffs(getP5())
	onAfterEffectFinished()

func onHotSwapHoverWithGemEnd():
	gemAnimation.play("NoSparkle")
