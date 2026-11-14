extends Item
var regenNeeded
var vampirism
var luckNeeded
var spikes
var manaNeeded
var empower
var tradeBonusValue

func onCalcTradeChance():
	pass

func doCooldownEffect():
	
	if character().getRegeneration() >= regenNeeded:
		var event = useRegeneration(regenNeeded)
		giveVampirism(vampirism, event)
	
	if character().getLucky() >= luckNeeded:
		var event = useLucky(luckNeeded)
		giveSpikes(spikes, event)
	
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		giveEmpower(empower, event)
	
	
	activate()

func _readyInit():
	._readyInit()
	regenNeeded = int(getP("regent"))
	vampirism = int(getP("vamp"))
	luckNeeded = int(getP("luckt"))
	spikes = int(getP("spikes"))
	manaNeeded = int(getP("manat"))
	empower = int(getP("empower"))
	tradeBonusValue = int(getP("gold"))
