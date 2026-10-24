extends Item

onready var buffs = [Game.EventType.Mana, Game.EventType.Lucky, Game.EventType.Regeneration]

onready var manaNeeded: = int(getP("manat"))
onready var luckNeeded: = int(getP("luckt"))
onready var regenNeeded: = int(getP("regent"))
onready var empower: = int(getP("empower"))
onready var buffsToUse: = int(getP("use"))

func doCooldownEffect():
	giveAllBuffs()
	
	var mana = character().getMana()
	var luck = character().getLucky()
	var regen = character().getRegeneration()
	
	if (mana >= manaNeeded or 
		luck >= luckNeeded or 
		regen >= regenNeeded):
			
			var event = removeMostBuffs(buffsToUse, null, true, buffs)
			giveEmpower(empower, event)
	
	activate()
