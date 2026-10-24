extends Weapon

var attackCounter = 0
var lastSpeedBonus = 0.0

onready var speedPerSpike = getP1()
onready var numHits: = int(getP3())

func onPrepare():
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")

func onSpikesChanged(_amount, _event):
	var clawsBonus = min(speedPerSpike * character().getSpikes(), getP2())
	clawsBonus /= 100.0
	addSpeed(clawsBonus - lastSpeedBonus)
	lastSpeedBonus = clawsBonus

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		attackCounter += 1
		if attackCounter == numHits:
			giveEmpower(1)
			attackCounter = 0

func onShopEntered():
	lastSpeedBonus = 0.0
	attackCounter = 0
