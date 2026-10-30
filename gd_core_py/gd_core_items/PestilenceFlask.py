# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class PestilenceFlask_2(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/PestilenceFlask.gd"


	def onTriggerPotion(self, triggerEvent=None):
		self.inflictPoison(self.getP1(), triggerEvent)
		self.selfInflictPoison(self.getP2(), triggerEvent)


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_healed", "onOpponentHeal")


	def onOpponentHeal(self, _amount, event):
		if self.isEmpty():
			return

		# ★ np25 evt12 面 AFFL 探针（双门控零耗链）：反制投掷链定谳——
		#   getAffectedItems 运行时值（gd 3 投 v oracle 2 投，affected[0] 链
		#   是否多执行一级）。定谳后可移除或保留（零耗不影响行为）。
		_aff = self.getAffectedItems()
		_aff_names = ""
		for _a in _iter(_aff):
			_aff_names += String(_a.descriptor.identifier) + ","
		self.ctx.rng.trace_diag("AFFL", String(self.descriptor.identifier), "n=" + str(len(_aff)), _aff_names)

		self.drink()

		self.triggerPotion(event)

		affected = self.getAffectedItems()
		if not (not affected):
			affected[0].triggerPotion(event)
			affected[0].miniActivate()

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/PestilenceFlask.gd", PestilenceFlask_2)
_R.reg("PestilenceFlask", PestilenceFlask_2)
