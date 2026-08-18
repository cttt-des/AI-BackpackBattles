extends ResizableControl

signal replay_finished

enum ActivationsState{
	Hide, 
	Minimized, 
	Show
}

enum GlobalStat{
	TimeAdvance = 0
}

const logLineScene = preload("res://Interface/CombatLog/CombatLogLine.tscn")
const logLineTooltipScene = preload("res://Interface/CombatLog/LogLineTooltip.tscn")

const playerStyleboxes = [
	preload("res://Interface/CombatLog/LogLinePlayerStylebox.tres"), 
	preload("res://Interface/CombatLog/LogLinePlayerStylebox_hovered.tres"), 
	preload("res://Interface/CombatLog/LogLinePlayerStylebox_connected.tres"), 
	preload("res://Interface/CombatLog/LogLinePlayerStylebox_tooltip.tres")
]

const opponentStyleboxes = [
	preload("res://Interface/CombatLog/LogLineOpponentStylebox.tres"), 
	preload("res://Interface/CombatLog/LogLineOpponentStylebox_hovered.tres"), 
	preload("res://Interface/CombatLog/LogLineOpponentStylebox_connected.tres"), 
	preload("res://Interface/CombatLog/LogLineOpponentStylebox_tooltip.tres")
]

var fadedStyleboxes: Dictionary

onready var scrollContainer = $ScrollContainer
onready var container = $ScrollContainer / VBoxContainer
onready var lineArrow = $LineArrow
onready var hoverHint = $HoverHint
onready var dragHint = $DragHint
onready var buttonHint = Game.combatSceneNode.get_node("%CombatLogButtonHint")
onready var tutorialAni = Game.combatSceneNode.get_node("%CombatLogTutorialAnimation")
onready var buttonTutorialAni = $TutorialAni
onready var playerDmgMeter = $PlayerDamageMeter
onready var opponentDmgMeter = $OpponentDamageMeter
onready var playerButton = $PlayerButton
onready var opponentButton = $OpponentButton
onready var filterPanel = $FilterPanel
onready var searchBar = $FilterPanel / Searchbar
onready var tooltipNode = $AboveLog
onready var scrollTimer = $ScrollTimer
onready var closeButton = $CloseButton

var arrowTween
var scrollWithArrow: bool = false
var tooltip = null
var warpPointNodes: Array

var events: = []
var eventNum: = - 1
var timestamps: = []
var logLines: = []
var activeLine: CombatLogLine = null
var loggingFinished: = false
var statLoggers = [CombatStatLogger.new(0), CombatStatLogger.new(1)]
var globalStatHistories: = []
var activeItemState: = {}
var activeCharacterStats: = [[], []]
var itemsWithCooldown: = [[], []]

var electricalCharges: = []
var emitterEventToChargeInstance: = {}
var numPlayerCharges: = 0


var showPlayerEvents: = true
var showOpponentEvents: = true
var activationsState: int = ActivationsState.Hide
var searchTerm: String

func _ready() -> void :
	
	
	get_parent().show()
	hide()
	hideArrow()
	get_tree().connect("idle_frame", self, "updateIdle")
	Game.connect("shop_closed", self, "onPrepare")
	Game.connect("combat_end", self, "onCombatEnd")
	Game.connect("switch_to_shop", self, "clear")
	Game.connect("return_to_title", self, "clear")
	Game.connect("return_to_history", self, "clear")
	Game.connect("warp_cursor_combat", self, "onCursorWarp")
	Game.connect("get_rects_combat", self, "onGetRects")
	
	var scrollBar = scrollContainer.get_v_scrollbar()
	scrollBar.connect("visibility_changed", self, "onScrollbarVisibilityChanged")
	searchBar.connect("search_text_changed", self, "onSearchTextChanged")
	
	playerDmgMeter.connect("drag_start", self, "startDragging")
	playerDmgMeter.connect("drag_end", self, "endDragging")
	
	opponentDmgMeter.connect("drag_start", self, "startDragging")
	opponentDmgMeter.connect("drag_end", self, "endDragging")
	
	filterPanel.connect("drag_start", self, "startDragging")
	filterPanel.connect("drag_end", self, "endDragging")
	
	$PlayerButton.connect("toggled", self, "onPlayerToggled")
	$OpponentButton.connect("toggled", self, "onOpponentToggled")
	
	for stylebox in playerStyleboxes:
		var fadedStylebox = stylebox.duplicate()
		fadedStylebox.bg_color.a *= 0.8
		fadedStyleboxes[stylebox] = fadedStylebox
	
	for stylebox in opponentStyleboxes:
		var fadedStylebox = stylebox.duplicate()
		fadedStylebox.bg_color.a *= 0.6
		fadedStyleboxes[stylebox] = fadedStylebox
	
	scrollContainer.onClose()
	
	for globalStat in GlobalStat:
		globalStatHistories.push_back(StatHistory.new())
	
	ObjectPool.prepare(logLineScene, 1000)
	
	warpPointNodes = Util.getInteractableNodes(self)

func clear():
	close()
	hideArrow()
	scrollContainer.scrollEnabled = false
	activeLine = null
	unhighlightItem()
	highlightedItem = null
	events.clear()
	logLines.clear()
	delayedLogList.clear()
	delayListDone = 0
	
	eventNum = - 1
	
	
	for child in container.get_children():
		assert (child is CombatLogLine)
		
		ObjectPool.returnInstance(child)
	
	playerDmgMeter.clear()
	opponentDmgMeter.clear()
	playerDmgMeter.clearPlots()
	opponentDmgMeter.clearPlots()
	Game.PLAYER.statsDisplay.reset()
	
	
	for i in 2:
		statLoggers[i].clear()
	activeItemState.clear()
	activeCharacterStats = [[], []]
	timestamps.clear()
	itemsWithCooldown = [[], []]
	loggingFinished = false
	for i in GlobalStat.size():
		globalStatHistories[i].clear()
	
	numPlayerCharges = 0
	electricalCharges.clear()
	for charge in emitterEventToChargeInstance.values():
		charge.returnToObjectPool()
	emitterEventToChargeInstance.clear()
	


func onPrepare():
	var items = Game.PLAYER.INVENTORY.getItemsAndGems() + Game.OPPONENT.INVENTORY.getItemsAndGems()
	for character in [Game.PLAYER, Game.OPPONENT]:
		for stat in Character.Stat:
			snapshotCharacterStat(character, Character.Stat[stat])
		
		for stackType in Game.getStacks():
			snapshotStack(character, stackType)
		
		var statLogger: CombatStatLogger = statLoggers[character.playerId]
		for item in items:
			
			statLogger.prepareItem(item)
		
		for metric in Game.ItemMetrics.values():
			for type in statLogger.metricHistories[metric]:
				statLogger.logMetric(metric, type, 0, eventNum)
		
		globalStatHistories[GlobalStat.TimeAdvance].addValue(0.0, eventNum)

func onCombatEnd(roundResult):
	close()
	
	
	loggingFinished = true
	
	if roundResult == Game.RoundResult.Win:
		logWin()
	else:
		logLoss()
	
	playerDmgMeter.createPlot()
	opponentDmgMeter.createPlot()
	scrollContainer.scrollEnabled = true
	
	for i in 2:
		var statLogger = statLoggers[i]
		for item in statLogger.itemStateHistories:
			if statLogger.hasStateData(item):
				activeItemState[item] = statLogger.getItemStateAt(item, eventNum)
		for stat in statLogger.characterStatHistories:
			activeCharacterStats[i].push_back(statLogger.getCharacterStatAt(stat, eventNum))
	
	for event in events:
		timestamps.push_back(event.timestamp)
	
	for i in 2:
		for item in statLoggers[i].itemTooltipHistories:
			
			if item.logCooldown():
				itemsWithCooldown[i].push_back(item)

func getTimeStamp():
	return Game.combatTimer.getTimeStamp()

func getCharacterFromId(id):
	if id == Character.ID.PLAYER:
		return Game.PLAYER
	else:
		return Game.OPPONENT

func getOtherCharacterId(id) -> int:
	return 1 - id

var scrolledToBottom = false

func createEvent(triggerEvent, origin, type) -> CombatEvent:
	eventNum += 1
	
	var event = CombatEvent.new(eventNum, getTimeStamp(), triggerEvent, 
				origin, type)
	
	for character in [Game.PLAYER, Game.OPPONENT]:
		snapshotCharacterStat(character, Character.Stat.Stamina)
	
	return event


var delayedLogList = []
var delayListDone = 0
var eventsLogged = 0

func replayDelayedEvent() -> bool:
	if delayListDone < delayedLogList.size():
		var eventToReplay = delayedLogList[delayListDone]
		catchUpEvent(eventToReplay)
		
		delayListDone += 1
		return false
	
	return true

func logEvent(event, afterFightAllowed = false):
	if Game.fightEnded and not afterFightAllowed: return
	
	eventsLogged += 1
	if not visible:
		delayedLogList.append(event)
		
	else:
		addLogLine(event)
	
	events.push_back(event)

func catchUpEvent(event):
	addLogLine(event)

func addLogLine(event):
	var logLine: CombatLogLine = ObjectPool.instance(logLineScene)
	
	logLine.setEvent(event)
	logLine.visible = isLineVisible(logLine)
	logLine.setMinimized(isLineMinimized(logLine))
	container.add_child(logLine)
	
	logLines.push_back(logLine)
	moveArrowTo(logLine, false)
	
	if container.rect_size.y - scrollContainer.get_v_scroll() < scrollContainer.rect_size.y + 50:
		if not scrolledToBottom:
			Util.callNextFrame(self, "scrollToBottom")
			scrolledToBottom = true


var highlightedItem = null

func unhighlightItem(modulateItem: bool = true):
	if highlightedItem:
		if modulateItem:
			if highlightedItem is Item:
				highlightedItem.unhighlight()
		
		for line in container.get_children():
			if highlightedItem is Item:
				if line.getItem() == highlightedItem:
					line.onConnectedHoverEnd()
			else:
				if line.getSource() == highlightedItem[0]:
					line.onConnectedHoverEnd()
		
		if highlightedItem is Item:
			
			playerDmgMeter.unhighlightSource(highlightedItem)
			opponentDmgMeter.unhighlightSource(highlightedItem)
		else:
			
			if highlightedItem[1]:
				playerDmgMeter.unhighlightSource(highlightedItem[0])
			else:
				opponentDmgMeter.unhighlightSource(highlightedItem[0])
		
		highlightedItem = null

func highlightItem(item, modulateItem: bool = true):
	if modulateItem:
		item.highlight()
	highlightedItem = item
	
	for line in container.get_children():
		if line.getItem() == highlightedItem:
			line.onConnectedHovered()
	
	
	playerDmgMeter.highlightSource(highlightedItem)
	opponentDmgMeter.highlightSource(highlightedItem)

func highlightSource(source, player):
	highlightedItem = [source, player]
	
	for line in container.get_children():
		if line.getSource() == source and line.player == player:
			line.onConnectedHovered()
	
	
	if player:
		playerDmgMeter.highlightSource(source)
	else:
		opponentDmgMeter.highlightSource(source)

func scrollToBottom():
	scrollContainer.set_v_scroll(10000)
	scrolledToBottom = false

func activateScrollWithArrow():
	scrollWithArrow = true
	lineArrow.show()

var replayingCombat: bool = false
var replayTime: float
var replaySpeed: float


func replayCombat(fromStart: bool, speed = 1.0):
	replayingCombat = true
	replaySpeed = speed
	activateScrollWithArrow()
	
	if (activeLine == null or fromStart or 
		activeLine.event.id == events.size() - 1):
		if speed < 0:
			replayTime = getCombatDuration() + 0.1
			scrollContainer.scroll_vertical = 100000
		else:
			replayTime = 0.0
			scrollContainer.scroll_vertical = 0
	else:
		replayTime = activeLine.event.timestamp
	
	
	Game.combatSceneNode.stopTimeTween()
	

func replayFinished():
	stopReplay()
	emit_signal("replay_finished")

func stopReplay():
	replayingCombat = false
	scrollWithArrow = false
	
	for event in emitterEventToChargeInstance:
		var charge = emitterEventToChargeInstance[event]
		charge.stop()
	
	

func physics_process_deferred():
	
	if eventsLogged <= 0:
		
		if Game.fightEnded:
			for i in 10:
				var done = replayDelayedEvent()
				if done: break
		else:
			replayDelayedEvent()
		
		
	eventsLogged = 0


func _physics_process(delta):
	call_deferred("physics_process_deferred")
	
	if not replayingCombat: return
	replayTime += delta * replaySpeed
	
	var prevEventNum = timestamps.bsearch(replayTime, false) - 1
	
	var timeAdvance = globalStatHistories[GlobalStat.TimeAdvance].getValueAt(prevEventNum)
	
	Game.combatSceneNode.setTime(replayTime + timeAdvance)
	
	if replaySpeed > 0:
		if prevEventNum >= events.size() - 1:
			scrollContainer.scroll_vertical = 100000
			replayFinished()
	else:
		if prevEventNum == - 1:
			prevEventNum = 0
			scrollContainer.scroll_vertical = 0
			replayFinished()
		
	var prevEvent = events[prevEventNum]
	var logLine = logLines[prevEventNum]
	
	if activeLine != logLine:
		
		var timestamp = timestamps[prevEventNum]
		var firstPrevEventNum = prevEventNum
		
		while firstPrevEventNum > 0:
			firstPrevEventNum -= 1
			if timestamp != timestamps[firstPrevEventNum]:
				break
		
		
		for eventI in range(firstPrevEventNum + 1, prevEventNum + 1):
			var event: CombatEvent = events[eventI]
			replayAnimation(event)

		
		onLineHoverEnd()
		moveArrowTo(logLine, false)
		replayLogLineEvent(logLine)
		replayElectricalCharges(logLine.event)
	
	updateDisplayCooldowns(prevEvent)
	playerDmgMeter.setTime(replayTime)
	opponentDmgMeter.setTime(replayTime)



func snapshotStack(character, stackType):
	statLoggers[character.playerId].logStack(stackType, eventNum, character.getStacks(stackType))

func snapshotDamageDealt(playerId, damageType, damage):
	statLoggers[playerId].logMetric(Game.ItemMetrics.Damage, damageType, damage, eventNum)

func snapshotMetric(playerId, metric, eventType, value):
	statLoggers[playerId].logMetric(metric, eventType, value, eventNum)

func snapshotItemMetric(item, metricIndex, playerId = null, withNextEvent = false):
	if playerId == null:
		playerId = item.character().playerId
	
	var connectedEventNum = eventNum
	if withNextEvent:
		connectedEventNum += 1
	statLoggers[playerId].logItemMetric(item, metricIndex, 
		connectedEventNum, item.getMetric(metricIndex))

func snapshotItemTooltipStat(item, statType, playerId = null, 
	withNextEvent = false, event = null):
	
	if playerId == null:
		playerId = item.character().playerId
	
	var connectedEventNum = eventNum
	if event != null:
		connectedEventNum = event.id
	elif withNextEvent:
		connectedEventNum += 1
	
	statLoggers[playerId].logItemStat(item, 
		statType, connectedEventNum, item.getStat(statType))
	
	item.queueTooltipUpdate()

func snapshotItemState(item, state, withNextEvent: bool, event: CombatEvent):
	var playerId = item.character().playerId
	var connectedEventNum = eventNum
	if event != null:
		connectedEventNum = event.id
	elif withNextEvent:
		connectedEventNum += 1
	
	statLoggers[playerId].logItemState(item, state, connectedEventNum)
	
	
	if loggingFinished:
		activeItemState[item] = state

func snapshotCharacterStat(character: Character, stat: int, 
	withNextEvent: bool = false, event: CombatEvent = null):
	var connectedEventNum = eventNum
	if event != null:
		connectedEventNum = event.id
	elif withNextEvent:
		connectedEventNum += 1
	var statValue = character.getStat(stat)
	statLoggers[character.playerId].logCharacterStat(stat, connectedEventNum, 
		statValue)
	character.statsDisplay.onStatChanged(stat, statValue)

func updateDisplayCooldowns(event):
	for i in 2:
		var statLogger: CombatStatLogger = statLoggers[i]
		for item in itemsWithCooldown[i]:
			var lastEntry = statLogger.getLastEventForStat(item, Item.Stat.Cooldown, event.id)
			var lastEntry_EventNum = lastEntry[0]
			if lastEntry_EventNum >= events.size():
				
				print("eventnum exceeded")
				lastEntry_EventNum = events.size() - 1
			var timeSinceEntry: float
			if replayingCombat:
				timeSinceEntry = replayTime - getTimeOfEvent(lastEntry_EventNum)
			else:
				timeSinceEntry = event.timestamp - getTimeOfEvent(lastEntry_EventNum)
			var encodedCd = lastEntry[1]
			
			item.reconstructCooldown(encodedCd, timeSinceEntry)

func onLineHovered(logLine: CombatLogLine):
	if replayingCombat:
		return
	
	var event: CombatEvent = logLine.event
	
	moveArrowTo(logLine, true)
	showArrow()
	var timeAdvance = globalStatHistories[GlobalStat.TimeAdvance].getValueAt(event.id)
	
	
	var time = event.timestamp + timeAdvance
	replayTime = time
	
	Game.combatSceneNode.interpolateTime(time)
	replayLogLineEvent(logLine)
	updateDisplayCooldowns(event)
	
	unhighlightItem()
	var item = logLine.getItem()
	if item != null:
		highlightItem(item)
		
	else:
		var source = logLine.getSource()
		if source:
			highlightSource(source, event.getMainActor() == Character.ID.PLAYER)
	
	replayAnimation(event)
	
	replayElectricalCharges(event)

func replayAnimation(event):
	var origin = event.getOrigin()
	if origin is Item:
		origin.activateFromEvent(event)
	else:
		var targetId = event.target
		if event.hasParam("damage"):
			targetId = getOtherCharacterId(targetId)
		getCharacterFromId(targetId).replayEvent(event)

func replayLogLineEvent(logLine: CombatLogLine):
	var event: CombatEvent = logLine.event
	for i in 2:
		var statLogger: CombatStatLogger = statLoggers[i]
		var character = getCharacterFromId(i)
		for stat in Character.Stat.values():
			if stat == Character.Stat.Stamina:
				pass
			var value = statLogger.getCharacterStatAt(stat, event.id)
			if value != activeCharacterStats[i][stat]:
				character.setStat(stat, value)
				character.statsDisplay.onStatChanged(stat, value)
				activeCharacterStats[i][stat] = value

		for stack in statLogger.stackHistories:
			var numStacks = statLogger.getStackAt(stack, event.id)
			
			character.setStacks(stack, numStacks)
		
		
		for item in statLogger.itemTooltipHistories:
			for stat in Item.Stat.values():
				item.setStat(stat, statLogger.getItemStatAt(item, stat, event.id))
				
		for item in statLogger.itemStateHistories:
			if statLogger.hasStateData(item):
				
				var state = statLogger.getItemStateAt(item, event.id)
				if not Util.equals(state, activeItemState[item]):
					item.onStateChanged(state)
					activeItemState[item] = state
		
		updateDamageMeter(i, event)
	
	if isLineVisible(logLine) and isLineMinimized(logLine):
		
		if tooltip != null:
			tooltip.queue_free()
		tooltip = logLineTooltipScene.instance()
		tooltipNode.add_child(tooltip)
		var tooltipLogLine = tooltip.get_node("VBoxContainer/LogLine")
		tooltipLogLine.setEvent(event)
		tooltipLogLine.setStylebox(tooltipLogLine.State.Tooltip)
		tooltip.updateSize()
		var toolPos = logLine.rect_global_position
		toolPos.x -= 20
		toolPos.y += 50
		var toolSize = Vector2(rect_size.x, logLine.rect_size.y)
		
		tooltip.forceUpdatePosition(toolPos, toolSize)

func onLineHoverEnd():
	if tooltip != null:
		tooltip.queue_free()
		tooltip = null

func updateDamageMeter(playerId, event):
	if playerId == 0:
		playerDmgMeter.updateMeter(event, statLoggers[playerId])
	else:
		opponentDmgMeter.updateMeter(event, statLoggers[playerId])


func createEvent_Attack(damageRes, triggerEvent = null):
	var event
	var origin = damageRes.damageSource.origin
	var character = origin.character()
	
	if damageRes.hasHit():
		
		
		if damageRes.wasCriticalHit():
			event = createEvent(triggerEvent, origin, Game.EventType.CriticalDamage)
		else:
			event = createEvent(triggerEvent, origin, Game.EventType.DealDamage)
		event.setParam("damage", damageRes.damage)
		
		var attackedCharacter
		if damageRes.damageSource.hasType(DamageSource.Type.SelfDamage):
			attackedCharacter = character
		else:
			attackedCharacter = character.opponent
		snapshotCharacterStat(attackedCharacter, Character.Stat.Health)
		snapshotStack(attackedCharacter, Game.EventType.Block)
		updateDamageMeter(attackedCharacter.playerId, event)
	else:
		event = createEvent(triggerEvent, origin, Game.EventType.MissedAttack)
	
	return event




func createEvent_Damage(damageRes: DamageResult, damagingPlayerId, triggerEvent = null):
	
	
	
	var event
	if damageRes.wasCriticalHit():
		event = createEvent(triggerEvent, damageRes.damageSource.types[0], 
			Game.EventType.CriticalDamage)
	else:
		event = createEvent(triggerEvent, damageRes.damageSource.types[0], 
			Game.EventType.DealDamage)
	event.setParam("damage", damageRes.damage)
	event.setTarget(damagingPlayerId)
	var damagingCharacter = getCharacterFromId(damagingPlayerId)
	var damagedCharacter = damagingCharacter.opponent
	snapshotCharacterStat(damagedCharacter, Character.Stat.Health)
	snapshotStack(damagedCharacter, Game.EventType.Block)
	snapshotDamageDealt(damagingPlayerId, damageRes.damageSource.types[0], damageRes.damage)
	updateDamageMeter(damagingPlayerId, event)
	return event

func createEvent_Heal(amount: int, playerId: int, origin, 
	triggerEvent: CombatEvent = null):
	
	var event = createEvent(triggerEvent, origin, Game.EventType.Health)
	event.setParam("amount", amount)
	event.setTarget(playerId)
	snapshotCharacterStat(getCharacterFromId(playerId), Character.Stat.Health)
	return event

func createEvent_LoseHealth(amount: int, playerId: int, origin, 
	triggerEvent: CombatEvent = null):
	
	var event = createEvent(triggerEvent, origin, Game.EventType.LoseHealth)
	event.setParam("amount", amount)
	event.setTarget(playerId)
	snapshotCharacterStat(getCharacterFromId(playerId), Character.Stat.Health)
	return event

func createEvent_Stack(type: int, item: Item, amount: int, 
	playerId: int, triggerEvent: CombatEvent = null, 
	used: bool = false, reflected: bool = false):
	
	var event = createEvent(triggerEvent, item, type)
	event.setParam("amount", amount)
	event.setParam("used", used)
	event.setParam("reflected", reflected)
	event.setTarget(playerId)
	snapshotStack(getCharacterFromId(playerId), type)
	
	if type == Game.EventType.Empower:
		for item in getCharacterFromId(playerId).INVENTORY.getItems():
			if item.isWeapon() and item.canBeEmpowered():
				snapshotItemTooltipStat(item, Item.Stat.MinDamage)
				snapshotItemTooltipStat(item, Item.Stat.MaxDamage)
	
	if type == Game.EventType.Heat or type == Game.EventType.Cold:
		for item in getCharacterFromId(playerId).INVENTORY.getItems():
			if item.hasCooldown():
				snapshotItemTooltipStat(item, Item.Stat.Speed)
				snapshotItemTooltipStat(item, Item.Stat.Cooldown)
	
	if type == Game.EventType.Lucky or type == Game.EventType.Blind:
		for item in getCharacterFromId(playerId).INVENTORY.getItems():
			if item.isWeapon():
				snapshotItemTooltipStat(item, Item.Stat.Accuracy)
	
	return event

func createEvent_StackTemporary(type, item, amount, duration, playerId, 
	triggerEvent, reflected: bool = false):
	var event = createEvent_Stack(type, item, amount, playerId, triggerEvent)
	event.setParam("duration", duration)
	event.setParam("reflected", reflected)
	return event

func createEvent_StackTimeout(type, item, amount, playerId, triggerEvent):
	var event = createEvent_Stack(type, item, amount, playerId, triggerEvent)
	event.setParam("timeout", true)
	return event

func createEvent_StackResistOrNullify(type, item, amount, playerId, triggerEvent, 
	reflect: bool = false):
	var event = createEvent_Stack(type, item, amount, playerId, triggerEvent)
	event.setParam("resisted", true)
	event.setParam("reflected", reflect)
	return event

func createEvent_StackProtect(type, item, amount, playerId, triggerEvent):
	var event = createEvent_Stack(type, item, amount, playerId, triggerEvent)
	event.setParam("protected", true)
	return event

func createEvent_Stun(item, duration, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.Stun)
	event.setParam("duration", duration)
	event.setTarget(playerId)
	return event

func createEvent_StunResist(item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.StunResisted)
	event.setTarget(playerId)
	return event

func createEvent_InvulnerableStart(item, duration, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.InvulnerableStart)
	event.setParam("duration", duration)
	event.setTarget(playerId)
	return event

func createEvent_InvulnerableEnd(item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.InvulnerableEnd)
	event.setTarget(playerId)
	return event

func createEvent_Stamina(amount, item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.Stamina)
	event.setParam("stamina", floor(amount * 10) / 10.0)
	event.setTarget(playerId)
	return event

func createEvent_DrainStamina(amount, item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.DrainStamina)
	event.setTarget(playerId)
	event.setParam("stamina", floor(amount * 10) / 10.0)
	return event

func createEvent_OutOfStamina(item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.OutofStamina)
	event.setTarget(playerId)
	return event

func createEvent_DamageBuff(item, buffedItem, damage, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.DamageBuff)
	event.setTarget(playerId)
	event.setParam("item", buffedItem.getTranslatedName())
	event.setParam("damage", damage)
	return event

func createEvent_TemporaryMaxHealth(item, amount, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.TemporaryMaxHealth)
	event.setParam("amount", amount)
	snapshotCharacterStat(item.character(), Character.Stat.Health)
	snapshotCharacterStat(item.character(), Character.Stat.MaxHealth)
	return event

func createEvent_TemporaryMaxStamina(item, amount, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.TemporaryMaxStamina)
	event.setParam("stamina", amount)
	snapshotCharacterStat(item.character(), Character.Stat.Stamina)
	snapshotCharacterStat(item.character(), Character.Stat.MaxStamina)
	return event


func createEvent_BattleRageStart(item, duration, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.BattleRageStart)
	event.setParam("duration", duration)
	return event

func createEvent_BattleRageEnd(playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, Game.EventType.BattleRageEnd, 
		Game.EventType.BattleRageEnd)
	event.setTarget(playerId)
	return event

func createEvent_Reincarnate(item, health: int, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.Reincarnate)
	event.setParam("health", health)
	snapshotCharacterStat(item.character(), Character.Stat.Health)
	return event

func createEvent_Activation(item, triggerEvent = null):
	var event = createEvent(triggerEvent, item, Game.EventType.Activation)
	return event

func createEvent_DamChange(item, amount: float, isPercent: bool, 
	duration = null, type = null, triggerEvent = null):
	
	var event = null
	if amount > 0:
		event = createEvent(triggerEvent, item, Game.EventType.DamIncrease)
	else:
		event = createEvent(triggerEvent, item, Game.EventType.DamReduction)
		
	event.setParam("amount", amount)
	event.setParam("isPercent", isPercent)
	if duration != null:
		event.setParam("duration", duration)
	if type != null:
		event.setParam("type", type)
	return event

func logWin():
	var event = createEvent(null, Game.EventType.Win, Game.EventType.Win)
	logEvent(event, true)
	return event

func logLoss():
	var event = createEvent(null, Game.EventType.Loss, Game.EventType.Loss)
	logEvent(event, true)
	return event

func moveArrowTo(line: CombatLogLine, ensureVisibility: bool):
	activeLine = line
	if ensureVisibility:
		if activeLine.visible:
			scrollContainer.ensure_control_visible(activeLine)
	










func showArrow():
	lineArrow.show()

func hideArrow():
	lineArrow.hide()

func onButtonPressed():
	if visible:
		close()
	else:
		open()
		Game.setTutorialDone(Game.TutorialSteps.CombatLog)
		tutorialAni.play("RESET")

func open() -> void :
	
	
	
	while true:
		var done = replayDelayedEvent()
		if done: break
	
	show()
	
	buttonHint.translationKey = "BUTTON_CloseLog"
	buttonHint.updateText()
	
	if playerDmgMeter.isOpen:
		playerDmgMeter.onShow()
	if opponentDmgMeter.isOpen:
		opponentDmgMeter.onShow()
	
	
	if not Game.isTutorialDone(Game.TutorialSteps.CombatLogButtons):
		buttonTutorialAni.play("Tutorial")
	
	scrollContainer.onOpen()

func close() -> void :
	hide()
	
	buttonHint.translationKey = "BUTTON_OpenLog"
	buttonHint.updateText()
	
	dragging = false
	scrollTimer.stop()
	endDragging()
	onHorizontalResizeButtonUp()
	onVerticalResizeButtonUp()
	scrollContainer.onClose()
	
	if replayingCombat:
		replayFinished()

func onScrollbarVisibilityChanged():
	if scrollContainer.get_v_scrollbar().visible:
		scrollContainer.rect_size.x = rect_size.x - 8
	else:
		scrollContainer.rect_size.x = rect_size.x - 35
		
	

func canDrag():
	return .canDrag() and not scrollContainer.scrollbarHovered


func updateIdle() -> void :
	
	if activeLine != null:
		var lastVisibleLine = getLastVisibleLine()
		if lastVisibleLine == null: return
		
		var pos = lastVisibleLine.rect_global_position.y + lastVisibleLine.rect_size.y * 0.5
		var containerStart = scrollContainer.rect_global_position.y
		var containerEnd = containerStart + scrollContainer.rect_size.y
		
		
		if scrollWithArrow:

			var diffToTop = (containerStart + 20) - pos
			if diffToTop > 0:
				scrollContainer.scroll_vertical -= diffToTop
				pos += diffToTop

			var diffToBottom = pos - containerEnd + 20
			if diffToBottom > 0:
				scrollContainer.scroll_vertical += diffToBottom
				pos -= diffToBottom
		else:
			if containerEnd + 20 < pos or pos < containerStart - 20:
				lineArrow.hide()
			else:
				lineArrow.show()
		
		lineArrow.global_position.y = pos
	
	

func onResizeButtonDown():
	.onResizeButtonDown()
	hideArrow()

func _on_CloseButton_pressed() -> void :
	close()

func onHorizontalResizeButtonDown() -> void :
	.onHorizontalResizeButtonDown()
	hideArrow()

func getNumEvents() -> int:
	return events.size()

func getTimeOfEvent(_eventNum: int) -> float:
	if _eventNum < 0: return 0.0
	return events[_eventNum].timestamp

func getCombatDuration() -> float:
	return events.back().timestamp

func getLastEventNum() -> int:
	return eventNum

func onPlayerToggled(pressed: bool):



	showPlayerEvents = pressed
	onFilterChanged()

func onOpponentToggled(pressed: bool):
	showOpponentEvents = pressed
	onFilterChanged()

func isLineVisible(line: CombatLogLine) -> bool:
	if (line.getType() == Game.EventType.Activation and 
		activationsState == ActivationsState.Hide):
			return false
	
	return true

func isLineMinimized(line: CombatLogLine) -> bool:
	if not showPlayerEvents and line.player:
		return true
	
	if not showOpponentEvents and not line.player:
		return true
	
	if (line.getType() == Game.EventType.Activation and 
		activationsState == ActivationsState.Minimized):
		return true
	
	if searchTerm != "":
		if line.getText().findn(searchTerm) == - 1:
			return true
		
	return false




func getLastVisibleLine() -> CombatLogLine:
	if activeLine == null:
		if logLines.empty():
			return null
		return logLines[0]
	
	var lastVisibleLine: CombatLogLine = null
	
	for line in logLines:
		if line.visible:
			lastVisibleLine = line
		if line == activeLine:
			break
	
	if lastVisibleLine == null:
		for line in logLines:
			if line.visible:
				lastVisibleLine = line
				break
	
	return lastVisibleLine

func getNextVisibleLine() -> CombatLogLine:
	
	var index = logLines.find(activeLine)
	
	
	while true:
		index += 1
		index %= logLines.size()
		if logLines[index].visible:
			return logLines[index]
	
	return activeLine

func getPreviousVisibleLine() -> CombatLogLine:
	var index = logLines.find(activeLine)
	
	while true:
		index = (index - 1 + logLines.size()) % logLines.size()
		if logLines[index].visible:
			return logLines[index]
	
	return activeLine

var activeLineYBeforeFilterChange: float

func onFilterChanged():
	if activeLine != null:
		activeLineYBeforeFilterChange = activeLine.rect_global_position.y
	
	for line in container.get_children():
		line.visible = isLineVisible(line)
		line.setMinimized(isLineMinimized(line))
	
	
	if activeLine != null:
		
		activeLine = getLastVisibleLine()
		
		if activeLine != null:
			lineArrow.hide()
			Util.callNextFrame(self, "updateScroll")
	
func updateScroll():
	lineArrow.show()
	var newLinePos = activeLine.rect_global_position.y
	var diff = newLinePos - activeLineYBeforeFilterChange
	scrollContainer.scroll_vertical += diff

func onSearchTextChanged(newText):
	searchTerm = newText
	onFilterChanged()

func getStylebox(player: bool, state: int, faded: bool):
	var stylebox
	if player:
		stylebox = playerStyleboxes[state]
	else:
		stylebox = opponentStyleboxes[state]
		
	if faded:
		return fadedStyleboxes[stylebox]
	else:
		return stylebox

func setActivationState(newState: int):
	activationsState = newState
	onFilterChanged()

func snapshotGlobalStat(stat: int, newValue):
	globalStatHistories[stat].addValue(eventNum, newValue)



func _input(event):
	if InputBlocker.isActive(): return
	if (Game.fightEnded and not replayingCombat and activeLine != null and 
		Util.isKeyOrJoyButton(event)):
		
		if Util.isActionPressed_event(event, "shift_down"):
			var nextLine = getNextVisibleLine()
			onLineHovered(nextLine)
			scrollTimer.start(0.2)
			
		elif Util.isActionPressed_event(event, "shift_up"):
			var nextLine = getPreviousVisibleLine()
			onLineHovered(nextLine)
			scrollTimer.start(0.2)
		
		elif Util.isActionReleased_event(event, "shift_down"):
			if not Util.isActionPressed("shift_up"):
				scrollTimer.stop()
				
		elif Util.isActionReleased_event(event, "shift_up"):
			if not Util.isActionPressed("shift_down"):
				scrollTimer.stop()

func scrollTimerTimeout():
	if Util.isActionPressed("shift_down"):
		var nextLine = getNextVisibleLine()
		onLineHovered(nextLine)
		scrollTimer.start(0.1)
		
	elif Util.isActionPressed("shift_up"):
		var nextLine = getPreviousVisibleLine()
		onLineHovered(nextLine)
		scrollTimer.start(0.1)

func onGetRects():
	if visible:
		Game.addOcclusion(rect_global_position, rect_size, 0)
		
	for dmgMeter in [playerDmgMeter, opponentDmgMeter]:
		if dmgMeter.isVisible():
			Game.addOcclusion(dmgMeter.rect_global_position, dmgMeter.rect_size, 0)

func onCursorWarp():
	if visible:
		for node in warpPointNodes:
			if node.is_visible_in_tree() and Util.isControlEnabled(node):
				Game.addControlOfInterest(node, Vector2.ZERO, null, null, 1)
		for line in logLines:
			Game.addControlOfInterest(line, Vector2.ZERO, scrollContainer, line, 1)
		
		for dmgMeter in [playerDmgMeter, opponentDmgMeter]:
			for plot in dmgMeter.plots:
				for entry in dmgMeter.plotToEntry.get(plot, []):
					Game.addControlOfInterest(entry, Vector2(60, 10), 
						dmgMeter.scrollContainer, entry, 1)

func logElectricalCharge(emitterEvent: CombatEvent, duration: float, cells: Array):
	
	if emitterEvent == null:
		Util.eprint("Charge event null")
		return
	
	var data = ElectricalChargeData.new(emitterEvent, duration, cells)
	electricalCharges.push_back(data)
	
	if emitterEvent.origin.character() == Game.PLAYER:
		numPlayerCharges += 1
	
	if numPlayerCharges == 10:
		SteamHelper.unlockAchievement("Charges", false)

func replayElectricalCharges(event: CombatEvent):
	var newChargeInstances: = {}
	
	for chargeData in electricalCharges:
		var progress = chargeData.getProgressAt(event)
		if progress >= 0:
			var charge = emitterEventToChargeInstance.get(chargeData)
			if charge == null:
				charge = ObjectPool.instance(Game.electricalChargeScene)
				Game.playerNode.add_child(charge)
			
			
			newChargeInstances[chargeData] = charge
			
			var stop = not replayingCombat or replaySpeed < 0
			
			charge.seek(chargeData.emitterEvent.origin, chargeData.cells, 
				chargeData.duration, progress, stop)
			
	
	for chargeData in emitterEventToChargeInstance:
		if not chargeData in newChargeInstances:
			var charge = emitterEventToChargeInstance[chargeData]
			charge.returnToObjectPool()

	emitterEventToChargeInstance = newChargeInstances

class ElectricalChargeData:

	var emitterEvent: CombatEvent
	var duration: float
	
	var cells: Array
	
	func _init(event: CombatEvent, dur: float, _cells: Array):
		emitterEvent = event
		duration = dur
		
		cells = _cells
	
	func getProgressAt(event: CombatEvent):
		
		if emitterEvent.id > event.id:
			return - 1
		
		
		if emitterEvent.timestamp + duration < event.timestamp:
			return - 2
		
		var timePassed = event.timestamp - emitterEvent.timestamp
		return timePassed
	
	
