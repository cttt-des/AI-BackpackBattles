# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ArtifactStoneHeat(_R.C("res://gd_core_items/Stone.gd")):

	resource_path = "res://gd_core_items/ArtifactStoneHeat.gd"

	def _init_fields(self):
		super()._init_fields()
		self.dmgBonusActive = False
		self.activationParticles = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")
		self.dmgBonusActive = False


	def onHeatChanged(self, amount, event):
		if not self.dmgBonusActive and amount > 0:
			if self.character().getHeat() >= self.getP2():
				self.dmgBonusActive = True
				for weapon in _iter(self.getAffectedItems()):
					weapon.addBonusDamage(self.getP3())


	def onCombatEnd(self):
		pass


	def preHit(self):
		self.giveHeat(self.getP1())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/ArtifactStoneHeat.gd", ArtifactStoneHeat)
_R.reg("ArtifactStoneHeat", ArtifactStoneHeat)
