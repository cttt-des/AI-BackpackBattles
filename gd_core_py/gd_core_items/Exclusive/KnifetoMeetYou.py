# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__KnifetoMeetYou(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/KnifetoMeetYou.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boosted = 0
		self.daggerDescriptor = None
		self.daggerSpeed = None
		self.damFactor = None
		self.speedPerDagger = None


	def onBought(self):
		self.boosted = 3


	def getData(self):
		return self.boosted


	def setData(self, data):
		if data != None:
			self.boosted = data


	def canAffect(self, item):
		return isinstance(item, _R.C("Dagger"))


	def onPrepare(self):
		for item in _iter(self.inventory.getItems()):
			if isinstance(item, _R.C("Dagger")):
				item.addSpeed(self.daggerSpeed)

		self.addSpeed(self.speedPerDagger * self.getNumAffectedItems())


	def doCooldownEffect(self):
		for item in _iter(self.inventory.getItems()):
			if item.canBeEmpowered():
				item.addBonusDamageFactor(self.damFactor)
		self.onAfterEffectFinished()


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.daggerDescriptor:
			self.boosted -= 1


	def canAffect_global(self, item):
		return item.canBeEmpowered()

	def _readyInit(self):
		super()._readyInit()
		self.daggerDescriptor = self.ctx.item_book.getDescriptor("Dagger")
		self.daggerSpeed = _div(self.getP('speed'), 100.0)
		self.damFactor = _div(self.getP('dam'), 100.0)
		self.speedPerDagger = _div(self.getP('speed2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/KnifetoMeetYou.gd", Exclusive__KnifetoMeetYou)
_R.reg("KnifetoMeetYou", Exclusive__KnifetoMeetYou)
