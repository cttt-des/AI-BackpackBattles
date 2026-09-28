# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletUnidentified(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletUnidentified.gd"


	def onDropped(self, dropRes):
		if (self.wasAddedToInventory(dropRes) or 
			dropRes == self.DropResult.AddedToStorageBox):

			self.prepareReplacement()
			self.ctx.defer(self, "identifyAmulet", [dropRes])


	def identifyAmulet(self, dropResult):
		pass

	def getRelatedItemColumns(self):
		return 4


	def getRelatedItemHeight(self):
		return 100

	def _readyInit(self):
		super()._readyInit()
		self.connect("dropped", self, "onDropped")



_R.reg("res://gd_core_items/Exclusive/AmuletUnidentified.gd", Exclusive__AmuletUnidentified)
_R.reg("AmuletUnidentified", Exclusive__AmuletUnidentified)
