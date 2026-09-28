# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FrozenBuckler(_R.C("res://gd_core_items/Shield.gd")):

	resource_path = "res://gd_core_items/Exclusive/FrozenBuckler.gd"

	def _init_fields(self):
		super()._init_fields()
		self.coldInflicted = 0


	def onPrepare(self):
		self.coldInflicted = 0


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)
		if self.coldInflicted < self.getP4():
			self.coldInflicted += 1
			self.inflictCold(self.getP3(), self.blockedDamageRes.event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/FrozenBuckler.gd", Exclusive__FrozenBuckler)
_R.reg("FrozenBuckler", Exclusive__FrozenBuckler)
