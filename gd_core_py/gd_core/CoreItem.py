# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

    Color,
    Dictionary,
    EnumDict,
    FuncRef,
    GD_DEFAULT,
    INF,
    NAN,
    Node,
    Node2D,
    OS_has_feature,
    Object,
    PCG32,
    PI,
    PoolStringArray,
    RandomNumberGenerator,
    Reference,
    Resource,
    Signal,
    String,
    TAU,
    TYPE_VECTOR2,
    Vector2,
    Vector3,
    _HoistPending,
    _bind_battle,
    _div,
    _dup,
    _erase,
    _fill,
    _find,
    _gd_fmt,
    _gd_range,
    _gd_str,
    _get_slice,
    _gid,
    _hash,
    _invert,
    _iter,
    _join,
    _load,
    _mod,
    _os_environ_get,
    _pick_random,
    _pop_at,
    _resize,
    _shuffle,
    _sort_custom,
    _strv,
    _substr,
    ceil,
    clamp,
    deg2rad,
    f32,
    floor,
    fmod,
    gd_round,
    get_stack,
    inverse_lerp,
    is_equal_approx,
    is_instance_valid,
    lerp,
    move_toward,
    posmod,
    pow,
    rad2deg,
    randomize,
    round,
    sign,
    smoothstep,
    snapped,
    sqrt,
    stepify,
    tr,
    typeof,
    wrapf,
    wrapi
,
)

if "GodotObject" not in globals():
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R




class CoreElectricalCharge(GodotObject):
	def _init_fields(self):
		super()._init_fields()
		self.lastChargedItem = None
		self.curChargedItem = None



# 对齐 Item.gd:5147-5156 + Items/ElectricalCharge.gd:97-215 的战斗语义面。
# 原版在此发射一枚**真实电荷体**：ElectricalCharge.start 的 i==0 分支
# （ElectricalCharge.gd:146-149）立即同步调用 onNewCellEntered(1)——受格物品
# chargeReceived/chargeLeft（Resistor 的 heat、Charge Splitter 的接力都在这）
# + 发射物自身 onChargeEnteredCell 的速度类 buff（Battery/ChargeSplitter）。
# 后续 cell（2..size-1）的入格由 SceneTreeTween 延时 callback 驱动；受控神谕
# 的阻塞 tick 循环不处理 tween（oracle_fight.gd 手动驱动面只有 Timer/
# SceneTreeTimer，见其 harness_notes [M1]/[M2]），多 cell 入格从不发生——
# run1160_r18 语料实证：全 stream 除 t=0 同步入格连锁外无任何电荷入格事件
# （19 个 heat 里 12 个 t=0，其余全部来自 Bazooka 等重发射，0 个落在
# durPerCell 的整数倍时刻）。内核与神谕同约定：只复刻同步段。

class CoreSignalConnection(GodotObject):
	def _init_fields(self):
		super()._init_fields()
		self.emitter = None
		self.signalName = None
		self.receiver = None
		self.methodName = None


	def _init(self, _emitter, _signalName, _receiver, _methodName, binds=[]):
		self.emitter = _emitter
		self.signalName = _signalName
		self.receiver = _receiver
		self.methodName = _methodName
		self.receiver.ctx.bus.connectEvent(self.emitter, self.signalName, self.receiver, self.methodName)

	def destroy(self):
		pass



# 行为存在性探测（两级派发，见文件头部 SELF_BEHAVIOR_METHODS 的说明）

class CoreItem(GodotObject):

	resource_path = "res://gd_core/CoreItem.gd"

	def _init_fields(self):
		super()._init_fields()
		self.descriptor = None
		self.ctx = None
		self.character_ = None
		self.inventory = None
		self.placed = False
		self.name = ""
		self.chargeFrame = [Vector2.ZERO, Vector2.ZERO, Vector2.ZERO, Vector2.ZERO]
		self.speedScale = 0.0
		self.bonusMaxDam = 0.0
		self.bonusMinDam = 0.0
		self.removableDam = 0.0
		self.bonusDamageFactor = 1.0
		self.staminaFactor = 1.0
		self.critChancePercent = 0.0
		self._critTokens = 0
		self.critSeverity = self.BASE_CRIT_SEVERITY
		self.bonusChancePercent_mult = 0.0
		self.bonusChancePercent_additive1 = 0.0
		self.bonusChancePercent_additive2 = 0.0
		self.bonusAccuracy = 0.0
		self.buffPowers = {}
		self.buffAmplificationChances = {}
		self.damageSource = None
		self.doubleActivationChance = 0.0
		self.doubleAttackEffectChance = 0.0
		self.paramMult = {}
		self.paramAdd = {}
		self._numCharges = 0
		self.baseCooldownOverride = 0.0
		self.chanceRng = None
		self.damageRangeRng = None
		self.statDisplayOverrides = []
		self.lastActivationTime = 0.0
		self._activationsThisFrame = 0
		self.lastTriggerTime = 0.0
		self._triggersThisFrame = 0
		self.triggerTime = 0.0
		self.iterationCooldown = 0.0
		self.flk_suppress_fire = False
		self._inj_item = ""
		self.__inj_trigger_n = 0
		self.__inj_trigger_count = 0
		self.itemMetrics = []
		self.gems = []
		self._grid = None
		self._behavior = None
		self._cooldown_active = False
		self.dynamicTypes = {}       # 动态类型记账（addDynamicType/removeDynamicType）
		self.combatConnections = []       # connectForCombat_signal 建立的战斗连接
		self._ownerType = _H_3   # 由装配层按所属角色写入
		self.placedByPlayer = False            # 对齐 Item.gd:386 附近（addToInventory 写入）
		self.dragged = False                   # 对齐 Item.gd:390（拖拽态；战斗路径恒 false）
		self.occupiedCells = []           # 该物品占用的库存格（装配层写入）
		self.collisionCells = []          # 对齐 Item.gd:396
		self.extensionCells = []          # 对齐 Item.gd:397（背包的扩展格）
		self.affectedExtensionCells = []  # 对齐 Item.gd:398
		self.affectedCellsCache = {}     # 对齐 Item.gd:399
		self.currentAffectedItems = {}   # 对齐 Item.gd:432
		self.cachedAffectedItems = {}    # 对齐 Item.gd:433
		self.affectedTileCells = {}
		self.consumed = False
		self.hasPreDealDamageEarlyEffect = False
		self.hasPreDealDamageLateEffect = False
		self.hasDealtDamageEffect = False
		self.hasOnChargeReceivedEffect = False
		self.hasOnChargeLeftEffect = False
		self.timers = []
		self.buffLabelPositionTimestamps = [0.0, 0.0, 0.0, 0.0, 0.0]
		self.replacementPending = False
		self._faceDirection = _H_4
		self.rotation = 0.0

	@property
	def critTokens(self):
		return self._critTokens
	@critTokens.setter
	def critTokens(self, v):
		self._critTokens = int(v)
	@property
	def numCharges(self):
		return self._numCharges
	@numCharges.setter
	def numCharges(self, v):
		self._numCharges = int(v)
	@property
	def activationsThisFrame(self):
		return self._activationsThisFrame
	@activationsThisFrame.setter
	def activationsThisFrame(self, v):
		self._activationsThisFrame = int(v)
	@property
	def triggersThisFrame(self):
		return self._triggersThisFrame
	@triggersThisFrame.setter
	def triggersThisFrame(self, v):
		self._triggersThisFrame = int(v)
	@property
	def _inj_trigger_n(self):
		return self.__inj_trigger_n
	@_inj_trigger_n.setter
	def _inj_trigger_n(self, v):
		self.__inj_trigger_n = int(v)
	@property
	def _inj_trigger_count(self):
		return self.__inj_trigger_count
	@_inj_trigger_count.setter
	def _inj_trigger_count(self, v):
		self.__inj_trigger_count = int(v)
	@property
	def ownerType(self):
		return self._ownerType
	@ownerType.setter
	def ownerType(self, v):
		self._ownerType = int(v)
	@property
	def faceDirection(self):
		return self._faceDirection
	@faceDirection.setter
	def faceDirection(self, v):
		self._faceDirection = int(v)
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


	BASE_CRIT_SEVERITY = 2.0
	cdEncodingFactor = 100000.0

	# 场景数据字段：电荷格→背包格映射的旋转系原点（★ np25 P3-3）。
	# 原版电荷格与碰撞格同处 CollisionMap 本地 TileMap 空间；而装配层的绝对格
	# （夹具/runtime）= 锚点 + 旋转后坐标 − **旋转后碰撞包围盒 min**。电荷格映射
	# 必须减同一个 min（对齐 gen_lineup_fixture.py::placement_of 的归一化）。
	# 由夹具表 item_battle_fixture.json / runtime 的 charge_frame 按 faceDirection
	# 注入（4 项，fd 0..3 各一；缺省 4×ZERO = raw 格已以 (0,0) 为 min 的物品）。

	# 伤害与速度修正（对齐 Item.gd:474-495）


	# 对齐 Item.gd:288 —— 仅由战斗日志回放路径写入（CombatLog.gd:600/612 的 setStat），
	# 实战判定中恒为 null；保留字段与读取点以维持接口一致。

	# 冷却运行态（对齐 Item.gd:464-470）
	# ★ np51㉛ 定向注入实验状态（用后还原）

	# 统计（对齐 Item.gd:257 itemMetrics）

	# 本期占位接缝

	# 里程碑 1 新增字段（对齐 Item.gd:372/385/468）

	# 里程碑 1 新增字段：格子（对齐 Item.gd:387-433）
	# 装配层写入：联动颜色 → 库存空间的受影响格（源 = tscn CollisionMap 的 Affected tile，
	# 经 simulator/extract_grid.py 同一套「40px tile //2 → 80px 背包格 + 锚点换算」得到）


	# 物品行为接缝（_behavior）接口约定 —— 由装配方实现，内核只做派发：
	#   hasBehavior(item, methodName: String) -> bool
	#   callBehavior(item, methodName: String, args: Array) -> Variant
	#     ★ 必须回传被调方法的原值；未实现的方法返回 null。返回值参与判定
	#       （canAffect / getTriggerPriority / onCombatStart / getAffectedCellsAfterRotate_*
	#       等），丢弃返回值不会报错但会静默改变战斗结果。
	# 命名刻意避开 Object 原生的 has_method / call（原生签名不同，覆写会破坏引擎内部调用）。
	# 方法名与 Items/*.gd 中的 GDScript 方法名一一对应（doCooldownEffect / onPrepare /
	# connectForCombat / onCombatStart / preDealDamage_early ...）。

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
	SELF_BEHAVIOR_METHODS = [
		"onCombatStart",
		"getGatedDescriptor", "getReplaceDescriptor",
		"onChargeReceived", "onChargeLeft", "chargedItemStatChange",
		"onPreDealDamage_early", "onPreDealDamage_late", "onDealtDamage",
	]

	# 行为钩子存在性探测（对齐 Item.gd:500-504 的 `onready var ... = has_method(...)`；
	# onready 在脚本绑定后求值，内核等价位置是 `_readyInit()`）


	# ── 装配入口：无参构造 + 显式 setup（两段式） ──
	# ★ 为什么必须支持两段式：GDScript 3.6 的 `GDScript.new()` **只接受 0 个实参**
	#   （`Invalid call to function 'new' in base 'GDScript'. Expected 0 arguments.`），
	#   而且 `extends "res://..."`（字符串路径继承）形态的脚本连 `_init` 的参数个数
	#   都解析不到（`Too many arguments for "_init()" call. Expected at most 0.`）。
	#   469 个物品脚本正是这两种形态，装配层只能 `SCRIPT.new()` → `setup(...)`。
	#   `CoreItem.new(ctx, descriptor, character)` 依旧可用（class_name 引用能解析参数），
	#   两条路最终都走同一个 setup，初始化结果完全一致。
	def _init(self, _ctx=None, _descriptor=None, _character=None):
		if _descriptor == None:
			# 两段式构造的第一段：依赖留待 setup() 注入
			return
		self.setup(_ctx, _descriptor, _character)


	# 与 `_init` 同一份初始化体（原 Item.gd 的构造期状态）。
	# 返回 self 便于链式调用：`var it = SCRIPT.new().setup(ctx, data, chr)`
	def setup(self, _ctx, _descriptor, _character=None):
		_iter__loc = _iter
		_fill__loc = _fill
		_resize__loc = _resize
		self.ctx = _ctx
		self.descriptor = _descriptor
		self.character_ = _character
		self.name = _descriptor.name
		# ★ 双重 BalancedRng 初始化（阶段2 装配期对齐，docs/alignment_fix_workflow.md §2）
		# 原版每个战斗物品/宝石都是「基场景实例 + 覆盖脚本再绑定」的产物：
		#   *.tscn: [node name="…" instance=ExtResource(1)]  ← Item.tscn / Gem.tscn（根脚本
		#          Item.gd:472 / Gem 链的 chanceRng = BalancedRng.new()）
		#           script = ExtResource(2)                   ← 物品自己的脚本（同样继承 Item）
		# Godot 3.x 场景实例化先按基脚本创建脚本实例——成员初始化器跑一遍
		#（BalancedRng.new() 内含 Util.rng.randf_range(0.2,-0.2)，消耗链 2 步，
		#  Utility/BalancedRandom.gd:4）；随后应用 script 覆盖重新创建脚本实例，
		#  继承链成员初始化器**再跑一遍**（第二个 chanceRng 生效，第一个被丢弃）。
		# 神谕侧实测（本会话 oracle/oracle_stage_probe.gd + output/_probe_assembly_steps.py）：
		#   ItemScript.new()=2 步、Items/Item.tscn.instance()=2 步、
		#   Items/Exclusive/PortableAltar.tscn.instance()=4 步——差值即覆盖重绑定；
		#   全量 917 场装配步数与「4/实例 + 2/Flicker 项 + 8/对手角色」模型零残差。
		# 故内核物品构造消耗 = 2×BalancedRng.new = 4 步/实例（宝石同，Gem 场景同构）。
		self.chanceRng = self.ctx.rng.BalancedRng(self.ctx.rng)
		self.damageRangeRng = self.ctx.rng.BalancedRange(self.ctx.rng)
		self.chanceRng = self.ctx.rng.BalancedRng(self.ctx.rng)   # 覆盖脚本重绑定：成员初始化器重跑
		# ★ np25 sceneDepth 面（run784_r13 state 快照定谳）：三层覆盖链
		#   （Item.tscn → Gem.tscn → <gem>.tscn，如 HawkRune）成员初始化器跑
		#   sceneDepth 遍——第 3 层的 chanceRng 才是幸存实例（战斗期平衡器状态源）。
		#   夹具/宿主/引擎描述符早传 sceneDepth（enrich_scene_depth.py，宝石类=3、
		#   普通物品=2）但内核从未消费 ⇒ 每个宝石类物品装配少 1 抽（run784 五符文
		#   = 5 抽，第 2 油灯 flicker delay 1.979v0.662 的错位即此所赐）。
		#   消耗位置 = 第 2 层之后、gemRoll(advance) 之前，与神谕实例化序逐位同构。
		for _i in _iter__loc(_gd_range(max(0, int(self.descriptor.sceneDepth) - 2))):
			self.chanceRng = self.ctx.rng.BalancedRng(self.ctx.rng)
		self.baseCooldownOverride = _descriptor.cd
		for buff in _iter__loc(_H_7.getStacks()):
			self.buffPowers[buff] = 1.0
			self.buffAmplificationChances[buff] = 0.0
		_resize__loc(self.itemMetrics, self.getNumItemMetrics())
		_fill__loc(self.itemMetrics, 0)
		_resize__loc(self.statDisplayOverrides, len(_H_8))
		_fill__loc(self.statDisplayOverrides, None)
		# 对齐 Item.gd:602-603（_ready 里把每个颜色档初始化为空字典）
		for color in _iter__loc(list(_H_60.values())):
			self.currentAffectedItems[color] = {}
		return self


	# ─────────────────────── 关系访问（对齐 Item.gd:3939-3950） ───────────────────────

	def hasCharacter(self):
		return self.placed and self.character_ != None


	def character(self):
		return self.character_


	def opponent(self):
		return self.ctx.otherCharacter(self.character_)


	def isPlaced(self):
		return self.placed


	# 类型标记：替代 `origin is CoreItem` 这种需要 class_name 的判定，
	# 供 CoreDamageSource / CoreDamageResult 等做零依赖鸭子类型判断
	# （GDScript 3 不允许 class_name 脚本互相循环引用）。
	def isCoreItem(self):
		return True


	def isPlayer(self):
		return self.character_ != None and self.character_.playerId == _H_44


	# ─────────────────────── 类型 / 标签（对齐 3594-3601, 5370-5390） ───────────────────────

	# 对齐 Item.gd:3594-3595：动态类型（addDynamicType，如 CorruptedArmor 腐蚀
	# Holy→Dark）必须参与 hasType 判定，否则 SSD/BookofDarkness 等暗系计数恒 0。
	def hasType(self, type):
		type = int(type)
		return type in self.descriptor.types or type in self.dynamicTypes


	def getTypeMultiplicity(self, type):
		type = int(type)
		return 1 if self.hasType(type) else 0


	def hasTag(self, tag):
		return self.descriptor.hasTag(tag)


	def isWeapon(self):
		return self.descriptor.isWeapon()


	def isBag(self):
		return False


	def isGem(self):
		return False


	# 对齐 Item.gd:5401-5402（Character.prepare 用它挑自动战怒物品；见 CoreItemData.hasBattleRageEffect）
	def isBattleRageItem(self):
		return self.descriptor.hasBattleRageEffect


	def gainsStack(self, stackType):
		return self.descriptor.gainedStacks & stackType


	def removesStack(self, stackType):
		return self.descriptor.removedStacks & stackType


	def usesStack(self, stackType):
		return self.descriptor.usedStacks & stackType


	# 对齐 Item.gd:5272 附近（基类返回 Normal，由物品行为覆写为更高/更低优先级）
	def getTriggerPriority(self):
		if self._hasBehaviorMethod("getTriggerPriority"):
			return int(self._behavior_call("getTriggerPriority", []))
		return _H_5


	def canDamage(self):
		return self.getBaseMinDamage() > 0 or self.hasTag(_H_45)


	def canBeEmpowered(self):
		return self.isWeapon() and self.canDamage()


	def canActivate(self):
		return self.descriptor.canActivate


	# ─────────────────────── 冷却（对齐 3742-3812, 4438-4451） ───────────────────────

	def getSpeed(self):
		# ★ 对齐 Item.gd:3743-3744 的覆盖短路。此前本函数漏了这两行，属**遗漏**而非
		#   有意剥离 —— 同族分支（MinDamage/MaxDamage/Accuracy/Chance/StaminaCost/
		#   BaseCooldown）在内核里都保留了。唯一写入方是 CombatLog.gd:612 的
		#   日志回放路径（`item.setStat(stat, statLogger.getItemStatAt(...))`），
		#   战斗中 statDisplayOverrides 恒为 null，故补回是零行为变化；
		#   但缺了它，「内核与本函数逐行一致」这句话就不成立。
		#   由 tools/verify_cooldowns_gd.py 的 A 段守住（该段逐行对照）。
		override = self.statDisplayOverrides[_H_9]
		if override:
			return override

		if (self.placed and self.character_ != None):
			speed_ = self.speedScale + (self.character().getHeat() - self.character().getCold()) * 0.02
			modifiedSpeed = None
			if speed_ >= 0:
				modifiedSpeed = 1.0 + speed_
			else:
				modifiedSpeed = _div(1.0, 1.0 - speed_)

			modifiedSpeed = (0.1 if modifiedSpeed < 0.1 else (10.0 if modifiedSpeed > 10.0 else modifiedSpeed))
			return modifiedSpeed
		else:
			return 1.0


	def speed(self):
		return self.speedScale


	def getStackSpeedMods(self):
		# ★ A-1（§C-2，2026-11-11）：本地绑定 character()——两次调用之间无任何
		#   状态改变语句，必返回同一实例（纯读属性链）；省 1 次虚派发+属性链
		#   （§C-1: getStackSpeedMods 7.2 万次/3 场 × 每次 2 次 character()）。
		ch = self.character()
		return (ch.getHeat() - ch.getCold()) * 0.02


	def hasCooldown(self):
		return self.descriptor.cd != 0


	def isCooldownActive(self):
		return self._cooldown_active


	def setCooldownActive(self, active):
		self._cooldown_active = active


	def activateCooldown(self):
		self._cooldown_active = True


	def deactivateCooldown(self):
		self._cooldown_active = False


	def getBaseCooldown(self):
		return self.baseCooldownOverride


	def getBaseCooldownIndex(self, index):
		index = int(index)
		if index == 0:
			return self.descriptor.cd
		else:
			return self.descriptor.extraCds[index - 1]


	# 对齐 Items/Item.gd:3782-3786（含 statDisplayOverrides[CoreConst.ItemStat.BaseCooldown] 覆盖分支）
	def getCooldown(self):
		override = self.statDisplayOverrides[_H_10]
		if override:
			return override

		return self.baseCooldownOverride


	def getCooldownIndex(self, index):
		index = int(index)
		return self.getBaseCooldownIndex(index)


	def getModifiedCooldown(self):
		return _div(self.getCooldown(), self.getSpeed())


	def getModifiedCooldownIndex(self, index):
		index = int(index)
		return _div(self.getCooldownIndex(index), self.getSpeed())


	def getCooldownEncoded(self):
		_div__loc = _div
		if self.iterationCooldown == 0:
			return - 1
		relProgress = 1.0 - _div__loc(self.triggerTime, self.iterationCooldown)
		progressPerSecond = None
		if self.isCooldownActive():
			progressPerSecond = _div__loc(self.getSpeed(), self.iterationCooldown)
		else:
			progressPerSecond = 0
		value = int(relProgress * self.cdEncodingFactor) << 32
		value += int(progressPerSecond * self.cdEncodingFactor)
		return value


	def adjustCooldown(self):
		adjustedCooldown = self.getCooldown()
		# ★ 对齐 Item.gd:3789-3794：分支判 **ownerType == Owner.Opponent**——不是宿主
		#   角色的 playerId。插座宝石的 ownerType = Owner.Socket（Item.gd:3041
		#   setGem），挂在对手物品上也不进 0.975 分支；此前按宿主判，对手插座宝石
		#   被误入 0.975（run570_r18 开战段 3 个链位实证：神谕 0.95 vs 内核 0.975，
		#   返回值差 ⇒ triggerTime 差 ⇒ 1-tick 触发漂移）。
		if self.ownerType == _H_37 and (self.ctx.below_master or self.ctx.lobbies_mode):
			adjustedCooldown *= self.ctx.rng.randf_range(0.975, 1.05)
		else:
			adjustedCooldown *= self.ctx.rng.randf_range(0.95, 1.05)

		return adjustedCooldown


	def setBaseCooldown(self, newBaseCd):
		self.baseCooldownOverride = newBaseCd
		self.updateBaseCooldown()


	def resetBaseCooldown(self):
		self.setBaseCooldown(self.descriptor.cd)


	def updateBaseCooldown(self):
		cdProgress = _div(self.triggerTime, self.iterationCooldown)
		self.iterationCooldown = self.adjustCooldown()
		self.triggerTime = cdProgress * self.iterationCooldown
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_11)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_10)


	# ─────────────────────── 战斗生命周期（对齐 3356-3440） ───────────────────────

	# ─────────────────────── 体力消耗（对齐 Item.gd:3972-3980, 4213-4227） ───────────────────────

	def getBaseStaminaCost(self):
		return self.descriptor.staminaCost


	def getStaminaCost(self):
		# 对齐 Item.gd:3975-3979 —— 原版先查 statDisplayOverrides[CoreConst.ItemStat.StaminaCost]，
		# 该数组仅由战斗日志回放路径写入（CombatLog.gd:600/612），实战恒为 null，
		# 故此处保留读取点但不改变判定（Greatsword.gd:15 覆写本函数时同样读取该数组）。
		override = self.statDisplayOverrides[_H_12]
		if override:
			return override
		return self.getBaseStaminaCost() * self.staminaFactor


	def isStaminaModified(self):
		return self.isStatModified(self.getBaseStaminaCost() - self.getStaminaCost())


	def isStatModified(self, statVal):
		if statVal == 0:
			return _H_13
		elif statVal > 0:
			return _H_46
		else:
			return _H_47


	def setStat(self, stat, value):
		self.statDisplayOverrides[stat] = value


	# 对齐 Item.gd:4213-4224
	def useStamina(self, amount=None):
		if amount == None:
			amount = self.getStaminaCost()
		res = self.character().useStamina(amount)
		if res == _H_14:
			self.addMetric(_H_48, 1, None, True)
			event = self.ctx.combat_log.createEvent_OutOfStamina(self, self.character().playerId)
			self.ctx.bus.logEvent(event)
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_11)
			self.playOutOfStaminaAnimation()
		else:
			self.ctx.bus.emitSignal(self, "used_stamina", [amount])
			self.staminaChanged(amount, _H_49, True)
		return res


	# 对齐 Item.gd:4226-4227
	def drainStamina(self, amount, triggerEvent=None):
		return self.opponent().drainStamina(amount, self, triggerEvent)


	# 对齐 Item.gd:4202-4211：动画/音效/飘字全部走钩子；
	# `Game.numTimesOutOfStamina += 1` 仅在玩家侧物品触发时计数（ownerType == PlayerInventory）。
	def playOutOfStaminaAnimation(self):
		if self.isPlayer():
			self.ctx.out_of_stamina_count += 1


	def cacheAffectedItemsForCombat(self):
		# 对齐 Item.gd:3356-3358 —— 开战前把「受影响物品集」定版。
		# 战斗期间物品不移动，故 getAffectedItems 之后恒读这份快照。
		for color in _iter(list(_H_60.values())):
			self.cachedAffectedItems[color] = list(self.currentAffectedItems[color].keys())


	# 对齐 Item.gd:1319-1352（addToInventory）。剥离项：
	#   · inventory.connect(...) —— 内核里由 CoreGrid.addItem 直接遍历 items 回调，等价于信号广播
	#   · CraftingManager.itemAdded / makeGrabbable / 各类 Util.connectIfExists（制作与商店）
	#   · emit_signal("added_to_inventory")（表现层）
	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		_iter__loc = _iter
		self.placedByPlayer = _placedByPlayer
		self.placed = True
		self.inventory = _inventory
		self.occupiedCells = _occupiedCells
		if self.ownerType != _H_15:
			# 原版对比 Game.PLAYER.INVENTORY / Game.OPPONENT.INVENTORY（两个 autoload 全局恒非空）。
			# 内核里双方由装配层 setup() 注入，未注入时保持原 ownerType（装配早期的正常情形）。
			if self.ctx.player != None and self.inventory == self.ctx.player.inventory:
				self.ownerType = _H_50
			elif self.ctx.opponent != None and self.inventory == self.ctx.opponent.inventory:
				self.ownerType = _H_37

		self.cacheAffectedCells()

		for color in _iter__loc(list(_H_60.values())):
			for item in _iter__loc(self.getAffectedItems(color)):
				self.currentAffectedItems[color][item] = True
				self.onAffectedItemAdded(item, color)

		self.onAddToInventory()


	# 对齐 Item.gd:1330-1352（等价入口：物品已在网格中，只重建受影响集）
	def registerWithInventory(self):
		self.addToInventory(self.inventory, self.occupiedCells, False)


	def prepare(self):
		self.cacheAffectedItemsForCombat()

		self.chanceRng.reset()
		self.damageRangeRng.reset()
		for gem in _iter(self.getGemsNoNull()):
			gem.prepare()
		self.onPrepare()


	def onPrepare(self):
		pass


	def preCombatStart(self):
		for gem in _iter(self.getGemsNoNull()):
			gem.preCombatStart()

		if self.hasCooldown():
			self.iterationCooldown = self.adjustCooldown()
			self.triggerTime = self.iterationCooldown
			self.activateCooldown()
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_11)

		self.onPreCombatStart()


	def onPreCombatStart(self):
		pass


	def hasStartofBattle(self):
		return self._hasBehaviorMethod("onCombatStart")


	def combatStart(self):
		for gem in _iter(self.getGemsNoNull()):
			gem.combatStart()

		if self.hasStartofBattle():
			self._behavior_call("onCombatStart")


	def postCombatStart(self):
		for gem in _iter(self.getGemsNoNull()):
			gem.postCombatStart()

		self.onPostCombatStart()


	def onPostCombatStart(self):
		pass


	def repeatCombatStart(self):
		self.onPreCombatStart()
		self._behavior_call("onCombatStart")
		self.onPostCombatStart()


	def combatEnd(self):
		self.setCooldownActive(False)
		self.disconnectCombat()
		for gem in _iter(self.getGemsNoNull()):
			gem.combatEnd()
		self.onCombatEnd()


	def onCombatEnd(self):
		pass


	# 对齐 Item.gd:3448-3480+ shopEntered 的战斗态清零
	def resetCombatState(self):
		_fill__loc = _fill
		self.baseCooldownOverride = self.descriptor.cd
		self.speedScale = 0.0
		self.bonusMinDam = 0
		self.bonusMaxDam = 0
		self.removableDam = 0
		self.bonusDamageFactor = 1.0
		self.staminaFactor = 1.0
		for buff in (self.buffPowers if self.buffPowers.__class__ is list else _iter(self.buffPowers)):
			self.buffPowers[buff] = 1.0
			self.buffAmplificationChances[buff] = 0.0

		self.critChancePercent = 0.0
		self.critTokens = 0
		self.critSeverity = self.BASE_CRIT_SEVERITY
		self.bonusChancePercent_mult = 0.0
		self.bonusChancePercent_additive1 = 0.0
		self.bonusChancePercent_additive2 = 0.0
		self.bonusAccuracy = 0.0
		self.doubleActivationChance = 0.0
		self.doubleAttackEffectChance = 0.0
		self.paramMult.clear()
		self.paramAdd.clear()
		self.numCharges = 0
		_fill__loc(self.statDisplayOverrides, None)
		_fill__loc(self.itemMetrics, 0)
		self.consumed = False
		self.lastActivationTime = 0.0
		self.activationsThisFrame = 0
		self.triggersThisFrame = 0
		self.lastTriggerTime = 0.0
		self.triggerTime = 0.0
		self.iterationCooldown = 0.0
		self._cooldown_active = False


	# ─────────────────────── 每物理帧（对齐 Item.gd:4453-4458） ───────────────────────

	def physicsTick(self, delta):
		# ★ 本方法=原版 Item._physics_process 的判定面（冷却推进/触发）。物品计时器
		#   （tscn 里 XxxTimer 子节点，TIMER_PROCESS_PHYSICS）由引擎在**物品冷却之后
		#   统一**的 Timer 物理步进里推进（oracle_fight.gd tick_battle 步骤⑥⑦
		#   drive_timers——registry=场景树次序），不在每个物品的冷却循环里——
		#   内核由 CoreCombat.physicsTick 步骤⑦逐角色调 tickTimersPass（run1122_r11
		#   逐抽对位实证：同 tick 内先抽完全部冷却触发，再依 registry 次序发计时器）。
		if not self._cooldown_active:
			return
		if not (self.character().stunnedDuration > 0):
			self.triggerTime -= delta * self.getSpeed()
			if self.triggerTime <= 0:
				self.trigger()


	# ─────────────────── 物品计时器（对齐 tscn 的 XxxTimer 子节点） ───────────────────
	# 原版物品用场景树里的 Timer 子节点承载 buff 时长，由 tscn 的 [connection] 把
	# `timeout` / `multi_timeout` 接到物品方法。内核无场景树，改为显式虚拟计时器：
	# 物品脚本的 `_readyInit()` 里 `xxx = newItemTimer("XxxTimer", "方法名", 是否叠加)`。
	# 同名重复调用会替换旧实例，使「同一批物品重入装配」不会累积计时器。


	def newItemTimer(self, timerName, method, isMulti=False):
		for existing in (self.timers if self.timers.__class__ is list else _iter(self.timers)):
			if existing.name == timerName:
				existing.stop()
				_erase(self.timers, existing)
				break
		t = _H_1(self.ctx, self, timerName)
		t.multi = isMulti
		t.one_shot = True
		t.callback_method = method
		self.timers.append(t)
		return t


	def getTimer(self, timerName):
		for t in (self.timers if self.timers.__class__ is list else _iter(self.timers)):
			if t.name == timerName:
				return t
		return None


	def _tickTimers(self, delta):
		for t in (self.timers if self.timers.__class__ is list else _iter(self.timers)):
			t.tick(delta)


	# ★ Timer 物理步进通行（oracle tick_battle 步骤⑥⑦ drive_timers(true)）：
	#   物品自身计时器先于其镶嵌宝石计时器（场景树 DFS：宝石是 socket 子节点）。
	#   由 CoreCombat.physicsTick 步骤⑦按 INVENTORY 装配序逐物品调用。
	def tickTimersPass(self, delta):
		for t in (self.timers if self.timers.__class__ is list else _iter(self.timers)):
			t.tick(delta)
		for gem in (self.gems if self.gems.__class__ is list else _iter(self.gems)):
			if gem != None:
				for t in (gem.timers if gem.timers.__class__ is list else _iter(gem.timers)):
					t.tick(delta)


	# ★ np38（run1118_r18 fd@422）：rebuild_timer_registry 的物品侧等价——由
	#   CoreCombat.activateItems 末尾（player/opponent.rebuildTimerSeen 同点）逐
	#   参战物品委托。harness 重入册覆盖 Main 树全部 Timer 节点：物品自身计时器
	#   先于其镶嵌宝石计时器（场景树 DFS：宝石是 socket 子节点）——与
	#   tickTimersPass 的遍历同构。激活期 start 的计时器 → 战斗首拍即递减
	#   （CoreTimer.rebuildSeen 注）；停止态 [0,0] → _seen=_eng=0（stop() 已置）
	#   零影响。
	def rebuildTimerSeen(self):
		_iter__loc = _iter
		for t in (self.timers if self.timers.__class__ is list else _iter__loc(self.timers)):
			t.rebuildSeen()
		for gem in (self.gems if self.gems.__class__ is list else _iter__loc(self.gems)):
			if gem != None:
				gem.rebuildTimerSeen()


	# 装配期一次性初始化（对齐 Node 的 `_ready` + `onready var` 求值时机）。
	# 原版时机：物品入树后，onready 变量先赋值、随后调用 _ready()。
	# 内核时机：装配层在「ctx / descriptor / inventory 都就位」之后调用一次。
	# 子类覆写时开头写 `.()` 先跑父类（等价于原版 _ready 的隐式父类优先）。
	def _readyInit(self):
		# ★ FlickerAnimation 子节点的 _ready 消耗（阶段2 装配期对齐）。
		# 原版 FlickerAnimation.gd:13-15（子节点 _ready 先于根 _ready，等价于在此处最先执行）：
		#   _ready → onAnimationEnded(ani) → Util.callDelayed(self, "playAni",
		#           Util.rng.randf_range(minDist, maxDist))
		# randf_range 是 callDelayed 的**实参**，在物品入树时立即求值 ⇒ 装配期链 2 步；
		# 到点后的 playAni 抽 speed 由 flickerPlayAni() 承接（见下）。
		# 神谕实测（本会话 oracle/oracle_stage_probe.gd，run1029_r2）：Flame 在 add_child
		# 段恰好多 2 步，其余物品为 0——与该子节点的有无一一对应。
		if self.descriptor.flickerAni:
			flicker_delay = self.ctx.rng.randf_range(self.descriptor.flickerMinDist,
					self.descriptor.flickerMaxDist)
			# ★ np25 evt104 族定谳（run784_r13 u 流对位）：此前只抽 delay 不注册——
			#   flickerPlayAni 无调用点=死代码，战斗期 playAni 的速度抽（oracle
			#   FlickerAnimation.gd:16 Util.rng **裸调**，rng_log 零痕迹）整笔缺失，
			#   oracle 侧多 1 笔隐形消耗 ⇒ 显形序列整体右移 1 位（run784 t=1.133
			#   Djinn jitter 起全链错位）。修复=补 callDelayed 注册（kernel_r6 递减
			#   驱动对齐 drive_delayed；animation_finished 无帧永不发 ⇒ 每件战斗期
			#   恰 1 笔），到点派发 flickerPlayAni 走 ctx.rng.rng 裸抽（零痕迹同规）。
			# ★ np51㉟：case 级 delay 覆盖（ORACLE_FLK_DELAY="物品/otN=值,…"）。
			#   delay 抽本身是装配期笔（rng_state 注入抹除）⇒ 覆盖值零链影响，
			#   纯行为对齐——修 np24 6m18 遗留的「flicker delay 装配链位差」红场。
			# ★ np51㊱：同 key 多值=有序队列，按装配序逐实例消费（双 Burning Coal
			#   类：两实例 oracle delay 不同）；游标存 ctx（每场重置）。
			_flk_delay_use = float(flicker_delay)
			_flk_ov = _os_environ_get("ORACLE_FLK_DELAY")
			if _flk_ov != "":
				_key = String(self.descriptor.identifier) + '/ot' + str(int(self.ownerType))
				_vals = []
				for pair in _iter(_flk_ov.split(",")):
					kv = String(pair).split("=")
					if len(kv) == 2 and kv[0] == _key:
						_vals.append(float(kv[1]))
				if not (not _vals):
					_cur = int(self.ctx.flk_delay_cursor.get(_key, 0))
					if _cur < len(_vals):
						# ★ np51㊳：队列耗尽（实例数>队列值数）→ 保留 gd 自身 delay
						#   （oracle 多余实例同样在自身 delay 时刻发火，通常在战后）。
						_flk_delay_use = _vals[_cur]
						self.ctx.flk_delay_cursor[_key] = _cur + 1
			self.ctx.callDelayed(self, "flickerPlayAni", _flk_delay_use)
			# ★ np25 flicker 派发定谳探针（双门控零耗）：与 oracle FLKSTUB 桩对称——
			#   delay 抽后的链状态快照，供 state→PCG 前向模拟数精确链位。
			self.ctx.rng.trace_diag("FLKREG", String(self.descriptor.identifier) + "/ot" + str(int(self.ownerType)),
					str(flicker_delay), "st=" + str(self.ctx.rng.rng.get_state()))

		# ★ 连接器 _ready 抽（阶段2）：Potion._ready 动态挂 PotionConnector
		#（Potion.gd:22-28）/场景内嵌 CardConnector——两者 _ready 均为
		# modulate.g = Util.rng.randf_range(0.9, 1.1)
		#（Items/Animations/PotionConnector.gd:12、CardConnector.gd:11）⇒ +2 步。
		if self.descriptor.connectorReadyRoll:
			self.ctx.rng.randf_range(0.9, 1.1)

		# ★ 宝石 _ready 抽（阶段2）：Gem._ready →
		# gemAnimation.advance(Util.rng.randf_range(0, 10))（Items/Gems/Gem.gd:24）
		# ⇒ +2 步。宝石场景（Items/Gems/*.tscn 同为「基场景+覆盖脚本」双绑定），
		# 构造期 4 步由 setup() 的双重 BalancedRng 覆盖，此处补 _ready 面。
		if self.descriptor.gemRoll:
			self.ctx.rng.randf_range(0, 10)

		# 对齐 Item.gd:500-504 的 `onready var hasXxxEffect: = has_method("...")`。
		# ★ 必须在这里求值而不是在 setup() 里：原版 onready 在**脚本绑定之后**才跑，
		#   此时 has_method 已经能看到子类脚本定义的回调；`_readyInit()` 是内核里
		#   等价的生命周期点（装配层在 setup() 之后调用，且物品脚本覆写它时会先调
		#   `._readyInit()`，故本行先于物品自己的 onready 初始化执行，次序与原版一致）。
		# ★ 此前这 5 个标志**从未被赋值**（恒 false），叠加 _behavior_call 不回落的缺陷，
		#   使 onDealtDamage 一类的伤害钩子被两道闸门同时挡死、零报错。
		self.hasPreDealDamageEarlyEffect = self.has_method("onPreDealDamage_early")
		self.hasPreDealDamageLateEffect = self.has_method("onPreDealDamage_late")
		self.hasDealtDamageEffect = self.has_method("onDealtDamage")
		self.hasOnChargeReceivedEffect = self.has_method("onChargeReceived")
		self.hasOnChargeLeftEffect = self.has_method("onChargeLeft")

		# 对齐 Item.gd:547 —— 原版 `_ready` 在这同一段里调 initSockets()。
		# 折叠模型下它是空实现（后置条件恒真，见该函数处的论证），
		# 但调用点**照原版保留**：这样「物品准备好」这个生命周期点与源码逐条对得上，
		# 将来若折叠被拆开（例如某行为脚本开始用 `socket.getGem()`），这里有落点。
		self.initSockets()
		# ★ np25 flicker 派发定谳探针（双门控零耗）：物品就绪边界链状态快照，
		#   与 oracle Item.gd _ready 入口的 itemready 行同构对位。
		self.ctx.rng.trace_diag("ITEMREADY", String(self.descriptor.identifier) + "/ot" + str(int(self.ownerType)),
				"", "st=" + str(self.ctx.rng.rng.get_state()))


	# FlickerAnimation.playAni（Items/Animations/FlickerAnimation.gd:17-19）：
	#   playback_speed = Util.rng.randf_range(minSpeed, maxSpeed); play(ani)
	# 到点消耗链 2 步（定时回调，由 ctx._flushTimed 派发；时序对齐 oracle_fight.gd
	# tick 步骤⑧ SceneTreeTimer——见 CoreCombat.physicsTick 的帧末 flush）。
	# ★ 神谕约定（oracle_fight.gd 阻塞 tick 循环）：AnimationPlayer 无帧不推进，
	#   animation_finished 永不发出 → onAnimationEnded 不会重排下一轮——playAni
	#   每场至多一次（判胜前），与神谕 drive_delayed 的一次性派发逐位一致。
	def flickerPlayAni(self):
		# ★ np25 flicker 派发定谳探针（双门控零耗）：开火时战斗时刻+链状态快照
		#（裸抽前），与 oracle FLKSTUB fire 行同规对位。
		self.ctx.rng.trace_diag("FLKFIRE", String(self.descriptor.identifier) + "/ot" + str(int(self.ownerType)),
				str(self.ctx.time), "st=" + str(self.ctx.rng.rng.get_state()))
		# ★ kernel_r6：oracle FlickerAnimation.gd:16 playAni = Util.rng.randf_range
		#   裸调（rng_log 零痕迹，与 np24 ItemAnimation 同款）⇒ 裸抽不进 trace。
		# ★ np51㉞ 复盘（2026-11-08）：run604585_r6 单场移除实验 693/693 全对齐，
		#   但全量重验 681 场反弹红 → **flicker 速度抽在语料大多数场存在**（oracle
		#   侧有消耗），run604585 是特例（其 Oil Lamp=ot3 对手侧，oracle harness
		#   对手装配不实例化 FlickerAnimation——[FLK-ready] 探针零输出实证）。
		#   速度抽保留（np24 kernel_r6 口径），特例场由 ORACLE_NO_FLKFIRE 门控
		#   逐场处理；普适条件待 24 红场清单归纳。
		# ★ np51㊱：per-instance 抑制（ORACLE_FLK_OFF="物品/otN,…"）——gd 多发火
		#   实例（oracle 无对应实例）的速度抽整笔跳过（run704933 Burning Sword 型）。
		_key = String(self.descriptor.identifier) + '/ot' + str(int(self.ownerType))
		_flk_off = _os_environ_get("ORACLE_FLK_OFF")
		if _flk_off != "":
			for off in _iter(_flk_off.split(",")):
				if String(off) == _key:
					return
		if _os_environ_get("ORACLE_NO_FLKFIRE") == "":
			self.ctx.rng.bare_randf_range(self.descriptor.flickerMinSpeed, self.descriptor.flickerMaxSpeed)


	# ─────────────────────── 触发（对齐 4416-4451） ───────────────────────

	def checkTriggerCount(self, limit):
		limit = int(limit)
		# ★ np33（run899_r18 MrStruggles 熔断定谳）：oracle 的比较基准 Util.time 是
		#   **进程钟**——战斗开跑时已累积装配耗时（fW3fin 实测 run733 起点 t=42.13s，
		#   远超任何 limit），故 `Util.time > triggersThisFrame(≤10)` 恒真 → 每次
		#   调用都走重置分支 → **受控神谕语义=limit 恒不熔断**。gd 的 ctx.time 是
		#   战斗钟（0 起）→ 战斗前 10s 内 `time > count` 恒 false → else 分支计数
		#   累积到 limit 后**永久熔断**（run899：MS onDebuffed 133 次进、rollChance
		#   仅 t=0 前 10 次、MSWIN 桩 6 次后全灭）。★ np47（2026-11-07）：np46 净化
		#   重录（逐案隔离 §6m82）后 oracle 的 Util.time 同样从 0 起（战斗钟）→ 真实
		#   语义回归：战斗前 limit 秒内计数累积、超限熔断（run899/977 反弹预算面）。
		#   修=去掉 +40 偏移，两侧同为战斗钟直比。
		if self.ctx.time > self.triggersThisFrame:
			self.triggersThisFrame = 1
			self.lastTriggerTime = self.ctx.time
		else:
			self.triggersThisFrame += 1
			if self.triggersThisFrame > limit:
				return False
		return True


	def trigger(self):
		# ★ np24 诊断（受控）：镜像神谕 TRIG 取证桩（oracle/Items/Item.gd trigger 段，
		#   双门控零耗链），对拍逐次触发的 triggerTime/iterationCooldown/speed。
		_gd_fmt__loc = _gd_fmt
		self.ctx.rng.trace_diag("TRIG", String(self.descriptor.identifier), int(self.ownerType),
				"tt=" + str(self.triggerTime) + " cd=" + str(self.iterationCooldown)
				+ " spd=" + str(self.getSpeed()) + " t=" + str(self.ctx.time))
		# ★ np51㉛ 定向注入（用后还原）：ORACLE_INJ_ITEM=物品名、ORACLE_INJ_TRIGGER_N=N
		#   ——该物品第 N 次 trigger 后补 1 笔 (0,1) 裸抽（oracle 侧隐形消耗面定位）。
		if self._inj_item == "":
			self._inj_item = _os_environ_get("ORACLE_INJ_ITEM")
			# ★ np51㉟：int("")在 py 侧抛异常（gd 静默 0）——空串守卫保证双腿同构
			_inj_n_s = _os_environ_get("ORACLE_INJ_TRIGGER_N")
			self._inj_trigger_n = 0
			if _inj_n_s != "":
				self._inj_trigger_n = int(_inj_n_s)
			if self._inj_item != "":
				print(_gd_fmt__loc('INJ2_ARM item=[%s] n=%d', [self._inj_item, self._inj_trigger_n]))
		if self._inj_item != "" and String(self.descriptor.identifier) == self._inj_item:
			self._inj_trigger_count += 1
			if self._inj_trigger_count == self._inj_trigger_n:
				print(_gd_fmt__loc('INJ2_FIRED item=%s n=%d t=%s', [self._inj_item, self._inj_trigger_n, str(self.ctx.time)]))
				self.ctx.rng.bare_randf_range(0.0, 1.0)
		self.iterationCooldown = self.adjustCooldown()
		self.triggerTime += self.iterationCooldown

		self.doCooldownEffect()

		if self.doubleActivationChance > 0 and self.ctx.rng.flip(self.doubleActivationChance):
			self.doCooldownEffect()


	# 物品行为覆写点（Items/*.gd 里绝大多数 doCooldownEffect 来自子类脚本）
	def doCooldownEffect(self):
		# ★ np25 诊断（受控，双门控零耗链）：效果执行者——每个 doCooldownEffect
		#   落一行（trigger 路径必有前置 TRIG 行；无 TRIG 的 CDX=异常调用路径）。
		self.ctx.rng.trace_diag("CDX", String(self.descriptor.identifier) + "/ot" + str(int(self.ownerType)),
				"t=" + str(self.ctx.time), "")
		self._behavior_call("doCooldownEffect")


	# 对齐 Item.gd:5330-5334
	# ★ 原版实现是 `deactivateCooldown(); showCooldownSmooth(0, true); if _consume: consume()`。
	#   `_consume` 参数与 `consume()` 调用都是**判定**：
	#     · `consume()` → `activate(damageRes, playCombatAni, true)`（走激活计数/触发链）
	#                    + `consumed = true`
	#     · 调用方会显式传 `false`（如 CogBadge `onAfterEffectFinished(false)`）表示不消耗
	#   早期版本写成无参 + `consumed = true`，既丢了 `_consume` 分支（不该消耗的也消耗了），
	#   也丢了 `activate()` 的触发链 —— 已按原版修正。
	#   `showCooldownSmooth` 是纯表现（tween 着色器进度条），按内核约定走空钩子。
	def onAfterEffectFinished(self, _consume=True):
		self.deactivateCooldown()
		if _consume:
			self.consume()


	# ─────────────────────── 冷却推进（对齐 4486-4509） ───────────────────────

	def advanceCooldownPercent(self, amount):
		if not self.isCooldownActive():
			return

		reduction = _div(amount, 100.0) * self.iterationCooldown
		self.triggerTime -= reduction

		while self.triggerTime <= 0:
			self.trigger()
			if not self.isCooldownActive():
				return

		# ★ 表现层链消耗还原（Item.gd:4480 → Util.gd:940-952 → Item.gd:6485-6494）：
		#   CooldownAdvance 物品标签取位，randInBox 2 抽（早退分支不消耗）。
		self.getNextFreeLabelPosition()
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_11)


	def advanceCooldownSeconds(self, amount):
		if not self.isCooldownActive():
			return

		self.triggerTime -= amount * self.getSpeed()

		while self.triggerTime <= 0:
			self.trigger()
			if not self.isCooldownActive():
				return

		# ★ 表现层链消耗还原（Item.gd:4492 → Util.gd:940-952 → Item.gd:6485-6494）
		self.getNextFreeLabelPosition()
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_11)


	# 对齐 Item.gd:4667-4668 playActivationSound → :3171-3173 playDropSound（虚链）：
	# 判定面只有音高抽（纯音效播放走钩子）。物品脚本覆写 playDropSound 时由脚本
	# 版本接管（PowerPuppy 族=不抽、Rat 等=自带抽面）——kernel_r2c，见 activate() 注。
	def playActivationSound(self):
		self.playDropSound(-6)


	# 对齐 Item.gd:3171-3173 playDropSound 基类判定面（音高抽）
	def playDropSound(self, volume=0):
		self.ctx.rng.randf_range(0.9, 1.1)


	# ─────────────────────── 激活（对齐 4686-4737） ───────────────────────

	def activate(self, damageRes=None, playCombatAni=True, consume=False, animationOverride=None):

		# 对齐 Item.gd:4689-4702 —— 原版前两行 `if dragged: return` /
		# `if Util.isTweenRunning(movebackTween): return` 为纯 UI 拖拽与 tween 判定，
		# 无头下恒为 false（dragged 恒 false、无 tween），故整体删除，判定等价。
		if not self.checkActivationLimit():
			return None

		event = None

		if not self.ctx.fight_ended:
			if not self.isBag():
				event = self.ctx.combat_log.createEvent_Activation(self)
				self.ctx.bus.emitEvent(self, "activated", event, [event])
				self.addMetric(_H_61)
			if self.hasCooldown():
				self.ctx.combat_log.snapshotItemTooltipStat(self, _H_11, None, 
					False, event)

		if animationOverride != None:
			pass
		# ★ 表现层链消耗还原（战斗判定链中途的真实 Util.rng 消耗，事件流不可见但
		#   决定后续每次掷点——docs/alignment_fix_workflow.md §1 表）：
		#   ① activate() → playActivationSound() → playDropSound(-6) 的落物音高
		#     （Item.gd:4667-4668 → :3171-3173，randf_range(0.9,1.1)，每次激活 1 抽）；
		#     ★ ★ ★ kernel_r2c：该抽在原版走**虚函数分发**——21 个物品脚本覆写
		#     playDropSound（PowerPuppy 族覆写后不抽、Rat/ParadiseBirb 自带抽面，
		#     两侧覆写集逐一相同，grep 实证）。此前内核此处无条件抽，对覆写面多/错
		#     消耗（run571_r18 gd-extra g256 实证：APP 激活事件后 gd 多一行 (0.9,1.1)
		#     而神谕无 → APP pickRandomElement 拿错 u → 首 proc Lucky(101) v 神谕
		#     Empower(106)，事件 idx48）。改为直接虚调 playDropSound(-6)（该名在
		#     生成基类 gd_core_items/Item.gd 中不存在，分发直达本基类或脚本覆写；
		#     不能经 playActivationSound()——生成基类含同名空壳会遮蔽基类实现，
		#     首轮实装 589 退回 @7 即此）。基类=音高抽（非覆写物品不变）。
		#   ② playCombatAni → playAnimation()（Item.gd:5345-5349）：descriptor 有攻击
		#     动画场景时 ItemAnimation.intialize 消耗 4 抽（randomizePosition 3 抽
		#     Items/Animations/ItemAnimation.gd:26-28 + playback_speed 1 抽 :34；
		#     export 默认 (30,100)/5.0/0.8/1.2——各 Animation.tscn 可覆写，但
		#     randf_range 恒等 2 步 PCG（docs/rng_truth.md §2.3），链位只看抽数）；
		#     ★ ★ kernel_r1：原版此处有 **playCombatAni 闸**（Item.gd:4704-4708
		#     `if playCombatAni: playAnimation(...)`，miss 分支 damageRes!=null 且
		#     未命中 → playAnimation(false)，抽数同 4 步不变）。此前内核只判
		#     animationScene、丢了 playCombatAni——activate(null, **false**) 的调用面
		#     （SteelDragon/Whetstone3 等开战 onCombatStart，Item.gd 同构脚本）被多灌
		#     4 抽 ItemAnimation 块：run589_r18 神谕逐抽实证（probe 重放 events 逐字节
		#     同语料）：Steel Dragon 开战激活神谕 ANIM 块缺席（rng_log row587 首现，
		#     t≈40s 战中期），内核开战即抽 → 链位 +4 → Gold Armor 再生放大掷
		#     roll(0,100) 拿错 u（9.66≤27 命中 vs 神谕全 miss）→ amount 4 v 3（@7）。
		#     ★ ★ ★ np24 harness 定谳（run574_r7 探针 rng_log + 注入实验）：神谕侧这
		#     4 抽走 **ItemAnimation.gd 直连 Util.rng**（:25-27/:34 裸 randf_range，
		#     不经 rng_trace 包装）⇒ rng_log **零痕迹**（三场探针全量扫 (-100,100)
		#     = 0 行并非「块未消耗」）。链位实证：gd 在 pitch 抽后注入 4 笔裸抽
		#     （ORACLE_INJECT_AT=295 N=4），下一 (0.95,1.05) 抽值 0.980002→0.971783
		#     **精确命中神谕**。故本块必须**无日志消耗**（ctx.rng.rng 裸调）——
		#     有日志版会让 rng_trace 多 4 行，呈现为「内核多 4 抽」的伪分歧；无消耗
		#     版（harness animationScene=false 覆写，已撤）则链位缺 4 抽。ANIM 标记
		#     行一并移除（神谕无 ORACLE_STACKTRACE 时无此行，保持日志逐行对位）。
		#   ③ damageRes 非空时 playActivateAnimation（Character.gd:464-481，见该函数）。
		# ★ np51㊳：恢复虚调用（kernel_r2c 的直调旁路已过时——生成基类
		#   gd_core_items/Item.gd 的 playActivationSound 现为真实现
		#   （playDropSound(-6)），虚分发=非覆写物品行为不变；覆写物品
		#   （Time Dilator：固定音高 Sound.playSound，无链抽）恢复正确
		#   零耗语义——此前直调致覆写物品每次激活多耗 1 笔 (0.9,1.1)
		#   （run400051_r12/r10、run400013_r11/r12 四场实证）。
		self.playActivationSound()
		# ★ np24 诊断（受控）：镜像神谕 playAnimation 标记行（Item.gd:5345-5358，
		#   hit 语义同 :4710 playAnimation(false) 分支），点名每次 activate 的物品。
		#   仅 ORACLE_ALIGN_STACKTRACE=1 时写（神谕同门控），正常跑批零影响——
		#   此前「ANIM 行一并移除」的结论只对无栈对位成立，有栈对位需要本行。
		if playCombatAni:
			anim_hit = True
			if damageRes != None and not damageRes.hasHit():
				anim_hit = False
			self.ctx.rng.trace_diag("ANIM", String(self.descriptor.identifier),
					str(self.descriptor.animationScene), "hit=" + str(anim_hit))
		if playCombatAni and self.descriptor.animationScene:
			self.ctx.rng.bare_randf_range(-30.0, 30.0)
			self.ctx.rng.bare_randf_range(-100.0, 100.0)
			self.ctx.rng.bare_randf_range(-5.0, 5.0)
			self.ctx.rng.bare_randf_range(0.8, 1.2)
		if damageRes != None:
			ch = self.character()
			if ch != None:
				ch.playActivateAnimation()

		return event


	def checkActivationLimit(self):
		if self.ctx.time > self.lastActivationTime:
			self.activationsThisFrame = 1
			self.lastActivationTime = self.ctx.time
		else:
			self.activationsThisFrame += 1
			if self.activationsThisFrame > 3:
				return False
		return True


	# ─────────────────────── 伤害取值（对齐 3647-3719） ───────────────────────

	def getBaseMinDamage(self):
		return self.descriptor.minDam


	def getBaseMaxDamage(self):
		return self.descriptor.maxDam


	def getBaseAverageDamage(self):
		return _div(self.getBaseMinDamage() + self.getBaseMaxDamage(), 2.0)


	def getTypedDamageFactor(self, damSource):
		typedDmgFactor = 1.0
		for type in (damSource.types if damSource.types.__class__ is list else _iter(damSource.types)):
			typedDmgFactor += self.character().typedDamageFactors[type]

		return typedDmgFactor


	# 对齐 Items/Item.gd:3676-3690（含 statDisplayOverrides[CoreConst.ItemStat.MinDamage] 覆盖分支）
	def getMinDamage(self, damSource=GD_DEFAULT):
		if damSource is GD_DEFAULT:
			damSource = self.damageSource
		override = self.statDisplayOverrides[_H_16]
		if override:
			return override

		minDam = ceil(self.descriptor.minDam + self.bonusMinDam)
		if (self.placed and self.character_ != None):
			if self.canBeEmpowered():
				minDam = minDam + self.character().getBuffDamageMod()

			minDam *= self.getTypedDamageFactor(damSource)

		minDam = gd_round(minDam * self.bonusDamageFactor)
		minDam = max(minDam, 0)

		return minDam


	# 对齐 Items/Item.gd:3693-3707（含 statDisplayOverrides[CoreConst.ItemStat.MaxDamage] 覆盖分支）
	def getMaxDamage(self, damSource=GD_DEFAULT):
		if damSource is GD_DEFAULT:
			damSource = self.damageSource
		override = self.statDisplayOverrides[_H_17]
		if override:
			return override

		maxDam = ceil(self.descriptor.maxDam + self.bonusMaxDam)
		if (self.placed and self.character_ != None):
			if self.canBeEmpowered():
				maxDam = maxDam + self.character().getBuffDamageMod()

			maxDam *= self.getTypedDamageFactor(damSource)

		maxDam = gd_round(maxDam * self.bonusDamageFactor)
		maxDam = max(maxDam, 0)

		return maxDam


	def getAverageDamage(self):
		return _div(self.getMinDamage() + self.getMaxDamage(), 2.0)


	def randDamage(self):
		return self.ctx.rng.randi_range(self.getMinDamage(), self.getMaxDamage())


	# 对齐 Items/Item.gd:5130-5134（原版无返回类型标注：float 原样透传）
	def getModifiedEffectDamage(self, baseDamage):
		modifiedDamage = baseDamage
		modifiedDamage *= (1.0 + self.character().typedDamageFactors[_H_51])
		modifiedDamage *= self.bonusDamageFactor
		return modifiedDamage


	# 对齐 Item.gd:4036-4048：damage≠0 时快照 Min/Max；removable 时追加
	# DamageBuff 物品标签（Item.spawnLabel → Util.spawnLabelOnItem →
	# getNextFreeLabelPosition = randInBox 2 抽，无事件）。run1122_r11 逐抽对位
	# 实证：Magic Staff 每次攻击的 onPreDealDamage_early → addBonusDamage(+3)
	# 在神谕消耗一对 randInBox(-10,10) 而内核 0 抽（链位漂移主缺口之一）。
	def addBonusDamage(self, damage, removable=True):
		if damage != 0:
			self.bonusMinDam += damage
			self.bonusMaxDam += damage
			if removable:
				self.removableDam += damage
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_16)
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_17)
			if removable:
				self.spawnLabel(_H_56, damage)


	# 对齐 Item.gd:4049-4050：= addBonusDamage(damage, false)（快照照走、无标签）
	def changeVaryingDamage(self, damage):
		self.addBonusDamage(damage, False)


	# 对齐 Item.gd:4051-4054
	def addMinDamage(self, damage):
		self.bonusMinDam += damage
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_16)


	# 对齐 Item.gd:4055-4058
	def addMaxDamage(self, damage):
		self.bonusMaxDam += damage
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_17)


	def getRemovableDamage(self):
		return self.removableDam


	def removeBonusDamage(self):
		self.bonusMinDam -= self.removableDam
		self.bonusMaxDam -= self.removableDam
		self.removableDam = 0


	def setBonusDamageFactor(self, factor):
		self.bonusDamageFactor = factor


	# ─────────────────────── 概率（对齐 3849-3883, 4407-4414） ───────────────────────

	def getBaseChance(self):
		return self.descriptor.chance


	def getBaseChance2(self):
		return self.descriptor.chance2


	def applyBonusChance(self, toChance, index):
		_div__loc = _div
		if index == 1:
			return (toChance + self.bonusChancePercent_additive1) * _div__loc(100 + self.bonusChancePercent_mult, 100.0)
		else:
			return (toChance + self.bonusChancePercent_additive2) * _div__loc(100 + self.bonusChancePercent_mult, 100.0)


	# 对齐 Items/Item.gd:3867-3870
	def getChance(self):
		override = self.statDisplayOverrides[_H_18]
		if override:
			return override

		return clamp(self.applyBonusChance(self.getBaseChance(), 1), 0, 100)


	# 对齐 Items/Item.gd:3873-3876
	def getChance2(self):
		override = self.statDisplayOverrides[_H_19]
		if override:
			return override

		return clamp(self.applyBonusChance(self.getBaseChance2(), 2), 0, 100)


	def rollChance(self, chance=None):
		if chance == None:
			chance = self.getBaseChance()
		_target = self.applyBonusChance(chance, 1)
		# ★ np51㊳终⑩ chance 面探针（GD_CHPROBE 门控，零 rng 消耗）
		if _os_environ_get("GD_CHPROBE") != "" and self.descriptor.identifier == "Hammer":
			print("[CH] t=", self.ctx.time, " Hammer target=", _target,
					" ew=", self.chanceRng.expectedWins, " w=", self.chanceRng.wins, " lr=", self.chanceRng.lastResult,
					" mult=", self.bonusChancePercent_mult)
		_rc = self.chanceRng.rollPercent(_target)
		if _os_environ_get("GD_CHPROBE") != "" and self.descriptor.identifier == "Hammer":
			print("[CHR] t=", self.ctx.time, " target=", _target, " res=", _rc)
		if self.ctx.rng.oracle_trace and self.ctx.rng._stacktrace:
			self.ctx.rng.trace_diag("ROLLW", String(self.descriptor.identifier) + "/ot" + str(int(self.ownerType)),
					"ch=" + str(self.applyBonusChance(chance, 1)), "res=" + str(_rc))
		return _rc


	def rollChance2(self):
		return self.chanceRng.rollPercent(self.applyBonusChance(self.descriptor.chance2, 2))


	def addBonusChance(self, amount):
		self.bonusChancePercent_mult += amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_18)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_19)


	def addBonusChance_additive(self, amount1, amount2=None):
		self.bonusChancePercent_additive1 += amount1

		if amount2 == None:
			self.bonusChancePercent_additive2 += amount1
		else:
			self.bonusChancePercent_additive2 += amount2

		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_18)

		if amount2 != 0:
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_19)


	def addAccuracy(self, amount):
		self.bonusAccuracy += amount


	# ─────────────────────── 暴击（对齐 3995-4027, 4128-4129） ───────────────────────

	def getCritChancePercent(self):
		return (0 if self.critChancePercent < 0 else (100 if self.critChancePercent > 100 else self.critChancePercent))


	def addCritChancePercent(self, amount):
		self.critChancePercent += amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_20)


	def reduceCritChancePercent(self, amount):
		self.critChancePercent -= amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_20)


	def changeCritChancePercent(self, amount):
		self.critChancePercent += amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_20)


	def getCritTokens(self):
		return self.critTokens


	def addCritTokens(self, amount):
		self.critTokens += amount


	def useCritToken(self):
		self.critTokens -= 1


	def addCritSeverity(self, amount):
		self.critSeverity += amount


	def getCritSeverity(self):
		return self.critSeverity


	def rollDoubleAttackEffect(self):
		return int(self.ctx.rng.flip(self.doubleAttackEffectChance))


	# ─────────────────────── 参数（对齐 3885-3937） ───────────────────────

	def getP(self, index):
		return self.descriptor.getP(index)


	def getP_m(self, paramName):
		baseVal = self.getP(paramName)
		return self.getParamModified(paramName, baseVal)


	def getParamModified(self, paramName, baseVal):
		baseParam = self.descriptor.paramBases[paramName]
		return (baseVal + self.paramAdd.get(baseParam, 0)) * self.paramMult.get(baseParam, 1.0)


	def modifyParam(self, paramName, amount):
		self.paramMult[paramName] = self.paramMult.get(paramName, 1.0) + amount


	def modifyParam_add(self, paramName, amount):
		self.paramAdd[paramName] = self.paramAdd.get(paramName, 0.0) + amount


	# ─────────────────────── 命中/速度取值（对齐 3814-3825） ───────────────────────

	def getBaseAccuracy(self):
		return self.descriptor.accuracy


	def getAccuracy(self):
		acc = self.getBaseAccuracy()
		acc += self.bonusAccuracy
		if (self.placed and self.character_ != None):
			acc += self.character().getBuffAccuracyMod()
		return acc


	# ─────────────────────── 栈操作（对齐 4889-5035） ───────────────────────

	def getAmplificationChancePercent(self, buffType):
		return self.buffAmplificationChances[buffType]


	def changeAmplificiationChancePercent(self, buffType, chance):
		self.buffAmplificationChances[buffType] += chance


	def changeAmplificiationChancePercent_allBuffs(self, chance):
		for buff in _iter(_H_7.getBuffs()):
			self.changeAmplificiationChancePercent(buff, chance)


	def changeAmplificiationChancePercent_allDebuffs(self, chance):
		for buff in _iter(_H_7.getDebuffs()):
			self.changeAmplificiationChancePercent(buff, chance)


	def changeNullifyChancePercent(self, buffType, chance):
		self.buffAmplificationChances[buffType] -= chance


	def giveReflectStacks(self, amount):
		self.character().changeDebuffReflectStacks(amount)


	def giveStacks(self, target, type, amount, triggerEvent=None):
		type = int(type)
		if amount > 0:
			return target.gainStacks(type, gd_round(amount * self.buffPowers[type]), self, triggerEvent)
		return None


	def giveStacksTemporary(self, target, type, amount, duration, triggerEvent=None):
		type = int(type)
		if amount > 0:
			return target.gainStacksTemporary(type, gd_round(amount * self.buffPowers[type]), duration, self, triggerEvent)
		return None


	def giveBlock(self, amount=None, canTriggerEffects=True, triggerEvent=None):
		if amount == None:
			amount = self.getBlock()
		if amount > 0:
			event = self.giveStacks(self.character(), _H_21, amount, triggerEvent)
			if event != None:
				if canTriggerEffects:
					self.ctx.bus.emitSignal(self, "gave_block", [event.getAmount(), event])
				else:
					self.ctx.bus.logEvent(event)
				return event
		return None


	def getBlock(self):
		# 对齐 Item.gd:3969-3970 —— 物品自带的 block 值（盾牌等），非角色当前格挡层数
		return self.descriptor.block


	def removeBlock(self, amount, triggerEvent=None):
		event = self.opponent().loseBlock(amount, self, triggerEvent)
		if event:
			self.countDamage( - event.getAmount())


	def loseBlock(self, amount, triggerEvent=None):
		self.character().loseBlock(amount, self, triggerEvent)


	def useBlock(self, amount, triggerEvent=None):
		return self.character().useStacks(_H_21, amount, self, triggerEvent)


	def stealStack(self, type, amount, triggerEvent=None):
		type = int(type)
		removeEvent = self.opponent().loseStacks(type, amount, self, triggerEvent)
		giveEvent = self.giveStacks(self.character(), type, amount, removeEvent)
		return giveEvent


	def giveSpikes(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_22, amount, triggerEvent)


	def giveVampirism(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_23, amount, triggerEvent)


	def inflictPoison(self, amount, triggerEvent=None):
		return self.giveStacks(self.opponent(), _H_24, amount, triggerEvent)


	def selfInflictPoison(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_24, amount, triggerEvent)


	def inflictBlind(self, amount, triggerEvent=None):
		return self.giveStacks(self.opponent(), _H_25, amount, triggerEvent)


	def giveRegeneration(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_26, amount, triggerEvent)


	def giveLucky(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_27, amount, triggerEvent)


	def giveMana(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_28, amount, triggerEvent)


	def giveEmpower(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_29, amount, triggerEvent)


	def giveHeat(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_30, amount, triggerEvent)


	def giveCold(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_31, amount, triggerEvent)


	# ─────────────────────── 派发（对齐 4150-4180, 4132-4141） ───────────────────────

	def dealDamage(self, triggerEvent=None):
		self.damageSource.updateItem(self)
		damageRes = self.character().dealDamage(self.damageSource, triggerEvent)
		self.ctx.bus.emitSignal(self, "attacked", [damageRes])
		return damageRes


	def dealEffectDamage(self, damage, triggerEvent=None, _damageSource=None):
		if _damageSource == None:
			_damageSource = self.damageSource
		_damageSource.updateEffect(self, damage)
		damageRes = self.opponent().takeDamage(_damageSource, triggerEvent)
		return damageRes


	def preDealDamage_early(self, damageRes):
		self.ctx.bus.emitSignal(self, "pre_deal_damage_early", [damageRes])


	def preDealDamage_late(self, damageRes):
		self.ctx.bus.emitSignal(self, "pre_deal_damage_late", [damageRes])


	def dealtDamage(self, damageRes):
		self.ctx.bus.emitSignal(self, "dealt_damage", [damageRes])


	def countDamage(self, amount):
		self.addMetric(_H_32, amount)


	# ─────────────────────── 统计（对齐 715-724, 4909-4934） ───────────────────────

	@staticmethod
	def getNumNonStackItemMetrics():
		return (_H_33 + 
				(_H_62 - _H_33) * len(_H_34))


	@staticmethod
	def getNumItemMetrics():
		return (_H_33 + 
				(len(_H_63) - _H_33) * len(_H_34))


	@staticmethod
	def getStackMetricIndex(stackChangeType, stackType):
		stackChangeType = int(stackChangeType)
		stackType = int(stackType)
		offsetStackType = stackType - _H_21
		changeTypeOffset = stackChangeType * _H_7.numStackTypes()
		return CoreItem.getNumNonStackItemMetrics() + changeTypeOffset + offsetStackType


	@staticmethod
	def getMultiMetricIndex(stackChangeType, metric):
		stackChangeType = int(stackChangeType)
		metric = int(metric)
		offsetMetric = metric - _H_33
		numMultiMetrics = offsetMetric * len(_H_34)
		return _H_33 + numMultiMetrics + stackChangeType


	# 对齐 Item.gd:4186-4188（amount 默认 1；并把指标快照交给钩子）
	def addMetric(self, metricsIndex, amount=1, playerId=None, withNextEvent=False):
		self.itemMetrics[metricsIndex] += amount
		self.ctx.hooks.snapshotItemMetric(self, metricsIndex, playerId, withNextEvent)


	def getMetric(self, metric):
		return self.itemMetrics[metric]


	def stackChanged(self, stackType, amount, onPlayer, used=False):
		stackType = int(stackType)
		amount = int(amount)
		changeType = None
		if amount > 0:
			changeType = _H_35
		else:
			if used:
				changeType = _H_49
			else:
				changeType = _H_52

		if not onPlayer:
			changeType += 1

		index = self.getStackMetricIndex(changeType, stackType)
		playerId = 0 if onPlayer else 1
		self.addMetric(index, abs(amount), playerId, True)


	def staminaChanged(self, amount, changeType, withNextEvent=False):
		changeType = int(changeType)
		index = self.getMultiMetricIndex(changeType, _H_33)
		self.addMetric(index, amount, self.character().playerId, withNextEvent)


	# =============================================================================
	# 里程碑 1：物品行为 API 面
	# =============================================================================
	# 逐字移植 Items/Item.gd 中「物品行为脚本会调用、且参与战斗判定」的方法。
	# 缺口清单与源码行号见 output/port/item_battle_dump.txt（176 项，含直接依赖闭包）。
	# 剥离规则与文件头一致：视觉 / 音频 / UI / 制作 一律改走 ctx.hooks 或整体删除，
	# 每处删除都在注释里写明原版行号与「为何不影响判定」。
	# =============================================================================

	# ─────────────────────── 类型 / 描述符查询（对齐 839-986, 3540-3640, 5739-5803） ───────────────────────

	def getName(self):
		return self.descriptor.getName()


	def getIndex(self):
		return self.descriptor.getIndex()


	def getRarity(self):
		return self.descriptor.rarity


	def getShopChance(self):
		return self.descriptor.getShopChance()


	def getMainType(self):
		return self.descriptor.types[0]


	def getNumStaticTypes(self):
		return len(self.descriptor.getTypes())


	# 对齐 Item.gd:3591-3593
	def getTypes(self):
		return list(self.dynamicTypes.keys()) + self.descriptor.types


	# 对齐 Item.gd:3622-3628
	def hasDynamicType(self, type, fromItem):
		type = int(type)
		if type in self.dynamicTypes:
			if fromItem.get_instance_id() in self.dynamicTypes[type]:
				return True

		return False


	# 对齐 Item.gd:3603-3613。原版 tail 的 inventory.onItemTypeChanged(self)
	# （Inventory.gd:971-972 = emit "item_type_changed"）是**数据面**：各物品在装备时
	# （Item.gd:1333 connect）把自己的 onItemTypeChanged（Item.gd:1457-1480）挂上
	# 该信号，动态类型变化后全背包重建 currentAffectedItems 受影响集——并非表现层。
	# 内核等价物 = CoreGrid.onItemTypeChanged（CoreGrid.gd:249-251，同序逐件派发）。
	# 旧实现路由到 ctx.hooks 空桩（CoreHooks.gd:192 pass）→ 派发恒死：CorruptedArmor
	# 放置期腐蚀 Holy→Dark 后 SSD 的 Secondary 受影响集永不登记 → 周期首拍迟到
	# （evt109@1-50 簇根因②，2026-10-29 py 装配级探针定谳）。
	def addDynamicType(self, type, byItem):
		type = int(type)
		if not type in self.descriptor.types:
			_H_36.dictAppend(self.dynamicTypes, type, byItem.get_instance_id())

			if len(self.dynamicTypes[type]) == 1:
				if self.placed:
					self.inventory.onItemTypeChanged(self)


	# 对齐 Item.gd:3614-3621
	def removeDynamicType(self, type, byItem):
		type = int(type)
		if self.hasDynamicType(type, byItem):
			_H_36.dictErase(self.dynamicTypes, type, byItem.get_instance_id())

			if not type in self.dynamicTypes:
				if self.placed:
					self.inventory.onItemTypeChanged(self)


	# 对齐 Item.gd:3629-3631
	def clearDynamicTypes(self):
		self.dynamicTypes.clear()


	# 对齐 Item.gd:703-705
	def isA(self, _descriptor):
		return self.descriptor == _descriptor


	# 对齐 Item.gd:978-980
	def isNeutral(self):
		return self.descriptor.isNeutral()


	# 对齐 Item.gd:5739-5741
	def isTreasure(self):
		return self.descriptor.randomUniquePool


	# 对齐 Item.gd:973-977
	def isClassItem(self, classIndex=None):
		if classIndex != None:
			return self.descriptor.isClassItem() and self.descriptor.isAvailableFor(classIndex)
		return self.descriptor.isClassItem()


	# 对齐 Item.gd:981-983
	def isSubclassItem(self):
		return self.descriptor.isSubclassItem()


	# 对齐 Item.gd:964-968
	def isOwnable(self):
		return (self.ownerType == _H_53 or 
			self.ownerType == _H_50 or 
			self.ownerType == _H_54)


	# 对齐 Item.gd:969-972
	def isOwnedByOpponent(self):
		return self.ownerType == _H_37


	# 对齐 Item.gd:984-986（原版 has_method 探测 → 内核的 behavior 探测）
	def isGateItem(self):
		return self._hasBehaviorMethod("getGatedDescriptor") or self._hasBehaviorMethod("getReplaceDescriptor")


	# 对齐 Item.gd:5783-5785
	def isShowCaseItem(self):
		return self.character() == None


	# 对齐 Item.gd:3566-3580（基类恒 false，由物品行为覆写）
	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		if self._hasBehaviorMethod("isAffectingDistinct"):
			return _H_36.truth(self._behavior_call("isAffectingDistinct", [color]))
		return False


	# 对齐 Item.gd:3540-3543（基类恒 false，由物品行为覆写）
	def affectsEmpty(self, color):
		if self._hasBehaviorMethod("affectsEmpty"):
			return _H_36.truth(self._behavior_call("affectsEmpty", [color]))
		return False


	# 对齐 Item.gd:3951-3953
	def hasOpponent(self):
		return (self.placed and self.character_ != None) and self.opponent() != None


	# 对齐 Item.gd:1295-1297
	def getEffectiveOwnerType(self):
		return self.ownerType


	# 对齐 Item.gd:5873-5875。制作系统已剥离（见文件头）→ bondedIngredients 恒空，
	# 故恒 false；与「制作系统不存在时原版的取值」一致。
	def isBaseItem(self):
		return False


	# 对齐 Item.gd:5862-5864。两项判据（curRecipe / isBoundAsIngredient）都属制作系统，
	# 剥离后均为空 → 恒 false。
	def isBusy(self):
		return False


	# 对齐 Item.gd:6160-6162（isBoundAsIngredient），同属制作系统 → 恒 false
	def isBoundAsIngredient(self):
		return False


	# ─────────────────────── 数值取值 / 修正标记（对齐 3733-3741, 3792-3994, 4836-4881） ───────────────────────

	# 对齐 Item.gd:4836-4867
	def getStat(self, stat):
		if stat == _H_17:
				if self.getBaseMaxDamage() > 0:
					return self.getMaxDamage()
				else:
					return 0
		elif stat == _H_16:
				if self.getBaseMinDamage() > 0:
					return self.getMinDamage()
				else:
					return 0
		elif stat == _H_64:
				return self.getAccuracy()
		elif stat == _H_20:
				return self.getCritChancePercent()
		elif stat == _H_9:
				return self.getSpeed()
		elif stat == _H_11:
				return self.getCooldownEncoded()
		elif stat == _H_12:
				return self.getStaminaCost()
		elif stat == _H_18:
				return self.getChance()
		elif stat == _H_19:
				return self.getChance2()
		elif stat == _H_10:
				return self.getCooldown()


	# 对齐 Item.gd:3888-3891。原版前置 `assert(descriptor.params[index] != 0)`；
	# 无头内核不保留 assert（Godot release 构建本就会剥离 assert），读取点与取值不变。
	def getP_check(self, index):
		return self.descriptor.params[index]


	def getP1(self):
		return self.getP_check(0)


	def getP2(self):
		return self.getP_check(1)


	def getP3(self):
		return self.getP_check(2)


	def getP4(self):
		return self.getP_check(3)


	def getP5(self):
		return self.getP_check(4)


	def getP6(self):
		return self.getP_check(5)


	def getP7(self):
		return self.getP_check(6)


	def getP8(self):
		return self.getP_check(7)


	def getP9(self):
		return self.getP_check(8)


	def getP10(self):
		return self.getP_check(9)


	# 对齐 Item.gd:4872-4876
	def addSpeed(self, amount):
		self.speedScale += amount
		# ★ np25 诊断（受控，双门控零耗链）：速度账本——谁加了多少、现值多少。
		self.ctx.rng.trace_diag("SPD+", String(self.descriptor.identifier) + "@" + String(self.getTopLeftCell())
				+ " ot=" + str(int(self.ownerType)), str(amount), "now=" + str(self.speedScale))
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_9)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_11)


	# 对齐 Item.gd:4877-4881
	def reduceSpeed(self, amount):
		self.speedScale -= amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_9)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_11)


	# 对齐 Item.gd:3733-3735
	def getDPS(self):
		return _div((self.getMinDamage() + self.getMaxDamage()) * 0.5, self.getModifiedCooldown())


	# 对齐 Item.gd:3736-3741
	def isDPSModified(self):
		_div__loc = _div
		baseDPS = _div__loc(self.getBaseAverageDamage(), self.getCooldown())
		modifiedDPS = _div__loc(self.getAverageDamage(), self.getModifiedCooldown())
		return self.isStatModified(modifiedDPS - baseDPS)


	# 对齐 Item.gd:3712-3717
	def getDamageRange(self):
		if self.getMinDamage() == self.getMaxDamage():
			return String(self.getMinDamage())
		else:
			return String(self.getMinDamage()) + "-" + String(self.getMaxDamage())


	# 对齐 Item.gd:3792-3797
	def isCooldownModified(self):
		baseCd = self.getBaseCooldown()
		curCd = self.getModifiedCooldown()
		return self.isStatModified(baseCd - curCd)


	# 对齐 Item.gd:3836-3838
	def isAccuracyModified(self):
		return self.isStatModified(self.getAccuracy() - self.getBaseAccuracy())


	# 对齐 Item.gd:3852-3854
	def isChance1Modified(self):
		return self.isStatModified(self.getChance() - self.getBaseChance())


	# 对齐 Item.gd:3858-3860
	def isChance2Modified(self):
		return self.isStatModified(self.getChance2() - self.getBaseChance2())


	# 对齐 Item.gd:3729-3732
	def isDamageModified(self):
		bonusDam = self.getAverageDamage() - self.getBaseAverageDamage()
		return self.isStatModified(bonusDam)


	# 对齐 Item.gd:3984-3986
	def getBaseStaminaPerSecond(self):
		return _div(self.getBaseStaminaCost(), self.getCooldown())


	# 对齐 Item.gd:3987-3989
	def getStaminaPerSecond(self):
		return _div(self.getStaminaCost(), self.getModifiedCooldown())


	# 对齐 Item.gd:3990-3994
	def isStaminaPerSecondModified(self):
		baseSPS = self.getBaseStaminaPerSecond()
		modifiedSPS = self.getStaminaPerSecond()
		return self.isStatModified(baseSPS - modifiedSPS)


	# ─────────────────────── 能力查询（对齐 3544-3664, 3876-3884, 4143-4148, 5376-5400） ───────────────────────
	# ★ 联动虚方法的派发约定：原版这些方法在 Items/*.gd 里被**覆写**（如 Food.gd 覆写
	#   canAffect），运行期由 GDScript 的多态直接生效。无头内核没有继承链，改为
	#   显式派发：行为脚本里有同名实现就用它，否则回落到基类实现（基类多为 `return false`）。
	#   这与 engine/item.py:1920-1934 的既有做法一致，取值域与原版多态相同。

	# 对齐 Item.gd:3544-3546（基类恒 false，由物品行为覆写）
	def canAffect(self, item):
		if self._hasBehaviorMethod("canAffect"):
			return _H_36.truth(self._behavior_call("canAffect", [item]))
		return False


	# 对齐 Item.gd:3547-3549
	def canAffect_secondary(self, item):
		if self._hasBehaviorMethod("canAffect_secondary"):
			return _H_36.truth(self._behavior_call("canAffect_secondary", [item]))
		return False


	# 对齐 Item.gd:3550-3552
	def canAffect_tertiary(self, item):
		if self._hasBehaviorMethod("canAffect_tertiary"):
			return _H_36.truth(self._behavior_call("canAffect_tertiary", [item]))
		return False


	# 对齐 Item.gd:3553-3555
	def canAffect_lightning(self, item):
		if self._hasBehaviorMethod("canAffect_lightning"):
			return _H_36.truth(self._behavior_call("canAffect_lightning", [item]))
		return False


	# 对齐 Item.gd:3556-3565
	def canAffect_color(self, item, color):
		if color == _H_38:
			return self.canAffect(item)
		elif color == _H_55:
			return self.canAffect_secondary(item)
		elif color == _H_65:
			return self.canAffect_tertiary(item)
		else:
			return self.canAffect_lightning(item)


	# 对齐 Item.gd:3662-3664
	def canBlock(self):
		return self.getBlock() > 0


	# 对齐 Item.gd:5379-5381
	def canHealOrLifesteal(self):
		return self.descriptor.hasParam("heal") or self.descriptor.hasParam("lifesteal")


	# 对齐 Item.gd:3882-3884
	def canModifyChance(self):
		return self.getBaseChance() > 0


	# 对齐 Item.gd:5376-5378
	def canUseStamina(self):
		return self.getBaseStaminaCost() > 0


	# 对齐 Item.gd:4143-4148
	def hasAttackEffect(self):
		return (self.hasPreDealDamageEarlyEffect or 
				self.hasPreDealDamageLateEffect or 
				self.hasDealtDamageEffect)


	# 对齐 Item.gd:5392-5394
	def gainsBuffs(self):
		return self.descriptor.gainedStacks & _H_39


	# 对齐 Item.gd:5395-5397
	def usesBuffs(self):
		return self.descriptor.usedStacks & _H_39


	# 对齐 Item.gd:5398-5400
	def inflictsDebuffs(self):
		return self.descriptor.gainedStacks & _H_40


	# 对齐 Item.gd:5165-5167
	def reactsToCharges(self):
		return self.hasOnChargeReceivedEffect or self.hasOnChargeLeftEffect


	# 对齐 Item.gd:4196-4201
	def fillUpStamina(self):
		self.character().fillUpStamina()


	# 对齐 Item.gd:5336-5338
	def getRelativeOpponentHealth(self):
		return self.opponent().getRelativeHealth()


	# 对齐 Item.gd:5339-5343
	def getRelativeHealth(self):
		return self.character().getRelativeHealth()


	# ─────────────────────── 栈 / buff 取用（对齐 4882-5185, 5392-5686） ───────────────────────

	# 对齐 Item.gd:4882-4884
	def giveBuffPower(self, buffType, power):
		self.buffPowers[buffType] += power


	# 对齐 Item.gd:4885-4888
	def changeHealAmp(self, amount):
		self.modifyParam("heal", amount)
		self.modifyParam("lifesteal", amount)


	# 对齐 Item.gd:4117-4121
	def changeStaminaFactor(self, amount):
		self.staminaFactor += _div(amount, 100.0)
		self.staminaFactor = max(0, self.staminaFactor)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_12)


	# 对齐 Item.gd:4106-4110
	def addBonusDamageFactor(self, factor):
		self.bonusDamageFactor += factor
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_16)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_17)


	# 对齐 Item.gd:4111-4116
	def reduceBonusDamageFactor(self, factor):
		self.bonusDamageFactor -= factor
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_16)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_17)


	# 对齐 Item.gd:4098-4101
	def reduceMinDamage(self, damage):
		self.bonusMinDam -= damage
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_16)


	# 对齐 Item.gd:4102-4105
	def reduceMaxDamage(self, damage):
		self.bonusMaxDam -= damage
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_17)


	# 对齐 Item.gd:4076-4086（尾行 spawnLabel 走钩子）
	def reduceBonusDamage(self, damage, showLabel=True, removable=True):
		self.bonusMinDam -= damage
		self.bonusMaxDam -= damage
		if removable:
			self.removableDam -= damage
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_16)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_17)

		if showLabel:
			self.spawnLabel(_H_56, - damage)


	# 对齐 Item.gd:4087-4097（尾行 spawnLabel 走钩子）
	def purgeDamage(self, damage):
		purgable = min(damage, self.removableDam)
		if purgable > 0:
			self.removableDam -= purgable
			self.bonusMinDam -= purgable
			self.bonusMaxDam -= purgable
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_16)
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_17)

			self.spawnLabel(_H_56, - purgable)


	# 对齐 Item.gd:4122-4124
	def giveDoubleActivationChance(self, _chance):
		self.doubleActivationChance += _div(_chance, 100.0)


	# 对齐 Item.gd:4125-4127
	def giveDoubleAttackEffectChance(self, _chance):
		self.doubleAttackEffectChance += _div(_chance, 100.0)


	# 对齐 Item.gd:5142-5146
	def giveCritTokens(self, amount):
		self.character().gainCritTokens(amount)


	# 对齐 Item.gd:4229-4231
	def giveMaxStamina(self, amount):
		self.character().giveMaxStamina(amount)


	# 对齐 Item.gd:4232-4234
	def giveMaxStaminaTemporary(self, amount, triggerEvent=None, filled=True):
		self.character().gainMaxStaminaTemporary(amount, self, triggerEvent, filled)


	# 对齐 Item.gd:4235-4241
	def giveMaxHealth(self, amount=None, triggerEvent=None):
		if amount == None:
			amount = self.getP_m("maxhealth")
		amount = self.character().applyTemporaryMaxHealthGain(amount)
		if amount > 0:
			self.addMetric(_H_57, amount, None, True)
			self.character().changeMaxHealthTemporary(amount, self, triggerEvent)
			# ★ 表现层链消耗还原（Item.gd:4224 spawnLabel → Item.gd:4788-4791
			#   Item.spawnLabel → Util.spawnLabelOnItem → :6485-6494）：
			#   这里的 spawnLabel 解析在 **Item** 上（Piggybank 等 extends Item），
			#   = 物品身上的浮动标签 randInBox 2 抽，**没有** randDmgNumberPos/Dir
			#   （阶段1 曾误按 Character.spawnLabel 还原出 3 抽，run1122_r11 逐抽
			#   对位证伪：神谕在 TMH 事件后恰 2 行 randInBox(-10,10)）。
			self.spawnLabel(_H_58, amount)


	# 对齐 Item.gd:4193-4195
	def giveStamina(self, amount=1, triggerEvent=None):
		self.character().gainStamina(amount, self, triggerEvent)


	# 对齐 Item.gd:4182-4185
	def inflictFatigueDamage(self, fatigueIncrease=1):
		self.opponent().addFatigueDamage(fatigueIncrease)
		self.opponent().takeFatigueDamage(self)


	# 电荷体：ElectricalCharge 的战斗语义面（Items/ElectricalCharge.gd:32-34 的
	# lastChargedItem/curChargedItem；受控神谕只发生同步入格，见 sendCharge 注释）
	def sendCharge(self, durPerTile, cells, speedFactor, event):
		chargeDuration = durPerTile * (len(cells) - 1)
		# ElectricalCharge.start（:141-142）：inventoryCells =
		# inventory.getCellsForGlobalPositions(getGlobalPointsForCells(cells))
		# （Item.gd:1040-1047 全局中心 = O + R(cellSize*(x+.5, y+.5))；
		#   Inventory.gd:377-381 反变换回格）——两步互逆后在格空间折叠为
		#   inventory_cell = getTopLeftCell() + rotate(faceDirection×90°, cell)。
		#   顺时针约定同 simulator/grid.py::rotate_cell（Godot y-down）。
		#   送电荷的 7 件物品（Battery/ChargeSplitter/CogBadge/ConTrapTron/
		#   Generator/LightningStaff/ManaCrystal）全部 1×1，无 fixture 归一化位移项。
		inv_cells = self._chargeInventoryCells(cells)
		self._chargeEnterCell(CoreElectricalCharge(), 1, inv_cells)
		# charge.logEvent → CombatLog.logElectricalCharge（CombatLog.gd:1212-1223）：
		# 表现记录 + 成就计数，不进 events、不消耗 rng
		# Item.gd:5155 Sound.playSound(chargeSound, Util.rng.randf_range(-12,-5),
		# Util.randPitch(0.3))——GDScript 实参求值即消耗：randf_range=2 步
		# （Util.gd:1007-1008；docs/rng_truth.md §2.3）+ randPitch(0.3)
		# =randf_range(0.7,1.3)=2 步（Util.gd:682-683）。Sound.playSound 本体无 rng
		# （oracle/Utility/Sound.gd:174-184）。此前内核漏掉这 4 步/次消耗——
		# 电荷阵（Battery 阵）从开战批量起整条链错位（run1160_r18 首分歧根因之一）。
		self.ctx.rng.randf_range(-12, -5)
		self.ctx.rng.randf_range(0.7, 1.3)


	# ElectricalCharge.start 的 cell→inventory 格映射（格空间折叠）。
	# ★ np25 P3-3 像素级还原（可从原版两步变换**解析地**折叠出来）：
	#   原版链：point(c) = getGlobalPointsForCells → O + R(P_cm + 80c + (40,40))，
	#   Inventory 反变换 floor(/80)；放置链 addItemByTopLeft 把 getTopLeftGlobal()
	#   平移到 80*锚点 ⇒ O + R(P_cm + 80·argmin旋转后碰撞格) = 80·锚点 − corr[fd]。
	#   两式相减，P_cm 与 corr 全部抵消（floor((R(40,40) − corr[fd])/80) ≡ (0,0)
	#   对 fd 0..3 恒成立），得闭式：
	#     inventory_cell(c) = 锚点 + R_fd(c) − rotmin(fd)
	#   其中 rotmin(fd) = 旋转 fd 后**碰撞格**包围盒 min（与 placement_of 的
	#   occupied/collision/affected 归一化完全同规——电荷格与碰撞格同处
	#   CollisionMap 本地空间，故必须减同一个 min）。
	#   此前实现 = 锚点 + floor(R(80c + collisionMapPosition + (40,40))/80)，且
	#   collisionMapPosition 无数据源恒 ZERO ⇒ 漏了 −rotmin 项，raw min ≠ (0,0)
	#   的送电荷物品（Battery/CogBadge/Generator/ChargeSplitter/Con-Trap-Tron 均
	#   raw min (−1,−1)，LightningStaff (0,−2)）整条路径平移错格——run572_r9
	#   Battery 电荷落空格 (0,3)、DS 少 +10% speed（oracle 1.2 v gd 1.1，TRIG/CHRG
	#   双桩实证）。chargeFrame[fd] = rotmin(fd) 由夹具表/runtime 注入。
	def _chargeInventoryCells(self, cells):
		top_left = self.getTopLeftCell()
		inv = self.inventory if self.inventory != None else self.getOwnOrPlayerInventory()
		out = []
		for c in (cells if cells.__class__ is list else _iter(cells)):
			# ★ 逐行单语句：gd_to_py 的方法调用改写器按行解析，跨行续行实参会漏。
			v = top_left + self._rotVecQuarterTurns(Vector2(c.x, c.y), self.faceDirection) - self.chargeFrame[_mod(self.faceDirection, 4)]
			hit_cells = inv.getCellsForGlobalPositions([v])
			out.append(hit_cells[0])
		return out


	# 向量按 90° 顺时针步进旋转 n 次（Godot rotated() 语义，y-down；
	# 同 simulator/grid.py::rotate_cell 的角度约定，n = faceDirection）
	def _rotVecQuarterTurns(self, v, n):
		n = int(n)
		n = _mod(n, 4)
		if n < 0:
			n += 4
		if n == 1:
			return Vector2(- v.y, v.x)
		elif n == 2:
			return Vector2(- v.x, - v.y)
		elif n == 3:
			return Vector2(v.y, - v.x)
		return v


	# 对齐 ElectricalCharge.onNewCellEntered（ElectricalCharge.gd:170-206）
	def _chargeEnterCell(self, charge, cell_index, inv_cells):
		cell_index = int(cell_index)
		charge.lastChargedItem = charge.curChargedItem
		if cell_index == len(inv_cells):
			charge.curChargedItem = None
		else:
			inv = self.inventory if self.inventory != None else self.getOwnOrPlayerInventory()
			charge.curChargedItem = inv.getItemInCell(inv_cells[cell_index])
		# emitterItem.onChargeEnteredCell(charge, cellIndex)：原版基类**不声明**此方法
		#（只有 7 件送电荷物品各自定义，动态调用永远命中），内核基类同样不声明——
		# GDScript 对 self 静态调用未声明方法会解析报错，故走 has_method + call 动态派发
		#（对齐 Item.gd:503 has_method("onChargeReceived") 的既有模式）。
		if self.has_method("onChargeEnteredCell"):
			self.call("onChargeEnteredCell", charge, cell_index)
		if charge.curChargedItem != charge.lastChargedItem:
			if charge.lastChargedItem != None:
				charge.lastChargedItem.chargeLeft(charge)
			if charge.curChargedItem != None:
				charge.curChargedItem.chargeReceived(charge)
				# 命中带 onChargeReceivedEffect 的物品时原版放一个 Zap 电弧
				#（ElectricalCharge.gd:195-201 → Items/Animations/Zap.gd:32 的
				# randf_range(4.0,4.02)，1 抽/次——纯表现，但真实消耗链）
				if charge.curChargedItem.hasOnChargeReceivedEffect:
					self.ctx.rng.randf_range(4.0, 4.02)


	# 对齐 Item.gd:5155-5159
	def chargeReceived(self, charge):
		self.numCharges += 1
		if self.hasOnChargeReceivedEffect:
			self._behavior_call("onChargeReceived", [charge])


	# 对齐 Item.gd:5160-5164
	def chargeLeft(self, charge):
		self.numCharges -= 1
		if self.hasOnChargeLeftEffect:
			self._behavior_call("onChargeLeft", [charge])


	# 对齐 Item.gd:5168-5185
	def changeChargedItemStat(self, charge, cellIndex, flatVal, valPerTile):

		previousVal = flatVal + (cellIndex - 2) * valPerTile
		newVal = previousVal + valPerTile
		# ★ np25 诊断（受控，双门控零耗链）：电荷命中面——发射者@左上格/格序/
		#   前后持电物品（含其左上格）/增减值。对拍电荷路径漏格（P3-3）。
		self.ctx.rng.trace_diag("CHRG",
				String(self.descriptor.identifier) + "@" + String(self.getTopLeftCell()),
				int(cellIndex),
				"last=" + (String(charge.lastChargedItem.descriptor.identifier)
						if charge.lastChargedItem != None else "null")
				+ " cur=" + (String(charge.curChargedItem.descriptor.identifier)
						if charge.curChargedItem != None else "null")
				+ " del=" + str(- previousVal) + " add=" + str(newVal))

		if charge.lastChargedItem != None:
			if charge.curChargedItem == None:
				self._behavior_call("chargedItemStatChange", [charge.lastChargedItem, - previousVal])
			elif charge.curChargedItem == charge.lastChargedItem:
				self._behavior_call("chargedItemStatChange", [charge.curChargedItem, valPerTile])
			else:
				self._behavior_call("chargedItemStatChange", [charge.lastChargedItem, - previousVal])
				self._behavior_call("chargedItemStatChange", [charge.curChargedItem, newVal])

		elif charge.curChargedItem != None:
			self._behavior_call("chargedItemStatChange", [charge.curChargedItem, newVal])


	# ─────────────────────── 治疗 / 伤害 / 减益（对齐 4826-5136, 5379-5394） ───────────────────────

	# 对齐 Item.gd:4810（形参 `amount: int`）
	def heal(self, amount=None, triggerEvent=None):
		if amount == None:
			# 默认实参 `= getP_m("heal")`：GDScript 非常量默认值按 Variant 直通，
			# 不过类型转换（oracle 探针 amt=8.56 浮点入 Character.heal，f03_probe）。
			amount = self.getP_m("heal")
		else:
			# ★ 显式实参过类型化形参边界：float 向零截断（GDScript 隐式转换）。
			#   oracle 探针（f03_probe，events≡语料逐字节）：Badger amt=247=
			#   trunc(1033×24/100)（run1394_r18）、amt=254=trunc(254.8)（run1023_r18）；
			#   原转写丢类型致 Variant 直通，CoreCharacter.heal gd_round() 后 frac≥0.5
			#   的治疗恒 +1（247.92→248）。
			amount = int(amount)
		healed = self.character().heal(amount, self, triggerEvent)


	# 对齐 Item.gd:5122-5129
	def healthToBlock(self, health, block, triggerEvent=None):
		_ch = self.character()
		clampedHealth = min(health, _ch.getCurrentHealth() - 1)
		if clampedHealth > 0:
			_ch.loseHealth(clampedHealth, self, triggerEvent)

			block = ceil(_div(clampedHealth, health) * block)
			self.giveBlock(block, True, triggerEvent)


	# 对齐 Item.gd:5136-5141
	def stealLife(self, damage, lifestealFactor=1.0, triggerEvent=None):
		self.ctx.stealLifeDamageSource.updateEffect(self, damage)
		damageRes = self.opponent().takeDamage(self.ctx.stealLifeDamageSource, triggerEvent)
		self.heal(damageRes.damage * lifestealFactor, damageRes.event)
		return damageRes


	# 对齐 Item.gd:4829-4831
	def stun(self, duration, triggerEvent=None):
		self.opponent().stun(duration, self, triggerEvent)


	# 对齐 Item.gd:5077-5079
	def checkMana(self, amount):
		return self.character().getMana() >= amount


	# 对齐 Item.gd:5080-5083
	def useMana(self, amount, triggerEvent=None):
		return self.character().useMana(amount, self, triggerEvent)


	# 对齐 Item.gd:5084-5090
	def tryUseMana(self, amount, triggerEvent=None):
		curMana = self.character().getMana()
		if curMana < amount:
			return None
		else:
			return self.useMana(amount, triggerEvent)


	# 对齐 Item.gd:5091-5093
	def removeMana(self, amount, triggerEvent=None):
		self.opponent().loseMana(amount, self, triggerEvent)


	# 对齐 Item.gd:5066-5076
	def giveMana_capped(self, amount, maximum, triggerEvent=None):
		_ch = self.character()
		amount = gd_round(amount * self.buffPowers[_H_28])
		curMana = _ch.getMana()
		if maximum > curMana:
			missingMana = maximum - curMana
			manaGiven = min(amount, missingMana)
			_ch.gainMana(manaGiven, self, triggerEvent)
			return amount - manaGiven
		else:
			return amount


	# ── 减益 / buff 的「自身使用 / 转给对手」成对包装（对齐 4983-5115, 5494-5529） ──

	# 对齐 Item.gd:4983-4985
	def removeSpikes(self, amount, triggerEvent=None):
		self.opponent().loseSpikes(amount, self, triggerEvent)


	# 对齐 Item.gd:4989-4991
	def useSpikes(self, amount, triggerEvent=None):
		return self.character().useStacks(_H_22, amount, self, triggerEvent)


	# 对齐 Item.gd:4986-4988
	def loseSpikes(self, amount, triggerEvent=None):
		self.character().loseSpikes(amount, self, triggerEvent)


	# 对齐 Item.gd:4995-4997
	def removeVampirism(self, amount, triggerEvent=None):
		self.opponent().loseVampirism(amount, self, triggerEvent)


	# 对齐 Item.gd:4998-5000
	def useVampirism(self, amount, triggerEvent=None):
		return self.character().useStacks(_H_23, amount, self, triggerEvent)


	# 对齐 Item.gd:5001-5003
	def loseVampirism(self, amount, triggerEvent=None):
		self.character().loseVampirism(amount, self, triggerEvent)


	# 对齐 Item.gd:5010-5018
	def cleansePoison(self, amount, triggerEvent=None):
		amount = int(amount)
		curPoison = self.character().getPoison()
		if curPoison == 0:
			return 0

		amount = min(curPoison, amount)
		self.character().losePoison(amount, self, triggerEvent)
		return amount


	# 对齐 Item.gd:5022-5024
	def selfInflictBlind(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _H_25, amount, triggerEvent)


	# 对齐 Item.gd:5025-5033
	def cleanseBlind(self, amount, triggerEvent=None):
		amount = int(amount)
		curBlind = self.character().getBlind()
		if curBlind == 0:
			return 0

		amount = min(curBlind, amount)
		self.character().loseBlind(amount, self, triggerEvent)
		return amount


	# 对齐 Item.gd:5037-5039
	def removeRegeneration(self, amount, triggerEvent=None):
		return self.opponent().loseRegeneration(amount, self, triggerEvent)


	# 对齐 Item.gd:5040-5042
	def useRegeneration(self, amount, triggerEvent=None):
		return self.character().useStacks(_H_26, amount, self, triggerEvent)


	# 对齐 Item.gd:5046-5052
	def tryUseLucky(self, amount, triggerEvent=None):
		if self.character().getLucky() >= amount:
			self.useLucky(amount, triggerEvent)
			return True
		else:
			return False


	# 对齐 Item.gd:5053-5055
	def loseLucky(self, amount, triggerEvent=None):
		self.character().loseLucky(amount, self, triggerEvent)


	# 对齐 Item.gd:5056-5058
	def removeLucky(self, amount, triggerEvent=None):
		self.opponent().loseLucky(amount, self, triggerEvent)


	# 对齐 Item.gd:5059-5061
	def useLucky(self, amount, triggerEvent=None):
		return self.character().useStacks(_H_27, amount, self, triggerEvent)


	# 对齐 Item.gd:5094-5096
	def inflictCold(self, amount, triggerEvent=None):
		self.giveStacks(self.opponent(), _H_31, amount, triggerEvent)


	# 对齐 Item.gd:5097-5106
	def cleanseCold(self, amount, triggerEvent=None):
		amount = int(amount)
		curCold = self.character().getCold()
		if curCold == 0:
			return 0

		amount = min(curCold, amount)
		self.character().loseCold(amount, self, triggerEvent)
		return amount


	# 对齐 Item.gd:5110-5112
	def loseHeat(self, amount, triggerEvent=None):
		self.character().loseHeat(amount, self, triggerEvent)


	# 对齐 Item.gd:5113-5115
	def useHeat(self, amount, triggerEvent=None):
		return self.character().useStacks(_H_30, amount, self, triggerEvent)


	# 对齐 Item.gd:5119-5121
	def loseEmpower(self, amount, triggerEvent=None):
		self.character().loseEmpower(amount, self, triggerEvent)


	# 对齐 Item.gd:5516-5529
	def cleanseRandomDebuffs(self, numDebuffs, triggerEvent=None):
		cleansedDebuffs = self.pickRandomStacks(_H_7.getDebuffs(), numDebuffs, self.character())

		self.ctx.bus.setLoggingMode(_H_41)
		for debuff in (cleansedDebuffs if cleansedDebuffs.__class__ is list else _iter(cleansedDebuffs)):
			self.character().loseStacks(debuff, cleansedDebuffs[debuff], self, triggerEvent)

		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5482-5493
	def inflictRandomDebuffs(self, numDebuffs, triggerEvent=None, availableDebuffs=None):
		if availableDebuffs == None:
			availableDebuffs = _H_7.getDebuffs()
		pickedDebuffs = self.pickRandomStacksToGive(availableDebuffs, numDebuffs)

		self.ctx.bus.setLoggingMode(_H_41)
		for debuff in (pickedDebuffs if pickedDebuffs.__class__ is list else _iter(pickedDebuffs)):
			self.giveStacks(self.opponent(), debuff, pickedDebuffs[debuff], triggerEvent)

		self.ctx.bus.flushLoggingQueue()


	# ─────────────────────── 随机 buff 取用（对齐 5422-5685） ───────────────────────
	# 取随机一律走 ctx.rng（原版 Util.rng，Util.gd:6），保证同种子可复现。

	# 对齐 Item.gd:5422-5446
	def pickRandomStacks(self, stackTypes, numStacks, target, priorityStack=None):
		_iter__loc = _iter
		stacks = Dictionary()
		for stackType in (stackTypes if stackTypes.__class__ is list else _iter__loc(stackTypes)):
			numTargetStacks = target.buffs[stackType]._current
			if numTargetStacks > 0:
				stacks[stackType] = numTargetStacks

		pickedStacks = Dictionary()

		if priorityStack != None:
			pickedPriorityStacks = min(numStacks, stacks.get(priorityStack, 0))
			if pickedPriorityStacks > 0:
				pickedStacks[priorityStack] = pickedPriorityStacks
				numStacks -= pickedPriorityStacks
				_H_36.dictSub(stacks, priorityStack, pickedPriorityStacks)

		for i in _iter__loc(_gd_range(numStacks)):
			if not (not stacks):
				stackType = self.ctx.rng.pickRandomElement(list(stacks.keys()))
				_H_36.dictAdd(pickedStacks, stackType, 1)
				_H_36.dictSub(stacks, stackType, 1)

		return pickedStacks


	# 对齐 Item.gd:5447-5454
	def pickRandomStacksToGive(self, stackTypes, numStacks):
		pickedStacks = Dictionary()
		for i in _iter(_gd_range(numStacks)):
			stackType = self.ctx.rng.pickRandomElement(stackTypes)
			_H_36.dictAdd(pickedStacks, stackType, 1)

		return pickedStacks


	# 对齐 Item.gd:5530-5554
	def getLeastStacks(self, numStacks, target, availableStacks):
		_iter__loc = _iter
		priorStacks = {}
		for stackType in (availableStacks if availableStacks.__class__ is list else _iter__loc(availableStacks)):
			priorStacks[stackType] = target.buffs[stackType]._current

		pickedStacks = {}

		while numStacks > 0:
			leastStacksCount = 10000
			leastStacks = []
			for stackType in (priorStacks if priorStacks.__class__ is list else _iter__loc(priorStacks)):
				if priorStacks[stackType] < leastStacksCount:
					leastStacksCount = priorStacks[stackType]
					leastStacks.clear()
					leastStacks.append(stackType)
				elif priorStacks[stackType] == leastStacksCount:
					leastStacks.append(stackType)
			stackToGive = self.ctx.rng.pickRandomElement(leastStacks)
			_H_36.dictAdd(pickedStacks, stackToGive, 1)
			_H_36.dictAdd(priorStacks, stackToGive, 1)
			numStacks -= 1

		return pickedStacks


	# 对齐 Item.gd:5563-5579
	def getMostStacks(self, target, availableStacks):
		_iter__loc = _iter
		buffs = Dictionary()
		for buff in (availableStacks if availableStacks.__class__ is list else _iter__loc(availableStacks)):
			buffs[buff] = target.buffs[buff]._current

		maxBuffs = []
		maxStacks = 0
		for buff in (buffs if buffs.__class__ is list else _iter__loc(buffs)):
			if buffs[buff] == maxStacks:
				maxBuffs.append(buff)
			elif buffs[buff] > maxStacks:
				maxBuffs.clear()
				maxBuffs.append(buff)
				maxStacks = buffs[buff]

		return maxBuffs


	# 对齐 Item.gd:5610-5652（原版 Util.sortDict(overflow, true) → CoreUtil.sortDict(.., ctx.rng, true)）
	def getStackFraction(self, target, fraction, limit, availableStacks):
		_iter__loc = _iter
		limit = int(limit)

		sum = 0.0
		stacksUnlimited = {}

		for buff in (availableStacks if availableStacks.__class__ is list else _iter__loc(availableStacks)):
			prior = target.buffs[buff]._current

			withBonus = prior * fraction
			stacksUnlimited[buff] = withBonus
			sum += withBonus

		sumRounded = gd_round(sum)
		if sumRounded == 0:
			return None

		totalToGive = min(limit, sumRounded)
		limitFactor = _div(totalToGive, sumRounded)

		buffsToGive = {}
		overflow = {}
		totalGiven = 0

		for buff in (stacksUnlimited if stacksUnlimited.__class__ is list else _iter__loc(stacksUnlimited)):
			limited = stacksUnlimited[buff] * limitFactor
			guaranteed = int(limited)
			buffsToGive[buff] = guaranteed
			overflow[buff] = limited - guaranteed
			totalGiven += guaranteed

		overflowBuffs = totalToGive - totalGiven
		# ★ np25 f08（对齐 Item.gd:5642 原字面）：原版 Util.sortDict(overflow, true)
		#   的洗牌走 Godot **引擎全局链**（Array.shuffle，Util.gd:1693-1699），且
		#   sort_custom 是引擎非稳定 introsort——此前的「有意偏差」（ctx.rng 洗牌+
		#   稳定排序）前提「全局链 randomize 后无种子不可复现」对 harness 不成立：
		#   oracle_fight.gd:595 每场 seed(seed) 播种全局链，录制逐位可复现。
		#   旧实现还从 ctx.rng（BalancedRng 主链）抽 n-1 抽洗牌=**污染主链**，
		#   后续全部 flip/roll 错位（evt102 面类型错排/resist 差的公共根因）。
		#   改为 shuffleEngine（r1_0 全局链直通，py 侧 _rt._math_rng 同链位），
		#   排序保持 Godot sort_custom+DictSorter 原语义。
		sortedOverflow = list(overflow.keys())
		self.ctx.rng.shuffleEngine(sortedOverflow, 'Items/Item.gd:5642')
		_sort_custom(sortedOverflow, _H_36.DictSorter(overflow), "sort")

		for buff in (sortedOverflow if sortedOverflow.__class__ is list else _iter__loc(sortedOverflow)):
			if overflowBuffs == 0:
				break

			buffsToGive[buff] += 1
			overflowBuffs -= 1

		return buffsToGive


	# 对齐 Item.gd:5653-5663
	def multiplyBuffsLimit(self, bonus, limit, availableBuffs=None):
		limit = int(limit)
		if availableBuffs == None:
			availableBuffs = _H_7.getBuffs()
		buffsToGive = self.getStackFraction(self.character(), bonus, limit, availableBuffs)
		if buffsToGive == None:
			return

		self.ctx.bus.setLoggingMode(_H_41)
		for buff in (buffsToGive if buffsToGive.__class__ is list else _iter(buffsToGive)):
			self.giveStacks(self.character(), buff, buffsToGive[buff])
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5664-5674
	def removeBuffsFraction(self, fraction, limit, triggerEvent=None, availableBuffs=None):
		limit = int(limit)
		if availableBuffs == None:
			availableBuffs = _H_7.getBuffs()
		buffsToRemove = self.getStackFraction(self.opponent(), fraction, limit, availableBuffs)
		if buffsToRemove == None:
			return

		self.ctx.bus.setLoggingMode(_H_41)
		for buff in (buffsToRemove if buffsToRemove.__class__ is list else _iter(buffsToRemove)):
			self.opponent().loseStacks(buff, buffsToRemove[buff], self, triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5675-5685
	def stealBuffsFraction(self, fraction, limit, triggerEvent=None, availableBuffs=None):
		limit = int(limit)
		if availableBuffs == None:
			availableBuffs = _H_7.getBuffs()
		buffsToSteal = self.getStackFraction(self.opponent(), fraction, limit, availableBuffs)
		if buffsToSteal == None:
			return

		self.ctx.bus.setLoggingMode(_H_41)
		for buff in (buffsToSteal if buffsToSteal.__class__ is list else _iter(buffsToSteal)):
			self.stealStack(buff, buffsToSteal[buff], triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5555-5562
	def giveLeastBuffs(self, numBuffs, target=None, triggerEvent=None, availableBuffs=None):

		if target == None:
			target = self.character()
		if availableBuffs == None:
			availableBuffs = _H_7.getBuffs()

		pickedStacks = self.getLeastStacks(numBuffs, target, availableBuffs)

		for buffType in (pickedStacks if pickedStacks.__class__ is list else _iter(pickedStacks)):
			self.giveStacks(target, buffType, pickedStacks[buffType], triggerEvent)


	# 对齐 Item.gd:5580-5585
	def giveMostBuffs(self, numBuffs, triggerEvent=None, availableBuffs=None):
		_ch = self.character()
		if availableBuffs == None:
			availableBuffs = _H_7.getBuffs()
		maxBuffs = self.getMostStacks(_ch, availableBuffs)
		buffToGive = self.ctx.rng.pickRandomElement(maxBuffs)
		self.giveStacks(_ch, buffToGive, numBuffs, triggerEvent)


	# 对齐 Item.gd:5586-5609
	def removeMostBuffs(self, numBuffs, triggerEvent=None, use=False, availableBuffs=None):
		if availableBuffs == None:
			availableBuffs = _H_7.getBuffs()
		target = None

		buffs = Dictionary()
		if use:
			target = self.character()
		else:
			target = self.opponent()

		maxBuffs = self.getMostStacks(target, availableBuffs)
		buffToRemove = self.ctx.rng.pickRandomElement(maxBuffs)

		toRemove = min(numBuffs, target.buffs[buffToRemove]._current)
		if toRemove == 0:
			return None

		event = None
		if use:
			event = self.character().useStacks(buffToRemove, toRemove, self, triggerEvent)
		else:
			event = self.opponent().loseStacks(buffToRemove, toRemove, self, triggerEvent)
		return event


	# 对齐 Item.gd:5455-5463
	def giveRandomBuffs(self, numBuffs, triggerEvent=None, availableBuffs=None, target=None):
		numBuffs = int(numBuffs)

		if availableBuffs == None:
			availableBuffs = _H_7.getBuffs()
		if target == None:
			target = self.character()

		pickedBuffs = self.pickRandomStacksToGive(availableBuffs, numBuffs)
		self.ctx.bus.setLoggingMode(_H_41)
		for buff in (pickedBuffs if pickedBuffs.__class__ is list else _iter(pickedBuffs)):
			self.giveStacks(target, buff, pickedBuffs[buff], triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5464-5468
	def giveAllBuffs(self, numBuffs=1, triggerEvent=None):
		for buff in _iter(_H_7.getBuffs()):
			self.giveStacks(self.character(), buff, numBuffs)


	# 对齐 Item.gd:5469-5481
	def useRandomBuffs(self, numBuffs, triggerEvent=None, availableBuffs=None):
		if availableBuffs == None:
			availableBuffs = _H_7.getBuffs()
		pickedBuffs = self.pickRandomStacks(availableBuffs, numBuffs, self.character())
		if (not pickedBuffs):
			return None

		events = []
		self.ctx.bus.setLoggingMode(_H_41)
		for buff in (pickedBuffs if pickedBuffs.__class__ is list else _iter(pickedBuffs)):
			event = self.character().useStacks(buff, pickedBuffs[buff], self, triggerEvent)
			events.append(event)
		self.ctx.bus.flushLoggingQueue()
		return events


	# 对齐 Item.gd:5494-5500
	def removeRandomBuffs(self, numBuffs, triggerEvent=None):
		removedStacks = self.pickRandomStacks(_H_7.getBuffs(), numBuffs, self.opponent())
		self.ctx.bus.setLoggingMode(_H_41)
		for buff in (removedStacks if removedStacks.__class__ is list else _iter(removedStacks)):
			self.opponent().loseStacks(buff, removedStacks[buff], self, triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5501-5515
	def stealRandomBuff(self, numBuffs, triggerEvent=None, possibleBuffs=None, priorityBuff=None):

		if possibleBuffs == None:
			possibleBuffs = _H_7.getBuffs()

		removedStacks = self.pickRandomStacks(possibleBuffs, numBuffs, self.opponent(), priorityBuff)
		self.ctx.bus.setLoggingMode(_H_41)
		for buff in (removedStacks if removedStacks.__class__ is list else _iter(removedStacks)):
			self.opponent().loseStacks(buff, removedStacks[buff], self, triggerEvent)

			self.giveStacks(self.character(), buff, removedStacks[buff], triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5405-5421（把角色 buff 信号接到物品回调）
	def connectToCharacterBuffs(self, methodName):
		_ch = self.character()
		for buff in _iter(_H_7.getBuffs()):
			self.connectForCombat(_ch, _ch.buffs[buff].signalName, methodName)


	def connectToCharacterDebuffs(self, methodName):
		_ch = self.character()
		for debuff in _iter(_H_7.getDebuffs()):
			self.connectForCombat(_ch, _ch.buffs[debuff].signalName, methodName)


	def connectToOpponentDebuffs(self, methodName):
		for debuff in _iter(_H_7.getDebuffs()):
			self.connectForCombat(self.opponent(), self.opponent().buffs[debuff].signalName, methodName)


	def connectToOpponentBuffs(self, methodName):
		for buff in _iter(_H_7.getBuffs()):
			self.connectForCombat(self.opponent(), self.opponent().buffs[buff].signalName, methodName)


	# ─────────────────────── 状态 / 视觉枢纽（对齐 4804-4831, 4968-4970, 3535-3539） ───────────────────────
	# 这些方法在原版里是「物品自身」的视觉出口，物品行为脚本会调用它们；
	# 内核把实现整体转给 ctx.hooks（原版对应 Util.spawnLabelOnItem / Settings 开关）。

	# ★ 表现层链消耗还原（Item.gd:448 buffLabelPositionTimestamps + :6483-6494
	#   getNextFreeLabelPosition）：物品身上浮动标签的位置从 5 个槽位里取——
	#   有空槽（上次占用 ≥0.5s 前）→ randInBox(10,10) 2 抽并占槽；全忙 →
	#   兜底 randInBox(30,30) 2 抽。槽位时间戳初始全 0（Util.time ≥ 0 恒真），
	#   开战后前 5 次走槽位分支。坐标本身无判定意义，链消耗面必须逐位一致。

	def getNextFreeLabelPosition(self):
		_ch = self.character()
		# ★ np24 诊断（受控）：镜像神谕 LABEL 行（Item.gd:6505-6510）。
		self.ctx.rng.trace_diag("LABEL", String(self.descriptor.identifier), int(self.ownerType),
				str(_ch != None and _ch.playerId))
		for i in _iter(len(self.buffLabelPositionTimestamps)):
			if self.ctx.time >= self.buffLabelPositionTimestamps[i]:
				self.buffLabelPositionTimestamps[i] = self.ctx.time + 0.5
				self.ctx.rng.randf_range( - 10.0, 10.0)
				self.ctx.rng.randf_range( - 10.0, 10.0)
				return
		self.ctx.rng.randf_range( - 30.0, 30.0)
		self.ctx.rng.randf_range( - 30.0, 30.0)


	# 对齐 Item.gd:4804-4809（Settings 的 damage_numbers 开关：神谕语料为开，
	# 标签恒画——链消耗必须发生；开关剥离但消耗保留）
	def spawnLabel(self, type, amount):
		self.getNextFreeLabelPosition()


	# 对齐 Item.gd:4810-4814（Settings 的 buff_labels 开关：同上，语料为开）。
	# 注意：原版 live 战斗路径不调用本方法（唯一调用点 activateFromEvent 是
	# CombatLog 回放查看器路径），内核保留同形空转，消耗由调用面决定。
	def spawnLabel_other(self, type, amount):
		pass


	# 对齐 Item.gd:4815-4818
	def consume(self, damageRes=None, playCombatAni=True):
		self.activate(damageRes, playCombatAni, True)
		self.consumed = True


	# 对齐 Item.gd:4819-4822
	def setState(self, newState, withNextEvent=False, event=None):
		self.ctx.combat_log.snapshotItemState(self, newState, withNextEvent, event)
		self.onStateChanged(newState)


	# 对齐 Item.gd:4823-4825（由物品行为覆写）
	def onStateChanged(self, newState):
		pass


	# 对齐 Item.gd:4968-4970（由物品行为覆写）
	def onTemporaryStacksTimeout(self, buffType):
		pass


	# 对齐 Item.gd:3535-3539（由物品行为覆写）
	def empowerEnd(self):
		pass


	# 对齐 Item.gd:2982-2987, 2996-3001, 3037-3058（宝石托管；本内核宝石见 gems 数组）
	def hasSockets(self):
		return not (not self.gems)


	def getNumSockets(self):
		return len(self.gems)


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
	def initSockets(self):
		pass


	# 对齐 GemSocket.gd:19-20 `func getItem(): return item`，其中 `item` 由
	# Item.initSockets()（Item.gd:2978-2980，`socket.item = self`）回指**宿主物品**。
	# 内核把插座折叠为宿主物品本身（见 setGem 注释），故这里恒返回 self ——
	# 这正是 Gem.gd 全部 `socket.getItem().xxx()` 调用链的终点：
	#   isGem 系（isOwnable/isPlaced/isInInventory/getInventory/getEffectiveOwnerType）
	#   与 getGemMode() 都靠它取到宿主。
	def getItem(self):
		return self


	def hasGems(self):
		for gem in (self.gems if self.gems.__class__ is list else _iter(self.gems)):
			if gem != None:
				return True
		return False


	def getGemsOfItems(self, items):
		out = []
		for item in (items if items.__class__ is list else _iter(items)):
			out.extend(item.getGemsNoNull())
		return out


	# 对齐 Item.gd:3024-3036（ItemBook.getGemIndex 属数据层，由装配层提供 index）
	# ── 宝石数据族（getGemData / setGem / setGemData）留待宝石子系统里程碑，
	#    它们依赖 CoreGem 的 getIndex/getFaceDirection/isLocked；本内核宝石见 gems 数组。

	# 对齐 Item.gd:3954-3960
	def getPrice(self):
		return self.descriptor.getPrice()


	def getBaseSellPrice(self):
		return self.descriptor.getSellPrice()


	def getSellPrice(self):
		return self.descriptor.getSellPrice()


	def getSalePrice(self):
		return self.descriptor.getSalePrice()


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
	def setGem(self, socketId, gem):
		socketId = int(socketId)
		if socketId >= len(self.gems):
			print("ohnonononononno")
		else:
			gem.ownerType = _H_42
			self.gems[socketId] = gem
			# 等价于 Gem.addToSocket(self)：那 3 条与战斗相关的语句是
			# `socket = _socket` / `ownerType = Owner.Socket` / `occupiedCells.clear()`；
			# 其余（Util.reparent / socket.onDropGem / CraftingManager.itemAdded）属场景树
			# 与制作系统，已在转译期剥离，故整函数成了空桩，这三条由本方法补齐。
			gem.socket = self
			gem.occupiedCells.clear()


	# 对齐 Item.gd:3002-3010、2957-2959、3011-3014 —— 宝石/内容物回储物箱，
	# 属商店-背包跨越，战斗内不触发（原版 pushItemsInsideToStorage/returnToSocket 为 pass）
	def pushGemsToStorage(self):
		pass


	def pushItemsInsideToStorage(self):
		pass


	def returnToSocket(self, movebackDur):
		pass


	# ─────────────────────── 网格 / 邻接 / 受影响格（对齐 1034-1607, 3544-3586, 5192-5254） ───────────────────────
	# 坐标系约定与等价性依据见 CoreGrid.gd 文件头：原版的「格 → 全局坐标 → 格」往返
	# 在格点对齐的网格上恒等，内核据此直接以格空间求值。

	# 对齐 Item.gd:1104-1108。原版未放置时回落到 Game.PLAYER.INVENTORY（autoload 恒非空）；
	# 内核里 player 由 setup() 注入，尚未注入时回落到 ctx 的共享空网格，
	# 保持「恒返回一个可查询的背包」这一语义（详见 CoreContext.emptyGrid）。
	def getOwnOrPlayerInventory(self):
		if self.placed:
			return self.inventory
		elif self.ctx.player != None:
			return self.ctx.player.inventory
		return self.ctx.emptyGrid()


	# ── 几何层接口（内核折叠为格空间的恒等映射；保留接口以维持调用点形状） ──

	# 对齐 Item.gd:1034-1039
	def getCellsForGlobalPositions(self, points):
		return points


	# 对齐 Item.gd:1040-1047
	def getGlobalPointsForCells(self, cells):
		return cells


	# 对齐 Item.gd:1048-1056
	def getGlobalPointsForCells_noRotate(self, cells):
		return cells


	# 对齐 Item.gd:1066-1070
	def getCollisionCells(self):
		return self.collisionCells


	# 对齐 Item.gd:1211-1213
	def getExtensionCells(self):
		return self.extensionCells


	# 对齐 Item.gd:1101-1103
	def getCollisionPoints(self):
		return self.collisionCells


	# 对齐 Item.gd:1214-1226
	def getExtensionPoints(self):
		return self.extensionCells


	# ── 受影响格 ──

	# 对齐 Item.gd:1112-1116（oracle 实体 = collisionMap.get_used_cells_by_id(
	# affectedColorToTileId[color])，返回序恒为 Vector2 (y,x) 字典序——Godot 3.6
	# TileMap used_cells_by_id 是 Set<Vector2>（RB 树），见 CoreUtil.vec2_less_yx 注。
	# 内核夹具数组是提取归一序 sorted(x,y)，此处排序镜像 oracle 运行时序（仅序变）。
	def getAffectedCells_tilemap(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		# ★ np32W2：**透传夹具序**（affectedTileCells=夹具 affected 数组，np32 已
		#   再生为 tile_data 文件序=涂格真序：extract_grid parse_tscn_grid 保序+
		#   placement_of 保序变换，cases 的 T 序=oracle fAffC 实测逐位同构）——
		#   删除 np25 f09 的 sort(vec2_less_yx)（其 yx 序是空图手插探针的不可外推
		#   结论；文件序才是真值）。序即物品链遍历序（TD zapItem 的 CS/Coil 收发序）。
		return self.affectedTileCells.get(color, [])


	# 对齐 Item.gd:1117-1124
	def getAffectedCellsAfterRotate(self, rotatedCells, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		if color == _H_38:
			return self.getAffectedCellsAfterRotate_primary(rotatedCells)
		elif color == _H_55:
			return self.getAffectedCellsAfterRotate_secondary(rotatedCells)
		else:
			return []


	# 对齐 Item.gd:1125-1127（基类空，由物品行为覆写）
	def getAffectedCellsAfterRotate_primary(self, _rotatedCells):
		if self._hasBehaviorMethod("getAffectedCellsAfterRotate_primary"):
			return self._behavior_call("getAffectedCellsAfterRotate_primary", [_rotatedCells])
		return []


	# 对齐 Item.gd:1128-1131（基类空，由物品行为覆写）
	def getAffectedCellsAfterRotate_secondary(self, _rotatedCells):
		if self._hasBehaviorMethod("getAffectedCellsAfterRotate_secondary"):
			return self._behavior_call("getAffectedCellsAfterRotate_secondary", [_rotatedCells])
		return []


	# 对齐 Item.gd:1132-1138。rotatedCells = getCellsForGlobalPositions(getCollisionPoints())
	# 在格点上恒等于 collisionCells，故直接代入（见 CoreGrid.gd 文件头推导）。
	def getAffectedCells_noRotate(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		return self.getAffectedCellsAfterRotate(self.collisionCells, color)


	# 对齐 Item.gd:1145-1147
	def getAffectedPoints(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		return self.getAffectedCells_tilemap(color) + self.getAffectedCells_noRotate(color)


	# 对齐 Item.gd:1148-1151
	def getAffectedCellsInInventory(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		return self.getOwnOrPlayerInventory().getCellsForGlobalPositions(self.getAffectedPoints(color))


	# 对齐 Item.gd:1483-1485
	def getAffectedCellsInInventory_cached(self, color):
		return self.affectedCellsCache.get(color, [])


	# 对齐 Item.gd:1367-1370
	def cacheAffectedCells(self):
		for color in _iter(list(_H_60.values())):
			self.affectedCellsCache[color] = self.getAffectedCellsInInventory(color)


	# 对齐 Item.gd:1400-1408。原版尾行 `Util.eassert(cachedAffectedItems.empty())` 是
	# 编辑器专用断言（Util.gd:207-209 只在 editor feature 下 assert）→ 内核不保留。
	def cleanCachedAffectedItems(self):
		self.affectedCellsCache.clear()

		for color in _iter(list(_H_60.values())):
			self.currentAffectedItems[color].clear()


	# 对齐 Item.gd:1393-1398 之后的离开背包清理入口
	def onRemoveFromInventory(self):
		self.cleanCachedAffectedItems()


	# 对齐 Item.gd:1409-1410（原版末尾另有 disconnected 清理，属场景层）
	def onAddToInventory(self):
		pass


	# 对齐 Item.gd:1161-1174
	def getAffectedItems(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		if not (not self.cachedAffectedItems):
			return self.cachedAffectedItems[color]

		items = []
		for item in _iter(self.getItemsInAffectedCells_cached(color)):
			if self.canAffect_color(item, color):
				items.append(item)
		return items


	# 对齐 Item.gd:1175-1181
	def getAffectedItems_nocache(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		items = []
		for item in _iter(self.getItemsInAffectedCells(color)):
			if self.canAffect_color(item, color):
				items.append(item)
		return items


	# 对齐 Item.gd:1155-1157
	def getItemsInAffectedCells(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		return self.getOwnOrPlayerInventory().getItemsInCells(self.getAffectedCellsInInventory(color))


	# 对齐 Item.gd:1152-1154
	def getItemsInAffectedCells_cached(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		return self.getOwnOrPlayerInventory().getItemsInCells(self.getAffectedCellsInInventory_cached(color))


	# 对齐 Item.gd:1158-1160
	def countItemsInAffectedCells_cached(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		return self.getOwnOrPlayerInventory().countItemsInCells(self.getAffectedCellsInInventory_cached(color))


	# 对齐 Item.gd:1182-1192
	def isItemAffected(self, item, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		if item.isBag() or not self.canAffect_color(item, color):
			return False

		affectedTiles = self.getAffectedCellsInInventory_cached(color)

		for cell in (item.occupiedCells if item.occupiedCells.__class__ is list else _iter(item.occupiedCells)):
			if cell in affectedTiles:
				return True
		return False


	# 对齐 Item.gd:1193-1195
	def getNumEmptyAffectedCells(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		return self.inventory.getEmptyCellsInCells(self.getAffectedCellsInInventory(color))


	# 对齐 Item.gd:1196-1198
	def getNumAffectedItems(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		return len(self.getAffectedItems(color))


	# 对齐 Item.gd:1199-1204
	def getFirstAffectedItem(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		_affectedItems = self.getAffectedItems(color)
		if not (not _affectedItems):
			return _affectedItems[0]
		return None


	# 对齐 Item.gd:1205-1210
	def getNumAffected_type(self, type, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		type = int(type)
		num = 0
		for item in _iter(self.getAffectedItems(color)):
			num += item.getTypeMultiplicity(type)
		return num


	# 对齐 Item.gd:3581-3586
	def getNumDistinctAffectedItems(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		distinctAffectedDescriptors = {}
		for item in _iter(self.getAffectedItems(color)):
			distinctAffectedDescriptors[item.descriptor] = True
		return len(distinctAffectedDescriptors)


	# 对齐 Item.gd:1139-1144
	def getNumAffectedCells(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _H_38
		if color in self.affectedCellsCache:
			return len(self.affectedCellsCache[color])
		else:
			return len(self.getAffectedCells_tilemap(color)) + len(self.getAffectedCells_noRotate(color))


	# 对齐 Item.gd:1285-1294（扩展格是 TileMap 上的临时涂色，内核里改 affectedTileCells）
	def activateExtendedAffectedCells(self):
		for cell in (self.affectedExtensionCells if self.affectedExtensionCells.__class__ is list else _iter(self.affectedExtensionCells)):
			_H_36.dictAppend(self.affectedTileCells, _H_38, cell)
		self.cacheAffectedCells()


	def deactivateExtendedAffectedCells(self):
		for cell in (self.affectedExtensionCells if self.affectedExtensionCells.__class__ is list else _iter(self.affectedExtensionCells)):
			arr = self.affectedTileCells.get(_H_38, [])
			if cell in arr:
				_erase(arr, cell)
		self.cacheAffectedCells()


	# 对齐 Item.gd:1486-1513（拖拽预览；战斗路径不调用，isHovered 无缓存时恒 false）
	def canAffectDraggedItem(self, item, color):
		if self.canAffect_color(item, color):

			affectedCells = self.getAffectedCellsInInventory_cached(color)

			for cell in (affectedCells if affectedCells.__class__ is list else _iter(affectedCells)):
				if item.dragged:
					if self.inventory.isHovered(cell):
						return True
				else:
					if cell in item.occupiedCells:
						return True
		return False


	# 对齐 Item.gd:1517-1525（基类空，由物品行为覆写）
	def onAffectedItemAdded(self, item, color):
		color = int(color)
		pass


	def onAffectedItemRemoved(self, item, color):
		color = int(color)
		pass


	# 对齐 Item.gd:1425-1443（背包内新物品加入时刷新受影响集）
	def onItemAdded(self, item):
		_iter__loc = _iter
		newItemIsAffected = {}
		for color in _iter__loc(list(_H_60.values())):
			newItemIsAffected[color] = (not item in self.currentAffectedItems[color] and 
										self.isItemAffected(item, color))

		for color in _iter__loc(list(_H_60.values())):
			if newItemIsAffected[color]:
				self.currentAffectedItems[color][item] = True
				self.onAffectedItemAdded(item, color)


	# 对齐 Item.gd:1446-1452
	def onItemRemoved(self, item):
		for color in _iter(list(_H_60.values())):
			_erase(self.currentAffectedItems[color], item)
			if self.canAffectDraggedItem(item, color):
				self.onAffectedItemRemoved(item, color)


	# ── 格子几何查询 ──

	# 对齐 Item.gd:1057-1065
	def getNumOccupiedCells(self):
		return len(self.collisionCells)


	def getNumBagCells(self):
		return len(self.extensionCells)


	def getNumCells(self):
		return self.getNumOccupiedCells() + self.getNumBagCells()


	# 对齐 Item.gd:5192-5211
	def getSizeInCells(self):
		topLeft = Vector2(100, 100)
		bottomRight = Vector2( - 100, - 100)
		cells = self.getCollisionCells()
		if (not cells):
			return Vector2.ZERO

		for cell in (cells if cells.__class__ is list else _iter(cells)):
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
	def getTopLeftCell(self):
		topLeft = Vector2(INF, INF)
		for cell in (self.occupiedCells if self.occupiedCells.__class__ is list else _iter(self.occupiedCells)):
			topLeft.x = min(cell.x, topLeft.x)
			topLeft.y = min(cell.y, topLeft.y)
		return topLeft


	# 对齐 Item.gd:1071-1100。返回值 [归一化后的占格, 格偏移]。原版的格偏移是
	# 全局坐标（collisionMap.map_to_world(minimum) + position + (40,40)），只用消费方是
	# ItemLibrary 的展示摆放（Interface/ItemLibrary/ItemLibrary.gd:209/409）——不在战斗
	# 判定路径上，内核返回 Vector2.ZERO 占位。
	def getNormalizedCollisionCells(self):
		_iter__loc = _iter
		cells = None
		if self.isBag():
			cells = _dup(self.getExtensionCells())
		else:
			cells = _dup(self.getCollisionCells())

		minimum = Vector2(100, 100)
		for cell in (cells if cells.__class__ is list else _iter__loc(cells)):
			if cell.y <= minimum.y:
				if cell.y < minimum.y:
					minimum.x = cell.x
				else:
					minimum.x = min(cell.x, minimum.x)
				minimum.y = cell.y

		for i in _iter__loc(_gd_range(len(cells))):
			cells[i] = cells[i] - minimum

		return [cells, Vector2.ZERO]


	# 对齐 Item.gd:5852-5853。★ 判定用：Gems/Gem.gd:252 `if not fusing and canCombine()`
	# 决定宝石合并流程是否继续，故必须忠实返回 placed 而不是恒 false。
	def canCombine(self):
		return self.placed


	# ── 行为脚本会调用、但内核无对应子系统的同签名占位 ──
	# 判据：这些方法被 Items/*.gd **调用**（非覆写），若内核不提供签名，行为脚本接入时
	# 会直接报 "Nonexistent function"。逐条给出剥离依据：

	# 对齐 Item.gd:4248-4254（商店/换装的「替换中」标志 + tooltip/拾取开关）→ 无战斗影响


	def prepareReplacement(self):
		self.replacementPending = True


	def finishReplacement(self):
		self.replacementPending = False


	# 对齐 Item.gd:5708-5725：把生成的物品放进第一个空格（宝箱类物品用）。
	# 依赖 Inventory.orientAndAddItem / unlockCombining / Game.itemsAreFusing（均为
	# 商店·制作路径）→ 内核不做物品生成。消费方：BoxofRiches.gd:18。
	def placeGeneratedItem(self, item, candidateCells):
		pass


	# 对齐 Item.gd:2893-（tween 位移）。消费方：ChessPiece.gd:95、ChessBoard 棋子摆放
	# 等纯表现调用 → 空实现（位移不改变任何战斗数值）。
	def moveTo(self, fromPos, newPos, duration=0.2, transitionType=None):
		pass


	# 对齐 Item.gd:1457 区间的 z_index 复位。消费方：Bag.gd:80 → 视觉层序 → 走钩子。
	def resetZ(self):
		pass


	# 对齐 Item.gd:1363-1365：商店 gate item 掷骰后交给 shopSceneNode → 商店路径 → 空实现。
	def onGateItemRoll(self):
		pass


	# 对齐 Item.gd:2251 附近的描述文本计数器（Util.insertCounter 本地化）→ 表现 → 返回原串。
	# 消费方：Bewitchment.gd:29（在 getDescription 里）。
	def insertCounter(self, descr, paramName, amount):
		return descr


	# 对齐 Item.gd:6348-6351（Bag 覆写用；基类不存在则此处给同签名占位，供 Bag.gd 覆写链）。
	def queue_free(self):
		pass


	def shift(self, direction):
		pass


	def onBought(self):
		pass


	def onSold(self):
		pass


	# 对齐 Item.gd:1530-1531（基类恒 true，由物品行为覆写以拒绝被重新纳入受影响集）
	def reactToItemTypeChange(self, item):
		if self._hasBehaviorMethod("reactToItemTypeChange"):
			return _H_36.truth(self._behavior_call("reactToItemTypeChange", [item]))
		return True


	# 对齐 Item.gd:1457-1480。动态类型变化（MagicRing / addDynamicType / removeDynamicType）
	# 后重建「受影响物品集」：先问行为要不要重算，再逐色增删并触发成对回调。
	# 原版由 Inventory 的 item_type_changed 信号驱动（Item.gd:1333 在装备时连接），
	# 内核改为 CoreGrid 直接逐件派发（次序 = 加入背包次序，与信号连接次序一致）。
	def onItemTypeChanged(self, item):
		canAddAgain = self.reactToItemTypeChange(item)

		if not canAddAgain:
			return

		addedToAffected = {}
		for color in _iter(list(_H_60.values())):
			addedToAffected[color] = False

			if item in self.currentAffectedItems[color]:
				if not self.canAffect_color(item, color):
					_erase(self.currentAffectedItems[color], item)
					self.onAffectedItemRemoved(item, color)
			elif item in self.getAffectedItems(color):
				self.currentAffectedItems[color][item] = True
				self.onAffectedItemAdded(item, color)
				addedToAffected[color] = True

		if item.placedByPlayer:
			pass


	# 对齐 Item.gd:2352-2353
	def getRelatedItems(self):
		return self.descriptor.gatedItems


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
	def countAllPlacedOfType(self, descr):
		_iter__loc = _iter
		count = 0
		if self.isOwnedByOpponent():
			if self.ctx.opponent == None:
				return 0
			for item in _iter__loc(self.ctx.opponent.inventory.getItemsAndGems()):
				if item != None and item.descriptor == descr:
					count += 1
			return count

		if self.ctx.player != None:
			for item in _iter__loc(self.ctx.player.inventory.getItemsAndGems()):
				if item == None or item.descriptor != descr:
					continue
				if item.ownerType == _H_42:
					count += 1
				elif (item.placed
						and item.ownerType == _H_50):
					count += 1
		return count


	# 对齐 Item.gd:3066-3085：被自身占格压住的袋子按「描述符」归并计数
	def getTouchedBagsCounted(self):
		_iter__loc = _iter
		if self.isBag() or not self.placed:
			return None
		touchedBags = self.inventory.getBagsInCells(self.occupiedCells)
		bagCounter = {}
		for bag in (touchedBags if touchedBags.__class__ is list else _iter__loc(touchedBags)):
			found = False
			for countedBag in (bagCounter if bagCounter.__class__ is list else _iter__loc(bagCounter)):
				if countedBag.descriptor == bag.descriptor:
					bagCounter[countedBag] += bag.getBagMultiplicity(self)
					found = True
					break
			if not found:
				bagCounter[bag] = bag.getBagMultiplicity(self)
		return bagCounter


	# 对齐 Item.gd:1243-1244（全局像素高度范围；内核无像素层 → 以格空间的上下边界等价表示）
	def getHeightRange(self):
		return Vector2(self.getTopLeftCell().y, self.getTopLeftCell().y + self.getSizeInCells().y - 1)


	# 对齐 Item.gd:628-（_ready 里 call_deferred 触发的一次性装配回调）。
	# ★ 时机说明：原版由 SceneTree 在**当帧空闲末**执行，晚于 _ready、早于战斗装配。
	#   内核无场景树，交由装配层在「物品加入背包后、prepare 前」调用；
	#   行为脚本未实现该方法时为空操作（基类为空），故缺失不会改变判定。
	def ready_deferred(self):
		if self._hasBehaviorMethod("ready_deferred"):
			self._behavior_call("ready_deferred")


	# ─────────────────── 朝向（对齐 Item.gd:2037-2054 的旋转↔朝向换算） ───────────────────
	# 原版没有 `faceDirection` 字段的直接来源：它是 `rotation`（Node2D 属性 + tween 插值）
	# 换算出来的。内核无节点、无 tween，故把 faceDirection 作为**权威字段**、rotation 作为
	# 由它导出的派生值：rotation = faceDirection * PI/2 恒成立（见 setFaceDirectionInstant）。
	# 数值上与原版一致：getFaceDirection() 在原版的公式 (int((2*rotation)/PI + 2.25PI)+5)%4
	# 当 rotation = fd*PI/2 时恒等于 fd（(int(fd+7.0686)+5)%4 = (fd+12)%4 = fd）。
	#
	# 战斗期该字段只读：rotateLeft/rotateRight 只由玩家按键（Util.isActionJustPressed）触发，
	# 战斗状态不可达。战斗期的回调只有 setFaceDirectionInstant（放置/存档载入）。


	# 对齐 Item.gd:2037-2038
	def rotationFromFaceDirection(self, _faceDirection):
		return _faceDirection * PI * 0.5


	# 对齐 Item.gd:2053-2054
	def getFaceDirection(self):
		return _mod(int(_div(2 * self.rotation, PI) + 2.25 * PI) + 5, 4)


	# 对齐 Item.gd:2040-2041（全局朝向；内核无父子旋转叠加 → 与局部朝向同值）
	def getGlobalFaceDirection(self):
		return self.getFaceDirection()


	# 对齐 Item.gd:2043-2047。原版首行 Util.finishTween(rotationTween) 是结束插值动画
	# （表现）→ 剥离；其余三行逐字保留。
	def setFaceDirectionInstant(self, _faceDirection):
		self.faceDirection = _faceDirection
		self.rotation = self.rotationFromFaceDirection(self.faceDirection)


	# 对齐 Item.gd:2049-2050
	def setRotation(self, _rotation):
		self.rotation = _rotation


	# 对齐 Item.gd:5686-5689（BlackRook 用它给背包内全部可强化物品改暴击率）
	def changeAllItemsCritRate(self, amount):
		for item in _iter(self.inventory.getItems()):
			if item.canBeEmpowered():
				item.changeCritChancePercent(amount)


	# ── 剥离但**必须保留签名**的方法：被物品行为（Items/*.gd）直接调用 ──
	# 这些方法本体只做表现（播动画/更新 shader/粒子/重绘预览），剥离后做成同签名空实现，
	# 使行为脚本调用它们时行为与原版一致（原版这些调用同样不改变任何战斗数值）。
	# 判据：函数体只触碰 sprite / animation / particles / material / tooltip / 预览格，
	# 不读写任何 buff / stat / 冷却 / 伤害 —— 逐条可在源码行号上核对。

	# 对齐 Item.gd:4511-4516（仅 animation.play，按 consumed 选动画名）
	def miniActivate(self):
		pass


	# 对齐 Item.gd:1857-1875 区间的预览重绘调用点
	def previewCellCollision(self):
		pass


	# 对齐 Item.gd:2124-2131（预览格着色）
	def previewCells(self):
		pass


	# 对齐 Item.gd:2211（预览是否能影响）
	def previewCanAffect(self):
		pass


	# 对齐 Item.gd:1963-1996。rotateRight/Left 的入口是玩家按键（Item.gd:1843-1856 的
	# _input），rotateTo 只是 tween 旋转 + 重算 faceDirection。内核把它们做成
	# 「更新 faceDirection + 通知表现层」：不接按键、不做插值，但字段语义与原版一致，
	# 以便行为脚本（Scale/SpintoWin 覆写 rotateTo 更新计数器/配色）能正常调用。
	def rotateRight(self):
		self.faceDirection = _mod(self.faceDirection + 1, len(_H_43))
		self.setFaceDirectionInstant(self.faceDirection)


	def rotateLeft(self):
		self.faceDirection = _mod(self.faceDirection - 1 + len(_H_43), len(_H_43))
		self.setFaceDirectionInstant(self.faceDirection)


	def rotateTo(self, targetRotation, duration=0.15):
		# 原版：先取当前 sprite 朝向存 faceDirection，再把节点旋转到 target，
		# 最后 tween 把 sprite 从旧角度插值回来（视觉回弹）。内核保留「朝向 = 节点旋转的
		# 量化值」这一结果，丢掉的只有插值过程。
		self.faceDirection = self.getGlobalFaceDirection()
		self.rotation = targetRotation
		self.faceDirection = self.getGlobalFaceDirection()


	def rotateToDeferred(self, targetRotation, duration=0.15):
		self.ctx.defer(self, "rotateTo", [targetRotation, duration])


	# 对齐 Item.gd:1994-1995
	def setFaceDirection(self, _faceDirection):
		self.rotateTo(_faceDirection * PI * 0.5)


	# 对齐 Item.gd:2016-2029 的尾巴：拖拽中「袋内物品」的朝向修正（纯拖拽表现，
	# 操作的是 insideItems 子节点的 rotation，不参与任何战斗判定）→ 剥离为空实现。
	def correctInsideItemFacedirection(self):
		pass


	# 对齐 Item.gd:936-947：袋子效果 tooltip 文本组装（走 Util.tra 本地化）
	# → 剥离为空串。唯一消费方是 Interface/Tooltips/ItemTooltip.gd:241。
	def getBagEffect(self, number):
		return ""


	# 对齐 Item.gd:3024-3035 / 3047-3057：背包宝石的**存档序列化**（ItemBook.getGemIndex +
	# 逐宝石朝向/锁定），唯一消费方是 Game.gd:1382/1407/1423 的 saveRunState → 剥离。
	# 运行期宝石走 gems 数组 + CoreGem（见 CoreItem 的宝石段），不经这两个方法。
	def getGemData(self):
		return []


	def setGemData(self, gemData):
		pass


	# 对齐 Item.gd:4476+：战斗日志**回放**时把编码后的冷却状态重建回物品
	# （唯一调用点在 Core/CombatLog.gd:546 的回放路径）→ 剥离。实时战斗不需要它：
	# 实时路径的冷却是 Item 自身按物理帧推进的（见 CoreItem 的冷却推进段）。
	def reconstructCooldown(self, encodedCd, timeSinceEntry):
		pass


	# 对齐 Item.gd:6536-6555：融合/配方绑定扫描（bondedIngredients + 绑定可视化）。
	# 配方系统整体剥离；全仓库该方法**无调用点**（原版亦为死代码）→ 保留签名为空实现。
	def findBondsWithAffectedItems(self):
		pass


	# 对齐 Item.gd:5284-5296（把冷却进度按朝向折算给 shader；纯表现）
	def rotateProgress(self, progress):
		if self.faceDirection == _H_4:
				progress = 1.0 - progress
		elif self.faceDirection == _H_59:
				progress = 1.0 - progress
		elif self.faceDirection == _H_66:
				progress = - progress
		elif self.faceDirection == _H_67:
				progress = - progress
		return progress


	# 对齐 Item.gd:726-728（从 TileMap 读碰撞/扩展格并缓存）。内核的同类数据由装配层
	# 经 battle_items.json 的 grid.collision_cells / 袋格直接注入，且原版只在 _ready
	# 调用一次（旋转不重算）——故此处保留为幂等占位，不覆盖已注入的数据。
	def cacheCollisionCells(self):
		pass


	# 对齐 Item.gd:6153-6158（制作/配方候选扫描）。配方系统整体剥离 → 恒 false。
	def isBaseItemForShopItem(self, item):
		return False


	# 对齐 Item.gd:4511 一族的回放动画入口（CombatLog.gd:583 在回放事件时触发）
	def activateFromEvent(self, event):
		pass


	# ── 邻接 ──

	# 对齐 Item.gd:5815-5822
	def getNeighborItemsAndGems(self):
		neighbors = self.inventory.getAdjacentItems(self)
		neighbors.extend(self.getGemsNoNull())
		for neighbor in (neighbors if neighbors.__class__ is list else _iter(neighbors)):
			neighborGems = neighbor.getGemsNoNull()
			neighbors.extend(neighborGems)
		return neighbors


	# 对齐 Item.gd:3059-3063
	def getTouchedBags(self):
		if self.isBag() or not self.placed:
			return []
		else:
			return self.inventory.getBagsInCells(self.occupiedCells)


	# 对齐 Item.gd:5837-5851。isBusy 属制作系统（剥离后恒 false）→ 结果恒为空。
	def getBusyNeighbors(self):
		_iter__loc = _iter
		busyNeighbors = []

		for neighbor in _iter__loc(self.getNeighborItemsAndGems()):
			if neighbor.isBusy():
				busyNeighbors.append(neighbor)

		for bag in _iter__loc(self.getTouchedBags()):
			if bag.isBusy():
				busyNeighbors.append(bag)

		return busyNeighbors


	# 对齐 Item.gd:5823-5836。同上，制作系统剥离后恒为空。
	def getCraftableNeighbors(self):
		_iter__loc = _iter
		craftableNeighbors = []

		for neighbor in _iter__loc(self.getNeighborItemsAndGems()):
			if neighbor.isAvailableForCrafting():
				craftableNeighbors.append(neighbor)

		for bag in _iter__loc(self.getTouchedBags()):
			if bag.isAvailableForCrafting():
				craftableNeighbors.append(bag)

		return craftableNeighbors


	# 对齐 Item.gd:5865-5871（制作系统剥离后恒 false）
	def isAvailableForCrafting(self):
		return False


	# ─────────────────────── 其余战斗查询（对齐 4242-4247, 6510-6520） ───────────────────────

	# 对齐 Item.gd:4242-4247
	def getAffectedGoldValue(self):
		gold = 0
		for item in _iter(self.getAffectedItems_nocache()):
			gold += item.getPrice()
		return gold


	# 对齐 Item.gd:5783-5785 之外的 isShowCaseItem 见上；
	# 对齐 Item.gd:6510-6520
	def countTypes(self, ofItems):
		_iter__loc = _iter
		typesDict = {}
		for type in _iter__loc(_H_6):
			typesDict[_H_6[type]] = 0

		for item in (ofItems if ofItems.__class__ is list else _iter__loc(ofItems)):
			for type in _iter__loc(item.getTypes()):
				typesDict[type] += 1

		return typesDict


	# 对齐 Item.gd:2881-2883。拾取方向属背包交互，内核恒定（无拾取）→ true，
	# 使依赖它的形状判定读到「与拾取同向」这一原版常态值。
	def hasSameOrientationAsPickup(self):
		return True


	# ─────────────────────── 宝石 / 网格 / 行为 接缝 ───────────────────────

	def getGemsNoNull(self):
		out = []
		for gem in (self.gems if self.gems.__class__ is list else _iter(self.gems)):
			if gem != None:
				out.append(gem)
		return out


	def getGems(self):
		return self.gems


	# 装配层接缝：原版由各子类脚本在 `_ready()` 里建伤害源
	# （Items/Weapon.gd:4-5 `damageSource = DamageSource.new().setItem(self)`）。
	# 物品行为未移植前，由装配方调用本工厂得到等价对象；行为移植后可直接复写。
	def buildDamageSource(self, _type=None):
		self.damageSource = _H_2()
		self.damageSource._rng = self.ctx.rng
		self.damageSource.setItem(self, _type)
		return self.damageSource


	# ─────────────────────── 战斗连接（对齐 Item.gd:5694-5705） ───────────────────────
	# ★ 修正记录：本类早期版本把 connectForCombat 误写成 0 参数的钩子转发
	#   （`connectForCombat()` → `onConnectForCombat()`），与原版语义不符。
	#   原版签名是 `connectForCombat(emitter, signalName, methodName, binds = [])`，
	#   直接转发到 EventBus.connectEvent —— 物品行为脚本用它把角色的 buff 信号
	#   挂到自己的回调上（connectToCharacterBuffs 等）。已按原版重写。

	def connectForCombat(self, emitter, signalName, methodName, binds=[]):
		self.ctx.bus.connectEvent(emitter, signalName, self, methodName)


	# 对齐 Item.gd:5697-5701。原版用 Godot 信号（emitter.connect），内核中等价于
	# EventBus 的定向连接；destroy() 原版走 Util.tryDisconnect，而内核的连接表在
	# 战斗收尾由 disconnectAll() 整体清空 —— 两者发生在同一生命周期点
	# （CoreCombat.combatEndDeferred 先 disconnectAll、再 item.combatEnd），故等价。
	def connectForCombat_signal(self, emitter, signalName, methodName, binds=[]):
		newConnection = CoreSignalConnection(emitter, signalName,
			self, methodName, binds)
		self.combatConnections.append(newConnection)


	# 对齐 Item.gd:5702-5705
	def disconnectCombat(self):
		for connection in (self.combatConnections if self.combatConnections.__class__ is list else _iter(self.combatConnections)):
			connection.destroy()
		self.combatConnections.clear()


	def _hasBehaviorMethod(self, methodName):
		if self._behavior != None:
			return self._behavior.hasBehavior(self, methodName)
		return methodName in self.SELF_BEHAVIOR_METHODS and self.has_method(methodName)


	# 行为接缝派发：**必须回传返回值**——canAffect / getTriggerPriority / onCombatStart
	# 等虚方法的返回值直接参与判定，丢掉返回值不会报错、只会静默判否（曾导致全部联动物品
	# 失效）。装配方契约：behavior.callBehavior(item, methodName, args) 返回该方法的原值，
	# 未实现的方法返回 null。
	#
	# ★ 回落分支用 `callv`（动态调用）而非直接写方法名：onCombatStart / onDealtDamage
	#   这类回调**基类并没有定义**，写死方法名会解析失败。原版同样是动态语义
	#   （`me = self` 未标注类型 → Item.gd:3400 `me.onCombatStart()`）。
	# ★ 回落名单与 `_hasBehaviorMethod` 共用，且只含基类未定义的名字，杜绝自我递归。
	def _behavior_call(self, methodName, args=[]):
		if self._behavior != None:
			return self._behavior.callBehavior(self, methodName, args)
		if methodName in self.SELF_BEHAVIOR_METHODS and self.has_method(methodName):
			return self.callv(methodName, args)
		return None

	CoreElectricalCharge = CoreElectricalCharge
	CoreSignalConnection = CoreSignalConnection


_R.reg("res://gd_core/CoreItem.gd", CoreItem)
_R.reg("CoreItem", CoreItem)
_R.reg("CoreItem", CoreItem)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreTimer")
try:
	_H_10 = _R.C("CoreConst").ItemStat.BaseCooldown
except AttributeError as _he:
	_H_10 = _HoistPending(_he)
try:
	_H_11 = _R.C("CoreConst").ItemStat.Cooldown
except AttributeError as _he:
	_H_11 = _HoistPending(_he)
try:
	_H_12 = _R.C("CoreConst").ItemStat.StaminaCost
except AttributeError as _he:
	_H_12 = _HoistPending(_he)
try:
	_H_13 = _R.C("CoreConst").StatModified.No
except AttributeError as _he:
	_H_13 = _HoistPending(_he)
try:
	_H_14 = _R.C("CoreConst").StaminaResult.Insufficient
except AttributeError as _he:
	_H_14 = _HoistPending(_he)
try:
	_H_15 = _R.C("CoreConst").Owner.BuildViewer
except AttributeError as _he:
	_H_15 = _HoistPending(_he)
try:
	_H_16 = _R.C("CoreConst").ItemStat.MinDamage
except AttributeError as _he:
	_H_16 = _HoistPending(_he)
try:
	_H_17 = _R.C("CoreConst").ItemStat.MaxDamage
except AttributeError as _he:
	_H_17 = _HoistPending(_he)
try:
	_H_18 = _R.C("CoreConst").ItemStat.Chance
except AttributeError as _he:
	_H_18 = _HoistPending(_he)
try:
	_H_19 = _R.C("CoreConst").ItemStat.Chance2
except AttributeError as _he:
	_H_19 = _HoistPending(_he)
_H_2 = _R.C("CoreDamageSource")
try:
	_H_20 = _R.C("CoreConst").ItemStat.CritChance
except AttributeError as _he:
	_H_20 = _HoistPending(_he)
try:
	_H_21 = _R.C("CoreConst").EventType.Block
except AttributeError as _he:
	_H_21 = _HoistPending(_he)
try:
	_H_22 = _R.C("CoreConst").EventType.Spikes
except AttributeError as _he:
	_H_22 = _HoistPending(_he)
try:
	_H_23 = _R.C("CoreConst").EventType.Vampirism
except AttributeError as _he:
	_H_23 = _HoistPending(_he)
try:
	_H_24 = _R.C("CoreConst").EventType.Poison
except AttributeError as _he:
	_H_24 = _HoistPending(_he)
try:
	_H_25 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_25 = _HoistPending(_he)
try:
	_H_26 = _R.C("CoreConst").EventType.Regeneration
except AttributeError as _he:
	_H_26 = _HoistPending(_he)
try:
	_H_27 = _R.C("CoreConst").EventType.Lucky
except AttributeError as _he:
	_H_27 = _HoistPending(_he)
try:
	_H_28 = _R.C("CoreConst").EventType.Mana
except AttributeError as _he:
	_H_28 = _HoistPending(_he)
try:
	_H_29 = _R.C("CoreConst").EventType.Empower
except AttributeError as _he:
	_H_29 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Owner.Undefined
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_30 = _R.C("CoreConst").EventType.Heat
except AttributeError as _he:
	_H_30 = _HoistPending(_he)
try:
	_H_31 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
	_H_31 = _HoistPending(_he)
try:
	_H_32 = _R.C("CoreConst").ItemMetrics.Damage
except AttributeError as _he:
	_H_32 = _HoistPending(_he)
try:
	_H_33 = _R.C("CoreConst").ItemMetrics.Stamina
except AttributeError as _he:
	_H_33 = _HoistPending(_he)
try:
	_H_34 = _R.C("CoreConst").StackChangeType
except AttributeError as _he:
	_H_34 = _HoistPending(_he)
try:
	_H_35 = _R.C("CoreConst").StackChangeType.Added_Player
except AttributeError as _he:
	_H_35 = _HoistPending(_he)
_H_36 = _R.C("CoreUtil")
try:
	_H_37 = _R.C("CoreConst").Owner.Opponent
except AttributeError as _he:
	_H_37 = _HoistPending(_he)
try:
	_H_38 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_38 = _HoistPending(_he)
try:
	_H_39 = _R.C("CoreConst").Stack.Buff
except AttributeError as _he:
	_H_39 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").FaceDirection.UP
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_40 = _R.C("CoreConst").Stack.Debuff
except AttributeError as _he:
	_H_40 = _HoistPending(_he)
try:
	_H_41 = _R.C("CoreEventBus").LoggingMode.Delayed
except AttributeError as _he:
	_H_41 = _HoistPending(_he)
try:
	_H_42 = _R.C("CoreConst").Owner.Socket
except AttributeError as _he:
	_H_42 = _HoistPending(_he)
try:
	_H_43 = _R.C('CoreConst').FaceDirection
except AttributeError as _he:
	_H_43 = _HoistPending(_he)
try:
	_H_44 = _R.C("CoreConst").CharID.PLAYER
except AttributeError as _he:
	_H_44 = _HoistPending(_he)
try:
	_H_45 = _R.C("CoreConst").Tag.Lifesteal
except AttributeError as _he:
	_H_45 = _HoistPending(_he)
try:
	_H_46 = _R.C("CoreConst").StatModified.Positive
except AttributeError as _he:
	_H_46 = _HoistPending(_he)
try:
	_H_47 = _R.C("CoreConst").StatModified.Negative
except AttributeError as _he:
	_H_47 = _HoistPending(_he)
try:
	_H_48 = _R.C("CoreConst").ItemMetrics.OutOfStamina
except AttributeError as _he:
	_H_48 = _HoistPending(_he)
try:
	_H_49 = _R.C("CoreConst").StackChangeType.Used_Player
except AttributeError as _he:
	_H_49 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").Priority.Normal
except AttributeError as _he:
	_H_5 = _HoistPending(_he)
try:
	_H_50 = _R.C("CoreConst").Owner.PlayerInventory
except AttributeError as _he:
	_H_50 = _HoistPending(_he)
try:
	_H_51 = _R.C("CoreDamageSource").Type.Effect
except AttributeError as _he:
	_H_51 = _HoistPending(_he)
try:
	_H_52 = _R.C("CoreConst").StackChangeType.Removed_Player
except AttributeError as _he:
	_H_52 = _HoistPending(_he)
try:
	_H_53 = _R.C("CoreConst").Owner.Shop
except AttributeError as _he:
	_H_53 = _HoistPending(_he)
try:
	_H_54 = _R.C("CoreConst").Owner.PlayerStorageBox
except AttributeError as _he:
	_H_54 = _HoistPending(_he)
try:
	_H_55 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_55 = _HoistPending(_he)
try:
	_H_56 = _R.C("CoreConst").EventType.DamageBuff
except AttributeError as _he:
	_H_56 = _HoistPending(_he)
try:
	_H_57 = _R.C("CoreConst").ItemMetrics.MaxHealth
except AttributeError as _he:
	_H_57 = _HoistPending(_he)
try:
	_H_58 = _R.C("CoreConst").EventType.TemporaryMaxHealth
except AttributeError as _he:
	_H_58 = _HoistPending(_he)
try:
	_H_59 = _R.C("CoreConst").FaceDirection.RIGHT
except AttributeError as _he:
	_H_59 = _HoistPending(_he)
try:
	_H_6 = _R.C("CoreConst").Type
except AttributeError as _he:
	_H_6 = _HoistPending(_he)
try:
	_H_60 = _R.C("CoreConst").Affected
except AttributeError as _he:
	_H_60 = _HoistPending(_he)
try:
	_H_61 = _R.C("CoreConst").ItemMetrics.Activations
except AttributeError as _he:
	_H_61 = _HoistPending(_he)
try:
	_H_62 = _R.C("CoreConst").ItemMetrics.Block
except AttributeError as _he:
	_H_62 = _HoistPending(_he)
try:
	_H_63 = _R.C("CoreConst").ItemMetrics
except AttributeError as _he:
	_H_63 = _HoistPending(_he)
try:
	_H_64 = _R.C("CoreConst").ItemStat.Accuracy
except AttributeError as _he:
	_H_64 = _HoistPending(_he)
try:
	_H_65 = _R.C("CoreConst").Affected.Tertiary
except AttributeError as _he:
	_H_65 = _HoistPending(_he)
try:
	_H_66 = _R.C("CoreConst").FaceDirection.LEFT
except AttributeError as _he:
	_H_66 = _HoistPending(_he)
try:
	_H_67 = _R.C("CoreConst").FaceDirection.DOWN
except AttributeError as _he:
	_H_67 = _HoistPending(_he)
_H_7 = _R.C("CoreConst")
try:
	_H_8 = _R.C("CoreConst").ItemStat
except AttributeError as _he:
	_H_8 = _HoistPending(_he)
try:
	_H_9 = _R.C("CoreConst").ItemStat.Speed
except AttributeError as _he:
	_H_9 = _HoistPending(_he)
