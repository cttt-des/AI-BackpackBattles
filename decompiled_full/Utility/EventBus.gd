extends Node

enum LoggingMode{
	None = 0, 
	Instant = 1, 
	Delayed = 2
}
var loggingMode = LoggingMode.Instant
var signalQueue = []

var connections = {}
var signalIDs = {}

func setLoggingMode(mode: int):
	loggingMode = mode
	
func getLoggingMode():
	return loggingMode

func queueSignal(emitter: Node, signalName: String, event: CombatEvent, arguments = []):
	signalQueue.push_back([emitter, signalName, event, arguments])


func flushLoggingQueue():
	setLoggingMode(LoggingMode.Instant)
	
	var queueDuplicate = signalQueue.duplicate()
	signalQueue.clear()
	
	for tuple in queueDuplicate:
		var emitter = tuple[0]
		var signalName = tuple[1]
		var event = tuple[2]
		var arguments = tuple[3]
		emitAndLog(emitter, signalName, event, arguments)


func emitSignal(emitter: Node, signalName: String, arguments = []):
	emitEvent(emitter, signalName, null, arguments)

func emitEvent(emitter: Node, signalName: String, event: CombatEvent, arguments = []):
	if loggingMode == LoggingMode.Delayed:
		queueSignal(emitter, signalName, event, arguments)
	else:
		emitAndLog(emitter, signalName, event, arguments)

func logEvent(event: CombatEvent):
	if loggingMode == LoggingMode.Delayed:
		queueSignal(null, "", event, [])
	else:
		emitAndLog(null, "", event, [])
		



func emitAndLog(emitter: Node, signalName: String, event: CombatEvent, arguments: Array):
	if event != null:
		Game.combatLog.logEvent(event)
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	if emitter == null or not signalName in signalIDs:
		return
	
	
	
	var signalID = signalIDs[signalName]
	var emissionID = getEmissionID(emitter, signalID)
	for funcRef in connections.get(emissionID, []):
		if Game.fightEnded:
			return
		
		funcRef.call_funcv(arguments)
	
func connectEvent(emitter: Node, signalName: String, receiver: Node, method: String):
	if not signalName in signalIDs:
		signalIDs[signalName] = signalIDs.size()
	var signalID = signalIDs[signalName]
	
	var emissionID = getEmissionID(emitter, signalID)
	var funcRef = FuncRef.new()
	funcRef.set_function(method)
	funcRef.set_instance(receiver)


	Util.dictAppend(connections, emissionID, funcRef)

func getEmissionID(emitter: Node, signalID: int) -> int:
	var ID = emitter.get_instance_id()
	
	ID += (signalID << 32)
	
	return ID









	

func disconnectAll():
	connections.clear()




