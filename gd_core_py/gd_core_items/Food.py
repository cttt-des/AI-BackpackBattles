# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Food(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Food.gd"


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food) and item.descriptor != self.descriptor


	def prepare(self):
		super().prepare()
		self.addSpeed(self.getNumAffectedItems() * 0.1)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Food.gd", Food)
_R.reg("Food", Food)
_R.reg("Food", Food)
