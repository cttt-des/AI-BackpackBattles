# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




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
		self.speedScale = 0.0
		self.bonusMaxDam = 0.0
		self.bonusMinDam = 0.0
		self.removableDam = 0.0
		self.bonusDamageFactor = 1.0
		self.staminaFactor = 1.0
		self.critChancePercent = 0.0
		self.critTokens = 0
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
		self.numCharges = 0
		self.baseCooldownOverride = 0.0
		self.chanceRng = None
		self.damageRangeRng = None
		self.statDisplayOverrides = []
		self.lastActivationTime = 0.0
		self.activationsThisFrame = 0
		self.lastTriggerTime = 0.0
		self.triggersThisFrame = 0
		self.triggerTime = 0.0
		self.iterationCooldown = 0.0
		self.itemMetrics = []
		self.gems = []
		self._grid = None
		self._behavior = None
		self._cooldown_active = False
		self.dynamicTypes = {}       # 动态类型记账（addDynamicType/removeDynamicType）
		self.combatConnections = []       # connectForCombat_signal 建立的战斗连接
		self.ownerType = _R.C("CoreConst").Owner.Undefined   # 由装配层按所属角色写入
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
		self.replacementPending = False
		self.faceDirection = _R.C("CoreConst").FaceDirection.UP
		self.rotation = 0.0

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


	# 伤害与速度修正（对齐 Item.gd:474-495）


	# 对齐 Item.gd:288 —— 仅由战斗日志回放路径写入（CombatLog.gd:600/612 的 setStat），
	# 实战判定中恒为 null；保留字段与读取点以维持接口一致。

	# 冷却运行态（对齐 Item.gd:464-470）

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
		self.ctx = _ctx
		self.descriptor = _descriptor
		self.character_ = _character
		self.name = _descriptor.name
		self.chanceRng = self.ctx.rng.BalancedRng(self.ctx.rng)
		self.damageRangeRng = self.ctx.rng.BalancedRange(self.ctx.rng)
		self.baseCooldownOverride = _descriptor.cd
		for buff in _iter(_R.C("CoreConst").getStacks()):
			self.buffPowers[buff] = 1.0
			self.buffAmplificationChances[buff] = 0.0
		_resize(self.itemMetrics, self.getNumItemMetrics())
		_fill(self.itemMetrics, 0)
		_resize(self.statDisplayOverrides, len(_R.C("CoreConst").ItemStat))
		_fill(self.statDisplayOverrides, None)
		# 对齐 Item.gd:602-603（_ready 里把每个颜色档初始化为空字典）
		for color in _iter(list(_R.C("CoreConst").Affected.values())):
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
		return self.character_ != None and self.character_.playerId == _R.C("CoreConst").CharID.PLAYER


	# ─────────────────────── 类型 / 标签（对齐 3594-3601, 5370-5390） ───────────────────────

	def hasType(self, type):
		return type in self.descriptor.types


	def getTypeMultiplicity(self, type):
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
		return _R.C("CoreConst").Priority.Normal


	def canDamage(self):
		return self.getBaseMinDamage() > 0 or self.hasTag(_R.C("CoreConst").Tag.Lifesteal)


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
		override = self.statDisplayOverrides[_R.C("CoreConst").ItemStat.Speed]
		if override:
			return override

		if self.hasCharacter():
			speed_ = self.speed() + self.getStackSpeedMods()
			modifiedSpeed = None
			if speed_ >= 0:
				modifiedSpeed = 1.0 + speed_
			else:
				modifiedSpeed = _div(1.0, 1.0 - speed_)

			modifiedSpeed = clamp(modifiedSpeed, 0.1, 10.0)
			return modifiedSpeed
		else:
			return 1.0


	def speed(self):
		return self.speedScale


	def getStackSpeedMods(self):
		return (self.character().getHeat() - self.character().getCold()) * 0.02


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
		if index == 0:
			return self.descriptor.cd
		else:
			return self.descriptor.extraCds[index - 1]


	# 对齐 Items/Item.gd:3782-3786（含 statDisplayOverrides[CoreConst.ItemStat.BaseCooldown] 覆盖分支）
	def getCooldown(self):
		override = self.statDisplayOverrides[_R.C("CoreConst").ItemStat.BaseCooldown]
		if override:
			return override

		return self.baseCooldownOverride


	def getCooldownIndex(self, index):
		return self.getBaseCooldownIndex(index)


	def getModifiedCooldown(self):
		return _div(self.getCooldown(), self.getSpeed())


	def getModifiedCooldownIndex(self, index):
		return _div(self.getCooldownIndex(index), self.getSpeed())


	def getCooldownEncoded(self):
		if self.iterationCooldown == 0:
			return - 1
		relProgress = 1.0 - _div(self.triggerTime, self.iterationCooldown)
		progressPerSecond = None
		if self.isCooldownActive():
			progressPerSecond = _div(self.getSpeed(), self.iterationCooldown)
		else:
			progressPerSecond = 0
		value = int(relProgress * self.cdEncodingFactor) << 32
		value += int(progressPerSecond * self.cdEncodingFactor)
		return value


	def adjustCooldown(self):
		adjustedCooldown = self.getCooldown()
		if self.character_ != None and self.character_.playerId == _R.C("CoreConst").CharID.OPPONENT and \
			(self.ctx.below_master or self.ctx.lobbies_mode):
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
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.BaseCooldown)


	# ─────────────────────── 战斗生命周期（对齐 3356-3440） ───────────────────────

	# ─────────────────────── 体力消耗（对齐 Item.gd:3972-3980, 4213-4227） ───────────────────────

	def getBaseStaminaCost(self):
		return self.descriptor.staminaCost


	def getStaminaCost(self):
		# 对齐 Item.gd:3975-3979 —— 原版先查 statDisplayOverrides[CoreConst.ItemStat.StaminaCost]，
		# 该数组仅由战斗日志回放路径写入（CombatLog.gd:600/612），实战恒为 null，
		# 故此处保留读取点但不改变判定（Greatsword.gd:15 覆写本函数时同样读取该数组）。
		override = self.statDisplayOverrides[_R.C("CoreConst").ItemStat.StaminaCost]
		if override:
			return override
		return self.getBaseStaminaCost() * self.staminaFactor


	def isStaminaModified(self):
		return self.isStatModified(self.getBaseStaminaCost() - self.getStaminaCost())


	def isStatModified(self, statVal):
		if statVal == 0:
			return _R.C("CoreConst").StatModified.No
		elif statVal > 0:
			return _R.C("CoreConst").StatModified.Positive
		else:
			return _R.C("CoreConst").StatModified.Negative


	def setStat(self, stat, value):
		self.statDisplayOverrides[stat] = value
		self.ctx.hooks.queueTooltipUpdate(self)


	# 对齐 Item.gd:4213-4224
	def useStamina(self, amount=None):
		if amount == None:
			amount = self.getStaminaCost()
		res = self.character().useStamina(amount)
		if res == _R.C("CoreConst").StaminaResult.Insufficient:
			self.addMetric(_R.C("CoreConst").ItemMetrics.OutOfStamina, 1, None, True)
			event = self.ctx.combat_log.createEvent_OutOfStamina(self, self.character().playerId)
			self.ctx.bus.logEvent(event)
			self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)
			self.playOutOfStaminaAnimation()
		else:
			self.ctx.bus.emitSignal(self, "used_stamina", [amount])
			self.staminaChanged(amount, _R.C("CoreConst").StackChangeType.Used_Player, True)
		return res


	# 对齐 Item.gd:4226-4227
	def drainStamina(self, amount, triggerEvent=None):
		return self.opponent().drainStamina(amount, self, triggerEvent)


	# 对齐 Item.gd:4202-4211：动画/音效/飘字全部走钩子；
	# `Game.numTimesOutOfStamina += 1` 仅在玩家侧物品触发时计数（ownerType == PlayerInventory）。
	def playOutOfStaminaAnimation(self):
		if self.isPlayer():
			self.ctx.out_of_stamina_count += 1
		self.ctx.hooks.playOutOfStaminaAnimation(self)


	def cacheAffectedItemsForCombat(self):
		# 对齐 Item.gd:3356-3358 —— 开战前把「受影响物品集」定版。
		# 战斗期间物品不移动，故 getAffectedItems 之后恒读这份快照。
		for color in _iter(list(_R.C("CoreConst").Affected.values())):
			self.cachedAffectedItems[color] = list(self.currentAffectedItems[color].keys())


	# 对齐 Item.gd:1319-1352（addToInventory）。剥离项：
	#   · inventory.connect(...) —— 内核里由 CoreGrid.addItem 直接遍历 items 回调，等价于信号广播
	#   · CraftingManager.itemAdded / makeGrabbable / 各类 Util.connectIfExists（制作与商店）
	#   · emit_signal("added_to_inventory")（表现层）
	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		self.placedByPlayer = _placedByPlayer
		self.placed = True
		self.inventory = _inventory
		self.occupiedCells = _occupiedCells
		if self.ownerType != _R.C("CoreConst").Owner.BuildViewer:
			# 原版对比 Game.PLAYER.INVENTORY / Game.OPPONENT.INVENTORY（两个 autoload 全局恒非空）。
			# 内核里双方由装配层 setup() 注入，未注入时保持原 ownerType（装配早期的正常情形）。
			if self.ctx.player != None and self.inventory == self.ctx.player.inventory:
				self.ownerType = _R.C("CoreConst").Owner.PlayerInventory
			elif self.ctx.opponent != None and self.inventory == self.ctx.opponent.inventory:
				self.ownerType = _R.C("CoreConst").Owner.Opponent

		self.cacheAffectedCells()

		for color in _iter(list(_R.C("CoreConst").Affected.values())):
			for item in _iter(self.getAffectedItems(color)):
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
			self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)

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
		self.baseCooldownOverride = self.descriptor.cd
		self.speedScale = 0.0
		self.bonusMinDam = 0
		self.bonusMaxDam = 0
		self.removableDam = 0
		self.bonusDamageFactor = 1.0
		self.staminaFactor = 1.0
		for buff in _iter(self.buffPowers):
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
		_fill(self.statDisplayOverrides, None)
		_fill(self.itemMetrics, 0)
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
		# 计时器推进（对齐物品 tscn 里 XxxTimer 的 TIMER_PROCESS_PHYSICS）。
		# ★ 必须放在冷却门之前：计时器承载 buff 时长（buffEnded 会撤掉 buff 效果），
		#   冷却未激活不代表计时器停摆。
		self._tickTimers(delta)
		# ★ 镶嵌宝石的计时器由宿主代为推进：原版宝石是 socket→item 的场景树子节点，
		#   其 XxxTimer 由引擎物理帧推进（如 ElephantRune 的 DebuffResistTimer 承载
		#   dur_resist 后移除全减伤抗性）；内核里宝石不在 combat.ordered_items
		#   （那里只有摆上格子的物品），若不在此推进，宝石计时器永不触发。
		for gem in _iter(self.gems):
			if gem != None:
				gem._tickTimers(delta)
		if not self._cooldown_active:
			return
		if not self.character().isStunned():
			self.triggerTime -= delta * self.getSpeed()
			self.ctx.hooks.showCooldown(self, 1.0 - _div(self.triggerTime, self.iterationCooldown))
			if self.triggerTime <= 0:
				self.trigger()


	# ─────────────────── 物品计时器（对齐 tscn 的 XxxTimer 子节点） ───────────────────
	# 原版物品用场景树里的 Timer 子节点承载 buff 时长，由 tscn 的 [connection] 把
	# `timeout` / `multi_timeout` 接到物品方法。内核无场景树，改为显式虚拟计时器：
	# 物品脚本的 `_readyInit()` 里 `xxx = newItemTimer("XxxTimer", "方法名", 是否叠加)`。
	# 同名重复调用会替换旧实例，使「同一批物品重入装配」不会累积计时器。


	def newItemTimer(self, timerName, method, isMulti=False):
		for existing in _iter(self.timers):
			if existing.name == timerName:
				existing.stop()
				_erase(self.timers, existing)
				break
		t = _R.C("CoreTimer")(self.ctx, self, timerName)
		t.multi = isMulti
		t.one_shot = True
		t.callback_method = method
		self.timers.append(t)
		return t


	def getTimer(self, timerName):
		for t in _iter(self.timers):
			if t.name == timerName:
				return t
		return None


	def _tickTimers(self, delta):
		for t in _iter(self.timers):
			t.tick(delta)


	# 装配期一次性初始化（对齐 Node 的 `_ready` + `onready var` 求值时机）。
	# 原版时机：物品入树后，onready 变量先赋值、随后调用 _ready()。
	# 内核时机：装配层在「ctx / descriptor / inventory 都就位」之后调用一次。
	# 子类覆写时开头写 `.()` 先跑父类（等价于原版 _ready 的隐式父类优先）。
	def _readyInit(self):
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


	# ─────────────────────── 触发（对齐 4416-4451） ───────────────────────

	def checkTriggerCount(self, limit):
		if self.ctx.time > self.triggersThisFrame:
			self.triggersThisFrame = 1
			self.lastTriggerTime = self.ctx.time
		else:
			self.triggersThisFrame += 1
			if self.triggersThisFrame > limit:
				return False
		return True


	def trigger(self):
		self.iterationCooldown = self.adjustCooldown()
		self.triggerTime += self.iterationCooldown

		self.doCooldownEffect()

		if self.doubleActivationChance > 0 and self.ctx.rng.flip(self.doubleActivationChance):
			self.doCooldownEffect()


	# 物品行为覆写点（Items/*.gd 里绝大多数 doCooldownEffect 来自子类脚本）
	def doCooldownEffect(self):
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
		self.ctx.hooks.showCooldownSmooth(self, 0, True)
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

		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)


	def advanceCooldownSeconds(self, amount):
		if not self.isCooldownActive():
			return

		self.triggerTime -= amount * self.getSpeed()

		while self.triggerTime <= 0:
			self.trigger()
			if not self.isCooldownActive():
				return

		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)


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
				self.addMetric(_R.C("CoreConst").ItemMetrics.Activations)
			if self.hasCooldown():
				self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown, None, 
					False, event)

		if animationOverride != None:
			self.ctx.hooks.playActivationAnimation(self, animationOverride, consume)
		self.ctx.hooks.playActivationSound(self)

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
		for type in _iter(damSource.types):
			typedDmgFactor += self.character().typedDamageFactors[type]

		return typedDmgFactor


	# 对齐 Items/Item.gd:3676-3690（含 statDisplayOverrides[CoreConst.ItemStat.MinDamage] 覆盖分支）
	def getMinDamage(self, damSource=GD_DEFAULT):
		if damSource is GD_DEFAULT:
			damSource = self.damageSource
		override = self.statDisplayOverrides[_R.C("CoreConst").ItemStat.MinDamage]
		if override:
			return override

		minDam = ceil(self.descriptor.minDam + self.bonusMinDam)
		if self.hasCharacter():
			if self.canBeEmpowered():
				minDam = minDam + self.character().getBuffDamageMod()

			minDam *= self.getTypedDamageFactor(damSource)

		minDam = round(minDam * self.bonusDamageFactor)
		minDam = max(minDam, 0)

		return minDam


	# 对齐 Items/Item.gd:3693-3707（含 statDisplayOverrides[CoreConst.ItemStat.MaxDamage] 覆盖分支）
	def getMaxDamage(self, damSource=GD_DEFAULT):
		if damSource is GD_DEFAULT:
			damSource = self.damageSource
		override = self.statDisplayOverrides[_R.C("CoreConst").ItemStat.MaxDamage]
		if override:
			return override

		maxDam = ceil(self.descriptor.maxDam + self.bonusMaxDam)
		if self.hasCharacter():
			if self.canBeEmpowered():
				maxDam = maxDam + self.character().getBuffDamageMod()

			maxDam *= self.getTypedDamageFactor(damSource)

		maxDam = round(maxDam * self.bonusDamageFactor)
		maxDam = max(maxDam, 0)

		return maxDam


	def getAverageDamage(self):
		return _div(self.getMinDamage() + self.getMaxDamage(), 2.0)


	def randDamage(self):
		return self.ctx.rng.randi_range(self.getMinDamage(), self.getMaxDamage())


	# 对齐 Items/Item.gd:5130-5134（原版无返回类型标注：float 原样透传）
	def getModifiedEffectDamage(self, baseDamage):
		modifiedDamage = baseDamage
		modifiedDamage *= (1.0 + self.character().typedDamageFactors[_R.C("CoreDamageSource").Type.Effect])
		modifiedDamage *= self.bonusDamageFactor
		return modifiedDamage


	def addBonusDamage(self, damage, removable=True):
		if removable:
			self.removableDam += damage
		self.bonusMinDam += damage
		self.bonusMaxDam += damage


	def changeVaryingDamage(self, damage):
		self.removableDam += damage


	def addMinDamage(self, damage):
		self.bonusMinDam += damage


	def addMaxDamage(self, damage):
		self.bonusMaxDam += damage


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
		if index == 1:
			return (toChance + self.bonusChancePercent_additive1) * _div(100 + self.bonusChancePercent_mult, 100.0)
		else:
			return (toChance + self.bonusChancePercent_additive2) * _div(100 + self.bonusChancePercent_mult, 100.0)


	# 对齐 Items/Item.gd:3867-3870
	def getChance(self):
		override = self.statDisplayOverrides[_R.C("CoreConst").ItemStat.Chance]
		if override:
			return override

		return clamp(self.applyBonusChance(self.getBaseChance(), 1), 0, 100)


	# 对齐 Items/Item.gd:3873-3876
	def getChance2(self):
		override = self.statDisplayOverrides[_R.C("CoreConst").ItemStat.Chance2]
		if override:
			return override

		return clamp(self.applyBonusChance(self.getBaseChance2(), 2), 0, 100)


	def rollChance(self, chance=None):
		if chance == None:
			chance = self.getBaseChance()
		return self.chanceRng.rollPercent(self.applyBonusChance(chance, 1))


	def rollChance2(self):
		return self.chanceRng.rollPercent(self.applyBonusChance(self.descriptor.chance2, 2))


	def addBonusChance(self, amount):
		self.bonusChancePercent_mult += amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Chance)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Chance2)


	def addBonusChance_additive(self, amount1, amount2=None):
		self.bonusChancePercent_additive1 += amount1

		if amount2 == None:
			self.bonusChancePercent_additive2 += amount1
		else:
			self.bonusChancePercent_additive2 += amount2

		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Chance)

		if amount2 != 0:
			self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Chance2)


	def addAccuracy(self, amount):
		self.bonusAccuracy += amount


	# ─────────────────────── 暴击（对齐 3995-4027, 4128-4129） ───────────────────────

	def getCritChancePercent(self):
		return clamp(self.critChancePercent, 0, 100)


	def addCritChancePercent(self, amount):
		self.critChancePercent += amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.CritChance)


	def reduceCritChancePercent(self, amount):
		self.critChancePercent -= amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.CritChance)


	def changeCritChancePercent(self, amount):
		self.critChancePercent += amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.CritChance)


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
		if self.hasCharacter():
			acc += self.character().getBuffAccuracyMod()
		return acc


	# ─────────────────────── 栈操作（对齐 4889-5035） ───────────────────────

	def getAmplificationChancePercent(self, buffType):
		return self.buffAmplificationChances[buffType]


	def changeAmplificiationChancePercent(self, buffType, chance):
		self.buffAmplificationChances[buffType] += chance


	def changeAmplificiationChancePercent_allBuffs(self, chance):
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.changeAmplificiationChancePercent(buff, chance)


	def changeAmplificiationChancePercent_allDebuffs(self, chance):
		for buff in _iter(_R.C("CoreConst").getDebuffs()):
			self.changeAmplificiationChancePercent(buff, chance)


	def changeNullifyChancePercent(self, buffType, chance):
		self.buffAmplificationChances[buffType] -= chance


	def giveReflectStacks(self, amount):
		self.character().changeDebuffReflectStacks(amount)


	def giveStacks(self, target, type, amount, triggerEvent=None):
		if amount > 0:
			return target.gainStacks(type, round(amount * self.buffPowers[type]), self, triggerEvent)
		return None


	def giveStacksTemporary(self, target, type, amount, duration, triggerEvent=None):
		if amount > 0:
			return target.gainStacksTemporary(type, round(amount * self.buffPowers[type]), duration, self, triggerEvent)
		return None


	def giveBlock(self, amount=None, canTriggerEffects=True, triggerEvent=None):
		if amount == None:
			amount = self.getBlock()
		if amount > 0:
			event = self.giveStacks(self.character(), _R.C("CoreConst").EventType.Block, amount, triggerEvent)
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
		return self.character().useStacks(_R.C("CoreConst").EventType.Block, amount, self, triggerEvent)


	def stealStack(self, type, amount, triggerEvent=None):
		removeEvent = self.opponent().loseStacks(type, amount, self, triggerEvent)
		giveEvent = self.giveStacks(self.character(), type, amount, removeEvent)
		return giveEvent


	def giveSpikes(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Spikes, amount, triggerEvent)


	def giveVampirism(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Vampirism, amount, triggerEvent)


	def inflictPoison(self, amount, triggerEvent=None):
		return self.giveStacks(self.opponent(), _R.C("CoreConst").EventType.Poison, amount, triggerEvent)


	def selfInflictPoison(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Poison, amount, triggerEvent)


	def inflictBlind(self, amount, triggerEvent=None):
		return self.giveStacks(self.opponent(), _R.C("CoreConst").EventType.Blind, amount, triggerEvent)


	def giveRegeneration(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Regeneration, amount, triggerEvent)


	def giveLucky(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Lucky, amount, triggerEvent)


	def giveMana(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Mana, amount, triggerEvent)


	def giveEmpower(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Empower, amount, triggerEvent)


	def giveHeat(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Heat, amount, triggerEvent)


	def giveCold(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Cold, amount, triggerEvent)


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
		self.addMetric(_R.C("CoreConst").ItemMetrics.Damage, amount)


	# ─────────────────────── 统计（对齐 715-724, 4909-4934） ───────────────────────

	@staticmethod
	def getNumNonStackItemMetrics():
		return (_R.C("CoreConst").ItemMetrics.Stamina + 
				(_R.C("CoreConst").ItemMetrics.Block - _R.C("CoreConst").ItemMetrics.Stamina) * len(_R.C("CoreConst").StackChangeType))


	@staticmethod
	def getNumItemMetrics():
		return (_R.C("CoreConst").ItemMetrics.Stamina + 
				(len(_R.C("CoreConst").ItemMetrics) - _R.C("CoreConst").ItemMetrics.Stamina) * len(_R.C("CoreConst").StackChangeType))


	@staticmethod
	def getStackMetricIndex(stackChangeType, stackType):
		offsetStackType = stackType - _R.C("CoreConst").EventType.Block
		changeTypeOffset = stackChangeType * _R.C("CoreConst").numStackTypes()
		return CoreItem.getNumNonStackItemMetrics() + changeTypeOffset + offsetStackType


	@staticmethod
	def getMultiMetricIndex(stackChangeType, metric):
		offsetMetric = metric - _R.C("CoreConst").ItemMetrics.Stamina
		numMultiMetrics = offsetMetric * len(_R.C("CoreConst").StackChangeType)
		return _R.C("CoreConst").ItemMetrics.Stamina + numMultiMetrics + stackChangeType


	# 对齐 Item.gd:4186-4188（amount 默认 1；并把指标快照交给钩子）
	def addMetric(self, metricsIndex, amount=1, playerId=None, withNextEvent=False):
		self.itemMetrics[metricsIndex] += amount
		self.ctx.hooks.snapshotItemMetric(self, metricsIndex, playerId, withNextEvent)


	def getMetric(self, metric):
		return self.itemMetrics[metric]


	def stackChanged(self, stackType, amount, onPlayer, used=False):
		changeType = None
		if amount > 0:
			changeType = _R.C("CoreConst").StackChangeType.Added_Player
		else:
			if used:
				changeType = _R.C("CoreConst").StackChangeType.Used_Player
			else:
				changeType = _R.C("CoreConst").StackChangeType.Removed_Player

		if not onPlayer:
			changeType += 1

		index = self.getStackMetricIndex(changeType, stackType)
		playerId = 0 if onPlayer else 1
		self.addMetric(index, abs(amount), playerId, True)


	def staminaChanged(self, amount, changeType, withNextEvent=False):
		index = self.getMultiMetricIndex(changeType, _R.C("CoreConst").ItemMetrics.Stamina)
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
		if type in self.dynamicTypes:
			if fromItem.get_instance_id() in self.dynamicTypes[type]:
				return True

		return False


	# 对齐 Item.gd:3603-3613。原版 tail 的 inventory.onItemTypeChanged(self) 属背包刷新，
	# ObjectPool.particleOneShot 属粒子表现 —— 两者均走钩子。
	def addDynamicType(self, type, byItem):
		if not type in self.descriptor.types:
			_R.C("CoreUtil").dictAppend(self.dynamicTypes, type, byItem.get_instance_id())

			if len(self.dynamicTypes[type]) == 1:
				if self.placed:
					self.ctx.hooks.onItemTypeChanged(self)


	# 对齐 Item.gd:3614-3621
	def removeDynamicType(self, type, byItem):
		if self.hasDynamicType(type, byItem):
			_R.C("CoreUtil").dictErase(self.dynamicTypes, type, byItem.get_instance_id())

			if not type in self.dynamicTypes:
				if self.placed:
					self.ctx.hooks.onItemTypeChanged(self)


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
		return (self.ownerType == _R.C("CoreConst").Owner.Shop or 
			self.ownerType == _R.C("CoreConst").Owner.PlayerInventory or 
			self.ownerType == _R.C("CoreConst").Owner.PlayerStorageBox)


	# 对齐 Item.gd:969-972
	def isOwnedByOpponent(self):
		return self.ownerType == _R.C("CoreConst").Owner.Opponent


	# 对齐 Item.gd:984-986（原版 has_method 探测 → 内核的 behavior 探测）
	def isGateItem(self):
		return self._hasBehaviorMethod("getGatedDescriptor") or self._hasBehaviorMethod("getReplaceDescriptor")


	# 对齐 Item.gd:5783-5785
	def isShowCaseItem(self):
		return self.character() == None


	# 对齐 Item.gd:3566-3580（基类恒 false，由物品行为覆写）
	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		if self._hasBehaviorMethod("isAffectingDistinct"):
			return _R.C("CoreUtil").truth(self._behavior_call("isAffectingDistinct", [color]))
		return False


	# 对齐 Item.gd:3540-3543（基类恒 false，由物品行为覆写）
	def affectsEmpty(self, color):
		if self._hasBehaviorMethod("affectsEmpty"):
			return _R.C("CoreUtil").truth(self._behavior_call("affectsEmpty", [color]))
		return False


	# 对齐 Item.gd:3951-3953
	def hasOpponent(self):
		return self.hasCharacter() and self.opponent() != None


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
		if stat == _R.C("CoreConst").ItemStat.MaxDamage:
				if self.getBaseMaxDamage() > 0:
					return self.getMaxDamage()
				else:
					return 0
		elif stat == _R.C("CoreConst").ItemStat.MinDamage:
				if self.getBaseMinDamage() > 0:
					return self.getMinDamage()
				else:
					return 0
		elif stat == _R.C("CoreConst").ItemStat.Accuracy:
				return self.getAccuracy()
		elif stat == _R.C("CoreConst").ItemStat.CritChance:
				return self.getCritChancePercent()
		elif stat == _R.C("CoreConst").ItemStat.Speed:
				return self.getSpeed()
		elif stat == _R.C("CoreConst").ItemStat.Cooldown:
				return self.getCooldownEncoded()
		elif stat == _R.C("CoreConst").ItemStat.StaminaCost:
				return self.getStaminaCost()
		elif stat == _R.C("CoreConst").ItemStat.Chance:
				return self.getChance()
		elif stat == _R.C("CoreConst").ItemStat.Chance2:
				return self.getChance2()
		elif stat == _R.C("CoreConst").ItemStat.BaseCooldown:
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
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Speed)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)


	# 对齐 Item.gd:4877-4881
	def reduceSpeed(self, amount):
		self.speedScale -= amount
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Speed)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.Cooldown)


	# 对齐 Item.gd:3733-3735
	def getDPS(self):
		return _div((self.getMinDamage() + self.getMaxDamage()) * 0.5, self.getModifiedCooldown())


	# 对齐 Item.gd:3736-3741
	def isDPSModified(self):
		baseDPS = _div(self.getBaseAverageDamage(), self.getCooldown())
		modifiedDPS = _div(self.getAverageDamage(), self.getModifiedCooldown())
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
			return _R.C("CoreUtil").truth(self._behavior_call("canAffect", [item]))
		return False


	# 对齐 Item.gd:3547-3549
	def canAffect_secondary(self, item):
		if self._hasBehaviorMethod("canAffect_secondary"):
			return _R.C("CoreUtil").truth(self._behavior_call("canAffect_secondary", [item]))
		return False


	# 对齐 Item.gd:3550-3552
	def canAffect_tertiary(self, item):
		if self._hasBehaviorMethod("canAffect_tertiary"):
			return _R.C("CoreUtil").truth(self._behavior_call("canAffect_tertiary", [item]))
		return False


	# 对齐 Item.gd:3553-3555
	def canAffect_lightning(self, item):
		if self._hasBehaviorMethod("canAffect_lightning"):
			return _R.C("CoreUtil").truth(self._behavior_call("canAffect_lightning", [item]))
		return False


	# 对齐 Item.gd:3556-3565
	def canAffect_color(self, item, color):
		if color == _R.C("CoreConst").Affected.Primary:
			return self.canAffect(item)
		elif color == _R.C("CoreConst").Affected.Secondary:
			return self.canAffect_secondary(item)
		elif color == _R.C("CoreConst").Affected.Tertiary:
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
		return self.descriptor.gainedStacks & _R.C("CoreConst").Stack.Buff


	# 对齐 Item.gd:5395-5397
	def usesBuffs(self):
		return self.descriptor.usedStacks & _R.C("CoreConst").Stack.Buff


	# 对齐 Item.gd:5398-5400
	def inflictsDebuffs(self):
		return self.descriptor.gainedStacks & _R.C("CoreConst").Stack.Debuff


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
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.StaminaCost)


	# 对齐 Item.gd:4106-4110
	def addBonusDamageFactor(self, factor):
		self.bonusDamageFactor += factor
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MinDamage)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MaxDamage)


	# 对齐 Item.gd:4111-4116
	def reduceBonusDamageFactor(self, factor):
		self.bonusDamageFactor -= factor
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MinDamage)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MaxDamage)


	# 对齐 Item.gd:4098-4101
	def reduceMinDamage(self, damage):
		self.bonusMinDam -= damage
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MinDamage)


	# 对齐 Item.gd:4102-4105
	def reduceMaxDamage(self, damage):
		self.bonusMaxDam -= damage
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MaxDamage)


	# 对齐 Item.gd:4076-4086（尾行 spawnLabel 走钩子）
	def reduceBonusDamage(self, damage, showLabel=True, removable=True):
		self.bonusMinDam -= damage
		self.bonusMaxDam -= damage
		if removable:
			self.removableDam -= damage
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MinDamage)
		self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MaxDamage)

		if showLabel:
			self.spawnLabel(_R.C("CoreConst").EventType.DamageBuff, - damage)


	# 对齐 Item.gd:4087-4097（尾行 spawnLabel 走钩子）
	def purgeDamage(self, damage):
		purgable = min(damage, self.removableDam)
		if purgable > 0:
			self.removableDam -= purgable
			self.bonusMinDam -= purgable
			self.bonusMaxDam -= purgable
			self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MinDamage)
			self.ctx.combat_log.snapshotItemTooltipStat(self, _R.C("CoreConst").ItemStat.MaxDamage)

			self.spawnLabel(_R.C("CoreConst").EventType.DamageBuff, - purgable)


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
			self.addMetric(_R.C("CoreConst").ItemMetrics.MaxHealth, amount, None, True)
			self.character().changeMaxHealthTemporary(amount, self, triggerEvent)
			self.spawnLabel(_R.C("CoreConst").EventType.TemporaryMaxHealth, amount)


	# 对齐 Item.gd:4193-4195
	def giveStamina(self, amount=1, triggerEvent=None):
		self.character().gainStamina(amount, self, triggerEvent)


	# 对齐 Item.gd:4182-4185
	def inflictFatigueDamage(self, fatigueIncrease=1):
		self.opponent().addFatigueDamage(fatigueIncrease)
		self.opponent().takeFatigueDamage(self)


	# 对齐 Item.gd:5147-5154（电荷传播的视觉与音效走钩子；numCharges 记账保留）
	def sendCharge(self, durPerTile, cells, speedFactor, event):
		chargeDuration = durPerTile * (len(cells) - 1)
		self.ctx.hooks.sendCharge(self, cells, _div(chargeDuration, speedFactor), event)


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

	# 对齐 Item.gd:4826-4828
	def heal(self, amount=None, triggerEvent=None):
		if amount == None:
			amount = self.getP_m("heal")
		healed = self.character().heal(amount, self, triggerEvent)


	# 对齐 Item.gd:5122-5129
	def healthToBlock(self, health, block, triggerEvent=None):
		clampedHealth = min(health, self.character().getCurrentHealth() - 1)
		if clampedHealth > 0:
			self.character().loseHealth(clampedHealth, self, triggerEvent)

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
		amount = round(amount * self.buffPowers[_R.C("CoreConst").EventType.Mana])
		curMana = self.character().getMana()
		if maximum > curMana:
			missingMana = maximum - curMana
			manaGiven = min(amount, missingMana)
			self.character().gainMana(manaGiven, self, triggerEvent)
			return amount - manaGiven
		else:
			return amount


	# ── 减益 / buff 的「自身使用 / 转给对手」成对包装（对齐 4983-5115, 5494-5529） ──

	# 对齐 Item.gd:4983-4985
	def removeSpikes(self, amount, triggerEvent=None):
		self.opponent().loseSpikes(amount, self, triggerEvent)


	# 对齐 Item.gd:4989-4991
	def useSpikes(self, amount, triggerEvent=None):
		return self.character().useStacks(_R.C("CoreConst").EventType.Spikes, amount, self, triggerEvent)


	# 对齐 Item.gd:4986-4988
	def loseSpikes(self, amount, triggerEvent=None):
		self.character().loseSpikes(amount, self, triggerEvent)


	# 对齐 Item.gd:4995-4997
	def removeVampirism(self, amount, triggerEvent=None):
		self.opponent().loseVampirism(amount, self, triggerEvent)


	# 对齐 Item.gd:4998-5000
	def useVampirism(self, amount, triggerEvent=None):
		return self.character().useStacks(_R.C("CoreConst").EventType.Vampirism, amount, self, triggerEvent)


	# 对齐 Item.gd:5001-5003
	def loseVampirism(self, amount, triggerEvent=None):
		self.character().loseVampirism(amount, self, triggerEvent)


	# 对齐 Item.gd:5010-5018
	def cleansePoison(self, amount, triggerEvent=None):
		curPoison = self.character().getPoison()
		if curPoison == 0:
			return 0

		amount = min(curPoison, amount)
		self.character().losePoison(amount, self, triggerEvent)
		return amount


	# 对齐 Item.gd:5022-5024
	def selfInflictBlind(self, amount, triggerEvent=None):
		return self.giveStacks(self.character(), _R.C("CoreConst").EventType.Blind, amount, triggerEvent)


	# 对齐 Item.gd:5025-5033
	def cleanseBlind(self, amount, triggerEvent=None):
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
		return self.character().useStacks(_R.C("CoreConst").EventType.Regeneration, amount, self, triggerEvent)


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
		return self.character().useStacks(_R.C("CoreConst").EventType.Lucky, amount, self, triggerEvent)


	# 对齐 Item.gd:5094-5096
	def inflictCold(self, amount, triggerEvent=None):
		self.giveStacks(self.opponent(), _R.C("CoreConst").EventType.Cold, amount, triggerEvent)


	# 对齐 Item.gd:5097-5106
	def cleanseCold(self, amount, triggerEvent=None):
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
		return self.character().useStacks(_R.C("CoreConst").EventType.Heat, amount, self, triggerEvent)


	# 对齐 Item.gd:5119-5121
	def loseEmpower(self, amount, triggerEvent=None):
		self.character().loseEmpower(amount, self, triggerEvent)


	# 对齐 Item.gd:5516-5529
	def cleanseRandomDebuffs(self, numDebuffs, triggerEvent=None):
		cleansedDebuffs = self.pickRandomStacks(_R.C("CoreConst").getDebuffs(), numDebuffs, self.character())

		self.ctx.bus.setLoggingMode(_R.C("CoreEventBus").LoggingMode.Delayed)
		for debuff in _iter(cleansedDebuffs):
			self.character().loseStacks(debuff, cleansedDebuffs[debuff], self, triggerEvent)

		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5482-5493
	def inflictRandomDebuffs(self, numDebuffs, triggerEvent=None, availableDebuffs=None):
		if availableDebuffs == None:
			availableDebuffs = _R.C("CoreConst").getDebuffs()
		pickedDebuffs = self.pickRandomStacksToGive(availableDebuffs, numDebuffs)

		self.ctx.bus.setLoggingMode(_R.C("CoreEventBus").LoggingMode.Delayed)
		for debuff in _iter(pickedDebuffs):
			self.giveStacks(self.opponent(), debuff, pickedDebuffs[debuff], triggerEvent)

		self.ctx.bus.flushLoggingQueue()


	# ─────────────────────── 随机 buff 取用（对齐 5422-5685） ───────────────────────
	# 取随机一律走 ctx.rng（原版 Util.rng，Util.gd:6），保证同种子可复现。

	# 对齐 Item.gd:5422-5446
	def pickRandomStacks(self, stackTypes, numStacks, target, priorityStack=None):
		stacks = Dictionary()
		for stackType in _iter(stackTypes):
			numTargetStacks = target.getStacks(stackType)
			if numTargetStacks > 0:
				stacks[stackType] = numTargetStacks

		pickedStacks = Dictionary()

		if priorityStack != None:
			pickedPriorityStacks = min(numStacks, stacks.get(priorityStack, 0))
			if pickedPriorityStacks > 0:
				pickedStacks[priorityStack] = pickedPriorityStacks
				numStacks -= pickedPriorityStacks
				_R.C("CoreUtil").dictSub(stacks, priorityStack, pickedPriorityStacks)

		for i in _iter(_gd_range(numStacks)):
			if not (not stacks):
				stackType = self.ctx.rng.pickRandomElement(list(stacks.keys()))
				_R.C("CoreUtil").dictAdd(pickedStacks, stackType, 1)
				_R.C("CoreUtil").dictSub(stacks, stackType, 1)

		return pickedStacks


	# 对齐 Item.gd:5447-5454
	def pickRandomStacksToGive(self, stackTypes, numStacks):
		pickedStacks = Dictionary()
		for i in _iter(_gd_range(numStacks)):
			stackType = self.ctx.rng.pickRandomElement(stackTypes)
			_R.C("CoreUtil").dictAdd(pickedStacks, stackType, 1)

		return pickedStacks


	# 对齐 Item.gd:5530-5554
	def getLeastStacks(self, numStacks, target, availableStacks):
		priorStacks = {}
		for stackType in _iter(availableStacks):
			priorStacks[stackType] = target.getStacks(stackType)

		pickedStacks = {}

		while numStacks > 0:
			leastStacksCount = 10000
			leastStacks = []
			for stackType in _iter(priorStacks):
				if priorStacks[stackType] < leastStacksCount:
					leastStacksCount = priorStacks[stackType]
					leastStacks.clear()
					leastStacks.append(stackType)
				elif priorStacks[stackType] == leastStacksCount:
					leastStacks.append(stackType)
			stackToGive = self.ctx.rng.pickRandomElement(leastStacks)
			_R.C("CoreUtil").dictAdd(pickedStacks, stackToGive, 1)
			_R.C("CoreUtil").dictAdd(priorStacks, stackToGive, 1)
			numStacks -= 1

		return pickedStacks


	# 对齐 Item.gd:5563-5579
	def getMostStacks(self, target, availableStacks):
		buffs = Dictionary()
		for buff in _iter(availableStacks):
			buffs[buff] = target.getStacks(buff)

		maxBuffs = []
		maxStacks = 0
		for buff in _iter(buffs):
			if buffs[buff] == maxStacks:
				maxBuffs.append(buff)
			elif buffs[buff] > maxStacks:
				maxBuffs.clear()
				maxBuffs.append(buff)
				maxStacks = buffs[buff]

		return maxBuffs


	# 对齐 Item.gd:5610-5652（原版 Util.sortDict(overflow, true) → CoreUtil.sortDict(.., ctx.rng, true)）
	def getStackFraction(self, target, fraction, limit, availableStacks):

		sum = 0.0
		stacksUnlimited = {}

		for buff in _iter(availableStacks):
			prior = target.getStacks(buff)

			withBonus = prior * fraction
			stacksUnlimited[buff] = withBonus
			sum += withBonus

		sumRounded = round(sum)
		if sumRounded == 0:
			return None

		totalToGive = min(limit, sumRounded)
		limitFactor = _div(totalToGive, sumRounded)

		buffsToGive = {}
		overflow = {}
		totalGiven = 0

		for buff in _iter(stacksUnlimited):
			limited = stacksUnlimited[buff] * limitFactor
			guaranteed = int(limited)
			buffsToGive[buff] = guaranteed
			overflow[buff] = limited - guaranteed
			totalGiven += guaranteed

		overflowBuffs = totalToGive - totalGiven
		sortedOverflow = _R.C("CoreUtil").sortDict(overflow, self.ctx.rng, True)

		for buff in _iter(sortedOverflow):
			if overflowBuffs == 0:
				break

			buffsToGive[buff] += 1
			overflowBuffs -= 1

		return buffsToGive


	# 对齐 Item.gd:5653-5663
	def multiplyBuffsLimit(self, bonus, limit, availableBuffs=None):
		if availableBuffs == None:
			availableBuffs = _R.C("CoreConst").getBuffs()
		buffsToGive = self.getStackFraction(self.character(), bonus, limit, availableBuffs)
		if buffsToGive == None:
			return

		self.ctx.bus.setLoggingMode(_R.C("CoreEventBus").LoggingMode.Delayed)
		for buff in _iter(buffsToGive):
			self.giveStacks(self.character(), buff, buffsToGive[buff])
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5664-5674
	def removeBuffsFraction(self, fraction, limit, triggerEvent=None, availableBuffs=None):
		if availableBuffs == None:
			availableBuffs = _R.C("CoreConst").getBuffs()
		buffsToRemove = self.getStackFraction(self.opponent(), fraction, limit, availableBuffs)
		if buffsToRemove == None:
			return

		self.ctx.bus.setLoggingMode(_R.C("CoreEventBus").LoggingMode.Delayed)
		for buff in _iter(buffsToRemove):
			self.opponent().loseStacks(buff, buffsToRemove[buff], self, triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5675-5685
	def stealBuffsFraction(self, fraction, limit, triggerEvent=None, availableBuffs=None):
		if availableBuffs == None:
			availableBuffs = _R.C("CoreConst").getBuffs()
		buffsToSteal = self.getStackFraction(self.opponent(), fraction, limit, availableBuffs)
		if buffsToSteal == None:
			return

		self.ctx.bus.setLoggingMode(_R.C("CoreEventBus").LoggingMode.Delayed)
		for buff in _iter(buffsToSteal):
			self.stealStack(buff, buffsToSteal[buff], triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5555-5562
	def giveLeastBuffs(self, numBuffs, target=None, triggerEvent=None, availableBuffs=None):

		if target == None:
			target = self.character()
		if availableBuffs == None:
			availableBuffs = _R.C("CoreConst").getBuffs()

		pickedStacks = self.getLeastStacks(numBuffs, target, availableBuffs)

		for buffType in _iter(pickedStacks):
			self.giveStacks(target, buffType, pickedStacks[buffType], triggerEvent)


	# 对齐 Item.gd:5580-5585
	def giveMostBuffs(self, numBuffs, triggerEvent=None, availableBuffs=None):
		if availableBuffs == None:
			availableBuffs = _R.C("CoreConst").getBuffs()
		maxBuffs = self.getMostStacks(self.character(), availableBuffs)
		buffToGive = self.ctx.rng.pickRandomElement(maxBuffs)
		self.giveStacks(self.character(), buffToGive, numBuffs, triggerEvent)


	# 对齐 Item.gd:5586-5609
	def removeMostBuffs(self, numBuffs, triggerEvent=None, use=False, availableBuffs=None):
		if availableBuffs == None:
			availableBuffs = _R.C("CoreConst").getBuffs()
		target = None

		buffs = Dictionary()
		if use:
			target = self.character()
		else:
			target = self.opponent()

		maxBuffs = self.getMostStacks(target, availableBuffs)
		buffToRemove = self.ctx.rng.pickRandomElement(maxBuffs)

		toRemove = min(numBuffs, target.getStacks(buffToRemove))
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

		if availableBuffs == None:
			availableBuffs = _R.C("CoreConst").getBuffs()
		if target == None:
			target = self.character()

		pickedBuffs = self.pickRandomStacksToGive(availableBuffs, numBuffs)
		self.ctx.bus.setLoggingMode(_R.C("CoreEventBus").LoggingMode.Delayed)
		for buff in _iter(pickedBuffs):
			self.giveStacks(target, buff, pickedBuffs[buff], triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5464-5468
	def giveAllBuffs(self, numBuffs=1, triggerEvent=None):
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.giveStacks(self.character(), buff, numBuffs)


	# 对齐 Item.gd:5469-5481
	def useRandomBuffs(self, numBuffs, triggerEvent=None, availableBuffs=None):
		if availableBuffs == None:
			availableBuffs = _R.C("CoreConst").getBuffs()
		pickedBuffs = self.pickRandomStacks(availableBuffs, numBuffs, self.character())
		if (not pickedBuffs):
			return None

		events = []
		self.ctx.bus.setLoggingMode(_R.C("CoreEventBus").LoggingMode.Delayed)
		for buff in _iter(pickedBuffs):
			event = self.character().useStacks(buff, pickedBuffs[buff], self, triggerEvent)
			events.append(event)
		self.ctx.bus.flushLoggingQueue()
		return events


	# 对齐 Item.gd:5494-5500
	def removeRandomBuffs(self, numBuffs, triggerEvent=None):
		removedStacks = self.pickRandomStacks(_R.C("CoreConst").getBuffs(), numBuffs, self.opponent())
		self.ctx.bus.setLoggingMode(_R.C("CoreEventBus").LoggingMode.Delayed)
		for buff in _iter(removedStacks):
			self.opponent().loseStacks(buff, removedStacks[buff], self, triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5501-5515
	def stealRandomBuff(self, numBuffs, triggerEvent=None, possibleBuffs=None, priorityBuff=None):

		if possibleBuffs == None:
			possibleBuffs = _R.C("CoreConst").getBuffs()

		removedStacks = self.pickRandomStacks(possibleBuffs, numBuffs, self.opponent(), priorityBuff)
		self.ctx.bus.setLoggingMode(_R.C("CoreEventBus").LoggingMode.Delayed)
		for buff in _iter(removedStacks):
			self.opponent().loseStacks(buff, removedStacks[buff], self, triggerEvent)

			self.giveStacks(self.character(), buff, removedStacks[buff], triggerEvent)
		self.ctx.bus.flushLoggingQueue()


	# 对齐 Item.gd:5405-5421（把角色 buff 信号接到物品回调）
	def connectToCharacterBuffs(self, methodName):
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.connectForCombat(self.character(), self.character().buffs[buff].signalName, methodName)


	def connectToCharacterDebuffs(self, methodName):
		for debuff in _iter(_R.C("CoreConst").getDebuffs()):
			self.connectForCombat(self.character(), self.character().buffs[debuff].signalName, methodName)


	def connectToOpponentDebuffs(self, methodName):
		for debuff in _iter(_R.C("CoreConst").getDebuffs()):
			self.connectForCombat(self.opponent(), self.opponent().buffs[debuff].signalName, methodName)


	def connectToOpponentBuffs(self, methodName):
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.connectForCombat(self.opponent(), self.opponent().buffs[buff].signalName, methodName)


	# ─────────────────────── 状态 / 视觉枢纽（对齐 4804-4831, 4968-4970, 3535-3539） ───────────────────────
	# 这些方法在原版里是「物品自身」的视觉出口，物品行为脚本会调用它们；
	# 内核把实现整体转给 ctx.hooks（原版对应 Util.spawnLabelOnItem / Settings 开关）。

	# 对齐 Item.gd:4804-4809（Settings 的 damage_numbers 开关一并剥离）
	def spawnLabel(self, type, amount):
		self.ctx.hooks.spawnLabelOnItem(type, self, amount)


	# 对齐 Item.gd:4810-4814（Settings 的 buff_labels 开关一并剥离）
	def spawnLabel_other(self, type, amount):
		self.ctx.hooks.spawnLabelOnItem(type, self, amount)


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
		for gem in _iter(self.gems):
			if gem != None:
				return True
		return False


	def getGemsOfItems(self, items):
		out = []
		for item in _iter(items):
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
		if socketId >= len(self.gems):
			print("ohnonononononno")
		else:
			gem.ownerType = _R.C("CoreConst").Owner.Socket
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

	# 对齐 Item.gd:1112-1116
	def getAffectedCells_tilemap(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return self.affectedTileCells.get(color, [])


	# 对齐 Item.gd:1117-1124
	def getAffectedCellsAfterRotate(self, rotatedCells, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		if color == _R.C("CoreConst").Affected.Primary:
			return self.getAffectedCellsAfterRotate_primary(rotatedCells)
		elif color == _R.C("CoreConst").Affected.Secondary:
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
			color = _R.C("CoreConst").Affected.Primary
		return self.getAffectedCellsAfterRotate(self.collisionCells, color)


	# 对齐 Item.gd:1145-1147
	def getAffectedPoints(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return self.getAffectedCells_tilemap(color) + self.getAffectedCells_noRotate(color)


	# 对齐 Item.gd:1148-1151
	def getAffectedCellsInInventory(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return self.getOwnOrPlayerInventory().getCellsForGlobalPositions(self.getAffectedPoints(color))


	# 对齐 Item.gd:1483-1485
	def getAffectedCellsInInventory_cached(self, color):
		return self.affectedCellsCache.get(color, [])


	# 对齐 Item.gd:1367-1370
	def cacheAffectedCells(self):
		for color in _iter(list(_R.C("CoreConst").Affected.values())):
			self.affectedCellsCache[color] = self.getAffectedCellsInInventory(color)


	# 对齐 Item.gd:1400-1408。原版尾行 `Util.eassert(cachedAffectedItems.empty())` 是
	# 编辑器专用断言（Util.gd:207-209 只在 editor feature 下 assert）→ 内核不保留。
	def cleanCachedAffectedItems(self):
		self.affectedCellsCache.clear()

		for color in _iter(list(_R.C("CoreConst").Affected.values())):
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
			color = _R.C("CoreConst").Affected.Primary
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
			color = _R.C("CoreConst").Affected.Primary
		items = []
		for item in _iter(self.getItemsInAffectedCells(color)):
			if self.canAffect_color(item, color):
				items.append(item)
		return items


	# 对齐 Item.gd:1155-1157
	def getItemsInAffectedCells(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return self.getOwnOrPlayerInventory().getItemsInCells(self.getAffectedCellsInInventory(color))


	# 对齐 Item.gd:1152-1154
	def getItemsInAffectedCells_cached(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return self.getOwnOrPlayerInventory().getItemsInCells(self.getAffectedCellsInInventory_cached(color))


	# 对齐 Item.gd:1158-1160
	def countItemsInAffectedCells_cached(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return self.getOwnOrPlayerInventory().countItemsInCells(self.getAffectedCellsInInventory_cached(color))


	# 对齐 Item.gd:1182-1192
	def isItemAffected(self, item, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		if item.isBag() or not self.canAffect_color(item, color):
			return False

		affectedTiles = self.getAffectedCellsInInventory_cached(color)

		for cell in _iter(item.occupiedCells):
			if cell in affectedTiles:
				return True
		return False


	# 对齐 Item.gd:1193-1195
	def getNumEmptyAffectedCells(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return self.inventory.getEmptyCellsInCells(self.getAffectedCellsInInventory(color))


	# 对齐 Item.gd:1196-1198
	def getNumAffectedItems(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return len(self.getAffectedItems(color))


	# 对齐 Item.gd:1199-1204
	def getFirstAffectedItem(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		_affectedItems = self.getAffectedItems(color)
		if not (not _affectedItems):
			return _affectedItems[0]
		return None


	# 对齐 Item.gd:1205-1210
	def getNumAffected_type(self, type, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		num = 0
		for item in _iter(self.getAffectedItems(color)):
			num += item.getTypeMultiplicity(type)
		return num


	# 对齐 Item.gd:3581-3586
	def getNumDistinctAffectedItems(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		distinctAffectedDescriptors = {}
		for item in _iter(self.getAffectedItems(color)):
			distinctAffectedDescriptors[item.descriptor] = True
		return len(distinctAffectedDescriptors)


	# 对齐 Item.gd:1139-1144
	def getNumAffectedCells(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		if color in self.affectedCellsCache:
			return len(self.affectedCellsCache[color])
		else:
			return len(self.getAffectedCells_tilemap(color)) + len(self.getAffectedCells_noRotate(color))


	# 对齐 Item.gd:1285-1294（扩展格是 TileMap 上的临时涂色，内核里改 affectedTileCells）
	def activateExtendedAffectedCells(self):
		for cell in _iter(self.affectedExtensionCells):
			_R.C("CoreUtil").dictAppend(self.affectedTileCells, _R.C("CoreConst").Affected.Primary, cell)
		self.cacheAffectedCells()


	def deactivateExtendedAffectedCells(self):
		for cell in _iter(self.affectedExtensionCells):
			arr = self.affectedTileCells.get(_R.C("CoreConst").Affected.Primary, [])
			if cell in arr:
				_erase(arr, cell)
		self.cacheAffectedCells()


	# 对齐 Item.gd:1486-1513（拖拽预览；战斗路径不调用，isHovered 无缓存时恒 false）
	def canAffectDraggedItem(self, item, color):
		if self.canAffect_color(item, color):

			affectedCells = self.getAffectedCellsInInventory_cached(color)

			for cell in _iter(affectedCells):
				if item.dragged:
					if self.inventory.isHovered(cell):
						return True
				else:
					if cell in item.occupiedCells:
						return True
		return False


	# 对齐 Item.gd:1517-1525（基类空，由物品行为覆写）
	def onAffectedItemAdded(self, item, color):
		pass


	def onAffectedItemRemoved(self, item, color):
		pass


	# 对齐 Item.gd:1425-1443（背包内新物品加入时刷新受影响集）
	def onItemAdded(self, item):
		newItemIsAffected = {}
		for color in _iter(list(_R.C("CoreConst").Affected.values())):
			newItemIsAffected[color] = (not item in self.currentAffectedItems[color] and 
										self.isItemAffected(item, color))

		for color in _iter(list(_R.C("CoreConst").Affected.values())):
			if newItemIsAffected[color]:
				self.currentAffectedItems[color][item] = True
				self.onAffectedItemAdded(item, color)


	# 对齐 Item.gd:1446-1452
	def onItemRemoved(self, item):
		for color in _iter(list(_R.C("CoreConst").Affected.values())):
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

		for cell in _iter(cells):
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
		for cell in _iter(self.occupiedCells):
			topLeft.x = min(cell.x, topLeft.x)
			topLeft.y = min(cell.y, topLeft.y)
		return topLeft


	# 对齐 Item.gd:1071-1100。返回值 [归一化后的占格, 格偏移]。原版的格偏移是
	# 全局坐标（collisionMap.map_to_world(minimum) + position + (40,40)），只用消费方是
	# ItemLibrary 的展示摆放（Interface/ItemLibrary/ItemLibrary.gd:209/409）——不在战斗
	# 判定路径上，内核返回 Vector2.ZERO 占位。
	def getNormalizedCollisionCells(self):
		cells = None
		if self.isBag():
			cells = _dup(self.getExtensionCells())
		else:
			cells = _dup(self.getCollisionCells())

		minimum = Vector2(100, 100)
		for cell in _iter(cells):
			if cell.y <= minimum.y:
				if cell.y < minimum.y:
					minimum.x = cell.x
				else:
					minimum.x = min(cell.x, minimum.x)
				minimum.y = cell.y

		for i in _iter(_gd_range(len(cells))):
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
		self.ctx.hooks.resetZ(self)


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
			return _R.C("CoreUtil").truth(self._behavior_call("reactToItemTypeChange", [item]))
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
		for color in _iter(list(_R.C("CoreConst").Affected.values())):
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
			self.ctx.hooks.playAffectedPlacedAnimation(self, addedToAffected)


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
		count = 0
		if self.isOwnedByOpponent():
			if self.ctx.opponent == None:
				return 0
			for item in _iter(self.ctx.opponent.inventory.getItemsAndGems()):
				if item != None and item.descriptor == descr:
					count += 1
			return count

		if self.ctx.player != None:
			for item in _iter(self.ctx.player.inventory.getItemsAndGems()):
				if item == None or item.descriptor != descr:
					continue
				if item.ownerType == _R.C("CoreConst").Owner.Socket:
					count += 1
				elif (item.placed
						and item.ownerType == _R.C("CoreConst").Owner.PlayerInventory):
					count += 1
		return count


	# 对齐 Item.gd:3066-3085：被自身占格压住的袋子按「描述符」归并计数
	def getTouchedBagsCounted(self):
		if self.isBag() or not self.placed:
			return None
		touchedBags = self.inventory.getBagsInCells(self.occupiedCells)
		bagCounter = {}
		for bag in _iter(touchedBags):
			found = False
			for countedBag in _iter(bagCounter):
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
		self.ctx.hooks.playActivationAnimation(
			self, "MiniActivate_consumed" if self.consumed else "MiniActivate", False)


	# 对齐 Item.gd:1857-1875 区间的预览重绘调用点
	def previewCellCollision(self):
		self.ctx.hooks.previewCellCollision(self)


	# 对齐 Item.gd:2124-2131（预览格着色）
	def previewCells(self):
		self.ctx.hooks.previewCells(self)


	# 对齐 Item.gd:2211（预览是否能影响）
	def previewCanAffect(self):
		self.ctx.hooks.previewCanAffect(self)


	# 对齐 Item.gd:1963-1996。rotateRight/Left 的入口是玩家按键（Item.gd:1843-1856 的
	# _input），rotateTo 只是 tween 旋转 + 重算 faceDirection。内核把它们做成
	# 「更新 faceDirection + 通知表现层」：不接按键、不做插值，但字段语义与原版一致，
	# 以便行为脚本（Scale/SpintoWin 覆写 rotateTo 更新计数器/配色）能正常调用。
	def rotateRight(self):
		self.faceDirection = _mod(self.faceDirection + 1, len(_R.C('CoreConst').FaceDirection))
		self.setFaceDirectionInstant(self.faceDirection)
		self.ctx.hooks.onItemRotated(self)


	def rotateLeft(self):
		self.faceDirection = _mod(self.faceDirection - 1 + len(_R.C('CoreConst').FaceDirection), len(_R.C('CoreConst').FaceDirection))
		self.setFaceDirectionInstant(self.faceDirection)
		self.ctx.hooks.onItemRotated(self)


	def rotateTo(self, targetRotation, duration=0.15):
		# 原版：先取当前 sprite 朝向存 faceDirection，再把节点旋转到 target，
		# 最后 tween 把 sprite 从旧角度插值回来（视觉回弹）。内核保留「朝向 = 节点旋转的
		# 量化值」这一结果，丢掉的只有插值过程。
		self.faceDirection = self.getGlobalFaceDirection()
		self.rotation = targetRotation
		self.faceDirection = self.getGlobalFaceDirection()
		self.ctx.hooks.onItemRotated(self)


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
		if self.faceDirection == _R.C("CoreConst").FaceDirection.UP:
				progress = 1.0 - progress
		elif self.faceDirection == _R.C("CoreConst").FaceDirection.RIGHT:
				progress = 1.0 - progress
		elif self.faceDirection == _R.C("CoreConst").FaceDirection.LEFT:
				progress = - progress
		elif self.faceDirection == _R.C("CoreConst").FaceDirection.DOWN:
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
		self.ctx.hooks.playActivationAnimation(self, "Activate", False)


	# ── 邻接 ──

	# 对齐 Item.gd:5815-5822
	def getNeighborItemsAndGems(self):
		neighbors = self.inventory.getAdjacentItems(self)
		neighbors.extend(self.getGemsNoNull())
		for neighbor in _iter(neighbors):
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
		busyNeighbors = []

		for neighbor in _iter(self.getNeighborItemsAndGems()):
			if neighbor.isBusy():
				busyNeighbors.append(neighbor)

		for bag in _iter(self.getTouchedBags()):
			if bag.isBusy():
				busyNeighbors.append(bag)

		return busyNeighbors


	# 对齐 Item.gd:5823-5836。同上，制作系统剥离后恒为空。
	def getCraftableNeighbors(self):
		craftableNeighbors = []

		for neighbor in _iter(self.getNeighborItemsAndGems()):
			if neighbor.isAvailableForCrafting():
				craftableNeighbors.append(neighbor)

		for bag in _iter(self.getTouchedBags()):
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
		typesDict = {}
		for type in _iter(_R.C("CoreConst").Type):
			typesDict[_R.C("CoreConst").Type[type]] = 0

		for item in _iter(ofItems):
			for type in _iter(item.getTypes()):
				typesDict[type] += 1

		return typesDict


	# 对齐 Item.gd:2881-2883。拾取方向属背包交互，内核恒定（无拾取）→ true，
	# 使依赖它的形状判定读到「与拾取同向」这一原版常态值。
	def hasSameOrientationAsPickup(self):
		return True


	# ─────────────────────── 宝石 / 网格 / 行为 接缝 ───────────────────────

	def getGemsNoNull(self):
		out = []
		for gem in _iter(self.gems):
			if gem != None:
				out.append(gem)
		return out


	def getGems(self):
		return self.gems


	# 装配层接缝：原版由各子类脚本在 `_ready()` 里建伤害源
	# （Items/Weapon.gd:4-5 `damageSource = DamageSource.new().setItem(self)`）。
	# 物品行为未移植前，由装配方调用本工厂得到等价对象；行为移植后可直接复写。
	def buildDamageSource(self, _type=None):
		self.damageSource = _R.C("CoreDamageSource")()
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
		for connection in _iter(self.combatConnections):
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

CoreItem.CoreSignalConnection = CoreSignalConnection


_R.reg("res://gd_core/CoreItem.gd", CoreItem)
_R.reg("CoreItem", CoreItem)
_R.reg("CoreItem", CoreItem)
