# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__EngineerBag2(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/EngineerBag2.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cogDescriptor = None


	def onShopEntered(self):
		pass

	def onItemRoll(self, descr):
		pass

	def getRelatedItems(self):
		return [self.cogDescriptor]

	def _readyInit(self):
		super()._readyInit()
		self.cogDescriptor = self.ctx.item_book.getDescriptor("Cog")


_R.reg("res://gd_core_items/Exclusive/EngineerBag2.gd", Exclusive__EngineerBag2)
_R.reg("EngineerBag2", Exclusive__EngineerBag2)
