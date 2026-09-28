# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CarrotGoobert(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/CarrotGoobert.gd"

	def _init_fields(self):
		super()._init_fields()
		self.empower = None
		self.particleTimer = None
		self.activationParticles = None


	def onPrepare(self):
		self.setState(False)


	def doCooldownEffect(self):
		self.setState(True, True)
		self.cleanseRandomDebuffs(self.getP2())
		duration = self.getP_m("dur")
		self.giveStacksTemporary(self.character(), _R.C("CoreConst").EventType.Empower, 
			self.empower, duration)
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
		self.empower = self.getP3()
		self.particleTimer = self.newItemTimer("ParticleTimer", "onParticleTimeout", False)


_R.reg("res://gd_core_items/CarrotGoobert.gd", CarrotGoobert)
_R.reg("CarrotGoobert", CarrotGoobert)
