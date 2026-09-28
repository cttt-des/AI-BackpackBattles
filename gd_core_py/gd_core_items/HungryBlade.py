# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HungryBlade(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/HungryBlade.gd"

	def _init_fields(self):
		super()._init_fields()
		self.vampirism = None
		self.regenNeeded = None
		self.vampirismForRegen = None


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_vampirism_changed", "onVampirismChanged")


	def onCombatStart(self):
		self.giveVampirism(self.vampirism)
		self.activate(None, False, False, self.ActivationAni.Jump)


	def onVampirismChanged(self, amount, _event):
		self.addMaxDamage(amount)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			numRegen = self.character().getRegeneration()
			if numRegen >= self.regenNeeded:
				event = self.useRegeneration(self.regenNeeded)
				self.giveVampirism(self.vampirismForRegen, event)


	def _readyInit(self):
		super()._readyInit()
		self.vampirism = int(self.getP1())
		self.regenNeeded = int(self.getP2())
		self.vampirismForRegen = int(self.getP3())


_R.reg("res://gd_core_items/HungryBlade.gd", HungryBlade)
_R.reg("HungryBlade", HungryBlade)
