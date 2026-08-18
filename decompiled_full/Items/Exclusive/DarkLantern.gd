extends Item

const resurrectionPulse = preload("res://Items/Animations/DarkResurectionPulse.tscn")
const usedSprite = preload("res://Items/Exclusive/Sprites/DarkLantern_used.png")

onready var normalSprite = sprite.texture
onready var invuTimer = $InvuTimer
onready var lanternLight = $Icon / Light

var deathPrevented = false

func _ready():
	
	damageSource = DamageSource.new().setItem(self)
	
func canAffect(item):
	return item.hasType(Type.Fire)

func canAffect_secondary(item):
	return item.hasType(Type.Dark)

func onPrepare():
	setState(false)
	connectForCombat(character(), "character_damaged", "onDamaged")
	connectForCombat(character(), "reincarnated", "onReincarnate")

func onDamaged(_damage, event):
	if deathPrevented:
		return
	
	if character().getCurrentHealth() <= 0:
		setState(true)
		var duration = getP_m("dur_invu")
		invuTimer.start(duration)
		character().makeInvulnerable(duration, self, event)
		var healAmount = round(getP2() / 100.0 * character().getMaxHealth())
		var event2 = character().reincarnate(healAmount, false, self, event)
		
		activate()
		Util.createPulse(resurrectionPulse, self, global_position)
	
func onCombatStart():
	character().loseHealth(getP1() / 100.0 * character().getMaxHealth(), self)
	
	
	activate()

func onReincarnate(event):
	var dam = getMinDamage() * getNumAffected_type(Type.Fire)
	if dam > 0:
		var damageRes = dealEffectDamage(dam, event)
	
	var numDebuffs: int = getP5() * getNumAffectedItems(Affected.Secondary)
	inflictRandomDebuffs(numDebuffs, event)
	
	
	
func invuEnded():
	pass
	

func onCombatEnd():
	invuTimer.stop()
	

func getTriggerPriority() -> int:
	return Priority.High

func onShopEntered():
	onStateChanged(false)

func onStateChanged(_deathPrevented: bool):
	deathPrevented = _deathPrevented
	if deathPrevented:
		lanternLight.hide()
		sprite.texture = usedSprite
	else:
		lanternLight.show()
		sprite.texture = normalSprite
