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

# 里程碑 1 新增字段（对齐 Item.gd:372/385/468）
var dynamicTypes: Dictionary = {}       # 动态类型记账（addDynamicType/removeDynamicType）
var combatConnections: Array = []       # connectForCombat_signal 建立的战斗连接
var ownerType: int = CoreConst.Owner.Undefined   # 由装配层按所属角色写入
var placedByPlayer := false            # 对齐 Item.gd:386 附近（addToInventory 写入）
var dragged := false                   # 对齐 Item.gd:390（拖拽态；战斗路径恒 false）

# 里程碑 1 新增字段：格子（对齐 Item.gd:387-433）
var occupiedCells: Array = []           # 该物品占用的库存格（装配层写入）
var collisionCells: Array = []          # 对齐 Item.gd:396
var extensionCells: Array = []          # 对齐 Item.gd:397（背包的扩展格）
var affectedExtensionCells: Array = []  # 对齐 Item.gd:398
var affectedCellsCache: Dictionary = {}     # 对齐 Item.gd:399
var currentAffectedItems: Dictionary = {}   # 对齐 Item.gd:432
var cachedAffectedItems: Dictionary = {}    # 对齐 Item.gd:433
# 装配层写入：联动颜色 → 库存空间的受影响格（源 = tscn CollisionMap 的 Affected tile，
# 经 simulator/extract_grid.py 同一套「40px tile //2 → 80px 背包格 + 锚点换算」得到）
var affectedTileCells: Dictionary = {}


# 物品行为接缝（_behavior）接口约定 —— 由装配方实现，内核只做派发：
#   hasBehavior(item, methodName: String) -> bool
#   callBehavior(item, methodName: String, args: Array) -> Variant
#     ★ 必须回传被调方法的原值；未实现的方法返回 null。返回值参与判定
#       （canAffect / getTriggerPriority / onCombatStart / getAffectedCellsAfterRotate_*
#       等），丢弃返回值不会报错但会静默改变战斗结果。
# 命名刻意避开 Object 原生的 has_method / call（原生签名不同，覆写会破坏引擎内部调用）。
# 方法名与 Items/*.gd 中的 GDScript 方法名一一对应（doCooldownEffect / onPrepare /
# connectForCombat / onCombatStart / preDealDamage_early ...）。
var consumed := false

# ── 行为接缝的两级派发 ──
# ① 装配方注入的 `_behavior`（合成测试用，见 gd_core_test/Smoke.gd / GridSmoke.gd）优先；
# ② 否则回落到**物品实例自身**的动态调用 —— 直挂形态下 `gd_core_items/X.gd`
#    就 `extends Item`，而原版这些调用本来就是打在物品自己身上的多态调用
#    （Item.gd:382 `var me = self` → :3400 `me.onCombatStart()`、
#      :5158 `me.onChargeReceived(charge)`、:503 `has_method("onChargeReceived")`）。
#
# ★ 为什么必须回落：早先只做 ①，而**没有任何物品脚本被注入 `_behavior`**
#   （全工程只有 Smoke/GridSmoke/Bench/Probe 这四个合成测试会设它），
#   于是 98 件物品的 onCombatStart、21 件的 onDealtDamage、11 件的 onChargeReceived
#   等回调**全部静默不执行，且零报错** —— 闸门 8/9 全绿也查不出来，因为它们只断言
#   「有激活」，而激活来自 doCooldownEffect 的多态调用（那条路不经过本接缝）。
#   实证：PiggyofRiches.onCombatStart 调 `inventory.countSocketedGems()`（内核无此
#   方法），闸门 9 逐一跑过它，却一条 SCRIPT ERROR 都没有。
#
# ★ 回落**只对下表中的名字**生效 —— 它们都是「基类未定义、只由物品脚本实现」的回调。
#   与基类同名的（canAffect / doCooldownEffect / getTriggerPriority /
#   getAffectedCellsAfterRotate_* / ready_deferred / reactToItemTypeChange …）是
#   虚方法覆写点：GDScript 多态已经打到物品脚本上，接缝再回落会变成**自我递归**
#   （CoreItem.doCooldownEffect 的整个函数体就是 `_behavior_call("doCooldownEffect")`）。
const SELF_BEHAVIOR_METHODS := [
	"onCombatStart",
	"getGatedDescriptor", "getReplaceDescriptor",
	"onChargeReceived", "onChargeLeft", "chargedItemStatChange",
	"onPreDealDamage_early", "onPreDealDamage_late", "onDealtDamage",
]

# 行为钩子存在性探测（对齐 Item.gd:500-504 的 `onready var ... = has_method(...)`；
# onready 在脚本绑定后求值，内核等价位置是 `_readyInit()`）
var hasPreDealDamageEarlyEffect := false
var hasPreDealDamageLateEffect := false
var hasDealtDamageEffect := false
var hasOnChargeReceivedEffect := false
var hasOnChargeLeftEffect := false


# ── 装配入口：无参构造 + 显式 setup（两段式） ──
# ★ 为什么必须支持两段式：GDScript 3.6 的 `GDScript.new()` **只接受 0 个实参**
#   （`Invalid call to function 'new' in base 'GDScript'. Expected 0 arguments.`），
#   而且 `extends "res://..."`（字符串路径继承）形态的脚本连 `_init` 的参数个数
#   都解析不到（`Too many arguments for "_init()" call. Expected at most 0.`）。
#   469 个物品脚本正是这两种形态，装配层只能 `SCRIPT.new()` → `setup(...)`。
#   `CoreItem.new(ctx, descriptor, character)` 依旧可用（class_name 引用能解析参数），
#   两条路最终都走同一个 setup，初始化结果完全一致。
func _init(_ctx = null, _descriptor = null, _character = null) -> void :
	if _descriptor == null:
		# 两段式构造的第一段：依赖留待 setup() 注入
		return
	setup(_ctx, _descriptor, _character)


# 与 `_init` 同一份初始化体（原 Item.gd 的构造期状态）。
# 返回 self 便于链式调用：`var it = SCRIPT.new().setup(ctx, data, chr)`
func setup(_ctx, _descriptor: CoreItemData, _character = null):
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
	statDisplayOverrides.resize(CoreConst.ItemStat.size())
	statDisplayOverrides.fill(null)
	# 对齐 Item.gd:602-603（_ready 里把每个颜色档初始化为空字典）
	for color in CoreConst.Affected.values():
		currentAffectedItems[color] = {}
	return self


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


# 对齐 Item.gd:5401-5402（Character.prepare 用它挑自动战怒物品；见 CoreItemData.hasBattleRageEffect）
func isBattleRageItem() -> bool:
	return descriptor.hasBattleRageEffect


func gainsStack(stackType) -> bool:
	return descriptor.gainedStacks & stackType


func removesStack(stackType) -> bool:
	return descriptor.removedStacks & stackType


func usesStack(stackType) -> bool:
	return descriptor.usedStacks & stackType


# 对齐 Item.gd:5272 附近（基类返回 Normal，由物品行为覆写为更高/更低优先级）
func getTriggerPriority() -> int:
	if _hasBehaviorMethod("getTriggerPriority"):
		return int(_behavior_call("getTriggerPriority", []))
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


# 对齐 Items/Item.gd:3782-3786（含 statDisplayOverrides[CoreConst.ItemStat.BaseCooldown] 覆盖分支）
func getCooldown() -> float:
	var override = statDisplayOverrides[CoreConst.ItemStat.BaseCooldown]
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
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown)
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.BaseCooldown)


# ─────────────────────── 战斗生命周期（对齐 3356-3440） ───────────────────────

# ─────────────────────── 体力消耗（对齐 Item.gd:3972-3980, 4213-4227） ───────────────────────

func getBaseStaminaCost() -> float:
	return descriptor.staminaCost


func getStaminaCost() -> float:
	# 对齐 Item.gd:3975-3979 —— 原版先查 statDisplayOverrides[CoreConst.ItemStat.StaminaCost]，
	# 该数组仅由战斗日志回放路径写入（CombatLog.gd:600/612），实战恒为 null，
	# 故此处保留读取点但不改变判定（Greatsword.gd:15 覆写本函数时同样读取该数组）。
	var override = statDisplayOverrides[CoreConst.ItemStat.StaminaCost]
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
		ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown)
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
	# 对齐 Item.gd:3356-3358 —— 开战前把「受影响物品集」定版。
	# 战斗期间物品不移动，故 getAffectedItems 之后恒读这份快照。
	for color in CoreConst.Affected.values():
		cachedAffectedItems[color] = currentAffectedItems[color].keys()


# 对齐 Item.gd:1319-1352（addToInventory）。剥离项：
#   · inventory.connect(...) —— 内核里由 CoreGrid.addItem 直接遍历 items 回调，等价于信号广播
#   · CraftingManager.itemAdded / makeGrabbable / 各类 Util.connectIfExists（制作与商店）
#   · emit_signal("added_to_inventory")（表现层）
func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	placedByPlayer = _placedByPlayer
	placed = true
	inventory = _inventory
	occupiedCells = _occupiedCells
	if ownerType != CoreConst.Owner.BuildViewer:
		# 原版对比 Game.PLAYER.INVENTORY / Game.OPPONENT.INVENTORY（两个 autoload 全局恒非空）。
		# 内核里双方由装配层 setup() 注入，未注入时保持原 ownerType（装配早期的正常情形）。
		if ctx.player != null and inventory == ctx.player.inventory:
			ownerType = CoreConst.Owner.PlayerInventory
		elif ctx.opponent != null and inventory == ctx.opponent.inventory:
			ownerType = CoreConst.Owner.Opponent
	
	cacheAffectedCells()
	
	for color in CoreConst.Affected.values():
		for item in getAffectedItems(color):
			currentAffectedItems[color][item] = true
			onAffectedItemAdded(item, color)
	
	onAddToInventory()


# 对齐 Item.gd:1330-1352（等价入口：物品已在网格中，只重建受影响集）
func registerWithInventory():
	addToInventory(inventory, occupiedCells, false)


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
		ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown)
	
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
	# 计时器推进（对齐物品 tscn 里 XxxTimer 的 TIMER_PROCESS_PHYSICS）。
	# ★ 必须放在冷却门之前：计时器承载 buff 时长（buffEnded 会撤掉 buff 效果），
	#   冷却未激活不代表计时器停摆。
	_tickTimers(delta)
	if not _cooldown_active:
		return
	if not character().isStunned():
		triggerTime -= delta * getSpeed()
		ctx.hooks.showCooldown(self, 1.0 - (triggerTime / iterationCooldown))
		if triggerTime <= 0:
			trigger()


# ─────────────────── 物品计时器（对齐 tscn 的 XxxTimer 子节点） ───────────────────
# 原版物品用场景树里的 Timer 子节点承载 buff 时长，由 tscn 的 [connection] 把
# `timeout` / `multi_timeout` 接到物品方法。内核无场景树，改为显式虚拟计时器：
# 物品脚本的 `_readyInit()` 里 `xxx = newItemTimer("XxxTimer", "方法名", 是否叠加)`。
# 同名重复调用会替换旧实例，使「同一批物品重入装配」不会累积计时器。
var timers: Array = []


func newItemTimer(timerName: String, method: String, isMulti: bool = false) -> CoreTimer:
	for existing in timers:
		if existing.name == timerName:
			existing.stop()
			timers.erase(existing)
			break
	var t = CoreTimer.new(ctx, self, timerName)
	t.multi = isMulti
	t.one_shot = true
	t.callback_method = method
	timers.push_back(t)
	return t


func getTimer(timerName: String):
	for t in timers:
		if t.name == timerName:
			return t
	return null


func _tickTimers(delta: float) -> void :
	for t in timers:
		t.tick(delta)


# 装配期一次性初始化（对齐 Node 的 `_ready` + `onready var` 求值时机）。
# 原版时机：物品入树后，onready 变量先赋值、随后调用 _ready()。
# 内核时机：装配层在「ctx / descriptor / inventory 都就位」之后调用一次。
# 子类覆写时开头写 `.()` 先跑父类（等价于原版 _ready 的隐式父类优先）。
func _readyInit() -> void :
	# 对齐 Item.gd:500-504 的 `onready var hasXxxEffect: = has_method("...")`。
	# ★ 必须在这里求值而不是在 setup() 里：原版 onready 在**脚本绑定之后**才跑，
	#   此时 has_method 已经能看到子类脚本定义的回调；`_readyInit()` 是内核里
	#   等价的生命周期点（装配层在 setup() 之后调用，且物品脚本覆写它时会先调
	#   `._readyInit()`，故本行先于物品自己的 onready 初始化执行，次序与原版一致）。
	# ★ 此前这 5 个标志**从未被赋值**（恒 false），叠加 _behavior_call 不回落的缺陷，
	#   使 onDealtDamage 一类的伤害钩子被两道闸门同时挡死、零报错。
	hasPreDealDamageEarlyEffect = has_method("onPreDealDamage_early")
	hasPreDealDamageLateEffect = has_method("onPreDealDamage_late")
	hasDealtDamageEffect = has_method("onDealtDamage")
	hasOnChargeReceivedEffect = has_method("onChargeReceived")
	hasOnChargeLeftEffect = has_method("onChargeLeft")

	# 对齐 Item.gd:547 —— 原版 `_ready` 在这同一段里调 initSockets()。
	# 折叠模型下它是空实现（后置条件恒真，见该函数处的论证），
	# 但调用点**照原版保留**：这样「物品准备好」这个生命周期点与源码逐条对得上，
	# 将来若折叠被拆开（例如某行为脚本开始用 `socket.getGem()`），这里有落点。
	initSockets()


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


# 对齐 Item.gd:5330-5334
# ★ 原版实现是 `deactivateCooldown(); showCooldownSmooth(0, true); if _consume: consume()`。
#   `_consume` 参数与 `consume()` 调用都是**判定**：
#     · `consume()` → `activate(damageRes, playCombatAni, true)`（走激活计数/触发链）
#                    + `consumed = true`
#     · 调用方会显式传 `false`（如 CogBadge `onAfterEffectFinished(false)`）表示不消耗
#   早期版本写成无参 + `consumed = true`，既丢了 `_consume` 分支（不该消耗的也消耗了），
#   也丢了 `activate()` 的触发链 —— 已按原版修正。
#   `showCooldownSmooth` 是纯表现（tween 着色器进度条），按内核约定走空钩子。
func onAfterEffectFinished(_consume = true):
	deactivateCooldown()
	ctx.hooks.showCooldownSmooth(self, 0, true)
	if _consume:
		consume()


# ─────────────────────── 冷却推进（对齐 4486-4509） ───────────────────────

func advanceCooldownPercent(amount):
	if not isCooldownActive(): return
	
	var reduction = amount / 100.0 * iterationCooldown
	triggerTime -= reduction
	
	while triggerTime <= 0:
		trigger()
		if not isCooldownActive(): return
	
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown)


func advanceCooldownSeconds(amount):
	if not isCooldownActive(): return
	
	triggerTime -= amount * getSpeed()
	
	while triggerTime <= 0:
		trigger()
		if not isCooldownActive(): return
	
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown)


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
			ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown, null, 
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


# 对齐 Items/Item.gd:3676-3690（含 statDisplayOverrides[CoreConst.ItemStat.MinDamage] 覆盖分支）
func getMinDamage(damSource = damageSource) -> int:
	var override = statDisplayOverrides[CoreConst.ItemStat.MinDamage]
	if override: return override
	
	var minDam = ceil(descriptor.minDam + bonusMinDam)
	if hasCharacter():
		if canBeEmpowered():
			minDam = minDam + character().getBuffDamageMod()
		
		minDam *= getTypedDamageFactor(damSource)
	
	minDam = round(minDam * bonusDamageFactor)
	minDam = max(minDam, 0)
	
	return minDam


# 对齐 Items/Item.gd:3693-3707（含 statDisplayOverrides[CoreConst.ItemStat.MaxDamage] 覆盖分支）
func getMaxDamage(damSource = damageSource) -> int:
	var override = statDisplayOverrides[CoreConst.ItemStat.MaxDamage]
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
	var override = statDisplayOverrides[CoreConst.ItemStat.Chance]
	if override: return override
	
	return clamp(applyBonusChance(getBaseChance(), 1), 0, 100)


# 对齐 Items/Item.gd:3873-3876
func getChance2() -> float:
	var override = statDisplayOverrides[CoreConst.ItemStat.Chance2]
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
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Chance)
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Chance2)


func addBonusChance_additive(amount1, amount2 = null):
	bonusChancePercent_additive1 += amount1
	
	if amount2 == null:
		bonusChancePercent_additive2 += amount1
	else:
		bonusChancePercent_additive2 += amount2
	
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Chance)
	
	if amount2 != 0:
		ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Chance2)


func addAccuracy(amount):
	bonusAccuracy += amount


# ─────────────────────── 暴击（对齐 3995-4027, 4128-4129） ───────────────────────

func getCritChancePercent() -> float:
	return clamp(critChancePercent, 0, 100)


func addCritChancePercent(amount):
	critChancePercent += amount
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.CritChance)


func reduceCritChancePercent(amount):
	critChancePercent -= amount
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.CritChance)


func changeCritChancePercent(amount):
	critChancePercent += amount
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.CritChance)


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


# =============================================================================
# 里程碑 1：物品行为 API 面
# =============================================================================
# 逐字移植 Items/Item.gd 中「物品行为脚本会调用、且参与战斗判定」的方法。
# 缺口清单与源码行号见 output/port/item_battle_dump.txt（176 项，含直接依赖闭包）。
# 剥离规则与文件头一致：视觉 / 音频 / UI / 制作 一律改走 ctx.hooks 或整体删除，
# 每处删除都在注释里写明原版行号与「为何不影响判定」。
# =============================================================================

# ─────────────────────── 类型 / 描述符查询（对齐 839-986, 3540-3640, 5739-5803） ───────────────────────

func getName() -> String:
	return descriptor.getName()


func getIndex() -> int:
	return descriptor.getIndex()


func getRarity() -> int:
	return descriptor.rarity


func getShopChance() -> float:
	return descriptor.getShopChance()


func getMainType() -> int:
	return descriptor.types[0]


func getNumStaticTypes() -> int:
	return descriptor.getTypes().size()


# 对齐 Item.gd:3591-3593
func getTypes() -> Array:
	return dynamicTypes.keys() + descriptor.types


# 对齐 Item.gd:3622-3628
func hasDynamicType(type: int, fromItem) -> bool:
	if type in dynamicTypes:
		if fromItem.get_instance_id() in dynamicTypes[type]:
			return true
	
	return false


# 对齐 Item.gd:3603-3613。原版 tail 的 inventory.onItemTypeChanged(self) 属背包刷新，
# ObjectPool.particleOneShot 属粒子表现 —— 两者均走钩子。
func addDynamicType(type: int, byItem) -> void :
	if not type in descriptor.types:
		CoreUtil.dictAppend(dynamicTypes, type, byItem.get_instance_id())
		
		if dynamicTypes[type].size() == 1:
			if placed:
				ctx.hooks.onItemTypeChanged(self)


# 对齐 Item.gd:3614-3621
func removeDynamicType(type: int, byItem) -> void :
	if hasDynamicType(type, byItem):
		CoreUtil.dictErase(dynamicTypes, type, byItem.get_instance_id())
		
		if not type in dynamicTypes:
			if placed:
				ctx.hooks.onItemTypeChanged(self)


# 对齐 Item.gd:3629-3631
func clearDynamicTypes() -> void :
	dynamicTypes.clear()


# 对齐 Item.gd:703-705
func isA(_descriptor) -> bool:
	return descriptor == _descriptor


# 对齐 Item.gd:978-980
func isNeutral() -> bool:
	return descriptor.isNeutral()


# 对齐 Item.gd:5739-5741
func isTreasure() -> bool:
	return descriptor.randomUniquePool


# 对齐 Item.gd:973-977
func isClassItem(classIndex = null) -> bool:
	if classIndex != null:
		return descriptor.isClassItem() and descriptor.isAvailableFor(classIndex)
	return descriptor.isClassItem()


# 对齐 Item.gd:981-983
func isSubclassItem() -> bool:
	return descriptor.isSubclassItem()


# 对齐 Item.gd:964-968
func isOwnable() -> bool:
	return (ownerType == CoreConst.Owner.Shop or 
		ownerType == CoreConst.Owner.PlayerInventory or 
		ownerType == CoreConst.Owner.PlayerStorageBox)


# 对齐 Item.gd:969-972
func isOwnedByOpponent() -> bool:
	return ownerType == CoreConst.Owner.Opponent


# 对齐 Item.gd:984-986（原版 has_method 探测 → 内核的 behavior 探测）
func isGateItem() -> bool:
	return _hasBehaviorMethod("getGatedDescriptor") or _hasBehaviorMethod("getReplaceDescriptor")


# 对齐 Item.gd:5783-5785
func isShowCaseItem() -> bool:
	return character() == null


# 对齐 Item.gd:3566-3580（基类恒 false，由物品行为覆写）
func isAffectingDistinct(color = CoreConst.Affected.Primary) -> bool:
	if _hasBehaviorMethod("isAffectingDistinct"):
		return CoreUtil.truth(_behavior_call("isAffectingDistinct", [color]))
	return false


# 对齐 Item.gd:3540-3543（基类恒 false，由物品行为覆写）
func affectsEmpty(color) -> bool:
	if _hasBehaviorMethod("affectsEmpty"):
		return CoreUtil.truth(_behavior_call("affectsEmpty", [color]))
	return false


# 对齐 Item.gd:3951-3953
func hasOpponent() -> bool:
	return hasCharacter() and opponent() != null


# 对齐 Item.gd:1295-1297
func getEffectiveOwnerType() -> int:
	return ownerType


# 对齐 Item.gd:5873-5875。制作系统已剥离（见文件头）→ bondedIngredients 恒空，
# 故恒 false；与「制作系统不存在时原版的取值」一致。
func isBaseItem():
	return false


# 对齐 Item.gd:5862-5864。两项判据（curRecipe / isBoundAsIngredient）都属制作系统，
# 剥离后均为空 → 恒 false。
func isBusy() -> bool:
	return false


# 对齐 Item.gd:6160-6162（isBoundAsIngredient），同属制作系统 → 恒 false
func isBoundAsIngredient() -> bool:
	return false


# ─────────────────────── 数值取值 / 修正标记（对齐 3733-3741, 3792-3994, 4836-4881） ───────────────────────

# 对齐 Item.gd:4836-4867
func getStat(stat):
	match stat:
		CoreConst.ItemStat.MaxDamage:
			if getBaseMaxDamage() > 0:
				return getMaxDamage()
			else:
				return 0
		CoreConst.ItemStat.MinDamage:
			if getBaseMinDamage() > 0:
				return getMinDamage()
			else:
				return 0
		CoreConst.ItemStat.Accuracy:
			return getAccuracy()
		CoreConst.ItemStat.CritChance:
			return getCritChancePercent()
		CoreConst.ItemStat.Speed:
			return getSpeed()
		CoreConst.ItemStat.Cooldown:
			return getCooldownEncoded()
		CoreConst.ItemStat.StaminaCost:
			return getStaminaCost()
		CoreConst.ItemStat.Chance:
			return getChance()
		CoreConst.ItemStat.Chance2:
			return getChance2()
		CoreConst.ItemStat.BaseCooldown:
			return getCooldown()


# 对齐 Item.gd:3888-3891。原版前置 `assert(descriptor.params[index] != 0)`；
# 无头内核不保留 assert（Godot release 构建本就会剥离 assert），读取点与取值不变。
func getP_check(index) -> float:
	return descriptor.params[index]


func getP1() -> float:
	return getP_check(0)


func getP2() -> float:
	return getP_check(1)


func getP3() -> float:
	return getP_check(2)


func getP4() -> float:
	return getP_check(3)


func getP5() -> float:
	return getP_check(4)


func getP6() -> float:
	return getP_check(5)


func getP7() -> float:
	return getP_check(6)


func getP8() -> float:
	return getP_check(7)


func getP9() -> float:
	return getP_check(8)


func getP10() -> float:
	return getP_check(9)


# 对齐 Item.gd:4872-4876
func addSpeed(amount):
	speedScale += amount
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Speed)
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown)


# 对齐 Item.gd:4877-4881
func reduceSpeed(amount):
	speedScale -= amount
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Speed)
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.Cooldown)


# 对齐 Item.gd:3733-3735
func getDPS() -> float:
	return ((getMinDamage() + getMaxDamage()) * 0.5) / getModifiedCooldown()


# 对齐 Item.gd:3736-3741
func isDPSModified() -> int:
	var baseDPS = getBaseAverageDamage() / getCooldown()
	var modifiedDPS = getAverageDamage() / getModifiedCooldown()
	return isStatModified(modifiedDPS - baseDPS)


# 对齐 Item.gd:3712-3717
func getDamageRange() -> String:
	if getMinDamage() == getMaxDamage():
		return String(getMinDamage())
	else:
		return String(getMinDamage()) + "-" + String(getMaxDamage())


# 对齐 Item.gd:3792-3797
func isCooldownModified() -> int:
	var baseCd = getBaseCooldown()
	var curCd = getModifiedCooldown()
	return isStatModified(baseCd - curCd)


# 对齐 Item.gd:3836-3838
func isAccuracyModified() -> int:
	return isStatModified(getAccuracy() - getBaseAccuracy())


# 对齐 Item.gd:3852-3854
func isChance1Modified() -> int:
	return isStatModified(getChance() - getBaseChance())


# 对齐 Item.gd:3858-3860
func isChance2Modified() -> int:
	return isStatModified(getChance2() - getBaseChance2())


# 对齐 Item.gd:3729-3732
func isDamageModified() -> int:
	var bonusDam = getAverageDamage() - getBaseAverageDamage()
	return isStatModified(bonusDam)


# 对齐 Item.gd:3984-3986
func getBaseStaminaPerSecond() -> float:
	return getBaseStaminaCost() / getCooldown()


# 对齐 Item.gd:3987-3989
func getStaminaPerSecond() -> float:
	return getStaminaCost() / getModifiedCooldown()


# 对齐 Item.gd:3990-3994
func isStaminaPerSecondModified() -> int:
	var baseSPS = getBaseStaminaPerSecond()
	var modifiedSPS = getStaminaPerSecond()
	return isStatModified(baseSPS - modifiedSPS)


# ─────────────────────── 能力查询（对齐 3544-3664, 3876-3884, 4143-4148, 5376-5400） ───────────────────────
# ★ 联动虚方法的派发约定：原版这些方法在 Items/*.gd 里被**覆写**（如 Food.gd 覆写
#   canAffect），运行期由 GDScript 的多态直接生效。无头内核没有继承链，改为
#   显式派发：行为脚本里有同名实现就用它，否则回落到基类实现（基类多为 `return false`）。
#   这与 engine/item.py:1920-1934 的既有做法一致，取值域与原版多态相同。

# 对齐 Item.gd:3544-3546（基类恒 false，由物品行为覆写）
func canAffect(item) -> bool:
	if _hasBehaviorMethod("canAffect"):
		return CoreUtil.truth(_behavior_call("canAffect", [item]))
	return false


# 对齐 Item.gd:3547-3549
func canAffect_secondary(item) -> bool:
	if _hasBehaviorMethod("canAffect_secondary"):
		return CoreUtil.truth(_behavior_call("canAffect_secondary", [item]))
	return false


# 对齐 Item.gd:3550-3552
func canAffect_tertiary(item) -> bool:
	if _hasBehaviorMethod("canAffect_tertiary"):
		return CoreUtil.truth(_behavior_call("canAffect_tertiary", [item]))
	return false


# 对齐 Item.gd:3553-3555
func canAffect_lightning(item) -> bool:
	if _hasBehaviorMethod("canAffect_lightning"):
		return CoreUtil.truth(_behavior_call("canAffect_lightning", [item]))
	return false


# 对齐 Item.gd:3556-3565
func canAffect_color(item, color):
	if color == CoreConst.Affected.Primary:
		return canAffect(item)
	elif color == CoreConst.Affected.Secondary:
		return canAffect_secondary(item)
	elif color == CoreConst.Affected.Tertiary:
		return canAffect_tertiary(item)
	else:
		return canAffect_lightning(item)


# 对齐 Item.gd:3662-3664
func canBlock() -> bool:
	return getBlock() > 0


# 对齐 Item.gd:5379-5381
func canHealOrLifesteal() -> bool:
	return descriptor.hasParam("heal") or descriptor.hasParam("lifesteal")


# 对齐 Item.gd:3882-3884
func canModifyChance() -> bool:
	return getBaseChance() > 0


# 对齐 Item.gd:5376-5378
func canUseStamina() -> bool:
	return getBaseStaminaCost() > 0


# 对齐 Item.gd:4143-4148
func hasAttackEffect() -> bool:
	return (hasPreDealDamageEarlyEffect or 
			hasPreDealDamageLateEffect or 
			hasDealtDamageEffect)


# 对齐 Item.gd:5392-5394
func gainsBuffs() -> bool:
	return descriptor.gainedStacks & CoreConst.Stack.Buff


# 对齐 Item.gd:5395-5397
func usesBuffs() -> bool:
	return descriptor.usedStacks & CoreConst.Stack.Buff


# 对齐 Item.gd:5398-5400
func inflictsDebuffs() -> bool:
	return descriptor.gainedStacks & CoreConst.Stack.Debuff


# 对齐 Item.gd:5165-5167
func reactsToCharges() -> bool:
	return hasOnChargeReceivedEffect or hasOnChargeLeftEffect


# 对齐 Item.gd:4196-4201
func fillUpStamina():
	character().fillUpStamina()


# 对齐 Item.gd:5336-5338
func getRelativeOpponentHealth():
	return opponent().getRelativeHealth()


# 对齐 Item.gd:5339-5343
func getRelativeHealth():
	return character().getRelativeHealth()


# ─────────────────────── 栈 / buff 取用（对齐 4882-5185, 5392-5686） ───────────────────────

# 对齐 Item.gd:4882-4884
func giveBuffPower(buffType, power):
	buffPowers[buffType] += power


# 对齐 Item.gd:4885-4888
func changeHealAmp(amount):
	modifyParam("heal", amount)
	modifyParam("lifesteal", amount)


# 对齐 Item.gd:4117-4121
func changeStaminaFactor(amount):
	staminaFactor += amount / 100.0
	staminaFactor = max(0, staminaFactor)
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.StaminaCost)


# 对齐 Item.gd:4106-4110
func addBonusDamageFactor(factor):
	bonusDamageFactor += factor
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MinDamage)
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MaxDamage)


# 对齐 Item.gd:4111-4116
func reduceBonusDamageFactor(factor):
	bonusDamageFactor -= factor
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MinDamage)
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MaxDamage)


# 对齐 Item.gd:4098-4101
func reduceMinDamage(damage):
	bonusMinDam -= damage
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MinDamage)


# 对齐 Item.gd:4102-4105
func reduceMaxDamage(damage):
	bonusMaxDam -= damage
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MaxDamage)


# 对齐 Item.gd:4076-4086（尾行 spawnLabel 走钩子）
func reduceBonusDamage(damage, showLabel: bool = true, removable: bool = true):
	bonusMinDam -= damage
	bonusMaxDam -= damage
	if removable:
		removableDam -= damage
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MinDamage)
	ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MaxDamage)
	
	if showLabel:
		spawnLabel(CoreConst.EventType.DamageBuff, - damage)


# 对齐 Item.gd:4087-4097（尾行 spawnLabel 走钩子）
func purgeDamage(damage):
	var purgable = min(damage, removableDam)
	if purgable > 0:
		removableDam -= purgable
		bonusMinDam -= purgable
		bonusMaxDam -= purgable
		ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MinDamage)
		ctx.combat_log.snapshotItemTooltipStat(self, CoreConst.ItemStat.MaxDamage)
		
		spawnLabel(CoreConst.EventType.DamageBuff, - purgable)


# 对齐 Item.gd:4122-4124
func giveDoubleActivationChance(_chance):
	doubleActivationChance += _chance / 100.0


# 对齐 Item.gd:4125-4127
func giveDoubleAttackEffectChance(_chance):
	doubleAttackEffectChance += _chance / 100.0


# 对齐 Item.gd:5142-5146
func giveCritTokens(amount):
	character().gainCritTokens(amount)


# 对齐 Item.gd:4229-4231
func giveMaxStamina(amount):
	character().giveMaxStamina(amount)


# 对齐 Item.gd:4232-4234
func giveMaxStaminaTemporary(amount, triggerEvent = null, filled: bool = true):
	character().gainMaxStaminaTemporary(amount, self, triggerEvent, filled)


# 对齐 Item.gd:4235-4241
func giveMaxHealth(amount = null, triggerEvent = null):
	if amount == null:
		amount = getP_m("maxhealth")
	amount = character().applyTemporaryMaxHealthGain(amount)
	if amount > 0:
		addMetric(CoreConst.ItemMetrics.MaxHealth, amount, null, true)
		character().changeMaxHealthTemporary(amount, self, triggerEvent)
		spawnLabel(CoreConst.EventType.TemporaryMaxHealth, amount)


# 对齐 Item.gd:4193-4195
func giveStamina(amount = 1, triggerEvent = null):
	character().gainStamina(amount, self, triggerEvent)


# 对齐 Item.gd:4182-4185
func inflictFatigueDamage(fatigueIncrease = 1):
	opponent().addFatigueDamage(fatigueIncrease)
	opponent().takeFatigueDamage(self)


# 对齐 Item.gd:5147-5154（电荷传播的视觉与音效走钩子；numCharges 记账保留）
func sendCharge(durPerTile: float, cells: Array, speedFactor: float, event):
	var chargeDuration = durPerTile * (cells.size() - 1)
	ctx.hooks.sendCharge(self, cells, chargeDuration / speedFactor, event)


# 对齐 Item.gd:5155-5159
func chargeReceived(charge):
	numCharges += 1
	if hasOnChargeReceivedEffect:
		_behavior_call("onChargeReceived", [charge])


# 对齐 Item.gd:5160-5164
func chargeLeft(charge):
	numCharges -= 1
	if hasOnChargeLeftEffect:
		_behavior_call("onChargeLeft", [charge])


# 对齐 Item.gd:5168-5185
func changeChargedItemStat(charge, cellIndex, flatVal, valPerTile):
	
	var previousVal = flatVal + (cellIndex - 2) * valPerTile
	var newVal = previousVal + valPerTile
	
	if charge.lastChargedItem != null:
		if charge.curChargedItem == null:
			_behavior_call("chargedItemStatChange", [charge.lastChargedItem, - previousVal])
		elif charge.curChargedItem == charge.lastChargedItem:
			_behavior_call("chargedItemStatChange", [charge.curChargedItem, valPerTile])
		else:
			_behavior_call("chargedItemStatChange", [charge.lastChargedItem, - previousVal])
			_behavior_call("chargedItemStatChange", [charge.curChargedItem, newVal])
	
	elif charge.curChargedItem != null:
		_behavior_call("chargedItemStatChange", [charge.curChargedItem, newVal])


# ─────────────────────── 治疗 / 伤害 / 减益（对齐 4826-5136, 5379-5394） ───────────────────────

# 对齐 Item.gd:4826-4828
func heal(amount = null, triggerEvent = null):
	if amount == null:
		amount = getP_m("heal")
	var healed = character().heal(amount, self, triggerEvent)


# 对齐 Item.gd:5122-5129
func healthToBlock(health: float, block, triggerEvent = null):
	var clampedHealth = min(health, character().getCurrentHealth() - 1)
	if clampedHealth > 0:
		character().loseHealth(clampedHealth, self, triggerEvent)
		
		block = ceil((clampedHealth / health) * block)
		giveBlock(block, true, triggerEvent)


# 对齐 Item.gd:5136-5141
func stealLife(damage, lifestealFactor: float = 1.0, triggerEvent = null):
	ctx.stealLifeDamageSource.updateEffect(self, damage)
	var damageRes = opponent().takeDamage(ctx.stealLifeDamageSource, triggerEvent)
	heal(damageRes.damage * lifestealFactor, damageRes.event)
	return damageRes


# 对齐 Item.gd:4829-4831
func stun(duration, triggerEvent = null):
	opponent().stun(duration, self, triggerEvent)


# 对齐 Item.gd:5077-5079
func checkMana(amount) -> bool:
	return character().getMana() >= amount


# 对齐 Item.gd:5080-5083
func useMana(amount, triggerEvent = null):
	return character().useMana(amount, self, triggerEvent)


# 对齐 Item.gd:5084-5090
func tryUseMana(amount, triggerEvent = null):
	var curMana = character().getMana()
	if curMana < amount:
		return null
	else:
		return useMana(amount, triggerEvent)


# 对齐 Item.gd:5091-5093
func removeMana(amount, triggerEvent = null):
	opponent().loseMana(amount, self, triggerEvent)


# 对齐 Item.gd:5066-5076
func giveMana_capped(amount, maximum, triggerEvent = null):
	amount = round(amount * buffPowers[CoreConst.EventType.Mana])
	var curMana = character().getMana()
	if maximum > curMana:
		var missingMana = maximum - curMana
		var manaGiven = min(amount, missingMana)
		character().gainMana(manaGiven, self, triggerEvent)
		return amount - manaGiven
	else:
		return amount


# ── 减益 / buff 的「自身使用 / 转给对手」成对包装（对齐 4983-5115, 5494-5529） ──

# 对齐 Item.gd:4983-4985
func removeSpikes(amount, triggerEvent = null):
	opponent().loseSpikes(amount, self, triggerEvent)


# 对齐 Item.gd:4989-4991
func useSpikes(amount, triggerEvent = null):
	return character().useStacks(CoreConst.EventType.Spikes, amount, self, triggerEvent)


# 对齐 Item.gd:4986-4988
func loseSpikes(amount, triggerEvent = null):
	character().loseSpikes(amount, self, triggerEvent)


# 对齐 Item.gd:4995-4997
func removeVampirism(amount, triggerEvent = null):
	opponent().loseVampirism(amount, self, triggerEvent)


# 对齐 Item.gd:4998-5000
func useVampirism(amount, triggerEvent = null):
	return character().useStacks(CoreConst.EventType.Vampirism, amount, self, triggerEvent)


# 对齐 Item.gd:5001-5003
func loseVampirism(amount, triggerEvent = null):
	character().loseVampirism(amount, self, triggerEvent)


# 对齐 Item.gd:5010-5018
func cleansePoison(amount: int, triggerEvent = null) -> int:
	var curPoison = character().getPoison()
	if curPoison == 0:
		return 0
	
	amount = min(curPoison, amount)
	character().losePoison(amount, self, triggerEvent)
	return amount


# 对齐 Item.gd:5022-5024
func selfInflictBlind(amount, triggerEvent = null):
	return giveStacks(character(), CoreConst.EventType.Blind, amount, triggerEvent)


# 对齐 Item.gd:5025-5033
func cleanseBlind(amount: int, triggerEvent = null) -> int:
	var curBlind = character().getBlind()
	if curBlind == 0:
		return 0
	
	amount = min(curBlind, amount)
	character().loseBlind(amount, self, triggerEvent)
	return amount


# 对齐 Item.gd:5037-5039
func removeRegeneration(amount, triggerEvent = null):
	return opponent().loseRegeneration(amount, self, triggerEvent)


# 对齐 Item.gd:5040-5042
func useRegeneration(amount, triggerEvent = null):
	return character().useStacks(CoreConst.EventType.Regeneration, amount, self, triggerEvent)


# 对齐 Item.gd:5046-5052
func tryUseLucky(amount, triggerEvent = null):
	if character().getLucky() >= amount:
		useLucky(amount, triggerEvent)
		return true
	else:
		return false


# 对齐 Item.gd:5053-5055
func loseLucky(amount, triggerEvent = null):
	character().loseLucky(amount, self, triggerEvent)


# 对齐 Item.gd:5056-5058
func removeLucky(amount, triggerEvent = null):
	opponent().loseLucky(amount, self, triggerEvent)


# 对齐 Item.gd:5059-5061
func useLucky(amount, triggerEvent = null):
	return character().useStacks(CoreConst.EventType.Lucky, amount, self, triggerEvent)


# 对齐 Item.gd:5094-5096
func inflictCold(amount, triggerEvent = null):
	giveStacks(opponent(), CoreConst.EventType.Cold, amount, triggerEvent)


# 对齐 Item.gd:5097-5106
func cleanseCold(amount: int, triggerEvent = null) -> int:
	var curCold = character().getCold()
	if curCold == 0:
		return 0
	
	amount = min(curCold, amount)
	character().loseCold(amount, self, triggerEvent)
	return amount


# 对齐 Item.gd:5110-5112
func loseHeat(amount, triggerEvent = null):
	character().loseHeat(amount, self, triggerEvent)


# 对齐 Item.gd:5113-5115
func useHeat(amount, triggerEvent = null):
	return character().useStacks(CoreConst.EventType.Heat, amount, self, triggerEvent)


# 对齐 Item.gd:5119-5121
func loseEmpower(amount, triggerEvent = null):
	character().loseEmpower(amount, self, triggerEvent)


# 对齐 Item.gd:5516-5529
func cleanseRandomDebuffs(numDebuffs, triggerEvent = null):
	var cleansedDebuffs = pickRandomStacks(CoreConst.getDebuffs(), numDebuffs, character())
	
	ctx.bus.setLoggingMode(CoreEventBus.LoggingMode.Delayed)
	for debuff in cleansedDebuffs:
		character().loseStacks(debuff, cleansedDebuffs[debuff], self, triggerEvent)
	
	ctx.bus.flushLoggingQueue()


# 对齐 Item.gd:5482-5493
func inflictRandomDebuffs(numDebuffs, triggerEvent = null, availableDebuffs = null):
	if availableDebuffs == null:
		availableDebuffs = CoreConst.getDebuffs()
	var pickedDebuffs = pickRandomStacksToGive(availableDebuffs, numDebuffs)
	
	ctx.bus.setLoggingMode(CoreEventBus.LoggingMode.Delayed)
	for debuff in pickedDebuffs:
		giveStacks(opponent(), debuff, pickedDebuffs[debuff], triggerEvent)
	
	ctx.bus.flushLoggingQueue()


# ─────────────────────── 随机 buff 取用（对齐 5422-5685） ───────────────────────
# 取随机一律走 ctx.rng（原版 Util.rng，Util.gd:6），保证同种子可复现。

# 对齐 Item.gd:5422-5446
func pickRandomStacks(stackTypes, numStacks, target, priorityStack = null):
	var stacks = Dictionary()
	for stackType in stackTypes:
		var numTargetStacks = target.getStacks(stackType)
		if numTargetStacks > 0:
			stacks[stackType] = numTargetStacks
	
	var pickedStacks = Dictionary()
	
	if priorityStack != null:
		var pickedPriorityStacks = min(numStacks, stacks.get(priorityStack, 0))
		if pickedPriorityStacks > 0:
			pickedStacks[priorityStack] = pickedPriorityStacks
			numStacks -= pickedPriorityStacks
			CoreUtil.dictSub(stacks, priorityStack, pickedPriorityStacks)
	
	for i in range(numStacks):
		if not stacks.empty():
			var stackType = ctx.rng.pickRandomElement(stacks.keys())
			CoreUtil.dictAdd(pickedStacks, stackType, 1)
			CoreUtil.dictSub(stacks, stackType, 1)
	
	return pickedStacks


# 对齐 Item.gd:5447-5454
func pickRandomStacksToGive(stackTypes, numStacks):
	var pickedStacks = Dictionary()
	for i in range(numStacks):
		var stackType = ctx.rng.pickRandomElement(stackTypes)
		CoreUtil.dictAdd(pickedStacks, stackType, 1)
	
	return pickedStacks


# 对齐 Item.gd:5530-5554
func getLeastStacks(numStacks, target, availableStacks):
	var priorStacks: Dictionary = {}
	for stackType in availableStacks:
		priorStacks[stackType] = target.getStacks(stackType)
	
	var pickedStacks: Dictionary = {}
	
	while numStacks > 0:
		var leastStacksCount: int = 10000
		var leastStacks = []
		for stackType in priorStacks:
			if priorStacks[stackType] < leastStacksCount:
				leastStacksCount = priorStacks[stackType]
				leastStacks.clear()
				leastStacks.push_back(stackType)
			elif priorStacks[stackType] == leastStacksCount:
				leastStacks.push_back(stackType)
		var stackToGive = ctx.rng.pickRandomElement(leastStacks)
		CoreUtil.dictAdd(pickedStacks, stackToGive, 1)
		CoreUtil.dictAdd(priorStacks, stackToGive, 1)
		numStacks -= 1
	
	return pickedStacks


# 对齐 Item.gd:5563-5579
func getMostStacks(target, availableStacks):
	var buffs = Dictionary()
	for buff in availableStacks:
		buffs[buff] = target.getStacks(buff)
	
	var maxBuffs = []
	var maxStacks = 0
	for buff in buffs:
		if buffs[buff] == maxStacks:
			maxBuffs.push_back(buff)
		elif buffs[buff] > maxStacks:
			maxBuffs.clear()
			maxBuffs.push_back(buff)
			maxStacks = buffs[buff]
	
	return maxBuffs


# 对齐 Item.gd:5610-5652（原版 Util.sortDict(overflow, true) → CoreUtil.sortDict(.., ctx.rng, true)）
func getStackFraction(target, fraction: float, 
	limit: int, availableStacks):
	
	var sum: float = 0.0
	var stacksUnlimited: Dictionary = {}
	
	for buff in availableStacks:
		var prior = target.getStacks(buff)
		
		var withBonus = prior * fraction
		stacksUnlimited[buff] = withBonus
		sum += withBonus
	
	var sumRounded = round(sum)
	if sumRounded == 0: return null
	
	var totalToGive: float = min(limit, sumRounded)
	var limitFactor = totalToGive / sumRounded
	
	var buffsToGive: Dictionary = {}
	var overflow: Dictionary = {}
	var totalGiven: int = 0
	
	for buff in stacksUnlimited:
		var limited = stacksUnlimited[buff] * limitFactor
		var guaranteed = int(limited)
		buffsToGive[buff] = guaranteed
		overflow[buff] = limited - guaranteed
		totalGiven += guaranteed
	
	var overflowBuffs: int = totalToGive - totalGiven
	var sortedOverflow: Array = CoreUtil.sortDict(overflow, ctx.rng, true)
	
	for buff in sortedOverflow:
		if overflowBuffs == 0:
			break
		
		buffsToGive[buff] += 1
		overflowBuffs -= 1
	
	return buffsToGive


# 对齐 Item.gd:5653-5663
func multiplyBuffsLimit(bonus: float, limit: int, availableBuffs = null):
	if availableBuffs == null:
		availableBuffs = CoreConst.getBuffs()
	var buffsToGive = getStackFraction(character(), bonus, limit, availableBuffs)
	if buffsToGive == null: return
	
	ctx.bus.setLoggingMode(CoreEventBus.LoggingMode.Delayed)
	for buff in buffsToGive:
		giveStacks(character(), buff, buffsToGive[buff])
	ctx.bus.flushLoggingQueue()


# 对齐 Item.gd:5664-5674
func removeBuffsFraction(fraction: float, limit: int, 
	triggerEvent = null, availableBuffs = null):
	if availableBuffs == null:
		availableBuffs = CoreConst.getBuffs()
	var buffsToRemove = getStackFraction(opponent(), fraction, limit, availableBuffs)
	if buffsToRemove == null: return
	
	ctx.bus.setLoggingMode(CoreEventBus.LoggingMode.Delayed)
	for buff in buffsToRemove:
		opponent().loseStacks(buff, buffsToRemove[buff], self, triggerEvent)
	ctx.bus.flushLoggingQueue()


# 对齐 Item.gd:5675-5685
func stealBuffsFraction(fraction: float, limit: int, 
	triggerEvent = null, availableBuffs = null):
	if availableBuffs == null:
		availableBuffs = CoreConst.getBuffs()
	var buffsToSteal = getStackFraction(opponent(), fraction, limit, availableBuffs)
	if buffsToSteal == null: return
	
	ctx.bus.setLoggingMode(CoreEventBus.LoggingMode.Delayed)
	for buff in buffsToSteal:
		stealStack(buff, buffsToSteal[buff], triggerEvent)
	ctx.bus.flushLoggingQueue()


# 对齐 Item.gd:5555-5562
func giveLeastBuffs(numBuffs, target = null, triggerEvent = null, 
	availableBuffs = null):
	
	if target == null:
		target = character()
	if availableBuffs == null:
		availableBuffs = CoreConst.getBuffs()
	
	var pickedStacks = getLeastStacks(numBuffs, target, availableBuffs)
	
	for buffType in pickedStacks:
		giveStacks(target, buffType, pickedStacks[buffType], triggerEvent)


# 对齐 Item.gd:5580-5585
func giveMostBuffs(numBuffs, triggerEvent = null, availableBuffs = null):
	if availableBuffs == null:
		availableBuffs = CoreConst.getBuffs()
	var maxBuffs = getMostStacks(character(), availableBuffs)
	var buffToGive = ctx.rng.pickRandomElement(maxBuffs)
	giveStacks(character(), buffToGive, numBuffs, triggerEvent)


# 对齐 Item.gd:5586-5609
func removeMostBuffs(numBuffs, triggerEvent = null, use: bool = false, availableBuffs = null):
	if availableBuffs == null:
		availableBuffs = CoreConst.getBuffs()
	var target
	
	var buffs = Dictionary()
	if use:
		target = character()
	else:
		target = opponent()
	
	var maxBuffs = getMostStacks(target, availableBuffs)
	var buffToRemove = ctx.rng.pickRandomElement(maxBuffs)
	
	var toRemove = min(numBuffs, target.getStacks(buffToRemove))
	if toRemove == 0:
		return null
	
	var event
	if use:
		event = character().useStacks(buffToRemove, toRemove, self, triggerEvent)
	else:
		event = opponent().loseStacks(buffToRemove, toRemove, self, triggerEvent)
	return event


# 对齐 Item.gd:5455-5463
func giveRandomBuffs(numBuffs: int, triggerEvent = null, availableBuffs = null, 
	target = null):
	
	if availableBuffs == null:
		availableBuffs = CoreConst.getBuffs()
	if target == null:
		target = character()
	
	var pickedBuffs = pickRandomStacksToGive(availableBuffs, numBuffs)
	ctx.bus.setLoggingMode(CoreEventBus.LoggingMode.Delayed)
	for buff in pickedBuffs:
		giveStacks(target, buff, pickedBuffs[buff], triggerEvent)
	ctx.bus.flushLoggingQueue()


# 对齐 Item.gd:5464-5468
func giveAllBuffs(numBuffs = 1, triggerEvent = null):
	for buff in CoreConst.getBuffs():
		giveStacks(character(), buff, numBuffs)


# 对齐 Item.gd:5469-5481
func useRandomBuffs(numBuffs, triggerEvent = null, availableBuffs = null):
	if availableBuffs == null:
		availableBuffs = CoreConst.getBuffs()
	var pickedBuffs = pickRandomStacks(availableBuffs, numBuffs, character())
	if pickedBuffs.empty():
		return null
	
	var events = []
	ctx.bus.setLoggingMode(CoreEventBus.LoggingMode.Delayed)
	for buff in pickedBuffs:
		var event = character().useStacks(buff, pickedBuffs[buff], self, triggerEvent)
		events.push_back(event)
	ctx.bus.flushLoggingQueue()
	return events


# 对齐 Item.gd:5494-5500
func removeRandomBuffs(numBuffs, triggerEvent = null):
	var removedStacks = pickRandomStacks(CoreConst.getBuffs(), numBuffs, opponent())
	ctx.bus.setLoggingMode(CoreEventBus.LoggingMode.Delayed)
	for buff in removedStacks:
		opponent().loseStacks(buff, removedStacks[buff], self, triggerEvent)
	ctx.bus.flushLoggingQueue()


# 对齐 Item.gd:5501-5515
func stealRandomBuff(numBuffs, triggerEvent = null, 
	possibleBuffs = null, priorityBuff = null):
	
	if possibleBuffs == null:
		possibleBuffs = CoreConst.getBuffs()
	
	var removedStacks = pickRandomStacks(possibleBuffs, numBuffs, opponent(), priorityBuff)
	ctx.bus.setLoggingMode(CoreEventBus.LoggingMode.Delayed)
	for buff in removedStacks:
		opponent().loseStacks(buff, removedStacks[buff], self, triggerEvent)
		
		giveStacks(character(), buff, removedStacks[buff], triggerEvent)
	ctx.bus.flushLoggingQueue()


# 对齐 Item.gd:5405-5421（把角色 buff 信号接到物品回调）
func connectToCharacterBuffs(methodName):
	for buff in CoreConst.getBuffs():
		connectForCombat(character(), character().buffs[buff].signalName, methodName)


func connectToCharacterDebuffs(methodName):
	for debuff in CoreConst.getDebuffs():
		connectForCombat(character(), character().buffs[debuff].signalName, methodName)


func connectToOpponentDebuffs(methodName):
	for debuff in CoreConst.getDebuffs():
		connectForCombat(opponent(), opponent().buffs[debuff].signalName, methodName)


func connectToOpponentBuffs(methodName):
	for buff in CoreConst.getBuffs():
		connectForCombat(opponent(), opponent().buffs[buff].signalName, methodName)


# ─────────────────────── 状态 / 视觉枢纽（对齐 4804-4831, 4968-4970, 3535-3539） ───────────────────────
# 这些方法在原版里是「物品自身」的视觉出口，物品行为脚本会调用它们；
# 内核把实现整体转给 ctx.hooks（原版对应 Util.spawnLabelOnItem / Settings 开关）。

# 对齐 Item.gd:4804-4809（Settings 的 damage_numbers 开关一并剥离）
func spawnLabel(type, amount):
	ctx.hooks.spawnLabelOnItem(type, self, amount)


# 对齐 Item.gd:4810-4814（Settings 的 buff_labels 开关一并剥离）
func spawnLabel_other(type, amount):
	ctx.hooks.spawnLabelOnItem(type, self, amount)


# 对齐 Item.gd:4815-4818
func consume(damageRes = null, playCombatAni = true):
	activate(damageRes, playCombatAni, true)
	consumed = true


# 对齐 Item.gd:4819-4822
func setState(newState, withNextEvent: bool = false, event = null):
	ctx.combat_log.snapshotItemState(self, newState, withNextEvent, event)
	onStateChanged(newState)


# 对齐 Item.gd:4823-4825（由物品行为覆写）
func onStateChanged(newState):
	pass


# 对齐 Item.gd:4968-4970（由物品行为覆写）
func onTemporaryStacksTimeout(buffType):
	pass


# 对齐 Item.gd:3535-3539（由物品行为覆写）
func empowerEnd():
	pass


# 对齐 Item.gd:2982-2987, 2996-3001, 3037-3058（宝石托管；本内核宝石见 gems 数组）
func hasSockets() -> bool:
	return not gems.empty()


func getNumSockets() -> int:
	return gems.size()


# 对齐 Item.gd:2978-2980（全文 `for socket in sockets: socket.item = self`）。
# ★ 本内核里它是**折叠后无事可做**，不是遗漏：
#   原版这一句的唯一作用是给 `GemSocket.item` 装回指指针，好让
#   `GemSocket.getItem()`（GemSocket.gd:19-20）能返回宿主物品。
#   而内核已把「插座」这个身份整体折叠为宿主物品本身（见 setGem 的注释），
#   方向又是**恒定的** self → `getItem()` 直接返回 self（见下），
#   `socket.item = self` 这条后置条件在折叠模型下**恒真**，无需也不可能有别的写法。
#   调用点照原版保留（Item.gd:547 在 `_ready` 里调它）→ 内核等价生命周期点 `_readyInit()`，
#   与 `onready var hasXxxEffect = has_method(...)` 同一处；调用本身不改任何状态。
#   实证：闸门 10（GemFacade）逐条比对 Gem.gd 对 socket 的全部访问面，
#   战斗路径上只会用到 `socket.getItem()`（15 处），全部落在本折叠上。
func initSockets() -> void :
	pass


# 对齐 GemSocket.gd:19-20 `func getItem(): return item`，其中 `item` 由
# Item.initSockets()（Item.gd:2978-2980，`socket.item = self`）回指**宿主物品**。
# 内核把插座折叠为宿主物品本身（见 setGem 注释），故这里恒返回 self ——
# 这正是 Gem.gd 全部 `socket.getItem().xxx()` 调用链的终点：
#   isGem 系（isOwnable/isPlaced/isInInventory/getInventory/getEffectiveOwnerType）
#   与 getGemMode() 都靠它取到宿主。
func getItem():
	return self


func hasGems() -> bool:
	for gem in gems:
		if gem != null:
			return true
	return false


func getGemsOfItems(items):
	var out = []
	for item in items:
		out.append_array(item.getGemsNoNull())
	return out


# 对齐 Item.gd:3024-3036（ItemBook.getGemIndex 属数据层，由装配层提供 index）
# ── 宝石数据族（getGemData / setGem / setGemData）留待宝石子系统里程碑，
#    它们依赖 CoreGem 的 getIndex/getFaceDirection/isLocked；本内核宝石见 gems 数组。

# 对齐 Item.gd:3954-3960
func getPrice():
	return descriptor.getPrice()


func getBaseSellPrice():
	return descriptor.getSellPrice()


func getSellPrice():
	return descriptor.getSellPrice()


func getSalePrice():
	return descriptor.getSalePrice()


# 对齐 Item.gd:3037-3045（setGem）
# ★ 原版走的是**插座节点**：`sockets: Array = $Icon/Sockets.get_children()`
#   （Item.gd:309），`sockets[socketId].add_child(gem)` 是场景树挂载，
#   `gem.addToSocket(sockets[socketId])` 收到的也是**插座节点**。
#   内核无节点树，`gems[]` 即原版的 `sockets[]`（等价性：Gem.gd 对 socket 的
#   全部访问都只经 `socket.getItem()` / `socket.getGem()`，
#   而 GemSocket.gd:19-20 的 `getItem()` 直接返回宿主物品、`getGem()` 返回格内宝石）
#   → 插座的身份折叠为宿主物品本身，故这里把 self 充当 socket 传入。
#   配套：CoreItem.getItem() 返回 self（对应 GemSocket.getItem() → item）。
# ★ 原版第 3039 行的 `print("ohnonononononno")` 是作者的调试怨言，逐字保留：
#   它标记「插座下标越界」这一异常分支，越界时原版同样只是打印、不做任何事。
func setGem(socketId: int, gem):
	if socketId >= gems.size():
		print("ohnonononononno")
	else:
		gem.ownerType = CoreConst.Owner.Socket
		gems[socketId] = gem
		# 等价于 Gem.addToSocket(self)：那 3 条与战斗相关的语句是
		# `socket = _socket` / `ownerType = Owner.Socket` / `occupiedCells.clear()`；
		# 其余（Util.reparent / socket.onDropGem / CraftingManager.itemAdded）属场景树
		# 与制作系统，已在转译期剥离，故整函数成了空桩，这三条由本方法补齐。
		gem.socket = self
		gem.occupiedCells.clear()


# 对齐 Item.gd:3002-3010、2957-2959、3011-3014 —— 宝石/内容物回储物箱，
# 属商店-背包跨越，战斗内不触发（原版 pushItemsInsideToStorage/returnToSocket 为 pass）
func pushGemsToStorage():
	pass


func pushItemsInsideToStorage():
	pass


func returnToSocket(movebackDur):
	pass


# ─────────────────────── 网格 / 邻接 / 受影响格（对齐 1034-1607, 3544-3586, 5192-5254） ───────────────────────
# 坐标系约定与等价性依据见 CoreGrid.gd 文件头：原版的「格 → 全局坐标 → 格」往返
# 在格点对齐的网格上恒等，内核据此直接以格空间求值。

# 对齐 Item.gd:1104-1108。原版未放置时回落到 Game.PLAYER.INVENTORY（autoload 恒非空）；
# 内核里 player 由 setup() 注入，尚未注入时回落到 ctx 的共享空网格，
# 保持「恒返回一个可查询的背包」这一语义（详见 CoreContext.emptyGrid）。
func getOwnOrPlayerInventory():
	if placed:
		return inventory
	elif ctx.player != null:
		return ctx.player.inventory
	return ctx.emptyGrid()


# ── 几何层接口（内核折叠为格空间的恒等映射；保留接口以维持调用点形状） ──

# 对齐 Item.gd:1034-1039
func getCellsForGlobalPositions(points: Array) -> Array:
	return points


# 对齐 Item.gd:1040-1047
func getGlobalPointsForCells(cells):
	return cells


# 对齐 Item.gd:1048-1056
func getGlobalPointsForCells_noRotate(cells):
	return cells


# 对齐 Item.gd:1066-1070
func getCollisionCells():
	return collisionCells


# 对齐 Item.gd:1211-1213
func getExtensionCells():
	return extensionCells


# 对齐 Item.gd:1101-1103
func getCollisionPoints():
	return collisionCells


# 对齐 Item.gd:1214-1226
func getExtensionPoints():
	return extensionCells


# ── 受影响格 ──

# 对齐 Item.gd:1112-1116
func getAffectedCells_tilemap(color = CoreConst.Affected.Primary) -> Array:
	return affectedTileCells.get(color, [])


# 对齐 Item.gd:1117-1124
func getAffectedCellsAfterRotate(rotatedCells, color = CoreConst.Affected.Primary) -> Array:
	if color == CoreConst.Affected.Primary:
		return getAffectedCellsAfterRotate_primary(rotatedCells)
	elif color == CoreConst.Affected.Secondary:
		return getAffectedCellsAfterRotate_secondary(rotatedCells)
	else:
		return []


# 对齐 Item.gd:1125-1127（基类空，由物品行为覆写）
func getAffectedCellsAfterRotate_primary(_rotatedCells):
	if _hasBehaviorMethod("getAffectedCellsAfterRotate_primary"):
		return _behavior_call("getAffectedCellsAfterRotate_primary", [_rotatedCells])
	return []


# 对齐 Item.gd:1128-1131（基类空，由物品行为覆写）
func getAffectedCellsAfterRotate_secondary(_rotatedCells):
	if _hasBehaviorMethod("getAffectedCellsAfterRotate_secondary"):
		return _behavior_call("getAffectedCellsAfterRotate_secondary", [_rotatedCells])
	return []


# 对齐 Item.gd:1132-1138。rotatedCells = getCellsForGlobalPositions(getCollisionPoints())
# 在格点上恒等于 collisionCells，故直接代入（见 CoreGrid.gd 文件头推导）。
func getAffectedCells_noRotate(color = CoreConst.Affected.Primary):
	return getAffectedCellsAfterRotate(collisionCells, color)


# 对齐 Item.gd:1145-1147
func getAffectedPoints(color = CoreConst.Affected.Primary) -> Array:
	return getAffectedCells_tilemap(color) + getAffectedCells_noRotate(color)


# 对齐 Item.gd:1148-1151
func getAffectedCellsInInventory(color = CoreConst.Affected.Primary) -> Array:
	return getOwnOrPlayerInventory().getCellsForGlobalPositions(getAffectedPoints(color))


# 对齐 Item.gd:1483-1485
func getAffectedCellsInInventory_cached(color):
	return affectedCellsCache.get(color, [])


# 对齐 Item.gd:1367-1370
func cacheAffectedCells():
	for color in CoreConst.Affected.values():
		affectedCellsCache[color] = getAffectedCellsInInventory(color)


# 对齐 Item.gd:1400-1408。原版尾行 `Util.eassert(cachedAffectedItems.empty())` 是
# 编辑器专用断言（Util.gd:207-209 只在 editor feature 下 assert）→ 内核不保留。
func cleanCachedAffectedItems():
	affectedCellsCache.clear()
	
	for color in CoreConst.Affected.values():
		currentAffectedItems[color].clear()


# 对齐 Item.gd:1393-1398 之后的离开背包清理入口
func onRemoveFromInventory():
	cleanCachedAffectedItems()


# 对齐 Item.gd:1409-1410（原版末尾另有 disconnected 清理，属场景层）
func onAddToInventory():
	pass


# 对齐 Item.gd:1161-1174
func getAffectedItems(color = CoreConst.Affected.Primary) -> Array:
	if not cachedAffectedItems.empty():
		return cachedAffectedItems[color]
	
	var items = []
	for item in getItemsInAffectedCells_cached(color):
		if canAffect_color(item, color):
			items.push_back(item)
	return items


# 对齐 Item.gd:1175-1181
func getAffectedItems_nocache(color = CoreConst.Affected.Primary) -> Array:
	var items = []
	for item in getItemsInAffectedCells(color):
		if canAffect_color(item, color):
			items.push_back(item)
	return items


# 对齐 Item.gd:1155-1157
func getItemsInAffectedCells(color = CoreConst.Affected.Primary) -> Array:
	return getOwnOrPlayerInventory().getItemsInCells(getAffectedCellsInInventory(color))


# 对齐 Item.gd:1152-1154
func getItemsInAffectedCells_cached(color = CoreConst.Affected.Primary) -> Array:
	return getOwnOrPlayerInventory().getItemsInCells(getAffectedCellsInInventory_cached(color))


# 对齐 Item.gd:1158-1160
func countItemsInAffectedCells_cached(color = CoreConst.Affected.Primary) -> Dictionary:
	return getOwnOrPlayerInventory().countItemsInCells(getAffectedCellsInInventory_cached(color))


# 对齐 Item.gd:1182-1192
func isItemAffected(item, color = CoreConst.Affected.Primary) -> bool:
	if item.isBag() or not canAffect_color(item, color):
		return false
	
	var affectedTiles = getAffectedCellsInInventory_cached(color)
	
	for cell in item.occupiedCells:
		if cell in affectedTiles:
			return true
	return false


# 对齐 Item.gd:1193-1195
func getNumEmptyAffectedCells(color = CoreConst.Affected.Primary) -> int:
	return inventory.getEmptyCellsInCells(getAffectedCellsInInventory(color))


# 对齐 Item.gd:1196-1198
func getNumAffectedItems(color = CoreConst.Affected.Primary) -> int:
	return getAffectedItems(color).size()


# 对齐 Item.gd:1199-1204
func getFirstAffectedItem(color = CoreConst.Affected.Primary):
	var _affectedItems = getAffectedItems(color)
	if not _affectedItems.empty():
		return _affectedItems[0]
	return null


# 对齐 Item.gd:1205-1210
func getNumAffected_type(type: int, color = CoreConst.Affected.Primary) -> int:
	var num = 0
	for item in getAffectedItems(color):
		num += item.getTypeMultiplicity(type)
	return num


# 对齐 Item.gd:3581-3586
func getNumDistinctAffectedItems(color = CoreConst.Affected.Primary) -> int:
	var distinctAffectedDescriptors = {}
	for item in getAffectedItems(color):
		distinctAffectedDescriptors[item.descriptor] = true
	return distinctAffectedDescriptors.size()


# 对齐 Item.gd:1139-1144
func getNumAffectedCells(color = CoreConst.Affected.Primary) -> int:
	if color in affectedCellsCache:
		return affectedCellsCache[color].size()
	else:
		return getAffectedCells_tilemap(color).size() + getAffectedCells_noRotate(color).size()


# 对齐 Item.gd:1285-1294（扩展格是 TileMap 上的临时涂色，内核里改 affectedTileCells）
func activateExtendedAffectedCells():
	for cell in affectedExtensionCells:
		CoreUtil.dictAppend(affectedTileCells, CoreConst.Affected.Primary, cell)
	cacheAffectedCells()


func deactivateExtendedAffectedCells():
	for cell in affectedExtensionCells:
		var arr = affectedTileCells.get(CoreConst.Affected.Primary, [])
		if cell in arr:
			arr.erase(cell)
	cacheAffectedCells()


# 对齐 Item.gd:1486-1513（拖拽预览；战斗路径不调用，isHovered 无缓存时恒 false）
func canAffectDraggedItem(item, color):
	if canAffect_color(item, color):
		
		var affectedCells = getAffectedCellsInInventory_cached(color)
		
		for cell in affectedCells:
			if item.dragged:
				if inventory.isHovered(cell):
					return true
			else:
				if cell in item.occupiedCells:
					return true
	return false


# 对齐 Item.gd:1517-1525（基类空，由物品行为覆写）
func onAffectedItemAdded(item, color: int):
	pass


func onAffectedItemRemoved(item, color: int):
	pass


# 对齐 Item.gd:1425-1443（背包内新物品加入时刷新受影响集）
func onItemAdded(item):
	var newItemIsAffected = {}
	for color in CoreConst.Affected.values():
		newItemIsAffected[color] = (not item in currentAffectedItems[color] and 
									isItemAffected(item, color))
	
	for color in CoreConst.Affected.values():
		if newItemIsAffected[color]:
			currentAffectedItems[color][item] = true
			onAffectedItemAdded(item, color)


# 对齐 Item.gd:1446-1452
func onItemRemoved(item):
	for color in CoreConst.Affected.values():
		currentAffectedItems[color].erase(item)
		if canAffectDraggedItem(item, color):
			onAffectedItemRemoved(item, color)


# ── 格子几何查询 ──

# 对齐 Item.gd:1057-1065
func getNumOccupiedCells():
	return collisionCells.size()


func getNumBagCells():
	return extensionCells.size()


func getNumCells():
	return getNumOccupiedCells() + getNumBagCells()


# 对齐 Item.gd:5192-5211
func getSizeInCells() -> Vector2:
	var topLeft = Vector2(100, 100)
	var bottomRight = Vector2( - 100, - 100)
	var cells = getCollisionCells()
	if cells.empty():
		return Vector2.ZERO
	
	for cell in cells:
		if cell.x < topLeft.x:
			topLeft.x = cell.x
		if cell.y < topLeft.y:
			topLeft.y = cell.y
		
		if cell.x > bottomRight.x:
			bottomRight.x = cell.x
		if cell.y > bottomRight.y:
			bottomRight.y = cell.y
	
	return bottomRight - topLeft + Vector2(1, 1)


# 对齐 Item.gd:1247-1254
func getTopLeftCell() -> Vector2:
	var topLeft = Vector2(INF, INF)
	for cell in occupiedCells:
		topLeft.x = min(cell.x, topLeft.x)
		topLeft.y = min(cell.y, topLeft.y)
	return topLeft


# 对齐 Item.gd:1071-1100。返回值 [归一化后的占格, 格偏移]。原版的格偏移是
# 全局坐标（collisionMap.map_to_world(minimum) + position + (40,40)），只用消费方是
# ItemLibrary 的展示摆放（Interface/ItemLibrary/ItemLibrary.gd:209/409）——不在战斗
# 判定路径上，内核返回 Vector2.ZERO 占位。
func getNormalizedCollisionCells() -> Array:
	var cells
	if isBag():
		cells = getExtensionCells().duplicate()
	else:
		cells = getCollisionCells().duplicate()
	
	var minimum = Vector2(100, 100)
	for cell in cells:
		if cell.y <= minimum.y:
			if cell.y < minimum.y:
				minimum.x = cell.x
			else:
				minimum.x = min(cell.x, minimum.x)
			minimum.y = cell.y
	
	for i in range(cells.size()):
		cells[i] = cells[i] - minimum
	
	return [cells, Vector2.ZERO]


# 对齐 Item.gd:5852-5853。★ 判定用：Gems/Gem.gd:252 `if not fusing and canCombine()`
# 决定宝石合并流程是否继续，故必须忠实返回 placed 而不是恒 false。
func canCombine() -> bool:
	return placed


# ── 行为脚本会调用、但内核无对应子系统的同签名占位 ──
# 判据：这些方法被 Items/*.gd **调用**（非覆写），若内核不提供签名，行为脚本接入时
# 会直接报 "Nonexistent function"。逐条给出剥离依据：

# 对齐 Item.gd:4248-4254（商店/换装的「替换中」标志 + tooltip/拾取开关）→ 无战斗影响
var replacementPending := false


func prepareReplacement():
	replacementPending = true


func finishReplacement():
	replacementPending = false


# 对齐 Item.gd:5708-5725：把生成的物品放进第一个空格（宝箱类物品用）。
# 依赖 Inventory.orientAndAddItem / unlockCombining / Game.itemsAreFusing（均为
# 商店·制作路径）→ 内核不做物品生成。消费方：BoxofRiches.gd:18。
func placeGeneratedItem(item, candidateCells):
	pass


# 对齐 Item.gd:2893-（tween 位移）。消费方：ChessPiece.gd:95、ChessBoard 棋子摆放
# 等纯表现调用 → 空实现（位移不改变任何战斗数值）。
func moveTo(fromPos, newPos, duration = 0.2, transitionType = null):
	pass


# 对齐 Item.gd:1457 区间的 z_index 复位。消费方：Bag.gd:80 → 视觉层序 → 走钩子。
func resetZ():
	ctx.hooks.resetZ(self)


# 对齐 Item.gd:1363-1365：商店 gate item 掷骰后交给 shopSceneNode → 商店路径 → 空实现。
func onGateItemRoll():
	pass


# 对齐 Item.gd:2251 附近的描述文本计数器（Util.insertCounter 本地化）→ 表现 → 返回原串。
# 消费方：Bewitchment.gd:29（在 getDescription 里）。
func insertCounter(descr, paramName, amount):
	return descr


# 对齐 Item.gd:6348-6351（Bag 覆写用；基类不存在则此处给同签名占位，供 Bag.gd 覆写链）。
func queue_free():
	pass


func shift(direction):
	pass


func onBought():
	pass


func onSold():
	pass


# 对齐 Item.gd:1530-1531（基类恒 true，由物品行为覆写以拒绝被重新纳入受影响集）
func reactToItemTypeChange(item) -> bool:
	if _hasBehaviorMethod("reactToItemTypeChange"):
		return CoreUtil.truth(_behavior_call("reactToItemTypeChange", [item]))
	return true


# 对齐 Item.gd:1457-1480。动态类型变化（MagicRing / addDynamicType / removeDynamicType）
# 后重建「受影响物品集」：先问行为要不要重算，再逐色增删并触发成对回调。
# 原版由 Inventory 的 item_type_changed 信号驱动（Item.gd:1333 在装备时连接），
# 内核改为 CoreGrid 直接逐件派发（次序 = 加入背包次序，与信号连接次序一致）。
func onItemTypeChanged(item):
	var canAddAgain = reactToItemTypeChange(item)
	
	if not canAddAgain:
		return
	
	var addedToAffected = {}
	for color in CoreConst.Affected.values():
		addedToAffected[color] = false
		
		if item in currentAffectedItems[color]:
			if not canAffect_color(item, color):
				currentAffectedItems[color].erase(item)
				onAffectedItemRemoved(item, color)
		elif item in getAffectedItems(color):
			currentAffectedItems[color][item] = true
			onAffectedItemAdded(item, color)
			addedToAffected[color] = true
	
	if item.placedByPlayer:
		ctx.hooks.playAffectedPlacedAnimation(self, addedToAffected)


# 对齐 Item.gd:2352-2353
func getRelatedItems() -> Array:
	return descriptor.gatedItems


# 对齐 Item.gd:5798-5802 → ItemBook.gd:294-303（本方）/ :390-391（对手）。
# 原版在全局索引 ownableItems[descriptor] 上按**描述符**数，并筛 ownerType：
#   本方   —— `(placed and ownerType == PlayerInventory) or ownerType == Socket`
#   对手侧 —— `opponentItems[descriptor].size()`，**不做任何过滤**
# ★ 本方必须带 `placed`：这正是「Placed」与 `countAllInInventoryOfType` 的区别，
#   漏掉它两者会恒等（该分支由 tools/run_gd_core.py 闸门 7 的 placed 用例把守）。
# ★ 对手侧不加 ownerType 过滤：原版取的就是「对手格子里的该描述符物品」（含宝石），
#   加过滤会把对手的 Socket 宝石漏掉。
# ★ 描述符比较用 `==`（引用相等），与 ItemBook 的 Dictionary 键一致 ——
#   要求装配层对同一物品类型复用同一个 CoreItemData 实例（原版共享一份 .tres），
#   内核侧的入口是 CoreItemBook.getDescriptor() / register()。
func countAllPlacedOfType(descr) -> int:
	var count = 0
	if isOwnedByOpponent():
		if ctx.opponent == null:
			return 0
		for item in ctx.opponent.inventory.getItemsAndGems():
			if item != null and item.descriptor == descr:
				count += 1
		return count
	
	if ctx.player != null:
		for item in ctx.player.inventory.getItemsAndGems():
			if item == null or item.descriptor != descr:
				continue
			if item.ownerType == CoreConst.Owner.Socket:
				count += 1
			elif (item.placed
					and item.ownerType == CoreConst.Owner.PlayerInventory):
				count += 1
	return count


# 对齐 Item.gd:3066-3085：被自身占格压住的袋子按「描述符」归并计数
func getTouchedBagsCounted():
	if isBag() or not placed:
		return null
	var touchedBags = inventory.getBagsInCells(occupiedCells)
	var bagCounter = {}
	for bag in touchedBags:
		var found = false
		for countedBag in bagCounter:
			if countedBag.descriptor == bag.descriptor:
				bagCounter[countedBag] += bag.getBagMultiplicity(self)
				found = true
				break
		if not found:
			bagCounter[bag] = bag.getBagMultiplicity(self)
	return bagCounter


# 对齐 Item.gd:1243-1244（全局像素高度范围；内核无像素层 → 以格空间的上下边界等价表示）
func getHeightRange() -> Vector2:
	return Vector2(getTopLeftCell().y, getTopLeftCell().y + getSizeInCells().y - 1)


# 对齐 Item.gd:628-（_ready 里 call_deferred 触发的一次性装配回调）。
# ★ 时机说明：原版由 SceneTree 在**当帧空闲末**执行，晚于 _ready、早于战斗装配。
#   内核无场景树，交由装配层在「物品加入背包后、prepare 前」调用；
#   行为脚本未实现该方法时为空操作（基类为空），故缺失不会改变判定。
func ready_deferred():
	if _hasBehaviorMethod("ready_deferred"):
		_behavior_call("ready_deferred")


# ─────────────────── 朝向（对齐 Item.gd:2037-2054 的旋转↔朝向换算） ───────────────────
# 原版没有 `faceDirection` 字段的直接来源：它是 `rotation`（Node2D 属性 + tween 插值）
# 换算出来的。内核无节点、无 tween，故把 faceDirection 作为**权威字段**、rotation 作为
# 由它导出的派生值：rotation = faceDirection * PI/2 恒成立（见 setFaceDirectionInstant）。
# 数值上与原版一致：getFaceDirection() 在原版的公式 (int((2*rotation)/PI + 2.25PI)+5)%4
# 当 rotation = fd*PI/2 时恒等于 fd（(int(fd+7.0686)+5)%4 = (fd+12)%4 = fd）。
#
# 战斗期该字段只读：rotateLeft/rotateRight 只由玩家按键（Util.isActionJustPressed）触发，
# 战斗状态不可达。战斗期的回调只有 setFaceDirectionInstant（放置/存档载入）。
var faceDirection: int = CoreConst.FaceDirection.UP
var rotation: float = 0.0


# 对齐 Item.gd:2037-2038
func rotationFromFaceDirection(_faceDirection):
	return _faceDirection * PI * 0.5


# 对齐 Item.gd:2053-2054
func getFaceDirection():
	return (int((2 * rotation) / PI + 2.25 * PI) + 5) % 4


# 对齐 Item.gd:2040-2041（全局朝向；内核无父子旋转叠加 → 与局部朝向同值）
func getGlobalFaceDirection():
	return getFaceDirection()


# 对齐 Item.gd:2043-2047。原版首行 Util.finishTween(rotationTween) 是结束插值动画
# （表现）→ 剥离；其余三行逐字保留。
func setFaceDirectionInstant(_faceDirection):
	faceDirection = _faceDirection
	rotation = rotationFromFaceDirection(faceDirection)


# 对齐 Item.gd:2049-2050
func setRotation(_rotation):
	rotation = _rotation


# 对齐 Item.gd:5686-5689（BlackRook 用它给背包内全部可强化物品改暴击率）
func changeAllItemsCritRate(amount):
	for item in inventory.getItems():
		if item.canBeEmpowered():
			item.changeCritChancePercent(amount)


# ── 剥离但**必须保留签名**的方法：被物品行为（Items/*.gd）直接调用 ──
# 这些方法本体只做表现（播动画/更新 shader/粒子/重绘预览），剥离后做成同签名空实现，
# 使行为脚本调用它们时行为与原版一致（原版这些调用同样不改变任何战斗数值）。
# 判据：函数体只触碰 sprite / animation / particles / material / tooltip / 预览格，
# 不读写任何 buff / stat / 冷却 / 伤害 —— 逐条可在源码行号上核对。

# 对齐 Item.gd:4511-4516（仅 animation.play，按 consumed 选动画名）
func miniActivate():
	ctx.hooks.playActivationAnimation(
		self, "MiniActivate_consumed" if consumed else "MiniActivate", false)


# 对齐 Item.gd:1857-1875 区间的预览重绘调用点
func previewCellCollision():
	ctx.hooks.previewCellCollision(self)


# 对齐 Item.gd:2124-2131（预览格着色）
func previewCells():
	ctx.hooks.previewCells(self)


# 对齐 Item.gd:2211（预览是否能影响）
func previewCanAffect():
	ctx.hooks.previewCanAffect(self)


# 对齐 Item.gd:1963-1996。rotateRight/Left 的入口是玩家按键（Item.gd:1843-1856 的
# _input），rotateTo 只是 tween 旋转 + 重算 faceDirection。内核把它们做成
# 「更新 faceDirection + 通知表现层」：不接按键、不做插值，但字段语义与原版一致，
# 以便行为脚本（Scale/SpintoWin 覆写 rotateTo 更新计数器/配色）能正常调用。
func rotateRight():
	faceDirection = (faceDirection + 1) % CoreConst.FaceDirection.size()
	setFaceDirectionInstant(faceDirection)
	ctx.hooks.onItemRotated(self)


func rotateLeft():
	faceDirection = (faceDirection - 1 + CoreConst.FaceDirection.size()) % CoreConst.FaceDirection.size()
	setFaceDirectionInstant(faceDirection)
	ctx.hooks.onItemRotated(self)


func rotateTo(targetRotation, duration = 0.15):
	# 原版：先取当前 sprite 朝向存 faceDirection，再把节点旋转到 target，
	# 最后 tween 把 sprite 从旧角度插值回来（视觉回弹）。内核保留「朝向 = 节点旋转的
	# 量化值」这一结果，丢掉的只有插值过程。
	faceDirection = getGlobalFaceDirection()
	rotation = targetRotation
	faceDirection = getGlobalFaceDirection()
	ctx.hooks.onItemRotated(self)


func rotateToDeferred(targetRotation, duration = 0.15):
	ctx.defer(self, "rotateTo", [targetRotation, duration])


# 对齐 Item.gd:1994-1995
func setFaceDirection(_faceDirection):
	rotateTo(_faceDirection * PI * 0.5)


# 对齐 Item.gd:2016-2029 的尾巴：拖拽中「袋内物品」的朝向修正（纯拖拽表现，
# 操作的是 insideItems 子节点的 rotation，不参与任何战斗判定）→ 剥离为空实现。
func correctInsideItemFacedirection():
	pass


# 对齐 Item.gd:936-947：袋子效果 tooltip 文本组装（走 Util.tra 本地化）
# → 剥离为空串。唯一消费方是 Interface/Tooltips/ItemTooltip.gd:241。
func getBagEffect(number):
	return ""


# 对齐 Item.gd:3024-3035 / 3047-3057：背包宝石的**存档序列化**（ItemBook.getGemIndex +
# 逐宝石朝向/锁定），唯一消费方是 Game.gd:1382/1407/1423 的 saveRunState → 剥离。
# 运行期宝石走 gems 数组 + CoreGem（见 CoreItem 的宝石段），不经这两个方法。
func getGemData():
	return []


func setGemData(gemData):
	pass


# 对齐 Item.gd:4476+：战斗日志**回放**时把编码后的冷却状态重建回物品
# （唯一调用点在 Core/CombatLog.gd:546 的回放路径）→ 剥离。实时战斗不需要它：
# 实时路径的冷却是 Item 自身按物理帧推进的（见 CoreItem 的冷却推进段）。
func reconstructCooldown(encodedCd, timeSinceEntry):
	pass


# 对齐 Item.gd:6536-6555：融合/配方绑定扫描（bondedIngredients + 绑定可视化）。
# 配方系统整体剥离；全仓库该方法**无调用点**（原版亦为死代码）→ 保留签名为空实现。
func findBondsWithAffectedItems():
	pass


# 对齐 Item.gd:5284-5296（把冷却进度按朝向折算给 shader；纯表现）
func rotateProgress(progress: float):
	match faceDirection:
		CoreConst.FaceDirection.UP:
			progress = 1.0 - progress
		CoreConst.FaceDirection.RIGHT:
			progress = 1.0 - progress
		CoreConst.FaceDirection.LEFT:
			progress = - progress
		CoreConst.FaceDirection.DOWN:
			progress = - progress
	return progress


# 对齐 Item.gd:726-728（从 TileMap 读碰撞/扩展格并缓存）。内核的同类数据由装配层
# 经 battle_items.json 的 grid.collision_cells / 袋格直接注入，且原版只在 _ready
# 调用一次（旋转不重算）——故此处保留为幂等占位，不覆盖已注入的数据。
func cacheCollisionCells():
	pass


# 对齐 Item.gd:6153-6158（制作/配方候选扫描）。配方系统整体剥离 → 恒 false。
func isBaseItemForShopItem(item) -> bool:
	return false


# 对齐 Item.gd:4511 一族的回放动画入口（CombatLog.gd:583 在回放事件时触发）
func activateFromEvent(event):
	ctx.hooks.playActivationAnimation(self, "Activate", false)


# ── 邻接 ──

# 对齐 Item.gd:5815-5822
func getNeighborItemsAndGems():
	var neighbors = inventory.getAdjacentItems(self)
	neighbors.append_array(getGemsNoNull())
	for neighbor in neighbors:
		var neighborGems = neighbor.getGemsNoNull()
		neighbors.append_array(neighborGems)
	return neighbors


# 对齐 Item.gd:3059-3063
func getTouchedBags():
	if isBag() or not placed:
		return []
	else:
		return inventory.getBagsInCells(occupiedCells)


# 对齐 Item.gd:5837-5851。isBusy 属制作系统（剥离后恒 false）→ 结果恒为空。
func getBusyNeighbors():
	var busyNeighbors = []
	
	for neighbor in getNeighborItemsAndGems():
		if neighbor.isBusy():
			busyNeighbors.push_back(neighbor)
	
	for bag in getTouchedBags():
		if bag.isBusy():
			busyNeighbors.push_back(bag)
	
	return busyNeighbors


# 对齐 Item.gd:5823-5836。同上，制作系统剥离后恒为空。
func getCraftableNeighbors():
	var craftableNeighbors = []
	
	for neighbor in getNeighborItemsAndGems():
		if neighbor.isAvailableForCrafting():
			craftableNeighbors.push_back(neighbor)
	
	for bag in getTouchedBags():
		if bag.isAvailableForCrafting():
			craftableNeighbors.push_back(bag)
	
	return craftableNeighbors


# 对齐 Item.gd:5865-5871（制作系统剥离后恒 false）
func isAvailableForCrafting():
	return false


# ─────────────────────── 其余战斗查询（对齐 4242-4247, 6510-6520） ───────────────────────

# 对齐 Item.gd:4242-4247
func getAffectedGoldValue() -> int:
	var gold = 0
	for item in getAffectedItems_nocache():
		gold += item.getPrice()
	return gold


# 对齐 Item.gd:5783-5785 之外的 isShowCaseItem 见上；
# 对齐 Item.gd:6510-6520
func countTypes(ofItems: Array) -> Dictionary:
	var typesDict = {}
	for type in CoreConst.Type:
		typesDict[CoreConst.Type[type]] = 0
	
	for item in ofItems:
		for type in item.getTypes():
			typesDict[type] += 1
	
	return typesDict


# 对齐 Item.gd:2881-2883。拾取方向属背包交互，内核恒定（无拾取）→ true，
# 使依赖它的形状判定读到「与拾取同向」这一原版常态值。
func hasSameOrientationAsPickup() -> bool:
	return true


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


# ─────────────────────── 战斗连接（对齐 Item.gd:5694-5705） ───────────────────────
# ★ 修正记录：本类早期版本把 connectForCombat 误写成 0 参数的钩子转发
#   （`connectForCombat()` → `onConnectForCombat()`），与原版语义不符。
#   原版签名是 `connectForCombat(emitter, signalName, methodName, binds = [])`，
#   直接转发到 EventBus.connectEvent —— 物品行为脚本用它把角色的 buff 信号
#   挂到自己的回调上（connectToCharacterBuffs 等）。已按原版重写。

func connectForCombat(emitter, signalName, methodName, binds = []):
	ctx.bus.connectEvent(emitter, signalName, self, methodName)


# 对齐 Item.gd:5697-5701。原版用 Godot 信号（emitter.connect），内核中等价于
# EventBus 的定向连接；destroy() 原版走 Util.tryDisconnect，而内核的连接表在
# 战斗收尾由 disconnectAll() 整体清空 —— 两者发生在同一生命周期点
# （CoreCombat.combatEndDeferred 先 disconnectAll、再 item.combatEnd），故等价。
func connectForCombat_signal(emitter, signalName, methodName, binds = []):
	var newConnection = CoreSignalConnection.new(emitter, signalName, 
		self, methodName, binds)
	combatConnections.push_back(newConnection)


# 对齐 Item.gd:5702-5705
func disconnectCombat():
	for connection in combatConnections:
		connection.destroy()
	combatConnections.clear()


class CoreSignalConnection extends Reference:
	var emitter
	var signalName
	var receiver
	var methodName
	
	func _init(_emitter, _signalName, _receiver, _methodName, binds = []):
		emitter = _emitter
		signalName = _signalName
		receiver = _receiver
		methodName = _methodName
		receiver.ctx.bus.connectEvent(emitter, signalName, receiver, methodName)
	
	func destroy():
		pass



# 行为存在性探测（两级派发，见文件头部 SELF_BEHAVIOR_METHODS 的说明）
func _hasBehaviorMethod(methodName: String) -> bool:
	if _behavior != null:
		return _behavior.hasBehavior(self, methodName)
	return methodName in SELF_BEHAVIOR_METHODS and has_method(methodName)


# 行为接缝派发：**必须回传返回值**——canAffect / getTriggerPriority / onCombatStart
# 等虚方法的返回值直接参与判定，丢掉返回值不会报错、只会静默判否（曾导致全部联动物品
# 失效）。装配方契约：behavior.callBehavior(item, methodName, args) 返回该方法的原值，
# 未实现的方法返回 null。
#
# ★ 回落分支用 `callv`（动态调用）而非直接写方法名：onCombatStart / onDealtDamage
#   这类回调**基类并没有定义**，写死方法名会解析失败。原版同样是动态语义
#   （`me = self` 未标注类型 → Item.gd:3400 `me.onCombatStart()`）。
# ★ 回落名单与 `_hasBehaviorMethod` 共用，且只含基类未定义的名字，杜绝自我递归。
func _behavior_call(methodName: String, args: Array = []):
	if _behavior != null:
		return _behavior.callBehavior(self, methodName, args)
	if methodName in SELF_BEHAVIOR_METHODS and has_method(methodName):
		return callv(methodName, args)
	return null
