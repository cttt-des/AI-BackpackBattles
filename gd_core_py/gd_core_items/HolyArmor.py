# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HolyArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/HolyArmor.gd"


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def onCombatStart(self):
		self.giveBlock()





		numAffected = self.getNumAffectedItems()
		if numAffected > 0:
			self.giveRegeneration(numAffected * self.getP1())

		self.activate()



	def doCooldownEffect(self):
		self.cleansePoison(self.getP2())
		self.activate()



	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/HolyArmor.gd", HolyArmor)
_R.reg("HolyArmor", HolyArmor)
