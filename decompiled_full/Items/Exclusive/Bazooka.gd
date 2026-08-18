extends Weapon

const stunParticles = preload("res://Items/Exclusive/Particles/BazookaStunParticles.tscn")

onready var heatNeeded: = int(getP("heatt"))
onready var luck: = int(getP("luck"))
onready var luckNeeded: = int(getP("luckt"))

onready var uses: = int(getP("max"))

var activationsLeft: int
var stunResistActive: bool

func onPrepare():
	activationsLeft = uses
	stunResistActive = false
	connectForCombat(character(), "character_lucky_changed", "onLuckChanged")

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		if (activationsLeft > 0 and 
			character().getHeat() >= heatNeeded):
			
			activationsLeft -= 1
			
			EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
			useHeat(heatNeeded, damageRes.event)
			giveLucky(luck, damageRes.event)
			giveBlock(getBlock(), true, damageRes.event)
			EventBus.flushLoggingQueue()
			
			stun(getP_m("dur_stun"), damageRes.event)
			character().stun(getP_m("dur_stunself"), self, damageRes.event)
			var particles = ObjectPool.particleOneShot(stunParticles, sprite)

func onLuckChanged(amount, event):
	if amount > 0 and not stunResistActive and character().getLucky() >= luckNeeded:
		character().changeStunResistance(getChance())
		stunResistActive = true
	
	elif amount < 0 and stunResistActive and character().getLucky() < luckNeeded:
		character().changeStunResistance( - getChance())
		stunResistActive = false
