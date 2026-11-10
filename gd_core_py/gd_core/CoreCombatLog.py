# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreCombatLog(GodotObject):

	resource_path = "res://gd_core/CoreCombatLog.gd"

	def _init_fields(self):
		super()._init_fields()
		self.eventNum = 0
		self._ctx = None

	# =============================================================================
	# CoreCombatLog.gd — 无头战斗内核：事件工厂
	# =============================================================================
	# 对齐源码：Core/CombatLog.gd（全文 1279 行）
	#
	# 本类**只保留事件工厂**（createEvent / createEvent_* 共 20 余个）与
	# 少量被判定路径读取的字段（eventNum）。判定路径调用它来构造事件对象，
	# 事件的 id / timestamp / parentEvent / origin / type / params 与
	# 原版逐字段一致 —— 因为物品行为会读取 event.getParam / getOrigin / getDepth。
	#
	# 剥离内容（合计约 1000 行，全部与判定无关）：
	#   · 文本渲染与回放：asText / CombatLogLine / 打字机效果 / 滚动 / 文件导出
	#   · 图表与统计聚合：StatHistory / statLoggers / 伤害计量表（只保留钩子入口）
	#   · UI 交互：hover / scrub / tutorial / 信号连接
	#   · `item.queueTooltipUpdate()` 等纯 UI 刷新 → hooks
	#
	# 保真保留的原版行为（含原版疑点，一律照搬不修）：
	#   · createEvent_BattleRageEnd 把 Game.EventType.BattleRageEnd 当作 origin 传入
	#   · createEvent_StackTemporary 先调 5 参 createEvent_Stack，再补 reflected
	#   · createEvent_Stamina / DrainStamina 的参数键是 "stamina"，不是 "amount"
	#   · createEvent_TemporaryMaxHealth 不 setTarget
	# =============================================================================




	# 对齐 CombatLog 的时间戳来源：CombatTimer.combatTime
	def getTimeStamp(self):
		return self._ctx.combat_time


	# ── 核心工厂（对齐 CombatLog.gd:240-249） ──
	def createEvent(self, triggerEvent, origin, type):
		self.eventNum += 1

		event = _H_1(self.eventNum, self.getTimeStamp(), triggerEvent,
				origin, type)

		for character in _iter([self._ctx.player, self._ctx.opponent]):
			self._ctx.hooks.snapshotCharacterStat(character, _H_18)

		return event


	def logEvent(self, event):
		self._ctx.hooks.logEvent(event)


	# ── 攻击类（对齐 653-702） ──
	def createEvent_Attack(self, damageRes, triggerEvent=None):
		event = None
		origin = damageRes.damageSource.origin
		character = origin.character()

		if damageRes.hasHit():
			if damageRes.wasCriticalHit():
				event = self.createEvent(triggerEvent, origin, _H_26)
			else:
				event = self.createEvent(triggerEvent, origin, _H_27)
			event.setParam("damage", damageRes.damage)

			attackedCharacter = None
			if damageRes.damageSource.hasType(_H_24):
				attackedCharacter = character
			else:
				attackedCharacter = character.opponent

			# ★ 对齐 CombatLog.gd:653-678：原版攻击事件**不 setTarget**（target 恒
			#   null；setTarget 只出现在 createEvent_Damage/OutOfStamina 等事件，
			#   CombatLog.gd:695+）。此前内核多设 target —— 神谕语料实证：攻击事件
			#   target=None（run572/573 首分歧即此，Death Scythe 首攻）。
			self._ctx.hooks.snapshotCharacterStat(attackedCharacter, _H_2)
			self._ctx.hooks.snapshotStack(attackedCharacter, _H_3)
			self._ctx.hooks.snapshotDamageDealt(character.playerId,
				damageRes.damageSource.types[0], damageRes.damage)
			self._ctx.hooks.updateDamageMeter(character.playerId, event)
		else:
			# 对齐 CombatLog.gd:675-676：落空分支只有 createEvent 一句——无 damage
			# 参数、无 target、无快照（神谕语料 MissedAttack 事件 params={} target=null）。
			event = self.createEvent(triggerEvent, origin, _H_25)

		return event


	def createEvent_Damage(self, damageRes, damagingPlayerId, triggerEvent=None):
		event = None
		if damageRes.wasCriticalHit():
			event = self.createEvent(triggerEvent, damageRes.damageSource.types[0], 
				_H_26)
		else:
			event = self.createEvent(triggerEvent, damageRes.damageSource.types[0], 
				_H_27)
		event.setParam("damage", damageRes.damage)
		event.setTarget(damagingPlayerId)
		damagingCharacter = self._ctx.getCharacterFromId(damagingPlayerId)
		damagedCharacter = damagingCharacter.opponent
		self._ctx.hooks.snapshotCharacterStat(damagedCharacter, _H_2)
		self._ctx.hooks.snapshotStack(damagedCharacter, _H_3)
		self._ctx.hooks.snapshotDamageDealt(damagingPlayerId, damageRes.damageSource.types[0], damageRes.damage)
		self._ctx.hooks.updateDamageMeter(damagingPlayerId, event)
		return event


	# ── 生命类（对齐 704-720） ──
	def createEvent_Heal(self, amount, playerId, origin, triggerEvent=None):
		amount = int(amount)
		playerId = int(playerId)
		event = self.createEvent(triggerEvent, origin, _H_4)
		event.setParam("amount", amount)
		event.setTarget(playerId)
		self._ctx.hooks.snapshotCharacterStat(self._ctx.getCharacterFromId(playerId), _H_2)
		return event


	def createEvent_LoseHealth(self, amount, playerId, origin, triggerEvent=None):
		amount = int(amount)
		playerId = int(playerId)
		event = self.createEvent(triggerEvent, origin, _H_5)
		event.setParam("amount", amount)
		event.setTarget(playerId)
		self._ctx.hooks.snapshotCharacterStat(self._ctx.getCharacterFromId(playerId), _H_2)
		return event


	# ── 栈类（对齐 722-774） ──
	def createEvent_Stack(self, type, item, amount, playerId, triggerEvent=None, used=False, reflected=False):
		_iter__loc = _iter
		type = int(type)
		amount = int(amount)
		playerId = int(playerId)

		event = self.createEvent(triggerEvent, item, type)
		event.setParam("amount", amount)
		event.setParam("used", used)
		event.setParam("reflected", reflected)
		event.setTarget(playerId)
		self._ctx.hooks.snapshotStack(self._ctx.getCharacterFromId(playerId), type)

		if type == _H_6:
			for i in _iter__loc(self._ctx.getCharacterFromId(playerId).items):
				if i.isWeapon() and i.canBeEmpowered():
					self._ctx.hooks.snapshotItemTooltipStat(i, _H_32)
					self._ctx.hooks.snapshotItemTooltipStat(i, _H_33)

		if type == _H_28 or type == _H_29:
			for i in _iter__loc(self._ctx.getCharacterFromId(playerId).items):
				if i.hasCooldown():
					self._ctx.hooks.snapshotItemTooltipStat(i, _H_34)

		return event


	def createEvent_StackTemporary(self, type, item, amount, duration, playerId, triggerEvent, reflected=False):
		event = self.createEvent_Stack(type, item, amount, playerId, triggerEvent)
		event.setParam("duration", duration)
		event.setParam("reflected", reflected)
		return event


	def createEvent_StackTimeout(self, type, item, amount, playerId, triggerEvent):
		event = self.createEvent_Stack(type, item, amount, playerId, triggerEvent)
		event.setParam("timeout", True)
		return event


	def createEvent_StackResistOrNullify(self, type, item, amount, playerId, triggerEvent, reflect=False):
		event = self.createEvent_Stack(type, item, amount, playerId, triggerEvent)
		event.setParam("resisted", True)
		event.setParam("reflected", reflect)
		return event


	def createEvent_StackProtect(self, type, item, amount, playerId, triggerEvent):
		event = self.createEvent_Stack(type, item, amount, playerId, triggerEvent)
		event.setParam("protected", True)
		return event


	# ── 控制类（对齐 776-796） ──
	def createEvent_Stun(self, item, duration, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_7)
		event.setParam("duration", duration)
		event.setTarget(playerId)
		return event


	def createEvent_StunResist(self, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_8)
		event.setTarget(playerId)
		return event


	def createEvent_InvulnerableStart(self, item, duration, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_9)
		event.setParam("duration", duration)
		event.setTarget(playerId)
		return event


	def createEvent_InvulnerableEnd(self, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_10)
		event.setTarget(playerId)
		return event


	# ── 体力类（对齐 798-813） ──
	def createEvent_Stamina(self, amount, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_11)
		event.setParam('stamina', _div(floor(amount * 10), 10.0))
		event.setTarget(playerId)
		return event


	def createEvent_DrainStamina(self, amount, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_12)
		event.setTarget(playerId)
		event.setParam('stamina', _div(floor(amount * 10), 10.0))
		return event


	def createEvent_OutOfStamina(self, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_13)
		event.setTarget(playerId)
		return event


	# ── 伤害修正 / 上限类（对齐 815-834） ──
	def createEvent_DamageBuff(self, item, buffedItem, damage, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_14)
		event.setTarget(playerId)
		# ★ np24：oracle 录制环境无翻译表（Unreleased.*.translation 缺失）⇒
		#   getTranslatedName() 实录恒空串（语料 26/26 type16 item=""）——镜像。
		event.setParam("item", "")
		event.setParam("damage", damage)
		return event


	def createEvent_TemporaryMaxHealth(self, item, amount, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_15)
		event.setParam("amount", amount)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _H_2)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _H_16)
		return event


	def createEvent_TemporaryMaxStamina(self, item, amount, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_17)
		event.setParam("stamina", amount)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _H_18)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _H_19)
		return event


	def createEvent_BattleRageStart(self, item, duration, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_20)
		event.setParam("duration", duration)
		return event


	def createEvent_BattleRageEnd(self, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, _H_21,
			_H_21)
		event.setTarget(playerId)
		return event


	def createEvent_Reincarnate(self, item, health, triggerEvent=None):
		health = int(health)
		event = self.createEvent(triggerEvent, item, _H_22)
		event.setParam("health", health)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _H_2)
		return event


	def createEvent_Activation(self, item, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _H_23)
		return event


	def createEvent_DamChange(self, item, amount, isPercent, duration=None, type=None, triggerEvent=None):

		event = None
		if amount > 0:
			event = self.createEvent(triggerEvent, item, _H_30)
		else:
			event = self.createEvent(triggerEvent, item, _H_31)

		event.setParam("amount", amount)
		event.setParam("isPercent", isPercent)
		if duration != None:
			event.setParam("duration", duration)
		if type != None:
			event.setParam("type", type)
		return event


	# ── 统计入口（全部走钩子，无判定影响） ──
	def snapshotMetric(self, playerId, metric, eventType, value):
		self._ctx.hooks.snapshotMetric(playerId, metric, eventType, value)


	def snapshotItemMetric(self, item, metricIndex, playerId=None, withNextEvent=False):
		if playerId == None:
			playerId = item.character().playerId

		connectedEventNum = self.eventNum
		if withNextEvent:
			connectedEventNum += 1
		self._ctx.hooks.snapshotItemMetric(item, metricIndex, playerId, withNextEvent)


	def snapshotItemTooltipStat(self, item, statType, playerId=None, withNextEvent=False, event=None):
		if playerId == None:
			playerId = item.character().playerId

		connectedEventNum = self.eventNum
		if event != None:
			connectedEventNum = event.id
		elif withNextEvent:
			connectedEventNum += 1

		self._ctx.hooks.snapshotItemTooltipStat(item, statType, playerId, withNextEvent, event)


	def snapshotItemState(self, item, state, withNextEvent, event):
		playerId = item.character().playerId
		self._ctx.hooks.snapshotItemState(item, state, withNextEvent, event)


	def snapshotGlobalStat(self, stat, newValue):
		stat = int(stat)
		self._ctx.hooks.snapshotGlobalStat(stat, newValue)


	# 对齐 CombatLog.gd:517-518（签名必须 4 参：物品行为与 CoreCharacter 都会带
	# withNextEvent / event 调用，例如 startBattleRage 里的 snapshotCharacterStat(self, Stat.BattleRage, false, event)）
	def snapshotCharacterStat(self, character, statType, withNextEvent=False, event=None):
		self._ctx.hooks.snapshotCharacterStat(character, statType, withNextEvent, event)


	def snapshotStack(self, character, type):
		self._ctx.hooks.snapshotStack(character, type)


_R.reg("res://gd_core/CoreCombatLog.gd", CoreCombatLog)
_R.reg("CoreCombatLog", CoreCombatLog)
_R.reg("CoreCombatLog", CoreCombatLog)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreEvent")
try:
	_H_10 = _R.C("CoreConst").EventType.InvulnerableEnd
except AttributeError as _he:
	_H_10 = _HoistPending(_he)
try:
	_H_11 = _R.C("CoreConst").EventType.Stamina
except AttributeError as _he:
	_H_11 = _HoistPending(_he)
try:
	_H_12 = _R.C("CoreConst").EventType.DrainStamina
except AttributeError as _he:
	_H_12 = _HoistPending(_he)
try:
	_H_13 = _R.C("CoreConst").EventType.OutofStamina
except AttributeError as _he:
	_H_13 = _HoistPending(_he)
try:
	_H_14 = _R.C("CoreConst").EventType.DamageBuff
except AttributeError as _he:
	_H_14 = _HoistPending(_he)
try:
	_H_15 = _R.C("CoreConst").EventType.TemporaryMaxHealth
except AttributeError as _he:
	_H_15 = _HoistPending(_he)
try:
	_H_16 = _R.C("CoreCharacter").Stat.MaxHealth
except AttributeError as _he:
	_H_16 = _HoistPending(_he)
try:
	_H_17 = _R.C("CoreConst").EventType.TemporaryMaxStamina
except AttributeError as _he:
	_H_17 = _HoistPending(_he)
try:
	_H_18 = _R.C("CoreCharacter").Stat.Stamina
except AttributeError as _he:
	_H_18 = _HoistPending(_he)
try:
	_H_19 = _R.C("CoreCharacter").Stat.MaxStamina
except AttributeError as _he:
	_H_19 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreCharacter").Stat.Health
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_20 = _R.C("CoreConst").EventType.BattleRageStart
except AttributeError as _he:
	_H_20 = _HoistPending(_he)
try:
	_H_21 = _R.C("CoreConst").EventType.BattleRageEnd
except AttributeError as _he:
	_H_21 = _HoistPending(_he)
try:
	_H_22 = _R.C("CoreConst").EventType.Reincarnate
except AttributeError as _he:
	_H_22 = _HoistPending(_he)
try:
	_H_23 = _R.C("CoreConst").EventType.Activation
except AttributeError as _he:
	_H_23 = _HoistPending(_he)
try:
	_H_24 = _R.C("CoreDamageSource").Type.SelfDamage
except AttributeError as _he:
	_H_24 = _HoistPending(_he)
try:
	_H_25 = _R.C("CoreConst").EventType.MissedAttack
except AttributeError as _he:
	_H_25 = _HoistPending(_he)
try:
	_H_26 = _R.C("CoreConst").EventType.CriticalDamage
except AttributeError as _he:
	_H_26 = _HoistPending(_he)
try:
	_H_27 = _R.C("CoreConst").EventType.DealDamage
except AttributeError as _he:
	_H_27 = _HoistPending(_he)
try:
	_H_28 = _R.C("CoreConst").EventType.Heat
except AttributeError as _he:
	_H_28 = _HoistPending(_he)
try:
	_H_29 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
	_H_29 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").EventType.Block
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_30 = _R.C("CoreConst").EventType.DamIncrease
except AttributeError as _he:
	_H_30 = _HoistPending(_he)
try:
	_H_31 = _R.C("CoreConst").EventType.DamReduction
except AttributeError as _he:
	_H_31 = _HoistPending(_he)
try:
	_H_32 = _R.C("CoreConst").ItemStat.MinDamage
except AttributeError as _he:
	_H_32 = _HoistPending(_he)
try:
	_H_33 = _R.C("CoreConst").ItemStat.MaxDamage
except AttributeError as _he:
	_H_33 = _HoistPending(_he)
try:
	_H_34 = _R.C("CoreConst").ItemStat.Cooldown
except AttributeError as _he:
	_H_34 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").EventType.Health
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").EventType.LoseHealth
except AttributeError as _he:
	_H_5 = _HoistPending(_he)
try:
	_H_6 = _R.C("CoreConst").EventType.Empower
except AttributeError as _he:
	_H_6 = _HoistPending(_he)
try:
	_H_7 = _R.C("CoreConst").EventType.Stun
except AttributeError as _he:
	_H_7 = _HoistPending(_he)
try:
	_H_8 = _R.C("CoreConst").EventType.StunResisted
except AttributeError as _he:
	_H_8 = _HoistPending(_he)
try:
	_H_9 = _R.C("CoreConst").EventType.InvulnerableStart
except AttributeError as _he:
	_H_9 = _HoistPending(_he)
