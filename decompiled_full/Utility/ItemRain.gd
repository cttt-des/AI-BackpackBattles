extends Node2D

const offset = 200
const impulse = 200
const rarityOdds = [0.6, 0.2, 0.11, 0.06, 0.03]

var xPos = 0.0

func _ready() -> void :
	for i in 100:
		Util.callDelayed(self, "dropItem", 5 + i * 0.1)

func dropItem():
	var item = ItemBook.instantiateItem_pooled(Util.pickRandomElement(ItemBook.itemList))
	item.ownerType = Item.Owner.Title
	add_child(item)
	item.position = Vector2(xPos, - 200)
	item.global_position = item.findFreeSpace(item.global_position)
	
	xPos += Util.rng.randf_range(100, 300)
	if xPos > 1900:
		xPos = 0
		
	item.disablePicking()
	item.disableTooltip()
	item.makeRigidBody()
	
	if Util.rng.randf() < 0.1:
		item.impactSoundVolume = - 5
	else:
		item.impactSoundVolume = - 12
		
	Util.callDelayed(self, "applyImpulse", 0.01, [item])
	
	

func applyImpulse(item):
	if not is_instance_valid(item):
		pass
	item.apply_impulse(Vector2(Util.rng.randf_range( - offset, offset), 
								Util.rng.randf_range( - offset, offset)), 
							Vector2(Util.rng.randf_range( - impulse, impulse), 
									Util.rng.randf_range( - impulse, impulse)))

func onItemReachedBottom(item) -> void :
	if item.ownerType == Item.Owner.Title:
		item.discard()
