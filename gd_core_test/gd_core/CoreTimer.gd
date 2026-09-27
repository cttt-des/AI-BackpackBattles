# =============================================================================
# CoreTimer.gd — 无头战斗内核：虚拟计时器
# =============================================================================
# 对齐两个原版源：
#   1) Godot 内建 `Timer`（物品 tscn 里的 XxxTimer 节点，process_mode = 0 即物理帧）
#   2) Utility/MultiTimer.gd（BuffTimer 等 17 处使用）
#
# 为什么必须建模（而不是当视觉剥掉）：
#   物品脚本用计时器承载**判定**。例如 CritwoodStaff：
#       onPreDealDamage_early → Util.changeTimer(critTimer, critBuffDur)   （重置 buff 时长）
#       onCombatEnd           → critTimer.stop()                            （结束 buff）
#   而 tscn 把 `timeout` 连到 `buffEnded`，后者会 reduceCritChancePercent(100)。
#   LeatherHelm 的 BuffTimer 同理（`multi_timeout → buffEnded`）。
#   若计时器不推进，这些 buff 会「开了永不结束」—— 与上一轮修掉的 `_invul_left`
#   只写不推进是同一类 bug，故此处一并模型化。
#
# 逐字对齐 MultiTimer.gd：
#   start(t)：已停止 → 正常启动；否则 → 把 `Util.time + t` 压入 timestamps
#   stop()：清 timestamps 并停止
#   onTimeout()：先发信号，再取下一个时间戳；差值 > 0.05 则重新 start，否则立即递归
#   内核把 `Util.time` 换成 `ctx.time`（同一物理帧累加量），把 `emit_signal("multi_timeout")`
#   换成 tscn 连接的等价物：直接调用目标方法（全部 43 条连接都是 `to="."`，即物品自身）。
#
# 连接来源：`tools/scan_tscn_connections.py` 实测 —— Items 下 760 个 tscn 共 43 条
# [connection]，**全部** signal ∈ {timeout, multi_timeout}、**全部** to="."。
# 故内核只需「计时器 → 物品的一个方法名」这一种回调形态。
# =============================================================================
extends Reference
class_name CoreTimer


var _ctx = null
var _owner = null          # 回调目标（物品自身）
var name := ""             # 对齐 tscn 节点名，便于对照

var wait_time := 1.0
var one_shot := true
var multi := false         # true → MultiTimer 语义（可叠加排队）
var callback_method := ""  # 对齐 `[connection ... method="X"]`

# MultiTimer.gd 的 timestamps
var timestamps: Array = []

var _left: float = 0.0
var _stopped := true
var fire_count := 0        # 供测试断言


func _init(ctx = null, owner = null, timerName: String = "") -> void :
	_ctx = ctx
	_owner = owner
	name = timerName


func is_stopped() -> bool:
	return _stopped


func get_time_left() -> float:
	if _stopped:
		return 0.0
	return _left


# 对齐 MultiTimer.gd:12-18 / Godot Timer.start(time)
func start(time = -1.0) -> void :
	if time != null:
		wait_time = time
	if multi and not _stopped:
		timestamps.push_back(_utilTime() + wait_time)
		return
	_stopped = false
	_left = wait_time


# 对齐 MultiTimer.gd:20-22
func stop() -> void :
	timestamps.clear()
	_stopped = true
	_left = 0.0


# 对齐 MultiTimer.gd:24-25
func isFinished() -> bool:
	return timestamps.empty()


# 由物理帧推进（对齐 Timer 的 process_mode = TIMER_PROCESS_PHYSICS）
func tick(delta: float) -> void :
	if _stopped:
		return
	_left -= delta
	if _left > 0.0:
		return
	_onTimeout()


# 对齐 MultiTimer.gd:27-38
func _onTimeout() -> void :
	fire_count += 1
	if _owner != null and callback_method != "":
		_owner.call(callback_method)
	
	if not multi:
		if one_shot:
			_stopped = true
		else:
			_left = wait_time
		return
	
	_stopped = true
	if not isFinished():
		var nextTimestamp = timestamps.pop_front()
		var dif = nextTimestamp - _utilTime()
		if dif > 0.05:
			start(dif)
		else:
			_onTimeout()


# 对齐 Util.time（无 ctx 时的兜底，便于独立单测）
func _utilTime() -> float:
	if _ctx != null:
		return _ctx.time
	return 0.0
