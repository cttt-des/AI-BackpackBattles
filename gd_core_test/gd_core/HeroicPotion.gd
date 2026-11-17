extends Potion

func onTriggerPotion(triggerEvent = null):
	giveStamina(getP1(), triggerEvent)
	giveEmpower(getP2(), triggerEvent)


func onPrepare():
	connectForCombat(character(), "character_pre_use_stamina", "checkStamina")


func checkStamina(amount):
	if OS.get_environment("GD_CHK_PROBE") != "":
		print("[CHK-G] t=", ctx.time, " amt=", amount, " isEmpty=", isEmpty(), " cur=", character().getCurrentStamina())
	if isEmpty(): return
	
	if character().getCurrentStamina() < amount:
		consumePotion()

func _readyInit():
	._readyInit()
	pass
