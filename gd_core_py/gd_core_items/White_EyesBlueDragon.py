# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class White_EyesBlueDragon(_R.C("res://gd_core_items/Card.gd")):

	resource_path = "res://gd_core_items/White-EyesBlueDragon.gd"

	def _init_fields(self):
		super()._init_fields()
		self.snowflakes = None
		self.damReduction = None


	def doRevealEffect(self):
		self.giveBlock(self.getBlock() + self.getP1() * self.chainPosition)
		self.inflictCold(self.getP2())
		self.opponent().changeEffectDamageFactor( - self.damReduction)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.damReduction = _div(self.getP('damfactor'), 100.0)


_R.reg("res://gd_core_items/White-EyesBlueDragon.gd", White_EyesBlueDragon)
_R.reg("White-EyesBlueDragon", White_EyesBlueDragon)
