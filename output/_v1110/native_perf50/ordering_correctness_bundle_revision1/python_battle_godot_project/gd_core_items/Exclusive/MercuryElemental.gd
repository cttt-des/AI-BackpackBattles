extends Item
var staminaRegen: float
var staminaUsed: float
var poison
var selfPoison
var staminaThreshold
var distortion

func isAffectingDistinct(color = CoreConst.Affected.Primary) -> bool:
	return color == CoreConst.Affected.Primary


func canAffect(item):
	return item.descriptor.isMeleeWeapon()


func onPrepare():
	connectForCombat(opponent(), "character_attacked", "onOpponentAttacked")
	connectForCombat(character(), "character_used_stamina", "onStaminaUsed")
	
	staminaRegen = getP("stamina") * getNumDistinctAffectedItems()
	staminaUsed = 0


func onOpponentAttacked(damageRes: CoreDamageResult):
	if damageRes.triggerOnAttacked():
		giveBlock(getBlock() / 100.0 * damageRes.damage)


func doCooldownEffect():
	giveStamina(staminaRegen)
	activate()


func onStaminaUsed(amount):
	staminaUsed += amount
	var ticks = floor(staminaUsed / staminaThreshold)
	if ticks > 0:
		inflictPoison(ticks * poison)
		selfInflictPoison(ticks * selfPoison)
		staminaUsed -= ticks * staminaThreshold
		miniActivate()

func _readyInit():
	._readyInit()
	poison = int(getP("poison"))
	selfPoison = int(getP("poison2"))
	staminaThreshold = getP("staminat")
	if ownerType == CoreConst.Owner.GridStorage:
		pass
	else:
		pass

