# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class TheFool(_R.C("res://gd_core_items/Card.gd")):

	resource_path = "res://gd_core_items/TheFool.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activationParticles = None


	def cardSecondaryEffectActive(self):
		return self.chainPosition == 0


	def doRevealEffect(self):
		bonusSpeed = _div(self.getP('revealspeed'), 100.0)
		for card in _iter(self.deck.cards):
			card.addSpeed(bonusSpeed)

		if self.cardSecondaryEffectActive():
			self.giveEmpower(self.getP("empower"))

		self.activate()


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/TheFool.gd", TheFool)
_R.reg("TheFool", TheFool)
