extends Item

const pickupSound = preload("res://Assets/Sound/Snake1.wav")
const dropSound = preload("res://Assets/Sound/Snake2.wav")

onready var poison = getP("poison")
onready var luckPerPet = getP("luck")

func canAffect(item):
	return item.hasType(Type.Pet)

func onPrepare():
	connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")

func onCombatStart():
	var numPets = getNumAffectedItems()
	giveLucky(numPets * luckPerPet)
	giveMaxHealth(numPets * getP_m("maxhealth"))
	activate()

func onLuckyChanged(amount, event):
	var protectChance = amount * getChance()
	opponent().changeProtectionChance(Game.EventType.Poison, protectChance)

func doCooldownEffect():
	inflictPoison(poison)
	activate()

func playPickupSound():
	var pitch = Util.rng.randf_range(0.9, 1.1)
	Sound.playSound_process(pickupSound, - 0, pitch)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = Util.rng.randf_range(0.9, 1.1)
	Sound.playSound(pickupSound, volume - 0, pitch)






































