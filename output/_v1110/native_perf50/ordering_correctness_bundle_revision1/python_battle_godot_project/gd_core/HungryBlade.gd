extends Weapon
var vampirism
var regenNeeded
var vampirismForRegen

func onPrepare():
	connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")


func onCombatStart():
	giveVampirism(vampirism)
	activate(null, false, false, ActivationAni.Jump)


func onVampirismChanged(amount, _event):
	addMaxDamage(amount)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		var numRegen = character().getRegeneration()
		if numRegen >= regenNeeded:
			var event = useRegeneration(regenNeeded)
			giveVampirism(vampirismForRegen, event)
			

func _readyInit():
	._readyInit()
	vampirism = int(getP1())
	regenNeeded = int(getP2())
	vampirismForRegen = int(getP3())
