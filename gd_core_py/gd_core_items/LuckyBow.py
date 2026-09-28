# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class LuckyBow(_R.C("res://gd_core_items/Bow.gd")):

	resource_path = "res://gd_core_items/LuckyBow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.extraAttack = False


	def onPrepare(self):
		self.setState(False)


	def onCombatStart(self):
		self.giveLucky(self.getP1())
		self.activate(None, False)


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			res = self.dealDamage()
			self.activate(res)
			if self.extraAttack:
				res2 = self.dealDamage(res.event)
				self.activate(res2)
				self.setState(False, False, res2.event)


	def onWeaponAttacked(self, damageRes):
		if damageRes.wasCriticalHit():
			self.setState(True, False, damageRes.event)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _extraAttack):
		if _extraAttack:
			pass
		else:
			pass

		self.extraAttack = _extraAttack

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/LuckyBow.gd", LuckyBow)
_R.reg("LuckyBow", LuckyBow)
