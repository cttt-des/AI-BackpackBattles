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
#   ★ np25w_f01 订正：以上 onTimeout 的「取下一时间戳/递归」在神谕 harness 下
#     不可达——oracle_fight.gd drive_timers 到点段先 `timer.stop()`（清排队）
#     再 emit。内核 _onTimeout 已按此对齐（见该函数注释），叠加排队只活到
#     首个到期拍。
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
# ★ np25w_f11 注册表同构（oracle_fight.gd drive_timers :881-919）：
#   阻塞循环无帧时钟 ⇒ 引擎 time_left 冻结、仅 start/stop 改写。harness 以
#   「eng != e[1]」判外部 start 并重同步 e[0]；冻结时钟下 eng 恒=wait_time，
#   故【运行中同值 start 是注册表盲区】——e[0] 沿旧截止期继续递减=重启丢失
#   （真实引擎有帧时钟本会重置；但语料即冻结时钟语义，461 绿场同此，gd 从之）。
var _eng := 0.0            # 引擎 time_left 冻结镜像（仅 start/stop 改写）
var _seen := 0.0           # 注册表 e[1]：上一 pass 的 eng（battle setup 登记 [left,left]；
                           #   stopped pass 走 e[0]=-1 分支不更新 e[1]）
# ★ np26fA multi 相位锚：multi start 发生在本拍 tickTimersPass **之后**时（如 EB
#   ChargeTimer=charge_emitted 回调链），下一拍 tick 的登记分支须照常递减 1 次
#   补相位——语料 harness drive_timers 对该场景登记拍也不递减，但语料事件
#   t=(fire拍-1)×dt（combatTime 在 drive_timers 之后推进=落后 1 tick）而 gd 事件
#   t=fire拍×dt（combat_time 在 tickTimersPass 之前推进=领先），两口径差 1 tick，
#   gd 端用「登记拍递减」吸收（run1160 EB Battery 5.0167 实证）。同拍 start
#   （start 在 tickTimersPass 之前，如 SPF poisonTimer=character_healed 链）则
#   登记拍不递减（run590 SPF 毒 4.9833 实证）。
var _multi_start_time := -1.0


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
# ★ kernel_r3：oracle_fight.gd drive_timers 的注册表语义（:881-905）——外部
#   start(x) 当 tick：`eng(x) != e[1] → e[0] = eng`，**注册 tick 不递减**，首帧
#   递减发生在下一 tick。此前 _left 直赋 + 同 tick step⑦ 即递减 → 一切中途
#   启动的计时器恒早 1 tick 到期（run583_r11 SPF 毒批语料 5.5167 v gd 5.5，
#   P3=3.5=210 tick 整、heal@1.9833 实证）。_started_frame 记注册 tick，
#   tick() 同帧跳过一次递减；循环内 handler 重启（_onTimeout 的 start(dif)）
#   走 oracle 的 restart 语义（当帧已消耗递减、下帧照常），不设标记。
var _started_frame := -1

func start(time = -1.0) -> void :
	if time != null:
		wait_time = time
	if multi and not _stopped:
		timestamps.push_back(_utilTime() + wait_time)
		return
	if multi:
		# multi 停止态重启：★ np28W3（run1134_r18 SPKR 哨兵定谳）——**不再直赋
		#   _left=wait_time**：oracle harness 对 MultiTimer 重启同走 eng==e[1]
		#   碰撞判定（stop 期间 e[0]=-1 每帧重置；同值 start 后 -1-dt≤0 当拍
		#   fire）——Echoing Battlecry 重放 LeatherHelm：oracle 重放 start(3)
		#   碰撞立即 fire（buffEnded +25/-25 同拍抵消，fW1134 SPKR 890/895 同
		#   t=6.583 铁证），gd 旧码 _left 直赋冲掉 -1 遗留→正常 3s 后才 fire
		#   （fd@7.67 DR 残留 25 → spikes 反弹 round(7×0.75)=5 v 语料 7）。
		#   _left 交 tick() 的 eng vs _seen 判定：eng==_seen→遗留值递减（立即
		#   fire）；eng!=_seen→登记分支 _left=eng（f01 首启 _seen=0 恒走此，
		#   语义不变；np26fA 相位补偿在登记分支，保持）。
		_stopped = false
		_eng = wait_time
		_multi_start_time = _utilTime()
		return
	_eng = wait_time      # 引擎：start 必写 time_left=wait_time（3.6 语义）
	_stopped = false
	# ★ 重同步移交 tick()（eng vs _seen 判定），不再无条件 _left=wait_time


# 对齐 MultiTimer.gd:20-22
func stop() -> void :
	timestamps.clear()
	_stopped = true
	_eng = 0.0            # 引擎：stop ⇒ time_left=0
	# ★ e[0]（_left）不动——harness 只在【停走 pass】置 e[0]=-1（:889-891）；
	#   同一处理器内 stop+start（changeTimer 模式）之间无 drive pass，
	#   旧截止期存活（f10 棺材案 3.4 提前触发=此处曾误清）。


# 对齐 MultiTimer.gd:24-25
func isFinished() -> bool:
	return timestamps.empty()


# 由物理帧推进（对齐 Timer 的 process_mode = TIMER_PROCESS_PHYSICS）
func tick(delta: float) -> void :
	if _stopped:
		_left = -1.0      # ★ 停走 pass：e[0]=-1（:889-891）——此后同值 start
		return            #   会在下一 pass 立即到点（harness 语义，语料实证）
	# ★ 注册表同构（:897-901）：eng=_eng（冻结）；eng != _seen ⇒ 外部 start/
	#   changeTimer → e[0]=eng（登记/重启拍不递减=kernel_r3 语义，由本分支覆盖，
	#   _started_frame 机制退役）；eng == _seen ⇒ 正常递减——同值 start 落此
	#   分支=重启丢失（盲区），旧截止期存活。
	var eng = _eng
	if eng != _seen:
		_left = eng
		# ★ np26fA 相位补偿：multi start 发生在上一拍 tickTimersPass 之后时，
		#   本拍（=start 后第一个 tick pass）登记拍照常递减（事件 t 口径差
		#   1 tick 的吸收，见 _multi_start_time 注）。同拍 start 不补。
		if multi and _multi_start_time >= 0.0 and _multi_start_time < _utilTime():
			_left = eng - delta
		_multi_start_time = -1.0
	else:
		_left = _left - delta
	_seen = eng
	if _left > 0.0:
		return
	_onTimeout()


# 对齐 MultiTimer.gd:27-38
# ★ np25w_f01 定谳（run583_r11 SPF 毒批首分歧@120：gd 3 发 v 语料 2 发）：
#   到点序列必须对齐 oracle_fight.gd drive_timers 到点段（:908-912）——引擎侧
#   `timer.stop()` 先于 `emit_signal("timeout")`。MultiTimer.stop()
#   （oracle/Utility/MultiTimer.gd:20-22）清 timestamps ⇒ start() 在运行中
#   排队的叠加到期（timestamps.push_back）在首个到期拍**全部丢弃**。
#   实证链：1.9833 拍两侧 canonical 逐行全等 ⇒ 双侧同为 3 次 start
#   （瓶1 own+chain 叠加、瓶2 own）；语料 fire=2（瓶1 叠加被 stop 清掉），
#   gd 旧 pop/递归语义 fire=3。处理器内再 start(x)（refresh 语义）因
#   先已 _stopped=true 走重启动分支（push 分支不触发），与 harness emit 后
#   `is_stopped()==false → e[0]=time_left` 同构。
func _onTimeout() -> void :
	_stopped = true
	_left = 0.0
	if multi:
		timestamps.clear()
	fire_count += 1
	if _owner != null and callback_method != "":
		_owner.call(callback_method)

	if _stopped:
		return          # 处理器未重启：叠加排队已清、one_shot 恒停（=harness e[0]=-1）
	if multi:
		return          # multi 重启走 start() 的 timestamps 路径（f01 语义）
	# ★ post-emit 重挂（harness :915-919）：处理器重启 ⇒ e[0]=e[1]=eng 无条件
	#   （含同值）；循环计时器无重启 ⇒ harness 代 start(w) 兜底续接，同式。
	_left = wait_time
	_seen = wait_time
	_eng = wait_time


# 对齐 Util.time（无 ctx 时的兜底，便于独立单测）
func _utilTime() -> float:
	if _ctx != null:
		return _ctx.time
	return 0.0
