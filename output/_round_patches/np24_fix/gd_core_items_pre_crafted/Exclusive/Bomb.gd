extends Item
var activationParticles
var damFactor

func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		ctx.bus.setLoggingMode(ctx.bus.LoggingMode.Delayed)
		var removedBuffs = 0
		for buff in CoreConst.getBuffs():
			var numStacks = character().getStacks(buff)
			removedBuffs += numStacks
			character().useStacks(buff, numStacks, self)
		ctx.bus.flushLoggingQueue()
		
		opponent().changeDamageResistance( - damFactor * removedBuffs)
		
		var dam = descriptor.minDam
		var damageRes = dealEffectDamage(dam)
		onAfterEffectFinished()

func _readyInit():
	._readyInit()
	damFactor = getP("dam")
	damageSource = CoreDamageSource.new().setItem(self)

