extends Item

const explosionSound = preload("res://Assets/Sound/Explosion1.wav")

onready var activationParticles = $ActivationParticles
onready var damFactor: = getP("dam")

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
		var removedBuffs = 0
		for buff in Game.getBuffs():
			var numStacks = character().getStacks(buff)
			removedBuffs += numStacks
			character().useStacks(buff, numStacks, self)
		EventBus.flushLoggingQueue()
		
		opponent().changeDamageResistance( - damFactor * removedBuffs)
		
		var dam = descriptor.minDam
		var damageRes = dealEffectDamage(dam)
		onAfterEffectFinished()
		activationParticles.activate()
		Sound.playSound(explosionSound)
