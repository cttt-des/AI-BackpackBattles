# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpringLoader(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpringLoader.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speed1 = None
		self.speed2 = None
		self.cdAdvance = None


	def canAffect(self, item):
		return item.hasCooldown()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.speed1)


	def doCooldownEffect(self):
		self.deactivateCooldown()

		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.speed1 + self.speed2)
			item.advanceCooldownSeconds(self.cdAdvance)

		self.onAfterEffectFinished()


	def getTextureSize(self):
		return Vector2.ZERO

	def getSpriteOffset(self):
		return Vector2.ZERO

	def _readyInit(self):
		super()._readyInit()
		self.speed1 = _div(self.getP('speed'), 100.0)
		self.speed2 = _div(self.getP('speed2'), 100.0)
		self.cdAdvance = self.getP("cdadvance")


_R.reg("res://gd_core_items/Exclusive/SpringLoader.gd", Exclusive__SpringLoader)
_R.reg("SpringLoader", Exclusive__SpringLoader)
