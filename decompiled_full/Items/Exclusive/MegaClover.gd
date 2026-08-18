extends Item

const megaCloverParticles = preload("res://Interface/MegaCloverParticles.tscn")

var stackTypes
var activated: bool

onready var sales: = getP("sales") / 100.0
onready var luckNeeded: int = getP("luckneeded")
onready var numBuffs: int = getP("buffs")

func _ready():
	stackTypes = Game.getBuffs()
	stackTypes.erase(Game.EventType.Lucky)

func onShopEntered():
	for i in 2:
		var clover = ItemBook.generateItem("Lucky Clover")
		placeGeneratedItem(clover, inventory.getAdjacentCells(occupiedCells))
	
	activate()
	Game.saveRunState()

func onPrepare():
	connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")
	activated = false

func onLuckyChanged(amount, event):
	if not activated and character().getLucky() >= luckNeeded:
		activated = true
		
		giveRandomBuffs(numBuffs, event, stackTypes)
		activate()
		var particles = ObjectPool.particleOneShot(megaCloverParticles, get_parent())
		particles.global_position = global_position

func onSaleRoll(_item):
	Game.shopSceneNode.addBonusSalesChance(sales)
