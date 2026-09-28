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
		self.giveStacks(self.character(), _R.C("CoreConst").EventType.Blind, self.blind)
		self.activate()


	def buffEnded(self):
		if self.buffsActive > 0:
			super().buffEnded()
			self.opponent().changeDamageResistance( - self.damReduction)
			self.ctx.sandbag_active = False



	def _readyInit(self):
		super()._readyInit()
		self.blind = int(self.getP("blind"))


_R.reg("res://gd_core_items/Exclusive/Sandbag.gd", Exclusive__Sandbag)
_R.reg("Sandbag", Exclusive__Sandbag)
