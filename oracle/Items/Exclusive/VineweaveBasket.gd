extends Bag

onready var salesRound1: = int(getP("round1"))
onready var salesRound2: = int(getP("round2"))
onready var salesChance: = getP("sales") / 100.0
onready var salesParticles = $Icon / SaleParticles

func _ready():
	if ownerType == Owner.PlayerInventory:
		Game.connect("shop_opened", self, "onShopOpened")

func canApplyEffect(toItem):
	return toItem.hasType(Type.Nature)

func onPrepare():
	var healAmp = getP("healamp")
	healAmp += getP("ampbonus") * getNumAffectedInside()
	character().addHealingEfficiency(healAmp / 100.0)
	
func onShopOpened():
	if Game.curRound == salesRound1 or Game.curRound == salesRound2:
		salesParticles.activate()
	
func onSaleRoll(_item):
	if Game.curRound == salesRound1 or Game.curRound == salesRound2:
		Game.shopSceneNode.addBonusSalesChance(salesChance)
