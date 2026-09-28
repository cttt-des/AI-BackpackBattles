# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Snowman(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Snowman.gd"

	def _init_fields(self):
		super()._init_fields()
		self.snowballDescriptor = None


	def onDropped(self, dropRes):
		if (self.wasAddedToInventory(dropRes) or 
			dropRes == self.DropResult.AddedToStorageBox):

			self.prepareReplacement()
			self.ctx.defer(self, "replaceWithSnowballs", [dropRes])


	def replaceWithSnowballs(self, dropResult):
		pass

	def getRecipeDescriptor(self):
		return self.snowballDescriptor

	def _readyInit(self):
		super()._readyInit()
		self.snowballDescriptor = self.ctx.item_book.getDescriptor("Snowball")
		self.connect("dropped", self, "onDropped")



_R.reg("res://gd_core_items/Exclusive/Snowman.gd", Exclusive__Snowman)
_R.reg("Snowman", Exclusive__Snowman)
