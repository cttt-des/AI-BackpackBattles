extends Item
var speed1
var speed2
var cdAdvance

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


func getTextureSize() -> Vector2:
	return Vector2.ZERO

func getSpriteOffset() -> Vector2:
	return Vector2.ZERO

func _readyInit():
	._readyInit()
	speed1 = getP("speed") / 100.0
	speed2 = getP("speed2") / 100.0
	cdAdvance = getP("cdadvance")
