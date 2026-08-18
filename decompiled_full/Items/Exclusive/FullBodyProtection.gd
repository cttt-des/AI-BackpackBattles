extends Item

const activeSprite = preload("res://Items/Exclusive/Sprites/FullBodyProtection_active.png")
const inactiveSprite = preload("res://Items/Exclusive/Sprites/FullBodyProtection.png")

onready var blockAmp: = getP("block") / 100.0
onready var damReduction: = getP("damreduction")

var active

func onItemAdded(item):
	.onItemAdded(item)
	checkItems()

func onItemRemoved(item):
	.onItemRemoved(item)
	checkItems()

func onRemoveFromInventory():
	active = false
	sprite.texture = inactiveSprite

func checkItems():
	var numArmor = 0
	var numHelmets = 0
	var numShoes = 0
	for item in inventory.getItems():
		if item.hasType(Type.Armor):
			numArmor += 1
		elif item.hasType(Type.Helmet):
			numHelmets += 1
		elif item.hasType(Type.Shoes):
			numShoes += 1
	
	if numArmor == 1 and numHelmets == 1 and numShoes == 1:
		active = true
		sprite.texture = activeSprite
	else:
		active = false
		sprite.texture = inactiveSprite

func canAffect(item):
	return item.canBlock()

func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(Game.EventType.Block, blockAmp)
	
	if active:
		connectForCombat(character(), "pre_take_damage", "preTakeDamage")

func preTakeDamage(damageRes: DamageResult):
	if damageRes.damageSource.isAttackOrEffect():
		damageRes.applyDamageReduction(damReduction, self)

func doCooldownEffect():
	giveBlock()
	activate()
