extends Gem

const gemColor = Color(0.267323, 0.624508, 0.970703)

func prepareWeapon():
	getItem().addCritChancePercent(getP("critchance"))
	getItem().addCritSeverity(getP("critdam") / 100.0)

func prepareArmor():
	character().changeResistChance(Game.EventType.Blind, 
		getGemPower() * getChance())

func doCooldownEffect():
	inflictBlind(1)
	activate()

func onHotSwapHoverWithGemEnd():
	gemAnimation.play("RuneShine")
