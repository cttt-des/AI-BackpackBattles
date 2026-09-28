# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class VampiricGloves(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/VampiricGloves.gd"

	def _init_fields(self):
		super()._init_fields()
		self.inactiveTexture = None
		self.activationParticles = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.setState(False)


	def doCooldownEffect(self):
		self.setState(True)
		self.giveVampirism(self.getP1())
		bonusSpeed = _div(self.getP2(), 100)
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(bonusSpeed)
		self.onAfterEffectFinished()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			self.updateShadowTexture()
		else:
			self.updateShadowTexture()


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/VampiricGloves.gd", VampiricGloves)
_R.reg("VampiricGloves", VampiricGloves)
