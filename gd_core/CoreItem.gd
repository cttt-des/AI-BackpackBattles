# =============================================================================
# CoreItem.gd — 无头战斗内核：物品（战斗部分）
# =============================================================================
# 对齐源码：Items/Item.gd（全文 6573 行）
#
# 本类只承载**战斗判定所需**的那一部分；原版把物理刚体(RigidBody2D)、拖拽/旋转、
# 悬停/聚焦、tooltip、影子、粒子、shader 冷却环、背包几何、制作系统全部塞在同一个
# 类里（6573 行 / 战斗函数仅 351 行），本类把它们整体剥离：
#
#   保留（逐字对齐的判定路径）
#     prepare / preCombatStart / combatStart / postCombatStart / repeatCombatStart / combatEnd
#     每物理帧冷却推进（原 _physics_process:4453-4458）
#     trigger / doCooldownEffect / activate / checkTriggerCount
#     冷却取值族：hasCooldown / getSpeed / getStackSpeedMods / getCooldown /
#       getBaseCooldown / getBaseCooldownIndex / getModifiedCooldown / adjustCooldown /
#       setBaseCooldown / resetBaseCooldown / updateBaseCooldown
#     冷却推进族：advanceCooldownPercent / advanceCooldownSeconds
#     伤害取值族：getBaseMinDamage / getBaseMaxDamage / getMinDamage / getMaxDamage /
#       getTypedDamageFactor / randDamage / getModifiedEffectDamage
#     概率族：getBaseChance / applyBonusChance / getChance / getChance2 / rollChance /
#       rollChance2 / rollDoubleAttackEffect
#     暴击族：getCritChancePercent / addCritChancePercent / getCritTokens /
#       useCritToken / getCritSeverity / rollDoubleAttackEffect
#     参数族：getP / getP_m / getParamModified / modifyParam / modifyParam_add
#     栈族：giveStacks / giveStacksTemporary / stackChanged / giveBlock / loseBlock /
#       stealStack / 各 give/lose/use 包装
#     派发：dealDamage / dealEffectDamage / preDealDamage_early / preDealDamage_late
#       （这三个方法体本身在 4150 行附近、只有 EventBus 派发，属通用逻辑）
#
#   剥离（全部走 ctx.hooks，见 CoreHooks.gd 顶部说明）
#     动画 / 音效 / z_index / 影子 / 粒子 / tween / shader / tooltip
#     拖拽、旋转、鼠标、聚焦、背包预览、制作
#
#   本期未实现、以同签名接缝占位（见 docs/gd_core_truth.md 第 5 节）
#     网格邻接与受影响格（getAffectedItems 等）→ `_grid` 注入点
#     宝石（Gems/Gem.gd 三模式）→ `gems` 数组 + getGemsNoNull
#     电荷（Engineer 逐格传播）→ `numCharges` 保留，传播逻辑待接
#     Items/*.gd 的 518 个物品行为 → `_behavior_call` 派发缝
# =============================================================================
extends Reference
class_name CoreItem


const BASE_CRIT_SEVERITY := 2.0
const cdEncodingFactor := 100000.0

# 对齐 Item.gd:241-252
enum Stat{
	MinDamage, 
	MaxDamage, 
	StaminaCost, 
	Speed, 
	BaseCooldown, 
	Accuracy, 
	CritChance, 
	Chance, 
	Chance2, 
	Cooldown
}


var descriptor: CoreItemData
var ctx
var character_                  # CoreCharacter（原 `character()`，注意 `character` 是方法名）
var inventory                   # 本期置 null；仅用于 placed 语义
var placed := false
var name: String = ""

# 伤害与速度修正（对齐 Item.gd:474-495）
var speedScale: float = 0.0
var bonusMaxDam: float = 0.0
var bonusMinDam: float = 0.0
var removableDam: float = 0.0
var bonusDamageFactor: float = 1.0
var staminaFactor: float = 1.0
var critChancePercent: float = 0.0
var critTokens: int = 0
var critSeverity: float = BASE_CRIT_SEVERITY
var bonusChancePercent_mult: float = 0.0
var bonusChancePercent_additive1: float = 0.0
var bonusChancePercent_additive2: float = 0.0
var bonusAccuracy: float = 0.0
var buffPowers: Dictionary = {}
var buffAmplificationChances: Dictionary = {}
var damageSource = null
var doubleActivationChance: float = 0.0
var doubleAttackEffectChance: float = 0.0
var paramMult: Dictionary = {}
var paramAdd: Dictionary = {}
var numCharges: int = 0

var baseCooldownOverride: float = 0.0
var chanceRng                 # CoreRng.BalancedRng
var damageRangeRng            # CoreRng.BalancedRange

# 对齐 Item.gd:288 —— 仅由战斗日志回放路径写入（CombatLog.gd:600/612 的 setStat），
# 实战判定中恒为 null；保留字段与读取点以维持接口一致。
var statDisplayOverrides: Array = []

# 冷却运行态（对齐 Item.gd:464-470）
var lastActivationTime: float = 0.0
var activationsThisFrame: int = 0
var lastTriggerTime: float = 0.0
var triggersThisFrame: int = 0
var triggerTime: float = 0.0
var iterationCooldown: float = 0.0

# 统计（对齐 Item.gd:257 itemMetrics）
var itemMetrics: Array = []

# 本期占位接缝
var gems: Array = []
var _grid = null
var _behavior = null
var _cooldown_active := false


# 物品行为接缝（_behavior）接口约定 —— 由装配方实现，内核只做派发：
#   hasBehavior(item, methodName: String) -> bool
#   callBehavior(item, methodName: String, args: Array)
# 命名刻意避开 Object 原生的 has_method / call（原生签名不同，覆写会破坏引擎内部调用）。
# 方法名与 Items/*.gd 中的 GDScript 方法名一一对应（doCooldownEffect / onPrepare /
# connectForCombat / onCombatStart / preDealDamage_early ...）。
var consumed := false

# 行为钩子存在性探测（对齐 Item.gd:500-504 onready 的 has_method 结果）
var hasPreDealDamageEarlyEffect := false
var hasPreDealDamageLateEffect := false
var hasDealtDamageEffect := false
var hasOnChargeReceivedEffect := false
var hasOnChargeLeftEffect := false


func _init(_ctx, _descriptor: CoreItemData, _character = null) -> void :
	ctx = _ctx
	descriptor = _descriptor
	character_ = _character
	name = _descriptor.name
	chanceRng = ctx.rng.BalancedRng.new(ctx.rng)
	damageRangeRng = ctx.rng.BalancedRange.new(ctx.rng)
	baseCooldownOverride = _descriptor.cd
	for buff in CoreConst.getStacks():
		buffPowers[buff] = 1.0
		buffAmplificationChances[buff] = 0.0
	itemMetrics.resize(getNumItemMetrics())
	itemMetrics.fill(0)
	statDisplayOverrides.resize(Stat.size())
	statDisplayOverrides.fill(null)


# ─────────────────────── 关系访问（对齐 Item.gd:3939-3950） ───────────────────────

func hasCharacter() -> bool:
	return placed and character_ != null


func character():
	return character_


func opponent():
	return ctx.otherCharacter(character_)


func isPlaced() -> bool:
	return placed


# 类型标记：替代 `origin is CoreItem` 这种需要 class_name 的判定，
# 供 CoreDamageSource / CoreDamageResult 等做零依赖鸭子类型判断
# （GDScript 3 不允许 class_name 脚本互相循环引用）。
func isCoreItem() -> bool:
	return true


func isPlayer() -> bool:
	return character_ != null and character_.playerId == CoreConst.CharID.PLAYER


# ─────────────────────── 类型 / 标签（对齐 3594-3601, 5370-5390） ───────────────────────

func hasType(type: int) -> bool:
	return type in descriptor.types


func getTypeMultiplicity(type: int) -> int:
	return 1 if hasType(type) else 0


func hasTag(tag) -> bool:
	return descriptor.hasTag(tag)


func isWeapon() -> bool:
	return descriptor.isWeapon()


func isBag() -> bool:
	return false


func isGem() -> bool:
	return false


func isBattleRageItem() -> bool:
	return false


func gainsStack(stackType) -> bool:
	return descriptor.gainedStacks & stackType


func removesStack(stackType) -> bool:
	return descriptor.removedStacks & stackType


func usesStack(stackType) -> bool:
	return descriptor.usedStacks & stackType


func getTriggerPriority() -> int:
	return CoreConst.Priority.Normal


func canDamage() -> bool:
	return getBaseMinDamage() > 0 or hasTag(CoreConst.Tag.Lifesteal)


func canBeEmpowered() -> bool:
	return isWeapon() and canDamage()


func canActivate() -> bool:
	return descriptor.canActivate


# ─────────────────────── 冷却（对齐 3742-3812, 4438-4451） ───────────────────────

func getSpeed() -> float:
	if hasCharacter():
		var speed_ = speed() + getStackSpeedMods()
		var modifiedSpeed: float
		if speed_ >= 0:
			modifiedSpeed = 1.0 + speed_
		else:
			modifiedSpeed = 1.0 / (1.0 - speed_)
		
		modifiedSpeed = clamp(modifiedSpeed, 0.1, 10.0)
		return modifiedSpeed
	else:
		return 1.0


func speed() -> float:
	return speedScale


func getStackSpeedMods() -> float:
	return (character().getHeat() - character().getCold()) * 0.02


func hasCooldown() -> bool:
	return descriptor.cd != 0


func isCooldownActive() -> bool:
	return _cooldown_active


func setCooldownActive(active: bool) -> void :
	_cooldown_active = active


func activateCooldown() -> void :
	_cooldown_active = true


func deactivateCooldown() -> void :
	_cooldown_active = false


func getBaseCooldown() -> float:
	return baseCooldownOverride


func getBaseCooldownIndex(index: int) -> float:
	if index == 0:
		return descriptor.cd
	else:
		return descriptor.extraCds[index - 1]


# 对齐 Items/Item.gd:3782-3786（含 statDisplayOverrides[Stat.BaseCooldown] 覆盖分支）
func getCooldown() -> float:
	var override = statDisplayOverrides[Stat.BaseCooldown]
	if override: return override
	
	return baseCooldownOverride


func getCooldownIndex(index: int) -> float:
	return getBaseCooldownIndex(index)


func getModifiedCooldown() -> float:
	return getCooldown() / getSpeed()


func getModifiedCooldownIndex(index: int):
	return getCooldownIndex(index) / getSpeed()


func getCooldownEncoded():
	if iterationCooldown == 0:
		return - 1
	var relProgress = 1.0 - triggerTime / iterationCooldown
	var progressPerSecond: float
	if isCooldownActive():
		progressPerSecond = getSpeed() / iterationCooldown
	else:
		progressPerSecond = 0
	var value = int(relProgress * cdEncodingFactor) << 32
	value += int(progressPerSecond * cdEncodingFactor)
	return value


func adjustCooldown():
	var adjustedCooldown = getCooldown()
	if character_ != null and character_.playerId == CoreConst.CharID.OPPONENT and \
		(ctx.below_master or ctx.lobbies_mode):
		adjustedCooldown *= ctx.rng.randf_range(0.975, 1.05)
	else:
		adjustedCooldown *= ctx.rng.randf_range(0.95, 1.05)
	
	return adjustedCooldown


func setBaseCooldown(newBaseCd):
	baseCooldownOverride = newBaseCd
	updateBaseCooldown()


func resetBaseCooldown():
	setBaseCooldown(descriptor.cd)


func updateBaseCooldown():
	var cdProgress = triggerTime / iterationCooldown
	iterationCooldown = adjustCooldown()
	triggerTime = cdProgress * iterationCooldown
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.Cooldown)
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.BaseCooldown)


# ─────────────────────── 战斗生命周期（对齐 3356-3440） ───────────────────────

# ─────────────────────── 体力消耗（对齐 Item.gd:3972-3980, 4213-4227） ───────────────────────

func getBaseStaminaCost() -> float:
	return descriptor.staminaCost


func getStaminaCost() -> float:
	# 对齐 Item.gd:3975-3979 —— 原版先查 statDisplayOverrides[Stat.StaminaCost]，
	# 该数组仅由战斗日志回放路径写入（CombatLog.gd:600/612），实战恒为 null，
	# 故此处保留读取点但不改变判定（Greatsword.gd:15 覆写本函数时同样读取该数组）。
	var override = statDisplayOverrides[Stat.StaminaCost]
	if override:
		return override
	return getBaseStaminaCost() * staminaFactor


func isStaminaModified() -> int:
	return isStatModified(getBaseStaminaCost() - getStaminaCost())


func isStatModified(statVal) -> int:
	if statVal == 0:
		return CoreConst.StatModified.No
	elif statVal > 0:
		return CoreConst.StatModified.Positive
	else:
		return CoreConst.StatModified.Negative


func setStat(stat, value) -> void :
	statDisplayOverrides[stat] = value
	ctx.hooks.queueTooltipUpdate(self)


# 对齐 Item.gd:4213-4224
func useStamina(amount = null):
	if amount == null:
		amount = getStaminaCost()
	var res = character().useStamina(amount)
	if res == CoreConst.StaminaResult.Insufficient:
		addMetric(CoreConst.ItemMetrics.OutOfStamina, 1, null, true)
		var event = ctx.combat_log.createEvent_OutOfStamina(self, character().playerId)
		ctx.bus.logEvent(event)
		ctx.combat_log.snapshotItemTooltipStat(self, Stat.Cooldown)
		playOutOfStaminaAnimation()
	else:
		ctx.bus.emitSignal(self, "used_stamina", [amount])
		staminaChanged(amount, CoreConst.StackChangeType.Used_Player, true)
	return res


# 对齐 Item.gd:4226-4227
func drainStamina(amount, triggerEvent = null):
	return opponent().drainStamina(amount, self, triggerEvent)


# 对齐 Item.gd:4202-4211：动画/音效/飘字全部走钩子；
# `Game.numTimesOutOfStamina += 1` 仅在玩家侧物品触发时计数（ownerType == PlayerInventory）。
func playOutOfStaminaAnimation() -> void :
	if isPlayer():
		ctx.out_of_stamina_count += 1
	ctx.hooks.playOutOfStaminaAnimation(self)


func cacheAffectedItemsForCombat():
	# 受影响格缓存属网格层（本期接缝）；保留调用点以维持生命周期顺序
	if _grid != null:
		_grid.cacheAffectedItemsForCombat(self)


func prepare():
	cacheAffectedItemsForCombat()
	
	chanceRng.reset()
	damageRangeRng.reset()
	for gem in getGemsNoNull():
		gem.prepare()
	onPrepare()


func onPrepare():
	pass


func preCombatStart():
	for gem in getGemsNoNull():
		gem.preCombatStart()
	
	if hasCooldown():
		iterationCooldown = adjustCooldown()
		triggerTime = iterationCooldown
		activateCooldown()
		ctx.combat_log.snapshotItemTooltipStat(self, Stat.Cooldown)
	
	onPreCombatStart()


func onPreCombatStart():
	pass


func hasStartofBattle() -> bool:
	return _hasBehaviorMethod("onCombatStart")


func combatStart():
	for gem in getGemsNoNull():
		gem.combatStart()
	
	if hasStartofBattle():
		_behavior_call("onCombatStart")


func postCombatStart():
	for gem in getGemsNoNull():
		gem.postCombatStart()
	
	onPostCombatStart()


func onPostCombatStart():
	pass


func repeatCombatStart():
	onPreCombatStart()
	_behavior_call("onCombatStart")
	onPostCombatStart()


func combatEnd():
	setCooldownActive(false)
	disconnectCombat()
	for gem in getGemsNoNull():
		gem.combatEnd()
	onCombatEnd()


func onCombatEnd():
	pass


# 对齐 Item.gd:3448-3480+ shopEntered 的战斗态清零
func resetCombatState():
	baseCooldownOverride = descriptor.cd
	speedScale = 0.0
	bonusMinDam = 0
	bonusMaxDam = 0
	removableDam = 0
	bonusDamageFactor = 1.0
	staminaFactor = 1.0
	for buff in buffPowers:
		buffPowers[buff] = 1.0
		buffAmplificationChances[buff] = 0.0
	
	critChancePercent = 0.0
	critTokens = 0
	critSeverity = BASE_CRIT_SEVERITY
	bonusChancePercent_mult = 0.0
	bonusChancePercent_additive1 = 0.0
	bonusChancePercent_additive2 = 0.0
	bonusAccuracy = 0.0
	doubleActivationChance = 0.0
	doubleAttackEffectChance = 0.0
	paramMult.clear()
	paramAdd.clear()
	numCharges = 0
	statDisplayOverrides.fill(null)
	itemMetrics.fill(0)
	consumed = false
	lastActivationTime = 0.0
	activationsThisFrame = 0
	triggersThisFrame = 0
	lastTriggerTime = 0.0
	triggerTime = 0.0
	iterationCooldown = 0.0
	_cooldown_active = false


# ─────────────────────── 每物理帧（对齐 Item.gd:4453-4458） ───────────────────────

func physicsTick(delta: float) -> void :
	if not _cooldown_active:
		return
	if not character().isStunned():
		triggerTime -= delta * getSpeed()
		ctx.hooks.showCooldown(self, 1.0 - (triggerTime / iterationCooldown))
		if triggerTime <= 0:
			trigger()


# ─────────────────────── 触发（对齐 4416-4451） ───────────────────────

func checkTriggerCount(limit: int) -> bool:
	if ctx.time > triggersThisFrame:
		triggersThisFrame = 1
		lastTriggerTime = ctx.time
	else:
		triggersThisFrame += 1
		if triggersThisFrame > limit:
			return false
	return true


func trigger():
	iterationCooldown = adjustCooldown()
	triggerTime += iterationCooldown
	
	doCooldownEffect()
	
	if doubleActivationChance > 0 and ctx.rng.flip(doubleActivationChance):
		doCooldownEffect()


# 物品行为覆写点（Items/*.gd 里绝大多数 doCooldownEffect 来自子类脚本）
func doCooldownEffect():
	_behavior_call("doCooldownEffect")


func onAfterEffectFinished():
	deactivateCooldown()
	consumed = true


# ─────────────────────── 冷却推进（对齐 4486-4509） ───────────────────────

func advanceCooldownPercent(amount):
	if not isCooldownActive(): return
	
	var reduction = amount / 100.0 * iterationCooldown
	triggerTime -= reduction
	
	while triggerTime <= 0:
		trigger()
		if not isCooldownActive(): return
	
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.Cooldown)


func advanceCooldownSeconds(amount):
	if not isCooldownActive(): return
	
	triggerTime -= amount * getSpeed()
	
	while triggerTime <= 0:
		trigger()
		if not isCooldownActive(): return
	
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.Cooldown)


# ─────────────────────── 激活（对齐 4686-4737） ───────────────────────

func activate(damageRes = null, playCombatAni = true, consume = false, 
	animationOverride = null):
	
	# 对齐 Item.gd:4689-4702 —— 原版前两行 `if dragged: return` /
	# `if Util.isTweenRunning(movebackTween): return` 为纯 UI 拖拽与 tween 判定，
	# 无头下恒为 false（dragged 恒 false、无 tween），故整体删除，判定等价。
	if not checkActivationLimit():
		return null
	
	var event = null
	
	if not ctx.fight_ended:
		if not isBag():
			event = ctx.combat_log.createEvent_Activation(self)
			ctx.bus.emitEvent(self, "activated", event, [event])
			addMetric(CoreConst.ItemMetrics.Activations)
		if hasCooldown():
			ctx.combat_log.snapshotItemTooltipStat(self, Stat.Cooldown, null, 
				false, event)
	
	if animationOverride != null:
		ctx.hooks.playActivationAnimation(self, animationOverride, consume)
	ctx.hooks.playActivationSound(self)
	
	return event


func checkActivationLimit() -> bool:
	if ctx.time > lastActivationTime:
		activationsThisFrame = 1
		lastActivationTime = ctx.time
	else:
		activationsThisFrame += 1
		if activationsThisFrame > 3: return false
	return true


# ─────────────────────── 伤害取值（对齐 3647-3719） ───────────────────────

func getBaseMinDamage() -> int:
	return descriptor.minDam


func getBaseMaxDamage() -> int:
	return descriptor.maxDam


func getBaseAverageDamage() -> float:
	return (getBaseMinDamage() + getBaseMaxDamage()) / 2.0


func getTypedDamageFactor(damSource) -> float:
	var typedDmgFactor = 1.0
	for type in damSource.types:
		typedDmgFactor += character().typedDamageFactors[type]
	
	return typedDmgFactor


# 对齐 Items/Item.gd:3676-3690（含 statDisplayOverrides[Stat.MinDamage] 覆盖分支）
func getMinDamage(damSource = damageSource) -> int:
	var override = statDisplayOverrides[Stat.MinDamage]
	if override: return override
	
	var minDam = ceil(descriptor.minDam + bonusMinDam)
	if hasCharacter():
		if canBeEmpowered():
			minDam = minDam + character().getBuffDamageMod()
		
		minDam *= getTypedDamageFactor(damSource)
	
	minDam = round(minDam * bonusDamageFactor)
	minDam = max(minDam, 0)
	
	return minDam


# 对齐 Items/Item.gd:3693-3707（含 statDisplayOverrides[Stat.MaxDamage] 覆盖分支）
func getMaxDamage(damSource = damageSource) -> int:
	var override = statDisplayOverrides[Stat.MaxDamage]
	if override: return override
	
	var maxDam = ceil(descriptor.maxDam + bonusMaxDam)
	if hasCharacter():
		if canBeEmpowered():
			maxDam = maxDam + character().getBuffDamageMod()
		
		maxDam *= getTypedDamageFactor(damSource)
	
	maxDam = round(maxDam * bonusDamageFactor)
	maxDam = max(maxDam, 0)
	
	return maxDam


func getAverageDamage() -> float:
	return (getMinDamage() + getMaxDamage()) / 2.0


func randDamage() -> int:
	return ctx.rng.randi_range(getMinDamage(), getMaxDamage())


# 对齐 Items/Item.gd:5130-5134（原版无返回类型标注：float 原样透传）
func getModifiedEffectDamage(baseDamage):
	var modifiedDamage = baseDamage
	modifiedDamage *= (1.0 + character().typedDamageFactors[CoreDamageSource.Type.Effect])
	modifiedDamage *= bonusDamageFactor
	return modifiedDamage


func addBonusDamage(damage, removable: bool = true):
	if removable:
		removableDam += damage
	bonusMinDam += damage
	bonusMaxDam += damage


func changeVaryingDamage(damage):
	removableDam += damage


func addMinDamage(damage):
	bonusMinDam += damage


func addMaxDamage(damage):
	bonusMaxDam += damage


func getRemovableDamage() -> float:
	return removableDam


func removeBonusDamage():
	bonusMinDam -= removableDam
	bonusMaxDam -= removableDam
	removableDam = 0


func setBonusDamageFactor(factor):
	bonusDamageFactor = factor


# ─────────────────────── 概率（对齐 3849-3883, 4407-4414） ───────────────────────

func getBaseChance() -> float:
	return descriptor.chance


func getBaseChance2() -> float:
	return descriptor.chance2


func applyBonusChance(toChance, index) -> float:
	if index == 1:
		return (toChance + bonusChancePercent_additive1) * ((100 + bonusChancePercent_mult) / 100.0)
	else:
		return (toChance + bonusChancePercent_additive2) * ((100 + bonusChancePercent_mult) / 100.0)


# 对齐 Items/Item.gd:3867-3870
func getChance() -> float:
	var override = statDisplayOverrides[Stat.Chance]
	if override: return override
	
	return clamp(applyBonusChance(getBaseChance(), 1), 0, 100)


# 对齐 Items/Item.gd:3873-3876
func getChance2() -> float:
	var override = statDisplayOverrides[Stat.Chance2]
	if override: return override
	
	return clamp(applyBonusChance(getBaseChance2(), 2), 0, 100)


func rollChance(chance = null) -> bool:
	if chance == null:
		chance = getBaseChance()
	return chanceRng.rollPercent(applyBonusChance(chance, 1))


func rollChance2() -> bool:
	return chanceRng.rollPercent(applyBonusChance(descriptor.chance2, 2))


func addBonusChance(amount):
	bonusChancePercent_mult += amount
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.Chance)
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.Chance2)


func addBonusChance_additive(amount1, amount2 = null):
	bonusChancePercent_additive1 += amount1
	
	if amount2 == null:
		bonusChancePercent_additive2 += amount1
	else:
		bonusChancePercent_additive2 += amount2
	
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.Chance)
	
	if amount2 != 0:
		ctx.combat_log.snapshotItemTooltipStat(self, Stat.Chance2)


func addAccuracy(amount):
	bonusAccuracy += amount


# ─────────────────────── 暴击（对齐 3995-4027, 4128-4129） ───────────────────────

func getCritChancePercent() -> float:
	return clamp(critChancePercent, 0, 100)


func addCritChancePercent(amount):
	critChancePercent += amount
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.CritChance)


func reduceCritChancePercent(amount):
	critChancePercent -= amount
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.CritChance)


func changeCritChancePercent(amount):
	critChancePercent += amount
	ctx.combat_log.snapshotItemTooltipStat(self, Stat.CritChance)


func getCritTokens() -> int:
	return critTokens


func addCritTokens(amount):
	critTokens += amount


func useCritToken():
	critTokens -= 1


func addCritSeverity(amount):
	critSeverity += amount


func getCritSeverity() -> float:
	return critSeverity


func rollDoubleAttackEffect() -> int:
	return int(ctx.rng.flip(doubleAttackEffectChance))


# ─────────────────────── 参数（对齐 3885-3937） ───────────────────────

func getP(index) -> float:
	return descriptor.getP(index)


func getP_m(paramName: String) -> float:
	var baseVal = getP(paramName)
	return getParamModified(paramName, baseVal)


func getParamModified(paramName: String, baseVal) -> float:
	var baseParam = descriptor.paramBases[paramName]
	return (baseVal + paramAdd.get(baseParam, 0)) * paramMult.get(baseParam, 1.0)


func modifyParam(paramName: String, amount: float):
	paramMult[paramName] = paramMult.get(paramName, 1.0) + amount


func modifyParam_add(paramName: String, amount: float):
	paramAdd[paramName] = paramAdd.get(paramName, 0.0) + amount


# ─────────────────────── 命中/速度取值（对齐 3814-3825） ───────────────────────

func getBaseAccuracy() -> float:
	return descriptor.accuracy


func getAccuracy() -> float:
	var acc = getBaseAccuracy()
	acc += bonusAccuracy
	if hasCharacter():
		acc += character().getBuffAccuracyMod()
	return acc


# ─────────────────────── 栈操作（对齐 4889-5035） ───────────────────────

func getAmplificationChancePercent(buffType):
	return buffAmplificationChances[buffType]


func changeAmplificiationChancePercent(buffType, chance):
	buffAmplificationChances[buffType] += chance


func changeAmplificiationChancePercent_allBuffs(chance):
	for buff in CoreConst.getBuffs():
		changeAmplificiationChancePercent(buff, chance)


func changeAmplificiationChancePercent_allDebuffs(chance):
	for buff in CoreConst.getDebuffs():
		changeAmplificiationChancePercent(buff, chance)


func changeNullifyChancePercent(buffType, chance):
	buffAmplificationChances[buffType] -= chance


func giveReflectStacks(amount):
	character().changeDebuffReflectStacks(amount)


func giveStacks(target, type: int, amount, triggerEvent = null):
	if amount > 0:
		return target.gainStacks(type, round(amount * buffPowers[type]), self, triggerEvent)
	return null


func giveStacksTemporary(target, type: int, amount, duration, triggerEvent = null):
	if amount > 0:
		return target.gainStacksTemporary(type, round(amount * buffPowers[type]), duration, self, triggerEvent)
	return null


func giveBlock(amount = null, canTriggerEffects = true, triggerEvent = null):
	if amount == null:
		amount = getBlock()
	if amount > 0:
		var event = giveStacks(character(), CoreConst.EventType.Block, amount, triggerEvent)
		if event != null:
			if canTriggerEffects:
				ctx.bus.emitSignal(self, "gave_block", [event.getAmount(), event])
			else:
				ctx.bus.logEvent(event)
			return event
	return null


func getBlock() -> int:
	# 对齐 Item.gd:3969-3970 —— 物品自带的 block 值（盾牌等），非角色当前格挡层数
	return descriptor.block


func removeBlock(amount, triggerEvent = null):
	var event = opponent().loseBlock(amount, self, triggerEvent)
	if event:
		countDamage( - event.getAmount())


func loseBlock(amount, triggerEvent = null):
	character().loseBlock(amount, self, triggerEvent)


func useBlock(amount, triggerEvent = null):
	return character().useStacks(CoreConst.EventType.Block, amount, self, triggerEvent)


func stealStack(type: int, amount, triggerEvent = null):
	var removeEvent = opponent().loseStacks(type, amount, self, triggerEvent)
	var giveEvent = giveStacks(character(), type, amount, removeEvent)
	return giveEvent


func giveSpikes(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Spikes, amount, triggerEvent)


func giveVampirism(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Vampirism, amount, triggerEvent)


func inflictPoison(amount, triggerEvent = null):
	return giveStacks(opponent(), CoreConst.EventType.Poison, amount, triggerEvent)


func selfInflictPoison(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Poison, amount, triggerEvent)


func inflictBlind(amount, triggerEvent = null):
	return giveStacks(opponent(), CoreConst.EventType.Blind, amount, triggerEvent)


func giveRegeneration(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Regeneration, amount, triggerEvent)


func giveLucky(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Lucky, amount, triggerEvent)


func giveMana(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Mana, amount, triggerEvent)


func giveEmpower(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Empower, amount, triggerEvent)


func giveHeat(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Heat, amount, triggerEvent)


func giveCold(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Cold, amount, triggerEvent)


# ─────────────────────── 派发（对齐 4150-4180, 4132-4141） ───────────────────────

func dealDamage(triggerEvent = null):
	damageSource.updateItem(self)
	var damageRes = character().dealDamage(damageSource, triggerEvent)
	ctx.bus.emitSignal(self, "attacked", [damageRes])
	return damageRes


func dealEffectDamage(damage, triggerEvent = null, _damageSource = null):
	if _damageSource == null:
		_damageSource = damageSource
	_damageSource.updateEffect(self, damage)
	var damageRes = opponent().takeDamage(_damageSource, triggerEvent)
	return damageRes


func preDealDamage_early(damageRes):
	ctx.bus.emitSignal(self, "pre_deal_damage_early", [damageRes])


func preDealDamage_late(damageRes):
	ctx.bus.emitSignal(self, "pre_deal_damage_late", [damageRes])


func dealtDamage(damageRes):
	ctx.bus.emitSignal(self, "dealt_damage", [damageRes])


func countDamage(amount):
	addMetric(CoreConst.ItemMetrics.Damage, amount)


# ─────────────────────── 统计（对齐 715-724, 4909-4934） ───────────────────────

static func getNumNonStackItemMetrics() -> int:
	return (CoreConst.ItemMetrics.Stamina + 
			(CoreConst.ItemMetrics.Block - CoreConst.ItemMetrics.Stamina) * CoreConst.StackChangeType.size())


static func getNumItemMetrics() -> int:
	return (CoreConst.ItemMetrics.Stamina + 
			(CoreConst.ItemMetrics.size() - CoreConst.ItemMetrics.Stamina) * CoreConst.StackChangeType.size())


static func getStackMetricIndex(stackChangeType: int, stackType: int) -> int:
	var offsetStackType = stackType - CoreConst.EventType.Block
	var changeTypeOffset = stackChangeType * CoreConst.numStackTypes()
	return getNumNonStackItemMetrics() + changeTypeOffset + offsetStackType


static func getMultiMetricIndex(stackChangeType: int, metric: int) -> int:
	var offsetMetric = metric - CoreConst.ItemMetrics.Stamina
	var numMultiMetrics = offsetMetric * CoreConst.StackChangeType.size()
	return CoreConst.ItemMetrics.Stamina + numMultiMetrics + stackChangeType


# 对齐 Item.gd:4186-4188（amount 默认 1；并把指标快照交给钩子）
func addMetric(metricsIndex, amount = 1, playerId = null, withNextEvent = false):
	itemMetrics[metricsIndex] += amount
	ctx.hooks.snapshotItemMetric(self, metricsIndex, playerId, withNextEvent)


func getMetric(metric):
	return itemMetrics[metric]


func stackChanged(stackType: int, amount: int, onPlayer: bool, used: bool = false):
	var changeType: int
	if amount > 0:
		changeType = CoreConst.StackChangeType.Added_Player
	else:
		if used:
			changeType = CoreConst.StackChangeType.Used_Player
		else:
			changeType = CoreConst.StackChangeType.Removed_Player
	
	if not onPlayer:
		changeType += 1
	
	var index = getStackMetricIndex(changeType, stackType)
	var playerId = 0 if onPlayer else 1
	addMetric(index, abs(amount), playerId, true)


func staminaChanged(amount: float, changeType: int, withNextEvent: bool = false):
	var index = getMultiMetricIndex(changeType, CoreConst.ItemMetrics.Stamina)
	addMetric(index, amount, character().playerId, withNextEvent)


# ─────────────────────── 宝石 / 网格 / 行为 接缝 ───────────────────────

func getGemsNoNull() -> Array:
	var out = []
	for gem in gems:
		if gem != null:
			out.push_back(gem)
	return out


func getGems() -> Array:
	return gems


# 装配层接缝：原版由各子类脚本在 `_ready()` 里建伤害源
# （Items/Weapon.gd:4-5 `damageSource = DamageSource.new().setItem(self)`）。
# 物品行为未移植前，由装配方调用本工厂得到等价对象；行为移植后可直接复写。
func buildDamageSource(_type = null):
	damageSource = CoreDamageSource.new()
	damageSource._rng = ctx.rng
	damageSource.setItem(self, _type)
	return damageSource


func connectForCombat():
	onConnectForCombat()


func disconnectCombat():
	# 原版 EventBus 的定向连接在战斗收尾由 disconnectAll() 整体清空，
	# 这里保留调用点以维持生命周期顺序（见 CoreCombat._finishCombat）
	onDisconnectCombat()


func onConnectForCombat():
	_behavior_call("connectForCombat")


func onDisconnectCombat():
	_behavior_call("disconnectCombat")


func _hasBehaviorMethod(methodName: String) -> bool:
	if _behavior == null:
		return false
	return _behavior.hasBehavior(self, methodName)


func _behavior_call(methodName: String, args: Array = []):
	if _behavior != null:
		_behavior.callBehavior(self, methodName, args)
