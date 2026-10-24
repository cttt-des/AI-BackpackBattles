extends Weapon

var lastSpeedBonus = 0.0

func canAffect(item):
	return item.gainsStack(Stack.Vampirism)

func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(Game.EventType.Vampirism, 1)
	connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")

func onVampirismChanged(_amount, _event):
	var scytheSpeedBonus = min(getP1() * character().getVampirism(), getP2())
	scytheSpeedBonus /= 100.0
	addSpeed(scytheSpeedBonus - lastSpeedBonus)
	lastSpeedBonus = scytheSpeedBonus

func onShopEntered():
	lastSpeedBonus = 0.0
