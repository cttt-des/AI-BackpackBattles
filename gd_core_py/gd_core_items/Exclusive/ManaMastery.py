# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ManaMastery(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ManaMastery.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boosted = 0
		self.mana = None
		self.magicSpeed = None
		self.bonusBuffs = None
		self.manaOrbDescriptor = None


	def getData(self):
		return self.boosted


	def setData(self, data):
		if data != None:
			self.boosted = data


	def onBought(self):
		self.boosted = 1


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Magic)


	def canAffect_global(self, item):
		return item.isA(self.manaOrbDescriptor)


	def onPrepare(self):
		numMagic = self.getNumAffectedItems()
		if numMagic > 0:
			self.addSpeed(self.magicSpeed * numMagic)


	def onPreCombatStart(self):
		for manaOrb in _iter(self.getAllInInventoryOfType(self.manaOrbDescriptor)):
			manaOrb.addBonusRandomBuffs(self.bonusBuffs)


	def doCooldownEffect(self):
		self.giveMana(self.mana)
		self.activate()


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.manaOrbDescriptor:
			self.boosted -= 1

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP("mana"))
		self.magicSpeed = _div(self.getP('speed'), 100.0)
		self.bonusBuffs = int(self.getP("buffs"))
		self.manaOrbDescriptor = self.ctx.item_book.getDescriptor("Mana Orb")


_R.reg("res://gd_core_items/Exclusive/ManaMastery.gd", Exclusive__ManaMastery)
_R.reg("ManaMastery", Exclusive__ManaMastery)
