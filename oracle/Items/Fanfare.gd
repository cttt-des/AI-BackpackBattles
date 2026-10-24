extends Item

const empowerParticles = preload("res://Items/Particles/FanfareActivationParticles.tscn")
const staminaParticles = preload("res://Items/Particles/FanfareStunParticles.tscn")
const manaParticles = preload("res://Items/Particles/FanfareManaParticles.tscn")

var options: Array

func canAffect(item):
	return true
















func onPrepare():
	addSpeed(getP5() / 100.0 * getNumAffectedItems())
	options = [0, 1, 2]

func doCooldownEffect():
	var rng = Util.pickRandomElement(options)
	if rng == 0:
		giveEmpower(getP1())
		ObjectPool.particleOneShot(empowerParticles, self)
	elif rng == 1:
		giveMana(getP2())
		removeMana(getP3())
		ObjectPool.particleOneShot(manaParticles, self)
	else:
		drainStamina(getP4())
		ObjectPool.particleOneShot(staminaParticles, self)
	
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)
