# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DragonscaleArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DragonscaleArmor.gd"


	def onPrepare(self):
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


	def onBattleRageStarted(self, event):
		self.giveBlock(self.getBlock(), True, event)
		self.character().changeDamageResistance(self.getP1())
		self.activate()


	def onBattleRageEnded(self, _event):
		self.character().changeDamageResistance( - self.getP1())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/DragonscaleArmor.gd", Exclusive__DragonscaleArmor)
_R.reg("DragonscaleArmor", Exclusive__DragonscaleArmor)
