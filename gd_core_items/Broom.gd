extends Weapon
var broomBonusDam = 0
var onMissReadyTime = 0.0
var bonusDamPerMiss

func onPrepare():
	connectForCombat(character(), "character_attacked", "onAttacked")


func onAttacked(damageRes):
	if not damageRes.hasHit():
		addBonusDamage(bonusDamPerMiss)
		broomBonusDam += bonusDamPerMiss





func attack(event = null):
	.attack(event)
	if broomBonusDam != 0:
		reduceBonusDamage(broomBonusDam, false)
		broomBonusDam = 0



func onDealtDamage(damageRes):
	if damageRes.hasHit():
		if rollChance():
			inflictBlind(1, damageRes.event)


func onShopEntered():
	broomBonusDam = 0

func _readyInit():
	._readyInit()
	bonusDamPerMiss = int(getP1())
