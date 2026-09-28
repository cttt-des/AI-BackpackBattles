# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ScholarBag(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/ScholarBag.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana = None


	def canApplyEffect(self, toItem):
		return toItem.gainsStack(_R.C("CoreConst").Stack.Mana)


	def onPrepare(self):
		for item in _iter(self.getAffectedItemsInside()):
			item.changeAmplificiationChancePercent(_R.C("CoreConst").EventType.Mana, self.getChance())

		self.character().changeProtectionChance(_R.C("CoreConst").EventType.Mana, self.getChance2())


	def onCombatStart(self):
		self.giveMana(self.mana)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Exclusive/ScholarBag.gd", Exclusive__ScholarBag)
_R.reg("ScholarBag", Exclusive__ScholarBag)
