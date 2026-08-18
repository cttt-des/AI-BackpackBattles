extends Item

onready var regenNeeded: = int(getP("regent"))
onready var numStealedBuffs: = int(getP("buffsteal"))
onready var fillAnimation = $Icon / AnimationPlayer

var activated: = false

func canAffect(item):
	return item.hasType(Type.Dark)

func onPrepare():
	setState(false)
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")
	addSpeed(getNumAffectedItems() * getP("darkspeed") / 100.0)
	
func doCooldownEffect():
	stealRandomBuff(numStealedBuffs, null, Game.getBuffs(), Game.EventType.Regeneration)
	activate()

func onRegenChanged(amount, event):
	if amount > 0 and not activated and character().getRegeneration() >= regenNeeded:
		setState(true, true)
		useRegeneration(regenNeeded, event)
		giveMaxHealth(getP_m("maxhealth"), event)
		giveEmpower(getP("empower"), event)
		opponent().reduceHealingEfficiency(getP("healreduction") / 100.0)

func onShopEntered():
	onStateChanged(false)

func getTriggerPriority() -> int:
	return Priority.High

func onStateChanged(filled):
	if activated == filled: return
	activated = filled
	
	if filled:
		fillAnimation.play("Appear")
		fillAnimation.queue("Idle")
	else:
		fillAnimation.play("Disappear")
