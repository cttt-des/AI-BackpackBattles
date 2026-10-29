extends Item
var poison
var luckPerPet

func canAffect(item):
	return item.hasType(CoreConst.Type.Pet)


func onPrepare():
	connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")


func onCombatStart():
	var numPets = getNumAffectedItems()
	giveLucky(numPets * luckPerPet)
	giveMaxHealth(numPets * getP_m("maxhealth"))
	activate()


func onLuckyChanged(amount, event):
	var protectChance = amount * getChance()
	opponent().changeProtectionChance(CoreConst.EventType.Poison, protectChance)


func doCooldownEffect():
	inflictPoison(poison)
	activate()


func playPickupSound():
	var pitch = ctx.rng.randf_range(0.9, 1.1)


func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = ctx.rng.randf_range(0.9, 1.1)






































func _readyInit():
	._readyInit()
	poison = getP("poison")
	luckPerPet = getP("luck")
