extends Item

const pickupSound = preload("res://Assets/Sound/Wolf3.mp3")

func playPickupSound():
	Sound.playSound_process(pickupSound, - 3)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(pickupSound, volume - 6)

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)

func canAffect(item):
	return item.hasType(Type.Pet)

func onPreCombatStart():
	addBonusDamage(getP1() * getNumAffectedItems())

func doCooldownEffect():
	var res: DamageResult = dealDamage()
	activate(res)
