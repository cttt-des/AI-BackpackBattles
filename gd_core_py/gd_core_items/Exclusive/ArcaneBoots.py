# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ArcaneBoots(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ArcaneBoots.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.speedTimer = None
		self.healthThreshold = None
		self.manaNeeded = None
		self.luck = None
		self.empower = None
		self.bonusSpeed = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.hasActivated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			if self.character().getMana() >= self.manaNeeded:
				self.hasActivated = True
				event2 = self.useMana(self.manaNeeded)
				self.giveLucky(self.luck, event2)
				self.giveEmpower(self.empower, event2)
				self.giveBlock(self.getBlock(), True, event2)

				for item in _iter(self.getAffectedItems()):
					item.addSpeed(self.bonusSpeed)

				self.speedTimer.start(self.getP_m("dur_speed"))

				self.consume()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 2


	def onSpeedTimerTimeout(self):
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.bonusSpeed)


	def onCombatEnd(self):
		self.speedTimer.stop()

	def _readyInit(self):
		super()._readyInit()
		self.speedTimer = self.newItemTimer("SpeedTimer", "onSpeedTimerTimeout", False)
		self.healthThreshold = _div(self.getP('healtht'), 100.0) - 0.0001
		self.manaNeeded = int(self.getP("manat"))
		self.luck = int(self.getP("luck"))
		self.empower = int(self.getP("empower"))
		self.bonusSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ArcaneBoots.gd", Exclusive__ArcaneBoots)
_R.reg("ArcaneBoots", Exclusive__ArcaneBoots)
