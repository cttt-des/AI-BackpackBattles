extends Weapon
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
var digParticles
var spawnPos

func onShopEntered():
	pass

func onDealtDamage(damageRes):
	if damageRes.hasHit():
		if rollChance():
			inflictBlind(1, damageRes.event)

func _readyInit():
	._readyInit()
	pass
