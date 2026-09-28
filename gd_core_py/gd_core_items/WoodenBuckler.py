# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class WoodenBuckler(_R.C("res://gd_core_items/Shield.gd")):

	resource_path = "res://gd_core_items/WoodenBuckler.gd"


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/WoodenBuckler.gd", WoodenBuckler)
_R.reg("WoodenBuckler", WoodenBuckler)
