# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Holdall(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/Holdall.gd"


	def canApplyEffect(self, toItem):
		return toItem.isNeutral()


	def onCombatStart(self):
		block = self.getBlock() * self.getNumAffectedInside()
		if block > 0:
			self.giveBlock(block)
			self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Holdall.gd", Exclusive__Holdall)
_R.reg("Holdall", Exclusive__Holdall)
