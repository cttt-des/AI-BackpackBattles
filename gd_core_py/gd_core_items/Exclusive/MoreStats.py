# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MoreStats(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MoreStats.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageFactor = None


	def canAffect_global(self, item):
		return item.canBeEmpowered()


	def onCombatStart(self):
		for item in _iter(self.inventory.getItems()):
			if self.canAffect_global(item):
				item.addBonusDamageFactor(self.damageFactor)
		self.giveMaxHealth(round(_div(self.getP_m('maxhealth'), 100.0) * self.character().getMaxHealth()))
		self.activate()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.Low


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		string = None
		if wrapInColor:
			string = self.ctx.util.tr("TOOLTIP_Always Offered").format(
				{"round": None})
		else:
			string = self.ctx.util.tr("TOOLTIP_Always Offered").format(
				{"round": self.descriptor.appearRounds[0]})
		descr += "\n\n" + string
		return descr


	def getSalesMultiplier(self):
		return 0.2

	def _readyInit(self):
		super()._readyInit()
		self.damageFactor = _div(self.getP('dam'), 100.0)


_R.reg("res://gd_core_items/Exclusive/MoreStats.gd", Exclusive__MoreStats)
_R.reg("MoreStats", Exclusive__MoreStats)
