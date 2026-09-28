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

		event = _R.C("CoreEvent")(self.eventNum, self.getTimeStamp(), triggerEvent,
				origin, type)

		for character in _iter([self._ctx.player, self._ctx.opponent]):
			self._ctx.hooks.snapshotCharacterStat(character, _R.C("CoreCharacter").Stat.Stamina)

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
				event = self.createEvent(triggerEvent, origin, _R.C("CoreConst").EventType.CriticalDamage)
			else:
				event = self.createEvent(triggerEvent, origin, _R.C("CoreConst").EventType.DealDamage)
			event.setParam("damage", damageRes.damage)

			attackedCharacter = None
			if damageRes.damageSource.hasType(_R.C("CoreDamageSource").Type.SelfDamage):
				attackedCharacter = character
			else:
				attackedCharacter = character.opponent

			event.setTarget(attackedCharacter.playerId)
			self._ctx.hooks.snapshotCharacterStat(attackedCharacter, _R.C("CoreCharacter").Stat.Health)
			self._ctx.hooks.snapshotStack(attackedCharacter, _R.C("CoreConst").EventType.Block)
			self._ctx.hooks.snapshotDamageDealt(character.playerId, 
				damageRes.damageSource.types[0], damageRes.damage)
			self._ctx.hooks.updateDamageMeter(character.playerId, event)
		else:
			event = self.createEvent(triggerEvent, origin, _R.C("CoreConst").EventType.MissedAttack)
			event.setParam("damage", damageRes.damage)
			event.setTarget(character.opponent.playerId)
			self._ctx.hooks.snapshotCharacterStat(character.opponent, _R.C("CoreCharacter").Stat.Health)
			self._ctx.hooks.snapshotStack(character.opponent, _R.C("CoreConst").EventType.Block)

		return event


	def createEvent_Damage(self, damageRes, damagingPlayerId, triggerEvent=None):
		event = None
		if damageRes.wasCriticalHit():
			event = self.createEvent(triggerEvent, damageRes.damageSource.types[0], 
				_R.C("CoreConst").EventType.CriticalDamage)
		else:
			event = self.createEvent(triggerEvent, damageRes.damageSource.types[0], 
				_R.C("CoreConst").EventType.DealDamage)
		event.setParam("damage", damageRes.damage)
		event.setTarget(damagingPlayerId)
		damagingCharacter = self._ctx.getCharacterFromId(damagingPlayerId)
		damagedCharacter = damagingCharacter.opponent
		self._ctx.hooks.snapshotCharacterStat(damagedCharacter, _R.C("CoreCharacter").Stat.Health)
		self._ctx.hooks.snapshotStack(damagedCharacter, _R.C("CoreConst").EventType.Block)
		self._ctx.hooks.snapshotDamageDealt(damagingPlayerId, damageRes.damageSource.types[0], damageRes.damage)
		self._ctx.hooks.updateDamageMeter(damagingPlayerId, event)
		return event


	# ── 生命类（对齐 704-720） ──
	def createEvent_Heal(self, amount, playerId, origin, triggerEvent=None):
		event = self.createEvent(triggerEvent, origin, _R.C("CoreConst").EventType.Health)
		event.setParam("amount", amount)
		event.setTarget(playerId)
		self._ctx.hooks.snapshotCharacterStat(self._ctx.getCharacterFromId(playerId), _R.C("CoreCharacter").Stat.Health)
		return event


	def createEvent_LoseHealth(self, amount, playerId, origin, triggerEvent=None):
		event = self.createEvent(triggerEvent, origin, _R.C("CoreConst").EventType.LoseHealth)
		event.setParam("amount", amount)
		event.setTarget(playerId)
		self._ctx.hooks.snapshotCharacterStat(self._ctx.getCharacterFromId(playerId), _R.C("CoreCharacter").Stat.Health)
		return event


	# ── 栈类（对齐 722-774） ──
	def createEvent_Stack(self, type, item, amount, playerId, triggerEvent=None, used=False, reflected=False):

		event = self.createEvent(triggerEvent, item, type)
		event.setParam("amount", amount)
		event.setParam("used", used)
		event.setParam("reflected", reflected)
		event.setTarget(playerId)
		self._ctx.hooks.snapshotStack(self._ctx.getCharacterFromId(playerId), type)

		if type == _R.C("CoreConst").EventType.Empower:
			for i in _iter(self._ctx.getCharacterFromId(playerId).items):
				if i.isWeapon() and i.canBeEmpowered():
					self._ctx.hooks.snapshotItemTooltipStat(i, _R.C("CoreConst").ItemStat.MinDamage)
					self._ctx.hooks.snapshotItemTooltipStat(i, _R.C("CoreConst").ItemStat.MaxDamage)

		if type == _R.C("CoreConst").EventType.Heat or type == _R.C("CoreConst").EventType.Cold:
			for i in _iter(self._ctx.getCharacterFromId(playerId).items):
				if i.hasCooldown():
					self._ctx.hooks.snapshotItemTooltipStat(i, _R.C("CoreConst").ItemStat.Cooldown)

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
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.Stun)
		event.setParam("duration", duration)
		event.setTarget(playerId)
		return event


	def createEvent_StunResist(self, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.StunResisted)
		event.setTarget(playerId)
		return event


	def createEvent_InvulnerableStart(self, item, duration, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.InvulnerableStart)
		event.setParam("duration", duration)
		event.setTarget(playerId)
		return event


	def createEvent_InvulnerableEnd(self, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.InvulnerableEnd)
		event.setTarget(playerId)
		return event


	# ── 体力类（对齐 798-813） ──
	def createEvent_Stamina(self, amount, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.Stamina)
		event.setParam('stamina', _div(floor(amount * 10), 10.0))
		event.setTarget(playerId)
		return event


	def createEvent_DrainStamina(self, amount, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.DrainStamina)
		event.setTarget(playerId)
		event.setParam('stamina', _div(floor(amount * 10), 10.0))
		return event


	def createEvent_OutOfStamina(self, item, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.OutofStamina)
		event.setTarget(playerId)
		return event


	# ── 伤害修正 / 上限类（对齐 815-834） ──
	def createEvent_DamageBuff(self, item, buffedItem, damage, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.DamageBuff)
		event.setTarget(playerId)
		event.setParam("item", buffedItem.getTranslatedName())
		event.setParam("damage", damage)
		return event


	def createEvent_TemporaryMaxHealth(self, item, amount, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.TemporaryMaxHealth)
		event.setParam("amount", amount)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _R.C("CoreCharacter").Stat.Health)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _R.C("CoreCharacter").Stat.MaxHealth)
		return event


	def createEvent_TemporaryMaxStamina(self, item, amount, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.TemporaryMaxStamina)
		event.setParam("stamina", amount)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _R.C("CoreCharacter").Stat.Stamina)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _R.C("CoreCharacter").Stat.MaxStamina)
		return event


	def createEvent_BattleRageStart(self, item, duration, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.BattleRageStart)
		event.setParam("duration", duration)
		return event


	def createEvent_BattleRageEnd(self, playerId, triggerEvent=None):
		event = self.createEvent(triggerEvent, _R.C("CoreConst").EventType.BattleRageEnd,
			_R.C("CoreConst").EventType.BattleRageEnd)
		event.setTarget(playerId)
		return event


	def createEvent_Reincarnate(self, item, health, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.Reincarnate)
		event.setParam("health", health)
		self._ctx.hooks.snapshotCharacterStat(item.character(), _R.C("CoreCharacter").Stat.Health)
		return event


	def createEvent_Activation(self, item, triggerEvent=None):
		event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.Activation)
		return event


	def createEvent_DamChange(self, item, amount, isPercent, duration=None, type=None, triggerEvent=None):

		event = None
		if amount > 0:
			event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.DamIncrease)
		else:
			event = self.createEvent(triggerEvent, item, _R.C("CoreConst").EventType.DamReduction)

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
