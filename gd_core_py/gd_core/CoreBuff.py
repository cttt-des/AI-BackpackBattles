# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class TemporaryStacks(GodotObject):
	def _init_fields(self):
		super()._init_fields()
		self.amount = 0
		self.timeout = 0.0
		self.item = None


	def _init(self, _amount, _timeout, _item=None):
		self.amount = _amount
		self.timeout = _timeout
		self.item = _item


class CoreBuff(GodotObject):

	resource_path = "res://gd_core/CoreBuff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.type = 0
		self.isBuff = False
		self.character = None
		self.current = 0
		self.permanentStacks = 0
		self.resistChancePercent = 0.0
		self.resistStacks = 0
		self.reflectChancePercent = 0.0
		self.cleanseProtectionChancePercent = 0.0
		self.signalName = ""
		self.temporaryStacks = []
		self.nextTemporaryTimeout = 0
		self.MAX_STACKS = 0
		self._timer_left = 0.0
		self._timer_active = False
		self.ctx = None

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
					tempToCleanse = 0

				else:
					tempToCleanse -= farthest.amount
					_pop_at(self.temporaryStacks, farthestIndex)

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
				self.ctx.hooks.spawnBuffLabel_item(self.type, item, - change, appliedToOpponent)

				return event

		return None


	def onTimeout(self):
		timedOutStacks = self.temporaryStacks[self.nextTemporaryTimeout]
		self.changeCurrentLogShowLabel(True, timedOutStacks.amount, timedOutStacks.item)
		_pop_at(self.temporaryStacks, self.nextTemporaryTimeout)

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
			if delay <= 0.01:
				self.onTimeout()
			else:
				self._startTimer(delay)


	def combatEnd(self):
		self._stopTimer()
		self.temporaryStacks.clear()


	# ── 内核计时器（语义等价于 Godot Timer(one_shot, TIMER_PROCESS_PHYSICS)） ──

	def _startTimer(self, duration):
		self._timer_left = duration
		self._timer_active = True


	def _stopTimer(self):
		self._timer_active = False
		self._timer_left = 0.0


	def isTimerActive(self):
		return self._timer_active


	def _tick(self, delta):
		if not self._timer_active:
			return
		self._timer_left -= delta
		if self._timer_left <= 0.0:
			self._timer_active = False
			self._timer_left = 0.0
			self.onTimeout()


CoreBuff.TemporaryStacks = TemporaryStacks


_R.reg("res://gd_core/CoreBuff.gd", CoreBuff)
_R.reg("CoreBuff", CoreBuff)
_R.reg("CoreBuff", CoreBuff)
