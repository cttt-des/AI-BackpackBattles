extends Item
class_name Weapon

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)

func attack(triggerEvent = null):
	var res: DamageResult = dealDamage(triggerEvent)
	activate(res)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		attack()
