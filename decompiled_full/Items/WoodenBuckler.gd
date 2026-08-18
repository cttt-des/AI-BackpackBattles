extends Shield

func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	activate()
