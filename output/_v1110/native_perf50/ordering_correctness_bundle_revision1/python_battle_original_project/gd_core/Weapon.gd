extends Item
class_name Weapon

func attack(triggerEvent = null):
	var res: CoreDamageResult = dealDamage(triggerEvent)
	activate(res)


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		attack()

func _readyInit():
	._readyInit()
	damageSource = CoreDamageSource.new().setItem(self)

