# =============================================================================
# CoreCharacter.gd — 无头战斗内核：角色（伤害链 / 体力 / 栈宿主）
# =============================================================================
# 对齐源码：Core/Character.gd（全文 1700 行）
#
# 逐字保留（本内核的判定主体）：
#   takeDamage 全链 17 步（Character.gd:495-653，顺序即真值）：
#     isDead 短路 → attackEffectCount=1+rollDoubleAttackEffect → 命中(accuracyRng/闪避栈)
#     → preDealDamage_early × count → randDamage（含疲劳加成）→ 暴击（critRng → 攻方
#       critTokens → 守方 critTokens 代打 → critResisted）→ 抗性 clamp(-10,1) 后 round
#     → isAttack 才减 damageReduction → invulnerable 归零 → pre_take_damage 信号
#       （盾牌挂钩）→ 减 damageReduction 并 max(0) → preDealDamage_late × count
#     → pre_take_damage_late → 格挡（先扣 block，healthDamage=0 或扣血）→ 扣血
#     → 事件 → character_attacked / character_damaged → onDealtDamage × count
#     → 死亡判定 → applySpikes
#   dealDamage / applyVampirism / applySpikes / heal（healingEfficiency + Unhealing 反噬）
#   loseHealth（不吃减伤）/ useStamina（allowStaminaOverflow 窗口）/ addStamina /
#   gainStamina / drainStamina / onTick（偶数秒再生、奇数秒毒伤）/ stun / critResisted /
#   onTick 与疲劳伤害入口 takeFatigueDamage / getMaxHealth / changeMaxHealthTemporary
#
# 保真保留的原版疑点（不修）：
#   · `setBlock(amount)` 实际写入的是 **Spikes** 栈（Character.gd:1182-1183 原样如此）
#   · `gainStacks(buffType, ..., reflect)` 忽略 reflect，直接转发 buffs[buffType].gainStacks
#   · `setCurrentHealth` 不做 clamp
#
# 剥离内容：动画 / 音效 / 伤害数字与 buff 标签 / 立绘 / 相机 / HUD 信号
#   → 全部改走 ctx.hooks；伤害数字坐标（randDmgNumberPos 等）整体删除（纯表现）
#
# 本期未实现、以接缝占位：
#   · 战怒（AUTO_RAGE 5s/4s）—— 需要 isBattleRageItem 的物品行为判定，随物品行为一起接
#   · invulnerabilityTimer / 自动 rage 计时器 —— 需要内核计时驱动，接入点已留（`_tick`）
# =============================================================================
extends Reference
class_name CoreCharacter


enum ID{
	PLAYER = 0, 
	OPPONENT = 1
}

enum Stat{
	Health, 
	MaxHealth, 
	Stamina, 
	MaxStamina, 
	Invulnerable, 
	Stunned, 
	BattleRage, 
	ReflectStacks, 
	DebuffResistStacks, 
	CritStacks, 
	DodgeStacks, 
	CritResistStacks, 
	CritResistance, 
	StunResistance, 
	HealEfficiency, 
	DamageResistance, 
	MeleeDmgFactor, 
	RangedDmgFactor, 
	EffectDmgFactor, 
	Unhealing, 
	StaminaRegen, 
	MaxHealthGain
}

const AUTO_RAGE_DELAY = 5.0
const AUTO_RAGE_DUR = 4.0

var ctx
var playerId: int
var opponent = null
var isDead := false
var buffs: Dictionary = {}

var maxHealth: float = 30.0
var curHealth: float
var temporaryMaxHealth: float = 0.0
var temporaryMaxHealthGain: float = 1.0

var baseMaxStamina: float
var maxStamina: float = 5.0
var curStamina: float
var temporaryMaxStamina: float = 0.0
var baseStaminaRegen: float = 1.0
var staminaRegen: float = 0.0
var allowStaminaOverflow := false

var statsDisplay: Array = []      # 仅统计出口

# 战斗修正量（对齐 Character.gd:64+）
var damageResistance: float = 0.0
var damageReduction: int = 0
var invulnerable := false
var dodgeStacks: int = 0
var critResistance: float = 0.0
var critResistStacks: int = 0
var critTokens: int = 0
var stunResistance: float = 0.0
var unhealingAmount: float = 0.0
var healingEfficiency: float = 1.0
var critTokensUsed := 0
var debuffResistStacks: int = 0
var debuffReflectStacks: int = 0
var buffProtectStacks: int = 0
var bonusFatigueDamage: int = 0
var empowerDamage: float = 1.0
var blindingLightActive := false
var stunnedDuration: float = 0.0
var tickCounter := 0

# 伤害类型系数（对齐 cleanse 里 typedDamageFactors 的初始化：全部 0.0）
var typedDamageFactors: Dictionary = {}

# 近战/远程/效果 尖刺与吸血上限（对齐 Character.gd:389-393）
var meleeSpikesLimit: float = 1.0
var rangedSpikesLimit: float = 0.0
var effectSpikesLimit: float = 0.0
var meleeVampirismLimit: float = 1.0
var rangedVampirismLimit: float = 0.0

var battleRageAura = null         # 表现
var battleRageBonusDur: float = 0.0

# 四类平衡随机源（对齐 Character.gd:299-302）
var accuracyRng                 # CoreRng.BalancedRng
var critRng
var critResistanceRng
var stunResistanceRng

var items: Array = []             # 该角色的参战物品（替代 INVENTORY.getItems()）

# 战斗事件信号（对齐 Character.tscn 的 connect）
var character_died_handlers: Array = []

# 角色自带伤害源（对齐 Character.tscn 上的 Poison / Spikes / Unhealing DamageSource 节点）
var poisonDamageSource          # CoreDamageSource，types=[Poison]
var spikeDamageSource           # CoreDamageSource，types=[Spikes]

# 无敌计时（对齐 invulnerabilityTimer，物理帧步进）
var invulnerabilityItem = null
var _invul_left: float = 0.0
var _invul_active := false


func _init(_ctx, _playerId: int) -> void :
	ctx = _ctx
	playerId = _playerId
	accuracyRng = ctx.rng.BalancedRng.new(ctx.rng)
	critRng = ctx.rng.BalancedRng.new(ctx.rng)
	critResistanceRng = ctx.rng.BalancedRng.new(ctx.rng)
	stunResistanceRng = ctx.rng.BalancedRng.new(ctx.rng)
	
	for stackType in CoreConst.getStacks():
		var buff = CoreBuff.new()
		buff.init(stackType, self, "_stacks_changed_%d" % stackType)
		buffs[stackType] = buff
	
	curHealth = maxHealth
	baseMaxStamina = maxStamina
	curStamina = 0.0
	staminaRegen = baseStaminaRegen
	
	for type in CoreDamageSource.Type.values():
		typedDamageFactors[type] = 0.0


func setOpponent(_opponent) -> void :
	opponent = _opponent


func isPlayer() -> bool:
	return playerId == ID.PLAYER


func getName() -> String:
	return ["Player", "Opponent"][playerId]


func registerCharacterDied(handler) -> void :
	character_died_handlers.push_back(handler)


# 原版仅有一对 connect（Game.gd:2549 / 2986）。重复 setup 时先清空，
# 避免同一 handler 被注册多次导致 endCombat 重入判定被跳过之外的副作用。
func clearCharacterDiedHandlers() -> void :
	character_died_handlers.clear()


# ─────────────────────────── 准备 / 开始 / 结束（对齐 294-347） ───────────────────────────

func prepare() -> void :
	staminaRegen = baseStaminaRegen
	
	accuracyRng.reset()
	critRng.reset()
	critResistanceRng.reset()
	stunResistanceRng.reset()
	
	# 对齐 Character.gd:304-310：低于大师或大厅模式，玩家 -0.2、对手 +0.2
	if ctx.below_master or ctx.lobbies_mode:
		if playerId == ID.PLAYER:
			accuracyRng.setBias( - 0.2)
			critRng.setBias( - 0.2)
		else:
			accuracyRng.setBias(0.2)
			critRng.setBias(0.2)


func combatStart() -> void :
	stunnedDuration = 0.0
	tickCounter = 0


func combatEnd() -> void :
	attackMovingForward_reset()
	
	for buffType in buffs:
		buffs[buffType].combatEnd()


# 原版是动画 tween 复位；无头下只需清标志
func attackMovingForward_reset() -> void :
	pass


func cleanse() -> void :
	isDead = false
	temporaryMaxHealth = 0
	temporaryMaxHealthGain = 1.0
	staminaRegen = baseStaminaRegen
	healToFull()
	setTemporaryMaxStamina(0)
	fillUpStamina()
	endStun()
	setBlock(0)
	
	for buffType in buffs:
		buffs[buffType].reset()
	
	invulnerable = false
	
	damageResistance = 0.0
	damageReduction = 0
	dodgeStacks = 0
	critResistance = 0.0
	critResistStacks = 0
	stunResistance = 0.0
	unhealingAmount = 0.0
	healingEfficiency = 1.0
	critTokens = 0
	debuffResistStacks = 0
	debuffReflectStacks = 0
	buffProtectStacks = 0
	battleRageBonusDur = 0.0
	bonusFatigueDamage = 0
	blindingLightActive = false
	meleeSpikesLimit = 1.0
	rangedSpikesLimit = 0.0
	effectSpikesLimit = 0.0
	meleeVampirismLimit = 1.0
	rangedVampirismLimit = 0.0
	empowerDamage = 1.0
	for damageType in CoreDamageSource.Type.values():
		typedDamageFactors[damageType] = 0.0
	
	poisonDamageSource.critChancePercent = 0
	spikeDamageSource.critChancePercent = 0


# ─────────────────────────── 每秒 Tick（对齐 401-414） ───────────────────────────

func onTick() -> void :
	if tickCounter % 2 == 0:
		var regen = getRegeneration()
		if regen > 0:
			heal(regen, CoreConst.EventType.Regeneration)
			ctx.hooks.activateBuffCounter(self, CoreConst.EventType.Regeneration)
	else:
		var poison = getPoison()
		if poison > 0:
			poisonDamageSource.setDamage(poison)
			takeDamage(poisonDamageSource)
			ctx.hooks.activateBuffCounter(self, CoreConst.EventType.Poison)
	
	tickCounter += 1


# ─────────────────────────── 伤害主链（对齐 482-653） ───────────────────────────

func dealDamage(damageSource: CoreDamageSource, triggerEvent = null) -> CoreDamageResult:
	var res = opponent.takeDamage(damageSource, triggerEvent)
	applyVampirism(res)
	return res


func takeDamage(damageSource: CoreDamageSource, triggerEvent = null) -> CoreDamageResult:
	
	var damageRes = CoreDamageResult.new()
	
	damageSource = CoreDamageSource.new().fromDamageSource(damageSource)
	# 无头内核的随机源按对象持有（原版为全局 Util.rng），复制出的新实例需补注入；
	# DamageResult 随机取值路径（randDamage）才会与本场战斗同一随机流。
	damageSource._rng = ctx.rng
	damageRes.damageSource = damageSource
	damageRes.reset()
	
	if isDead:
		return damageRes
	
	var item = null
	if damageSource.origin is CoreItem:
		item = damageSource.origin
	
	var attackEffectCount: = 1
	
	if item != null:
		attackEffectCount += item.rollDoubleAttackEffect()
	
	if damageSource.canMiss():
		var accuracy = damageSource.accuracy
		damageRes.hit = accuracyRng.rollPercent(accuracy)
		if damageRes.hit and dodgeStacks > 0:
			changeDodgeStacks( - 1)
			damageRes.hit = false
	else:
		damageRes.hit = true
	
	if item != null and damageSource.isAttack():
		item.preDealDamage_early(damageRes)
		if item.hasPreDealDamageEarlyEffect:
			for i in attackEffectCount:
				item._behavior_call("onPreDealDamage_early", [damageRes])
	
	if damageRes.hit:
		damageRes.damage += damageSource.randDamage()
		
		if damageSource.hasType(CoreDamageSource.Type.Fatigue):
			damageRes.damage += bonusFatigueDamage
		
		if damageSource.canCrit():
			var critical = false
			
			var critChancePercent = damageSource.getCritChancePercent()
			if critChancePercent > 0 and critRng.rollPercent(critChancePercent):
				critical = true
			
			if not damageRes.critical and item != null and item.getCritTokens() > 0:
				item.useCritToken()
				critical = true
			
			if not damageRes.critical and opponent.getCritTokens() > 0:
				opponent.useCritToken()
				critical = true
			
			if critical:
				if critResisted():
					ctx.hooks.spawnBuffLabel(CoreConst.EventType.CriticalResisted, null)
				else:
					damageRes.makeCritical()
		
		var activeDmgResi = clamp(damageResistance / 100, - 10, 1)
		damageRes.damage = round(damageRes.damage * (1.0 - activeDmgResi))
		
		if damageRes.damageSource.isAttack():
			damageRes.damage -= damageReduction
		
		if invulnerable:
			damageRes.damage = 0
		
		ctx.bus.emitSignal(self, "pre_take_damage", [damageRes])
		
		damageRes.damage -= damageRes.damageReduction
		
		damageRes.damage = max(0, damageRes.damage)
		
		if item != null and damageSource.isAttack():
			item.preDealDamage_late(damageRes)
			if item.hasPreDealDamageLateEffect:
				for i in attackEffectCount:
					item._behavior_call("onPreDealDamage_late", [damageRes])
		
		ctx.bus.emitSignal(self, "pre_take_damage_late", [damageRes])
		damageRes.healthDamage = damageRes.damage
		
		if damageSource.canBeBlocked():
			var curBlock = getBlock()
			if damageRes.damage > curBlock:
				damageRes.healthDamage -= curBlock
				loseBlock(curBlock)
			else:
				loseBlock(damageRes.damage)
				damageRes.healthDamage = 0
		
		curHealth -= damageRes.healthDamage
		
		if damageRes.wasCriticalHit():
			spawnLabel_native(CoreConst.EventType.CriticalDamage, damageRes.damage, item)
		elif damageSource.hasType(CoreDamageSource.Type.Fatigue):
			spawnLabel_native(CoreConst.EventType.Fatigue, damageRes.damage, item)
		elif damageSource.hasType(CoreDamageSource.Type.Poison):
			spawnLabel_native(CoreConst.EventType.Poison, damageRes.damage, item)
		elif damageSource.hasType(CoreDamageSource.Type.Spikes):
			spawnLabel_native(CoreConst.EventType.Spikes, damageRes.damage, item)
		else:
			spawnLabel_native(CoreConst.EventType.DealDamage, damageRes.damage, item)
		
		# 原版此处写入 damageAnimation 播放速度与片段（纯表现）→ 已剥离
		ctx.hooks.damageAnimation(self, "Fatigue" if damageSource.hasType(CoreDamageSource.Type.Fatigue) else "Hit")
	else:
		spawnLabel_native(CoreConst.EventType.MissedAttack, 0, item)
	
	var event
	if item != null:
		event = ctx.combat_log.createEvent_Attack(damageRes, triggerEvent)
		ctx.bus.emitSignal(item, "dealt_damage_signal_placeholder", [damageRes])
		item.dealtDamage(damageRes)
	else:
		event = ctx.combat_log.createEvent_Damage(damageRes, opponent.playerId, triggerEvent)
	
	damageRes.event = event
	ctx.bus.emitEvent(self, "character_attacked", event, [damageRes])
	ctx.bus.emitSignal(self, "character_damaged", [damageRes.healthDamage, damageRes.event])
	
	ctx.hooks.onHealthChangedUI(self)
	
	if (item != null and 
		damageSource.isAttack() and 
		item.hasDealtDamageEffect):
		for i in attackEffectCount:
			item._behavior_call("onDealtDamage", [damageRes])
	
	if curHealth <= 0:
		death()
	
	applySpikes(damageRes)
	
	return damageRes


func spawnLabel_native(type: int, damage: int, item = null) -> void :
	ctx.hooks.spawnLabel_character(self, type, damage, item)


func applySpikes(damageRes: CoreDamageResult) -> void :
	if getSpikes() > 0 and damageRes.canTriggerSpikes():
		var spikesLimit: float
		if damageRes.damageSource.hasType(CoreDamageSource.Type.Ranged):
			spikesLimit = rangedSpikesLimit
		else:
			spikesLimit = meleeSpikesLimit
		
		if damageRes.damageSource.hasType(CoreDamageSource.Type.Effect):
			spikesLimit = max(effectSpikesLimit, spikesLimit)
		
		var spikeDam = min(getSpikes(), round(damageRes.damage * spikesLimit))
		if spikeDam > 0:
			spikeDamageSource.setDamage(spikeDam)
			opponent.takeDamage(spikeDamageSource, damageRes.event)
			ctx.hooks.activateBuffCounter(self, CoreConst.EventType.Spikes)


func applyVampirism(damageRes: CoreDamageResult) -> void :
	if getVampirism() > 0 and damageRes.canTriggerVampirism():
		var vampLimit: float
		if damageRes.damageSource.hasType(CoreDamageSource.Type.Ranged):
			vampLimit = rangedVampirismLimit
		else:
			vampLimit = meleeVampirismLimit
		
		var healAmount = min(getVampirism(), round(damageRes.damage * vampLimit))
		if healAmount > 0:
			heal(healAmount, CoreConst.EventType.Vampirism, damageRes.event)
			ctx.hooks.activateBuffCounter(self, CoreConst.EventType.Vampirism)


# ─────────────────────────── 治疗 / 直接扣血（对齐 739-869） ───────────────────────────

func heal(amount, origin = null, triggerEvent = null) -> void :
	amount *= getHealingEfficiency()
	amount = round(amount)
	
	var missingHealth = getMaxHealth() - curHealth
	var overheal = max(0, amount - missingHealth)
	curHealth += amount
	curHealth = min(curHealth, getMaxHealth())
	
	ctx.hooks.onHealthChangedUI(self)
	ctx.hooks.spawnLabel_character(self, CoreConst.EventType.Health, amount, origin)
	
	var event = ctx.combat_log.createEvent_Heal(amount, playerId, origin, triggerEvent)
	
	if origin:
		if origin is CoreItem:
			origin.addMetric(CoreConst.ItemMetrics.Heal, amount)
			origin.addMetric(CoreConst.ItemMetrics.Overheal, overheal)
		else:
			ctx.combat_log.snapshotMetric(playerId, CoreConst.ItemMetrics.Heal, origin, amount)
			ctx.combat_log.snapshotMetric(playerId, CoreConst.ItemMetrics.Overheal, origin, overheal)
	
	ctx.bus.emitEvent(self, "character_healed", event, [event.getAmount(), event])
	if overheal > 0:
		ctx.bus.emitSignal(self, "character_overhealed", [overheal, event])
	
	if getUnhealing() > 0:
		var unhealing = ceil(amount * getUnhealing() * (1 + typedDamageFactors[CoreDamageSource.Type.Unhealing]))
		if unhealing > 0:
			ctx.unhealingDamageSource.setDamage(unhealing)
			opponent.takeDamage(ctx.unhealingDamageSource, event)


func healToFull() -> void :
	curHealth = getMaxHealth()
	ctx.hooks.onHealthChangedUI(self)


func reincarnate(healAmount: int, isHeal: bool, item, triggerEvent):
	setCurrentHealth(0)
	
	healAmount = min(getMaxHealth(), healAmount)
	setCurrentHealth(healAmount)
	var event = ctx.combat_log.createEvent_Reincarnate(item, healAmount, triggerEvent)
	item.addMetric(CoreConst.ItemMetrics.Heal, healAmount)
	ctx.bus.emitEvent(self, "reincarnated", event, [event])
	return event


func getCurrentHealth():
	return curHealth


func getRelativeHealth() -> float:
	return getCurrentHealth() / getMaxHealth()


func getMissingHealth() -> int:
	return int(ceil(getMaxHealth() - getCurrentHealth()))


func setCurrentHealth(_curHealth) -> void :
	curHealth = _curHealth
	ctx.hooks.onHealthChangedUI(self)


func loseHealth(amount, item = null, triggerEvent = null):
	curHealth -= amount
	var event = null
	if item:
		event = ctx.combat_log.createEvent_LoseHealth( - amount, playerId, item, triggerEvent)
		ctx.bus.emitEvent(self, "character_damaged", event, [event.getAmount(), event])
	
	ctx.hooks.onHealthChangedUI(self)
	
	if curHealth <= 0:
		death()
	
	return event


func setMaxHealth(_maxHealth) -> void :
	maxHealth = _maxHealth
	curHealth = maxHealth
	ctx.hooks.onHealthChangedUI(self)


func giveMaxHealth(amount) -> void :
	maxHealth += amount
	curHealth += amount
	ctx.hooks.onHealthChangedUI(self)


func getBaseMaxHealth() -> float:
	return maxHealth


func getMaxHealth() -> float:
	return maxHealth + temporaryMaxHealth


func applyTemporaryMaxHealthGain(amount):
	return round(amount * temporaryMaxHealthGain)


func changeMaxHealthTemporary(amount, item = null, triggerEvent = null) -> void :
	if amount != 0:
		temporaryMaxHealth += amount
		
		curHealth += amount
		if item != null:
			var event = ctx.combat_log.createEvent_TemporaryMaxHealth(item, amount, triggerEvent)
			ctx.bus.emitEvent(self, "temporary_max_health_changed", event, [event])


# ─────────────────────────── 体力（对齐 791-848） ───────────────────────────

func getMaxStamina() -> float:
	return maxStamina + temporaryMaxStamina


func gainStamina(amount, item = null, triggerEvent = null) -> void :
	curStamina += amount
	
	if not allowStaminaOverflow:
		clampStamina()
	
	if item != null:
		var event = ctx.combat_log.createEvent_Stamina(amount, item, playerId, triggerEvent)
		ctx.bus.logEvent(event)
		item.staminaChanged(amount, CoreConst.StackChangeType.Added_Player)


func addStamina(amount) -> void :
	curStamina += amount
	clampStamina()


func clampStamina() -> void :
	curStamina = clamp(curStamina, 0, getMaxStamina())


func fillUpStamina() -> void :
	addStamina(maxStamina)


enum StaminaResult{
	Sufficient, 
	Insufficient
}


func useStamina(amount):
	allowStaminaOverflow = true
	ctx.bus.emitSignal(self, "character_pre_use_stamina", [amount])
	allowStaminaOverflow = false
	
	if curStamina >= amount:
		curStamina = max(curStamina - amount, 0)
		clampStamina()
		ctx.bus.emitSignal(self, "character_used_stamina", [amount])
		
		return StaminaResult.Sufficient
	else:
		clampStamina()
		
		return StaminaResult.Insufficient


func drainStamina(amount, item, triggerEvent = null):
	var drained = min(curStamina, amount)
	curStamina -= drained
	var event = ctx.combat_log.createEvent_DrainStamina(drained, item, playerId, triggerEvent)
	ctx.bus.logEvent(event)
	item.staminaChanged(drained, CoreConst.StackChangeType.Removed_Opponent)
	return event


func setTemporaryMaxStamina(amount) -> void :
	temporaryMaxStamina = amount


func setTemporaryMaxHealthGain(amount) -> void :
	temporaryMaxHealthGain = amount


# ─────────────────────────── 死亡 / 眩晕 / 抗性（对齐 997-1083, 1390-1408） ───────────────────────────

func death() -> void :
	isDead = true
	for handler in character_died_handlers:
		handler.call_func()


func stun(duration, item = null, triggerEvent = null) -> void :
	if stunResisted():
		ctx.hooks.spawnBuffLabel(CoreConst.EventType.StunResisted, null)
		var event = ctx.combat_log.createEvent_StunResist(item, playerId, triggerEvent)
		ctx.bus.logEvent(event)
	else:
		stunnedDuration = max(stunnedDuration, duration)
		var event = ctx.combat_log.createEvent_Stun(item, duration, playerId, triggerEvent)
		ctx.bus.logEvent(event)
		ctx.hooks.playStunAnimation(self, duration)


func endStun() -> void :
	stunnedDuration = 0.0
	ctx.combat_log.snapshotCharacterStat(self, Stat.Stunned)


func isStunned() -> bool:
	return stunnedDuration > 0


func changeDodgeStacks(amount: int) -> void :
	dodgeStacks = int(max(0, dodgeStacks + amount))
	ctx.combat_log.snapshotCharacterStat(self, Stat.DodgeStacks)


func changeCritResistance(amount: float) -> void :
	critResistance += amount
	ctx.combat_log.snapshotCharacterStat(self, Stat.CritResistance)


func critResisted() -> bool:
	var resisted = critResistanceRng.rollPercent(critResistance)
	if not resisted:
		if critResistStacks > 0:
			critResistStacks -= 1
			ctx.combat_log.snapshotCharacterStat(self, Stat.CritResistStacks)
			return true
	return resisted


func gainCritResistStacks(num: int) -> void :
	critResistStacks += num
	ctx.combat_log.snapshotCharacterStat(self, Stat.CritResistStacks)


func changeStunResistance(amount: float) -> void :
	stunResistance += amount


func stunResisted() -> bool:
	return stunResistanceRng.rollPercent(stunResistance)


func giveUnhealing(amount: float) -> void :
	unhealingAmount += amount
	ctx.combat_log.snapshotCharacterStat(self, Stat.Unhealing)


func reduceUnhealing(amount: float) -> void :
	unhealingAmount = max(0.0, unhealingAmount - amount)
	ctx.combat_log.snapshotCharacterStat(self, Stat.Unhealing)


func getUnhealing() -> float:
	return unhealingAmount


# 对齐 Character.gd:1421-1422（原版无返回类型标注）
func getHealingEfficiency():
	return max(0.0, healingEfficiency)


func addHealingEfficiency(amount: float) -> void :
	healingEfficiency += amount
	ctx.combat_log.snapshotCharacterStat(self, Stat.HealEfficiency)


func reduceHealingEfficiency(amount: float) -> void :
	healingEfficiency -= amount
	ctx.combat_log.snapshotCharacterStat(self, Stat.HealEfficiency)


func getCritTokens() -> int:
	return critTokens


func gainCritTokens(amount) -> void :
	critTokens += amount


func changeDebuffResistStacks(amount) -> void :
	debuffResistStacks += amount
	ctx.combat_log.snapshotCharacterStat(self, Stat.DebuffResistStacks)


func changeDebuffReflectStacks(amount) -> void :
	debuffReflectStacks += amount
	ctx.combat_log.snapshotCharacterStat(self, Stat.ReflectStacks)


func changeBuffProtectStacks(amount) -> void :
	buffProtectStacks += amount


func changeReflectChance(debuff, amount) -> void :
	buffs[debuff].changeReflectChance(amount)


func changeAllDebuffsReflectChance(amount) -> void :
	for debuff in CoreConst.getDebuffs():
		changeReflectChance(debuff, amount)


func changeMeleeSpikesLimit(amount) -> void :
	meleeSpikesLimit += amount


func changeRangedSpikesLimit(amount) -> void :
	rangedSpikesLimit += amount


func changeEffectSpikesLimit(amount) -> void :
	effectSpikesLimit += amount


func changeMeleeVampirismLimit(amount) -> void :
	meleeVampirismLimit += amount


func changeRangedVampirismLimit(amount) -> void :
	rangedVampirismLimit += amount


func getBonusFatigueDamage() -> int:
	return bonusFatigueDamage


func addFatigueDamage(amount) -> void :
	bonusFatigueDamage += amount
	ctx.bus.emitSignal(self, "fatigue_damage_changed")


func takeFatigueDamage(item = null) -> void :
	takeDamage(ctx.fatigueDamageSource)


func startBlindingLight() -> void :
	blindingLightActive = true


func endBlindingLight(event = null) -> void :
	blindingLightActive = false
	ctx.bus.emitSignal(self, "blinding_light_ended", [event])


func startBattleRage(item = null) -> void :
	# 完整战怒（5s/4s 自动开大、BattleRage 标签优先）依赖物品行为判定，
	# 随 Items/*.gd 接入时补齐；此处保留入口与事件形状。
	pass


# ── 无敌（对齐 Character.gd:1037-1062，Timer 改为物理帧步进） ──

func makeInvulnerable(invuDur, item, triggerEvent = null):
	invulnerabilityItem = item
	
	if not invulnerable:
		_invul_left = invuDur
		_invul_active = true
		invulnerable = true
	else:
		_invul_left = invuDur
	
	var event = ctx.combat_log.createEvent_InvulnerableStart(item, invuDur, playerId, triggerEvent)
	ctx.bus.emitEvent(self, "character_invulnerable_start", event, [event])
	ctx.combat_log.snapshotCharacterStat(self, Stat.Invulnerable)
	return event


func makeVulnerable(item, triggerEvent = null) -> void :
	pass


func invulnerabilityEnded() -> void :
	invulnerable = false
	var event = ctx.combat_log.createEvent_InvulnerableEnd(invulnerabilityItem, playerId)
	ctx.bus.emitEvent(self, "character_invulnerable_end", event, [event])
	ctx.combat_log.snapshotCharacterStat(self, Stat.Invulnerable)


func setInvulnerable(active: bool, item = null) -> void :
	invulnerable = active


# ─────────────────────────── 栈宿主（对齐 1122-1200+） ───────────────────────────

func getStacks(buffType) -> int:
	return buffs[buffType].getStacks()


func getBuffStacks() -> int:
	var stacks = 0
	for buff in CoreConst.getBuffs():
		stacks += getStacks(buff)
	return stacks


func getDebuffStacks() -> int:
	var stacks = 0
	for debuff in CoreConst.getDebuffs():
		stacks += getStacks(debuff)
	return stacks


func setStacks(buffType, amount: int) -> void :
	buffs[buffType].setStacks(amount)


func setStacksLogged(buffType, amount: int, item = null, triggerEvent = null) -> void :
	var curStacks = getStacks(buffType)
	if amount < curStacks:
		loseStacks(buffType, curStacks - amount, item, triggerEvent)
	elif amount > curStacks:
		gainStacks(buffType, amount - curStacks, item, triggerEvent)


func gainStacks(buffType, amount: int, item = null, triggerEvent = null, 
	reflect: bool = false):
	return buffs[buffType].gainStacks(amount, item, triggerEvent)


func gainStacksTemporary(buffType, amount: int, duration, item = null, 
	triggerEvent = null, reflect: bool = false):
	return buffs[buffType].gainTemporary(amount, duration, item, triggerEvent, reflect)


func loseStacks(buffType, amount: int, item = null, triggerEvent = null):
	return buffs[buffType].loseStacks(amount, item, triggerEvent)


func useStacks(buffType, amount: int, item = null, triggerEvent = null):
	return buffs[buffType].loseStacks(amount, item, triggerEvent, true)


func changeResistChance(buffType, chance) -> void :
	buffs[buffType].changeResistChance(chance)


func changeDebuffResistChances(chance) -> void :
	for debuff in CoreConst.getDebuffs():
		changeResistChance(debuff, chance)


func changeResistStacks(buffType, amount) -> void :
	buffs[buffType].changeResistStacks(amount)


func getBlock() -> int:
	return getStacks(CoreConst.EventType.Block)


# 对齐 Character.gd:1182-1183：原版此处写入的是 Spikes（原样保留，不修）
func setBlock(amount: int) -> void :
	setStacks(CoreConst.EventType.Spikes, amount)


func gainBlock(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Block, amount, item, triggerEvent)


func loseBlock(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Block, amount, item, triggerEvent)


# ── 各栈取值（对齐 1179-1360 的模板） ──

func getSpikes() -> int:
	return getStacks(CoreConst.EventType.Spikes)


func setSpikes(amount: int) -> void :
	setStacks(CoreConst.EventType.Spikes, amount)


func gainSpikes(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Spikes, amount, item, triggerEvent)


func loseSpikes(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Spikes, amount, item, triggerEvent)


func getVampirism() -> int:
	return getStacks(CoreConst.EventType.Vampirism)


func setVampirism(amount: int) -> void :
	setStacks(CoreConst.EventType.Vampirism, amount)


func gainVampirism(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Vampirism, amount, item, triggerEvent)


func loseVampirism(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Vampirism, amount, item, triggerEvent)


func getPoison() -> int:
	return getStacks(CoreConst.EventType.Poison)


func setPoison(amount: int) -> void :
	setStacks(CoreConst.EventType.Poison, amount)


func gainPoison(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Poison, amount, item, triggerEvent)


func losePoison(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Poison, amount, item, triggerEvent)


func getRegeneration() -> int:
	return getStacks(CoreConst.EventType.Regeneration)


func setRegeneration(amount: int) -> void :
	setStacks(CoreConst.EventType.Regeneration, amount)


func gainRegeneration(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Regeneration, amount, item, triggerEvent)


func loseRegeneration(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Regeneration, amount, item, triggerEvent)


func getLucky() -> int:
	return getStacks(CoreConst.EventType.Lucky)


func setLucky(amount: int) -> void :
	setStacks(CoreConst.EventType.Lucky, amount)


func gainLucky(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Lucky, amount, item, triggerEvent)


func loseLucky(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Lucky, amount, item, triggerEvent)


func getBlind() -> int:
	return getStacks(CoreConst.EventType.Blind)


func setBlind(amount: int) -> void :
	setStacks(CoreConst.EventType.Blind, amount)


func gainBlind(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Blind, amount, item, triggerEvent)


func loseBlind(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Blind, amount, item, triggerEvent)


func getMana() -> int:
	return getStacks(CoreConst.EventType.Mana)


func setMana(amount: int) -> void :
	setStacks(CoreConst.EventType.Mana, amount)


func gainMana(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Mana, amount, item, triggerEvent)


func loseMana(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Mana, amount, item, triggerEvent)


func getEmpower() -> int:
	return getStacks(CoreConst.EventType.Empower)


func setEmpower(amount: int) -> void :
	setStacks(CoreConst.EventType.Empower, amount)


func gainEmpower(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Empower, amount, item, triggerEvent)


func loseEmpower(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Empower, amount, item, triggerEvent)


func getHeat() -> int:
	return getStacks(CoreConst.EventType.Heat)


func setHeat(amount: int) -> void :
	setStacks(CoreConst.EventType.Heat, amount)


func gainHeat(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Heat, amount, item, triggerEvent)


func loseHeat(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Heat, amount, item, triggerEvent)


func getCold() -> int:
	return getStacks(CoreConst.EventType.Cold)


func setCold(amount: int) -> void :
	setStacks(CoreConst.EventType.Cold, amount)


func gainCold(amount: int, item = null, triggerEvent = null):
	return gainStacks(CoreConst.EventType.Cold, amount, item, triggerEvent)


func loseCold(amount, item = null, triggerEvent = null):
	return loseStacks(CoreConst.EventType.Cold, amount, item, triggerEvent)


func getBuffDamageMod() -> float:
	return getEmpower() * empowerDamage


# 对齐 Character.gd:1353-1354（原版无返回类型标注：int 运算结果原样返回）
func getBuffAccuracyMod():
	return (getLucky() - getBlind()) * 5


# ─────────────────────────── 每帧驱动 ───────────────────────────

# 对齐 Character.gd:1029-1035：眩晕倒计时递减 + 体力再生
func physicsTick(delta: float) -> void :
	if isStunned():
		stunnedDuration -= delta
		if stunnedDuration <= 0.0:
			stunnedDuration = 0.0
			endStun()
	
	addStamina(staminaRegen * delta)


# Buff 临时栈超时（对齐 Godot Timer 的物理步进）
func tickBuffs(delta: float) -> void :
	for buffType in buffs:
		buffs[buffType]._tick(delta)
