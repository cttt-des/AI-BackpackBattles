# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FortunasKiss(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/FortunasKiss.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stackTypes = []
		self.bonusChance = None
		self.luckNeeded = None


	def canAffect(self, item):
		return item.canModifyChance()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusChance(self.bonusChance)


	def doCooldownEffect(self):
		if self.character().getLucky() >= self.luckNeeded:
			self.giveRandomBuffs(1, None, self.stackTypes)
		else:
			self.giveLucky(1)
		self.activate()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 5

	def _readyInit(self):
		super()._readyInit()
		self.bonusChance = self.getP("chance")
		self.luckNeeded = int(self.getP("luckt"))
		self.stackTypes = _R.C("CoreConst").getBuffs()
		_erase(self.stackTypes, _R.C("CoreConst").EventType.Lucky)



_R.reg("res://gd_core_items/Exclusive/FortunasKiss.gd", Exclusive__FortunasKiss)
_R.reg("FortunasKiss", Exclusive__FortunasKiss)
