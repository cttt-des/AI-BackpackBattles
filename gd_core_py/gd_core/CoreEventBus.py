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
			# ★ 对齐 oracle/Core/CombatLog.gd:266-267 logEvent 的闸：
			#   `if Game.fightEnded and not afterFightAllowed: return` —— 判胜后事件
			#   不再记录（run1029_r2 语料实证：终局尖刺反伤事件被该闸吞掉，事件流
			#   以 Win/Loss 结尾）。afterFightAllowed 的唯一使用点是 logWin/logLoss
			#   （CombatLog.gd:883/888），内核由宿主 OracleAlignBattle 合成终局事件，
			#   不走本总线，故此处一律按闸处理。
			if not self._ctx.fight_ended:
				# ★ 逐抽对位标记（ORACLE_ALIGN_TRACE=1 时启用）：事件类型写进
				#   rng_trace，与神谕 rng_log 的 EVENT 行同构，不消耗链。
				if self._ctx.rng.oracle_trace:
					self._ctx.rng.trace_event(event.type)
				self._ctx.hooks.logEvent(event)

		if emitter == None or not signalName in self.signalIDs:
			return

		signalID = self.signalIDs[signalName]
		emissionID = self.getEmissionID(emitter, signalID)
		# ★ np25：连接表值 = [funcRef, receiver] 对（receiver 供 BUS 诊断读身份；
		#   派发语义不变——仍只调 funcRef）。Godot 3 FuncRef 无实例读取器，唯一
		#   身份源就是连接时的 receiver 引用。
		_bus_list = self.connections.get(emissionID, [])
		# ★ np25 诊断（受控，双门控零耗链）：总线派发面——发射者/信号/监听数 +
		#   监听者逐个身份（isCoreItem 鸭子守卫，非物品监听记 "?"）。
		#   对拍 activated 级联派发序（run874_r7 P3 py-only 面）。
		if self._ctx.rng.oracle_trace and self._ctx.rng._stacktrace:
			_eid = "?"
			if emitter != None and emitter.has_method("isCoreItem"):
				_eid = String(emitter.descriptor.identifier) + '/ot' + str(int(emitter.ownerType))
			self._ctx.rng.trace_diag("BUS", String(signalName), str(len(_bus_list)), "emitter=" + _eid)
		_bus_i = 0
		_eid2 = "?"
		if emitter != None and emitter.has_method("isCoreItem"):
			_eid2 = String(emitter.descriptor.identifier) + '/ot' + str(int(emitter.ownerType))
		for _bus_pair in _iter(_bus_list):
			if self._ctx.fight_ended:
				return
			if self._ctx.rng.oracle_trace and self._ctx.rng._stacktrace:
				_rid = "?"
				_recv = _bus_pair[1]
				if _recv != None and _recv.has_method("isCoreItem"):
					_rid = String(_recv.descriptor.identifier) + '/ot' + str(int(_recv.ownerType))
				self._ctx.rng.trace_diag("BUSL", String(signalName), str(_bus_i), _rid)
			_bus_i += 1
			_bus_pair[0].call_funcv(arguments)
		if self._ctx.rng.oracle_trace and self._ctx.rng._stacktrace:
			self._ctx.rng.trace_diag("BUSD", String(signalName), str(_bus_i), "emitter=" + _eid2)


	def connectEvent(self, emitter, signalName, receiver, method):
		if not signalName in self.signalIDs:
			self.signalIDs[signalName] = len(self.signalIDs)
		signalID = self.signalIDs[signalName]

		emissionID = self.getEmissionID(emitter, signalID)
		funcRef = FuncRef()
		funcRef.set_function(method)
		funcRef.set_instance(receiver)

		# ★ np25：值 = [funcRef, receiver] 对（见 emitAndLog 注释）。
		self.Util_dictAppend(self.connections, emissionID, [funcRef, receiver])


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
