# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DivinePotion(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/Exclusive/DivinePotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.debuffsNeeded = 0


	def onPrepare(self):
		self.connectToCharacterDebuffs("debuffsChanged")


	def debuffsChanged(self, _amount, event):
		if self.isEmpty():
			return

		if self.character().getDebuffStacks() >= self.debuffsNeeded:
			self.consumePotion()


	def onTriggerPotion(self, triggerEvent=None):
		self.cleanseRandomDebuffs(self.getP2())

	def _readyInit(self):
		super()._readyInit()
		self.debuffsNeeded = self.getP1()


_R.reg("res://gd_core_items/Exclusive/DivinePotion.gd", Exclusive__DivinePotion)
_R.reg("DivinePotion", Exclusive__DivinePotion)
