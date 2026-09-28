# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CustomerCard(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/CustomerCard.gd"


	def onCalcTradeChance(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/CustomerCard.gd", CustomerCard)
_R.reg("CustomerCard", CustomerCard)
