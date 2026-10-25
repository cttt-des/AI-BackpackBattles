extends Weapon
var buffRemoval
var buffGain
var speedPerFood

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		var buffsLeft = buffRemoval
		var ownMostBuffs = getMostStacks(character(), CoreConst.getBuffs())
		ownMostBuffs.shuffle()
		for buffType in ownMostBuffs:
			var cur = opponent().getStacks(buffType)
			var buffsRemoved = min(cur, buffsLeft)
			opponent().loseStacks(buffType, buffsRemoved, self)
			buffsLeft -= buffsRemoved
			if buffsLeft == 0:
				break
		
		var oppoMostBuffs = getMostStacks(opponent(), CoreConst.getBuffs())
		giveStacks(character(), ctx.util.pickRandomElement(oppoMostBuffs), 
			buffGain)


func canAffect(item):
	return item.hasType(CoreConst.Type.Food)


func onPrepare():
	addSpeed(speedPerFood * getNumAffectedItems())

func _readyInit():
	._readyInit()
	buffRemoval = int(getP("remove"))
	buffGain = int(getP("gain"))
	speedPerFood = getP("speed") / 100.0
