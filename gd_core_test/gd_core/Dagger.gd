extends Weapon
class_name Dagger

func prepare():
	.prepare()
	connectForCombat(opponent(), "character_stunned", "onStun")


func onStun(triggerEvent):
	attack(triggerEvent)

func _readyInit():
	._readyInit()
	pass
