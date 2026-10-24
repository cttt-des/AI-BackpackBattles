extends Gem

const gemColor = Color(0.466766, 0.625994, 0.742188)
const stunParticles = preload("res://Items/Particles/StunParticles.tscn")

onready var debuffResistTimer = $DebuffResistTimer
onready var stunCd = getBaseCooldown()

var stunReadyTime = 0.0
var debuffResistChance: float

func prepareWeapon():
	connectForCombat(getItem(), "attacked", "onAttack")

func onAttack(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		if Util.time >= stunReadyTime:
			stunReadyTime = Util.time + stunCd
			stun(getP_m("dur_stun"), damageRes.event)
			var particles = ObjectPool.particleOneShot(stunParticles, sprite)
			particles.position = Vector2.ZERO
			miniActivate()

func prepareArmor():
	debuffResistChance = getGemPower() * getChance2()
	character().changeDebuffResistChances(debuffResistChance)

func combatStartArmor():
	debuffResistTimer.start(getP_m("dur_resist"))

func removeDebuffResistance():
	character().changeDebuffResistChances( - debuffResistChance)

func combatEndArmor():
	debuffResistTimer.stop()


func hasCooldown():
	return false

func combatStartInventory():
	giveMaxHealth()
	consume()
	
func onHotSwapHoverWithGemEnd():
	gemAnimation.play("RuneShine")

func hasInventoryDuration() -> bool:
	return false
