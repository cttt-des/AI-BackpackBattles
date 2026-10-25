extends "res://gd_core_items/Crown.gd"

func prepare():
	var gemPower = getP("gempower") / 100.0
	for gem in getGemsNoNull():
		gem.changeGemPower(gemPower)
	.prepare()



func doCooldownEffect():
	character().changeBuffProtectStacks(1)
	heal()
	activate()


func getTriggerPriority() -> int:
	return CoreConst.Priority.Normal + 1

func _readyInit():
	._readyInit()
	pass
