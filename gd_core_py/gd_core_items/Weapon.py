# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Weapon(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Weapon.gd"


	def attack(self, triggerEvent=None):
		res = self.dealDamage(triggerEvent)
		self.activate(res)


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			self.attack()

	def _readyInit(self):
		super()._readyInit()
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Weapon.gd", Weapon)
_R.reg("Weapon", Weapon)
_R.reg("Weapon", Weapon)
