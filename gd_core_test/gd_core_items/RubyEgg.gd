extends DragonEgg
var reflects
var heat

func onPreCombatStart():
	giveReflectStacks(reflects)


func onCombatStart():
	doCooldownEffect(false)



func doCooldownEffect(withReflectStacks: bool = true):
	if withReflectStacks:
		giveReflectStacks(reflects)
	giveHeat(heat)
	activate()

func _readyInit():
	._readyInit()
	reflects = int(getP1())
	heat = int(getP3())
