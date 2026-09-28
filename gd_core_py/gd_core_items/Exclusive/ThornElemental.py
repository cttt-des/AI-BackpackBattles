# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ThornElemental(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ThornElemental.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikesLimit = None
		self.spikes = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Nature)


	def onPrepare(self):
		self.character().changeEffectSpikesLimit(self.spikesLimit)
		self.character().changeRangedSpikesLimit(self.spikesLimit)
		self.character().changeSpikesCritChancePercent(self.getChance() * self.getNumAffectedItems())


	def doCooldownEffect(self):
		self.giveSpikes(self.spikes)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.spikesLimit = _div(self.getP('spikedam'), 100.0)
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core_items/Exclusive/ThornElemental.gd", Exclusive__ThornElemental)
_R.reg("ThornElemental", Exclusive__ThornElemental)
