# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ArmoredCouragePuppy(_R.C("res://gd_core_items/Exclusive/CouragePuppy.gd")):

	resource_path = "res://gd_core_items/Exclusive/ArmoredCouragePuppy.gd"


	def _readyInit(self):
		super()._readyInit()
		self.damageSource.unsetFlag(_H_1)
		self.damageSource.unsetFlag(_H_2)


_R.reg("res://gd_core_items/Exclusive/ArmoredCouragePuppy.gd", Exclusive__ArmoredCouragePuppy)
_R.reg("ArmoredCouragePuppy", Exclusive__ArmoredCouragePuppy)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreDamageSource").Flags.CanTriggerItems
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreDamageSource").Flags.CanTriggerSpikes
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
