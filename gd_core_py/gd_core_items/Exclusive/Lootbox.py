# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Lootbox(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Lootbox.gd"

	def _init_fields(self):
		super()._init_fields()
		self.itemValue = None

	OFFSET = 50.0

	def onDropped(self, dropRes):
		if (self.wasAddedToInventory(dropRes) or 
			dropRes == self.DropResult.AddedToStorageBox):

			self.prepareReplacement()
			self.ctx.defer(self, "generateItems", [dropRes])


	def generateItems(self, dropResult):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.itemValue = int(self.getP("gold"))
		self.connect("dropped", self, "onDropped")



_R.reg("res://gd_core_items/Exclusive/Lootbox.gd", Exclusive__Lootbox)
_R.reg("Lootbox", Exclusive__Lootbox)
