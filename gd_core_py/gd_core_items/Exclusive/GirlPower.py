# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__GirlPower(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/GirlPower.gd"

	def _init_fields(self):
		super()._init_fields()
		self.empower = None
		self.regen = None
		self.speed_v = None


	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return color == _R.C("CoreConst").Affected.Primary


	def canAffect(self, item):
		return item.isClassItem()


	def onPrepare(self):
		self.addSpeed(self.speed_v * self.getNumDistinctAffectedItems())


	def doCooldownEffect(self):
		curEmpower = self.character().getEmpower()
		curRegen = self.character().getRegeneration()

		if curRegen < curEmpower:
			self.giveRegeneration(self.regen)
		elif curRegen > curEmpower:
			self.giveEmpower(self.empower)
		else:
			if self.ctx.util.flip():
				self.giveRegeneration(self.regen)
			else:
				self.giveEmpower(self.empower)

		self.activate()


	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.empower = int(self.getP("empower"))
		self.regen = int(self.getP("regen"))
		self.speed_v = _div(int(self.getP('speed')), 100.0)


_R.reg("res://gd_core_items/Exclusive/GirlPower.gd", Exclusive__GirlPower)
_R.reg("GirlPower", Exclusive__GirlPower)
