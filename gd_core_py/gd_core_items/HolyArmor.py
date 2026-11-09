# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HolyArmor_2(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/HolyArmor.gd"


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onCombatStart(self):
		self.giveBlock()





		numAffected = self.getNumAffectedItems()
		if numAffected > 0:
			self.giveRegeneration(numAffected * self.getP1())

		self.activate()



	def doCooldownEffect(self):
		self.cleansePoison(self.getP2())
		self.activate()



	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/HolyArmor.gd", HolyArmor_2)
_R.reg("HolyArmor", HolyArmor_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
