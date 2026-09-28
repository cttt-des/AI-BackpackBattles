# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletofLight(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletofLight.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regenOnActivate = None

	amuletColor = Color(1, 0.850098, 0.400391)

	def canAffect(self, item):
		return item.canActivate()


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")

		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")


	def onItemActivated(self, event):
		if event.origin.hasType(_R.C("CoreConst").Type.Holy):
			if self.rollChance2():
				self.giveRegeneration(self.regenOnActivate, event)
				self.miniActivate()
		else:
			if self.rollChance():
				self.giveRegeneration(self.regenOnActivate, event)
				self.miniActivate()


	def onRegenChanged(self, amount, event):
		if amount > 0:
			self.giveMaxHealth(amount * self.getP_m("maxhealth"), event)

	def _readyInit(self):
		super()._readyInit()
		self.regenOnActivate = int(self.getP("regen"))
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofLight.gd", Exclusive__AmuletofLight)
_R.reg("AmuletofLight", Exclusive__AmuletofLight)
