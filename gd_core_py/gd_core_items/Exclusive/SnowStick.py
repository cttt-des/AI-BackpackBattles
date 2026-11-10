# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SnowStick(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/SnowStick.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cold = None
		self.selfCold = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.inflictCold(self.cold)
			self.giveStacks(self.character(), _H_1, self.selfCold)

	def _readyInit(self):
		super()._readyInit()
		self.cold = int(self.getP("cold"))
		self.selfCold = int(self.getP("cold2"))


_R.reg("res://gd_core_items/Exclusive/SnowStick.gd", Exclusive__SnowStick)
_R.reg("SnowStick", Exclusive__SnowStick)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
