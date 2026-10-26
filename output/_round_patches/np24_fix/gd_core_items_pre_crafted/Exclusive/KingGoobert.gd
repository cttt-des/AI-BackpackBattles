extends Goobert
var invuCharges: int
enum CrownState{
	Inactive, 
	Active, 
	Used
}
var protectedBuffs
var manaCost
var activationParticles
var buffTimer
var light

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
		pass
	
	elif _crownState == CrownState.Active:
		pass
	
	else:
		pass

func _readyInit():
	._readyInit()
	protectedBuffs = getP("buffs")
	manaCost = getP("mana")
	buffTimer = newItemTimer("BuffTimer", "buffEnded", false)
