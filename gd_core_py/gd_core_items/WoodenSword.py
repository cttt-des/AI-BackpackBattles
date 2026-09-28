# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class WoodenSword(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/WoodenSword.gd"


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			res = self.dealDamage()
			self.activate(res)

	def _readyInit(self):
		super()._readyInit()
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/WoodenSword.gd", WoodenSword)
_R.reg("WoodenSword", WoodenSword)
