# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BrassKnuckles(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/BrassKnuckles.gd"

	def _init_fields(self):
		super()._init_fields()
		self.extraAccuracy = None
		self.battleRageSpeed = None


	def canAffect(self, item):
		return item.canDamage()


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.addCritChancePercent(self.getChance2())
			self.addAccuracy(self.extraAccuracy)
			for item in _iter(self.getAffectedItems()):
				item.addCritChancePercent(self.getChance2())
				if item.isWeapon():
					item.addAccuracy(self.extraAccuracy)
			if self.rollChance():
				self.stun(self.getP_m("dur_stun"), damageRes.event)


	def onPrepare(self):
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


	def onBattleRageStarted(self, _event):
		self.addSpeed(self.battleRageSpeed)


	def onBattleRageEnded(self, _event):
		self.reduceSpeed(self.battleRageSpeed)

	def _readyInit(self):
		super()._readyInit()
		self.extraAccuracy = self.getP2()
		self.battleRageSpeed = _div(self.getP4(), 100.0)


_R.reg("res://gd_core_items/Exclusive/BrassKnuckles.gd", Exclusive__BrassKnuckles)
_R.reg("BrassKnuckles", Exclusive__BrassKnuckles)
