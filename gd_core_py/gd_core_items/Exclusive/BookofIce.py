# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BookofIce(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BookofIce.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.cold = None
		self.spellSpeed = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Spell)


	def onPrepare(self):
		speed = 0.0
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_R.C("CoreConst").Type.Ice):
				speed += self.spellSpeed * 2
			else:
				speed += self.spellSpeed
		self.addSpeed(speed)


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.inflictCold(self.cold, event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("mana"))
		self.cold = int(self.getP("cold"))
		self.spellSpeed = _div(int(self.getP('speed')), 100.0)


_R.reg("res://gd_core_items/Exclusive/BookofIce.gd", Exclusive__BookofIce)
_R.reg("BookofIce", Exclusive__BookofIce)
