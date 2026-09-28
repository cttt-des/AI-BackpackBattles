# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CorruptedArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/CorruptedArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.movedDebuffs = 0


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Dark) or item.hasType(_R.C("CoreConst").Type.Holy)



	def reactToItemTypeChange(self, item):
		if item in self.currentAffectedItems[_R.C("CoreConst").Affected.Primary]:

			if not item.hasType(_R.C("CoreConst").Type.Holy) and item.hasDynamicType(_R.C("CoreConst").Type.Dark, self):
				_erase(self.currentAffectedItems[_R.C("CoreConst").Affected.Primary], item)
				self.onAffectedItemRemoved(item, _R.C("CoreConst").Affected.Primary)
				return False
		return True


	def onAffectedItemAdded(self, item, color):
		if item.hasType(_R.C("CoreConst").Type.Holy) and not item.hasType(_R.C("CoreConst").Type.Dark):
			item.addDynamicType(_R.C("CoreConst").Type.Dark, self)


	def onAffectedItemRemoved(self, item, color):
		item.removeDynamicType(_R.C("CoreConst").Type.Dark, self)


	def onCombatStart(self):
		self.giveBlock()
		debuffProtectionChance = self.getChance() * self.getNumAffectedItems()
		self.opponent().changeDebuffProtectionChance(debuffProtectionChance)
		self.activate()


	def doCooldownEffect(self):
		cleansedDebuffs = self.pickRandomStacks(_R.C("CoreConst").getDebuffs(), self.movedDebuffs, self.character())

		for debuff in _iter(cleansedDebuffs):
			event = self.character().loseStacks(debuff, cleansedDebuffs[debuff], self)
			if event:
				actuallyCleansed = - event.getAmount()
				self.giveStacks(self.opponent(), debuff, actuallyCleansed, event)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.movedDebuffs = self.getP1()


_R.reg("res://gd_core_items/CorruptedArmor.gd", CorruptedArmor)
_R.reg("CorruptedArmor", CorruptedArmor)
