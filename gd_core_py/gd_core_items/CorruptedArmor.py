# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CorruptedArmor_2(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/CorruptedArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self._movedDebuffs = 0

	@property
	def movedDebuffs(self):
		return self._movedDebuffs
	@movedDebuffs.setter
	def movedDebuffs(self, v):
		self._movedDebuffs = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1) or item.hasType(_H_3)



	def reactToItemTypeChange(self, item):
		if item in self.currentAffectedItems[_H_4]:

			if not item.hasType(_H_3) and item.hasDynamicType(_H_1, self):
				_erase(self.currentAffectedItems[_H_4], item)
				self.onAffectedItemRemoved(item, _H_4)
				return False
		return True


	def onAffectedItemAdded(self, item, color):
		color = int(color)
		if item.hasType(_H_3) and not item.hasType(_H_1):
			item.addDynamicType(_H_1, self)


	def onAffectedItemRemoved(self, item, color):
		color = int(color)
		item.removeDynamicType(_H_1, self)


	def onCombatStart(self):
		self.giveBlock()
		debuffProtectionChance = self.getChance() * self.getNumAffectedItems()
		self.opponent().changeDebuffProtectionChance(debuffProtectionChance)
		self.activate()


	def doCooldownEffect(self):
		cleansedDebuffs = self.pickRandomStacks(_H_2.getDebuffs(), self.movedDebuffs, self.character())

		for debuff in (cleansedDebuffs if cleansedDebuffs.__class__ is list else _iter(cleansedDebuffs)):
			event = self.character().loseStacks(debuff, cleansedDebuffs[debuff], self)
			if event:
				actuallyCleansed = - event.getAmount()
				self.giveStacks(self.opponent(), debuff, actuallyCleansed, event)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.movedDebuffs = self.getP1()


_R.reg("res://gd_core_items/CorruptedArmor.gd", CorruptedArmor_2)
_R.reg("CorruptedArmor", CorruptedArmor_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
_H_2 = _R.C("CoreConst")
try:
    _H_3 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
