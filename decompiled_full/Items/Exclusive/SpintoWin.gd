extends Item

onready var heat: = int(getP("heat"))
onready var luck: = int(getP("luck"))
onready var regen: = int(getP("regen"))
onready var mana: = int(getP("mana"))
onready var frame = $Icon / Frame

const colors = {
	FaceDirection.UP: Color(0.941176, 0.489231, 0.301961), 
	FaceDirection.RIGHT: Color(0.301961, 0.941176, 0.41682), 
	FaceDirection.DOWN: Color(0.941176, 0.301961, 0.513726), 
	FaceDirection.LEFT: Color(0.320312, 0.466339, 1)
}

const neutralColor = Color(1, 1, 1, 0.364706)
onready var skillLight = $Icon / SkillLight

func ready_deferred():
	.ready_deferred()
	updateColor()
	frame.setRotationTarget( - sprite.global_rotation)

func updateColor():
	skillLight.modulate = colors[faceDirection]
	specificDragParticles[0].self_modulate = skillLight.modulate







func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	var colors = [Util.inactiveColor, Util.inactiveColor, Util.inactiveColor, Util.inactiveColor]
	var gold: int
	
	if placed:
		colors[faceDirection] = Util.modifiedColor
	
	descr = getModeDescription(descr, colors, false, wrapInColor)
	
	return descr

func doCooldownEffect():
	match faceDirection:
		FaceDirection.UP:
			giveHeat(heat)
		FaceDirection.RIGHT:
			giveLucky(luck)
		FaceDirection.DOWN:
			giveRegeneration(regen)
		FaceDirection.LEFT:
			giveMana(mana)
	activate()

func gainsStack(stackType) -> bool:
	match faceDirection:
		FaceDirection.UP:
			return stackType == Stack.Heat
		FaceDirection.RIGHT:
			return stackType == Stack.Lucky
		FaceDirection.DOWN:
			return stackType == Stack.Regeneration
		FaceDirection.LEFT:
			return stackType == Stack.Mana
	return false

func rotateTo(targetRotation, duration = 0.15):
	.rotateTo(targetRotation, duration)
	updateColor()






func setFaceDirectionInstant(_faceDirection):
	.setFaceDirectionInstant(_faceDirection)
	frame.setRotationInstant( - sprite.global_rotation)
	updateColor()
