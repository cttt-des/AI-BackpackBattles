extends Gem
const gemColor = Color(0.938676, 0.24128, 0.988281)
var damageBonusApplied: bool
var debuffsInflicted: int
var weaponParticles
var healthThreshold
var damageFactor
var debuffsNeeded
var blockGain

func prepareWeapon():
	damageBonusApplied = false
	connectForCombat(opponent(), "character_damaged", "onOpponentDamaged")


func onOpponentDamaged(_healthChange, _event):
	if opponent().getRelativeHealth() < healthThreshold:
		if not damageBonusApplied:
			damageBonusApplied = true
			getItem().addBonusDamageFactor(damageFactor)
	elif damageBonusApplied:
		damageBonusApplied = false
		getItem().reduceBonusDamageFactor(damageFactor)


func combatEndWeapon():
	pass


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
	pass
	

func _readyInit():
	._readyInit()
	healthThreshold = getP1() / 100.0 - 0.0001
	damageFactor = getP2() / 100.0
	debuffsNeeded = getP3()
	blockGain = getP4()
