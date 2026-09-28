# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Fanfare(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Fanfare.gd"

	def _init_fields(self):
		super()._init_fields()
		self.options = []


	def canAffect(self, item):
		return True

















	def onPrepare(self):
		self.addSpeed(_div(self.getP5(), 100.0) * self.getNumAffectedItems())
		self.options = [0, 1, 2]


	def doCooldownEffect(self):
		rng = self.ctx.util.pickRandomElement(self.options)
		if rng == 0:
			self.giveEmpower(self.getP1())
		elif rng == 1:
			self.giveMana(self.getP2())
			self.removeMana(self.getP3())
		else:
			self.drainStamina(self.getP4())

		self.activate()

		self.options = [0, 1, 2]
		_erase(self.options, rng)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Fanfare.gd", Fanfare)
_R.reg("Fanfare", Fanfare)
