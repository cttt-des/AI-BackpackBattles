# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CritwoodStaff(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/CritwoodStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffActive = False
		self.activationParticles = None
		self.critTimer = None
		self.manaCost = None
		self.tempDamBonus = None


	def onPrepare(self):
		self.setState(False)


	def onPreDealDamage_early(self, damageRes):
		if self.character().getMana() >= self.manaCost:
			if not self.buffActive:
				self.setState(True, True)
				for item in _iter(self.inventory.getItems()):
					item.addCritChancePercent(100)

			self.useMana(self.manaCost)
			damageRes.damage += self.tempDamBonus
			critBuffDur = self.getP_m("dur")
			self.ctx.util.changeTimer(self.critTimer, critBuffDur)


	def buffEnded(self):
		for item in _iter(self.inventory.getItems()):
			item.reduceCritChancePercent(100)
		self.setState(False)


	def onCombatEnd(self):
		self.critTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass

		self.buffActive = active

	def _readyInit(self):
		super()._readyInit()
		self.critTimer = self.newItemTimer("CritBuffTimer", "buffEnded", False)
		self.manaCost = self.getP1()
		self.tempDamBonus = self.getP2()


_R.reg("res://gd_core_items/CritwoodStaff.gd", CritwoodStaff)
_R.reg("CritwoodStaff", CritwoodStaff)
