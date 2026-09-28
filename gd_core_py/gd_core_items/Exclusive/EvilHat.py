# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__EvilHat(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/EvilHat.gd"

	def _init_fields(self):
		super()._init_fields()
		self.selfBuffs = None
		self.opponentBuffs = None
		self.regen = None


	def canAffect(self, item):
		return item.canDamage()


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Dark)


	def onPrepare(self):
		unhealing = _div(self.getP('unhealing'), 100.0)
		unhealing += _div(self.getNumAffectedItems(_R.C('CoreConst').Affected.Secondary) * self.getP('unhealing2'), 100.0)
		self.character().giveUnhealing(unhealing)

		self.connectToCharacterDebuffs("onDebuffsChanged")
		self.connectToOpponentBuffs("onOpponentBuffsChanged")


	def onDebuffsChanged(self, amount, event):
		if (amount > 0 and 
			isinstance(event.origin, _R.C("Item")) and 
			event.origin.character() == self.character()):

			regenToGive = 0
			for i in _iter(amount):
				if self.rollChance():
					regenToGive += self.regen

			if regenToGive > 0:
				self.giveRegeneration(regenToGive, event)


	def onOpponentBuffsChanged(self, amount, event):
		if (amount < 0 and 
			isinstance(event.origin, _R.C("Item")) and 
			event.origin.character() == self.character()):

			for item in _iter(self.getAffectedItems()):
				item.addCritChancePercent(self.getChance2() * - amount)


	def doCooldownEffect(self):
		self.giveRandomBuffs(self.selfBuffs)
		self.giveRandomBuffs(self.opponentBuffs, None, _R.C("CoreConst").getBuffs(), self.opponent())
		self.activate()


	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

	def _readyInit(self):
		super()._readyInit()
		self.selfBuffs = int(self.getP("buffs"))
		self.opponentBuffs = int(self.getP("buffs2"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/EvilHat.gd", Exclusive__EvilHat)
_R.reg("EvilHat", Exclusive__EvilHat)
