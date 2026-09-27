extends Item
var tickI: int
var slow
var speedUp

func onPrepare():
	tickI = 0
	var allItems = ctx.player.INVENTORY.getItems() + ctx.opponent.INVENTORY.getItems()
	for item in allItems:
		if item.isWeapon():
			item.reduceSpeed(slow)


func doCooldownEffect():
	var slowestCd: = 0.0
	var slowestItem = null
	
	for item in inventory.getItems():
		if item.hasCooldown() and item.isCooldownActive():
			var cd = item.getModifiedCooldown()
			if cd > slowestCd:
				slowestCd = cd
				slowestItem = item
	
	
	slowestItem.addSpeed(speedUp)
	activate()
	tickI += 1


func playActivationSound():
	var pitch = 1.0 if tickI % 2 == 0 else 0.7
	

func _readyInit():
	._readyInit()
	slow = getP("slow") / 100.0
	speedUp = getP("speed") / 100.0
