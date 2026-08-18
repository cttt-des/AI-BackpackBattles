extends Food

const activationParticlesScene = preload("res://Items/Particles/GingerbreadManParticles.tscn")
onready var luckNeeded: int = getP2()
onready var heatNeeded: int = getP3()
onready var manaNeeded: int = getP4()

func onCombatStart():
	giveMaxHealth()
	activate()

func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		if character().getHeat() >= heatNeeded:
			if character().getMana() >= manaNeeded:
				
				EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
				useLucky(luckNeeded)
				useHeat(heatNeeded)
				useMana(manaNeeded)
				giveEmpower(getP5())
				giveRegeneration(getP6())
				EventBus.flushLoggingQueue()
				
				giveMaxHealth(getP_m("maxhealth_use"))
				var activationParticles = ObjectPool.particleOneShot(activationParticlesScene, self)
				activationParticles.global_rotation = 0
				
	activate()
