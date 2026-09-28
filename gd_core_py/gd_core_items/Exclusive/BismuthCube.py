# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BismuthCube(_R.C("res://gd_core_items/Exclusive/Cube.gd")):

	resource_path = "res://gd_core_items/Exclusive/BismuthCube.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numActivations = 0
		self.buffCounter = 0
		self.nonOxidated = None
		self.buffsNeeded = None
		self.maxUses = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.setState(0)
		self.buffCounter = 0
		self.affectedItem = self.getFirstAffectedItem()
		self.connectToCharacterBuffs("onBuffsChanged")


	def onBuffsChanged(self, amount, event):
		remainingUses = self.maxUses - self.numActivations
		if remainingUses == 0:
			return

		if amount > 0:
			numProccs = 0
			self.buffCounter += amount
			while self.buffCounter > self.buffsNeeded:
				numProccs += 1
				self.buffCounter -= self.buffsNeeded

			numProccs = min(remainingUses, numProccs)

			if numProccs > 0:
				if self.affectedItem != None:
					if self.ctx.cube_advanced.get(self.affectedItem, self) == self:
						self.ctx.cube_advanced[self.affectedItem] = self
						self.affectedItem.advanceCooldownSeconds(self.cdAdvance * numProccs)
					else:
						self.affectedItem.advanceCooldownSeconds(self.cdAdvance * numProccs * self.penaltyFactor)

				self.giveRandomBuffs(numProccs)
				self.setState(self.numActivations + numProccs)
				self.miniActivate()


	def onShopEntered(self):
		self.onStateChanged(self.maxUses)


	def onStateChanged(self, _numActivations):
		self.numActivations = _numActivations

	def _readyInit(self):
		super()._readyInit()
		self.buffsNeeded = self.getP("buffs")
		self.maxUses = int(self.getP("max"))
		self.onStateChanged(self.maxUses)



_R.reg("res://gd_core_items/Exclusive/BismuthCube.gd", Exclusive__BismuthCube)
_R.reg("BismuthCube", Exclusive__BismuthCube)
