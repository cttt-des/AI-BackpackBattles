extends SpiritCompanion

const pickupSound = preload("res://Assets/Sound/Owl1.ogg")
const dropSound = preload("res://Assets/Sound/Owl2.ogg")

onready var manaNeeded: = int(getP("manat"))
onready var mana: = int(getP("mana"))
onready var fatigueMana: = int(getP("fatiguemana"))

func canAffect(item):
	return item.gainsBuffs()

func onPrepare():
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent_allBuffs(getChance())
	
func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		if Game.combatTimer.hasFatigueStarted():
			giveMana(fatigueMana, event)
		else:
			giveMana(mana, event)
	activate()

func playPickupSound():
	Sound.playSound_process(pickupSound, - 12, Util.randPitch(0.1))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 18, Util.randPitch(0.1))
