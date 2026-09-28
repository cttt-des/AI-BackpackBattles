# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class PlatinCustomerCard(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/PlatinCustomerCard.gd"


	def canAffect(self, item):
		return item.getRarity() >= _R.C("CoreConst").Rarity.Legendary


	def onPreCombatStart(self):
		self.giveReflectStacks(self.getNumAffectedItems() * self.getP2())
		self.activate()


	def onCombatStart(self):

		pass


	def onCalcTradeChance(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/PlatinCustomerCard.gd", PlatinCustomerCard)
_R.reg("PlatinCustomerCard", PlatinCustomerCard)
