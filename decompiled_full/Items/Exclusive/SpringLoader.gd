extends Item

onready var speed1: = getP("speed") / 100.0
onready var speed2: = getP("speed2") / 100.0
onready var cdAdvance: = getP("cdadvance")

func canAffect(item):
	return item.hasCooldown()

func onCombatStart():
	for item in getAffectedItems():
		item.reduceSpeed(speed1)

func doCooldownEffect():
	deactivateCooldown()
	
	for item in getAffectedItems():
		item.addSpeed(speed1 + speed2)
		item.advanceCooldownSeconds(cdAdvance)
	
	onAfterEffectFinished()
	sprite.addMomentum(0.5)

func getTextureSize() -> Vector2:
	return sprite.texture.get_size() * Vector2(1.0, 1.3) * sprite.global_scale

func getSpriteOffset() -> Vector2:
	var offset = Vector2(0, 85.0) * sprite.global_scale * 0.5
	return offset
