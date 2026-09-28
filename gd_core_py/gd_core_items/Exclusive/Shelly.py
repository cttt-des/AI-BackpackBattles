# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Shelly(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Shelly.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cleanses = None
		self.potionSpeed = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Potion)


	def doCooldownEffect(self):
		self.cleanseRandomDebuffs(self.cleanses)
		self.heal()
		self.activate()


	def onPrepare(self):
		self.character().changeDebuffProtectionChance( - self.getChance())
		self.addSpeed(self.potionSpeed * self.getNumAffectedItems())


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High

	def _readyInit(self):
		super()._readyInit()
		self.cleanses = int(self.getP("debuffs"))
		self.potionSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Shelly.gd", Exclusive__Shelly)
_R.reg("Shelly", Exclusive__Shelly)
