# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StrongPestilenceFlask(_R.C("res://gd_core_items/PestilenceFlask.gd")):

	resource_path = "res://gd_core_items/StrongPestilenceFlask.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poisonTimer = None


	def onTriggerPotion(self, triggerEvent=None):
		super().onTriggerPotion(triggerEvent)
		self.poisonTimer.start(self.getP3())


	def poisonTimerTimeout(self):
		self.inflictPoison(self.getP4())


	def onCombatEnd(self):
		self.poisonTimer.stop()

	def _readyInit(self):
		super()._readyInit()
		self.poisonTimer = self.newItemTimer("PoisonTimer", "poisonTimerTimeout", True)


_R.reg("res://gd_core_items/StrongPestilenceFlask.gd", StrongPestilenceFlask)
_R.reg("StrongPestilenceFlask", StrongPestilenceFlask)
