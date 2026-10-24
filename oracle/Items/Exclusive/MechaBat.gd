extends Item

onready var lifestealParticles = $Icon / LifestealParticles
onready var lifestealLight = $Icon / LifestealLight
onready var vampirism1: = int(getP("vampirism"))
onready var luckNeeded: = int(getP("luckt"))
onready var luckUsed: = int(getP("luck"))
onready var vampirism2: = int(getP("vampirism2"))
var lifestealActive: = false

func canAffect(item):
	return item.canDamage()

func doCooldownEffect():
	var numVamp: = 0
	if character().getLucky() >= luckNeeded:
		useLucky(luckUsed)
		numVamp += vampirism2
	
	if useStamina() == Character.StaminaResult.Sufficient:
		numVamp += vampirism1
	
	if numVamp > 0:
		giveVampirism(numVamp)
		activate()

func onPrepare():
	setState(false)
	connectForCombat(opponent(), "character_attacked", "onOpponentDamaged")

func onOpponentDamaged(damageRes: DamageResult):
	if lifestealActive:
		if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
			if damageRes.damageSource.origin in getAffectedItems():
				heal(ceil(damageRes.damage * getP_m("lifesteal") / 100.0), damageRes.event)

func onChargeReceived(_charge):
	if numCharges == 1:
		setState(true)

func onChargeLeft(_charge):
	if numCharges == 0:
		setState(false)

func onShopEntered():
	onStateChanged(false)

func onStateChanged(_lifestealActive):
	lifestealActive = _lifestealActive
	if lifestealActive:
		lifestealLight.show()
		lifestealParticles.activate()
	else:
		lifestealLight.hide()
		lifestealParticles.deactivate()
