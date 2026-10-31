# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreTimer(GodotObject):

	resource_path = "res://gd_core/CoreTimer.gd"

	def _init_fields(self):
		super()._init_fields()
		self._ctx = None
		self._owner = None          # 回调目标（物品自身）
		self.name = ""             # 对齐 tscn 节点名，便于对照
		self.wait_time = 1.0
		self.one_shot = True
		self.multi = False         # true → MultiTimer 语义（可叠加排队）
		self.callback_method = ""  # 对齐 `[connection ... method="X"]`
		self.timestamps = []
		self._left = 0.0
		self._stopped = True
		self.fire_count = 0        # 供测试断言
		self._eng = 0.0            # 引擎 time_left 冻结镜像（仅 start/stop 改写）
		self._seen = 0.0           # 注册表 e[1]：上一 pass 的 eng（battle setup 登记 [left,left]；
		self._multi_start_time = -1.0
		self._started_frame = -1

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




	# MultiTimer.gd 的 timestamps

	# ★ np25w_f11 注册表同构（oracle_fight.gd drive_timers :881-919）：
	#   阻塞循环无帧时钟 ⇒ 引擎 time_left 冻结、仅 start/stop 改写。harness 以
	#   「eng != e[1]」判外部 start 并重同步 e[0]；冻结时钟下 eng 恒=wait_time，
	#   故【运行中同值 start 是注册表盲区】——e[0] 沿旧截止期继续递减=重启丢失
	#   （真实引擎有帧时钟本会重置；但语料即冻结时钟语义，461 绿场同此，gd 从之）。
	#   stopped pass 走 e[0]=-1 分支不更新 e[1]）
	# ★ np26fA multi 相位锚：multi start 发生在本拍 tickTimersPass **之后**时（如 EB
	#   ChargeTimer=charge_emitted 回调链），下一拍 tick 的登记分支须照常递减 1 次
	#   补相位——语料 harness drive_timers 对该场景登记拍也不递减，但语料事件
	#   t=(fire拍-1)×dt（combatTime 在 drive_timers 之后推进=落后 1 tick）而 gd 事件
	#   t=fire拍×dt（combat_time 在 tickTimersPass 之前推进=领先），两口径差 1 tick，
	#   gd 端用「登记拍递减」吸收（run1160 EB Battery 5.0167 实证）。同拍 start
	#   （start 在 tickTimersPass 之前，如 SPF poisonTimer=character_healed 链）则
	#   登记拍不递减（run590 SPF 毒 4.9833 实证）。


	def _init(self, ctx=None, owner=None, timerName=""):
		self._ctx = ctx
		self._owner = owner
		self.name = timerName


	def is_stopped(self):
		return self._stopped


	def get_time_left(self):
		if self._stopped:
			return 0.0
		return self._left


	# 对齐 MultiTimer.gd:12-18 / Godot Timer.start(time)
	# ★ kernel_r3：oracle_fight.gd drive_timers 的注册表语义（:881-905）——外部
	#   start(x) 当 tick：`eng(x) != e[1] → e[0] = eng`，**注册 tick 不递减**，首帧
	#   递减发生在下一 tick。此前 _left 直赋 + 同 tick step⑦ 即递减 → 一切中途
	#   启动的计时器恒早 1 tick 到期（run583_r11 SPF 毒批语料 5.5167 v gd 5.5，
	#   P3=3.5=210 tick 整、heal@1.9833 实证）。_started_frame 记注册 tick，
	#   tick() 同帧跳过一次递减；循环内 handler 重启（_onTimeout 的 start(dif)）
	#   走 oracle 的 restart 语义（当帧已消耗递减、下帧照常），不设标记。

	def start(self, time=-1.0):
		if time != None:
			self.wait_time = time
		if self.multi and not self._stopped:
			self.timestamps.append(self._utilTime() + self.wait_time)
			return
		if self.multi:
			# multi 停止态重启：维持 f01 对齐语义（无条件满计数）
			self._stopped = False
			self._left = self.wait_time
			# ★ np26fA 定谳（run590_r13 SPF 毒 4.9667 v 语料 4.9833=早 1 tick）：
			#   f11 注册表同构重构时 multi 分支漏写 _eng——同帧 tickTimersPass 里
			#   eng(0.0)==_seen(0.0) 走递减分支=登记拍同帧递减，multi timer 恒早
			#   1 tick（f01 的 _started_frame 机制退役后未补 eng/_seen 等价物）。
			#   语料 harness drive_timers 对 MultiTimer 同走 eng!=e[1] 判定
			#   （oracle_fight.gd:899-901，SPF tscn PoisonTimer 挂 MultiTimer 脚本
			#   实证），补 _eng 后同帧 tick 走登记分支（不递减），211 递减对齐。
			self._eng = self.wait_time
			self._multi_start_time = self._utilTime()
			return
		self._eng = self.wait_time      # 引擎：start 必写 time_left=wait_time（3.6 语义）
		self._stopped = False
		# ★ 重同步移交 tick()（eng vs _seen 判定），不再无条件 _left=wait_time


	# 对齐 MultiTimer.gd:20-22
	def stop(self):
		self.timestamps.clear()
		self._stopped = True
		self._eng = 0.0            # 引擎：stop ⇒ time_left=0
		# ★ e[0]（_left）不动——harness 只在【停走 pass】置 e[0]=-1（:889-891）；
		#   同一处理器内 stop+start（changeTimer 模式）之间无 drive pass，
		#   旧截止期存活（f10 棺材案 3.4 提前触发=此处曾误清）。


	# 对齐 MultiTimer.gd:24-25
	def isFinished(self):
		return (not self.timestamps)


	# 由物理帧推进（对齐 Timer 的 process_mode = TIMER_PROCESS_PHYSICS）
	def tick(self, delta):
		if self._stopped:
			self._left = -1.0      # ★ 停走 pass：e[0]=-1（:889-891）——此后同值 start
			return            #   会在下一 pass 立即到点（harness 语义，语料实证）
		# ★ 注册表同构（:897-901）：eng=_eng（冻结）；eng != _seen ⇒ 外部 start/
		#   changeTimer → e[0]=eng（登记/重启拍不递减=kernel_r3 语义，由本分支覆盖，
		#   _started_frame 机制退役）；eng == _seen ⇒ 正常递减——同值 start 落此
		#   分支=重启丢失（盲区），旧截止期存活。
		eng = self._eng
		if eng != self._seen:
			self._left = eng
			# ★ np26fA 相位补偿：multi start 发生在上一拍 tickTimersPass 之后时，
			#   本拍（=start 后第一个 tick pass）登记拍照常递减（事件 t 口径差
			#   1 tick 的吸收，见 _multi_start_time 注）。同拍 start 不补。
			if self.multi and self._multi_start_time >= 0.0 and self._multi_start_time < self._utilTime():
				self._left = eng - delta
			self._multi_start_time = -1.0
		else:
			self._left = self._left - delta
		self._seen = eng
		if self._left > 0.0:
			return
		self._onTimeout()


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
	def _onTimeout(self):
		self._stopped = True
		self._left = 0.0
		if self.multi:
			self.timestamps.clear()
		self.fire_count += 1
		if self._owner != None and self.callback_method != "":
			self._owner.call(self.callback_method)

		if self._stopped:
			return          # 处理器未重启：叠加排队已清、one_shot 恒停（=harness e[0]=-1）
		if self.multi:
			return          # multi 重启走 start() 的 timestamps 路径（f01 语义）
		# ★ post-emit 重挂（harness :915-919）：处理器重启 ⇒ e[0]=e[1]=eng 无条件
		#   （含同值）；循环计时器无重启 ⇒ harness 代 start(w) 兜底续接，同式。
		self._left = self.wait_time
		self._seen = self.wait_time
		self._eng = self.wait_time


	# 对齐 Util.time（无 ctx 时的兜底，便于独立单测）
	def _utilTime(self):
		if self._ctx != None:
			return self._ctx.time
		return 0.0


_R.reg("res://gd_core/CoreTimer.gd", CoreTimer)
_R.reg("CoreTimer", CoreTimer)
_R.reg("CoreTimer", CoreTimer)
