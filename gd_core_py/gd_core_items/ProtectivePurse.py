# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ProtectivePurse(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/ProtectivePurse.gd"


	def onCombatStart(self):
		totalBlock = self.getBlock()
		if self.isTypeInInventory(self.ctx.item_book.getDescriptor("Bagtacular")):
			totalBlock += self.ctx.item_book.getDescriptor("Bagtacular").getP("block")

		self.giveBlock(totalBlock)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/ProtectivePurse.gd", ProtectivePurse)
_R.reg("ProtectivePurse", ProtectivePurse)
