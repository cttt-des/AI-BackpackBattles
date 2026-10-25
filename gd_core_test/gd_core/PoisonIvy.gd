extends Item
var damageIncreaseActive = false
var activationParticles
var poisonPerSpike: int

func canAffect(item):
	return item.hasType(CoreConst.Type.Nature)


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
		pass
	else:
		pass
	
	damageIncreaseActive = active

func _readyInit():
	._readyInit()
	poisonPerSpike = getP4()
