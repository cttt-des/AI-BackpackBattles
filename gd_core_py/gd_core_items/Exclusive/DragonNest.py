# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DragonNest(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DragonNest.gd"

	gatedItems = ["Emerald Egg", "Amethyst Egg", "Sapphire Egg"]

	def canAffect(self, item):
		return isinstance(item, _R.C("DragonEgg")) or item.hasTag(_R.C("CoreConst").Tag.Dragon)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			if item.hasTag(_R.C("CoreConst").Tag.Dragon):
				self.connectForCombat(item, "attacked", "onDragonAttacked")



	def onDragonAttacked(self, damageRes):
		self.heal(self.getP_m("heal"), damageRes.event)
		self.miniActivate()


	def onCombatStart(self):
		self.giveLucky(self.getP2())
		self.giveRegeneration(self.getP3())
		self.giveMana(self.getP4())
		self.giveHeat(self.getP5())
		self.activate()


	def getGatedDescriptor(self, rarity):
		return self.ctx.item_book.getDescriptor(self.ctx.util.pickRandomElement(self.gatedItems))

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/DragonNest.gd", Exclusive__DragonNest)
_R.reg("DragonNest", Exclusive__DragonNest)
