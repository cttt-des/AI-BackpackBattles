extends Weapon

onready var buffRemoval: = int(getP("remove"))
onready var buffGain: = int(getP("gain"))
onready var speedPerFood: = getP("speed") / 100.0

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		var buffsLeft = buffRemoval
		var ownMostBuffs = getMostStacks(character(), Game.getBuffs())
		ownMostBuffs.shuffle()
		for buffType in ownMostBuffs:
			var cur = opponent().getStacks(buffType)
			var buffsRemoved = min(cur, buffsLeft)
			opponent().loseStacks(buffType, buffsRemoved, self)
			buffsLeft -= buffsRemoved
			if buffsLeft == 0:
				break
		
		var oppoMostBuffs = getMostStacks(opponent(), Game.getBuffs())
		giveStacks(character(), Util.pickRandomElement(oppoMostBuffs), 
			buffGain)

func canAffect(item):
	return item.hasType(Type.Food)

func onPrepare():
	addSpeed(speedPerFood * getNumAffectedItems())
