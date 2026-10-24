extends Weapon

func onPrepare():
	connectForCombat(character(), "character_empower_changed", "onEmpowerChanged")

func onEmpowerChanged(amount, _event):
	changeVaryingDamage(amount * getP1())
