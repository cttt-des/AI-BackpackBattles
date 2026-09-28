# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PoisonSpear(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/PoisonSpear.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blockRemoval = None
		self.poison = None
		self.selfPoison = None


	def affectsEmpty(self, color):
		return True


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Nature)


	def onPrepare(self):
		self.blockRemoval = self.getP("blockremoval") * (self.getNumEmptyAffectedCells() + self.getNumAffectedItems())


	def onPreDealDamage_late(self, damageRes):

		self.inflictPoison(self.poison)
		self.selfInflictPoison(self.selfPoison)
		self.removeBlock(self.blockRemoval)

	def _readyInit(self):
		super()._readyInit()
		self.poison = int(self.getP("poison"))
		self.selfPoison = int(self.getP("poison2"))


_R.reg("res://gd_core_items/Exclusive/PoisonSpear.gd", Exclusive__PoisonSpear)
_R.reg("PoisonSpear", Exclusive__PoisonSpear)
