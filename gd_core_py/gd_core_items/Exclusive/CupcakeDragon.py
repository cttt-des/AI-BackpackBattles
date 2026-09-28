# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__CupcakeDragon(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/CupcakeDragon.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffRemoval = None
		self.buffGain = None
		self.speedPerFood = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			buffsLeft = self.buffRemoval
			ownMostBuffs = self.getMostStacks(self.character(), _R.C("CoreConst").getBuffs())
			_shuffle(ownMostBuffs)
			for buffType in _iter(ownMostBuffs):
				cur = self.opponent().getStacks(buffType)
				buffsRemoved = min(cur, buffsLeft)
				self.opponent().loseStacks(buffType, buffsRemoved, self)
				buffsLeft -= buffsRemoved
				if buffsLeft == 0:
					break

			oppoMostBuffs = self.getMostStacks(self.opponent(), _R.C("CoreConst").getBuffs())
			self.giveStacks(self.character(), self.ctx.util.pickRandomElement(oppoMostBuffs), 
				self.buffGain)


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food)


	def onPrepare(self):
		self.addSpeed(self.speedPerFood * self.getNumAffectedItems())

	def _readyInit(self):
		super()._readyInit()
		self.buffRemoval = int(self.getP("remove"))
		self.buffGain = int(self.getP("gain"))
		self.speedPerFood = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/CupcakeDragon.gd", Exclusive__CupcakeDragon)
_R.reg("CupcakeDragon", Exclusive__CupcakeDragon)
