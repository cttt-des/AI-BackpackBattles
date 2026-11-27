extends Weapon
var extraAccuracy
var battleRageSpeed

func canAffect(item):
	return item.canDamage()


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		addCritChancePercent(getChance2())
		addAccuracy(extraAccuracy)
		for item in getAffectedItems():
			item.addCritChancePercent(getChance2())
			if item.isWeapon():
				item.addAccuracy(extraAccuracy)
		if rollChance():
			stun(getP_m("dur_stun"), damageRes.event)


func onPrepare():
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")


func onBattleRageStarted(_event):
	addSpeed(battleRageSpeed)


func onBattleRageEnded(_event):
	reduceSpeed(battleRageSpeed)

func _readyInit():
	._readyInit()
	extraAccuracy = getP2()
	battleRageSpeed = getP4() / 100.0
