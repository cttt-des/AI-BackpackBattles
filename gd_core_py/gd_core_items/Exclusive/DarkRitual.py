# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DarkRitual(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DarkRitual.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boosted = 0
		self.crystalDescriptor = None
		self.debuffs = None
		self.vampirism = None
		self.darkSpeed = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Dark)


	def getData(self):
		return self.boosted


	def setData(self, data):
		if data != None:
			self.boosted = data


	def onBought(self):
		self.boosted = 1


	def doCooldownEffect(self):
		self.inflictRandomDebuffs(self.debuffs)
		self.giveVampirism(self.vampirism)
		self.onAfterEffectFinished()


	def onPrepare(self):
		numDark = self.getNumAffectedItems()
		if numDark > 0:
			self.addSpeed(self.darkSpeed * numDark)


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.crystalDescriptor:
			self.boosted -= 1

	def _readyInit(self):
		super()._readyInit()
		self.crystalDescriptor = self.ctx.item_book.getDescriptor("Corrupted Crystal")
		self.debuffs = int(self.getP("debuffs"))
		self.vampirism = int(self.getP("vampirism"))
		self.darkSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/DarkRitual.gd", Exclusive__DarkRitual)
_R.reg("DarkRitual", Exclusive__DarkRitual)
