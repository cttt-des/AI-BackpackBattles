# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Scissorswords(_R.C("res://gd_core_items/Lightsaber.gd")):

	resource_path = "res://gd_core_items/Exclusive/Scissorswords.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luckNeeded = None
		self.bonusDam = None
		self.luck = None
		self.regen = None


	def inflict(self, duration, event):
		super().inflict(duration, event)
		self.giveStacksTemporary(self.character(), _H_1, 
			self.blind, duration, event)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if self.character().getLucky() >= self.luckNeeded:
				event = self.useLucky(self.luckNeeded, damageRes.event)
				self.addBonusDamage(self.bonusDam)
				self.giveRegeneration(self.regen, event)
		else:
			self.giveLucky(self.luck, damageRes.event)

	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = int(self.getP("luckt"))
		self.bonusDam = self.getP("dam")
		self.luck = int(self.getP("luck"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/Scissorswords.gd", Exclusive__Scissorswords)
_R.reg("Scissorswords", Exclusive__Scissorswords)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
