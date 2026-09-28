# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Flute(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Flute.gd"

	def _init_fields(self):
		super()._init_fields()
		self.options = []


	def canAffect(self, item):
		return True


	def onPrepare(self):
		self.addSpeed(_div(self.getP3(), 100.0) * self.getNumAffectedItems())
		self.options = [0, 1, 2]


	def doCooldownEffect(self):
		rng = self.ctx.util.pickRandomElement(self.options)
		if rng == 0:
			self.giveBlock()
		elif rng == 1:
			self.giveStamina(self.getP1())
		else:
			self.giveLucky(self.getP2())

		self.activate()

		self.options = [0, 1, 2]
		_erase(self.options, rng)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Flute.gd", Flute)
_R.reg("Flute", Flute)
