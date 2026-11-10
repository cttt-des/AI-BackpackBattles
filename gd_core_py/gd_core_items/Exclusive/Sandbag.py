# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Sandbag(_R.C("res://gd_core_items/LeatherHelm.gd")):

	resource_path = "res://gd_core_items/Exclusive/Sandbag.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blind = None


	def onPrepare(self):
		pass


	def onPreCombatStart(self):
		if not self.ctx.sandbag_active:
			self.ctx.sandbag_active = True
			super().onPreCombatStart()
			self.opponent().changeDamageResistance(self.damReduction)
		elif self.buffsActive > 0:
			self.ctx.util.changeTimer(self.buffTimer, self.getBuffDur())


	def onCombatStart(self):
		self.inflictBlind(self.blind)
		self.giveStacks(self.character(), _H_1, self.blind)
		self.activate()


	def buffEnded(self):
		if self.buffsActive > 0:
			super().buffEnded()
			self.opponent().changeDamageResistance( - self.damReduction)
			self.ctx.sandbag_active = False



	def _readyInit(self):
		super()._readyInit()
		# ★ np49（run602_r14 fd@334）：oracle 的 Sandbag.tscn BuffTimer=**普通 one_shot
		#   Timer（无脚本）+ timeout→buffEnded**（Exclusive/Sandbag.tscn:70-73,89——区别于
		#   父类 LeatherHelm.tscn 的 MultiTimer+multi_timeout）。此前继承 LH 的
		#   newItemTimer(..., multi=true)：changeTimer 延长（start(t+left)）走 CoreTimer
		#   multi 运行中分支=仅 push timestamps、引擎读数不改写 ⇒ 注册表 eng==e[1] 不
		#   重同步 ⇒ 按原截止期提前 fire（EB 回声 changeTimer@5.5 后 SB 仍 7.017 炸，
		#   oracle 实证 eng→8.5167 重同步、14.017 才炸）→ damageResistance 窗口错位
		#   → 14 处疲劳 dmg 分歧。修=按 tscn 真身重建为非 multi。
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.blind = int(self.getP("blind"))


_R.reg("res://gd_core_items/Exclusive/Sandbag.gd", Exclusive__Sandbag)
_R.reg("Sandbag", Exclusive__Sandbag)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
