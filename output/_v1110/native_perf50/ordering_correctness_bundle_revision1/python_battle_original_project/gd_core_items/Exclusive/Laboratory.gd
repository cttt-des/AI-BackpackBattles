extends Item
var phase: int
var typesDict: Dictionary
var fluidTween: SceneTreeTween
const params = {
	"luckt": 1, 
	"heatt": 4, 
	"heat_bonus": 1, 
	"heat": 4, 
	"spikest": 6, 
	"spikes_bonus": 1, 
	"spikes": 8, 
	"regent": 8, 
	"regen_bonus": 1, 
	"regen": 10, 
	"vampirism": 12, 
	"vamp_bonus": 1, 
	"vampt": 10, 
	"empower_bonus": 1, 
	"empower": 14
}
const flashColor = Color(1.3, 1.3, 1.3)
const DUR = 0.2
var fluid
var fluidMat

func onShopEntered():
	onStateChanged( - 1)


func getDescription(wrapInColor = true) -> String:
	var descr = descriptor.getDescription()
	
	for param in params:
		descr = insertParameter(descr, str("p_", param), params[param], 
			CoreConst.StatModified.No, false, wrapInColor)
	
	return insertParameters(descr, wrapInColor)


func onPreCombatStart():
	setState(0)
	typesDict = countTypes(getAffectedItems())


func trigger():
	setState(phase + 1)
	
	.trigger()
	




func canAffect(item):
	return (item.hasType(CoreConst.Type.Fire) or 
			item.hasType(CoreConst.Type.Nature) or 
			item.hasType(CoreConst.Type.Holy) or 
			item.hasType(CoreConst.Type.Vampiric) or 
			item.isClassItem(CoreConst.Classes_Full.Engineer))


func doCooldownEffect():
	if phase == 1:
		if character().getLucky() >= params["luckt"]:
			var event = useLucky(params["luckt"])
			var numFire = typesDict[CoreConst.Type.Fire]
			giveHeat(params["heat"] + numFire * params["heat_bonus"], event)
		
	elif phase == 2:
		if character().getHeat() >= params["heatt"]:
			var event = useHeat(params["heatt"])
			var numNature = typesDict[CoreConst.Type.Nature]
			giveSpikes(params["spikes"] + numNature * params["spikes_bonus"], event)
		
	elif phase == 3:
		if character().getSpikes() >= params["spikest"]:
			var event = useSpikes(params["spikest"])
			var numHoly = typesDict[CoreConst.Type.Holy]
			giveRegeneration(params["regen"] + numHoly * params["regen_bonus"], event)

	elif phase == 4:
		if character().getRegeneration() >= params["regent"]:
			var event = useRegeneration(params["regent"])
			var numVamp = typesDict[CoreConst.Type.Vampiric]
			giveVampirism(params["vampirism"] + numVamp * params["vamp_bonus"], event)
			
	elif phase == 5:
		if character().getVampirism() >= params["vampt"]:
			var event = useVampirism(params["vampt"])
			var numEngineer = 0
			for item in getAffectedItems():
				if item.isClassItem(CoreConst.Classes_Full.Engineer):
					numEngineer += 1
			giveEmpower(params["empower"] + numEngineer * params["empower_bonus"], event)
	
	if phase == 5:
		onAfterEffectFinished()
	else:
		activate()


func onStateChanged(_phase: int):
	phase = _phase
	if phase <= 0:
		baseCooldownOverride = getBaseCooldownIndex(0)
	elif phase < 5:
		baseCooldownOverride = getBaseCooldownIndex(phase) - getBaseCooldownIndex(phase - 1)
	
	
	
	

func switchGradient():
	pass
	
	

func _readyInit():
	._readyInit()
	phase = - 1
	switchGradient()

