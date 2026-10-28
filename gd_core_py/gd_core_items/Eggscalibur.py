# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Eggscalibur_2(_R.C("res://gd_core_items/Pan.gd")):

	resource_path = "res://gd_core_items/Eggscalibur.gd"


	def onDealtDamage(self, damageRes):
		event = self.tryUseMana(self.getP2(), damageRes.event)
		if event:
			affected = self.getAffectedItems()
			_shuffle(affected)
			_ids = ""
			for food in _iter(affected):
				_ids += String(food.descriptor.identifier) + "|"
			self.ctx.rng.trace_diag("ESHUF", str(_ids), "t=" + str(self.ctx.time), "")
			for food in _iter(affected):
				food.doCooldownEffect()


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Eggscalibur.gd", Eggscalibur_2)
_R.reg("Eggscalibur", Eggscalibur_2)
