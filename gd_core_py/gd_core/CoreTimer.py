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




	# MultiTimer.gd 的 timestamps



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
	def start(self, time=-1.0):
		if time != None:
			self.wait_time = time
		if self.multi and not self._stopped:
			self.timestamps.append(self._utilTime() + self.wait_time)
			return
		self._stopped = False
		self._left = self.wait_time


	# 对齐 MultiTimer.gd:20-22
	def stop(self):
		self.timestamps.clear()
		self._stopped = True
		self._left = 0.0


	# 对齐 MultiTimer.gd:24-25
	def isFinished(self):
		return (not self.timestamps)


	# 由物理帧推进（对齐 Timer 的 process_mode = TIMER_PROCESS_PHYSICS）
	def tick(self, delta):
		if self._stopped:
			return
		self._left -= delta
		if self._left > 0.0:
			return
		self._onTimeout()


	# 对齐 MultiTimer.gd:27-38
	def _onTimeout(self):
		self.fire_count += 1
		if self._owner != None and self.callback_method != "":
			self._owner.call(self.callback_method)

		if not self.multi:
			if self.one_shot:
				self._stopped = True
			else:
				self._left = self.wait_time
			return

		self._stopped = True
		if not self.isFinished():
			nextTimestamp = self.timestamps.pop(0)
			dif = nextTimestamp - self._utilTime()
			if dif > 0.05:
				self.start(dif)
			else:
				self._onTimeout()


	# 对齐 Util.time（无 ctx 时的兜底，便于独立单测）
	def _utilTime(self):
		if self._ctx != None:
			return self._ctx.time
		return 0.0


_R.reg("res://gd_core/CoreTimer.gd", CoreTimer)
_R.reg("CoreTimer", CoreTimer)
_R.reg("CoreTimer", CoreTimer)
