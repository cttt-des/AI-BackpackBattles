# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BoxofRiches(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/BoxofRiches.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numGems = 1

	gemOdds = [
		16, 
		8, 
		2, 
		1, 
		0.5
	]

	def onShopEntered(self):
		pass

	def getGatedDescriptor(self, rarityOdds, numHighRolls=0):
		return None

	def getRelatedItemHeight(self):
		return 50



	def onGateItemRoll(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/BoxofRiches.gd", BoxofRiches)
_R.reg("BoxofRiches", BoxofRiches)
