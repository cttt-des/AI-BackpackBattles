extends Food
var luckNeeded: int
var heatNeeded: int
var manaNeeded: int

func onCombatStart():
	giveMaxHealth()
	activate()


func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		if character().getHeat() >= heatNeeded:
			if character().getMana() >= manaNeeded:
				
				ctx.bus.setLoggingMode(ctx.bus.LoggingMode.Delayed)
				useLucky(luckNeeded)
				useHeat(heatNeeded)
				useMana(manaNeeded)
				giveEmpower(getP5())
				giveRegeneration(getP6())
				ctx.bus.flushLoggingQueue()
				
				giveMaxHealth(getP_m("maxhealth_use"))
				
	activate()

func _readyInit():
	._readyInit()
	luckNeeded = getP2()
	heatNeeded = getP3()
	manaNeeded = getP4()
