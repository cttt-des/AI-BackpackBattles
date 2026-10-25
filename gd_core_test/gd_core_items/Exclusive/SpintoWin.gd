extends Item
const colors = {
	CoreConst.FaceDirection.UP: Color(0.941176, 0.489231, 0.301961), 
	CoreConst.FaceDirection.RIGHT: Color(0.301961, 0.941176, 0.41682), 
	CoreConst.FaceDirection.DOWN: Color(0.941176, 0.301961, 0.513726), 
	CoreConst.FaceDirection.LEFT: Color(0.320312, 0.466339, 1)
}
const neutralColor = Color(1, 1, 1, 0.364706)
var heat
var luck
var regen
var mana
var frame
var skillLight

func ready_deferred():
	.ready_deferred()
	updateColor()


func updateColor():
	pass








func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	var colors = [ctx.util.inactiveColor, ctx.util.inactiveColor, ctx.util.inactiveColor, ctx.util.inactiveColor]
	var gold: int
	
	if placed:
		colors[faceDirection] = ctx.util.modifiedColor
	
	descr = getModeDescription(descr, colors, false, wrapInColor)
	
	return descr


func doCooldownEffect():
	match faceDirection:
		CoreConst.FaceDirection.UP:
			giveHeat(heat)
		CoreConst.FaceDirection.RIGHT:
			giveLucky(luck)
		CoreConst.FaceDirection.DOWN:
			giveRegeneration(regen)
		CoreConst.FaceDirection.LEFT:
			giveMana(mana)
	activate()


func gainsStack(stackType) -> bool:
	match faceDirection:
		CoreConst.FaceDirection.UP:
			return stackType == CoreConst.Stack.Heat
		CoreConst.FaceDirection.RIGHT:
			return stackType == CoreConst.Stack.Lucky
		CoreConst.FaceDirection.DOWN:
			return stackType == CoreConst.Stack.Regeneration
		CoreConst.FaceDirection.LEFT:
			return stackType == CoreConst.Stack.Mana
	return false


func rotateTo(targetRotation, duration = 0.15):
	.rotateTo(targetRotation, duration)
	updateColor()







func setFaceDirectionInstant(_faceDirection):
	.setFaceDirectionInstant(_faceDirection)
	updateColor()

func _readyInit():
	._readyInit()
	heat = int(getP("heat"))
	luck = int(getP("luck"))
	regen = int(getP("regen"))
	mana = int(getP("mana"))
