# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Cauldron(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Cauldron.gd"

	def _init_fields(self):
		super()._init_fields()
		self.options = []

	healColor = Color(0.384314, 0.913725, 0.423529)
	manaColor = Color(0.329412, 0.392157, 0.992157)
	heatColor = Color(0.996078, 0.458824, 0.290196)

	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food) or item.hasType(_R.C("CoreConst").Type.Potion)


	def onPrepare(self):
		self.addSpeed(_div(self.getP4(), 100.0) * self.getNumAffectedItems())
		self.options = [0, 1, 2]


	def doCooldownEffect(self):
		rng = self.ctx.util.pickRandomElement(self.options)
		if rng == 0:
			self.heal()
		elif rng == 1:
			self.giveMana(self.getP2())
		else:
			self.giveHeat(self.getP3())
		self.activate()

		self.options = [0, 1, 2]
		_erase(self.options, rng)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Cauldron.gd", Exclusive__Cauldron)
_R.reg("Cauldron", Exclusive__Cauldron)
