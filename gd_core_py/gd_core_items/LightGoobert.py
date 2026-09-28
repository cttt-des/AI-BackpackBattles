# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class LightGoobert(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/LightGoobert.gd"

	def _init_fields(self):
		super()._init_fields()
		self.particleTimer = None
		self.activationParticles = None
		self.blindAmount = None


	def onPrepare(self):
		self.setState(False)


	def doCooldownEffect(self):
		self.setState(True, True)
		self.heal()
		duration = self.getP_m("dur_blind")
		self.giveStacksTemporary(self.opponent(), _R.C("CoreConst").EventType.Blind, 
			self.blindAmount, duration)
		self.particleTimer.stop()
		self.particleTimer.start(duration)


	def onCombatEnd(self):
		self.particleTimer.stop()


	def onParticleTimeout(self):
		self.setState(False)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass


	def _readyInit(self):
		super()._readyInit()
		self.particleTimer = self.newItemTimer("ParticleTimer", "onParticleTimeout", False)
		self.blindAmount = self.getP3()


_R.reg("res://gd_core_items/LightGoobert.gd", LightGoobert)
_R.reg("LightGoobert", LightGoobert)
