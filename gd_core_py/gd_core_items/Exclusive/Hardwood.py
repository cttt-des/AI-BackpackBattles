# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Hardwood(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Hardwood.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasCommonMeleeWeapon = False
		self.numCommons = 0
		self.commonDam = None


	def canAffect(self, item):
		return item.getRarity() == _R.C("CoreConst").Rarity.Common


	def isMeleeWeapon(self, item):
		return item.canBeEmpowered() and item.descriptor.isMeleeWeapon()


	def onPrepare(self):
		self.numCommons = 0
		for item in _iter(self.getAffectedItems()):
			self.numCommons += 1
			if self.isMeleeWeapon(item):
				item.addBonusDamageFactor(self.commonDam)


	def onCombatStart(self):
		if self.numCommons > 0:
			self.giveBlock(self.getBlock() * self.numCommons)

		self.activate()


	def onItemsCounted(self):
		pass

	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.commonDam = _div(self.getP('dam'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Hardwood.gd", Exclusive__Hardwood)
_R.reg("Hardwood", Exclusive__Hardwood)
