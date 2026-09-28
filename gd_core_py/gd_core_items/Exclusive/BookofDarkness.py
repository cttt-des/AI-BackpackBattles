# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BookofDarkness(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BookofDarkness.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healthNeeded = None
		self.mana = None
		self.blind = None
		self.spellSpeed = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Spell)


	def onPrepare(self):
		speed = 0.0
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_R.C("CoreConst").Type.Dark):
				speed += self.spellSpeed * 2
			else:
				speed += self.spellSpeed
		self.addSpeed(speed)


	def doCooldownEffect(self):
		if self.character().getCurrentHealth() > self.healthNeeded:
			event = self.character().loseHealth(self.healthNeeded, self)
			self.giveMana(self.mana, event)
			self.inflictBlind(self.blind, event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.healthNeeded = int(self.getP("health"))
		self.mana = int(self.getP("mana"))
		self.blind = int(self.getP("blind"))
		self.spellSpeed = _div(int(self.getP('speed')), 100.0)


_R.reg("res://gd_core_items/Exclusive/BookofDarkness.gd", Exclusive__BookofDarkness)
_R.reg("BookofDarkness", Exclusive__BookofDarkness)
