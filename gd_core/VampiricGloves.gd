extends Item
var inactiveTexture
var activationParticles

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	setState(false)


func doCooldownEffect():
	setState(true)
	giveVampirism(getP1())
	var bonusSpeed = getP2() / 100
	for item in getAffectedItems():
		item.addSpeed(bonusSpeed)
	onAfterEffectFinished()


func onShopEntered():
	onStateChanged(false)


func onStateChanged(active):
	if active:
		updateShadowTexture()
	else:
		updateShadowTexture()
		

func _readyInit():
	._readyInit()
	pass
