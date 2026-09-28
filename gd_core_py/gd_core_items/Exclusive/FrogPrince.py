# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FrogPrince(_R.C("res://gd_core_items/Exclusive/Toad.gd")):

	resource_path = "res://gd_core_items/Exclusive/FrogPrince.gd"

	FrogState = EnumDict("FrogState", {"Inactive": 0, "Active": 1, "Used": 2})



	def _init_fields(self):
		super()._init_fields()
		self.frogState = 0
		self.activationParticles = None
		self.buffTimer = None
		self.light = None
		self.blind = None


	def onGainThresholdReached(self, ticks, event):
		self.cleanseBlind(self.blind, event)
		self.heal(ticks * self.getP_m("heal"), event)
		self.miniActivate()


	def onUseThresholdReached(self, ticks, event):
		if self.frogState == self.FrogState.Inactive:
			self.setState(self.FrogState.Active, True)
			self.giveLucky(self.luck, event)
			self.giveMana(self.mana, event)
			invuDur = self.getP_m("dur_1")
			self.character().makeInvulnerable(invuDur, self, event)
			self.buffTimer.start(invuDur)
			self.miniActivate()


	def onPrepare(self):
		super().onPrepare()
		self.setState(self.FrogState.Inactive)


	def buffEnded(self):
		self.setState(self.FrogState.Used, True)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(self.FrogState.Inactive)


	def onStateChanged(self, _frogState):
		if _frogState == self.FrogState.Inactive:
			pass

		elif _frogState == self.FrogState.Active:
			pass

		else:
			pass

		self.frogState = _frogState

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.blind = int(self.getP("blind"))


_R.reg("res://gd_core_items/Exclusive/FrogPrince.gd", Exclusive__FrogPrince)
_R.reg("FrogPrince", Exclusive__FrogPrince)
