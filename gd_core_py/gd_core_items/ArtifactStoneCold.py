# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ArtifactStoneCold(_R.C("res://gd_core_items/Stone.gd")):

	resource_path = "res://gd_core_items/ArtifactStoneCold.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		for weapon in _iter(self.getAffectedItems()):
			self.connectForCombat(weapon, "attacked", "onAffectedWeaponAttacked")


	def onAffectedWeaponAttacked(self, damageRes):
		if damageRes.hasHit():
			self.inflictCold(self.getP2())
			self.miniActivate()


	def preHit(self):
		self.inflictCold(self.getP1())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/ArtifactStoneCold.gd", ArtifactStoneCold)
_R.reg("ArtifactStoneCold", ArtifactStoneCold)
