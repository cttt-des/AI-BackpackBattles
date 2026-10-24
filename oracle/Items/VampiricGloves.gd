extends Item

onready var inactiveTexture = sprite.texture
const activeTexture = preload("res://Items/Sprites/VampiricGloves_active.png")

onready var activationParticles = $Icon / ActivationParticles

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
		activationParticles.activate()
		setTexture(activeTexture)
		updateShadowTexture()
	else:
		activationParticles.deactivate()
		setTexture(inactiveTexture)
		updateShadowTexture()
		
