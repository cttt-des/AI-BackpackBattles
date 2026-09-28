# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ThornBow(_R.C("res://gd_core_items/Bow.gd")):

	resource_path = "res://gd_core_items/ThornBow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusCounter = 0
		self.tempBonusDam = 0


	def hasAttackEffect(self):
		return True


	def onPrepare(self):
		self.bonusCounter = 0
		self.setState(self.bonusCounter)


	def onCombatStart(self):
		self.giveSpikes(self.getP1())
		self.activate(None, False)


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			res = self.dealDamage()
			self.activate(res)

			if self.bonusCounter > 0:
				self.reduceBonusDamage(self.tempBonusDam * self.bonusCounter, False)
				self.bonusCounter = 0
				self.setState(self.bonusCounter, False, res.event)


	def onWeaponAttacked(self, damageRes):
		if damageRes.hasHit():
			attackEffectCount = 1 + self.rollDoubleAttackEffect()
			for i in _iter(attackEffectCount):
				if self.character().getSpikes() > 0:
					self.bonusCounter += 1
					self.useSpikes(1, damageRes.event)
					self.addBonusDamage(self.tempBonusDam)
			self.setState(self.bonusCounter, False, damageRes.event)


	def onShopEntered(self):
		self.onStateChanged(0)


	def onStateChanged(self, _bonusCounter):
		if _bonusCounter > 0:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.tempBonusDam = self.getP2()


_R.reg("res://gd_core_items/ThornBow.gd", ThornBow)
_R.reg("ThornBow", ThornBow)
