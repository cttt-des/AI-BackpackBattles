# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StoneSkinPotion(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/StoneSkinPotion.gd"


	def onTriggerPotion(self, triggerEvent=None):
		self.healthToBlock(self.getP2(), self.getBlock(), triggerEvent)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_block_changed", "onBlockChanged")


	def onBlockChanged(self, _amount, event):
		if self.isEmpty():
			return

		if self.character().getBlock() >= self.getP1():

			self.consumePotion()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/StoneSkinPotion.gd", StoneSkinPotion)
_R.reg("StoneSkinPotion", StoneSkinPotion)
