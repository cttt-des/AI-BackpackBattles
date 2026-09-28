# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class TheLovers(_R.C("res://gd_core_items/Card.gd")):

	resource_path = "res://gd_core_items/TheLovers.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heartParticles = None
		self.healAmp = None
		self.dam = None
		self.regen = None


	def cardSecondaryEffectActive(self):
		return _mod(self.chainPosition, 2) == 0


	def doRevealEffect(self):
		if self.cardSecondaryEffectActive():
			self.character().addHealingEfficiency(self.healAmp)

		self.stealLife(self.dam, _div(self.getP_m('lifesteal'), 100.0))

		if self.cardSecondaryEffectActive():
			self.giveRegeneration(self.regen)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.healAmp = _div(self.getP('healamp'), 100.0)
		self.dam = self.getP("dam")
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/TheLovers.gd", TheLovers)
_R.reg("TheLovers", TheLovers)
