extends Gem

const gemColor = Color(0.912109, 0.904984, 0.904984)

onready var healthThreshold: = getP1() / 100.0 - 0.0001
var activated: bool

func prepareInventory():
	activated = false
	connectForCombat(opponent(), "character_damaged", "onOpponentDamaged")

func onOpponentDamaged(_healthChange, event):
	if not activated:
		if opponent().getRelativeHealth() <= healthThreshold:
			activated = true
			heal(getP_m("heal"), event)
			giveEmpower(getP3(), event)
			activate()

func prepareWeapon():
	connectForCombat(socket.getItem(), "attacked", "onAttack")

func onAttack(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance2():
		stealRandomBuff(1)
		miniActivate()

func prepareArmor():
	character().changeDebuffResistChances(getGemPower() * getChance())
	character().changeCritResistance(getGemPower() * getChance())

func hasCooldown():
	return false
