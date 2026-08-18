extends Gem

onready var weaponParticles = $ActivationParticles
const gemColor = Color(0.938676, 0.24128, 0.988281)


onready var healthThreshold = getP1() / 100.0 - 0.0001
onready var damageFactor = getP2() / 100.0
var damageBonusApplied: bool


onready var debuffsNeeded = getP3()
onready var blockGain = getP4()
var debuffsInflicted: int

func prepareWeapon():
	damageBonusApplied = false
	connectForCombat(opponent(), "character_damaged", "onOpponentDamaged")

func onOpponentDamaged(_healthChange, _event):
	if opponent().getRelativeHealth() < healthThreshold:
		if not damageBonusApplied:
			damageBonusApplied = true
			getItem().addBonusDamageFactor(damageFactor)
			weaponParticles.activate()
	elif damageBonusApplied:
		damageBonusApplied = false
		getItem().reduceBonusDamageFactor(damageFactor)
		weaponParticles.deactivate()

func combatEndWeapon():
	weaponParticles.deactivate()

func prepareArmor():
	debuffsInflicted = 0
	connectToOpponentDebuffs("onOpponentDebuffsChanged")

func onOpponentDebuffsChanged(amount, event):
	if amount > 0:
		if event.getOrigin() is Item and event.getOrigin().character() == character():
			debuffsInflicted += amount
			var activations = int(debuffsInflicted / debuffsNeeded)
			debuffsInflicted %= int(debuffsNeeded)
			if activations > 0:
				giveBlock(getGemPower() * blockGain * activations, true, event)
				miniActivate()








func doCooldownEffect():
	opponent().addFatigueDamage(1)
	opponent().takeFatigueDamage(self)
	activate()

func onHotSwapHoverWithGemEnd():
	
	gemAnimation.play("CorruptedSparkle")
