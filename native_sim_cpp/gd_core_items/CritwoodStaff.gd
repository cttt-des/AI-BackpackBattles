extends Weapon
var buffActive = false
var activationParticles
var critTimer
var manaCost
var tempDamBonus

func onPrepare():
	setState(false)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if character().getMana() >= manaCost:
		if not buffActive:
			setState(true, true)
			for item in inventory.getItems():
				item.addCritChancePercent(100)
		
		useMana(manaCost)
		damageRes.damage += tempDamBonus
		var critBuffDur = getP_m("dur")
		ctx.util.changeTimer(critTimer, critBuffDur)


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
		pass
	else:
		pass
	
	buffActive = active

func _readyInit():
	._readyInit()
	critTimer = newItemTimer("CritBuffTimer", "buffEnded", false)
	manaCost = getP1()
	tempDamBonus = getP2()
