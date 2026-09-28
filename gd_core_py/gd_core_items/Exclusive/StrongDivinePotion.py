# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StrongDivinePotion(_R.C("res://gd_core_items/Exclusive/DivinePotion.gd")):

	resource_path = "res://gd_core_items/Exclusive/StrongDivinePotion.gd"


	def onTriggerPotion(self, triggerEvent=None):
		super().onTriggerPotion(triggerEvent)
		self.giveRandomBuffs(self.getP3())


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/StrongDivinePotion.gd", Exclusive__StrongDivinePotion)
_R.reg("StrongDivinePotion", Exclusive__StrongDivinePotion)
