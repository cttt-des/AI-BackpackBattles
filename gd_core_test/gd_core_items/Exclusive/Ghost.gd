extends Item
var unhealing
var activationParticles

func onPrepare():
	character().giveUnhealing(unhealing)


func doCooldownEffect():
	var useEvents = useRandomBuffs(1)
	if useEvents != null:
		heal(getP_m("heal"), useEvents[0])
	activate()


func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

func _readyInit():
	._readyInit()
	unhealing = getP("unhealing") / 100.0
