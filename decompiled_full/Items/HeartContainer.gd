extends Item

onready var regenNeeded: = int(getP2())
onready var fillAnimation = $Icon / AnimationPlayer

var activated: = false

func onPrepare():
	setState(false)
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")

func doCooldownEffect():
	giveRegeneration(getP1())
	activate()

func onRegenChanged(amount, event):
	if amount > 0 and not activated and character().getRegeneration() >= regenNeeded:
		setState(true, true)
		useRegeneration(regenNeeded, event)
		giveMaxHealth(getP_m("maxhealth"), event)
		giveEmpower(getP4(), event)
		character().addHealingEfficiency(getP5() / 100.0)

func onShopEntered():
	onStateChanged(false)

func onStateChanged(filled):
	if activated == filled: return
	activated = filled
	
	if filled:
		fillAnimation.play("Appear")
		fillAnimation.queue("Idle")
	else:
		fillAnimation.play("Disappear")
