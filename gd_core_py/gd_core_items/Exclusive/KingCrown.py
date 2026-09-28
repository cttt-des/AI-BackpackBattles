# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__KingCrown(_R.C("res://gd_core_items/Crown.gd")):

	resource_path = "res://gd_core_items/Exclusive/KingCrown.gd"


	def prepare(self):
		gemPower = _div(self.getP('gempower'), 100.0)
		for gem in _iter(self.getGemsNoNull()):
			gem.changeGemPower(gemPower)
		super().prepare()



	def doCooldownEffect(self):
		self.character().changeBuffProtectStacks(1)
		self.heal()
		self.activate()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.Normal + 1

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/KingCrown.gd", Exclusive__KingCrown)
_R.reg("KingCrown", Exclusive__KingCrown)
