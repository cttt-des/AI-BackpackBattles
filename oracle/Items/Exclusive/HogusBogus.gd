extends Item

var phase: int
onready var maxStaminaUsed: = getP("stamina")
onready var buffsPerStamina: = getP("buffs")

func onPrepare():
	phase = 0

func trigger():
	setState(phase + 1)
	.trigger()
	


func canUseStamina() -> bool:
	return true

func doCooldownEffect():
	if phase == 1:
		var curStamina = character().getCurrentStamina()
		var step = 1.0 / buffsPerStamina
		if curStamina >= step:
			var numProccs = floor(curStamina / step)
			var staminaToUse = min(curStamina, min(numProccs * step, maxStaminaUsed))
			useStamina(staminaToUse)
			giveRandomBuffs(round(staminaToUse * buffsPerStamina))
		activate()
	
	elif phase == 2:
		stun(getP_m("dur_stun"))
		character().stun(getP_m("dur_self_stun"), self)
		activate()
	
	else:
		var curHealth = opponent().getCurrentHealth()
		heal(curHealth * getP_m("heal") / 100.0)
		onAfterEffectFinished()

func onStateChanged(_phase: int):
	phase = _phase
	if phase == 0:
		baseCooldownOverride = getBaseCooldownIndex(0)
	elif phase < 3:
		baseCooldownOverride = getBaseCooldownIndex(phase) - getBaseCooldownIndex(phase - 1)
	
