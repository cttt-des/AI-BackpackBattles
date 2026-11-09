# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Pan_2(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Pan.gd"

	def _init_fields(self):
		super()._init_fields()
		self._bonusDamage = 0

	@property
	def bonusDamage(self):
		return self._bonusDamage
	@bonusDamage.setter
	def bonusDamage(self, v):
		self._bonusDamage = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPreCombatStart(self):
		self.addBonusDamage(self.getP1() * self.getNumAffectedItems())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Pan.gd", Pan_2)
_R.reg("Pan", Pan_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Food
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
