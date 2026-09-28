# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ArmoredCouragePuppy(_R.C("res://gd_core_items/Exclusive/CouragePuppy.gd")):

	resource_path = "res://gd_core_items/Exclusive/ArmoredCouragePuppy.gd"


	def _readyInit(self):
		super()._readyInit()
		self.damageSource.unsetFlag(_R.C("CoreDamageSource").Flags.CanTriggerItems)
		self.damageSource.unsetFlag(_R.C("CoreDamageSource").Flags.CanTriggerSpikes)


_R.reg("res://gd_core_items/Exclusive/ArmoredCouragePuppy.gd", Exclusive__ArmoredCouragePuppy)
_R.reg("ArmoredCouragePuppy", Exclusive__ArmoredCouragePuppy)
