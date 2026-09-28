# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class PestilenceFlask(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/PestilenceFlask.gd"


	def onTriggerPotion(self, triggerEvent=None):
		self.inflictPoison(self.getP1(), triggerEvent)
		self.selfInflictPoison(self.getP2(), triggerEvent)


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_healed", "onOpponentHeal")


	def onOpponentHeal(self, _amount, event):
		if self.isEmpty():
			return

		self.drink()

		self.triggerPotion(event)

		affected = self.getAffectedItems()
		if not (not affected):
			affected[0].triggerPotion(event)
			affected[0].miniActivate()

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/PestilenceFlask.gd", PestilenceFlask)
_R.reg("PestilenceFlask", PestilenceFlask)
