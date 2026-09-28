# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StrongHealthPotion(_R.C("res://gd_core_items/HealthPotion.gd")):

	resource_path = "res://gd_core_items/StrongHealthPotion.gd"


	def onTriggerPotion(self, triggerEvent=None):
		super().onTriggerPotion(triggerEvent)
		self.giveRegeneration(self.getP4(), triggerEvent)


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 1

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/StrongHealthPotion.gd", StrongHealthPotion)
_R.reg("StrongHealthPotion", StrongHealthPotion)
