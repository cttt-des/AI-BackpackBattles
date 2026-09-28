# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class SteelGoobert(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/SteelGoobert.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedWeapons = []


	def canAffect_secondary(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)):
			self.affectedWeapons.append(item)


	def doCooldownEffect(self):
		for item in _iter(self.affectedWeapons):
			item.addBonusDamage(self.getP2())
		self.giveBlock()


	def onCombatEnd(self):
		self.affectedWeapons.clear()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/SteelGoobert.gd", SteelGoobert)
_R.reg("SteelGoobert", SteelGoobert)
