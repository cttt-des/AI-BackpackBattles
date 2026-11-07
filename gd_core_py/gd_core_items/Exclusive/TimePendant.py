# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__TimePendant(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/TimePendant.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cdAdvance = None


	def canAffect(self, item):
		return item.hasCooldown()


	def doCooldownEffect(self):
		item = self.getFirstAffectedItem()
		if item != None and item.isCooldownActive():
			item.advanceCooldownSeconds(self.cdAdvance)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.cdAdvance = self.getP("cdadvance")


_R.reg("res://gd_core_items/Exclusive/TimePendant.gd", Exclusive__TimePendant)
_R.reg("TimePendant", Exclusive__TimePendant)
