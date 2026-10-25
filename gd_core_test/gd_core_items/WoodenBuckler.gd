extends Shield

func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	activate()

func _readyInit():
	._readyInit()
	pass
