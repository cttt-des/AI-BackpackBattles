# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SunArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SunArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heatNeeded = 0
		self.debuffsCleansed = 0


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Fire) or item.hasType(_R.C("CoreConst").Type.Holy)


	def reactToItemTypeChange(self, item):
		if item in self.currentAffectedItems[_R.C("CoreConst").Affected.Primary]:

			if not item.hasType(_R.C("CoreConst").Type.Fire) and item.hasDynamicType(_R.C("CoreConst").Type.Holy, self):
				_erase(self.currentAffectedItems[_R.C("CoreConst").Affected.Primary], item)
				self.onAffectedItemRemoved(item, _R.C("CoreConst").Affected.Primary)
				return False
		return True


	def onAffectedItemAdded(self, item, color):
		if item.hasType(_R.C("CoreConst").Type.Fire):
			item.addDynamicType(_R.C("CoreConst").Type.Holy, self)


	def onAffectedItemRemoved(self, item, color):
		item.removeDynamicType(_R.C("CoreConst").Type.Holy, self)


	def doCooldownEffect(self):
		if self.character().getHeat() >= self.heatNeeded:
			event = self.useHeat(self.heatNeeded)
			self.heal(self.getP_m("heal"), event)
			self.cleanseRandomDebuffs(self.debuffsCleansed, event)
			self.ctx.bus.emitSignal(self, "used_heat", [event])
		self.activate()


	def onCombatStart(self):
		self.giveBlock()
		self.giveHeat(self.getNumAffectedItems() * self.getP1())
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = self.getP2()
		self.debuffsCleansed = self.getP4()


_R.reg("res://gd_core_items/Exclusive/SunArmor.gd", Exclusive__SunArmor)
_R.reg("SunArmor", Exclusive__SunArmor)
