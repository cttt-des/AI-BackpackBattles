# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BookofLight(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BookofLight.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.regen = None
		self.spellSpeed = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Spell)


	def onPrepare(self):
		speed = 0.0
		for item in _iter(self.getAffectedItems()):
			if item.hasType(_R.C("CoreConst").Type.Holy):
				speed += self.spellSpeed * 2
			else:
				speed += self.spellSpeed
		self.addSpeed(speed)


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.giveRegeneration(self.regen, event)
			self.heal(self.getP_m("heal"), event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("mana"))
		self.regen = int(self.getP("regen"))
		self.spellSpeed = _div(int(self.getP('speed')), 100.0)


_R.reg("res://gd_core_items/Exclusive/BookofLight.gd", Exclusive__BookofLight)
_R.reg("BookofLight", Exclusive__BookofLight)
