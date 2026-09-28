# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DigDeeper(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DigDeeper.gd"

	def _init_fields(self):
		super()._init_fields()
		self.shovelDescriptor = None
		self.shovelDogDescriptor = None
		self.blind = None


	def onCombatStart(self):
		self.inflictBlind(self.blind)


	def canAffect_global(self, item):
		return item.isA(self.shovelDescriptor) or item.isA(self.shovelDogDescriptor)

	def _readyInit(self):
		super()._readyInit()
		self.shovelDescriptor = self.ctx.item_book.getDescriptor("Shovel")
		self.shovelDogDescriptor = self.ctx.item_book.getDescriptor("Robodog")
		self.blind = int(self.getP("blind"))


_R.reg("res://gd_core_items/Exclusive/DigDeeper.gd", Exclusive__DigDeeper)
_R.reg("DigDeeper", Exclusive__DigDeeper)
