# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BurningSpikes(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BurningSpikes.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikesAcc = 0
		self.affectedItemsDict = {}
		self.spikes = None
		self.heat = None
		self.spikesNeeded = None
		self.heatForSpikes = None


	def canAffect(self, item):
		return item.gainsStack(_R.C("CoreConst").Stack.Spikes)


	def onPrepare(self):
		self.spikesAcc = 0
		self.affectedItemsDict = self.ctx.util.arrayAsIndexDict(self.getAffectedItems())

		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onSpikesChanged(self, amount, event):
		if amount > 0 and event.origin in self.affectedItemsDict:
			self.spikesAcc += amount
			numProccs = _div(self.spikesAcc, self.spikesNeeded)
			if numProccs > 0:
				self.giveHeat(self.heatForSpikes * numProccs)
				self.spikesAcc %= self.spikesNeeded
				self.miniActivate()


	def onCombatStart(self):
		self.giveSpikes(self.spikes)
		self.giveHeat(self.heat)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))
		self.heat = int(self.getP("heat"))
		self.spikesNeeded = int(self.getP("spikest"))
		self.heatForSpikes = int(self.getP("heat2"))


_R.reg("res://gd_core_items/Exclusive/BurningSpikes.gd", Exclusive__BurningSpikes)
_R.reg("BurningSpikes", Exclusive__BurningSpikes)
