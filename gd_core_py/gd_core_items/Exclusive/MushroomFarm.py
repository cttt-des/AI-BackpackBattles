# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MushroomFarm(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MushroomFarm.gd"

	def _init_fields(self):
		super()._init_fields()
		self.flyAgaricDescriptor = None
		self.doomCapDescriptor = None
		self.mushroomSpeed = None
		self.mushroomsNeeded = None
		self.activeLight = None


	def onItemAdded(self, item):
		super().onItemAdded(item)
		if self.isActive():
			pass


	def onItemRemoved(self, item):
		super().onItemRemoved(item)
		if not self.isActive():
			pass


	def onRemoveFromInventory(self):
		pass


	def canAffect(self, item):
		return item.isA(self.flyAgaricDescriptor) or item.isA(self.doomCapDescriptor)


	def isActive(self):
		numMushrooms = self.ctx.item_book.countPlacedItemsInInventoryOfType(self.flyAgaricDescriptor)
		numMushrooms += self.ctx.item_book.countPlacedItemsInInventoryOfType(self.doomCapDescriptor)
		return numMushrooms >= self.mushroomsNeeded


	def onShopEntered(self):
		pass

	def onCombatStart(self):





		for mushroom in _iter(self.getAffectedItems()):
			mushroom.addSpeed(self.mushroomSpeed)

		self.activate()


	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.flyAgaricDescriptor = self.ctx.item_book.getDescriptor("Fly Agaric")
		self.doomCapDescriptor = self.ctx.item_book.getDescriptor("Doom Cap")
		self.mushroomSpeed = _div(self.getP('speed'), 100.0)
		self.mushroomsNeeded = self.getP("num")


_R.reg("res://gd_core_items/Exclusive/MushroomFarm.gd", Exclusive__MushroomFarm)
_R.reg("MushroomFarm", Exclusive__MushroomFarm)
