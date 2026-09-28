# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Robodog(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Robodog.gd"

	def _init_fields(self):
		super()._init_fields()
		self.digUpItems = { "Stone": 4, "Garlic": 3, "Blueberries": 2, "Lump of Coal": 3, "Pocket Sand": 3, "Chipped Ruby": 1, "Chipped Sapphire": 1, "Chipped Emerald": 1, "Chipped Topaz": 1, "Chipped Amethyst": 1, "Healing Herbs": 0.5, "Bag of Stones": 0.5, "Walrus Tusk": 0.2, "Whetstone": 0.2, "Piggybank": 0.2, "Pan": 0.2, "Customer Card": 0.2, "Gloves of Haste": 0.2, "Dagger": 0.2, "Protective Purse": 0.1, "Flawed Ruby": 0.2, "Flawed Sapphire": 0.2, "Flawed Emerald": 0.2, "Flawed Topaz": 0.2, "Flawed Amethyst": 0.2, }
		self.spawnPos = None
		self.luck = None
		self.heat = None
		self.cdIncrease = None


	def onShopEntered(self):
		pass

	def onPrepare(self):
		pass



	def onChargeReceived(self, _charge):
		self.resetBaseCooldown()
		if self.numCharges == 1:
			self.setState(True)


	def onChargeLeft(self, _charge):
		if self.numCharges == 0:
			self.setState(False)


	def doCooldownEffect(self):
		self.giveLucky(self.luck)
		self.giveHeat(self.heat)
		if self.numCharges == 0:
			self.setBaseCooldown(self.baseCooldownOverride + self.cdIncrease)
		self.activate()


	def onStateChanged(self, charged):
		if charged:
			pass
		else:
			pass


	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.heat = int(self.getP("heat"))
		self.cdIncrease = self.getP("cdincrease")
		pass



_R.reg("res://gd_core_items/Exclusive/Robodog.gd", Exclusive__Robodog)
_R.reg("Robodog", Exclusive__Robodog)
