# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Weapon(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core/Weapon.gd"


	def attack(self, triggerEvent=None):
		res = self.dealDamage(triggerEvent)
		self.activate(res)


	def doCooldownEffect(self):
		if self.useStamina() == _H_1:
			self.attack()

	def _readyInit(self):
		super()._readyInit()
		self.damageSource = _H_2().setItem(self)



_R.reg("res://gd_core/Weapon.gd", Weapon)
_R.reg("Weapon", Weapon)
_R.reg("Weapon", Weapon)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").StaminaResult.Sufficient
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
_H_2 = _R.C("CoreDamageSource")
