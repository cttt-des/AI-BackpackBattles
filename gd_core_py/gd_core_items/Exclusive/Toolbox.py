# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Toolbox(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/Toolbox.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedReduction = None
		self.damBonusFactor = None


	def canLockBag(self):
		return True


	def canApplyEffect(self, toItem):
		return toItem.canBeEmpowered()


	def onPrepare(self):


		self.connectForCombat(self.opponent(), "character_attacked", "onOpponentDamaged")


	def onCombatStart(self):
		for item in _iter(self.getItemsInside()):
			if self.canApplyEffect(item):
				item.reduceSpeed(self.speedReduction)
				item.addBonusDamageFactor(self.damBonusFactor)


	def onOpponentDamaged(self, damageRes):
		if self.character().isBattleRaging():
			if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
				self.heal(ceil(_div(self.getP_m('lifesteal'), 100.0) * damageRes.damage), damageRes.event)








	def doCooldownEffect(self):
		self.character().startBattleRage(self, self.getP_m("dur_rage"))
		self.onAfterEffectFinished()

	def _readyInit(self):
		super()._readyInit()
		self.speedReduction = _div(self.getP('speedreduction'), 100.0)
		self.damBonusFactor = _div(self.getP('dambonus'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Toolbox.gd", Exclusive__Toolbox)
_R.reg("Toolbox", Exclusive__Toolbox)
