# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StrongStoneSkinPotion(_R.C("res://gd_core_items/StoneSkinPotion.gd")):

	resource_path = "res://gd_core/StrongStoneSkinPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikes = None


	def onTriggerPotion(self, triggerEvent=None):
		super().onTriggerPotion(triggerEvent)
		self.giveStacksTemporary(self.character(), _H_1, 
			self.spikes, self.getP_m("dur"), triggerEvent)

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core/StrongStoneSkinPotion.gd", StrongStoneSkinPotion)
_R.reg("StrongStoneSkinPotion", StrongStoneSkinPotion)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").EventType.Spikes
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
