# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ForestDragon(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/ForestDragon.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regen = None
		self.luck = None
		self.damPerRegen = None
		self.speedPerNature = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Nature)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")
		self.addSpeed(self.speedPerNature * self.getNumAffectedItems())


	def onRegenChanged(self, amount, event):
		self.changeVaryingDamage(amount * self.damPerRegen)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.giveRegeneration(self.regen)
			self.giveLucky(self.luck)

	def _readyInit(self):
		super()._readyInit()
		self.regen = int(self.getP("regen"))
		self.luck = int(self.getP("luck"))
		self.damPerRegen = self.getP("dam")
		self.speedPerNature = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ForestDragon.gd", Exclusive__ForestDragon)
_R.reg("ForestDragon", Exclusive__ForestDragon)
