extends Item

onready var healthUsed: = int(getP("healtht"))
onready var effectDmg: = getP("dam") / 100.0

onready var availableBuffs = {
	Game.EventType.Mana: int(getP("mana")), 
	Game.EventType.Lucky: int(getP("luck")), 
	Game.EventType.Regeneration: int(getP("regen"))
}

func _ready():
	damageSource = DamageSource.new().setItem(self)

func doCooldownEffect():
	if character().getCurrentHealth() > healthUsed:
		var event = character().loseHealth(healthUsed, self)
		var dam = descriptor.minDam
		var res = dealEffectDamage(dam, event)
		
		var maxBuffs = getMostStacks(character(), availableBuffs.keys())
		var buffToGive = Util.pickRandomElement(maxBuffs)
		var amount = availableBuffs[buffToGive]
		giveStacks(character(), buffToGive, amount, event)
		
		
	activate()

func canAffect(item):
	return item.hasType(Type.Dark)

func onPrepare():
	var bonusEffectDmg = 0.0
	for item in getAffectedItems():
		if item.hasType(Type.Spell):
			bonusEffectDmg += effectDmg * 2.0
		else:
			bonusEffectDmg += effectDmg
	
	character().changeEffectDamageFactor(bonusEffectDmg)
