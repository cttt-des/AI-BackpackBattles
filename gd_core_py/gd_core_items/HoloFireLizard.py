# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HoloFireLizard(_R.C("res://gd_core_items/Card.gd")):

	resource_path = "res://gd_core_items/HoloFireLizard.gd"

	def _init_fields(self):
		super()._init_fields()
		self.fireParticles = None
		self.damFactor = None
		self.heat = None


	def doRevealEffect(self):
		self.character().changeEffectDamageFactor(self.damFactor)
		dam = self.descriptor.minDam + self.getP1() * self.chainPosition
		res = self.dealEffectDamage(dam)
		self.giveHeat(self.heat)

		self.activate(res)

	def _readyInit(self):
		super()._readyInit()
		self.damFactor = _div(self.getP('damfactor'), 100.0)
		self.heat = int(self.getP2())
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/HoloFireLizard.gd", HoloFireLizard)
_R.reg("HoloFireLizard", HoloFireLizard)
