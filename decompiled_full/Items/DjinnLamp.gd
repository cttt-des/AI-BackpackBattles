extends Item

const numIngredients = 5.0

var activated: bool
var affectedWeapon = null
onready var stacksNeeded = getP1()
onready var healthNeeded = getP2()
onready var activationParticles = $ActivationParticles

func canAffect(item):
	return item.canBeEmpowered()
	
func onPrepare():
	activated = false
	affectedWeapon = null
	var affectedItems = getAffectedItems()
	if not affectedItems.empty():
		affectedWeapon = affectedItems[0]
		connectForCombat(character(), "character_block_changed", "checkStacks")
		connectForCombat(character(), "character_spikes_changed", "checkStacks")
		connectForCombat(character(), "character_mana_changed", "checkStacks")
		connectForCombat(character(), "character_lucky_changed", "checkStacks")
		connectForCombat(character(), "character_damaged", "checkStacks")
		connectForCombat(character(), "character_healed", "checkStacks")
	
func checkStacks(changeAmount, event):
	if activated: return
	
	var progress = 0.0
	progress += min(character().getBlock(), stacksNeeded) / float(stacksNeeded)
	progress += min(character().getSpikes(), stacksNeeded) / float(stacksNeeded)
	progress += min(character().getMana(), stacksNeeded) / float(stacksNeeded)
	progress += min(character().getLucky(), stacksNeeded) / float(stacksNeeded)
	progress += min(character().getCurrentHealth() - 1, healthNeeded) / float(healthNeeded)
	progress /= numIngredients
	
	if changeAmount > 0:
		
		if progress >= 0.9999:
			activated = true
			EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
			useBlock(stacksNeeded, event)
			useSpikes(stacksNeeded, event)
			useMana(stacksNeeded, event)
			useLucky(stacksNeeded, event)
			character().loseHealth(healthNeeded, self, event)
			var bonusDamage = getP3()
			affectedWeapon.addBonusDamage(bonusDamage)
			var dmgBuffEvent = Game.combatLog.createEvent_DamageBuff(self, affectedWeapon, bonusDamage, character().playerId, event)
			EventBus.logEvent(dmgBuffEvent)
			EventBus.flushLoggingQueue()
			activate()
			activationParticles.activate()

func doCooldownEffect():
	var numLucky = character().getLucky()
	var numSpikes = character().getSpikes()
	var numMana = character().getMana()
	
	if numLucky < numSpikes:
		if numLucky < numMana:
			
			giveLucky(1)
		else:
			
			giveMana(1)
	else:
		
		if numSpikes < numMana:
			
			giveSpikes(1)
		else:
			
			giveMana(1)
	
	activate()
