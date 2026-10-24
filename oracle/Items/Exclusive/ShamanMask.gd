extends Item

var runes = ["Badger Rune", "Elephant Rune", "Hawk Rune"]

onready var luckNeeded: int = getP2()

func _ready():
	if not pooled:
		runes.push_back("Tiger Rune")

func onCombatStart():
	giveLucky(inventory.countSocketedGems())

func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		var event = useLucky(luckNeeded)
		giveRandomBuffs(getP3(), event)
	activate()

func getGatedDescriptor(rarity) -> ItemDescriptor:
	return ItemBook.getDescriptor(Util.pickRandomElement(runes))


func getRelatedItemHeight() -> int:
	return 90
