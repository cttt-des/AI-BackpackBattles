# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class GlovesofHaste(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/GlovesofHaste.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusSpeed = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.bonusSpeed)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.bonusSpeed = _div(self.getP1(), 100)


_R.reg("res://gd_core_items/GlovesofHaste.gd", GlovesofHaste)
_R.reg("GlovesofHaste", GlovesofHaste)
