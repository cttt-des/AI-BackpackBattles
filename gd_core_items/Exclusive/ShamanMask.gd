extends Item
var runes = ["Badger Rune", "Elephant Rune", "Hawk Rune"]
var luckNeeded: int

func onCombatStart():
	# ★ 诊断标记（不消耗链）：幸运计数的逐物品宝石明细
	if ctx.rng.oracle_trace:
		var detail := []
		for it in inventory.items:
			detail.append(String(it.descriptor.identifier) + "=" +
					str(it.getGemsNoNull().size()))
		ctx.rng.oracle_trace_log.push_back([ctx.rng.oracle_trace_log.size(),
				"GEMS", str(inventory.countSocketedGems()),
				PoolStringArray(detail).join(","), "", ""])
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

