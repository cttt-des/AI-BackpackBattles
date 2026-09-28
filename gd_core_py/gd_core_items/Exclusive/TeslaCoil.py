# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__TeslaCoil(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/TeslaCoil.gd"

	def _init_fields(self):
		super()._init_fields()
		self.itemsToAdvance = []
		self.numCollectedCharges = 0
		self.advanceItemCounter = 0
		self.collectCharges = True
		self.cdAdvance = None
		self.salesChance = None
		self.engineerWeight = None
		self.chargeCounter = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.setState(0)
		self.collectCharges = True
		self.numCollectedCharges = 0
		self.advanceItemCounter = 0
		self.itemsToAdvance = _dup(self.getAffectedItems())
		_shuffle(self.itemsToAdvance)

		otherItems = []
		for item in _iter(self.inventory.getItems()):
			if item != self and not item in self.itemsToAdvance:
				if item.hasCooldown():
					otherItems.append(item)

		_shuffle(otherItems)
		self.itemsToAdvance.extend(otherItems)


	def onChargeReceived(self, _charge):
		if self.collectCharges:
			self.numCollectedCharges += 1
			self.setState(self.numCollectedCharges)
			self.miniActivate()
		else:
			self.advanceItem()


	def doCooldownEffect(self):
		self.collectCharges = False
		for i in _iter(self.numCollectedCharges):
			self.advanceItem()

		self.onStateChanged(None)
		done = (len(self.itemsToAdvance) < self.advanceItemCounter + 1)
		self.onAfterEffectFinished(done)
		if not done:
			self.activate()


	def advanceItem(self):
		while True:
			if len(self.itemsToAdvance) < self.advanceItemCounter + 1:
				return

			item = self.itemsToAdvance[self.advanceItemCounter]
			self.advanceItemCounter += 1

			if item.isCooldownActive():
				item.advanceCooldownSeconds(self.cdAdvance)


				if len(self.itemsToAdvance) < self.advanceItemCounter + 1:
					self.consumed = True

				self.miniActivate()
				return


	def onStateChanged(self, _numCollectedCharges):
		if _numCollectedCharges == None:
			pass
		else:
			pass


	def onShopEntered(self):
		self.onStateChanged(None)


	def onSaleRoll(self, item):
		pass

	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.cdAdvance = self.getP("cdadvance")
		self.salesChance = _div(self.getP('sales'), 100.0)
		self.engineerWeight = self.getP("weight")
		pass



_R.reg("res://gd_core_items/Exclusive/TeslaCoil.gd", Exclusive__TeslaCoil)
_R.reg("TeslaCoil", Exclusive__TeslaCoil)
