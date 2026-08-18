extends Weapon

var critBonusActive = false
onready var poisonThreshold: int = getP1()
onready var activationParticles = $Icon / ActivationParticles

func canAffect(item):
	return item.gainsStack(Stack.Poison)

func onPrepare():
	setState(false)
	connectForCombat(opponent(), "character_poison_changed", "onOpponentPoisonChanged")
	for item in getAffectedItems():
		item.giveBuffPower(Game.EventType.Poison, 1)

func onOpponentPoisonChanged(_amount, _event):
	var curPoison = opponent().getPoison()
	
	if not critBonusActive and curPoison >= poisonThreshold:
		setState(true)
		changeCritChancePercent(getChance())
		activationParticles.activate()
	
func onShopEntered():
	onStateChanged(false)

func onStateChanged(_critBonusActive):
	if _critBonusActive:
		activationParticles.activate()
	else:
		activationParticles.deactivate()
	critBonusActive = _critBonusActive
