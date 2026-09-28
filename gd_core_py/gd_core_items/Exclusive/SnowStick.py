# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SnowStick(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/SnowStick.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cold = None
		self.selfCold = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.inflictCold(self.cold)
			self.giveStacks(self.character(), _R.C("CoreConst").EventType.Cold, self.selfCold)

	def _readyInit(self):
		super()._readyInit()
		self.cold = int(self.getP("cold"))
		self.selfCold = int(self.getP("cold2"))


_R.reg("res://gd_core_items/Exclusive/SnowStick.gd", Exclusive__SnowStick)
_R.reg("SnowStick", Exclusive__SnowStick)
