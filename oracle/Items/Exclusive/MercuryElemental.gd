extends Item

var staminaRegen: float
var staminaUsed: float
onready var poison: = int(getP("poison"))
onready var selfPoison: = int(getP("poison2"))
onready var staminaThreshold: = getP("staminat")
onready var distortion = $Distortion

func _ready():
	if ownerType == Owner.GridStorage:
		distortion.hide()
	else:
		distortion.show()

func isAffectingDistinct(color = Affected.Primary) -> bool:
	return color == Affected.Primary

func canAffect(item):
	return item.descriptor.isMeleeWeapon()

func onPrepare():
	connectForCombat(opponent(), "character_attacked", "onOpponentAttacked")
	connectForCombat(character(), "character_used_stamina", "onStaminaUsed")
	
	staminaRegen = getP("stamina") * getNumDistinctAffectedItems()
	staminaUsed = 0

func onOpponentAttacked(damageRes: DamageResult):
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
