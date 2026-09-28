# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Puzzlebox(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/Puzzlebox.gd"

	def _init_fields(self):
		super()._init_fields()
		self.slowSpeed = None
		self.fastSpeed = None

	puzzlebags = ["L", "S", "Z", "T", "J"]

	def canApplyEffect(self, toItem):
		return toItem.hasCooldown()


	def onPrepare(self):
		for item in _iter(self.getAffectedItemsInside()):
			item.reduceSpeed(self.slowSpeed)


	def doCooldownEffect(self):
		for item in _iter(self.getAffectedItemsInside()):
			item.addSpeed(self.slowSpeed + self.fastSpeed)
		self.onAfterEffectFinished()


	def getReplaceDescriptor(self, rarity):
		pass

	def getRelatedItemColumns(self):
		return 2

	def _readyInit(self):
		super()._readyInit()
		self.slowSpeed = _div(self.getP('speed'), 100.0)
		self.fastSpeed = _div(self.getP('speed2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Puzzlebox.gd", Exclusive__Puzzlebox)
_R.reg("Puzzlebox", Exclusive__Puzzlebox)
