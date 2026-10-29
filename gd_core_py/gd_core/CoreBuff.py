# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class TemporaryStacks(GodotObject):
	def _init_fields(self):
		super()._init_fields()
		self._amount = 0
		self.timeout = 0.0
		self.item = None

	@property
	def amount(self):
		return self._amount
	@amount.setter
	def amount(self, v):
		self._amount = int(v)

	def _init(self, _amount, _timeout, _item=None):
		self.amount = _amount
		self.timeout = _timeout
		self.item = _item


class CoreBuff(GodotObject):

	resource_path = "res://gd_core/CoreBuff.gd"

	def _init_fields(self):
		super()._init_fields()
		self._type = 0
		self.isBuff = False
		self.character = None
		self._current = 0
		self._permanentStacks = 0
		self.resistChancePercent = 0.0
		self._resistStacks = 0
		self.reflectChancePercent = 0.0
		self.cleanseProtectionChancePercent = 0.0
		self.signalName = ""
		self.temporaryStacks = []
		self._nextTemporaryTimeout = 0
		self._MAX_STACKS = 0
		self._timer_left = 0.0
		self._timer_active = False
		self._timer_eng = 0.0
		self._timer_seen = 0.0
		self.ctx = None

	@property
	def type(self):
		return self._type
	@type.setter
	def type(self, v):
		self._type = int(v)
	@property
	def current(self):
		return self._current
	@current.setter
	def current(self, v):
		self._current = int(v)
	@property
	def permanentStacks(self):
		return self._permanentStacks
	@permanentStacks.setter
	def permanentStacks(self, v):
		self._permanentStacks = int(v)
	@property
	def resistStacks(self):
		return self._resistStacks
	@resistStacks.setter
	def resistStacks(self, v):
		self._resistStacks = int(v)
	@property
	def nextTemporaryTimeout(self):
		return self._nextTemporaryTimeout
	@nextTemporaryTimeout.setter
	def nextTemporaryTimeout(self, v):
		self._nextTemporaryTimeout = int(v)
	@property
	def MAX_STACKS(self):
		return self._MAX_STACKS
	@MAX_STACKS.setter
	def MAX_STACKS(self, v):
		self._MAX_STACKS = int(v)
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
	# 「外部 start/重挂/延长改写引擎读数的当 tick：eng != _timer_seen → 重同步
	#   **不递减**（首递减推迟到下一 tick）」，修「中途 (re)start 计时器恒早 1 tick」
	#   （evt8=InvulnerableEnd 全族 + evt109=Blind StackTimeout 族 ≈84 场）。
	#   停止期**不动** _timer_seen（对齐 :890-892 continue 不更新 e[1]）。



	def init(self, _type, _character, _signalName=""):
		self.type = _type
		self.isBuff = _R.C("CoreConst").isBuff(self.type)
		self.character = _character
		self.signalName = _signalName
		self.ctx = _character.ctx

		if self.type == _R.C("CoreConst").EventType.Block:
			self.MAX_STACKS = 100000
		else:
			self.MAX_STACKS = 10000

		return self


	def getStacks(self):
		return self.current


	def setStacks(self, amount):
		self.current = amount
		self.ctx.hooks.activateBuffCounter(self.character, self.type)


	def reset(self):
		self.setStacks(0)
		self.resistStacks = 0
		self.resistChancePercent = 0.0
		self.cleanseProtectionChancePercent = 0.0
		self.reflectChancePercent = 0.0


	def changeResistChance(self, chance):
		self.resistChancePercent += chance


	def changeResistStacks(self, amount):
		self.resistStacks = max(0, self.resistStacks + amount)


	def changeCleanseProtectionChance(self, chance):
		self.cleanseProtectionChancePercent += chance


	def changeReflectChance(self, amount):
		self.reflectChancePercent += amount


	def gainStacks(self, amount, item=None, triggerEvent=None, reflect=False):

		return self.gainTemporary(amount, - 1, item, triggerEvent, reflect)


	def gainTemporary(self, amount, duration, item=None, triggerEvent=None, reflect=False):

		event = None

		if amount > 0:

			resisted = 0
			totalResistChance = self.resistChancePercent

			if item != None and not reflect:
				totalResistChance -= item.getAmplificationChancePercent(self.type)

			if totalResistChance > 0:
				for i in _iter(amount):
					if self.ctx.rng.flipPercent(totalResistChance):
						resisted += 1
			elif totalResistChance < 0:
				for i in _iter(amount):
					if self.ctx.rng.flipPercent( - totalResistChance):
						amount += 1

			left = amount - resisted

			reflected = 0

			if not self.isBuff:

				if not reflect:
					for i in _iter(amount):
						if self.ctx.rng.flipPercent(self.reflectChancePercent):
							reflected += 1

					left -= reflected

					reflectedByStacks = 0
					if left > 0:
						reflectedByStacks = min(left, self.character.debuffReflectStacks)

					if reflectedByStacks > 0:
						reflected += reflectedByStacks
						left -= reflectedByStacks
						self.character.changeDebuffReflectStacks( - reflectedByStacks)

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
						target = self.character.opponent
						target.randBuffLabelPos()
						target.randBuffLabelDir()
						self.ctx.hooks.spawnReflectLabel(self.type, reflected)

				ownStacksUsed = min(left, self.resistStacks)
				resisted += ownStacksUsed
				left -= ownStacksUsed
				self.resistStacks -= ownStacksUsed

				if left > 0:
					characterStacksUsed = min(left, self.character.debuffResistStacks)
					resisted += characterStacksUsed
					self.character.changeDebuffResistStacks( - characterStacksUsed)

			if resisted > 0:
				amount -= resisted
				# ★ 表现层链消耗（Buff.gd:125-128 → Util.gd:934-941）：
				#   Util.spawnResistedLabel(type, character.randBuffLabelPos(), resisted)
				#   —— pos 是调用点实参（2 抽）+ spawnResistedLabel 内部 dir（1 抽）。
				#   阶段1 曾按 run1160_r18 语料误读为「只补 dir」；reflect 分支的
				#   run570_r18 对位（2026-10-08）证明 pos 照常求值，三分支统一更正。
				self.character.randBuffLabelPos()
				self.character.randBuffLabelDir()
				self.ctx.hooks.spawnResistedLabel(self.type, resisted)
				resistedEvent = self.ctx.combat_log.createEvent_StackResistOrNullify(self.type,
							item, resisted, self.character.playerId, triggerEvent, reflect)
				self.ctx.bus.logEvent(resistedEvent)

			if amount > 0:
				amount = int(min(amount, self.MAX_STACKS - self.current))
				if amount == 0:
					return None

				self.current += amount
				self.ctx.hooks.activateBuffCounter(self.character, self.type)

				if duration < 0:
					self.permanentStacks += amount
				else:
					timeout = self.ctx.time + duration
					tempStacks = TemporaryStacks(amount, timeout, item)
					self.temporaryStacks.append(tempStacks)

					if not self._timer_active:
						self._startTimer(duration)
						self.nextTemporaryTimeout = 0
					else:
						if duration < self._timer_left:
							self._stopTimer()
							self._startTimer(duration)
							self.nextTemporaryTimeout = len(self.temporaryStacks) - 1
					self._blnd_snap("gain", str(duration))

				if item:
					isPlayer = (self.character == self.ctx.player)

					if not self.isBuff:
						isPlayer = not isPlayer

					item.stackChanged(self.type, amount, isPlayer)

					if duration <= 0:
						event = self.ctx.combat_log.createEvent_Stack(self.type, item, 
							amount, self.character.playerId, triggerEvent, False, reflect)
					else:
						event = self.ctx.combat_log.createEvent_StackTemporary(self.type, 
							item, amount, duration, self.character.playerId, triggerEvent, 
							reflect)

					appliedToOpponent = (self.character != item.character())
					# ★ np24 诊断（受控）：镜像神谕 SRC gain_label 行（Buff.gd:192-197）。
					self.ctx.rng.trace_diag("SRC", "gain_label",
							String(item.descriptor.identifier), str(self.type))
					# ★ 表现层链消耗还原（Buff.gd:194 → Util.gd:975-983 spawnBuffLabel_item
					#   → Item.gd:6485-6494 getNextFreeLabelPosition）：物品身上的 buff
					#   浮动标签在事件 emit 之前取位，恒消耗 Util.randInBox 2 抽
					#   （槽位复用 (10,10) / 兜底 (30,30)；buff_labels 设置神谕语料为开）。
					item.getNextFreeLabelPosition()
					self.ctx.hooks.spawnBuffLabel_item(self.type, item, amount, appliedToOpponent)

					self.ctx.bus.emitEvent(self.character, self.signalName, event, [event.getAmount(), event])

			if reflected > 0:
				self.character.opponent.gainStacksTemporary(self.type, reflected, duration, 
					item, triggerEvent, True)

		return event


	def loseStacks(self, amount, item=None, triggerEvent=None, used=False):

		amount = min(self.current, amount)

		if not used:
			protected = 0

			if self.cleanseProtectionChancePercent > 0:
				for i in _iter(amount):
					if self.ctx.rng.flipPercent(self.cleanseProtectionChancePercent):
						protected += 1

			elif self.cleanseProtectionChancePercent < 0:
				for i in _iter(amount):
					if self.ctx.rng.flipPercent( - self.cleanseProtectionChancePercent):
						protected -= 1

			amount -= protected
			amount = clamp(amount, 0, self.current)

			if amount > 0 and self.resistStacks > 0:
				protectedByStacks = min(amount, self.resistStacks)
				protected += protectedByStacks
				amount -= protectedByStacks
				self.resistStacks -= protectedByStacks

			if (self.isBuff and 
				self.type != _R.C("CoreConst").EventType.Block and 
				amount > 0 and 
				self.character.buffProtectStacks > 0):

				protectedByStacks = min(amount, self.character.buffProtectStacks)
				protected += protectedByStacks
				amount -= protectedByStacks
				self.character.buffProtectStacks -= protectedByStacks

			if protected > 0:
				# ★ 表现层链消耗（Buff.gd:236-237 → Util.gd:944-951）：同 resisted/
				#   reflect 三分支统一——pos 实参 2 抽 + spawnProtectedLabel 内部
				#   randBuffLabelDir 1 抽。
				self.character.randBuffLabelPos()
				self.character.randBuffLabelDir()
				self.ctx.hooks.spawnProtectedLabel(self.type, protected)
				protectedEvent = self.ctx.combat_log.createEvent_StackProtect(self.type,
					item, protected, self.character.playerId, triggerEvent)
				self.ctx.bus.logEvent(protectedEvent)

		if self.permanentStacks >= amount:
			self.permanentStacks -= amount
		else:
			tempToCleanse = amount - self.permanentStacks
			self.permanentStacks = 0

			while tempToCleanse > 0:
				if (not self.temporaryStacks):
					break

				farthestTimeout = 0
				farthestIndex = - 1
				for i in _iter(len(self.temporaryStacks)):
					stacks = self.temporaryStacks[i]
					if stacks.timeout > farthestTimeout:
						farthestTimeout = stacks.timeout
						farthestIndex = i

				farthest = self.temporaryStacks[farthestIndex]
				if farthest.amount > tempToCleanse:
					farthest.amount -= tempToCleanse
					self._blnd_snap("partial", str(farthestIndex) + "amt" + str(farthest.amount))
					tempToCleanse = 0

				else:
					tempToCleanse -= farthest.amount
					_pop_at(self.temporaryStacks, farthestIndex)
					self._blnd_snap("lose", str(farthestIndex))

					if (not self.temporaryStacks):
						self._stopTimer()

		return self.changeCurrentLogShowLabel(False, amount, item, triggerEvent, used)


	def changeCurrentLogShowLabel(self, isTimeout, amount, item=None, triggerEvent=None, used=False):

		change = min(self.current, amount)

		if change > 0:
			self.current -= change
			self.ctx.hooks.activateBuffCounter(self.character, self.type)

			if item:
				isPlayer = (self.character == self.ctx.player)
				if not used:
					if self.isBuff:
						isPlayer = not isPlayer

				item.stackChanged(self.type, - change, isPlayer, used)

				event = None
				if isTimeout:
					event = self.ctx.combat_log.createEvent_StackTimeout(self.type, item, - change, self.character.playerId, triggerEvent)
				else:
					event = self.ctx.combat_log.createEvent_Stack(self.type, item, - change, self.character.playerId, triggerEvent, used)

				self.ctx.bus.emitEvent(self.character, self.signalName, event, [event.getAmount(), event])

				appliedToOpponent = (self.character != item.character())
				# ★ 表现层链消耗还原（Buff.gd:317 → Util.gd:975-983 → Item.gd:6485-6494）：
				#   与 gainStacks 同面，但原版顺序是 **先 emit 事件后取位**（标签在
				#   事件之后）——顺序即链位，必须保持。
				item.getNextFreeLabelPosition()
				self.ctx.hooks.spawnBuffLabel_item(self.type, item, - change, appliedToOpponent)

				return event

		return None


	def _blnd_snap(self, op, pre):
		if self.ctx.rng.oracle_trace and self.ctx.rng._stacktrace:
			_b = ""
			for ts in _iter(self.temporaryStacks):
				_b += _gd_fmt('(%s@%s)', [str(ts.amount), _substr(str(ts.timeout), 0, 5)])
			# ★ np25 timeout1t：payload 追加 fr=<frame_counter>（六点全加、双门控
			#   不变）——rng_trace 行首数字是行号非时间，没有帧号无法读「gain→fire
			#   间隔 = K 或 K-1 次递减」这一决定性读数（验收门，见守门方案3）。
			self.ctx.rng.trace_diag('BLND', 'p' + str(self.character.playerId) + ' ty' + str(self.type) + ' ' + op + ' ' + pre, 'len=' + str(len(self.temporaryStacks)) + ' ntp=' + str(self.nextTemporaryTimeout) + ' tm=' + str(self._timer_active) + '/' + str(self._timer_left) + '/e' + str(self._timer_eng) + '/s' + str(self._timer_seen) + ' fr=' + str(self.ctx.frame_counter), _b)

	def onTimeout(self):
		self._blnd_snap("fire", str(self.nextTemporaryTimeout))
		# ★ np25（run1132_r18 定谳，gd1132v 无守卫跑实证）：Godot **release** 构建的
		#   数组越界读是**软错误并中止整个函数**——fire 行之后无 CLS/remove/重扫/
		#   重挂任何痕迹：栈原样保留、定时器已被 _tick 置死（该临时栈随后由普通
		#   loseStacks 路径清掉，Automanaton -5 铁证）。此处显式同语义**早退**；
		#   转写侧若不早退，Python 硬索引越界即进程崩溃（IndexError，py-only 族
		#   最后一场残因）。越界源=loseStacks 删 farthest 后 ntp 未回拨（原版同构
		#   隐患，仅 release 软错误语义下无症状）。
		if self.nextTemporaryTimeout < 0 or self.nextTemporaryTimeout >= len(self.temporaryStacks):
			return
		timedOutStacks = self.temporaryStacks[self.nextTemporaryTimeout]
		self.changeCurrentLogShowLabel(True, timedOutStacks.amount, timedOutStacks.item)
		_pop_at(self.temporaryStacks, self.nextTemporaryTimeout)
		self._blnd_snap("timeout", str(self.nextTemporaryTimeout))

		if not (not self.temporaryStacks):
			earliestTimeout = INF
			earliestIndex = - 1
			for i in _iter(len(self.temporaryStacks)):
				stacks = self.temporaryStacks[i]
				if stacks.timeout < earliestTimeout:
					earliestTimeout = stacks.timeout
					earliestIndex = i

			self.nextTemporaryTimeout = earliestIndex
			delay = earliestTimeout - self.ctx.time
			self._blnd_snap("rearm", "delay=" + str(delay) + " et=" + str(earliestTimeout) + " now=" + str(self.ctx.time))
			if delay <= 0.01:
				self.onTimeout()
			else:
				self._startTimer(delay)


	def combatEnd(self):
		self._stopTimer()
		self.temporaryStacks.clear()


	# ── 内核计时器（语义等价于 Godot Timer(one_shot, TIMER_PROCESS_PHYSICS)） ──

	def _startTimer(self, duration):
		# ★ np25 timeout1t：对齐 Timer.start(t)——**只改写引擎读数**，_timer_left
		#   （≡e[0]）不动：oracle 注册表 e[0] 停留遗留值（fire 后 -1），同值重启
		#   （eng==e[1]）时走 :901 从遗留值继续减 → ≤0 当 tick 立即 fire。若在这里
		#   直赋 _timer_left=duration（初版 timeout1t 的写法），遗留值被冲掉 →
		#   重同步不递减 → 比 oracle 晚 1 tick 起（run599_r10 Blind 393/574 铁证）。
		self._timer_eng = duration
		self._timer_active = True


	def _stopTimer(self):
		# 对齐 Timer.stop()：引擎读数归零；e[0]（_timer_left）从不在 stop 里被动
		# （oracle :891 的 e[0]=-1 是 drive_timers 停止分支每帧重置，gd 停止期
		# _tick 早退等价该 continue；_timer_left 冻结在遗留值，语义同 ≤0）。
		self._timer_active = False
		self._timer_eng = 0.0


	def isTimerActive(self):
		return self._timer_active


	def _tick(self, delta):
		if not self._timer_active:
			return
		# ★ np25 timeout1t：逐行对齐 drive_timers :895-904。
		if self._timer_eng == self._timer_seen:
			self._timer_left -= delta       # :901 eng==e[1] → e[0]-=dt（遗留值继续减=
		else:                          #   同值重启当 tick 立即 fire 的原版怪癖）
			self._timer_left = self._timer_eng   # :899 eng!=e[1] → e[0]=eng 重同步（不递减）
		self._timer_seen = self._timer_eng       # :902 e[1]=eng（每 pass 更新，先于 fire 判定）
		if self._timer_left > 0.0:          # :903-904
			return
		self._timer_active = False          # :910 one_shot 自停先于派发
		self._timer_eng = 0.0               # :910 stop() → 引擎读数归零；_timer_left
		self.onTimeout()                    #   保留 ≤0 发火值（下一次同值重启靠它立即 fire）
		if self._timer_active:              # :915-917 handler 内重挂（rearm start(delay)）
			self._timer_left = self._timer_eng   #   → e[0]=e[1]=新引擎读数，下一 tick 照常递减
			self._timer_seen = self._timer_eng


	# ★ np25 timeout1t：rebuild_timer_registry 等价（oracle_fight.gd:690 调用、
	#   :972-987 实现——activateItems 之后、手动 tick 循环之前把全部 Timer 以
	#   [left,left]=[eng,eng] 重入册；停止态 get_time_left()=0）。由
	#   CoreCombat.activateItems 末尾逐角色委托。激活期 start 的计时器 → 战斗首帧
	#   即递减；战斗中首 gain 的新 Buff [0,0] → start 后首帧重同步——两分支由此锚定。
	def rebuildTimerSeen(self):
		if not self._timer_active:
			self._timer_eng = 0.0
		self._timer_left = self._timer_eng
		self._timer_seen = self._timer_eng


CoreBuff.TemporaryStacks = TemporaryStacks


_R.reg("res://gd_core/CoreBuff.gd", CoreBuff)
_R.reg("CoreBuff", CoreBuff)
_R.reg("CoreBuff", CoreBuff)
