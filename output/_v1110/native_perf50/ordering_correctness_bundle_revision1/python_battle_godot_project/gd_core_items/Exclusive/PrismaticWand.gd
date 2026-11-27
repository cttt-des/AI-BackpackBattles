extends Item
var buffs
var manaNeeded
var luckNeeded
var regenNeeded
var empower
var buffsToUse

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

func _readyInit():
	._readyInit()
	buffs = [CoreConst.EventType.Mana, CoreConst.EventType.Lucky, CoreConst.EventType.Regeneration]
	manaNeeded = int(getP("manat"))
	luckNeeded = int(getP("luckt"))
	regenNeeded = int(getP("regent"))
	empower = int(getP("empower"))
	buffsToUse = int(getP("use"))
