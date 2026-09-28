# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Hypercube(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Hypercube.gd"


	def onDropped(self, dropRes):
		if (self.wasAddedToInventory(dropRes) or 
			dropRes == self.DropResult.AddedToStorageBox):

			self.prepareReplacement()
			self.ctx.defer(self, "replaceWithCubes", [dropRes])


	def replaceWithCubes(self, dropResult):
		pass

	def getTextureSize(self):
		return Vector2.ZERO

	def _readyInit(self):
		super()._readyInit()
		self.connect("dropped", self, "onDropped")



_R.reg("res://gd_core_items/Exclusive/Hypercube.gd", Exclusive__Hypercube)
_R.reg("Hypercube", Exclusive__Hypercube)
