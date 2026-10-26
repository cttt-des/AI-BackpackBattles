extends Item
var digUpItems = {
	"Stone": 4, 
	"Garlic": 3, 
	"Blueberries": 2, 
	"Lump of Coal": 3, 
	"Pocket Sand": 3, 
	"Chipped Ruby": 1, 
	"Chipped Sapphire": 1, 
	"Chipped Emerald": 1, 
	"Chipped Topaz": 1, 
	"Chipped Amethyst": 1, 
	"Healing Herbs": 0.5, 
	"Bag of Stones": 0.5, 
	"Walrus Tusk": 0.2, 
	"Whetstone": 0.2, 
	"Piggybank": 0.2, 
	"Pan": 0.2, 
	"Customer Card": 0.2, 
	"Gloves of Haste": 0.2, 
	"Dagger": 0.2, 
	"Protective Purse": 0.1, 
	"Flawed Ruby": 0.2, 
	"Flawed Sapphire": 0.2, 
	"Flawed Emerald": 0.2, 
	"Flawed Topaz": 0.2, 
	"Flawed Amethyst": 0.2, 
}
var spawnPos
var luck
var heat
var cdIncrease

func onShopEntered():
	pass

func onPrepare():
	pass
	


func onChargeReceived(_charge):
	resetBaseCooldown()
	if numCharges == 1:
		setState(true)


func onChargeLeft(_charge):
	if numCharges == 0:
		setState(false)


func doCooldownEffect():
	giveLucky(luck)
	giveHeat(heat)
	if numCharges == 0:
		setBaseCooldown(baseCooldownOverride + cdIncrease)
	activate()


func onStateChanged(charged: bool):
	if charged:
		pass
	else:
		pass


func _readyInit():
	._readyInit()
	luck = int(getP("luck"))
	heat = int(getP("heat"))
	cdIncrease = getP("cdincrease")
	pass

