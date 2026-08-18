extends Gem

const gemColor = Color(2, 1.8, 0.8)

func prepareInventory():
	character().giveStaminaRegeneration(getP2() / 100.0)

func prepareWeapon():
	socket.getItem().addSpeed(getP1() / 100)

func prepareArmor():
	character().changeStunResistance(getGemPower() * getChance())
	character().changeCritResistance(getGemPower() * getChance2())
