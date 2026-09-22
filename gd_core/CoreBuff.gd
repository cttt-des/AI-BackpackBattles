# =============================================================================
# CoreBuff.gd — 无头战斗内核：栈（buff/debuff）语义
# =============================================================================
# 对齐源码：Core/Buff.gd（全文 361 行）
#
# 逐字保留：抗性逐栈 flip、减益逐栈反射（递归 + debuffReflectStacks 吸收）、
#   resistStacks / buffProtectStacks 吸收、净化保护、永久/临时栈分离与
#   「先永久、临时先删 timeout 最远者」的消耗顺序、MAX_STACKS（Block 100000 / 其余 10000）、
#   onTimeout 的「取最早到期、否则立即递归」逻辑。
#
# 剥离内容：
#   · `counter` —— 原为 HUD 节点（BuffCounter），全部调用改走 ctx.hooks.activateBuffCounter
#   · `Util.spawnReflectLabel / spawnResistedLabel / spawnProtectedLabel / spawnBuffLabel_item`
#     → ctx.hooks 同名方法
#   · `Game.combatLog.createEvent_*` → ctx.combat_log（事件对象结构不变）
#   · `timer = Timer.new(); character.add_child(timer)` → 内核内计时器 `_timer_left`
#
# ★ 唯一的机制替换（见 docs/gd_core_truth.md 第 4 节）：
#   原版临时栈超时用 Godot Timer（one_shot + TIMER_PROCESS_PHYSICS）。
#   无头内核改为由 CoreCharacter 每物理帧驱动 `_tick(delta)`，并在
#   「全部物品 tick 完成后」统一检查超时。以固定 60Hz 步长推进时，
#   `start(duration)` / `get_time_left()` 的语义等价；
#   与物品 tick 的相对先后由本内核显式定义（原版取决于节点树顺序）。
# =============================================================================
extends Reference
class_name CoreBuff


var type: int
var isBuff: bool
var character                # CoreCharacter
var current: int = 0
var permanentStacks: int = 0

var resistChancePercent: float = 0.0
var resistStacks: int = 0

var reflectChancePercent: float = 0.0

var cleanseProtectionChancePercent: float = 0.0

var signalName: String
var temporaryStacks: Array = []
var nextTemporaryTimeout: int
var MAX_STACKS: int

# 内核计时器（替代 Godot Timer，语义等价）
var _timer_left: float = 0.0
var _timer_active: bool = false

var ctx


func init(_type, _character, _signalName: String = ""):
	type = _type
	isBuff = CoreConst.isBuff(type)
	character = _character
	signalName = _signalName
	ctx = _character.ctx
	
	if type == CoreConst.EventType.Block:
		MAX_STACKS = 100000
	else:
		MAX_STACKS = 10000
	
	return self


func getStacks():
	return current


func setStacks(amount: int):
	current = amount
	ctx.hooks.activateBuffCounter(character, type)


func reset():
	setStacks(0)
	resistStacks = 0
	resistChancePercent = 0.0
	cleanseProtectionChancePercent = 0.0
	reflectChancePercent = 0.0


func changeResistChance(chance):
	resistChancePercent += chance


func changeResistStacks(amount):
	resistStacks = max(0, resistStacks + amount)


func changeCleanseProtectionChance(chance):
	cleanseProtectionChancePercent += chance


func changeReflectChance(amount):
	reflectChancePercent += amount


func gainStacks(amount: int, item = null, triggerEvent = null, 
	reflect: bool = false):
	
	return gainTemporary(amount, - 1, item, triggerEvent, reflect)


func gainTemporary(amount: int, duration: float, item = null, 
	triggerEvent = null, reflect: bool = false):
	
	var event = null
	
	if amount > 0:
		
		var resisted = 0
		var totalResistChance = resistChancePercent
		
		if item != null and not reflect:
			totalResistChance -= item.getAmplificationChancePercent(type)
		
		if totalResistChance > 0:
			for i in amount:
				if ctx.rng.flipPercent(totalResistChance):
					resisted += 1
		elif totalResistChance < 0:
			for i in amount:
				if ctx.rng.flipPercent( - totalResistChance):
					amount += 1
		
		var left = amount - resisted
		
		var reflected = 0
		
		if not isBuff:
			
			if not reflect:
				for i in amount:
					if ctx.rng.flipPercent(reflectChancePercent):
						reflected += 1
				
				left -= reflected
				
				var reflectedByStacks = 0
				if left > 0:
					reflectedByStacks = min(left, character.debuffReflectStacks)
				
				if reflectedByStacks > 0:
					reflected += reflectedByStacks
					left -= reflectedByStacks
					character.changeDebuffReflectStacks( - reflectedByStacks)
				
				if reflected > 0:
					amount -= reflected
					ctx.hooks.spawnReflectLabel(type, character.randBuffLabelPos(), reflected)
			
			var ownStacksUsed = min(left, resistStacks)
			resisted += ownStacksUsed
			left -= ownStacksUsed
			resistStacks -= ownStacksUsed
			
			if left > 0:
				var characterStacksUsed = min(left, character.debuffResistStacks)
				resisted += characterStacksUsed
				character.changeDebuffResistStacks( - characterStacksUsed)
		
		if resisted > 0:
			amount -= resisted
			ctx.hooks.spawnResistedLabel(type, character.randBuffLabelPos(), resisted)
			var resistedEvent = ctx.combat_log.createEvent_StackResistOrNullify(type, 
						item, resisted, character.playerId, triggerEvent, reflect)
			ctx.bus.logEvent(resistedEvent)
		
		if amount > 0:
			amount = int(min(amount, MAX_STACKS - current))
			if amount == 0: return null
			
			current += amount
			ctx.hooks.activateBuffCounter(character, type)
			
			if duration < 0:
				permanentStacks += amount
			else:
				var timeout = ctx.time + duration
				var tempStacks = TemporaryStacks.new(amount, timeout, item)
				temporaryStacks.push_back(tempStacks)
				
				if not _timer_active:
					_startTimer(duration)
					nextTemporaryTimeout = 0
				else:
					if duration < _timer_left:
						_stopTimer()
						_startTimer(duration)
						nextTemporaryTimeout = temporaryStacks.size() - 1
			
			if item:
				var isPlayer = (character == ctx.player)
				
				if not isBuff:
					isPlayer = not isPlayer
				
				item.stackChanged(type, amount, isPlayer)
				
				if duration <= 0:
					event = ctx.combat_log.createEvent_Stack(type, item, 
						amount, character.playerId, triggerEvent, false, reflect)
				else:
					event = ctx.combat_log.createEvent_StackTemporary(type, 
						item, amount, duration, character.playerId, triggerEvent, 
						reflect)
				
				var appliedToOpponent = (character != item.character())
				ctx.hooks.spawnBuffLabel_item(type, item, amount, appliedToOpponent)
				
				ctx.bus.emitEvent(character, signalName, event, [event.getAmount(), event])
		
		if reflected > 0:
			character.opponent.gainStacksTemporary(type, reflected, duration, 
				item, triggerEvent, true)
		
	return event


func loseStacks(amount: int, item = null, triggerEvent = null, used = false):
	
	amount = min(current, amount)
	
	if not used:
		var protected = 0
		
		if cleanseProtectionChancePercent > 0:
			for i in amount:
				if ctx.rng.flipPercent(cleanseProtectionChancePercent):
					protected += 1
		
		elif cleanseProtectionChancePercent < 0:
			for i in amount:
				if ctx.rng.flipPercent( - cleanseProtectionChancePercent):
					protected -= 1
		
		amount -= protected
		amount = clamp(amount, 0, current)
		
		if amount > 0 and resistStacks > 0:
			var protectedByStacks = min(amount, resistStacks)
			protected += protectedByStacks
			amount -= protectedByStacks
			resistStacks -= protectedByStacks
		
		if (isBuff and 
			type != CoreConst.EventType.Block and 
			amount > 0 and 
			character.buffProtectStacks > 0):
			
			var protectedByStacks = min(amount, character.buffProtectStacks)
			protected += protectedByStacks
			amount -= protectedByStacks
			character.buffProtectStacks -= protectedByStacks
		
		if protected > 0:
			ctx.hooks.spawnProtectedLabel(type, character.randBuffLabelPos(), protected)
			var protectedEvent = ctx.combat_log.createEvent_StackProtect(type, 
				item, protected, character.playerId, triggerEvent)
			ctx.bus.logEvent(protectedEvent)
	
	if permanentStacks >= amount:
		permanentStacks -= amount
	else:
		var tempToCleanse = amount - permanentStacks
		permanentStacks = 0
		
		while tempToCleanse > 0:
			if temporaryStacks.empty():
				break
			
			var farthestTimeout = 0
			var farthestIndex = - 1
			for i in temporaryStacks.size():
				var stacks = temporaryStacks[i]
				if stacks.timeout > farthestTimeout:
					farthestTimeout = stacks.timeout
					farthestIndex = i
			
			var farthest = temporaryStacks[farthestIndex]
			if farthest.amount > tempToCleanse:
				farthest.amount -= tempToCleanse
				tempToCleanse = 0
				
			else:
				tempToCleanse -= farthest.amount
				temporaryStacks.remove(farthestIndex)
				
				if temporaryStacks.empty():
					_stopTimer()
	
	return changeCurrentLogShowLabel(false, amount, item, triggerEvent, used)


func changeCurrentLogShowLabel(isTimeout: bool, amount: int, 
	item = null, triggerEvent = null, used: bool = false):
	
	var change = min(current, amount)
	
	if change > 0:
		current -= change
		ctx.hooks.activateBuffCounter(character, type)
		
		if item:
			var isPlayer = (character == ctx.player)
			if not used:
				if isBuff:
					isPlayer = not isPlayer
			
			item.stackChanged(type, - change, isPlayer, used)
			
			var event
			if isTimeout:
				event = ctx.combat_log.createEvent_StackTimeout(type, item, - change, character.playerId, triggerEvent)
			else:
				event = ctx.combat_log.createEvent_Stack(type, item, - change, character.playerId, triggerEvent, used)
			
			ctx.bus.emitEvent(character, signalName, event, [event.getAmount(), event])
			
			var appliedToOpponent = (character != item.character())
			ctx.hooks.spawnBuffLabel_item(type, item, - change, appliedToOpponent)
			
			return event
	
	return null


func onTimeout():
	var timedOutStacks = temporaryStacks[nextTemporaryTimeout]
	changeCurrentLogShowLabel(true, timedOutStacks.amount, timedOutStacks.item)
	temporaryStacks.remove(nextTemporaryTimeout)
	
	if not temporaryStacks.empty():
		var earliestTimeout = INF
		var earliestIndex = - 1
		for i in temporaryStacks.size():
			var stacks = temporaryStacks[i]
			if stacks.timeout < earliestTimeout:
				earliestTimeout = stacks.timeout
				earliestIndex = i
		
		nextTemporaryTimeout = earliestIndex
		var delay = earliestTimeout - ctx.time
		if delay <= 0.01:
			onTimeout()
		else:
			_startTimer(delay)


func combatEnd():
	_stopTimer()
	temporaryStacks.clear()


# ── 内核计时器（语义等价于 Godot Timer(one_shot, TIMER_PROCESS_PHYSICS)） ──

func _startTimer(duration: float) -> void :
	_timer_left = duration
	_timer_active = true


func _stopTimer() -> void :
	_timer_active = false
	_timer_left = 0.0


func isTimerActive() -> bool:
	return _timer_active


func _tick(delta: float) -> void :
	if not _timer_active:
		return
	_timer_left -= delta
	if _timer_left <= 0.0:
		_timer_active = false
		_timer_left = 0.0
		onTimeout()


class TemporaryStacks extends Reference:
	var amount: int
	var timeout: float
	var item
	
	func _init(_amount, _timeout, _item = null):
		amount = _amount
		timeout = _timeout
		item = _item
