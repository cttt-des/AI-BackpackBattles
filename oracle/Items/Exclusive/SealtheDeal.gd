extends Item

onready var regenNeeded: = int(getP("regent"))
onready var vampirism: = int(getP("vamp"))
onready var luckNeeded: = int(getP("luckt"))
onready var spikes: = int(getP("spikes"))
onready var manaNeeded: = int(getP("manat"))
onready var empower: = int(getP("empower"))
onready var tradeBonusValue: = int(getP("gold"))

func onCalcTradeChance():
	Game.SELLBOX.tradeChance += getShopChance() / 100.0
	Game.SELLBOX.tradeBonusValue += tradeBonusValue

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
