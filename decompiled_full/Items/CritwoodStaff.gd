extends Weapon

const activationPulse = preload("res://Items/Animations/CritPulse.tscn")

onready var activationParticles = $ActivationParticles
onready var critTimer = $CritBuffTimer
onready var manaCost = getP1()
onready var tempDamBonus = getP2()

var buffActive = false

func onPrepare():
	setState(false)

func onPreDealDamage_early(damageRes: DamageResult):
	if character().getMana() >= manaCost:
		if not buffActive:
			setState(true, true)
			for item in inventory.getItems():
				item.addCritChancePercent(100)
		
		useMana(manaCost)
		damageRes.damage += tempDamBonus
		var critBuffDur = getP_m("dur")
		Util.changeTimer(critTimer, critBuffDur)
		Util.createPulse(activationPulse, self, $Icon / PulsePosition.global_position)

func buffEnded():
	for item in inventory.getItems():
		item.reduceCritChancePercent(100)
	setState(false)

func onCombatEnd():
	critTimer.stop()

func onShopEntered():
	onStateChanged(false)

func onStateChanged(active):
	if active:
		activationParticles.activate()
	else:
		activationParticles.deactivate()
	
	buffActive = active
