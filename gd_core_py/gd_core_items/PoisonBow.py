# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class PoisonBow(_R.C("res://gd_core_items/Bow.gd")):

	resource_path = "res://gd_core_items/PoisonBow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageAcc = 0
		self.damagePerPoison = 0


	def hasAttackEffect(self):
		return True


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_poison_changed", "onOpponentPoisonChanged")
		self.damageAcc = 0


	def onWeaponAttacked(self, damageRes):
		if damageRes.hasHit():

			attackEffectCount = 1 + self.rollDoubleAttackEffect()
			for i in _iter(attackEffectCount):
				self.damageAcc += damageRes.damage

			self.setState(self.damageAcc, False, damageRes.event)


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:

			poisonStacks = _div(self.damageAcc, self.damagePerPoison)
			poisonEvent = self.inflictPoison(poisonStacks)
			self.damageAcc %= self.damagePerPoison
			self.setState(self.damageAcc, False, poisonEvent)

			res = self.dealDamage()
			self.activate(res)


	def onOpponentPoisonChanged(self, amount, _event):
		self.changeVaryingDamage(amount * self.getP2())


	def onShopEntered(self):
		self.onStateChanged(0)


	def onStateChanged(self, _damageAcc):
		if _damageAcc < self.damagePerPoison:
			pass
		else:
			poisonStacks = _div(_damageAcc, self.damagePerPoison)

	def _readyInit(self):
		super()._readyInit()
		self.damagePerPoison = self.getP1()


_R.reg("res://gd_core_items/PoisonBow.gd", PoisonBow)
_R.reg("PoisonBow", PoisonBow)
