extends Item

const activationParticlesScene = preload("res://Items/Exclusive/Particles/CauldronActivationParticles.tscn")
const healColor = Color(0.384314, 0.913725, 0.423529)
const manaColor = Color(0.329412, 0.392157, 0.992157)
const heatColor = Color(0.996078, 0.458824, 0.290196)

var options: Array

func canAffect(item):
	return item.hasType(Type.Food) or item.hasType(Type.Potion)

func onPrepare():
	addSpeed(getP4() / 100.0 * getNumAffectedItems())
	options = [0, 1, 2]
	
func doCooldownEffect():
	var rng = Util.pickRandomElement(options)
	var particles = ObjectPool.particleOneShot(activationParticlesScene, sprite)
	if rng == 0:
		heal()
		particles.self_modulate = healColor
	elif rng == 1:
		giveMana(getP2())
		particles.self_modulate = manaColor
	else:
		giveHeat(getP3())
		particles.self_modulate = heatColor
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)
