extends Potion
var healthThreshold
var dam
var vampirism

func onPrepare():
	
	connectForCombat(character(), "character_damaged", "onPlayerDamaged")
	connectForCombat(opponent(), "character_damaged", "onPlayerDamaged")



func onPlayerDamaged(_healthChange, event):
	if isEmpty(): return
	
	var relHealth = character().getRelativeHealth()
	if relHealth < healthThreshold:
		var relHealth2 = opponent().getRelativeHealth()
		if relHealth2 < healthThreshold:
			consumePotion()


func onTriggerPotion(triggerEvent = null):
	
	stealLife(dam, getP_m("lifesteal") / 100.0, triggerEvent)
	giveVampirism(vampirism, triggerEvent)
	

func _readyInit():
	._readyInit()
	healthThreshold = getP1() / 100.0
	dam = getP3()
	vampirism = int(getP2())
