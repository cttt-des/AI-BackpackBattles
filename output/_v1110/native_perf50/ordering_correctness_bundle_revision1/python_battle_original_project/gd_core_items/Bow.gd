extends Weapon
class_name Bow
var affectedWeapon = null
var activationParticles
var light

func canAffect(item):
	return item.isWeapon()


func prepare():
	affectedWeapon = getFirstAffectedItem()
	if affectedWeapon != null:
		connectForCombat(affectedWeapon, "attacked", "onWeaponAttacked")
	.prepare()


func onWeaponAttacked(damageRes: CoreDamageResult):
	pass


func combatEnd():
	.combatEnd()
	affectedWeapon = null

func _readyInit():
	._readyInit()
	pass
