extends Item
var runes = ["Badger Rune", "Elephant Rune", "Hawk Rune"]
var luckNeeded: int

func onCombatStart():
	giveLucky(inventory.countSocketedGems())


func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		var event = useLucky(luckNeeded)
		giveRandomBuffs(getP3(), event)
	activate()


func getGatedDescriptor(rarity) -> CoreItemData:
	return ctx.item_book.getDescriptor(ctx.util.pickRandomElement(runes))



func getRelatedItemHeight() -> int:
	return 90

func _readyInit():
	._readyInit()
	luckNeeded = getP2()
	if not pooled:
		runes.push_back("Tiger Rune")

