extends Gem
const gemColor = Color(1.977344, 0.8, 3)
var healReduction
var buffRemoval

func doCooldownEffect():
	cleanseRandomDebuffs(1)
	activate()


func prepareWeapon():
	connectForCombat(socket.getItem(), "attacked", "onAttack")


func onAttack(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		removeRandomBuffs(buffRemoval, damageRes.event)
		miniActivate()


func prepareArmor():
	opponent().reduceHealingEfficiency(getGemPower() * healReduction)


func getBaseDescription(wrapInColor = true) -> String:
	if getRarity() == CoreConst.Rarity.Godly:
		return insertParameters(ctx.util.tra("Perfect Amethyst_DESCR"), wrapInColor)
	else:
		return .getBaseDescription(wrapInColor)

func _readyInit():
	._readyInit()
	healReduction = getP1() / 100.0
	buffRemoval = int(getP2())
