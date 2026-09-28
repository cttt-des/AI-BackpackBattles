# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SlimeTime(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SlimeTime.gd"

	def _init_fields(self):
		super()._init_fields()
		self.gooblingDescriptor = None


	def onBought(self):
		pass

	def doCooldownEffect(self):
		for item in _iter(self.inventory.getItems()):
			if self.canAffect_global(item):
				item.onItemActivated(None)
		self.activate()


	def getGatedDescriptor(self, _rarity):
		return self.gooblingDescriptor


	def canAffect_global(self, item):
		return isinstance(item, _R.C("Goobert"))

	def _readyInit(self):
		super()._readyInit()
		self.gooblingDescriptor = self.ctx.item_book.getDescriptor("Goobling")


_R.reg("res://gd_core_items/Exclusive/SlimeTime.gd", Exclusive__SlimeTime)
_R.reg("SlimeTime", Exclusive__SlimeTime)
