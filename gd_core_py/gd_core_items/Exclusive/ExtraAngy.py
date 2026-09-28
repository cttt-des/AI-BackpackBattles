# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ExtraAngy(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ExtraAngy.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.battleRageDur = 0.0


	def onPrepare(self):
		self.activated = False

		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


	def preCombatStart(self):
		super().preCombatStart()
		self.deactivateCooldown()


	def onBattleRageStarted(self, event):
		if not self.activated:
			self.battleRageDur = event.getParam("duration", 0)


	def onBattleRageEnded(self, _event):
		if not self.activated:
			self.activated = True

			self.activateCooldown()


	def doCooldownEffect(self):
		dur = _div(self.battleRageDur * self.getP_m('dur'), 100.0)
		self.character().startBattleRage(self, dur, None, False)
		self.onAfterEffectFinished()


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ExtraAngy.gd", Exclusive__ExtraAngy)
_R.reg("ExtraAngy", Exclusive__ExtraAngy)
