# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DragonKnight(_R.C("res://gd_core_items/RubyWhelp.gd")):

	resource_path = "res://gd_core_items/Exclusive/DragonKnight.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cdAdvance = None


	def canAffect(self, item):
		return item.canActivate()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.heal(self.getP_m("heal"), damageRes.event)


	def onItemActivated(self, event):
		self.advanceCooldownPercent(self.cdAdvance)

	def _readyInit(self):
		super()._readyInit()
		self.cdAdvance = self.getP("advance")


_R.reg("res://gd_core_items/Exclusive/DragonKnight.gd", Exclusive__DragonKnight)
_R.reg("DragonKnight", Exclusive__DragonKnight)
