# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Spear_2(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Spear.gd"

	def _init_fields(self):
		super()._init_fields()
		self._totalBlockRemoval = 0
		self.blockRemoval = None

	@property
	def totalBlockRemoval(self):
		return self._totalBlockRemoval
	@totalBlockRemoval.setter
	def totalBlockRemoval(self, v):
		self._totalBlockRemoval = int(v)

	def affectsEmpty(self, color):
		return True


	def canAffect(self, item):
		return False


	def onPrepare(self):
		self.totalBlockRemoval = self.blockRemoval * self.getNumEmptyAffectedCells()


	def onPreDealDamage_late(self, damageRes):

		self.removeBlock(self.totalBlockRemoval)

	def _readyInit(self):
		super()._readyInit()
		self.blockRemoval = self.getP("blockremoval")


_R.reg("res://gd_core_items/Spear.gd", Spear_2)
_R.reg("Spear", Spear_2)
