extends Node
var label = ""
var character_
var affected = []
var strength = 4.0
var trace
func character():
    return character_
func getP1():
    return strength
func getP2():
    return 0
func getP3():
    return 0
func getP_m(_key):
    return strength
func connectForCombat(emitter, sig, callback):
    EventBus.connectEvent(emitter, sig, self, callback)
func setState(value, _withNext = false):
    set("isFull", value)
func getAffectedItems():
    return affected
func playActivationAnimation():
    pass
func miniActivate():
    pass
func activate(_damageRes = null, _play = true, _consume = false, _animation = null):
    EventBus.emitSignal(self, "activated", [self])
func giveStamina(amount, _event = null):
    character_.curStamina += amount
    if not character_.allowStaminaOverflow:
        character_.clampStamina()
func giveEmpower(_amount, _event = null):
    pass
func heal(amount, _event = null):
    character_.curHealth = min(character_.maxHealth, character_.curHealth + amount)
func cleansePoison(_amount, _event = null):
    pass

func getTriggerPriority():
    return 0
