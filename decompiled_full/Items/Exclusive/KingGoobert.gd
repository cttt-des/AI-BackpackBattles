extends Goobert

const activationPulse = preload("res://Items/Animations/BookOfLightActivationPulse.tscn")

onready var protectedBuffs = getP("buffs")
onready var manaCost = getP("mana")
onready var activationParticles = $ActivationParticles
onready var buffTimer = $BuffTimer
onready var light = $Icon / CircleLight

var invuCharges: int

enum CrownState{
	Inactive, 
	Active, 
	Used
}

func prepare():
	var gemPower = getP("gempower") / 100.0
	for gem in getGemsNoNull():
		gem.changeGemPower(gemPower)
	
	invuCharges = getP("charges")
	setState(CrownState.Inactive)
	.prepare()

func doCooldownEffect():
	character().changeBuffProtectStacks(protectedBuffs)
	heal()
	if invuCharges > 0 and character().isVulnerable() and checkMana(manaCost):
		invuCharges -= 1
		setState(CrownState.Active, true)
		var invuDur = getP_m("dur_invu")
		var event = character().makeInvulnerable(invuDur, self)
		buffTimer.start(invuDur)
		useMana(manaCost, event)
		Util.createPulse(activationPulse, self, global_position)

func buffEnded():
	if invuCharges > 0:
		setState(CrownState.Inactive, true)
	else:
		setState(CrownState.Used, true)

func onCombatEnd():
	buffTimer.stop()

func onShopEntered():
	onStateChanged(CrownState.Inactive)

func onStateChanged(_crownState):
	if _crownState == CrownState.Inactive:
		activationParticles.deactivate()
		light.self_modulate = Color.white
		light.show()
	
	elif _crownState == CrownState.Active:
		activationParticles.activate()
		light.self_modulate = Color(1.3, 1.3, 1.3, 1)
		light.show()
	
	else:
		activationParticles.deactivate()
		light.hide()
