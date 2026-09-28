# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MagicMirror(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MagicMirror.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffFactor = None
		self.buffLimit = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def onPrepare(self):
		totalChance = self.getChance() + self.getNumAffectedItems() * self.getChance2()
		self.character().changeAllDebuffsReflectChance(totalChance)


	def doCooldownEffect(self):
		self.multiplyBuffsLimit(self.buffFactor, self.buffLimit)
		self.onAfterEffectFinished()

	def _readyInit(self):
		super()._readyInit()
		self.buffFactor = _div(self.getP('buffs'), 100.0)
		self.buffLimit = int(self.getP("max"))


_R.reg("res://gd_core_items/Exclusive/MagicMirror.gd", Exclusive__MagicMirror)
_R.reg("MagicMirror", Exclusive__MagicMirror)
