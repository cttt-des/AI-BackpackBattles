extends Gem

const gemColor = Color(0.8, 0.8, 3)

onready var manaNeeded = int(getP2())

var manaCounter = 0
var spectral = false

func doCooldownEffect():
	inflictCold(getP5())
	onAfterEffectFinished()

func prepareWeapon():
	spectral = false
	connectForCombat(socket.getItem(), "pre_deal_damage_late", "preAttack")
	connectForCombat(socket.getItem(), "attacked", "onAttack")

func preAttack(damageRes: DamageResult):
	
	spectral = rollChance()
	if spectral:
		damageRes.damageSource.makeSpectral()

func onAttack(damageRes: DamageResult):
	if spectral and damageRes.hasHit():
		giveMana(getP1(), damageRes.event)
		inflictCold(getP4(), damageRes.event)
		miniActivate()

func prepareArmor():
	manaCounter = 0
	connectForCombat(character(), "character_mana_changed", "onManaChanged")

func onManaChanged(amount, event):
	if amount > 0:
		manaCounter += amount
		var relMana = manaCounter / manaNeeded
		var block = relMana * getP3()
		manaCounter %= manaNeeded
		if block > 0:
			giveBlock(getGemPower() * block, event)
			miniActivate()
			showCooldownSmooth(relMana, true)
		else:
			showCooldownSmooth(relMana, false)
