extends Item

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		var res = dealDamage()
		activate(res)
