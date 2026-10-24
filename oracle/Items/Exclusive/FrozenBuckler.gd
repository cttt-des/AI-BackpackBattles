extends Shield

var coldInflicted: int

func onPrepare():
	coldInflicted = 0

func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	if coldInflicted < getP4():
		coldInflicted += 1
		inflictCold(getP3(), blockedDamageRes.event)
	activate()
