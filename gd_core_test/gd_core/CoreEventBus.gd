# =============================================================================
# CoreEventBus.gd — 无头战斗内核：定向信号派发
# =============================================================================
# 对齐源码：Utility/EventBus.gd（全文 133 行）
#
# 关键语义（必须逐字保留）：
#   · emissionID = emitter.get_instance_id() + (signalID << 32)，
#     signalID 为信号名的首次注册序号 —— 同一 (发射者, 信号名) 才互相命中
#   · `logEvent(event)` 只写日志，不派发
#   · 派发循环内若 Game.fightEnded 为真则 **立即 return**（剩余回调整体跳过，
#     不是 continue）—— 这是原版真实行为，保真保留
#   · disconnectAll() 清空连接表（收尾调用）
#
# 剥离内容：
#   · LoggingMode 延迟队列（Delayed 模式仅用于回放建档，战斗路径恒为 Instant）
#   · `Game.combatLog.logEvent(event)` → ctx.hooks.logEvent(event)（可注入，默认空）
#   · Node 类型标注 → Object（无头下发射者/接收者均为 Reference）
# =============================================================================
extends Reference
class_name CoreEventBus


enum LoggingMode{
	None = 0, 
	Instant = 1, 
	Delayed = 2
}

var loggingMode = LoggingMode.Instant
var signalQueue = []

var connections = {}
var signalIDs = {}

var _ctx


func setLoggingMode(mode: int) -> void :
	loggingMode = mode


func getLoggingMode():
	return loggingMode


func queueSignal(emitter, signalName: String, event, arguments = []):
	signalQueue.push_back([emitter, signalName, event, arguments])


func flushLoggingQueue():
	setLoggingMode(LoggingMode.Instant)
	
	var queueDuplicate = signalQueue.duplicate()
	signalQueue.clear()
	
	for tuple in queueDuplicate:
		emitAndLog(tuple[0], tuple[1], tuple[2], tuple[3])


func emitSignal(emitter, signalName: String, arguments = []):
	emitEvent(emitter, signalName, null, arguments)


func emitEvent(emitter, signalName: String, event, arguments = []):
	if loggingMode == LoggingMode.Delayed:
		queueSignal(emitter, signalName, event, arguments)
	else:
		emitAndLog(emitter, signalName, event, arguments)


func logEvent(event):
	if loggingMode == LoggingMode.Delayed:
		queueSignal(null, "", event, [])
	else:
		emitAndLog(null, "", event, [])


func emitAndLog(emitter, signalName: String, event, arguments: Array):
	if event != null:
		# ★ 对齐 oracle/Core/CombatLog.gd:266-267 logEvent 的闸：
		#   `if Game.fightEnded and not afterFightAllowed: return` —— 判胜后事件
		#   不再记录（run1029_r2 语料实证：终局尖刺反伤事件被该闸吞掉，事件流
		#   以 Win/Loss 结尾）。afterFightAllowed 的唯一使用点是 logWin/logLoss
		#   （CombatLog.gd:883/888），内核由宿主 OracleAlignBattle 合成终局事件，
		#   不走本总线，故此处一律按闸处理。
		if not _ctx.fight_ended:
			# ★ 逐抽对位标记（ORACLE_ALIGN_TRACE=1 时启用）：事件类型写进
			#   rng_trace，与神谕 rng_log 的 EVENT 行同构，不消耗链。
			if _ctx.rng.oracle_trace:
				_ctx.rng.trace_event(event.type)
			_ctx.hooks.logEvent(event)
	
	if emitter == null or not signalName in signalIDs:
		return
	
	var signalID = signalIDs[signalName]
	var emissionID = getEmissionID(emitter, signalID)
	# ★ np25：连接表值 = [funcRef, receiver] 对（receiver 供 BUS 诊断读身份；
	#   派发语义不变——仍只调 funcRef）。Godot 3 FuncRef 无实例读取器，唯一
	#   身份源就是连接时的 receiver 引用。
	var _bus_list: Array = connections.get(emissionID, [])
	# ★ np25 诊断（受控，双门控零耗链）：总线派发面——发射者/信号/监听数 +
	#   监听者逐个身份（isCoreItem 鸭子守卫，非物品监听记 "?"）。
	#   对拍 activated 级联派发序（run874_r7 P3 py-only 面）。
	if _ctx.rng.oracle_trace and _ctx.rng._stacktrace:
		var _eid = "?"
		if emitter != null and emitter.has_method("isCoreItem"):
			_eid = String(emitter.descriptor.identifier) + "/ot" + str(int(emitter.ownerType))
		_ctx.rng.trace_diag("BUS", String(signalName), str(_bus_list.size()), "emitter=" + _eid)
	var _bus_i = 0
	var _eid2 = "?"
	if emitter != null and emitter.has_method("isCoreItem"):
		_eid2 = String(emitter.descriptor.identifier) + "/ot" + str(int(emitter.ownerType))
	for _bus_pair in _bus_list:
		if _ctx.fight_ended:
			return
		if _ctx.rng.oracle_trace and _ctx.rng._stacktrace:
			var _rid = "?"
			var _recv = _bus_pair[1]
			if _recv != null and _recv.has_method("isCoreItem"):
				_rid = String(_recv.descriptor.identifier) + "/ot" + str(int(_recv.ownerType))
			_ctx.rng.trace_diag("BUSL", String(signalName), str(_bus_i), _rid)
		_bus_i += 1
		_bus_pair[0].call_funcv(arguments)
	if _ctx.rng.oracle_trace and _ctx.rng._stacktrace:
		_ctx.rng.trace_diag("BUSD", String(signalName), str(_bus_i), "emitter=" + _eid2)


func connectEvent(emitter, signalName: String, receiver, method: String):
	if not signalName in signalIDs:
		signalIDs[signalName] = signalIDs.size()
	var signalID = signalIDs[signalName]
	
	var emissionID = getEmissionID(emitter, signalID)
	var funcRef = FuncRef.new()
	funcRef.set_function(method)
	funcRef.set_instance(receiver)
	
	# ★ np25：值 = [funcRef, receiver] 对（见 emitAndLog 注释）。
	Util_dictAppend(connections, emissionID, [funcRef, receiver])


func getEmissionID(emitter, signalID: int) -> int:
	var ID = emitter.get_instance_id()
	
	ID += (signalID << 32)
	
	return ID


func disconnectAll():
	connections.clear()


# 对齐 Util.dictAppend
static func Util_dictAppend(dict, key, value):
	if not key in dict:
		dict[key] = []
	dict[key].push_back(value)
