# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ShieldofValor(_R.C("res://gd_core_items/Shield.gd")):

	resource_path = "res://gd_core_items/ShieldofValor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blockFactor = None


	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_R.C("CoreConst").EventType.Block, self.blockFactor)


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)
		self.activate()


	def _readyInit(self):
		super()._readyInit()
		self.blockFactor = _div(self.getP3(), 100.0)


_R.reg("res://gd_core_items/ShieldofValor.gd", ShieldofValor)
_R.reg("ShieldofValor", ShieldofValor)
