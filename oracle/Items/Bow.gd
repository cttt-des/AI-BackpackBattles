extends Weapon
class_name Bow

onready var activationParticles = $Icon / ActivationParticles
onready var light = $Icon / Light
var affectedWeapon = null


func canAffect(item):
	return item.isWeapon()

func prepare():
	affectedWeapon = getFirstAffectedItem()
	if affectedWeapon != null:
		connectForCombat(affectedWeapon, "attacked", "onWeaponAttacked")
	.prepare()

func onWeaponAttacked(damageRes: DamageResult):
	pass

func combatEnd():
	.combatEnd()
	affectedWeapon = null
