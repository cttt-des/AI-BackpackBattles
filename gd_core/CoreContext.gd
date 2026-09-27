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
extends Reference
class_name CoreContext


# 帧率与固定步长（对齐 Godot 默认物理帧率 60Hz；原版 Item._physics_process 即此步长）
const PHYSICS_FPS := 60.0
const PHYSICS_DELTA := 1.0 / 60.0

# 对齐 Game.gd:201 `const COMBAT_DELAY = 2.5`
const COMBAT_DELAY := 2.5

# 对齐 CombatTimer.gd:5 `const FATIGUE_TIME = 17`
const FATIGUE_TIME := 17

var rng                        # CoreRng
var util                       # CoreUtil（对齐原版 Util autoload；物品行为脚本调 ctx.util.*）
var bus                        # CoreEventBus
var hooks                      # CoreHooks
var combat_log                 # CoreCombatLog（原版 Game.combatLog）
var player                     # CoreCharacter
var opponent                   # CoreCharacter

var fight_ended := false
var time := 0.0                # 对齐 Util.time（物理帧累加）
var frame_counter := 0         # 对齐 Util.frameCounter
var combat_time := 0.0         # 对齐 CombatTimer.combatTime（供事件时间戳）

var below_master := false      # 对齐 Game.isBelowLeague(Game.Leagues.Master)
var lobbies_mode := false      # 对齐 Game.curMode == Game.Mode.Lobbies

# ── 单例门面（原版 autoload → 显式对象，随 ctx 走） ──
#   Game.combatTimer     → ctx.combat      （ItemBook 之外的**信号发射者身份**：
#                                            CoreCombat 用 self 发 fatigue_start /
#                                            fatigue_damage_changed，与 CombatTimer.gd
#                                            同为「疲劳计时器」这一实体）
#   Game.sandbagActive   → ctx.sandbag_active
#   Game.curMode         → ctx.cur_mode
#   Game.curRound        → ctx.cur_round
#   ItemBook             → ctx.item_book   （描述符注册表 + 库存类型查询）
var combat                     # CoreCombat（由 CoreCombat._init 回填 self）
var item_book                  # CoreItemBook（描述符注册表）
# 对齐 Game.gd:390 `var sandbagActive := false` + :3332 在**战斗收尾**置回 false。
# 一个 ctx 即一场战斗，故这里就是「本场是否已有沙袋生效」。
var sandbag_active := false
# 对齐 Game.gd:148-154 `enum Mode{Ranked=0, Unranked, Lobbies, Unselected, History}`。
# 无头内核不模拟局外流程，默认 Ranked（≠ History）。消费方：ChessBoard.onPrepare
# 只用它决定「要不要接商店信号」，而该信号连接本身属表现层（已被剥离）。
var cur_mode := 0
# 对齐 Game.curRound（局外回合数）。消费方：LevelUp.onPrepare 的
# `addSpeed((curRound - buyRound) * speedPerRound)` —— 装配层可按需写入。
var cur_round := 0

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
var rope_speedups := {}
var cube_advanced := {}

# 对齐 Game.gd:512 —— EventType 的**反查表**（枚举值 → 名字字符串），在 _init 派生。
# ★ 曾把 eventTypeKeys 当「纯文本渲染」剔除，那是误判：MagicRing.giveStacksFromEffect
#   用它把 `effect.stackType`（int）转成**参数名**（"poison"/"cold"/…），紧接着
#   `getP(stackName)` 取的就是战斗数值（MagicRing.gd:107-109）。它是判定链的一环。
var event_type_keys := {}

# 对齐 Game.classResources（Game.gd:131 的职业 → 职业资源表）。
# 消费方：CoreCharacter.setClass / setClassResource —— 职业资源提供 health / stamina，
# 直接决定角色 maxHealth 与 baseMaxStamina。形如 {Classes.Ranger: {...}} 或
# {Classes.Ranger: Resource}，取字段统一用 .get(key)（Object.get 与 Dictionary.get 都通），
# 故宿主既能塞 Dictionary（纯数据/测试）也能塞真 Resource。
var class_resources = null

# ── 全局伤害源（对齐 Game.gd:2426-2433 的 _ready 构造） ──
#   unhealingDamageSource  origin=null  flags=unhealingFlags  (Character.gd:771)
#   fatigueDamageSource    origin=self  flags=CanBeBlocked    (Character.gd:1600)
#   stealLifeDamageSource  origin=null  flags=effectFlags
var unhealingDamageSource
var fatigueDamageSource
var stealLifeDamageSource

# 一次战斗的统计出口（供外部读取；不参与判定）
var out_of_stamina_count := 0  # 对齐 Game.numTimesOutOfStamina
var warn_unknown_api := true

# ── 延迟调用队列（替代原版的 call_deferred） ──
# 原版散落 6 处 call_deferred（Character.gd:968 重算体力上限、Item.gd:2035 旋转落位、
# Item.gd:1544 等）。语义都是「当前帧末执行」。内核不依赖场景树，故用一个显式队列
# 在帧末 flush（CoreCombat.physicsTick 的最后一步），次序与原版 SceneTree 的
# call_deferred 一致（同一帧内按入队顺序执行）。
var _deferred: Array = []


func _init(_seed: int = 0, _hooks = null) -> void :
	rng = CoreRng.new(_seed)
	util = CoreUtil.new(rng)
	util._ctx = self
	hooks = _hooks if _hooks != null else CoreHooks.new()
	bus = CoreEventBus.new()
	bus._ctx = self
	combat_log = CoreCombatLog.new()
	combat_log._ctx = self
	item_book = CoreItemBook.new()
	item_book._ctx = self
	
	# 对齐 Game.gd:2426-2433
	stealLifeDamageSource = _newDamageSource(null, CoreDamageSource.Type.Effect, 
		CoreDamageSource.effectFlags)
	unhealingDamageSource = _newDamageSource(null, CoreDamageSource.Type.Unhealing, 
		CoreDamageSource.unhealingFlags)
	fatigueDamageSource = _newDamageSource(self, CoreDamageSource.Type.Fatigue, 
		CoreDamageSource.Flags.CanBeBlocked)
	
	# 对齐 Game.gd:512 `onready var eventTypeKeys = Util.invertDictionary(EventType)`
	event_type_keys = CoreUtil.invertDictionary(CoreConst.EventType)


func _newDamageSource(origin, type: int, flags: int):
	var src = CoreDamageSource.new()
	src._rng = rng
	src.init(origin, type)
	src.flags = flags
	return src


func getCharacterFromId(playerId: int):
	return player if playerId == CoreCharacter.ID.PLAYER else opponent


func otherCharacter(character):
	return opponent if character == player else player


# ── 物理帧推进（对齐 Util.gd:148-152） ──
func advancePhysicsFrame(delta: float = PHYSICS_DELTA) -> void :
	frame_counter += 1
	time += delta
	combat_time += delta
	_flushTimed()


# ── 按时延迟调用（对齐 Util.callDelayed 的 `get_tree().create_timer(delay)`） ──
# 与下面的 _deferred（帧末）区分：这是**按时长**触发的一次性回调。
# 原版走 SceneTreeTimer，粒度也是帧；此处按 ctx.time（同一物理帧累加量）判到期，
# 故触发时刻与原版落在同一帧。到期检查放在时间推进之后、帧末队列之前 ——
# 原版 SceneTreeTimer 与 call_deferred 都在帧末处理，两者之间的先后不影响判定
# （已核：物品侧不存在同时依赖二者的同一帧路径）。
var _timed: Array = []


func callDelayed(obj, methodName: String, delay: float, binds: Array = []) -> void :
	if obj == null:
		return
	_timed.push_back([obj, methodName, time + delay, binds])


func _flushTimed() -> void :
	if _timed.empty():
		return
	var due: Array = []
	var keep: Array = []
	for call in _timed:
		if call[2] <= time:
			due.push_back(call)
		else:
			keep.push_back(call)
	if due.empty():
		return
	_timed = keep
	for call in due:
		call[0].callv(call[1], call[3])


# ── 延迟调用（对齐 Node.call_deferred） ──
func defer(obj, methodName: String, args: Array = []) -> void :
	_deferred.push_back([obj, methodName, args])


func hasDeferred() -> bool:
	return not _deferred.empty()


# 帧末 flush。执行期间新入队的调用留到下一帧（与 SceneTree 语义一致）。
func flushDeferred() -> void :
	if _deferred.empty():
		return
	var batch = _deferred
	_deferred = []
	for call in batch:
		var obj = call[0]
		if obj == null:
			continue
		obj.callv(call[1], call[2])


# ── 空背包回落（对齐「Game.PLAYER.INVENTORY 恒非空」） ──
# 原版 Item.getOwnOrPlayerInventory() 未放置时回落到 Game.PLAYER.INVENTORY，那是个
# autoload 上的真实节点，**永不为 null**。内核里 player 由装配层注入，在装配早期
# （物品尚未挂到任何角色、或纯几何查询）可能还没有 player，此时若返回 null，
# 调用方 .getItemsInCells(...) 会直接崩。此处提供一个共享空网格，使「查询得到空集」
# 这一语义与原版一致，而不是崩。
var _emptyGrid = null


func emptyGrid():
	if _emptyGrid == null:
		_emptyGrid = CoreGrid.new(null)
	return _emptyGrid
