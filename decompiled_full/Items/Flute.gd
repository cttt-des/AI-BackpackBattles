extends Item

const activationParticles = preload("res://Items/Particles/FluteActivationParticles.tscn")
var options: Array

func canAffect(item):
	return true

func onPrepare():
	addSpeed(getP3() / 100.0 * getNumAffectedItems())
	options = [0, 1, 2]

func doCooldownEffect():
	var rng = Util.pickRandomElement(options)
	var particles = ObjectPool.particleOneShot(activationParticles, self)
	if rng == 0:
		giveBlock()
		particles.modulate = Color(0.87451, 0.968627, 1)
	elif rng == 1:
		giveStamina(getP1())
		particles.modulate = Color(0.952941, 0.901961, 0.145098)
	else:
		giveLucky(getP2())
		particles.modulate = Color(0.345098, 0.823529, 0.12549)
	
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)
