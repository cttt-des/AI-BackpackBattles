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
#     ★ 这三个标签钩子**去掉了 `pos` 形参**（原版由 `character.randBuffLabelPos()` 供值）。
#       那个表达式不是纯取值：它内部抽两次 `Util.rng.randf_range`，而结果只喂给一个
#       表现为空实现的钩子 —— 于是「一次纯表现抽样」被夹带进判定路径，会平移后续所有
#       随机判定。内核的不变式是「写入 rng 的调用点都参与判定」，故整体删除该实参
#       （与文件头 CoreCharacter「伤害数字坐标整体删除（纯表现）」同一政策）。
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
# ★ np25 timeout1t：严格三变量模型，逐位映射 oracle_fight.gd drive_timers 注册表
#   （:880-924）——引擎读数被独立建模，_startTimer 只改写它，绝不能直赋
#   _timer_left：
#     _timer_eng   ≡ Godot Timer.time_left / drive_timers 的 eng
#                    （start(t) 时=t、stop() 时=0，其余每帧不变——阻塞循环下冻结）
#     _timer_left  ≡ 注册表 e[0]（自记剩余；每 pass 递减或被 eng 重同步；fire 后
#                    保留 ≤0 发火值、停止期冻结——同值重启时它继续减出 ≤0 →
#                    立即 fire，正是 oracle e[0]=-1 遗留 + :901 的原版怪癖，
#                    run599_r10 实证：Light Goobert 每 3.25s 重 gain dur=3 Blind，
#                    oracle 393 gain+TO 同 tick、对手侧 409 gain→410 TO）
#     _timer_seen  ≡ 注册表 e[1]（上一 pass 的 eng 采样）
var _timer_left: float = 0.0
var _timer_active: bool = false
var _timer_eng: float = 0.0
# 「外部 start/重挂/延长改写引擎读数的当 tick：eng != _timer_seen → 重同步
#   **不递减**（首递减推迟到下一 tick）」，修「中途 (re)start 计时器恒早 1 tick」
#   （evt8=InvulnerableEnd 全族 + evt109=Blind StackTimeout 族 ≈84 场）。
#   停止期**不动** _timer_seen（对齐 :890-892 continue 不更新 e[1]）。
var _timer_seen: float = 0.0

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
					# ★ 表现层链消耗（Buff.gd:140 → Util.gd:952-959）：
					#   Util.spawnReflectLabel(event.type, target.randBuffLabelPos(),
					#   reflected) —— pos 是**调用点实参**（randBuffLabelPos =
					#   Character.gd:688-691 的 (-60,60)+(-40,40) 2 抽，必求值），
					#   spawnReflectLabel 内部再 randBuffLabelDir 1 抽。run570_r18
					#   逐抽对位实证（Snowball 反射 Cold：神谕在 roll×2 后恰有
					#   (-60,60)/(-40,40)/(-75,-120) 三行）——阶段1「只补 dir」的
					#   结论系 golden model ±1ULP 噪声期的误读，此处更正。
					var target = character.opponent
					target.randBuffLabelPos()
					target.randBuffLabelDir()
					ctx.hooks.spawnReflectLabel(type, reflected)
			
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
			# ★ 表现层链消耗（Buff.gd:125-128 → Util.gd:934-941）：
			#   Util.spawnResistedLabel(type, character.randBuffLabelPos(), resisted)
			#   —— pos 是调用点实参（2 抽）+ spawnResistedLabel 内部 dir（1 抽）。
			#   阶段1 曾按 run1160_r18 语料误读为「只补 dir」；reflect 分支的
			#   run570_r18 对位（2026-10-08）证明 pos 照常求值，三分支统一更正。
			character.randBuffLabelPos()
			character.randBuffLabelDir()
			ctx.hooks.spawnResistedLabel(type, resisted)
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
				_blnd_snap("gain", str(duration))
			
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
				# ★ np24 诊断（受控）：镜像神谕 SRC gain_label 行（Buff.gd:192-197）。
				ctx.rng.trace_diag("SRC", "gain_label",
						String(item.descriptor.identifier), str(type))
				# ★ 表现层链消耗还原（Buff.gd:194 → Util.gd:975-983 spawnBuffLabel_item
				#   → Item.gd:6485-6494 getNextFreeLabelPosition）：物品身上的 buff
				#   浮动标签在事件 emit 之前取位，恒消耗 Util.randInBox 2 抽
				#   （槽位复用 (10,10) / 兜底 (30,30)；buff_labels 设置神谕语料为开）。
				item.getNextFreeLabelPosition()
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
			# ★ 表现层链消耗（Buff.gd:236-237 → Util.gd:944-951）：同 resisted/
			#   reflect 三分支统一——pos 实参 2 抽 + spawnProtectedLabel 内部
			#   randBuffLabelDir 1 抽。
			character.randBuffLabelPos()
			character.randBuffLabelDir()
			ctx.hooks.spawnProtectedLabel(type, protected)
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
				_blnd_snap("partial", str(farthestIndex) + "amt" + str(farthest.amount))
				tempToCleanse = 0
				
			else:
				tempToCleanse -= farthest.amount
				temporaryStacks.remove(farthestIndex)
				_blnd_snap("lose", str(farthestIndex))
				
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
			# ★ 表现层链消耗还原（Buff.gd:317 → Util.gd:975-983 → Item.gd:6485-6494）：
			#   与 gainStacks 同面，但原版顺序是 **先 emit 事件后取位**（标签在
			#   事件之后）——顺序即链位，必须保持。
			item.getNextFreeLabelPosition()
			ctx.hooks.spawnBuffLabel_item(type, item, - change, appliedToOpponent)

			return event
	
	return null


func _blnd_snap(op: String, pre: String) -> void :
	if ctx.rng.oracle_trace and ctx.rng._stacktrace:
		var _b := ""
		for ts in temporaryStacks:
			_b += "(%s@%s)" % [str(ts.amount), str(ts.timeout).substr(0, 5)]
		# ★ np25 timeout1t：payload 追加 fr=<frame_counter>（六点全加、双门控
		#   不变）——rng_trace 行首数字是行号非时间，没有帧号无法读「gain→fire
		#   间隔 = K 或 K-1 次递减」这一决定性读数（验收门，见守门方案3）。
		ctx.rng.trace_diag("BLND", "p" + str(character.playerId) + " ty" + str(type) + " " + op + " " + pre, "len=" + str(temporaryStacks.size()) + " ntp=" + str(nextTemporaryTimeout) + " tm=" + str(_timer_active) + "/" + str(_timer_left) + "/e" + str(_timer_eng) + "/s" + str(_timer_seen) + " fr=" + str(ctx.frame_counter), _b)

func onTimeout():
	_blnd_snap("fire", str(nextTemporaryTimeout))
	# ★ np25（run1132_r18 定谳，gd1132v 无守卫跑实证）：Godot **release** 构建的
	#   数组越界读是**软错误并中止整个函数**——fire 行之后无 CLS/remove/重扫/
	#   重挂任何痕迹：栈原样保留、定时器已被 _tick 置死（该临时栈随后由普通
	#   loseStacks 路径清掉，Automanaton -5 铁证）。此处显式同语义**早退**；
	#   转写侧若不早退，Python 硬索引越界即进程崩溃（IndexError，py-only 族
	#   最后一场残因）。越界源=loseStacks 删 farthest 后 ntp 未回拨（原版同构
	#   隐患，仅 release 软错误语义下无症状）。
	if nextTemporaryTimeout < 0 or nextTemporaryTimeout >= temporaryStacks.size():
		return
	var timedOutStacks = temporaryStacks[nextTemporaryTimeout]
	changeCurrentLogShowLabel(true, timedOutStacks.amount, timedOutStacks.item)
	temporaryStacks.remove(nextTemporaryTimeout)
	_blnd_snap("timeout", str(nextTemporaryTimeout))
	
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
		_blnd_snap("rearm", "delay=" + str(delay) + " et=" + str(earliestTimeout) + " now=" + str(ctx.time))
		if delay <= 0.01:
			onTimeout()
		else:
			_startTimer(delay)


func combatEnd():
	_stopTimer()
	temporaryStacks.clear()


# ── 内核计时器（语义等价于 Godot Timer(one_shot, TIMER_PROCESS_PHYSICS)） ──

func _startTimer(duration: float) -> void :
	# ★ np25 timeout1t：对齐 Timer.start(t)——**只改写引擎读数**，_timer_left
	#   （≡e[0]）不动：oracle 注册表 e[0] 停留遗留值（fire 后 -1），同值重启
	#   （eng==e[1]）时走 :901 从遗留值继续减 → ≤0 当 tick 立即 fire。若在这里
	#   直赋 _timer_left=duration（初版 timeout1t 的写法），遗留值被冲掉 →
	#   重同步不递减 → 比 oracle 晚 1 tick 起（run599_r10 Blind 393/574 铁证）。
	_timer_eng = duration
	_timer_active = true


func _stopTimer() -> void :
	# 对齐 Timer.stop()：引擎读数归零；e[0]（_timer_left）从不在 stop 里被动
	# （oracle :891 的 e[0]=-1 是 drive_timers 停止分支每帧重置，gd 停止期
	# _tick 早退等价该 continue；_timer_left 冻结在遗留值，语义同 ≤0）。
	_timer_active = false
	_timer_eng = 0.0


func isTimerActive() -> bool:
	return _timer_active


func _tick(delta: float) -> void :
	if not _timer_active:
		return
	# ★ np25 timeout1t：逐行对齐 drive_timers :895-904。
	if _timer_eng == _timer_seen:
		_timer_left -= delta       # :901 eng==e[1] → e[0]-=dt（遗留值继续减=
	else:                          #   同值重启当 tick 立即 fire 的原版怪癖）
		_timer_left = _timer_eng   # :899 eng!=e[1] → e[0]=eng 重同步（不递减）
	_timer_seen = _timer_eng       # :902 e[1]=eng（每 pass 更新，先于 fire 判定）
	if _timer_left > 0.0:          # :903-904
		return
	_timer_active = false          # :910 one_shot 自停先于派发
	_timer_eng = 0.0               # :910 stop() → 引擎读数归零；_timer_left
	onTimeout()                    #   保留 ≤0 发火值（下一次同值重启靠它立即 fire）
	if _timer_active:              # :915-917 handler 内重挂（rearm start(delay)）
		_timer_left = _timer_eng   #   → e[0]=e[1]=新引擎读数，下一 tick 照常递减
		_timer_seen = _timer_eng


# ★ np25 timeout1t：rebuild_timer_registry 等价（oracle_fight.gd:690 调用、
#   :972-987 实现——activateItems 之后、手动 tick 循环之前把全部 Timer 以
#   [left,left]=[eng,eng] 重入册；停止态 get_time_left()=0）。由
#   CoreCombat.activateItems 末尾逐角色委托。激活期 start 的计时器 → 战斗首帧
#   即递减；战斗中首 gain 的新 Buff [0,0] → start 后首帧重同步——两分支由此锚定。
func rebuildTimerSeen() -> void :
	if not _timer_active:
		_timer_eng = 0.0
	_timer_left = _timer_eng
	_timer_seen = _timer_eng


class TemporaryStacks extends Reference:
	var amount: int
	var timeout: float
	var item
	
	func _init(_amount, _timeout, _item = null):
		amount = _amount
		timeout = _timeout
		item = _item
