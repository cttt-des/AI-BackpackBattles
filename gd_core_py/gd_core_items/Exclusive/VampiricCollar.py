# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__VampiricCollar(_R.C("res://gd_core_items/RangerCollar.gd")):

	resource_path = "res://gd_core_items/Exclusive/VampiricCollar.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItems_dict = {}
		self.maxLifesteal = None


	def canAffect(self, item):
		return item.canDamage()


	def onPrepare(self):
		if not (not self.affectedItems):
			self.connectForCombat(self.character(), "character_vampirism_changed", "onVampirismChanged")
			self.connectForCombat(self.opponent(), "character_attacked", "onOpponentAttacked")

		self.affectedItems_dict = self.ctx.util.arrayAsIndexDict(self.affectedItems)


	def onVampirismChanged(self, amount, event):
		for item in _iter(self.affectedItems):
			item.changeCritChancePercent(amount * self.getChance())


	def onOpponentAttacked(self, damageRes):
		if (damageRes.getDamage() > 0 and 
			damageRes.damageSource.canApplyLifesteal() and 
			damageRes.damageSource.origin in self.affectedItems_dict):

			lifestealFactor = _div(self.getP_m('lifesteal'), 100.0) * self.character().getLucky()
			if lifestealFactor > 0:
				lifestealFactor = min(lifestealFactor, self.maxLifesteal)
				lifesteal = max(1, damageRes.damage * lifestealFactor)
				self.heal(lifesteal, damageRes.event)

	def _readyInit(self):
		super()._readyInit()
		self.maxLifesteal = _div(self.getP('max'), 100.0)


_R.reg("res://gd_core_items/Exclusive/VampiricCollar.gd", Exclusive__VampiricCollar)
_R.reg("VampiricCollar", Exclusive__VampiricCollar)
