# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Broom(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Broom.gd"

	def _init_fields(self):
		super()._init_fields()
		self.broomBonusDam = 0
		self.onMissReadyTime = 0.0
		self.bonusDamPerMiss = None


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_attacked", "onAttacked")


	def onAttacked(self, damageRes):
		if not damageRes.hasHit():
			self.addBonusDamage(self.bonusDamPerMiss)
			self.broomBonusDam += self.bonusDamPerMiss





	def attack(self, event=None):
		super().attack(event)
		if self.broomBonusDam != 0:
			self.reduceBonusDamage(self.broomBonusDam, False)
			self.broomBonusDam = 0



	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if self.rollChance():
				self.inflictBlind(1, damageRes.event)


	def onShopEntered(self):
		self.broomBonusDam = 0

	def _readyInit(self):
		super()._readyInit()
		self.bonusDamPerMiss = int(self.getP1())


_R.reg("res://gd_core_items/Broom.gd", Broom)
_R.reg("Broom", Broom)
