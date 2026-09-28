# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class AceofSpades(_R.C("res://gd_core_items/Card.gd")):

	resource_path = "res://gd_core_items/AceofSpades.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spadesParticles = None
		self.luck = None
		self.spikes = None


	def cardSecondaryEffectActive(self):
		return _mod(self.chainPosition, 2) == 1


	def doRevealEffect(self):
		self.giveCritTokens(1)

		if self.cardSecondaryEffectActive():
			self.giveLucky(self.luck)
			self.giveSpikes(self.spikes)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core_items/AceofSpades.gd", AceofSpades)
_R.reg("AceofSpades", AceofSpades)
