extends Potion

onready var healthThreshold = getP1() / 100.0 - 0.0001

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)


func canDamage() -> bool:
	return true

func onTriggerPotion(triggerEvent = null):
	var dam = opponent().getDebuffStacks()
	dam *= getP2()
	dam = ceil(dam)
	dealEffectDamage(dam, triggerEvent)

func onPrepare():
	connectForCombat(opponent(), "character_damaged", "onDamaged")

func onDamaged(healthChange, event):
	if isEmpty(): return
	
	if opponent().getRelativeHealth() < healthThreshold:
		
		drink()
		
		triggerPotion(event)
		
		var affected = getAffectedItems()
		if not affected.empty():
			affected[0].triggerPotion(event)
			affected[0].miniActivate()
		
		activate()
