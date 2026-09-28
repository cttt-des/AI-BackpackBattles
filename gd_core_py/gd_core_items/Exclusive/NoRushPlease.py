# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__NoRushPlease(_R.C("res://gd_core_items/LeatherHelm.gd")):

	resource_path = "res://gd_core_items/Exclusive/NoRushPlease.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cold = None


	def onPrepare(self):
		pass


	def onPreCombatStart(self):
		super().onPreCombatStart()
		self.opponent().changeDamageResistance(self.damReduction)


	def buffEnded(self):
		super().buffEnded()
		self.opponent().changeDamageResistance( - self.damReduction)


	def onCombatStart(self):
		self.inflictCold(self.cold)
		super().onCombatStart()

	def _readyInit(self):
		super()._readyInit()
		self.cold = int(self.getP("cold"))


_R.reg("res://gd_core_items/Exclusive/NoRushPlease.gd", Exclusive__NoRushPlease)
_R.reg("NoRushPlease", Exclusive__NoRushPlease)
