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
		_ctx.hooks.logEvent(event)
	
	if emitter == null or not signalName in signalIDs:
		return
	
	var signalID = signalIDs[signalName]
	var emissionID = getEmissionID(emitter, signalID)
	for funcRef in connections.get(emissionID, []):
		if _ctx.fight_ended:
			return
		
		funcRef.call_funcv(arguments)


func connectEvent(emitter, signalName: String, receiver, method: String):
	if not signalName in signalIDs:
		signalIDs[signalName] = signalIDs.size()
	var signalID = signalIDs[signalName]
	
	var emissionID = getEmissionID(emitter, signalID)
	var funcRef = FuncRef.new()
	funcRef.set_function(method)
	funcRef.set_instance(receiver)
	
	Util_dictAppend(connections, emissionID, funcRef)


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
