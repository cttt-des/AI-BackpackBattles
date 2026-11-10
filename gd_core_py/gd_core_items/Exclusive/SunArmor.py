# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SunArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SunArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self._heatNeeded = 0
		self._debuffsCleansed = 0

	@property
	def heatNeeded(self):
		return self._heatNeeded
	@heatNeeded.setter
	def heatNeeded(self, v):
		self._heatNeeded = int(v)
	@property
	def debuffsCleansed(self):
		return self._debuffsCleansed
	@debuffsCleansed.setter
	def debuffsCleansed(self, v):
		self._debuffsCleansed = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1) or item.hasType(_H_2)


	def reactToItemTypeChange(self, item):
		if item in self.currentAffectedItems[_H_3]:

			if not item.hasType(_H_1) and item.hasDynamicType(_H_2, self):
				_erase(self.currentAffectedItems[_H_3], item)
				self.onAffectedItemRemoved(item, _H_3)
				return False
		return True


	def onAffectedItemAdded(self, item, color):
		color = int(color)
		if item.hasType(_H_1):
			item.addDynamicType(_H_2, self)


	def onAffectedItemRemoved(self, item, color):
		color = int(color)
		item.removeDynamicType(_H_2, self)


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


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Fire
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
