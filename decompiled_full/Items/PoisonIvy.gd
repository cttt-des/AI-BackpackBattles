extends Item

var damageIncreaseActive = false

onready var activationParticles = $ActivationParticles
onready var poisonPerSpike: int = getP4()

func canAffect(item):
	return item.hasType(Type.Nature)

func onPrepare():
	setState(false)
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")
	connectForCombat(opponent(), "character_poison_changed", "onOpponentPoisonChanged")

	


	
	character().changeDebuffResistChances(getChance() * getNumAffectedItems())
		

func onSpikesChanged(amount, event):
	if amount > 0:
		inflictPoison(amount * poisonPerSpike, event)
		miniActivate()

func onOpponentPoisonChanged(amount, event):
	var curPoison = opponent().getPoison()
	
	if not damageIncreaseActive and curPoison >= getP1():
		opponent().changeDamageResistance( - getP2())
		setState(true, false, event)

func onShopEntered():
	onStateChanged(false)

func onStateChanged(active):
	if active:
		activationParticles.activate()
	else:
		activationParticles.deactivate()
	
	damageIncreaseActive = active
