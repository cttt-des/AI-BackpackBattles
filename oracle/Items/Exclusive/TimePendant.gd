extends Item

onready var cdAdvance: = getP("cdadvance")

func canAffect(item):
	return item.hasCooldown()

func doCooldownEffect():
	var item = getFirstAffectedItem()
	if item != null and item.isCooldownActive():
		item.advanceCooldownSeconds(cdAdvance)
	activate()
