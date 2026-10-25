extends Item
const healColor = Color(0.384314, 0.913725, 0.423529)
const manaColor = Color(0.329412, 0.392157, 0.992157)
const heatColor = Color(0.996078, 0.458824, 0.290196)
var options: Array

func canAffect(item):
	return item.hasType(CoreConst.Type.Food) or item.hasType(CoreConst.Type.Potion)


func onPrepare():
	addSpeed(getP4() / 100.0 * getNumAffectedItems())
	options = [0, 1, 2]
	

func doCooldownEffect():
	var rng = ctx.util.pickRandomElement(options)
	if rng == 0:
		heal()
	elif rng == 1:
		giveMana(getP2())
	else:
		giveHeat(getP3())
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)

func _readyInit():
	._readyInit()
	pass
