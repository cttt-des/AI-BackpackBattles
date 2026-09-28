# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Shovel(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Shovel.gd"

	def _init_fields(self):
		super()._init_fields()
		self.digUpItems = { "Stone": 4, "Garlic": 3, "Blueberries": 2, "Lump of Coal": 3, "Pocket Sand": 3, "Chipped Ruby": 1, "Chipped Sapphire": 1, "Chipped Emerald": 1, "Chipped Topaz": 1, "Chipped Amethyst": 1, "Healing Herbs": 0.5, "Bag of Stones": 0.5, "Walrus Tusk": 0.2, "Whetstone": 0.2, "Piggybank": 0.2, "Pan": 0.2, "Customer Card": 0.2, "Gloves of Haste": 0.2, "Dagger": 0.2, "Protective Purse": 0.1, "Flawed Ruby": 0.2, "Flawed Sapphire": 0.2, "Flawed Emerald": 0.2, "Flawed Topaz": 0.2, "Flawed Amethyst": 0.2, }
		self.digParticles = None
		self.spawnPos = None


	def onShopEntered(self):
		pass

	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if self.rollChance():
				self.inflictBlind(1, damageRes.event)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Shovel.gd", Shovel)
_R.reg("Shovel", Shovel)
