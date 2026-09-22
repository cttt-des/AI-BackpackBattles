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


func _init(_seed: int = 0, _hooks = null) -> void :
	rng = CoreRng.new(_seed)
	hooks = _hooks if _hooks != null else CoreHooks.new()
	bus = CoreEventBus.new()
	bus._ctx = self
	combat_log = CoreCombatLog.new()
	combat_log._ctx = self
	
	# 对齐 Game.gd:2426-2433
	stealLifeDamageSource = _newDamageSource(null, CoreDamageSource.Type.Effect, 
		CoreDamageSource.effectFlags)
	unhealingDamageSource = _newDamageSource(null, CoreDamageSource.Type.Unhealing, 
		CoreDamageSource.unhealingFlags)
	fatigueDamageSource = _newDamageSource(self, CoreDamageSource.Type.Fatigue, 
		CoreDamageSource.Flags.CanBeBlocked)


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
