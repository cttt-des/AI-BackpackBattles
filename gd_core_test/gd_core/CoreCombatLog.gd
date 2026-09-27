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
extends Reference
class_name CoreCombatLog


var eventNum := 0
var _ctx


# 对齐 CombatLog 的时间戳来源：CombatTimer.combatTime
func getTimeStamp() -> float:
	return _ctx.combat_time


# ── 核心工厂（对齐 CombatLog.gd:240-249） ──
func createEvent(triggerEvent, origin, type) -> CoreEvent:
	eventNum += 1
	
	var event = CoreEvent.new(eventNum, getTimeStamp(), triggerEvent, 
			origin, type)
	
	for character in [_ctx.player, _ctx.opponent]:
		_ctx.hooks.snapshotCharacterStat(character, CoreCharacter.Stat.Stamina)
	
	return event


func logEvent(event) -> void :
	_ctx.hooks.logEvent(event)


# ── 攻击类（对齐 653-702） ──
func createEvent_Attack(damageRes, triggerEvent = null):
	var event
	var origin = damageRes.damageSource.origin
	var character = origin.character()
	
	if damageRes.hasHit():
		if damageRes.wasCriticalHit():
			event = createEvent(triggerEvent, origin, CoreConst.EventType.CriticalDamage)
		else:
			event = createEvent(triggerEvent, origin, CoreConst.EventType.DealDamage)
		event.setParam("damage", damageRes.damage)
		
		var attackedCharacter
		if damageRes.damageSource.hasType(CoreDamageSource.Type.SelfDamage):
			attackedCharacter = character
		else:
			attackedCharacter = character.opponent
		
		event.setTarget(attackedCharacter.playerId)
		_ctx.hooks.snapshotCharacterStat(attackedCharacter, CoreCharacter.Stat.Health)
		_ctx.hooks.snapshotStack(attackedCharacter, CoreConst.EventType.Block)
		_ctx.hooks.snapshotDamageDealt(character.playerId, 
			damageRes.damageSource.types[0], damageRes.damage)
		_ctx.hooks.updateDamageMeter(character.playerId, event)
	else:
		event = createEvent(triggerEvent, origin, CoreConst.EventType.MissedAttack)
		event.setParam("damage", damageRes.damage)
		event.setTarget(character.opponent.playerId)
		_ctx.hooks.snapshotCharacterStat(character.opponent, CoreCharacter.Stat.Health)
		_ctx.hooks.snapshotStack(character.opponent, CoreConst.EventType.Block)
	
	return event


func createEvent_Damage(damageRes, damagingPlayerId, triggerEvent = null):
	var event
	if damageRes.wasCriticalHit():
		event = createEvent(triggerEvent, damageRes.damageSource.types[0], 
			CoreConst.EventType.CriticalDamage)
	else:
		event = createEvent(triggerEvent, damageRes.damageSource.types[0], 
			CoreConst.EventType.DealDamage)
	event.setParam("damage", damageRes.damage)
	event.setTarget(damagingPlayerId)
	var damagingCharacter = _ctx.getCharacterFromId(damagingPlayerId)
	var damagedCharacter = damagingCharacter.opponent
	_ctx.hooks.snapshotCharacterStat(damagedCharacter, CoreCharacter.Stat.Health)
	_ctx.hooks.snapshotStack(damagedCharacter, CoreConst.EventType.Block)
	_ctx.hooks.snapshotDamageDealt(damagingPlayerId, damageRes.damageSource.types[0], damageRes.damage)
	_ctx.hooks.updateDamageMeter(damagingPlayerId, event)
	return event


# ── 生命类（对齐 704-720） ──
func createEvent_Heal(amount: int, playerId: int, origin, triggerEvent = null):
	var event = createEvent(triggerEvent, origin, CoreConst.EventType.Health)
	event.setParam("amount", amount)
	event.setTarget(playerId)
	_ctx.hooks.snapshotCharacterStat(_ctx.getCharacterFromId(playerId), CoreCharacter.Stat.Health)
	return event


func createEvent_LoseHealth(amount: int, playerId: int, origin, triggerEvent = null):
	var event = createEvent(triggerEvent, origin, CoreConst.EventType.LoseHealth)
	event.setParam("amount", amount)
	event.setTarget(playerId)
	_ctx.hooks.snapshotCharacterStat(_ctx.getCharacterFromId(playerId), CoreCharacter.Stat.Health)
	return event


# ── 栈类（对齐 722-774） ──
func createEvent_Stack(type: int, item, amount: int, 
	playerId: int, triggerEvent = null, 
	used: bool = false, reflected: bool = false):
	
	var event = createEvent(triggerEvent, item, type)
	event.setParam("amount", amount)
	event.setParam("used", used)
	event.setParam("reflected", reflected)
	event.setTarget(playerId)
	_ctx.hooks.snapshotStack(_ctx.getCharacterFromId(playerId), type)
	
	if type == CoreConst.EventType.Empower:
		for i in _ctx.getCharacterFromId(playerId).items:
			if i.isWeapon() and i.canBeEmpowered():
				_ctx.hooks.snapshotItemTooltipStat(i, CoreConst.ItemStat.MinDamage)
				_ctx.hooks.snapshotItemTooltipStat(i, CoreConst.ItemStat.MaxDamage)
	
	if type == CoreConst.EventType.Heat or type == CoreConst.EventType.Cold:
		for i in _ctx.getCharacterFromId(playerId).items:
			if i.hasCooldown():
				_ctx.hooks.snapshotItemTooltipStat(i, CoreConst.ItemStat.Cooldown)
	
	return event


func createEvent_StackTemporary(type, item, amount, duration, playerId, 
	triggerEvent, reflected: bool = false):
	var event = createEvent_Stack(type, item, amount, playerId, triggerEvent)
	event.setParam("duration", duration)
	event.setParam("reflected", reflected)
	return event


func createEvent_StackTimeout(type, item, amount, playerId, triggerEvent):
	var event = createEvent_Stack(type, item, amount, playerId, triggerEvent)
	event.setParam("timeout", true)
	return event


func createEvent_StackResistOrNullify(type, item, amount, playerId, triggerEvent, 
	reflect: bool = false):
	var event = createEvent_Stack(type, item, amount, playerId, triggerEvent)
	event.setParam("resisted", true)
	event.setParam("reflected", reflect)
	return event


func createEvent_StackProtect(type, item, amount, playerId, triggerEvent):
	var event = createEvent_Stack(type, item, amount, playerId, triggerEvent)
	event.setParam("protected", true)
	return event


# ── 控制类（对齐 776-796） ──
func createEvent_Stun(item, duration, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.Stun)
	event.setParam("duration", duration)
	event.setTarget(playerId)
	return event


func createEvent_StunResist(item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.StunResisted)
	event.setTarget(playerId)
	return event


func createEvent_InvulnerableStart(item, duration, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.InvulnerableStart)
	event.setParam("duration", duration)
	event.setTarget(playerId)
	return event


func createEvent_InvulnerableEnd(item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.InvulnerableEnd)
	event.setTarget(playerId)
	return event


# ── 体力类（对齐 798-813） ──
func createEvent_Stamina(amount, item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.Stamina)
	event.setParam("stamina", floor(amount * 10) / 10.0)
	event.setTarget(playerId)
	return event


func createEvent_DrainStamina(amount, item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.DrainStamina)
	event.setTarget(playerId)
	event.setParam("stamina", floor(amount * 10) / 10.0)
	return event


func createEvent_OutOfStamina(item, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.OutofStamina)
	event.setTarget(playerId)
	return event


# ── 伤害修正 / 上限类（对齐 815-834） ──
func createEvent_DamageBuff(item, buffedItem, damage, playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.DamageBuff)
	event.setTarget(playerId)
	event.setParam("item", buffedItem.getTranslatedName())
	event.setParam("damage", damage)
	return event


func createEvent_TemporaryMaxHealth(item, amount, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.TemporaryMaxHealth)
	event.setParam("amount", amount)
	_ctx.hooks.snapshotCharacterStat(item.character(), CoreCharacter.Stat.Health)
	_ctx.hooks.snapshotCharacterStat(item.character(), CoreCharacter.Stat.MaxHealth)
	return event


func createEvent_TemporaryMaxStamina(item, amount, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.TemporaryMaxStamina)
	event.setParam("stamina", amount)
	_ctx.hooks.snapshotCharacterStat(item.character(), CoreCharacter.Stat.Stamina)
	_ctx.hooks.snapshotCharacterStat(item.character(), CoreCharacter.Stat.MaxStamina)
	return event


func createEvent_BattleRageStart(item, duration, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.BattleRageStart)
	event.setParam("duration", duration)
	return event


func createEvent_BattleRageEnd(playerId, triggerEvent = null):
	var event = createEvent(triggerEvent, CoreConst.EventType.BattleRageEnd, 
		CoreConst.EventType.BattleRageEnd)
	event.setTarget(playerId)
	return event


func createEvent_Reincarnate(item, health: int, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.Reincarnate)
	event.setParam("health", health)
	_ctx.hooks.snapshotCharacterStat(item.character(), CoreCharacter.Stat.Health)
	return event


func createEvent_Activation(item, triggerEvent = null):
	var event = createEvent(triggerEvent, item, CoreConst.EventType.Activation)
	return event


func createEvent_DamChange(item, amount: float, isPercent: bool, 
	duration = null, type = null, triggerEvent = null):
	
	var event = null
	if amount > 0:
		event = createEvent(triggerEvent, item, CoreConst.EventType.DamIncrease)
	else:
		event = createEvent(triggerEvent, item, CoreConst.EventType.DamReduction)
	
	event.setParam("amount", amount)
	event.setParam("isPercent", isPercent)
	if duration != null:
		event.setParam("duration", duration)
	if type != null:
		event.setParam("type", type)
	return event


# ── 统计入口（全部走钩子，无判定影响） ──
func snapshotMetric(playerId, metric, eventType, value):
	_ctx.hooks.snapshotMetric(playerId, metric, eventType, value)


func snapshotItemMetric(item, metricIndex, playerId = null, withNextEvent = false):
	if playerId == null:
		playerId = item.character().playerId
	
	var connectedEventNum = eventNum
	if withNextEvent:
		connectedEventNum += 1
	_ctx.hooks.snapshotItemMetric(item, metricIndex, playerId, withNextEvent)


func snapshotItemTooltipStat(item, statType, playerId = null, 
	withNextEvent = false, event = null):
	if playerId == null:
		playerId = item.character().playerId
	
	var connectedEventNum = eventNum
	if event != null:
		connectedEventNum = event.id
	elif withNextEvent:
		connectedEventNum += 1
	
	_ctx.hooks.snapshotItemTooltipStat(item, statType, playerId, withNextEvent, event)


func snapshotItemState(item, state, withNextEvent: bool, event):
	var playerId = item.character().playerId
	_ctx.hooks.snapshotItemState(item, state, withNextEvent, event)


func snapshotGlobalStat(stat: int, newValue):
	_ctx.hooks.snapshotGlobalStat(stat, newValue)


# 对齐 CombatLog.gd:517-518（签名必须 4 参：物品行为与 CoreCharacter 都会带
# withNextEvent / event 调用，例如 startBattleRage 里的 snapshotCharacterStat(self, Stat.BattleRage, false, event)）
func snapshotCharacterStat(character, statType, withNextEvent: bool = false, event = null):
	_ctx.hooks.snapshotCharacterStat(character, statType, withNextEvent, event)


func snapshotStack(character, type):
	_ctx.hooks.snapshotStack(character, type)
