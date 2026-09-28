# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__WolfBadge(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/WolfBadge.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.healthThreshold = None
		self.battleRageSpeed = None
		self.battleRageDamReduction = None


	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		pass

	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.activated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


	def onDamaged(self, _damage, event):
		if not self.activated:
			if self.character().getRelativeHealth() < self.healthThreshold:
				self.activated = True
				self.character().startBattleRage(self, self.getP_m("dur"), event)
				self.activate()


	def onBattleRageStarted(self, _event):
		self.character().changeDamageResistance(self.battleRageDamReduction)
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.battleRageSpeed)


	def onBattleRageEnded(self, _event):
		self.character().changeDamageResistance( - self.battleRageDamReduction)
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.battleRageSpeed)


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 10


	def getRelatedItems(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0) - 0.0001
		self.battleRageSpeed = _div(self.getP3(), 100.0)
		self.battleRageDamReduction = self.getP4()


_R.reg("res://gd_core_items/Exclusive/WolfBadge.gd", Exclusive__WolfBadge)
_R.reg("WolfBadge", Exclusive__WolfBadge)
