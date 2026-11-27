extends Node
var curStamina = 0.0
var maxStamina = 2.0
var temporaryMaxStamina = 0.0
var allowStaminaOverflow = false
var curHealth = 40.0
var maxHealth = 100.0
enum StaminaResult { Sufficient, Insufficient }
func getCurrentStamina():
    return curStamina
func getRelativeHealth():
    return curHealth / maxHealth
func getMaxStamina():
	return maxStamina + temporaryMaxStamina
func clampStamina():
	curStamina = clamp(curStamina, 0, getMaxStamina())
func useStamina(amount):
	allowStaminaOverflow = true
	EventBus.emitSignal(self, "character_pre_use_stamina", [amount])
	allowStaminaOverflow = false
	
	if curStamina >= amount:
		curStamina = max(curStamina - amount, 0)
		clampStamina()
		EventBus.emitSignal(self, "character_used_stamina", [amount])
		
		return StaminaResult.Sufficient
	else:
		clampStamina()
		
		return StaminaResult.Insufficient
