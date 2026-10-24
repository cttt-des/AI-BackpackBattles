extends Potion

onready var healthThreshold: = getP1() / 100.0 - 0.0001


func onTriggerPotion(event = null):
	giveMana(getP2(), event)
	
	giveMaxHealth()

func onPrepare():
	
	connectForCombat(character(), "character_mana_changed", "onManaChanged")
	connectForCombat(character(), "character_damaged", "onDamaged")

func onDamaged(_healthChange, event):
	if isEmpty(): return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		consumePotion(event)

func onManaChanged(amount, event):
	if isEmpty(): return
	
	if (amount < 0 and 
		event.getOrigin() is Item and 
		event.getOrigin().character() == character()):
			consumePotion(event)
