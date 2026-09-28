# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BerserkerBag(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/BerserkerBag.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.healthThreshold = None
		self.battleRageSpeed = None
		self.damageResistance = None


	def canApplyEffect(self, toItem):
		return toItem.hasCooldown()


	def onPrepare(self):
		self.activated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


	def onDamaged(self, _damage, event):
		if not self.activated:
			if self.character().getRelativeHealth() < self.healthThreshold:
				self.activated = True
				self.character().startBattleRage(self, self.getP_m("dur_rage"), event)
				self.activate()


	def onBattleRageStarted(self, _event):
		self.character().changeDamageResistance(self.damageResistance)
		for item in _iter(self.getItemsInside()):
			if self.canApplyEffect(item):
				item.addSpeed(self.battleRageSpeed)


	def onBattleRageEnded(self, _event):
		self.character().changeDamageResistance( - self.damageResistance)
		for item in _iter(self.getItemsInside()):
			if self.canApplyEffect(item):
				item.reduceSpeed(self.battleRageSpeed)


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 10

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP('healtht'), 100.0) - 0.0001
		self.battleRageSpeed = _div(self.getP('speed_rage'), 100.0)
		self.damageResistance = self.getP("damresistance")


_R.reg("res://gd_core_items/Exclusive/BerserkerBag.gd", Exclusive__BerserkerBag)
_R.reg("BerserkerBag", Exclusive__BerserkerBag)
