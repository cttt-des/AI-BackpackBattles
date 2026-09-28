# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ChromeCube(_R.C("res://gd_core_items/Exclusive/Cube.gd")):

	resource_path = "res://gd_core_items/Exclusive/ChromeCube.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.healthThreshold = None
		self.healReduction = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.hasActivated = False
		self.affectedItem = self.getFirstAffectedItem()
		self.connectForCombat(self.opponent(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.opponent().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True

			if self.affectedItem != None:
				self.advanceAffectedItem()

			self.opponent().reduceHealingEfficiency(self.healReduction)
			self.consume()

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP('healtht'), 100.0) - 0.0001
		self.healReduction = _div(self.getP('healreduction'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ChromeCube.gd", Exclusive__ChromeCube)
_R.reg("ChromeCube", Exclusive__ChromeCube)
