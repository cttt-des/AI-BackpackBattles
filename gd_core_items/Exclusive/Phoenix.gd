extends Weapon
export (Texture) var ashSprite
var deathPrevented = false
var normalSprite
var selfDam: int
var reincarnateHealth: int

func onPrepare():
	setState(false)
	connectForCombat(character(), "character_damaged", "onDamaged")


func onDamaged(_damage, event):
	if deathPrevented:
		return
	
	if character().getCurrentHealth() <= 0:
		var heat = character().getHeat()
		if heat > 0:
			setState(true)
			
			var event2 = character().reincarnate(reincarnateHealth * heat, false, self, event)
			useHeat(heat, event2)
			activate()


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		if character().getCurrentHealth() > selfDam:
			character().loseHealth(selfDam, self)
			var res: CoreDamageResult = dealDamage()
			activate(res)


func onShopEntered():
	onStateChanged(false)


func onStateChanged(_deathPrevented):
	if _deathPrevented:
		pass
	else:
		pass
	deathPrevented = _deathPrevented

func _readyInit():
	._readyInit()
	selfDam = getP("selfdam")
	reincarnateHealth = getP("reincarnate_health")
