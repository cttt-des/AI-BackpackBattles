# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DeathLotus(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DeathLotus.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana = None
		self.buffs = None
		self.darkSpeed = None
		self.luckNeeded = None
		self.stamina = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Dark)


	def onPrepare(self):
		self.addSpeed(self.getNumAffectedItems() * self.darkSpeed)


	def doCooldownEffect(self):
		self.giveMana(self.mana)
		self.removeRandomBuffs(self.buffs)
		if self.character().getLucky() >= self.luckNeeded:
			event = self.useLucky(self.luckNeeded)
			self.giveStamina(self.stamina, event)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP("mana"))
		self.buffs = int(self.getP("buffs"))
		self.darkSpeed = _div(self.getP('speed'), 100.0)
		self.luckNeeded = int(self.getP("luckt"))
		self.stamina = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/DeathLotus.gd", Exclusive__DeathLotus)
_R.reg("DeathLotus", Exclusive__DeathLotus)
