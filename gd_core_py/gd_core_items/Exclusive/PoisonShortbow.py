# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PoisonShortbow(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/PoisonShortbow.gd"

	def _init_fields(self):
		super()._init_fields()
		self._poison = 0

	@property
	def poison(self):
		return self._poison
	@poison.setter
	def poison(self, v):
		self._poison = int(v)

	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			randomDebuff = self.ctx.util.pickRandomElement(_H_1.getDebuffs())
			if randomDebuff == _H_2:
				self.inflictPoison(self.poison + 1)
			else:
				self.inflictPoison(self.poison)
				self.giveStacks(self.opponent(), randomDebuff, 1)

	def _readyInit(self):
		super()._readyInit()
		self.poison = self.getP1()


_R.reg("res://gd_core_items/Exclusive/PoisonShortbow.gd", Exclusive__PoisonShortbow)
_R.reg("PoisonShortbow", Exclusive__PoisonShortbow)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreConst")
try:
    _H_2 = _R.C("CoreConst").EventType.Poison
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
