extends Gem

const gemColor = Color(1.977344, 0.8, 3)

onready var healReduction: = getP1() / 100.0
onready var buffRemoval: = int(getP2())

func doCooldownEffect():
	cleanseRandomDebuffs(1)
	activate()

func prepareWeapon():
	connectForCombat(socket.getItem(), "attacked", "onAttack")

func onAttack(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		removeRandomBuffs(buffRemoval, damageRes.event)
		miniActivate()

func prepareArmor():
	opponent().reduceHealingEfficiency(getGemPower() * healReduction)

func getBaseDescription(wrapInColor = true) -> String:
	if getRarity() == Rarity.Godly:
		return insertParameters(Util.tra("Perfect Amethyst_DESCR"), wrapInColor)
	else:
		return .getBaseDescription(wrapInColor)
