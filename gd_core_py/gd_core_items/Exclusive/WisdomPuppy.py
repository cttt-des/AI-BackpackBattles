# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__WisdomPuppy(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/WisdomPuppy.gd"


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Pet)


	def doCooldownEffect(self):
		self.giveBlock()
		self.cleanseCold(self.getP1())
		self.activate()


	def onPrepare(self):
		self.addSpeed(_div(self.getNumAffectedItems() * self.getP2(), 100.0))

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/WisdomPuppy.gd", Exclusive__WisdomPuppy)
_R.reg("WisdomPuppy", Exclusive__WisdomPuppy)
