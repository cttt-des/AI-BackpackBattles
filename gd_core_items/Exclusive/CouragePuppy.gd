extends Item

func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume


func canAffect(item):
	return item.hasType(CoreConst.Type.Pet)


func onPreCombatStart():
	addBonusDamage(getP1() * getNumAffectedItems())


func doCooldownEffect():
	var res: CoreDamageResult = dealDamage()
	activate(res)

func _readyInit():
	._readyInit()
	damageSource = CoreDamageSource.new().setItem(self)

