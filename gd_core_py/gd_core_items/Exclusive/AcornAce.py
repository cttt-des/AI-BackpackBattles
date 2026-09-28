# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AcornAce(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AcornAce.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedDescriptors = None
		self.boostedCollars = 0
		self.collarDescriptors = None
		self.acornCollarDescriptor = None
		self.critwoodStaffDescriptor = None
		self.staminaReduction = None


	def getData(self):
		return self.boostedCollars


	def setData(self, data):
		if data != None:
			self.boostedCollars = data


	def onBought(self):
		self.boostedCollars = 1


	def canAffect_global(self, item):
		return item.descriptor in self.affectedDescriptors


	def onItemInstantiated(self, item):
		if (self.placed and 
			isinstance(item, _R.C("RangerCollar")) and 
			
			item.isOwnable()):
				item.activateExtendedAffectedCells()


	def onAddToInventory(self):
		self.ctx.defer(self, "onAddToInventory_deferred", [])


	def onAddToInventory_deferred(self):
		pass

	def onRemoveFromInventory(self):
		self.ctx.defer(self, "onRemoveFromInventory_deferred", [])


	def onRemoveFromInventory_deferred(self):
		pass

	def onPrepare(self):
		for staff in _iter(self.getAllInInventoryOfType(self.critwoodStaffDescriptor)):
			staff.changeStaminaFactor(self.staminaReduction)



	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.acornCollarDescriptor:
			self.boostedCollars -= 1

	def _readyInit(self):
		super()._readyInit()
		self.collarDescriptors = [
		self.ctx.item_book.getDescriptor("Acorn Collar"), 
		self.ctx.item_book.getDescriptor("Magic Collar"), 
		self.ctx.item_book.getDescriptor("Holy Collar"), 
		self.ctx.item_book.getDescriptor("Vampiric Collar")
	]
		self.acornCollarDescriptor = self.collarDescriptors[0]
		self.critwoodStaffDescriptor = self.ctx.item_book.getDescriptor("Critwood Staff")
		self.staminaReduction = - self.getP("stamina2")
		self.affectedDescriptors = self.ctx.util.arrayAsIndexDict(self.collarDescriptors)
		self.affectedDescriptors[self.critwoodStaffDescriptor] = 4



_R.reg("res://gd_core_items/Exclusive/AcornAce.gd", Exclusive__AcornAce)
_R.reg("AcornAce", Exclusive__AcornAce)
