extends ResizableControl

const damageMeterEntry = preload("res://Interface/DamageMeter/DamageMeterEntry.tscn")
const totalScene = preload("res://Interface/DamageMeter/DamageMeterTotal.tscn")
const stackChangeSectionLabel = preload("res://Interface/DamageMeter/StackChangeSectionLabel.tscn")
const plotScene = preload("res://Interface/DamageMeter/DamageMeterPlot.tscn")

const submetricNames_buff = ["UI_DamageMeter_Gained", "UI_DamageMeter_Removed", "UI_DamageMeter_Used"]
const submetricNames_debuff = ["UI_DamageMeter_Inflicted", "UI_DamageMeter_Cleansed", "UI_DamageMeter_Used"]
const submetricNames_stamina = ["UI_DamageMeter_Used", "UI_DamageMeter_Gained", "UI_DamageMeter_Removed"]

export var player: bool
var isOpen = false

onready var header = $Label
onready var scrollContainer = $ScrollContainer
onready var vboxContainer = $ScrollContainer / VBoxContainer
onready var openButton = $OpenButton
onready var icon = $Icon
onready var metricList: ItemListButton = $Node2D / MetricList
onready var verticalResizeButton = $VerticalResizeButton

var itemToEntry: Dictionary
var visibleMetric = Game.ItemMetrics.Damage
var currentEvent = null
var plots: = []
var plotToEntry: Dictionary

func _ready() -> void :
	close()
	add_to_group("Localized")
	Game.connect("returned_to_title", self, "reset")
	Game.connect("shop_opened", self, "reset")
	metricList.connect("list_opened", self, "onMetricListOpened")
	metricList.connect("list_closed", self, "onMetricListClosed")
	updateMetricList()
	scrollContainer.onClose()

func canDrag():
	return .canDrag() and not scrollContainer.scrollbarHovered
	
func updateLocale():
	updateMetricList()

var metricKeys = {
	Game.ItemMetrics.Damage: "UI_DamageMeter_Player", 
	Game.ItemMetrics.Heal: "UI_DamageMeter_Heal", 
	Game.ItemMetrics.Stamina: "Stamina_NAME", 
	Game.ItemMetrics.Overheal: "UI_DamageMeter_Overheal", 
	Game.ItemMetrics.Misses: "UI_DamageMeter_Misses", 
	Game.ItemMetrics.Activations: "UI_DamageMeter_Activations", 
	Game.ItemMetrics.DamageBlocked: "UI_DamageMeter_DamageBlocked", 
	Game.ItemMetrics.MaxHealth: "UI_DamageMeter_MaxHealth", 
	Game.ItemMetrics.OutOfStamina: "UI_DamageMeter_OutOfStamina"
}


var metricIndices = [
	Game.ItemMetrics.Damage, 
	Game.ItemMetrics.Heal, 
	Game.ItemMetrics.Stamina, 
	Game.ItemMetrics.Activations, 
	Game.ItemMetrics.Block, 
	Game.ItemMetrics.Lucky, 
	Game.ItemMetrics.Regeneration, 
	Game.ItemMetrics.Vampirism, 
	Game.ItemMetrics.Spikes, 
	Game.ItemMetrics.Mana, 
	Game.ItemMetrics.Empower, 
	Game.ItemMetrics.Heat, 
	Game.ItemMetrics.Poison, 
	Game.ItemMetrics.Blind, 
	Game.ItemMetrics.Cold
]

onready var metricIndicesReversed = Util.arrayAsIndexDict(metricIndices)
onready var stacksMetricOffset = Game.EventType.Block - metricIndicesReversed[Game.ItemMetrics.Block]

func updateMetricList():
	metricList.clearList()
	
	var nonStackMetrics = metricIndicesReversed[Game.ItemMetrics.Block]
	for i in metricIndices.size():
		var index = metricIndices[i]
		
		if i < nonStackMetrics:
			metricList.addItem(metricKeys[index])
		else:
			
			var keyword = Game.typeToKeyword(stacksMetricOffset + i)
			
			
			metricList.addItem(keyword + "_NAME", Util.getIconTexture(keyword))
		
	metricList.selectItemByIndex(metricIndicesReversed[visibleMetric])

func onMetricListOpened():
	verticalResizeButton.hide()

func onMetricListClosed():
	verticalResizeButton.show()

func reset():
	currentEvent = null

func clear():
	for child in vboxContainer.get_children():
		if not child is DamageMeterPlot:
			ObjectPool.returnInstance(child)
		
	itemToEntry.clear()
	plotToEntry.clear()

func setTime(time):
	for plot in plots:
		plot.setHoveredTime(time)

func onMetricSelected(index, text):
	var asMetric = metricIndices[index]
	if asMetric == visibleMetric: return
	
	visibleMetric = asMetric
	clearPlots()
	if Game.combatLog.loggingFinished:
		updatePlot()
	
	var playerId = 0 if player else 1
	updateMeter(currentEvent, Game.combatLog.statLoggers[playerId])

func clearPlots():
	for plot in plots:
		plot.returnToObjectPool()
	plots.clear()

func createPlot():
	clearPlots()
	if Game.combatLog.loggingFinished:
		updatePlot()
	
	var playerId = 0 if player else 1
	updateMeter(currentEvent, Game.combatLog.statLoggers[playerId])

func updatePlot():
	var metrics = getSubMetrics()
	for i in metrics.size():
		var metric = metrics[i]
		var plot = ObjectPool.instance(plotScene)
		vboxContainer.add_child(plot)
		var playerId = 0 if player else 1
		plot.setStatLogger(Game.combatLog.statLoggers[playerId])
		plot.setMetric(metric)
		plots.push_back(plot)

func getSubMetrics():
	var metrics = []
	if visibleMetric >= Game.ItemMetrics.Block:
		if player:
			for changeType in [Item.StackChangeType.Added_Player, 
										Item.StackChangeType.Removed_Player, 
										Item.StackChangeType.Used_Player]:
				metrics.push_back(Item.getStackMetricIndex(changeType, metricToEventType(visibleMetric)))
		else:
			for changeType in [Item.StackChangeType.Added_Opponent, 
										Item.StackChangeType.Removed_Opponent, 
										Item.StackChangeType.Used_Opponent]:
				metrics.push_back(Item.getStackMetricIndex(changeType, metricToEventType(visibleMetric)))
	
	elif visibleMetric >= Game.ItemMetrics.Stamina:
		for changeType in [Item.StackChangeType.Used_Player, 
									Item.StackChangeType.Added_Player, 
									Item.StackChangeType.Removed_Opponent]:
			metrics.push_back(Item.getMultiMetricIndex(changeType, visibleMetric))
		
	else:
		metrics.push_back(visibleMetric)
	
	
	
	if visibleMetric == Game.ItemMetrics.Damage:
		metrics.push_back(Game.ItemMetrics.Misses)
		metrics.push_back(Game.ItemMetrics.DamageBlocked)
	
	elif visibleMetric == Game.ItemMetrics.Heal:
		metrics.push_back(Game.ItemMetrics.Overheal)
		metrics.push_back(Game.ItemMetrics.MaxHealth)
	


	
	elif visibleMetric == Game.ItemMetrics.Activations:
		metrics.push_back(Game.ItemMetrics.OutOfStamina)
	
	
	return metrics


func metricToEventType(metric: int) -> int:
	return Game.EventType.Block + metric - Game.ItemMetrics.Block



func updateMeter(event, statLogger: CombatStatLogger):
	if event == null:
		return
	
	currentEvent = event
	
	if not isVisible():
		return
	
	clear()
	
	var metrics = getSubMetrics()
	
	for i in metrics.size():
		var metric = metrics[i]
		var dict = statLogger.getValuesForMetricAt(metric, event.id)
		
		var plot = null
		if plots.size() > i:
			plot = plots[i]
		
		var addMetric: bool = (plot != null and plot.visible) or not dict.empty()
		
		if addMetric:
			if metrics.size() > 1:
				var label = stackChangeSectionLabel.instance()
				vboxContainer.add_child(label)
				
				if visibleMetric == Game.ItemMetrics.Stamina:
					label.translationKey = submetricNames_stamina[i]
				
				elif metric in metricKeys:
					label.translationKey = metricKeys[metric]
				else:
					var isBuff = Game.isBuff(metricToEventType(visibleMetric))
					if isBuff:
						label.translationKey = submetricNames_buff[i]
					else:
						label.translationKey = submetricNames_debuff[i]
					
				label.updateLocale()
			
			if not dict.empty():
				addMeter(dict, event.timestamp, plot)
			
			if plot != null:
				plot.raise()
			
			setTime(event.timestamp)

func addMeter(dmgMeter: Dictionary, combatTime: float, plot = null):
	
	var totalDamage = 0.0
	for source in dmgMeter:
		totalDamage += dmgMeter[source]
	
	var sortedEntries: Array = Util.sortDict(dmgMeter)
	var largestDmg = float(dmgMeter[sortedEntries[0]])
	
	for source in sortedEntries:
		var entry = ObjectPool.instance(damageMeterEntry)
		vboxContainer.add_child(entry)
		
		var dmg = dmgMeter[source]
		var relDmg = dmg / totalDamage if totalDamage > 0 else 0
		var dps = dmg / max(0.5, combatTime)
		var relToLargest = dmg / largestDmg if largestDmg > 0 else 0
		
		entry.init(player, source, dmg, dps, relDmg, relToLargest, plot, self)
		if plot != null:
			Util.dictAppend(plotToEntry, plot, entry)
		
		Util.dictAppend(itemToEntry, source, entry)
	
	if sortedEntries.size() > 1:
		var totalEntry = ObjectPool.instance(totalScene)
		vboxContainer.add_child(totalEntry)
		totalEntry.init(totalDamage, totalDamage / max(0.5, combatTime))

func highlightSource(source):
	if source in itemToEntry:
		for entry in itemToEntry[source]:
			entry.highlight()

func unhighlightSource(source):
	if source in itemToEntry:
		for entry in itemToEntry[source]:
			entry.unhighlight()

func isVisible():
	return isOpen and Game.combatLog.visible

func onShow():
	var playerId = 0 if player else 1
	updateMeter(currentEvent, Game.combatLog.statLoggers[playerId])

func open():
	isOpen = true
	onShow()
	metricList.show()
	scrollContainer.show()
	icon.hide()
	vResizeButton.show()
	scrollContainer.onOpen()
	
	if player:
		margin_left = - 440
		openButton.flip_h = false
	else:
		margin_right = 430
		openButton.flip_h = true
	
	openButton.rect_size = Vector2(63, 52)
	rect_min_size.y = 200
	rect_size.y = 500
	
	if not Game.isTutorialDone(Game.TutorialSteps.CombatLogButtons):
		Game.setTutorialDone(Game.TutorialSteps.CombatLogButtons)
		Game.combatLog.buttonTutorialAni.play("RESET")


func close():
	isOpen = false
	metricList.hide()
	scrollContainer.hide()
	scrollContainer.onClose()
	icon.show()
	vResizeButton.hide()
	
	if player:
		margin_left = 0
		openButton.flip_h = true
	else:
		margin_right = 62
		openButton.flip_h = false
	
	openButton.rect_size = Vector2(63, 103)
	rect_min_size.y = 115
	margin_bottom = 0

func _on_OpenButton_pressed() -> void :
	if isOpen:
		close()
	else:
		open()
