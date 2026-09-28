# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__LevelUp(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/LevelUp.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stamina = None
		self.mana = None
		self.luck = None
		self.speedPerRound = None
		self.buyRound = None


	def onPrepare(self):
		roundsPassed = self.ctx.cur_round - self.buyRound
		self.addSpeed(roundsPassed * self.speedPerRound)


	def doCooldownEffect(self):
		self.giveMaxHealth(self.getP_m("maxhealth"))
		self.giveStamina(self.stamina)
		self.giveMana(self.mana)
		self.giveLucky(self.luck)
		self.activate()









	def _readyInit(self):
		super()._readyInit()
		self.stamina = self.getP("stamina")
		self.mana = int(self.getP("mana"))
		self.luck = int(self.getP("luck"))
		self.speedPerRound = _div(self.getP('speed'), 100.0)
		self.buyRound = int(self.getP("skillround"))


_R.reg("res://gd_core_items/Exclusive/LevelUp.gd", Exclusive__LevelUp)
_R.reg("LevelUp", Exclusive__LevelUp)
