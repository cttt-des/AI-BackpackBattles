# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DragonClaws(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DragonClaws.gd"


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):

		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


		self.character().changeResistChance(_R.C("CoreConst").EventType.Poison, 
			self.getChance())


	def onBattleRageStarted(self, _event):
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(_div(self.getP1(), 100))


	def onBattleRageEnded(self, _event):
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(_div(self.getP1(), 100))

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/DragonClaws.gd", Exclusive__DragonClaws)
_R.reg("DragonClaws", Exclusive__DragonClaws)
