# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Wolpertinger_2(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Wolpertinger.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaRegenPerBuff = None
		self._numBuffs = 0

	@property
	def numBuffs(self):
		return self._numBuffs
	@numBuffs.setter
	def numBuffs(self, v):
		self._numBuffs = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.addSpeed(_div(self.getNumAffectedItems() * self.getP3(), 100.0))
		self.connectToCharacterBuffs("onBuffChanged")
		baseStaminaRegen = self.character().baseStaminaRegen
		self.staminaRegenPerBuff = _div(self.getP1() * baseStaminaRegen, 100.0)


	def doCooldownEffect(self):
		self.giveLeastBuffs(self.numBuffs)
		self.activate()


	def onBuffChanged(self, amount, event):

		self.character().giveStaminaRegeneration(amount * self.staminaRegenPerBuff)

	def _readyInit(self):
		super()._readyInit()
		self.numBuffs = self.getP2()


_R.reg("res://gd_core_items/Wolpertinger.gd", Wolpertinger_2)
_R.reg("Wolpertinger", Wolpertinger_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Pet
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
