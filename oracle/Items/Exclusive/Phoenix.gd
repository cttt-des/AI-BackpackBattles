extends Weapon

const resurrectionPulse = preload("res://Items/Animations/ResurectionPulse.tscn")
export (Texture) var ashSprite

onready var normalSprite = sprite.texture
onready var selfDam: int = getP("selfdam")
onready var reincarnateHealth: int = getP("reincarnate_health")
var deathPrevented = false

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
			Util.createPulse(resurrectionPulse, self, global_position)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		if character().getCurrentHealth() > selfDam:
			character().loseHealth(selfDam, self)
			var res: DamageResult = dealDamage()
			activate(res)

func onShopEntered():
	onStateChanged(false)

func onStateChanged(_deathPrevented):
	if _deathPrevented:
		setTexture(ashSprite)
	else:
		setTexture(normalSprite)
	deathPrevented = _deathPrevented
