# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StrongHealthPotion_2(_R.C("res://gd_core_items/HealthPotion.gd")):

	resource_path = "res://gd_core_items/StrongHealthPotion.gd"


	def onTriggerPotion(self, triggerEvent=None):
		super().onTriggerPotion(triggerEvent)
		self.giveRegeneration(self.getP4(), triggerEvent)


	def getTriggerPriority(self):
		return _H_1 + 1

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/StrongHealthPotion.gd", StrongHealthPotion_2)
_R.reg("StrongHealthPotion", StrongHealthPotion_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
