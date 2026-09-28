# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__GoldCube(_R.C("res://gd_core_items/Exclusive/Cube.gd")):

	resource_path = "res://gd_core_items/Exclusive/GoldCube.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.healthThreshold = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.hasActivated = False
		self.affectedItem = self.getFirstAffectedItem()
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True

			if self.affectedItem != None:
				self.advanceAffectedItem()

			self.heal(self.getP_m("heal") + self.getP_m("heal_regen") * self.character().getRegeneration())
			self.consume()

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP('healtht'), 100.0) - 0.0001


_R.reg("res://gd_core_items/Exclusive/GoldCube.gd", Exclusive__GoldCube)
_R.reg("GoldCube", Exclusive__GoldCube)
