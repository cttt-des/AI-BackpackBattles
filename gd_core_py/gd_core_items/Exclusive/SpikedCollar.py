# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpikedCollar(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpikedCollar.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikes = None


	def onPrepare(self):
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.character().addBattleRageDuration(self.getP_m("dur_rage"))


	def onBattleRageStarted(self, event):
		self.giveSpikes(self.spikes, event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core_items/Exclusive/SpikedCollar.gd", Exclusive__SpikedCollar)
_R.reg("SpikedCollar", Exclusive__SpikedCollar)
