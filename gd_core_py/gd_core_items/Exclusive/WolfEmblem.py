# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__WolfEmblem(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/WolfEmblem.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blockThreshold = None
		self.empower = None

	puppies = ["Courage Puppy", "Wisdom Puppy", "Power Puppy"]

	def canAffect(self, item):
		return item.canBeEmpowered()


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Pet)


	def onPrepare(self):
		bonusCritChance = self.getChance()
		bonusCritChance += len(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)) * self.getChance2()

		for item in _iter(self.getAffectedItems()):
			item.changeCritChancePercent(bonusCritChance)


	def doCooldownEffect(self):
		curBlock = self.character().getBlock()

		if curBlock >= self.blockThreshold:
			self.giveEmpower(self.empower)
		else:
			self.giveBlock()

		self.activate()


	def getGatedDescriptor(self, rarity):
		return self.ctx.item_book.getDescriptor(self.ctx.util.pickRandomElement(self.puppies))

	def _readyInit(self):
		super()._readyInit()
		self.blockThreshold = self.getP("blockt")
		self.empower = self.getP("empower")


_R.reg("res://gd_core_items/Exclusive/WolfEmblem.gd", Exclusive__WolfEmblem)
_R.reg("WolfEmblem", Exclusive__WolfEmblem)
