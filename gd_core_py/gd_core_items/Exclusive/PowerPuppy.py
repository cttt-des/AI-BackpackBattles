# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PowerPuppy(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/PowerPuppy.gd"

	def _init_fields(self):
		super()._init_fields()
		self.options = []


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Pet)


	def onPrepare(self):
		self.addSpeed(_div(self.getNumAffectedItems() * self.getP4(), 100.0))
		self.options = [0, 1, 2]


	def doCooldownEffect(self):
		rng = self.ctx.util.pickRandomElement(self.options)
		if rng == 0:
			self.giveLucky(self.getP1())
		elif rng == 1:
			self.giveRegeneration(self.getP2())
		else:
			self.giveEmpower(self.getP3())
		self.activate()

		self.options = [0, 1, 2]
		_erase(self.options, rng)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/PowerPuppy.gd", Exclusive__PowerPuppy)
_R.reg("PowerPuppy", Exclusive__PowerPuppy)
