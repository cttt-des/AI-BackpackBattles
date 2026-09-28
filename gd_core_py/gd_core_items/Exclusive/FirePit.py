# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FirePit(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/FirePit.gd"


	def canApplyEffect(self, toItem):
		return toItem.hasType(_R.C("CoreConst").Type.Fire)


	def onPreCombatStart(self):
		self.giveMaxHealth(self.getP_m("maxhealth") * self.getNumAffectedInside_type(_R.C("CoreConst").Type.Fire))
		self.activate()


	def onShopEntered(self):
		pass

	def getBagMultiplicity(self, forItem):
		return forItem.getTypeMultiplicity(_R.C("CoreConst").Type.Fire)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/FirePit.gd", Exclusive__FirePit)
_R.reg("FirePit", Exclusive__FirePit)
