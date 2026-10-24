extends Reference
class_name CombatStatLogger


var playerId: int
var characterStatHistories = {}
var stackHistories = {}
var itemTooltipHistories = {}
var itemMetricHistories = {}
var itemStateHistories = {}
var metricHistories = []

func _init(_playerId = 0):
	playerId = _playerId
	
	for type in Character.Stat.values():
		characterStatHistories[type] = StatHistory.new()
	
	for stack in Game.getStacks():
		stackHistories[stack] = StatHistory.new()
	
	metricHistories.resize(Item.getNumItemMetrics())
	var dict1 = {}
	for type in [Game.EventType.Fatigue, Game.EventType.Poison, 
					Game.EventType.Spikes, Game.EventType.Unhealing]:
		dict1[type] = StatHistory.new()
	
	metricHistories[Game.ItemMetrics.Damage] = dict1
	
	var dict2 = {}
	var dict3 = {}
	for type in [Game.EventType.Regeneration, Game.EventType.Vampirism]:
		dict2[type] = StatHistory.new()
		dict3[type] = StatHistory.new()
	
	metricHistories[Game.ItemMetrics.Heal] = dict2
	metricHistories[Game.ItemMetrics.Overheal] = dict3
	for i in range(Game.ItemMetrics.Overheal + 1, metricHistories.size()):
		metricHistories[i] = {}

func clear():
	for history in characterStatHistories.values():
		history.clear()
	
	for stackHistory in stackHistories.values():
		stackHistory.clear()
	
	for i in metricHistories.size():
		for history in metricHistories[i].values():
			history.clear()
	
	itemTooltipHistories.clear()
	itemMetricHistories.clear()
	itemStateHistories.clear()

func logCharacterStat(stat: int, eventNum: int, value: float):
	
	characterStatHistories[stat].addValue(eventNum, value)

func getCharacterStatAt(stackType: int, eventNum: int) -> float:
	return characterStatHistories[stackType].getValueAt(eventNum)

func logStack(stackType: int, eventNum: int, value: int):
	stackHistories[stackType].addValue(eventNum, value)

func getStackAt(stackType: int, eventNum: int) -> int:
	return stackHistories[stackType].getValueAt(eventNum)

func prepareItem(item):
	var arr = []
	for metric in Item.getNumItemMetrics():
		var statHistory = StatHistory.new()
		statHistory.addValue( - 1, item.getMetric(metric))
		arr.push_back(statHistory)
	itemMetricHistories[item] = arr
	
	if item.character().playerId == playerId:
		var arr2 = []
		for stat in Item.getNumTooltipStats():
			var statHistory = StatHistory.new()
			statHistory.addValue( - 1, item.getStat(stat))
			arr2.push_back(statHistory)
		itemTooltipHistories[item] = arr2
		
		itemStateHistories[item] = StatHistory.new()

# [ORACLE 桩化记录 #10] 战斗中创建的物品（召唤物 Stone/Dragon Knight、
# @Darkest Lotus@ 克隆等）原版同样不经过 onPrepare 的 prepareItem（唯一调用点
# Core/CombatLog.gd:186 shop_closed），原版运行时这些条目照报
# "Invalid get index … on base: Dictionary" 并中止该遥测函数，实测每场刷
# 2-6 MB 错误文本、拖慢批量。神谕在此改为**未命中即补 prepareItem**：
# 只影响统计史（纯 UI 遥测，CombatLog.events/rng 链零交互），
# 且让后续遥测行照常执行（与原版"中止"的差别仅在遥测完整性，向有利方向）。
func _prepare_if_missing(item) -> void :
	if not itemMetricHistories.has(item):
		prepareItem(item)


func logItemStat(item: Item, statType: int, eventNum: int, value):
	_prepare_if_missing(item)
	itemTooltipHistories[item][statType].addValue(eventNum, value)

func getItemStatAt(item: Item, statType: int, eventNum: int):
	_prepare_if_missing(item)
	return itemTooltipHistories[item][statType].getValueAt(eventNum)

func getLastEventForStat(item: Item, statType: int, eventNum: int) -> Array:
	_prepare_if_missing(item)
	return itemTooltipHistories[item][statType].getLastEntryBefore(eventNum)

func logItemState(item: Item, state, eventNum: int):
	_prepare_if_missing(item)
	itemStateHistories[item].addValue(eventNum, state)

func hasStateData(item: Item) -> bool:
	_prepare_if_missing(item)
	return itemStateHistories[item].hasData()

func getItemStateAt(item: Item, eventNum: int):
	_prepare_if_missing(item)
	return itemStateHistories[item].getValueAt(eventNum)

func logItemMetric(item: Item, metricIndex: int, eventNum: int, value):
	_prepare_if_missing(item)
	itemMetricHistories[item][metricIndex].addValue(eventNum, value)

func getItemMetricAt(item: Item, metricIndex: int, eventNum: int):
	_prepare_if_missing(item)
	return itemMetricHistories[item][metricIndex].getValueAt(eventNum)

func logMetric(metric: int, type: int, val: int, eventNum: int):
	metricHistories[metric][type].addValueAcc(eventNum, val)

func getMetricAt(metric: int, type: int, eventNum: int) -> int:
	return metricHistories[metric][type].getValueAt(eventNum)

func printItemHistories():
	for item in itemMetricHistories:
		for statType in itemMetricHistories[item].size():
			var statHistory = itemMetricHistories[item][statType]
			if statHistory.values.size() > 1:
				print(item.getName(), " stat ", statType, " = ", statHistory.values)



func getValuesForMetricAt(metric: int, eventNum: int) -> Dictionary:
	var dict = {}
	for type in metricHistories[metric]:
		var val = getMetricAt(metric, type, eventNum)
		if val > 0: dict[type] = val
	for item in itemMetricHistories:
		var val = getItemMetricAt(item, metric, eventNum)
		if val > 0:
			dict[item] = val
	return dict



func getStatHistoriesForMetric(metric: int) -> Dictionary:
	var dict = {}
	for type in metricHistories[metric]:
		var statHistory = metricHistories[metric][type]
		if statHistory.hasData():
			dict[type] = statHistory
	for item in itemMetricHistories:
		var statHistory = itemMetricHistories[item][metric]
		if statHistory.hasData():
			dict[item] = statHistory
	return dict



