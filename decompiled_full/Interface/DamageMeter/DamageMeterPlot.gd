extends Control
class_name DamageMeterPlot

const lineScene = preload("res://Interface/DamageMeter/PlotLine.tscn")

const colors = [
	Color(0.996094, 0.47081, 0.47081), 
	Color(0.96875, 0.682571, 0.363281), 
	Color(0.986328, 0.887328, 0.435371), 
	Color(0.704778, 0.988281, 0.602234), 
	Color(0.389587, 0.958984, 0.71877), 
	Color(0.024536, 0.785156, 0.776243), 
	Color(0.51059, 0.815988, 0.990234), 
	Color(0.511657, 0.507812, 1), 
	Color(0.811584, 0.507812, 1), 
	Color(0.955731, 0.561882, 0.978516), 
	Color(1, 0.535156, 0.73671)
]

var linesNode
var coordinateSystem
var timeZeroLabel
var combatDurationLabel
var maxValueLabel
var hoveredTimeLine

var poolingHandle
var statLogger: CombatStatLogger

var sourceSorting: Dictionary
var lines: Dictionary
var timeTween: SceneTreeTween

func preset():
	linesNode = $Lines
	coordinateSystem = $Panel
	timeZeroLabel = $Time1
	combatDurationLabel = $Time2
	maxValueLabel = $Node2D / Max
	hoveredTimeLine = $HoveredTime
	
	add_to_group("Localized")
	Util.localizeFonts(self)

func returnToObjectPool():
	for line in linesNode.get_children():
		line.returnToObjectPool()
	
	lines.clear()
	
	ObjectPool.returnInstance(self)

func setStatLogger(_statLogger: CombatStatLogger):
	statLogger = _statLogger


func setMetric(metric):
	for line in linesNode.get_children():
		line.returnToObjectPool()
	
	
	var statHistories = statLogger.getStatHistoriesForMetric(metric)
	if statHistories.empty():
		hide()
		return
	
	var maxValue = 0
	var endValues = Dictionary()
	
	for source in statHistories:
		var statHistory: StatHistory = statHistories[source]




		
		var value = statHistory.getValueAt(Game.combatLog.getLastEventNum())
		endValues[source] = value
		maxValue = max(value, maxValue)
	
	if maxValue == 0:
		print("plot maxvalue == 0")
		hide()
		return
	
	show()
	maxValueLabel.text = String(stepify(maxValue, 0.1))
	sourceSorting.clear()
	var sortedSources: Array = Util.sortDict(endValues)
	for i in sortedSources.size():
		sourceSorting[sortedSources[i]] = i
	
	var totalTime = Game.combatLog.getCombatDuration()
	
	var xScale = coordinateSystem.rect_size.x / totalTime
	var yScale = coordinateSystem.rect_size.y / maxValue
	
	updateLocale()
	
	for source in statHistories:
		var line: PlotLine = ObjectPool.instance(lineScene)




		lines[source] = line
		linesNode.add_child(line)
		line.setColor(getColor(source))
		line.setSymbol(getSymbol(source))
		var statHistory: StatHistory = statHistories[source]
		for eventNum in statHistory.eventNumbers:
			if eventNum < Game.combatLog.getNumEvents():
				var value = statHistory.getValueAt(eventNum)
				var time: float
				if eventNum == - 1:
					time = 0.0
				else:
					time = Game.combatLog.getTimeOfEvent(eventNum)
				
				line.addPoint(Vector2(time * xScale, value * yScale))
		line.flatline(coordinateSystem.rect_size.x)
	





func updateLocale():
	timeZeroLabel.text = "0.0" + Util.tra("FORMAT_Second")
	var totalTime = Game.combatLog.getCombatDuration()
	combatDurationLabel.text = ("%1.2f" % totalTime) + Util.tra("FORMAT_Second")

func setHoveredTime(time: float):
	var totalTime = Game.combatLog.getCombatDuration()
	var xScale = coordinateSystem.rect_size.x / totalTime
	Util.killTween(timeTween)
	timeTween = create_tween()
	timeTween.tween_property(hoveredTimeLine, "position:x", 
		coordinateSystem.rect_position.x + time * xScale, 0.1)
	
	
func showLine(source):
	lines[source].show()

func hideLine(source):
	lines[source].hide()

func getColor(source) -> Color:
	var index = sourceSorting[source]
	var wrappedIndex = index % colors.size()
	var iteration = index / colors.size()
	if iteration == 0:
		return colors[wrappedIndex]
	elif iteration == 1:
		return colors[wrappedIndex].lightened(0.5)
	else:
		return colors[wrappedIndex].darkened(0.3)

func getSymbol(source) -> Texture:
	var index = sourceSorting[source]
	var wrappedIndex = index % symbols.size()
	return symbols[wrappedIndex]

func isActive(source) -> bool:
	return lines[source].visible

const symbols = [
	preload("res://Interface/DamageMeter/Plot/Symbol_Star.png"), 
	preload("res://Interface/DamageMeter/Plot/Symbol_Triangle.png"), 
	preload("res://Interface/DamageMeter/Plot/Symbol_Circle.png"), 
	preload("res://Interface/DamageMeter/Plot/Symbol_Square.png"), 
	preload("res://Interface/DamageMeter/Plot/Symbol_Moon.png"), 
	preload("res://Interface/DamageMeter/Plot/Symbol_Heart.png"), 
	preload("res://Interface/DamageMeter/Plot/Symbol_Cross.png"), 
	preload("res://Interface/DamageMeter/Plot/Symbol_Tear.png"), 
	preload("res://Interface/DamageMeter/Plot/Symbol_Cloud.png"), 
	preload("res://Interface/DamageMeter/Plot/Symbol_Pacman.png"), 
]
