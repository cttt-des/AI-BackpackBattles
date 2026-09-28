# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__EchoingBattlecry(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/EchoingBattlecry.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItems = []
		self.speedPerItem = None


	def canAffect(self, item):
		return item.hasStartofBattle()


	def onPrepare(self):
		self.affectedItems = self.getAffectedItems()
		_shuffle(self.affectedItems)

		self.addSpeed(self.speedPerItem * len(self.affectedItems))


	def doCooldownEffect(self):
		if not (not self.affectedItems):
			item = self.affectedItems.pop()
			item.repeatCombatStart()
			if (not self.affectedItems):
				self.onAfterEffectFinished()
			else:
				self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.speedPerItem = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/EchoingBattlecry.gd", Exclusive__EchoingBattlecry)
_R.reg("EchoingBattlecry", Exclusive__EchoingBattlecry)
