extends DragonEgg

onready var reflects: = int(getP1())
onready var heat: = int(getP3())

func onPreCombatStart():
	giveReflectStacks(reflects)

func onCombatStart():
	doCooldownEffect(false)


func doCooldownEffect(withReflectStacks: bool = true):
	if withReflectStacks:
		giveReflectStacks(reflects)
	giveHeat(heat)
	activate()
