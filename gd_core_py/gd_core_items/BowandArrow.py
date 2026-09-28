# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BowandArrow(_R.C("res://gd_core_items/Bow.gd")):

	resource_path = "res://gd_core_items/BowandArrow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusDmg = 0
		self.bonusDmgPerHit = 0
		self.maxDmg = 0


	def hasAttackEffect(self):
		return True


	def onPrepare(self):
		self.bonusDmg = 0
		self.setState(0)


	def onWeaponAttacked(self, damageRes):
		if damageRes.hasHit():
			dmgAdded = False
			attackEffectCount = 1 + self.rollDoubleAttackEffect()
			for i in _iter(attackEffectCount):
				if self.bonusDmg < self.maxDmg:
					self.bonusDmg += self.bonusDmgPerHit
					self.addBonusDamage(self.bonusDmgPerHit)
					dmgAdded = True

			if dmgAdded:
				self.setState(self.bonusDmg, False, damageRes.event)


	def onShopEntered(self):
		self.onStateChanged(0)


	def onStateChanged(self, _bonusDmg):
		if _bonusDmg > 0:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.bonusDmgPerHit = self.getP1()
		self.maxDmg = self.getP2()


_R.reg("res://gd_core_items/BowandArrow.gd", BowandArrow)
_R.reg("BowandArrow", BowandArrow)
