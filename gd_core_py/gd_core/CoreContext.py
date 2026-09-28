# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreContext(GodotObject):

	resource_path = "res://gd_core/CoreContext.gd"

	def _init_fields(self):
		super()._init_fields()
		self.rng = None
		self.util = None
		self.bus = None
		self.hooks = None
		self.combat_log = None
		self.player = None
		self.opponent = None
		self.fight_ended = False
		self.time = 0.0                # 对齐 Util.time（物理帧累加）
		self.frame_counter = 0         # 对齐 Util.frameCounter
		self.combat_time = 0.0         # 对齐 CombatTimer.combatTime（供事件时间戳）
		self.below_master = False      # 对齐 Game.isBelowLeague(Game.Leagues.Master)
		self.lobbies_mode = False      # 对齐 Game.curMode == Game.Mode.Lobbies
		self.combat = None
		self.item_book = None
		self.sandbag_active = False
		self.cur_mode = 0
		self.cur_round = 0
		self.rope_speedups = {}
		self.cube_advanced = {}
		self.event_type_keys = {}
		self.class_resources = None
		self.unhealingDamageSource = None
		self.fatigueDamageSource = None
		self.stealLifeDamageSource = None
		self.out_of_stamina_count = 0  # 对齐 Game.numTimesOutOfStamina
		self.warn_unknown_api = True
		self._deferred = []
		self._timed = []
		self._emptyGrid = None

	# =============================================================================
	# CoreContext.gd — 无头战斗内核：战斗上下文（替代全局单例）
	# =============================================================================
	# 原版中战斗逻辑横向依赖 6 个全局单例：Game / Util / Sound / ItemBook / EventBus / Settings。
	# 这些单例把「战斗状态」与「渲染、场景、存档、UI」绑在一起，是耦合的主要来源。
	# gd_core 用一个显式对象 CoreContext 承载战斗所需的全部状态，由外部注入到
	# CoreItem / CoreCharacter / CoreBuff 中（各对象持 `ctx` 引用），
	# 从而做到：
	#   · 同一进程内可并行跑多场战斗（无单例）
	#   · 可固定种子复现（rng 可注入）
	#   · 可 deepcopy / 序列化（为后续 RL 批量推演铺路）
	#
	# 语义对齐表（原 → 新）：
	#   Util.rng                     → ctx.rng            (Util.gd:6)
	#   Util.time                    → ctx.time           (Util.gd:148-152，物理帧累加)
	#   Util.frameCounter            → ctx.frame_counter  (Util.gd:151)
	#   Game.fightEnded              → ctx.fight_ended    (Game.gd:3002 起)
	#   Game.PLAYER / Game.OPPONENT  → ctx.player / ctx.opponent
	#   Game.isBelowLeague(Master)   → ctx.below_master   (Character.gd:304, Item.gd:3807)
	#   Game.curMode == Mode.Lobbies → ctx.lobbies_mode   (同上)
	#   Game.combatLog               → ctx.combat_log     (CoreCombatLog：仅事件工厂 + 钩子)
	#   EventBus                     → ctx.bus
	#   Util.tra / Sound / 各类视觉   → ctx.hooks
	# =============================================================================


	# 帧率与固定步长（对齐 Godot 默认物理帧率 60Hz；原版 Item._physics_process 即此步长）
	PHYSICS_FPS = 60.0
	PHYSICS_DELTA = _div(1.0, 60.0)

	# 对齐 Game.gd:201 `const COMBAT_DELAY = 2.5`
	COMBAT_DELAY = 2.5

	# 对齐 CombatTimer.gd:5 `const FATIGUE_TIME = 17`
	FATIGUE_TIME = 17




	# ── 单例门面（原版 autoload → 显式对象，随 ctx 走） ──
	#   Game.combatTimer     → ctx.combat      （ItemBook 之外的**信号发射者身份**：
	#                                            CoreCombat 用 self 发 fatigue_start /
	#                                            fatigue_damage_changed，与 CombatTimer.gd
	#                                            同为「疲劳计时器」这一实体）
	#   Game.sandbagActive   → ctx.sandbag_active
	#   Game.curMode         → ctx.cur_mode
	#   Game.curRound        → ctx.cur_round
	#   ItemBook             → ctx.item_book   （描述符注册表 + 库存类型查询）
	# 对齐 Game.gd:390 `var sandbagActive := false` + :3332 在**战斗收尾**置回 false。
	# 一个 ctx 即一场战斗，故这里就是「本场是否已有沙袋生效」。
	# 对齐 Game.gd:148-154 `enum Mode{Ranked=0, Unranked, Lobbies, Unselected, History}`。
	# 无头内核不模拟局外流程，默认 Ranked（≠ History）。消费方：ChessBoard.onPrepare
	# 只用它决定「要不要接商店信号」，而该信号连接本身属表现层（已被剥离）。
	# 对齐 Game.curRound（局外回合数）。消费方：LevelUp.onPrepare 的
	# `addSpeed((curRound - buyRound) * speedPerRound)` —— 装配层可按需写入。

	# ── 跨回合的**战斗内运行期字典**（对齐 Game.gd:388-389） ──
	#   Game.ropeSpeedups    → ctx.rope_speedups
	#   Game.cubeAdvanced    → ctx.cube_advanced
	# 二者都是「一场战斗内累积、战斗收尾清空」的状态（清空点 Game.gd:3330-3331，
	# 由 CoreCombat.combatEndDeferred 对齐）。它们的语义各自是：
	#   · ropeSpeedups[item] = 该物品已从绳索获得的速度总量 → Rope 用它夹住 maxSpeed
	#     上限，并在自己的计时器到期时**按同量回收**（Util.dictSub）。
	#   · cubeAdvanced[item] = 最后一个对该物品推进冷却的方块 → 原版据此判定
	#     「同一物品被第二个方块推进时要乘 penaltyFactor」，即同名减益。
	# 键是物品实例（Object），故用 Dictionary 的引用相等语义，与原版一致。

	# 对齐 Game.gd:512 —— EventType 的**反查表**（枚举值 → 名字字符串），在 _init 派生。
	# ★ 曾把 eventTypeKeys 当「纯文本渲染」剔除，那是误判：MagicRing.giveStacksFromEffect
	#   用它把 `effect.stackType`（int）转成**参数名**（"poison"/"cold"/…），紧接着
	#   `getP(stackName)` 取的就是战斗数值（MagicRing.gd:107-109）。它是判定链的一环。

	# 对齐 Game.classResources（Game.gd:131 的职业 → 职业资源表）。
	# 消费方：CoreCharacter.setClass / setClassResource —— 职业资源提供 health / stamina，
	# 直接决定角色 maxHealth 与 baseMaxStamina。形如 {Classes.Ranger: {...}} 或
	# {Classes.Ranger: Resource}，取字段统一用 .get(key)（Object.get 与 Dictionary.get 都通），
	# 故宿主既能塞 Dictionary（纯数据/测试）也能塞真 Resource。

	# ── 全局伤害源（对齐 Game.gd:2426-2433 的 _ready 构造） ──
	#   unhealingDamageSource  origin=null  flags=unhealingFlags  (Character.gd:771)
	#   fatigueDamageSource    origin=self  flags=CanBeBlocked    (Character.gd:1600)
	#   stealLifeDamageSource  origin=null  flags=effectFlags

	# 一次战斗的统计出口（供外部读取；不参与判定）

	# ── 延迟调用队列（替代原版的 call_deferred） ──
	# 原版散落 6 处 call_deferred（Character.gd:968 重算体力上限、Item.gd:2035 旋转落位、
	# Item.gd:1544 等）。语义都是「当前帧末执行」。内核不依赖场景树，故用一个显式队列
	# 在帧末 flush（CoreCombat.physicsTick 的最后一步），次序与原版 SceneTree 的
	# call_deferred 一致（同一帧内按入队顺序执行）。


	def _init(self, _seed=0, _hooks=None):
		self.rng = _R.C("CoreRng")(_seed)
		self.util = _R.C("CoreUtil")(self.rng)
		self.util._ctx = self
		self.hooks = _hooks if _hooks != None else _R.C("CoreHooks")()
		self.bus = _R.C("CoreEventBus")()
		self.bus._ctx = self
		self.combat_log = _R.C("CoreCombatLog")()
		self.combat_log._ctx = self
		self.item_book = _R.C("CoreItemBook")()
		self.item_book._ctx = self

		# 对齐 Game.gd:2426-2433
		self.stealLifeDamageSource = self._newDamageSource(None, _R.C("CoreDamageSource").Type.Effect, 
			_R.C("CoreDamageSource").effectFlags)
		self.unhealingDamageSource = self._newDamageSource(None, _R.C("CoreDamageSource").Type.Unhealing, 
			_R.C("CoreDamageSource").unhealingFlags)
		self.fatigueDamageSource = self._newDamageSource(self, _R.C("CoreDamageSource").Type.Fatigue, 
			_R.C("CoreDamageSource").Flags.CanBeBlocked)

		# 对齐 Game.gd:512 `onready var eventTypeKeys = Util.invertDictionary(EventType)`
		self.event_type_keys = _R.C("CoreUtil").invertDictionary(_R.C("CoreConst").EventType)


	def _newDamageSource(self, origin, type, flags):
		src = _R.C("CoreDamageSource")()
		src._rng = self.rng
		src.init(origin, type)
		src.flags = flags
		return src


	def getCharacterFromId(self, playerId):
		return self.player if playerId == _R.C("CoreCharacter").ID.PLAYER else self.opponent


	def otherCharacter(self, character):
		return self.opponent if character == self.player else self.player


	# ── 物理帧推进（对齐 Util.gd:148-152） ──
	def advancePhysicsFrame(self, delta=GD_DEFAULT):
		if delta is GD_DEFAULT:
			delta = self.PHYSICS_DELTA
		self.frame_counter += 1
		self.time += delta
		self.combat_time += delta
		self._flushTimed()


	# ── 按时延迟调用（对齐 Util.callDelayed 的 `get_tree().create_timer(delay)`） ──
	# 与下面的 _deferred（帧末）区分：这是**按时长**触发的一次性回调。
	# 原版走 SceneTreeTimer，粒度也是帧；此处按 ctx.time（同一物理帧累加量）判到期，
	# 故触发时刻与原版落在同一帧。到期检查放在时间推进之后、帧末队列之前 ——
	# 原版 SceneTreeTimer 与 call_deferred 都在帧末处理，两者之间的先后不影响判定
	# （已核：物品侧不存在同时依赖二者的同一帧路径）。


	def callDelayed(self, obj, methodName, delay, binds=[]):
		if obj == None:
			return
		self._timed.append([obj, methodName, self.time + delay, binds])


	def _flushTimed(self):
		if (not self._timed):
			return
		due = []
		keep = []
		for call in _iter(self._timed):
			if call[2] <= self.time:
				due.append(call)
			else:
				keep.append(call)
		if (not due):
			return
		self._timed = keep
		for call in _iter(due):
			call[0].callv(call[1], call[3])


	# ── 延迟调用（对齐 Node.call_deferred） ──
	def defer(self, obj, methodName, args=[]):
		self._deferred.append([obj, methodName, args])


	def hasDeferred(self):
		return not (not self._deferred)


	# 帧末 flush。执行期间新入队的调用留到下一帧（与 SceneTree 语义一致）。
	def flushDeferred(self):
		if (not self._deferred):
			return
		batch = self._deferred
		self._deferred = []
		for call in _iter(batch):
			obj = call[0]
			if obj == None:
				continue
			obj.callv(call[1], call[2])


	# ── 空背包回落（对齐「Game.PLAYER.INVENTORY 恒非空」） ──
	# 原版 Item.getOwnOrPlayerInventory() 未放置时回落到 Game.PLAYER.INVENTORY，那是个
	# autoload 上的真实节点，**永不为 null**。内核里 player 由装配层注入，在装配早期
	# （物品尚未挂到任何角色、或纯几何查询）可能还没有 player，此时若返回 null，
	# 调用方 .getItemsInCells(...) 会直接崩。此处提供一个共享空网格，使「查询得到空集」
	# 这一语义与原版一致，而不是崩。


	def emptyGrid(self):
		if self._emptyGrid == None:
			self._emptyGrid = _R.C("CoreGrid")(None)
		return self._emptyGrid


_R.reg("res://gd_core/CoreContext.gd", CoreContext)
_R.reg("CoreContext", CoreContext)
_R.reg("CoreContext", CoreContext)
