# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BloodyDagger_2(_R.C("res://gd_core_items/Dagger.gd")):

	resource_path = "res://gd_core_items/BloodyDagger.gd"

	def _init_fields(self):
		super()._init_fields()
		self._vampirismStacks = 0

	@property
	def vampirismStacks(self):
		return self._vampirismStacks
	@vampirismStacks.setter
	def vampirismStacks(self, v):
		self._vampirismStacks = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.vampirismStacks = 0


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.vampirismStacks < self.getP2():
				self.giveVampirism(self.getP1())
				self.vampirismStacks += self.getP1()

			numAffected = self.getNumAffectedItems()
			if numAffected > 0:
				self.heal(numAffected * self.getP_m("heal"))

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/BloodyDagger.gd", BloodyDagger_2)
_R.reg("BloodyDagger", BloodyDagger_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Vampiric
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
