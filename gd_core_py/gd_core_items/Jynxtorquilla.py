# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Jynxtorquilla(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Jynxtorquilla.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numActivations = 0
		self.speedBonus = None
		self.maxActivations = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.numActivations = 0


	def doCooldownEffect(self):
		if self.numActivations < self.maxActivations:
			for item in _iter(self.getAffectedItems()):

				item.addSpeed(self.speedBonus)

			self.numActivations += 1

		if self.opponent().getLucky() > 0:
			self.removeLucky(self.getP3())

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.speedBonus = _div(self.getP('speed'), 100.0)
		self.maxActivations = int(self.getP("max"))


_R.reg("res://gd_core_items/Jynxtorquilla.gd", Jynxtorquilla)
_R.reg("Jynxtorquilla", Jynxtorquilla)
