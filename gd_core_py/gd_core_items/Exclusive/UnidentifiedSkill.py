# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__UnidentifiedSkill(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/UnidentifiedSkill.gd"

	def _init_fields(self):
		super()._init_fields()
		self.skillPool = None


	def getSkillPool(self):
		pass

	def onDropped(self, dropRes):
		if (self.wasAddedToInventory(dropRes) or 
			dropRes == self.DropResult.AddedToStorageBox):

			self.prepareReplacement()
			skill = _pick_random(self.skillPool)
			self.ctx.defer(self, "identifySkill", [dropRes, skill])


	def identifySkill(self, dropResult, skillDescriptor):
		pass

	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		string = None
		if wrapInColor:
			string = self.ctx.util.tr("TOOLTIP_Always Offered2").format(
				{"round1": None, 
					"round2": None})
		else:
			string = self.ctx.util.tr("TOOLTIP_Always Offered2").format(
				{"round1": self.descriptor.appearRounds[0], 
					"round2": self.descriptor.appearRounds[1]})
		descr += "\n\n" + string
		return descr


	def getRelatedItems(self):
		pass

	def getRelatedItemColumns(self):
		return 6


	def getRelatedItemHeight(self):
		return 80

	def _readyInit(self):
		super()._readyInit()
		self.connect("dropped", self, "onDropped")
		if self.ownerType == _R.C("CoreConst").Owner.Shop:
			self.ctx.defer(self, "getSkillPool", [])



_R.reg("res://gd_core_items/Exclusive/UnidentifiedSkill.gd", Exclusive__UnidentifiedSkill)
_R.reg("UnidentifiedSkill", Exclusive__UnidentifiedSkill)
