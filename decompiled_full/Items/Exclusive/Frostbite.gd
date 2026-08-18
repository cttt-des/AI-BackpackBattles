extends Weapon

const activationParticles = preload("res://Items/Exclusive/Particles/FrostbiteActivationParticles.tscn")

var gaveVampirism: bool

onready var damagePerCold = getP2()
onready var coldNeeded: = int(getP3())
onready var vampirism: = int(getP4())

func onPrepare():
	gaveVampirism = false
	connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")
	connectForCombat(opponent(), "character_cold_changed", "onOpponentColdChanged")

func onVampirismChanged(amount, _event):
	changeVaryingDamage(amount)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		inflictCold(getP1())
		ObjectPool.particleOneShot(activationParticles, sprite)

func onOpponentColdChanged(amount, event):
	changeVaryingDamage(damagePerCold * amount)
	
	if not gaveVampirism and opponent().getCold() >= coldNeeded:
		gaveVampirism = true
		giveVampirism(vampirism, event)
