extends Weapon
var activationsLeft: int
var stunResistActive: bool
var heatNeeded
var luck
var luckNeeded
var uses

func onPrepare():
	activationsLeft = uses
	stunResistActive = false
	connectForCombat(character(), "character_lucky_changed", "onLuckChanged")


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if (activationsLeft > 0 and 
			character().getHeat() >= heatNeeded):
			
			activationsLeft -= 1
			
			ctx.bus.setLoggingMode(ctx.bus.LoggingMode.Delayed)
			useHeat(heatNeeded, damageRes.event)
			giveLucky(luck, damageRes.event)
			giveBlock(getBlock(), true, damageRes.event)
			ctx.bus.flushLoggingQueue()
			
			stun(getP_m("dur_stun"), damageRes.event)
			character().stun(getP_m("dur_stunself"), self, damageRes.event)


func onLuckChanged(amount, event):
	if amount > 0 and not stunResistActive and character().getLucky() >= luckNeeded:
		character().changeStunResistance(getChance())
		stunResistActive = true
	
	elif amount < 0 and stunResistActive and character().getLucky() < luckNeeded:
		character().changeStunResistance( - getChance())
		stunResistActive = false

func _readyInit():
	._readyInit()
	heatNeeded = int(getP("heatt"))
	luck = int(getP("luck"))
	luckNeeded = int(getP("luckt"))
	uses = int(getP("max"))
