# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreEventBus(GodotObject):

	resource_path = "res://gd_core/CoreEventBus.gd"

	LoggingMode = EnumDict("LoggingMode", {"None": 0, "Instant": 1, "Delayed": 2})



	def _init_fields(self):
		super()._init_fields()
		self.loggingMode = self.LoggingMode.Instant
		self.signalQueue = []
		self.connections = {}
		self.signalIDs = {}
		self._ctx = None

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







	def setLoggingMode(self, mode):
		self.loggingMode = mode


	def getLoggingMode(self):
		return self.loggingMode


	def queueSignal(self, emitter, signalName, event, arguments=[]):
		self.signalQueue.append([emitter, signalName, event, arguments])


	def flushLoggingQueue(self):
		self.setLoggingMode(self.LoggingMode.Instant)

		queueDuplicate = _dup(self.signalQueue)
		self.signalQueue.clear()

		for tuple in _iter(queueDuplicate):
			self.emitAndLog(tuple[0], tuple[1], tuple[2], tuple[3])


	def emitSignal(self, emitter, signalName, arguments=[]):
		self.emitEvent(emitter, signalName, None, arguments)


	def emitEvent(self, emitter, signalName, event, arguments=[]):
		if self.loggingMode == self.LoggingMode.Delayed:
			self.queueSignal(emitter, signalName, event, arguments)
		else:
			self.emitAndLog(emitter, signalName, event, arguments)


	def logEvent(self, event):
		if self.loggingMode == self.LoggingMode.Delayed:
			self.queueSignal(None, "", event, [])
		else:
			self.emitAndLog(None, "", event, [])


	def emitAndLog(self, emitter, signalName, event, arguments):
		if event != None:
			self._ctx.hooks.logEvent(event)

		if emitter == None or not signalName in self.signalIDs:
			return

		signalID = self.signalIDs[signalName]
		emissionID = self.getEmissionID(emitter, signalID)
		for funcRef in _iter(self.connections.get(emissionID, [])):
			if self._ctx.fight_ended:
				return

			funcRef.call_funcv(arguments)


	def connectEvent(self, emitter, signalName, receiver, method):
		if not signalName in self.signalIDs:
			self.signalIDs[signalName] = len(self.signalIDs)
		signalID = self.signalIDs[signalName]

		emissionID = self.getEmissionID(emitter, signalID)
		funcRef = FuncRef()
		funcRef.set_function(method)
		funcRef.set_instance(receiver)

		self.Util_dictAppend(self.connections, emissionID, funcRef)


	def getEmissionID(self, emitter, signalID):
		ID = emitter.get_instance_id()

		ID += (signalID << 32)

		return ID


	def disconnectAll(self):
		self.connections.clear()


	# 对齐 Util.dictAppend
	@staticmethod
	def Util_dictAppend(dict, key, value):
		if not key in dict:
			dict[key] = []
		dict[key].append(value)


_R.reg("res://gd_core/CoreEventBus.gd", CoreEventBus)
_R.reg("CoreEventBus", CoreEventBus)
_R.reg("CoreEventBus", CoreEventBus)
