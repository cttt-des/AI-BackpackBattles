# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class SpiritCompanion(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpiritCompanion.gd"


	def getDescription(self, wrapInColor=True):
		descr = self.descriptor.getDescription()

		descr += "\n\n" + self.ctx.util.tra("Spirit Companion_DESCR")
		return self.insertParameters(descr, wrapInColor)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/SpiritCompanion.gd", SpiritCompanion)
_R.reg("SpiritCompanion", SpiritCompanion)
_R.reg("SpiritCompanion", SpiritCompanion)
